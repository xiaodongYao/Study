#pragma once

///////////////////////////////////////////////////////////////////////////////
// Vectors.h
// =========
// 2D/3D/4D vectors
//
//  AUTHOR: yao xiao dong
// CREATED: 2025-02-09
//
// Copyright (C) 2025 yao xiao dong
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
///////////////////////////////////////////////////////////////////////////////
// 2D vector
///////////////////////////////////////////////////////////////////////////////

struct Vector2
{
	float x, y;
	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}

	//Utility functions
	Vector2& Set(float x, float y);
	float		Length() const;
	float		distance(const Vector2& vec) const;			//distance between two vectors
	Vector2& Normalize();
	float		dot(const Vector2& vec) const;				//dot product
	float		equal(const Vector2& vec, float e) const;	//compare with epsilon

	//operators
	Vector2		operator-() const;							//unary operator (negate)
	Vector2		operator+(const Vector2& rhs) const;		//add rhs
	Vector2		operator-(const Vector2& rhs) const;		//subtract rhs
	Vector2& operator+=(const Vector2& rhs);		//add rhs and update this object
	Vector2& operator-=(const Vector2& rhs);		//subtract rhs and update this object

	Vector2		operator*(const float scale) const;			//scale
	Vector2		operator*(const Vector2& rhs) const;		//multiply each elements
	Vector2& operator*=(const float scale);				//scale and update this object
	Vector2& operator*=(const Vector2& rhs);				//multiply each element and update this object
	Vector2		operator/(const float scale) const;			//inverse scale
	Vector2& operator/=(const float scale);				//scale and update this object

	bool		operator==(const Vector2& rhs) const;		// exact compare, no epsilon //精确比较，没有epsilon
	bool		operator!=(const Vector2& rhs) const;		// exact compare, no epsilon 
	bool		operator<(const Vector2& rhs) const;		// comparison for sort
	float		operator[](int index) const;				// subscript operator v[0], v[1]
	float& operator[](int index);						// subscript operator v[0], v[1]

	friend Vector2 operator*(const float a, const Vector2 vec);
	friend std::ostream& operator<<(std::ostream& os, const Vector2& vec);
};


///////////////////////////////////////////////////////////////////////////////
// 3D vector
///////////////////////////////////////////////////////////////////////////////

struct  Vector3
{
	float x, y, z;
	Vector3() : x(0), y(0), z(0) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	//Utility functions
	Vector3& Set(float x, float y, float z);
	float		Length() const;
	float		distance(const Vector3& vec) const;			//distance between two vectors
	float		angle(const Vector3& vec) const;			//angle between two vectors
	Vector3& Normalize();
	float		dot(const Vector3& vec) const;				//dot product
	Vector3		cross(const Vector3& vec) const;			//cross product
	float		equal(const Vector3& vec, float e) const;	//compare with epsilon
	//operators
	Vector3		operator-() const;							//unary operator (negate)
	Vector3		operator+(const Vector3& rhs) const;		//add rhs
	Vector3		operator-(const Vector3& rhs) const;		//subtract rhs
	Vector3& operator+=(const Vector3& rhs);		//add rhs and update this object
	Vector3& operator-=(const Vector3& rhs);		//subtract rhs and update this object
	Vector3		operator*(const float scale) const;			//scale
	Vector3		operator*(const Vector3& rhs) const;		//multiply each elements
	Vector3& operator*=(const float scale);				//scale and update this object
	Vector3& operator*=(const Vector3& rhs);				//multiply each element and update this object
	Vector3		operator/(const float scale) const;			//inverse scale
	Vector3& operator/=(const float scale);				//scale and update this object
	bool		operator==(const Vector3& rhs) const;		// exact compare, no epsilon //精确比较，没有epsilon
	bool		operator!=(const Vector3& rhs) const;		// exact compare, no epsilon 
	bool		operator<(const Vector3& rhs) const;		// comparison for sort
	float		operator[](int index) const;				// subscript operator v[0], v[1], v[2]
	float& operator[](int index);						// subscript operator v[0], v[1], v[2]

	friend Vector3 operator*(const float a, const Vector3 vec);
	friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);
};

///////////////////////////////////////////////////////////////////////////////
// 4D vector
///////////////////////////////////////////////////////////////////////////////
struct Vector4
{
	float x, y, z, w;
	Vector4() : x(0), y(0), z(0), w(0) {}
	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	//Utility functions
	Vector4& Set(float x, float y, float z, float w);
	float		Length() const;
	float		distance(const Vector4& vec) const;			//distance between two vectors
	Vector4& Normalize();
	float		dot(const Vector4& vec) const;				//dot product
	float		equal(const Vector4& vec, float e) const;	//compare with epsilon
	//operators
	Vector4		operator-() const;							//unary operator (negate)
	Vector4		operator+(const Vector4& rhs) const;		//add rhs
	Vector4		operator-(const Vector4& rhs) const;		//subtract rhs
	Vector4& operator+=(const Vector4& rhs);		//add rhs and update this object
	Vector4& operator-=(const Vector4& rhs);		//subtract rhs and update this object
	Vector4		operator*(const float scale) const;			//scale
	Vector4		operator*(const Vector4& rhs) const;		//multiply each elements
	Vector4& operator*=(const float scale);				//scale and update this object
	Vector4& operator*=(const Vector4& rhs);				//multiply each element and update this object
	Vector4		operator/(const float scale) const;			//inverse scale
	Vector4& operator/=(const float scale);				//scale and update this object
	bool		operator==(const Vector4& rhs) const;		// exact compare, no epsilon //精确比较，没有epsilon
	bool		operator!=(const Vector4& rhs) const;		// exact compare, no epsilon 
	bool		operator<(const Vector4& rhs) const;		// comparison for sort
	float		operator[](int index) const;				// subscript operator v[0], v[1], v[2], v[3]
	float& operator[](int index);						// subscript operator v[0], v[1],v[2], v[3]

	friend Vector4 operator*(const float a, const Vector4 vec);
	friend std::ostream& operator<<(std::ostream& os, const Vector4& vec);
};

//著名的快速平方根倒数算法 Fast Inverse Square Root
//fast math routines from Doom3 SDK
inline float InvSqrt(float x)
{
	float xhalf = 0.5f * x;
	int i = *(int*)&x;
	i = 0x5f3759df - (i >> 1);
	x = *(float*)&i;
	x = x * (1.5f - xhalf * x * x);
	return x;
}

///////////////////////////////////////////////////////////////////////////////
// inline functions for Vector2
///////////////////////////////////////////////////////////////////////////////
inline Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

inline Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

inline Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

inline Vector2& Vector2::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

inline Vector2 Vector2::operator*(const float a) const
{
	return Vector2(x * a, y * a);
}

inline Vector2 Vector2::operator*(const Vector2& rhs) const
{
	return Vector2(x * rhs.x, y * rhs.y);
}

inline Vector2& Vector2::operator*=(const float a)
{
	x *= a;
	y *= a;
	return *this;
}

inline Vector2& Vector2::operator*=(const Vector2& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

inline Vector2 Vector2::operator/(const float a) const
{
	return Vector2(x / a, y / a);
}

inline Vector2& Vector2::operator/=(const float a)
{
	x /= a;
	y /= a;
	return *this;
}

inline bool Vector2::operator==(const Vector2& rhs) const
{
	return (x == rhs.x) && (y == rhs.y);
}

inline bool Vector2::operator!=(const Vector2& rhs) const
{
	return (x != rhs.x) || (y != rhs.y);
}

inline bool Vector2::operator<(const Vector2& rhs) const
{
	if (x < rhs.x) return true;
	if (x > rhs.x) return false;
	if (y < rhs.y) return true;
	if (y > rhs.y) return false;
	return false;
}

inline float Vector2::operator[](int index) const
{
	return (&x)[index];
}

inline float& Vector2::operator[](int index)
{
	return (&x)[index];
}

inline Vector2& Vector2::Set(float x, float y)
{
	this->x = x;
	this->y = y;
	return *this;
}

inline float Vector2::Length() const
{
	return sqrtf(x * x + y * y);
}

inline float Vector2::distance(const Vector2& vec) const
{
	float dx = x - vec.x;
	float dy = y - vec.y;
	return sqrtf(dx * dx + dy * dy);
}

inline Vector2& Vector2::Normalize()
{
	//const float EPSILON = 0.000001f;
	//if (x * x + y * y < EPSILON)
	//{
		//return *this;
	//}
	float inv = 1.0f / sqrtf(x * x + y * y);
	//float inv = InvSqrt(x * x + y * y);
	x *= inv;
	y *= inv;
	return *this;
}

inline float Vector2::dot(const Vector2& rhs) const
{
	return x * rhs.x + y * rhs.y;
}

inline float Vector2::equal(const Vector2& rhs, float epsilon) const
{
	return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon;
}

inline Vector2 operator*(const float a, const Vector2 vec)
{
	return Vector2(a * vec.x, a * vec.y);
}

inline std::ostream& operator<<(std::ostream& os, const Vector2& vec)
{
	os << "(" << vec.x << ", " << vec.y << ")";
	return os;
}
//End of Vector2 //////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// inline functions for Vector3
///////////////////////////////////////////////////////////////////////////////

inline Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

inline Vector3 Vector3::operator+(const Vector3& rhs) const
{
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

inline Vector3 Vector3::operator-(const Vector3& rhs) const
{
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

inline Vector3& Vector3::operator+=(const Vector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

inline Vector3 Vector3::operator*(const float a) const
{
	return Vector3(x * a, y * a, z * a);
}

inline Vector3 Vector3::operator*(const Vector3& rhs) const
{
	return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
}

inline Vector3& Vector3::operator*=(const float a)
{
	x *= a;
	y *= a;
	z *= a;
	return *this;
}

inline Vector3& Vector3::operator*=(const Vector3& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

inline Vector3 Vector3::operator/(const float a) const
{
	return Vector3(x / a, y / a, z / a);
}

inline Vector3& Vector3::operator/=(const float a)
{
	x /= a;
	y /= a;
	z /= a;
	return *this;
}

inline bool Vector3::operator==(const Vector3& rhs) const
{
	return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}

inline bool Vector3::operator!=(const Vector3& rhs) const
{
	return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
}

inline bool Vector3::operator<(const Vector3& rhs) const
{
	if (x < rhs.x) return true;
	if (x > rhs.x) return false;
	if (y < rhs.y) return true;
	if (y > rhs.y) return false;
	if (z < rhs.z) return true;
	if (z > rhs.z) return false;
	return false;
}

inline float Vector3::operator[](int index) const
{
	return (&x)[index];
}

inline float& Vector3::operator[](int index)
{
	return (&x)[index];
}

inline Vector3& Vector3::Set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

inline float Vector3::Length() const
{
	return sqrtf(x * x + y * y + z * z);
}

inline float Vector3::distance(const Vector3& vec) const
{
	float dx = x - vec.x;
	float dy = y - vec.y;
	float dz = z - vec.z;
	return sqrtf(dx * dx + dy * dy + dz * dz);
}

inline float Vector3::angle(const Vector3& vec) const
{
	// return angle between [0, 180]
	//float l1 = this->Length();
	//float l2 = vec.Length();
	//float d = this->dot(vec);
	//float angle = acosf(d / (l1 * l2)) / 3.141592f * 180.0f;
	//return angle;

	//return angle between [0, 180]
	float lenProduct = this->Length() * vec.Length();
	// Divide by zero check
	if (lenProduct < 1e-6f)
		lenProduct = 1e-6f;
	float f = dot(vec) / lenProduct;
	f = f < -1.0f ? -1.0f : (f > 1.0f ? 1.0f : f);
	return acosf(f);
}

inline Vector3& Vector3::Normalize()
{
	//const float EPSILON = 0.000001f;
	//if (x * x + y * y + z * z < EPSILON)
	//{
		//return *this;
	//}
	float inv = 1.0f / sqrtf(x * x + y * y + z * z);
	//float inv = InvSqrt(x * x + y * y + z * z);
	x *= inv;
	y *= inv;
	z *= inv;
	return *this;
}

inline float Vector3::dot(const Vector3& rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

inline Vector3 Vector3::cross(const Vector3& rhs) const
{
	return Vector3(
		y * rhs.z - z * rhs.y,
		z * rhs.x - x * rhs.z,
		x * rhs.y - y * rhs.x);
}

inline float Vector3::equal(const Vector3& rhs, float epsilon) const
{
	return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon && fabs(z - rhs.z) < epsilon;
}

inline Vector3 operator*(const float a, const Vector3 vec)
{
	return Vector3(a * vec.x, a * vec.y, a * vec.z);
}

inline std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
	os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	return os;
}
//End of Vector3 //////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// inline functions for Vector4
///////////////////////////////////////////////////////////////////////////////
inline Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, -w);
}

inline Vector4 Vector4::operator+(const Vector4& rhs) const
{
	return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

inline Vector4 Vector4::operator-(const Vector4& rhs) const
{
	return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

inline Vector4& Vector4::operator+=(const Vector4& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}

inline Vector4& Vector4::operator-=(const Vector4& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}

inline Vector4 Vector4::operator*(const float a) const
{
	return Vector4(x * a, y * a, z * a, w * a);
}

inline Vector4 Vector4::operator*(const Vector4& rhs) const
{
	return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

inline Vector4& Vector4::operator*=(const float a)
{
	x *= a;
	y *= a;
	z *= a;
	w *= a;
	return *this;
}

inline Vector4& Vector4::operator*=(const Vector4& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	w *= rhs.w;
	return *this;
}

inline Vector4 Vector4::operator/(const float a) const
{
	return Vector4(x / a, y / a, z / a, w / a);
}

inline Vector4& Vector4::operator/=(const float a)
{
	x /= a;
	y /= a;
	z /= a;
	w /= a;
	return *this;
}

inline bool Vector4::operator==(const Vector4& rhs) const
{
	return (x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (w == rhs.w);
}

inline bool Vector4::operator!=(const Vector4& rhs) const
{
	return (x != rhs.x) || (y != rhs.y) || (z != rhs.z) || (w != rhs.w);
}

inline bool Vector4::operator<(const Vector4& rhs) const
{
	if (x < rhs.x) return true;
	if (x > rhs.x) return false;
	if (y < rhs.y) return true;
	if (y > rhs.y) return false;
	if (z < rhs.z) return true;
	if (z > rhs.z) return false;
	if (w < rhs.w) return true;
	if (w > rhs.w) return false;
	return false;
}

inline float Vector4::operator[](int index) const
{
	return (&x)[index];
}

inline float& Vector4::operator[](int index)
{
	return (&x)[index];
}

inline Vector4& Vector4::Set(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	return *this;
}

inline float Vector4::Length() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

inline float Vector4::distance(const Vector4& vec) const
{
	float dx = x - vec.x;
	float dy = y - vec.y;
	float dz = z - vec.z;
	float dw = w - vec.w;
	return sqrtf(dx * dx + dy * dy + dz * dz + dw * dw);
}

inline Vector4& Vector4::Normalize()
{
	//const float EPSILON = 0.000001f;
	//if (x * x + y * y + z * z + w * w < EPSILON)
	//{
		//return *this;
	//}
	float inv = 1.0f / sqrtf(x * x + y * y + z * z + w * w);
	//float inv = InvSqrt(x * x + y * y + z * z + w * w);
	x *= inv;
	y *= inv;
	z *= inv;
	w *= inv;
	return *this;
}

inline float Vector4::dot(const Vector4& rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

inline float Vector4::equal(const Vector4& rhs, float epsilon) const
{
	return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon && fabs(z - rhs.z) < epsilon && fabs(w - rhs.w) < epsilon;
}

inline Vector4 operator*(const float a, const Vector4 vec)
{
	return Vector4(a * vec.x, a * vec.y, a * vec.z, a * vec.w);
}

inline std::ostream& operator<<(std::ostream& os, const Vector4& vec)
{
	os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
	return os;
}