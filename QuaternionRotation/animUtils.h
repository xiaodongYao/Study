#pragma once
///////////////////////////////////////////////////////////////////////////////
// animUtils.h
// ===========
//
//  AUTHOR: yao xiao dong
// CREATED: 2025-2-12
//
// Copyright 2025 yao xiao dong. All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#include "Vectors.h"
#include "Quaternion.h"

namespace Gil
{
	//enums
	enum AnimationMode
	{
		LINEAR = 0,
		EASE_IN,
		EASE_IN2,       // using circle
		EASE_OUT,
		EASE_OUT2,      // using circle
		EASE_IN_OUT,
		EASE_IN_OUT2,   // using circle
		BOUNCE,
		ELASTIC
	};


	// get current frame at given time (sec)
	// - return the current frame number
	int getFrame(int frameStart, int frameEnd, float elapsedTime, float frameRate = 30, bool loop = true);


	//spherical linear interpolation between 3D vectors 三维球面线性插值
	// alpha should be 0 ~ 1
	Vector3 slerp(const Vector3& from, const Vector3& to, float alpha, AnimationMode mode = LINEAR);

	//spherical linear interpolation between 2 quaternions 两个四元数之间的球面线性插值
	// the alpha value should be 0 ~ 1
	Quaternion slerp(const Quaternion& from, const Quaternion& to, float alpha, AnimationMode mode = LINEAR);


	// accelerate / deaccelerate speed
	// === PARAMS ===
	//  isMoving: accelerate if true, deaccelerate if false
	// currSpeed: the current speed
	//  maxSpeed: maximum speed (positive or negative)
	//     accel: acceleration (always positive)
	// deltaTime: frame time in second
	float accelerate(bool isMoving, float currSpeed, float maxSpeed, float accel, float deltaTime);


	// move from one point to the other
	// - the result will be stored in "vec"
	// - "speed" param is units/sec
	// - return "true" when it reaches "to" point
	template <class T>
	bool move(T& vec, const T& from, const T& to, float elapsedTime, float speed)
	{
		// check if it is moving to itself
		if (from == to)
		{
			vec = to;
			return true;
		}

		bool done = false;
		vec = to - from;
		float length1 = vec.Length();

		vec.Normalize();
		float distance = elapsedTime * speed;
		vec *= distance;
		float length2 = vec.Length();

		vec = from + vec;
		if (length2 > length1)
		{
			vec = to;
			done = true;
		}

		return done;
	}

	// linear interpolation: P = (1-t)*P1 + t* P2 //线性插值
	// use interpolate() for non-linear interpolations
	template <class T>
	T lerp(const T& from, const T& to, float alpha)
	{
		return from + alpha * (to - from);
	}

	// interpolate from one point to the other
	// - "alpha" param is interpolation value (0 ~ 1)
	// - "mode" param is animation mode
	// - return new vector after interpolation
	template <class T>
	T interpolate(const T& from, const T& to, float alpha, AnimationMode mode)
	{
		//const float PI = 3.141593f;
		//const float HALF_PI = 3.141593f * 0.5f;

		if (mode == EASE_IN)
		{
			//@@alpha = 1 - cosf(HALF_PI * alpha);
			// with cubic function
			alpha = alpha * alpha * alpha;
		}
		else if (mode == EASE_IN2)
		{
			alpha = 1.0f - sqrtf(1.0f - alpha * alpha);
		}
		else if (mode == EASE_OUT)
		{
			//@@alpha = sinf(HALF_PI * alpha);
			// with cubic function
			float beta = 1.0f - alpha;
			alpha = 1.0f - beta * beta * beta;
		}
		else if (mode == EASE_OUT2)
		{
			alpha = sqrtf(1.0f - (1.0f - alpha) * (1.0f - alpha));
		}
		else if (mode == EASE_IN_OUT)
		{
			//@@alpha = 0.5f * (1 - cosf(PI * alpha));
			// with cubic function
			float beta = 1.0f - alpha;
			float scale = 4.0f;     // 0.5 / (0.5^3)
			if (alpha < 0.5f)
				alpha = alpha * alpha * alpha * scale;
			else
				alpha = 1.0f - (beta * beta * beta * scale);
		}
		else if (mode == EASE_IN_OUT2)
		{
			if (alpha < 0.5f)
				alpha = 0.5f * (1.0f - sqrtf(1.0f - alpha * alpha));
			else
				alpha = 0.5f * sqrtf(1.0f - (1.0f - alpha) * (1.0f - alpha)) + 0.5f;
		}
		else if (mode == BOUNCE)
		{
		}
		else if (mode == ELASTIC)
		{
		}

		return from + alpha * (to - from);

	}
} //end of namespace Gil


