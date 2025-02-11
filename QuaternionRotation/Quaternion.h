#pragma once
///////////////////////////////////////////////////////////////////////////////
// Quaternion.h
// ============
// Quaternion class represented as sum of a scalar and a vector(rotation axis)
// parts; [s, v] = s + (ix + jy + kz)
//
// When the quaternion is used for 3D rotation, initialize the quaternion with
// the rotation axis (unit vector) and the half rotation angle (radian) because
// of double multiplication, qpq*.
// q = cos(a) + sin(a)(ix + jy + kz)
//
// If there is no rotation, initialize the quaternion (1,0,0,0) because of
// cos(0) = 1, sin(0) = 0
//
//  AUTHOR: yao xiao dong
// CREATED: 2025-02-11
//
// Copyright (C) 2015 yao xiao dong
///////////////////////////////////////////////////////////////////////////////

#include "Vectors.h"
#include "Matrices.h"


struct Quaternion
{
	float s;  //scalar part
	float x, y, z; //vector part

	//constructors
	Quaternion() : s(0), x(0), y(0), z(0) {}
	Quaternion(float s, float x, float y, float z) : s(s), x(x), y(y), z(z) {}
	Quaternion(const Vector3& axis, float angle); // rot axis & angle (radian)

	//Uti functions
	void	Set(float s, float x, float y, float z);
	void	Set(const Vector3& axis, float angle); // half angle (radian)
	float	length() const;
	Quaternion& normalize();
	Quaternion& conjugate(); //conjugate of quaternion //¹²éî
	Quaternion& invert(); //inverse of quaternion //Äæ
	Matrix4 getMatrix() const;
	Vector3 getVector() const;

	//operators
	Quaternion operator-() const; //unary operator (negate)
	Quaternion operator+(const Quaternion& rhs) const; //addition
	Quaternion operator-(const Quaternion& rhs) const; //subtraction
	Quaternion operator*(float a) const; //scalar multiplication
	Quaternion operator*(const Quaternion& rhs) const; //multiplication
	Quaternion operator*(const Vector3& v) const;      // conjugation for rotation

	Quaternion& operator+=(const Quaternion& rhs); //addition and update
	Quaternion& operator-=(const Quaternion& rhs); //subtraction and update
	Quaternion& operator*=(float a); //scalar multiplication and update
	Quaternion& operator*=(const Quaternion& rhs); //quaternion multiplication and update

	bool operator==(const Quaternion& rhs) const; // exact compare, no epsilon
	bool operator!=(const Quaternion& rhs) const; // exact compare, no epsilon

	//friend functions
	friend Quaternion operator*(float a, const Quaternion& q); //pre-multiplication
	friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);

	//static functions
	// find quaternion for rotating from v1 to v2
	static Quaternion RotationArc(const Vector3& v1, const Vector3& v2);

	//return quaternion from Euler angles (x,y) or (x,y,z)
	//The rotation order is x->y->z
};