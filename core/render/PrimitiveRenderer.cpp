#include "PrimitiveRenderer.h"


PrimitiveRenderer::PrimitiveRenderer(){

	shader = new PrimitiveShader();

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	glGenBuffers(1, &vertexVboID);
	glGenBuffers(1, &colorVboID);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVboID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVboID);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

}

PrimitiveRenderer::~PrimitiveRenderer(){
}

void PrimitiveRenderer::beginRender(Camera * cam){
	shader->use();
	shader->loadProjViewMatrix(cam->createProjectionViewMatrix());
}

void PrimitiveRenderer::endRender(){
	shader->stop();
	
}

void PrimitiveRenderer::render(Camera * cam, std::map<GLenum, std::vector<Primitive*>>& primitives){
	beginRender(cam);

	for (auto i = primitives.begin(); i != primitives.end(); i++) {
		std::vector<Primitive *> & ps = i->second;
		int size, pointer;
		vec3 * vertexArr, * colorArr;
		switch (i->first) {
			case GL_POINTS:
			case GL_LINES:
				size = 0;
				for (Primitive * p : ps)
					size += p->getSize();

				vertexArr = new vec3[size];
				colorArr = new vec3[size];

				pointer = 0;
				for (Primitive * p : ps) {
					memcpy_s(vertexArr + pointer, p->getSize() * sizeof(vec3), p->getPoints(), p->getSize() * sizeof(vec3));
					for (int i = 0; i < p->getSize(); i++)
						colorArr[pointer + i] = p->getColor();

					pointer += p->getSize();
				}

				shader->loadUseUniformColor(false);

				glBindVertexArray(vaoID);

				glBindBuffer(GL_ARRAY_BUFFER, vertexVboID);
				glBufferData(GL_ARRAY_BUFFER, size * sizeof(vec3), vertexArr, GL_DYNAMIC_DRAW);

				glBindBuffer(GL_ARRAY_BUFFER, colorVboID);
				glBufferData(GL_ARRAY_BUFFER, size * sizeof(vec3), colorArr, GL_DYNAMIC_DRAW);

				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);

				glDrawArrays(i->first, 0, size);

				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);

				glBindVertexArray(0);

				delete[] vertexArr;
				delete[] colorArr;

				break;

			case GL_LINE_STRIP:

				for (Primitive * p : ps) {
					shader->loadUseUniformColor(true);
					shader->loadUniformColor(p->getColor());

					glBindVertexArray(vaoID);

					glBindBuffer(GL_ARRAY_BUFFER, vertexVboID);
					glBufferData(GL_ARRAY_BUFFER, p->getSize() * sizeof(vec3), p->getPoints(), GL_DYNAMIC_DRAW);
					
					glEnableVertexAttribArray(0);

					glDrawArrays(p->getType(), 0, p->getSize());

					glDisableVertexAttribArray(0);

					glBindVertexArray(0);
				}

				break;
		}
	}

	endRender();
}