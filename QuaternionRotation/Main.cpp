#include <GL/freeglut.h>
#include <iostream>
#include "Vectors.h"
#include "Matrices.h"
#include "Quaternion.h"
#include "Timer.h"

int main(int argc, char* argv[])
{
	Vector4 vec(1, 1, 1, 1);
	std::cout << vec << std::endl;


	Matrix2 m;
	m.identity();
	std::cout << m << std::endl;

	std::cout << "Hello World" << std::endl;


	return 0;
}