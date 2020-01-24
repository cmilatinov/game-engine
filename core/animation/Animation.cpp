#include "Animation.h"

Joint::~Joint() {
	for (Joint * child : children)
		delete child;
}


vec3 TranslationKeyframe::interpolate(TranslationKeyframe * previous, TranslationKeyframe * next, float progress) {
	return previous->translation + progress * (next->translation - previous->translation);
}
vec4 RotationKeyframe::interpolate(RotationKeyframe * previous, RotationKeyframe * next, float progress) {
	return nlerp(previous->rotation, next->rotation, progress);
}
vec3 ScaleKeyframe::interpolate(ScaleKeyframe * previous, ScaleKeyframe * next, float progress) {
	return previous->scale + progress * (next->scale - previous->scale);
}


AnimationKeyframes::~AnimationKeyframes() {
	for (TranslationKeyframe * t : translations)
		delete t;
	for (RotationKeyframe * r : rotations)
		delete r;
	for (ScaleKeyframe * s : scales)
		delete s;
}

vector<TranslationKeyframe*> AnimationKeyframes::getPreviousAndNextTranslations(float animTime) {
	vector<TranslationKeyframe*> result;
	for (int k = translations.size() - 1; k >= 0; k--) {
		if (animTime >= translations[k]->time) {
			result.push_back(translations[k]);
			result.push_back(translations[(k + 1) % translations.size()]);
			return result;
		}
	}
	return result;
}
vector<RotationKeyframe*> AnimationKeyframes::getPreviousAndNextRotations(float animTime) {
	vector<RotationKeyframe*> result;
	for (int k = rotations.size() - 1; k >= 0; k--) {
		if (animTime >= rotations[k]->time) {
			result.push_back(rotations[k]);
			result.push_back(rotations[(k + 1) % rotations.size()]);
			return result;
		}
	}
	return result;
}
vector<ScaleKeyframe*> AnimationKeyframes::getPreviousAndNextScales(float animTime) {
	vector<ScaleKeyframe*> result;
	for (int k = scales.size() - 1; k >= 0; k--) {
		if (animTime >= scales[k]->time) {
			result.push_back(scales[k]);
			result.push_back(scales[(k + 1) % scales.size()]);
			return result;
		}
	}
	return result;
}


Animation::~Animation() {
	for (auto it = keyframes.begin(); it != keyframes.end(); it++)
		delete it->second;
}


Animator::Animator(Joint * root, mat4 globalInverseTransform) {
	preorder(root, [this](Joint * joint) {
		this->joints[joint->name] = joint;
		this->numJoints++;
	});
	this->globalInverseTransform = globalInverseTransform;
	this->animTransforms = new mat4[numJoints];
	this->root = root;
	this->anim = nullptr;
	this->animTime = 0;
	this->playing = false;
}
Animator::~Animator() {
	delete[] animTransforms;
	delete root;
}

void Animator::preorder(Joint * current, function<void(Joint*)> callback) {
	callback(current);

	if (current->children.empty())
		return;

	for (int c = 0; c < current->children.size(); c++)
		preorder(current->children[c], callback);
}
void Animator::applyPoseToJoints(map<string, mat4> & pose, Joint * joint, mat4 & parentTransform) {
	mat4 currentTransform = parentTransform * pose[joint->name];
	animTransforms[joint->index] = globalInverseTransform * currentTransform * joint->transform;

	for (Joint* child : joint->children)
		applyPoseToJoints(pose, child, currentTransform);
}

Animator * Animator::use(Animation * anim) {
	this->anim = anim;
	return this;
}
Animator * Animator::seek(float time) {
	this->animTime = time;
	return this;
}
Animator * Animator::play() {
	this->playing = true;
	computeTransforms();
	return this;
}
Animator * Animator::stop() {
	this->playing = false;
	return this;
}

mat4 * Animator::computeTransforms()  {
	
	// Create the current pose based on the animation time
	map<string, mat4> pose;
	for (auto it = anim->keyframes.begin(); it != anim->keyframes.end(); it++) {

		// Translation
		vector<TranslationKeyframe*> tKeys = it->second->getPreviousAndNextTranslations(animTime);
		vec3 translation = TranslationKeyframe::interpolate(tKeys[0], tKeys[1], (animTime - tKeys[0]->time) / (tKeys[1]->time - tKeys[0]->time));

		// Rotation
		vector<RotationKeyframe*> rKeys = it->second->getPreviousAndNextRotations(animTime);
		vec4 rotation = RotationKeyframe::interpolate(rKeys[0], rKeys[1], (animTime - rKeys[0]->time) / (rKeys[1]->time - rKeys[0]->time));
		
		// Scale
		vector<ScaleKeyframe*> sKeys = it->second->getPreviousAndNextScales(animTime);
		vec3 scale = ScaleKeyframe::interpolate(sKeys[0], sKeys[1], (animTime - sKeys[0]->time) / (sKeys[1]->time - sKeys[0]->time));

		// Convert the transformations to matrices
		mat4 matTranslation, matRotation, matScale;
		matTranslation = mat4().translate(translation);
		matRotation = glmath::toMatrix(rotation);
		matScale = mat4().scale(scale);

		// Combine the transformations into a single matrix
		pose[it->first] = matTranslation * matRotation * matScale;
	}
	
	// Apply the pose to the joints
	mat4 identity;
	applyPoseToJoints(pose, root, identity);

	return animTransforms;
}

Animator * Animator::update(float delta) {
	if(playing)
		animTime = std::fmodf(animTime + delta, anim->duration);
	//std::cout << animTime << std::endl;
	return this;
}