#include <string>
#include <vector>

#include "GLMatrix.h"
#include "Mesh.h"

using namespace glmath;
using std::string;
using std::vector;

#pragma once

// Represents a single bone of a mesh's skeleton
struct Joint {
	unsigned int index;
	string name;
	mat4 offset;
	vector<Joint*> children;
};

// Represents a transform applied to a joint
struct JointTransform {
	unsigned int targetIndex;
	string targetName;
	vec4 rotation;
	vec3 scale;
	vec3 translation;
};

// Reresents a keyframe at a specific time in an animation, 0 being the beginning of the animation
struct AnimationKeyframe {
	JointTransform * transform;
	double time;
};

// Represents an animation with a set of keyframes and a duration in seconds
struct Animation {
	string name;
	vector<AnimationKeyframe*> keyframes;
	double animTime;
	double ticksPerSecond;
};

// Applies the correct pose at the correct time of an animation for each joint by interpolating between keyframes
class Animator {

	private: 
		Animation * anim;

	public:


};