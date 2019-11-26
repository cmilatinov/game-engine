#include <iostream>
#include <chrono>

#include <glfw/glfw3.h>

#include "Mouse.h"
#include "Keyboard.h"
#include "Display.h"

#include "MeshShader.h"
#include "VAO.h"
#include "FBO.h"
#include "Loader.h"
#include "CameraFPS.h"

using namespace std;

int main() {

	// Init GLFW.
	if (glfwInit() == GLFW_FALSE)
		return ERR_GLFW_INIT;

	// OpenGL version.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Compatibility profile.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	// Enable forward compatibility.
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the display.
	Display * display = (new Display())->setResizable(true)->setSize(1280, 720)->setGrabMouse(true);
	if(display->createDisplay("THIS IS AN AWESOME TITLE") != ENG_SUCCESS)
		return ERR_CREATE_DISPLAY_FAILED;
	display->keyboard->registerKeyUp(GLFW_KEY_ESCAPE, [display] { glfwSetWindowShouldClose(display->window, GLFW_TRUE); });

	// Load the OpenGL API capabilities.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return ERR_GLAD_INIT;

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	// Mesh shader
	MeshShader * shader = new MeshShader();
	
	// Load model matrix into shader
	shader->use();

	shader->loadTextureUnit(0);

	mat4 mat = glmath::Mat4Identity;
	mat.translate(vec3(0, 0, -10.0f));
	mat.rotate(-PI / 2, vec3(1, 0, 0));
	shader->loadModelMatrix(mat);

	shader->stop();
	
	// Camera
	Camera * cam = new CameraFPS(16, 9, 70.0f, display->mouse, display->keyboard);

	// Loader
	Loader * loader = new Loader();

	// Load mesh and texture
	Mesh * mesh = loader->loadMesh("character.dae");
	Texture * texture = loader->loadTexture2D("character.png", GL_LINEAR);

	// Create fbo used to implement multisampling.
	FBO * fbo = FBO::create(display->getDisplaySize().x, display->getDisplaySize().y, 8)
		->addAttachment(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_COLOR_ATTACHMENT0, false)
		->addAttachment(GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_FLOAT, GL_DEPTH_ATTACHMENT, false)
		->bindAttachments()
		->unbind();

	// Last frame timestamp.
	auto last = chrono::high_resolution_clock::now();

	while( !display->shouldClose() ) {

		auto now = chrono::high_resolution_clock::now();
		float delta = chrono::duration_cast<chrono::nanoseconds>(now - last).count() / 1e9f;

		// ========================== BEGIN RENDER ==========================
		fbo->bind();

		glClearColor(1.0f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam->update(delta);

		shader->use();
		mat4 pView = cam->createProjectionViewMatrix();
		shader->loadProjViewMatrix(pView);

		// Bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(texture->getType(), texture->getID());

		// Render mesh
		mesh->getVAO()->bind({ 0, 1, 2 });
		glDrawElements(GL_TRIANGLES, mesh->getVertexCount(), GL_UNSIGNED_INT, 0);
		mesh->getVAO()->unbind({ 0, 1, 2 });

		shader->stop();
		fbo->unbind();
		// =========================== END RENDER ===========================

		// Copy the framebuffer contents to the main framebuffer.
		fbo->resolveToDisplay(display, GL_COLOR_ATTACHMENT0);

		// Update the display.
		display->update();

		// Set last frame time.
		last = now;

	}

	VAO::cleanAll();

	delete fbo;

	delete mesh;
	delete texture;

	delete loader;

	delete cam;

	delete shader;

	delete display;

	glfwTerminate();
	
	return 0;
}