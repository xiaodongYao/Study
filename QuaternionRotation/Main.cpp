#include <GL/freeglut.h>
#include <iostream>
#include "Vectors.h"
#include "Matrices.h"

int main(int argc, char* argv[])
{
	Vector4 vec(1, 1, 1, 1);
	std::cout << vec << std::endl;


	Matrix2 m;
	m.identity();
	std::cout << m << std::endl;

	std::cout << "Hello World" << std::endl;


	double num = 123.456789;

	//// 使用 fixed 和 setprecision 控制输出
	//std::cout << std::fixed << std::setprecision(2) << num << std::endl;  // 输出: 123.46

	//// 重置格式化标志
	//std::cout << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);

	//// 恢复默认格式
	//std::cout << num << std::endl;  // 输出: 123.457（默认格式）


	return 0;
}