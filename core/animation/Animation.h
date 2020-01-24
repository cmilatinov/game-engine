#include <string>
#include <vector>
#include <functional>

#include "../math/GLMatrix.h"
#include "../objects/Mesh.h"

using namespace glmath;
using std::string;
using std::vector;
using std::map;
using std::function;

#pragma once

// Represents a single bone of a mesh's skeleton
struct Joint {
	unsigned int index;
	string name;
	mat4 transform;
	vector<Joint*> children;

	~Joint();
};

// Animation translation keyframe
struct TranslationKeyframe {
	vec3 translation;
	float time;

	static vec3 interpolate(TranslationKeyframe * previous, TranslationKeyframe * next, float progress);
};

// Animation rotation keyframe
struct RotationKeyframe {
	vec4 rotation;
	float time;

	static vec4 interpolate(RotationKeyframe * previous, RotationKeyframe * next, float progress);
};

// Animation scale keyframe
struct ScaleKeyframe {
	vec3 scale;
	float time;

	static vec3 interpolate(ScaleKeyframe * previous, ScaleKeyframe * next, float progress);
};

// Combination of all keyframes
struct AnimationKeyframes {
	vector<TranslationKeyframe*> translations;
	vector<RotationKeyframe*> rotations;
	vector<ScaleKeyframe*> scales;

	~AnimationKeyframes();

	vector<TranslationKeyframe*> getPreviousAndNextTranslations(float time);
	vector<RotationKeyframe*> getPreviousAndNextRotations(float time);
	vector<ScaleKeyframe*> getPreviousAndNextScales(float time);
};

// Represents an animation with a set of keyframes for each joint and a duration in seconds
struct Animation {
	string name;
	map<string, AnimationKeyframes*> keyframes;
	float duration;
	float ticksPerSecond;

	~Animation();
};

// Applies the correct pose at the correct time of an animation for each joint by interpolating between keyframes
class Animator {

	private:

		// Animation to play
		Animation * anim;
		float animTime;
		bool playing;

		// Skeleton data
		unsigned int numJoints;
		map<string, Joint *> joints;
		Joint * root;

		// Global inverse skeleton transform
		mat4 globalInverseTransform;

		// Joint transforms
		mat4 * animTransforms;


		// Performs preorder traversal of a joint tree
		void preorder(Joint * current, function<void(Joint *)> callback);
		
		// Applies a transform to a joint and its children
		void applyPoseToJoints(map<string, mat4> & rotation, Joint * joint, mat4 & parentTransform);
		
	public:
		Animator(Joint * root, mat4 globalInverseTransform);
		~Animator();

		// Set the current animation
		Animator * use(Animation * anim);

		// Set the current animation time
		Animator * seek(float time);

		// Play the animation
		Animator * play();

		// Stop the animation
		Animator * stop();

		// Compute joint transformation matrices
		mat4 * computeTransforms();
		
		// Increment the animation time
		Animator * update(float delta);

		// Number of joints in the skeleton
		inline unsigned int getJointCount() const { return numJoints; };
};