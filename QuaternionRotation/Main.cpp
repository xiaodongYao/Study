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

	//// ʹ�� fixed �� setprecision �������
	//std::cout << std::fixed << std::setprecision(2) << num << std::endl;  // ���: 123.46

	//// ���ø�ʽ����־
	//std::cout << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);

	//// �ָ�Ĭ�ϸ�ʽ
	//std::cout << num << std::endl;  // ���: 123.457��Ĭ�ϸ�ʽ��


	return 0;
}