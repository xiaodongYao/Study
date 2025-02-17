#include <GL/freeglut.h>
#include <iostream>
#include "Vectors.h"
#include "Matrices.h"
#include "Quaternion.h"
#include "Timer.h"
#include <sstream>

//GLUT CALLBACK functions//////////////////////////////////////////////////////////////////////////
void displayCB();
void reshapeCB(int w, int h);
void timerCB(int millisec);
//void idleCB();
void keyboardCB(unsigned char key, int x, int y);
void mouseCB(int button, int stat, int x, int y);
void mouseMotionCB(int x, int y);
void mousePassiveMotionCB(int x, int y);

//CALLBACK function when exit() called//////////////////////////////////////////////////////////////////////////
void exitCB();

//function declearations//////////////////////////////////////////////////////////////////////////
void initGL();
int  initGLUT(int argc, char** argv);
bool initSharedMem();
void clearSharedMem();
void initLights();
void drawString(const char* str, int x, int y, float color[4], void* font);
void drawString3D(const char* str, float pos[3], float color[4], void* font);
void showInfo();
void drawCube();
void draw();

//constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const float ANIM_DURATION = 200.0f;     // ms
const float D2R = acosf(-1.0f) / 180.0f;
const float R2D = 180.0f / acosf(-1.0);

//global varibales
void* font = GLUT_BITMAP_8_BY_13;
bool mouseLeftDown;
bool mouseRightDown;
float mouseX, mouseY;
//float cameraAngleX;
//float cameraAngleY;
float cameraDistance = 4;
int screenWidth, screenHeight;
int drawMode;
float frameTime;
float runTime;
Timer timer;
Quaternion quat;
Quaternion fromQ, toQ;
float fromX, fromY;     // prev mouse coords 上一个鼠标坐标
float animTime;


// cube ///////////////////////////////////////////////////////////////////////
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3

// vertex array for glDrawElements() and glDrawRangeElement() =================
GLfloat vertices[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,   1,-1, 1,   // v0,v1,v2,v3 (front)
					   1, 1, 1,   1,-1, 1,   1,-1,-1,   1, 1,-1,   // v0,v3,v4,v5 (right)
					   1, 1, 1,   1, 1,-1,  -1, 1,-1,  -1, 1, 1,   // v0,v5,v6,v1 (top)
					  -1, 1, 1,  -1, 1,-1,  -1,-1,-1,  -1,-1, 1,   // v1,v6,v7,v2 (left)
					  -1,-1,-1,   1,-1,-1,   1,-1, 1,  -1,-1, 1,   // v7,v4,v3,v2 (bottom)
					   1,-1,-1,  -1,-1,-1,  -1, 1,-1,   1, 1,-1 }; // v4,v7,v6,v5 (back)

// normal array
GLfloat normals[] = { 0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v0,v1,v2,v3 (front)
					   1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v0,v3,v4,v5 (right)
					   0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v0,v5,v6,v1 (top)
					  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,   // v1,v6,v7,v2 (left)
					   0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,   // v7,v4,v3,v2 (bottom)
					   0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1 }; // v4,v7,v6,v5 (back)

// color array
GLfloat colors[] = { 1, 1, 1,   1, 1, 0,   1, 0, 0,   1, 0, 1,   // v0,v1,v2,v3 (front)
					   1, 1, 1,   1, 0, 1,   0, 0, 1,   0, 1, 1,   // v0,v3,v4,v5 (right)
					   1, 1, 1,   0, 1, 1,   0, 1, 0,   1, 1, 0,   // v0,v5,v6,v1 (top)
					   1, 1, 0,   0, 1, 0,   0, 0, 0,   1, 0, 0,   // v1,v6,v7,v2 (left)
					   0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,   // v7,v4,v3,v2 (bottom)
					   0, 0, 1,   0, 0, 0,   0, 1, 0,   0, 1, 1 }; // v4,v7,v6,v5 (back)

// index array of vertex array for glDrawElements() & glDrawRangeElement()
GLubyte indices[] = { 0, 1, 2,   2, 3, 0,      // front
					   4, 5, 6,   6, 7, 4,      // right
					   8, 9,10,  10,11, 8,      // top
					  12,13,14,  14,15,12,      // left
					  16,17,18,  18,19,16,      // bottom
					  20,21,22,  22,23,20 };    // back


///////////////////////////////////////////////////////////////////////////////
// draw a cube with glDrawElements()
// The main advantage of glDrawElements() over glDrawArray() is that glDrawElements() allows hopping around the vertex array with the associated index values. 
// In a cube, the number of vertex data in the vertex array can be reduced to 24 vertices for glDrawElements().
// Note that you need an additional array (index array) to store how to traverse the vertext data. For a cube, we need 36 entries in the index array.
///////////////////////////////////////////////////////////////////////////////
void drawCube()
{
	//enable and specify pointers to vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glNormalPointer(GL_FLOAT, 0, normals);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_NORMAL_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}


///////////////////////////////////////////////////////////////////////////////
// draw a sphere
///////////////////////////////////////////////////////////////////////////////
void draw()
{
	drawCube();
}

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

	initSharedMem();

	//register exit callback
	atexit(exitCB);

	//init GLUT and GL
	initGLUT(argc, argv);
	initGL();

	timer.start();

	// the last GLUT call (LOOP)
	// window will be shown and display callback is triggered by events
	// NOTE: this call never return main().
	glutMainLoop(); /* Start GLUT event-processing loop */

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//initialize GLUT for windowing
//////////////////////////////////////////////////////////////////////////
int initGLUT(int argc, char** argv)
{
	// GLUT stuff for windowing
	// initialization openGL window.
	// It must be called before any other GLUT routine.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA);   // display mode //RGB 双缓冲 alpha
	glutInitWindowSize(screenWidth, screenHeight);              // window size

	int maxWidth = glutGet(GLUT_SCREEN_WIDTH);
	int maxHeight = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitWindowPosition(maxWidth / 2 - screenWidth / 2, maxHeight / 2 - screenHeight / 2);

	// finally, create a window with openGL context
	// Window will not displayed until glutMainLoop() is called
	// It returns a unique ID.

	int handle = glutCreateWindow(argv[0]);  // param is the title of window

	//Register GLUT callback functions
	glutDisplayFunc(displayCB);
	glutTimerFunc(33, timerCB, 33);             // redraw only every given millisec
	glutReshapeFunc(reshapeCB);
	glutKeyboardFunc(keyboardCB);
	glutMouseFunc(mouseCB);
	glutMotionFunc(mouseMotionCB);
	glutPassiveMotionFunc(mousePassiveMotionCB);

	return handle;
}

///////////////////////////////////////////////////////////////////////////////
// initialize OpenGL 初始化OpenGL
// disable unused features 禁用未使用功能
///////////////////////////////////////////////////////////////////////////////
void initGL()
{
	glShadeModel(GL_SMOOTH);				//Shading mathod: GL_SMOOTH or GL_FLAT
	glPixelStorei(GL_UNPACK_ALIGNMENT,4);	//4-byte pixel alignment	 4字节

	// enable /disable features
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE); //面剔除
	glEnable(GL_BLEND); //混合

	// track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(0, 0, 0, 0);
	glClearStencil(0);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);

	initLights();
}

///////////////////////////////////////////////////////////////////////////////
// write 2d text using GLUT
// The projection matrix must be set to orthogonal before call this function.
///////////////////////////////////////////////////////////////////////////////
void drawString(const char* str, int x, int y, float color[4], void* font)
{
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
	glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
	glDisable(GL_TEXTURE_2D);

	glColor4fv(color);          // set text color
	glRasterPos2i(x, y);        // place text position

	// loop all characters in the string
	while (*str)
	{
		glutBitmapCharacter(font, *str);
		++str;
	}

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPopAttrib();
}


///////////////////////////////////////////////////////////////////////////////
// draw a string in 3D space
///////////////////////////////////////////////////////////////////////////////
void drawString3D(const char* str, float pos[3], float color[4], void* font)
{
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
	glDisable(GL_LIGHTING);     // need to disable lighting for proper text color

	glColor4fv(color);          // set text color
	glRasterPos3fv(pos);        // place text position

	// loop all characters in the string
	while (*str)
	{
		glutBitmapCharacter(font, *str);
		++str;
	}

	glEnable(GL_LIGHTING);
	glPopAttrib();
}


//////////////////////////////////////////////////////////////////////////
// initialize global variables
//////////////////////////////////////////////////////////////////////////
bool initSharedMem()
{
	runTime = frameTime = 0.0f;
	animTime = ANIM_DURATION;

	screenWidth = SCREEN_WIDTH;
	screenHeight = SCREEN_HEIGHT;
	mouseLeftDown = mouseRightDown = false;
	drawMode = 0;

	//init quaternions
	quat.Set(1, 0, 0, 0);
	fromQ.Set(1, 0, 0, 0);
	toQ.Set(1, 0, 0, 0);

	return true;
}

//////////////////////////////////////////////////////////////////////////
// initialize lights
//////////////////////////////////////////////////////////////////////////
void initLights()
{
	// set up light colors (ambient, diffuse, specular)
	GLfloat lightKa[] = { 0.0f, 0.0f, 0.0f, 1.0f };  // ambient light
	GLfloat lightKd[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // diffuse light
	GLfloat lightKs[] = { 1, 1, 1, 1 };           // specular light
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

	// position the light
	float lightPos[4] = { 0, 4, 4, 1 }; // positional light
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration
}


///////////////////////////////////////////////////////////////////////////////
// display info messages
///////////////////////////////////////////////////////////////////////////////
void showInfo()
{
	// backup current model-view matrix
	glPushMatrix();                     // save current modelview matrix
	glLoadIdentity();                   // reset modelview matrix

	// set to 2D orthogonal projection
	glMatrixMode(GL_PROJECTION);        // switch to projection matrix
	glPushMatrix();                     // save current projection matrix
	glLoadIdentity();                   // reset projection matrix
	gluOrtho2D(0, screenWidth, 0, screenHeight);  // set to orthogonal projection

	const int FONT_HEIGHT = 14;
	float color[4] = { 1, 1, 1, 1 };

	// for print infos
	std::stringstream ss;
	ss << " Raw: (" << mouseX << ", " << mouseY << ")";
	drawString(ss.str().c_str(), 2, screenHeight - (FONT_HEIGHT * 1), color, font);
	ss.str("");

	ss << std::fixed << std::setprecision(3);
	ss << "Quat: " << quat;
	drawString(ss.str().c_str(), 2, screenHeight - (FONT_HEIGHT * 2), color, font);
	ss.str("");

	// unset floating format
	ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);

	// restore projection matrix
	glPopMatrix();                   // restore to previous projection matrix

	// restore modelview matrix
	glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
	glPopMatrix();                   // restore to previous modelview matrix
}

//////////////////////////////////////////////////////////////////////////
//CALLBACKS
//////////////////////////////////////////////////////////////////////////
void displayCB()
{
	//float elapsedTime = (float)timer.getElapsedTimeInMilliSec();
	//frameTime = elapsedTime - runTime;
	//runTime += frameTime;
	//updateCamera(frameTime);

	// clear framebuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glPushMatrix();

	//transform camera
	glTranslatef(0, 0, -cameraDistance);
	Matrix4 mat = quat.getMatrix();
	glMultMatrixf(mat.get());

	//draw 3D
	draw();

	showInfo();

	glPopMatrix();
	glutSwapBuffers();
}


void reshapeCB(int width, int height)
{
	screenWidth = width;
	screenHeight = height;

	// set viewport to be the entire window
	glViewport(0, 0, width, height);

	// set perspective viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)(width) / height, 1.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

	// switch to modelview matrix in order to set scene
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void timerCB(int millisec)
{
	glutTimerFunc(millisec, timerCB, millisec);
	glutPostRedisplay();
}

void keyboardCB(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // ESCAPE
		exit(0);
		break;

	case 'd': // switch rendering modes (fill -> wire -> point)
	case 'D':
		drawMode = ++drawMode % 3;
		if (drawMode == 0)        // fill mode
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
		}
		else if (drawMode == 1)  // wireframe mode
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);
		}
		else                    // point mode
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);
		}
		break;

	case 'r':
	case 'R':
	{
		quat.Set(1, 0, 0, 0);
	}
	break;
	default:
		;
	}

	glutPostRedisplay();
}


void mouseCB(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseLeftDown = true;

			// remember mouse coords and quaternion before move
			fromX = x;
			fromY = y;
			fromQ = quat;
		}
		else if (state == GLUT_UP)
			mouseLeftDown = false;
	}

	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseRightDown = true;
		}
		else if (state == GLUT_UP)
			mouseRightDown = false;
	}
}


void mouseMotionCB(int x, int y)
{
	if (mouseLeftDown)
	{
		float dx = (x - fromX);
		float dy = (y - fromY);
		Quaternion qx = Quaternion(Vector3(1, 0, 0), dy * 0.002f);   // rotate along X
		Quaternion qy = Quaternion(Vector3(0, 1, 0), dx * 0.002f);   // rotate along Y
		quat = qx * qy * fromQ;

		mouseX = x;
		mouseY = y;
	}
	if (mouseRightDown)
	{
		cameraDistance -= (y - mouseY) * 0.2f;
		mouseY = y;
	}
}


void mousePassiveMotionCB(int x, int y)
{
	mouseX = x;
	mouseY = y;
}




void exitCB()
{
	clearSharedMem();
}

//////////////////////////////////////////////////////////////////////////
// clean up shared memory
//////////////////////////////////////////////////////////////////////////
void clearSharedMem()
{

}
