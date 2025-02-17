#include <GL/freeglut.h>
#include <iostream>
#include "Vectors.h"
#include "Matrices.h"
#include "Quaternion.h"
#include "Timer.h"

//constants
const float D2R = acos(-1.0f) / 180.0f;

int main(int argc, char** argv)
{
	// test quaternion ====================================
	Vector3 v(1, 2, 3);                             // 3D vertex to rotate
	Vector3 r(0.57735f, 0.57735f, 0.57735f);        // rotation axis (unit vector)
	float a = 45.0f;                                // rotation angle in degree
	Quaternion p = Quaternion(0, v.x, v.y, v.z);    // quaternion form of v
	Quaternion q = Quaternion(r, a * 0.5f * D2R);   // rotation quaternion
	Quaternion c = q;
	c.conjugate();                                  // q*
	Quaternion p2 = q * p * c;                      // rotate with quaternion, qpq*

	// verify the result by comparing with matrix rotation
	Matrix4 m;
	m.rotate(a, r);                                 // rotation matrix
	Vector3 v2 = m * v;                             // rotate vertex using matrix

	std::cout << "===== Test Quaternion Rotation =====" << std::endl;
	std::cout << "Vertex: " << v << std::endl;
	std::cout << "  Axis: " << r << std::endl;
	std::cout << " Angle: " << a << " degree" << std::endl;
	std::cout << std::endl;
	std::cout << "qpq* = (" << p2.x << ", " << p2.y << ", " << p2.z << ")" << std::endl;
	std::cout << "M*v  = " << v2 << std::endl;
	std::cout << std::endl;

	Timer t;

	// sequence of multiple rotations with quaternion form
	Quaternion qx = Quaternion(Vector3(1, 0, 0), 22.5f * D2R); // 45 degree about x-axis
	Quaternion qy = Quaternion(Vector3(0, 1, 0), 22.5f * D2R); // 45 degree about y-axis
	Quaternion qz = Quaternion(Vector3(0, 0, 1), 22.5f * D2R); // 45 degree about z-axis
	t.start();
	q = qx * qy * qz;										// rotation order: qz -> qy -> qx
	t.stop();

	std::cout << "Multiple Rotations, qx*qy*qz = " << q << std::endl;
	std::cout << q.getMatrix() << std::endl;
	std::cout << "Elapsed Time: " << t.getElapsedTimeInMicroSec() << " us\n" << std::endl;

	// sequence of multiple rotations with matrix form
	Matrix4 mx = Matrix4().rotateX(45);
	Matrix4 my = Matrix4().rotateY(45);
	Matrix4 mz = Matrix4().rotateZ(45);
	t.start();
	m = mx * my * mz;
	t.stop();
	// compare the result with the quaternion
	std::cout << "Multiple Rotations, Mx*My*Mz = \n" << m << std::endl;
	std::cout << "Elapsed Time: " << t.getElapsedTimeInMicroSec() << " us" << std::endl;
	//=====================================================

	return 0;
}