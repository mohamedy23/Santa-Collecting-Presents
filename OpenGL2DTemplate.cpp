#include <iostream>
#include <math.h>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include<time.h>

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)

double xPlayer = 0.45;
double zPlayer = 0.65;
double xRotate = 0.0;

double xdist = 0.0;
double zdist = 0.0;

bool FrontView = true;
bool SideView = false;
bool TopView = false;

double xPresent1 = 0.65;
double yPresent1 = 0.08;
double zPresent1 = 0.7;

bool fCollision = false;
bool sCollision = false;
bool tCollision = false;

double rColor;
double gColor;
double bColor;

double yPresent1Animation = 0;
bool present1Animation = false;
double yPresent2Animation = 0;
bool present2Animation = false;
double yPresent3Animation = 0;
bool present3Animation = false;

bool gateAnimation = false;
double zGateAnimation = 0.0;

bool tree1Animation = false;
double yTree1Animation = 0.0;
bool tree2Aniamtion = false;
double yTree2Animation = 0.0;

bool fenceAnimation = false;
double xRightFenceAnimation = 0.05;
double xLeftFenceAnimation = 0.0;
double zBackFenceAnimation = 0.0;

bool snowManAnimation = false;
double ySnowManAniamtion = 0.0;

bool timeUp = false;
double yPlayer = 0.0;
bool playerWin = false;
bool GameOver = false;


double counter = 0.0;

class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};
//class Player {
//public:
//	void drawPlayer() {
//		//the body cone
//		glPushMatrix();
//		glTranslated(0.45, 0.1, 0.65);
//		glRotated(-90, 1, 0, 0);
//		glColor3f(1, 0, 0);
//		glutSolidCone(0.1, 0.25, 10, 8);
//		glPopMatrix();
//		//the head
//		glPushMatrix();
//		glTranslated(0.45, 0.33, 0.65);
//		glColor3f(1, 1, 1);
//		glutSolidSphere(0.04, 30, 50);
//		glPopMatrix();
//		//the torus below the head
//		glPushMatrix();
//		glTranslated(0.45, 0.3, 0.65);
//		glRotated(-90, 1, 0, 0);
//		glColor3d(1, 1, 1);
//		glutSolidTorus(0.01, 0.04, 50, 50);
//		glPopMatrix();
//		//the torus above the head
//		glPushMatrix();
//		glTranslated(0.45, 0.36, 0.65);
//		glRotated(-90, 1, 0, 0);
//		glColor3d(1, 1, 1);
//		glutSolidTorus(0.008, 0.03, 50, 50);
//		glPopMatrix();
//		//the torus around the middle of the cone body
//		glPushMatrix();
//		glTranslated(0.45, 0.15, 0.65);
//		glRotated(-90, 1, 0, 0);
//		glColor3d(0.9, 1, 0.4);
//		glutSolidTorus(0.009, 0.07, 50, 50);
//		glPopMatrix();
//		//the torus around the bootom of the cone body
//		glPushMatrix();
//		glTranslated(0.45, 0.1, 0.65);
//		glRotated(-90, 1, 0, 0);
//		glColor3d(0.9, 1, 0.4);
//		glutSolidTorus(0.009, 0.09, 50, 50);
//		glPopMatrix();
//		//the cone above the head
//		glPushMatrix();
//		glTranslated(0.45, 0.33, 0.65);
//		glRotated(-90, 1, 0, 0);
//		glColor3f(1, 0, 0);
//		glutSolidCone(0.04, 0.1, 10, 8);
//		glPopMatrix();
//		//the sphere above the upper cone
//		glPushMatrix();
//		glTranslated(0.45, 0.435, 0.65);
//		glScaled(1, 1, 0.5);
//		glColor3f(1, 0.9, 0.3);
//		glutSolidSphere(0.01, 20, 20);
//		glPopMatrix();
//		//the eyes
//		glPushMatrix();
//		glTranslated(0.465, 0.34, 0.69);
//		glScaled(1, 1, 0.5);
//		glColor3f(0, 0, 0);
//		glutSolidSphere(0.005, 20, 20);
//		glPopMatrix();
//		glPushMatrix();
//		glTranslated(0.445, 0.34, 0.69);
//		glScaled(1, 1, 0.5);
//		glColor3f(0, 0, 0);
//		glutSolidSphere(0.005, 20, 20);
//		glPopMatrix();
//		//the right arm
//		glPushMatrix();
//		glTranslated(0.52, 0.23, 0.65);
//		glRotated(-90, 0, 1, 0);
//		glRotated(-45, 1, 0, 0);
//		glScaled(0.1, 0.1, 0.5);
//		glColor3d(1, 0, 0);
//		glutSolidSphere(0.12, 15, 15);
//		glPopMatrix();
//		//the left arm
//		glPushMatrix();
//		glTranslated(0.38, 0.23, 0.65);
//		glRotated(90, 0, 1, 0);
//		glRotated(-45, 1, 0, 0);
//		glScaled(0.1, 0.1, 0.5);
//		glColor3d(1, 0, 0);
//		glutSolidSphere(0.12, 15, 15);
//		glPopMatrix();
//		//the right hand
//		glPushMatrix();
//		glTranslated(0.57, 0.185, 0.65);
//		glScaled(1, 1, 0.5);
//		glColor3f(0, 0, 0);
//		glutSolidSphere(0.01, 20, 20);
//		glPopMatrix();
//		//the left hand
//		glPushMatrix();
//		glTranslated(0.33, 0.183, 0.65);
//		glScaled(1, 1, 0.5);
//		glColor3f(0, 0, 0);
//		glutSolidSphere(0.01, 20, 20);
//		glPopMatrix();
//		//the right leg
//		glPushMatrix();
//		glTranslated(0.5, 0.09, 0.6);
//		glScaled(0.02, 0.1, 0.01);
//		glColor3f(1, 0, 0);
//		glutSolidCube(1.0);
//		glPopMatrix();
//		//the left leg
//		glPushMatrix();
//		glTranslated(0.4, 0.09, 0.6);
//		glScaled(0.02, 0.1, 0.01);
//		glColor3f(1, 0, 0);
//		glutSolidCube(1.0);
//		glPopMatrix();
//		//the right foot
//		glPushMatrix();
//		glTranslated(0.5, 0.04, 0.6);
//		glScaled(0.035, 0.02, 0.045);
//		glColor3f(0, 0, 0);
//		glutSolidCube(1.0);
//		glPopMatrix();
//		//the left foot
//		glPushMatrix();
//		glTranslated(0.4, 0.04, 0.6);
//		glScaled(0.035, 0.02, 0.045);
//		glColor3f(0, 0, 0);
//		glutSolidCube(1.0);
//		glPopMatrix();
//	}
//	//void SetPosition(float x, float y, float z);
//};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 0.5f, float eyeY = 0.5, float eyeZ = 2.0f, float centerX = 0.5f, float centerY = 0.5f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;

class sideCamera {
public:
	Vector3f eye, center, up;

	sideCamera(float eyeX = 2.0f, float eyeY = 0.5, float eyeZ = 0.5f, float centerX = 0.0f, float centerY = 0.5f, float centerZ = 0.5f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

sideCamera sideView;

class topCamera {
public:
	Vector3f eye, center, up;

	topCamera(float eyeX = 0.5f, float eyeY = 2.0, float eyeZ = 0.5f, float centerX = 0.5f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

topCamera topView;



void TimeDelay(int val)
{
	glutTimerFunc(500, TimeDelay, 0);
}

void drawWall(double thickness) {
	glPushMatrix();
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	//glColor3f(1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();
}
void drawTableLeg(double thick, double len) {
	glPushMatrix();
	glTranslated(0.6, len / 2, -0.4);
	glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glPopMatrix();
}
void drawHorizentalFence(double thick, double len) {
	glPushMatrix();
	glTranslated(0.6, len / 2, -0.4);
	glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glPopMatrix();
}
void setFenceColor(double x, double y, double z) {
	glColor3d(rColor, gColor, bColor);
}
void drawJackPart() {
	glPushMatrix();
	glScaled(0.2, 0.2, 1.0);
	glutSolidSphere(1, 15, 15);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0, 1.2);
	glutSolidSphere(0.2, 15, 15);
	glTranslated(0, 0, -2.4);
	glutSolidSphere(0.2, 15, 15);
	glPopMatrix();
}
void drawJack() {
	glPushMatrix();
	drawJackPart();
	glRotated(90.0, 0, 1, 0);
	drawJackPart();
	glRotated(90.0, 1, 0, 0);
	drawJackPart();
	glPopMatrix();
}
void drawRightFence(double topWid, double topThick, double legThick, double legLen) {
	glPushMatrix();
	glTranslated(0.6, legLen / 2, 0.1);
	glScaled(0, topThick, topWid);
	glColor3d(rColor, gColor, bColor);
	glutSolidCube(1.0);
	glPopMatrix();

	//double dist = 0.95 * topWid / 2.0 - legThick / 2.0;
	double dist = 0.1;
	glPushMatrix();
	glTranslated(0, 0, dist);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(0, 0, dist);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(0, 0, dist);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(0, 0, dist);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(0, 0, dist);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(0, 0, dist);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(0, 0, dist);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(0, 0, dist);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(0, 0, dist);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(0, 0, dist);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	//dist += 0.1;
	//glColor3f(1, 0, 0);
	//drawHorizentalFence(0.02, 1);

	/*glTranslated(0.6, 0, 0.02);
	drawTableLeg(legThick, legLen);*/

	/*glPushMatrix();
	glTranslated(dist, 0, dist);
	drawTableLeg(legThick, legLen);

	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);

	glTranslated(-2 * dist, 0, 2 * dist);
	drawTableLeg(legThick, legLen);

	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glPopMatrix();*/
}
void drawBackFence(double topWid, double topThick, double legThick, double legLen) {
	glPushMatrix();
	glTranslated(0.1, legLen / 2, -0.4);
	glScaled(topWid, topThick, 0);
	glColor3d(rColor, gColor, bColor);
	glutSolidCube(1.0);
	glPopMatrix();

	glColor3d(0.7, 0.3, 0);
	drawTableLeg(legThick, legLen);

	//double dist = 0.95 * topWid / 2.0 - legThick / 2.0;
	double dist = -0.1;
	glPushMatrix();
	glTranslated(dist, 0, 0.0);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist -= 0.1;
	glPushMatrix();
	glTranslated(dist, 0, 0.0);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist -= 0.1;
	glPushMatrix();
	glTranslated(dist, 0, 0.0);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist -= 0.1;
	glPushMatrix();
	glTranslated(dist, 0, 0.0);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist -= 0.1;
	glPushMatrix();
	glTranslated(dist, 0, 0.0);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist -= 0.1;
	glPushMatrix();
	glTranslated(dist, 0, 0.0);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist -= 0.1;
	glPushMatrix();
	glTranslated(dist, 0, 0.0);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist -= 0.1;
	glPushMatrix();
	glTranslated(dist, 0, 0.0);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist -= 0.1;
	glPushMatrix();
	glTranslated(dist, 0, 0.0);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist -= 0.1;
	glPushMatrix();
	glTranslated(dist, 0, 0.0);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();

	//glColor3f(1, 0, 0);
	//drawHorizentalFence(0.02, 1);

	/*glTranslated(0.6, 0, 0.02);
	drawTableLeg(legThick, legLen);*/

	/*glPushMatrix();
	glTranslated(dist, 0, dist);
	drawTableLeg(legThick, legLen);

	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);

	glTranslated(-2 * dist, 0, 2 * dist);
	drawTableLeg(legThick, legLen);

	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glPopMatrix();*/
}
void drawLeftFence(double topWid, double topThick, double legThick, double legLen) {
	glPushMatrix();
	//glColor3d(0, 0, 1);
	//glColor4i(0, 0, 1, 0);
	glTranslated(-0.4, legLen / 2, 0.1);
	glScaled(0, topThick, topWid);
	glColor3d(rColor, gColor, bColor);
	glutSolidCube(1.0);
	glPopMatrix();

	//double dist = 0.95 * topWid / 2.0 - legThick / 2.0;
	double dist = 0.1;
	double trans = -1;
	glPushMatrix();
	glTranslated(trans, 0, dist);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(trans, 0, 0.2);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(trans, 0, 0.3);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(trans, 0, 0.4);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(trans, 0, 0.5);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(trans, 0, 0.6);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(trans, 0, 0.7);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(trans, 0, 0.8);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(trans, 0, 0.9);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	dist += 0.1;
	glPushMatrix();
	glTranslated(trans, 0, 1.0);
	glColor3d(rColor, gColor, bColor);
	drawTableLeg(legThick, legLen);
	glPopMatrix();

	//glColor3f(1, 0, 0);
	//drawHorizentalFence(0.02, 1);

	/*glTranslated(0.6, 0, 0.02);
	drawTableLeg(legThick, legLen);*/

	/*glPushMatrix();
	glTranslated(dist, 0, dist);
	drawTableLeg(legThick, legLen);

	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);

	glTranslated(-2 * dist, 0, 2 * dist);
	drawTableLeg(legThick, legLen);

	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glPopMatrix();*/
}
void drawSnowMan() {
	/*glPushMatrix();
	glTranslated(0.8, 0.3, 0.4);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.02, 30, 50);
	glPopMatrix();*/
	//first layer (head)
	glPushMatrix();
	glTranslated(0.8, 0.34, 0.4);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.04, 30, 50);
	glPopMatrix();

	//second layer
	glPushMatrix();
	glTranslated(0.8, 0.25, 0.4);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.06, 20, 20);
	glPopMatrix();
	//thrid layer
	glPushMatrix();
	glTranslated(0.8, 0.15, 0.4);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.08, 20, 20);
	glPopMatrix();
	//the cone
	glPushMatrix();
	glTranslated(0.8, 0.35, 0.4);
	glRotated(-90, 1, 0, 0);
	glColor3f(1, 0, 0);
	glutSolidCone(0.03, 0.1, 10, 8);
	glPopMatrix();
	//the nose
	glPushMatrix();
	glTranslated(0.795, 0.35, 0.44);
	//glRotated(90, 1, 0, 0);
	glColor3f(1, 0.6, 0.1);
	glutSolidCone(0.009, 0.01, 10, 8);
	glPopMatrix();
	//two eyes
	glPushMatrix();
	glTranslated(0.81, 0.36, 0.435);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.005, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.78, 0.36, 0.432);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.005, 20, 20);
	glPopMatrix();

}
void drawRightTree(double x, double yUpperCone, double yMiddleCone, double yLowerCone, double z) {
	glPushMatrix();
	glTranslated(x, yUpperCone+0.86, z);
	glScaled(1, 1, 0.5);
	glColor3f(1, 0.0, 0.0);
	glutSolidSphere(0.01, 20, 20);
	glPopMatrix();
	
	
	glPushMatrix();
	glTranslated(x, yUpperCone, z);
	glRotated(-90, 1, 0, 0);
	glColor3f(0.1, 0.5, 0);
	glutSolidCone(0.2, 0.45, 10, 8);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, yMiddleCone, z);
	glRotated(-90, 1, 0, 0);
	glColor3f(0.1, 0.5, 0);
	glutSolidCone(0.15, 0.45, 10, 8);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, yLowerCone, z);
	glRotated(-90, 1, 0, 0);
	glColor3f(0.1, 0.5, 0);
	glutSolidCone(0.12, 0.45, 10, 8);
	glPopMatrix();
}
void drawLeftTree(double x, double yUpperCone, double yMiddleCone, double yLowerCone, double z) {
	
	glPushMatrix();
	glTranslated(x, yUpperCone + 0.86, z);
	glScaled(1, 1, 0.5);
	glColor3f(1, 0.0, 0.0);
	glutSolidSphere(0.01, 20, 20);
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(x, yUpperCone, z);
	glRotated(-90, 1, 0, 0);
	glColor3f(0.1, 0.5, 0);
	glutSolidCone(0.2, 0.45, 10, 8);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, yMiddleCone, z);
	glRotated(-90, 1, 0, 0);
	glColor3f(0.1, 0.5, 0);
	glutSolidCone(0.15, 0.45, 10, 8);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, yLowerCone, z);
	glRotated(-90, 1, 0, 0);
	glColor3f(0.1, 0.5, 0);
	glutSolidCone(0.12, 0.45, 10, 8);
	glPopMatrix();
}
void drawGate() {
	glPushMatrix();
	glTranslated(0.6, 0.3, 0.1);
	glScaled(0.05, 0.6, 0.01);
	glColor3d(1, 0, 0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.4, 0.3, 0.1);
	glScaled(0.05, 0.6, 0.01);
	glColor3d(1, 0, 0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0.39, 0.1);
	glScaled(0.4, 0.07, 0.01);
	glColor3d(1, 0, 0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0.6, 0.15);
	glScaled(0.6, 0.05, 0.01);
	glColor3d(1, 0, 0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0.65, 0.15);
	glScaled(0.7, 0.06, 0.01);
	glColor3d(0, 0, 0);
	glutSolidCube(1.0);
	glPopMatrix();
}
void drawPresent(double x, double y, double z) {
	//the rectangle
	glPushMatrix();
	glTranslated(x, y, z);
	glScaled(0.09, 0.08, 0.08);
	glColor3f(1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.65, 0.12, 0.7);
	glColor3f(0, 1, 0);
	glutSolidSphere(0.013, 30, 50);
	glPopMatrix();

	//the first ribbon
	glPushMatrix();
	glTranslated(0.65, 0.08, 0.74);
	glScaled(0.01, 0.08, 0.001);
	glColor3f(1, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	//the second ribbon
	glPushMatrix();
	glTranslated(0.65, 0.12, 0.7);
	glScaled(0.01, 0.001, 0.08);
	glColor3f(1, 1, 0);
	glutSolidCube(1.0);
	glPopMatrix();
	//the third ribbon
	glPushMatrix();
	glTranslated(0.65, 0.12, 0.7);
	glScaled(0.09, 0.001, 0.01);
	glColor3f(1, 1, 0);
	glutSolidCube(1.0);
	glPopMatrix();
	//the fourth ribbon
	glPushMatrix();
	glTranslated(0.605, 0.08, 0.7);
	glScaled(0.001, 0.08, 0.01);
	glColor3f(1, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	//the fifth ribbon
	glPushMatrix();
	glTranslated(0.695, 0.08, 0.7);
	glScaled(0.001, 0.08, 0.01);
	glColor3f(1, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	//the sixth ribbon
	glPushMatrix();
	glTranslated(0.65, 0.08, 0.66);
	glScaled(0.01, 0.08, 0.001);
	glColor3f(1, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
}
void drawPlayer(double xPlayer, double zPlayer) {
	//the body cone
	glPushMatrix();
	glTranslated(xPlayer, 0.1, zPlayer);
	glRotated(-90, 1, 0, 0);
	glColor3f(1, 0, 0);
	glutSolidCone(0.1, 0.25, 10, 8);
	glPopMatrix();
	//the head
	glPushMatrix();
	glTranslated(xPlayer, 0.33, zPlayer);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.04, 30, 50);
	glPopMatrix();
	//the torus below the head
	glPushMatrix();
	glTranslated(xPlayer, 0.3, zPlayer);
	glRotated(-90, 1, 0, 0);
	glColor3d(1, 1, 1);
	glutSolidTorus(0.01, 0.04, 50, 50);
	glPopMatrix();
	//the torus above the head
	glPushMatrix();
	glTranslated(xPlayer, 0.36, zPlayer);
	glRotated(-90, 1, 0, 0);
	glColor3d(1, 1, 1);
	glutSolidTorus(0.008, 0.03, 50, 50);
	glPopMatrix();
	//the torus around the middle of the cone body
	glPushMatrix();
	glTranslated(xPlayer, 0.15, zPlayer);
	glRotated(-90, 1, 0, 0);
	glColor3d(0.9, 1, 0.4);
	glutSolidTorus(0.009, 0.07, 50, 50);
	glPopMatrix();
	//the torus around the bootom of the cone body
	glPushMatrix();
	glTranslated(xPlayer, 0.1, zPlayer);
	glRotated(-90, 1, 0, 0);
	glColor3d(0.9, 1, 0.4);
	glutSolidTorus(0.009, 0.09, 50, 50);
	glPopMatrix();
	//the cone above the head
	glPushMatrix();
	glTranslated(xPlayer, 0.33, zPlayer);
	glRotated(-90, 1, 0, 0);
	glColor3f(1, 0, 0);
	glutSolidCone(0.04, 0.1, 10, 8);
	glPopMatrix();
	//the sphere above the upper cone
	glPushMatrix();
	glTranslated(xPlayer, 0.435, zPlayer);
	glScaled(1, 1, 0.5);
	glColor3f(1, 0.9, 0.3);
	glutSolidSphere(0.01, 20, 20);
	glPopMatrix();
	//the eyes
	glPushMatrix();
	glTranslated(xPlayer + 0.015, 0.34, zPlayer + 0.04);
	glScaled(1, 1, 0.5);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.005, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslated(xPlayer - 0.005, 0.34, zPlayer + 0.04);
	glScaled(1, 1, 0.5);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.005, 20, 20);
	glPopMatrix();
	//the right arm
	glPushMatrix();
	glTranslated(xPlayer + 0.07, 0.23, zPlayer);
	glRotated(-90, 0, 1, 0);
	glRotated(-45, 1, 0, 0);
	glScaled(0.1, 0.1, 0.5);
	glColor3d(1, 0, 0);
	glutSolidSphere(0.12, 15, 15);
	glPopMatrix();
	//the left arm
	glPushMatrix();
	glTranslated(xPlayer - 0.07, 0.23, zPlayer);
	glRotated(90, 0, 1, 0);
	glRotated(-45, 1, 0, 0);
	glScaled(0.1, 0.1, 0.5);
	glColor3d(1, 0, 0);
	glutSolidSphere(0.12, 15, 15);
	glPopMatrix();
	//the right hand
	glPushMatrix();
	glTranslated(xPlayer + 0.12, 0.185, zPlayer);
	glScaled(1, 1, 0.5);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.01, 20, 20);
	glPopMatrix();
	//the left hand
	glPushMatrix();
	glTranslated(xPlayer - 0.12, 0.183, zPlayer);
	glScaled(1, 1, 0.5);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.01, 20, 20);
	glPopMatrix();
	//the right leg
	glPushMatrix();
	glTranslated(xPlayer + 0.05, 0.09, zPlayer - 0.05);
	glScaled(0.02, 0.1, 0.01);
	glColor3f(1, 0, 0);
	glutSolidCube(1.0);
	glPopMatrix();
	//the left leg
	glPushMatrix();
	glTranslated(xPlayer - 0.05, 0.09, zPlayer - 0.05);
	glScaled(0.02, 0.1, 0.01);
	glColor3f(1, 0, 0);
	glutSolidCube(1.0);
	glPopMatrix();
	//the right foot
	glPushMatrix();
	glTranslated(xPlayer + 0.05, 0.04, zPlayer - 0.05);
	glScaled(0.035, 0.02, 0.045);
	glColor3f(0, 0, 0);
	glutSolidCube(1.0);
	glPopMatrix();
	//the left foot
	glPushMatrix();
	glTranslated(xPlayer - 0.05, 0.04, zPlayer - 0.05);
	glScaled(0.035, 0.02, 0.045);
	glColor3f(0, 0, 0);
	glutSolidCube(1.0);
	glPopMatrix();
}
void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}
void setupCamera2() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	sideView.look();
}
void setupCamera3() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	topView.look();
}

void Display() {
	setupCamera();
	if (SideView == true)setupCamera2();
	else if (TopView == true)setupCamera3();
	setupLights();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*glPushMatrix();
	glTranslated(0.4, 0.4, 0.6);
	glRotated(45, 0, 0, 1);
	glScaled(0.03, 0.03, 0.03);
	drawJack();
	glPopMatrix();*/

	/*glPushMatrix();
	glTranslated(0.6, 0.38, 0.5);
	glRotated(30, 0, 1, 0);
	glutSolidTeapot(0.08);
	glPopMatrix();*/

	//draw SnowMan
	glPushMatrix();
	if (snowManAnimation == false) {
		glTranslated(0.0, 0.0, 0.3);
		drawSnowMan();
	}
	else {
		glTranslated(0, ySnowManAniamtion, 0);
		glTranslated(0.0, 0.0, 0.3);
		drawSnowMan();
	}
	glPopMatrix();

	//draw the right tree
	glPushMatrix();
	if (tree1Animation == false) {
		glTranslated(0.0, 0.0, 0.2);
		drawRightTree(0.8, 0.0, 0.2, 0.4, 0.0);
	}
	else {
		glTranslated(0, yTree1Animation, 0);
		glTranslated(0.0, 0.0, 0.2);
		drawRightTree(0.8, 0.0, 0.2, 0.4, 0.0);
	}
	glPopMatrix();

	//draw the left tree
	glPushMatrix();
	if (tree2Aniamtion == false) {
		glTranslated(0.0, 0.0, 0.2);
		drawLeftTree(0.2, 0.0, 0.2, 0.4, 0.0);
	}
	else {
		glTranslated(0, yTree2Animation, 0);
		glTranslated(0.0, 0.0, 0.2);
		drawLeftTree(0.2, 0.0, 0.2, 0.4, 0.0);
	}
	glPopMatrix();

	//Right Fence
	glPushMatrix();
	if (fenceAnimation == false) {
		glTranslated(0.4, 0.0, 0.4);
		glColor3f(0, 1, 1);
		drawRightFence(1, 0.02, 0.02, 0.3);
	}
	else {
		glTranslated(xRightFenceAnimation, 0, 0);
		glTranslated(0.4, 0.0, 0.4);
		glColor3f(0, 1, 1);
		drawRightFence(1, 0.02, 0.02, 0.3);
	}
	glPopMatrix();

	//Back Fence
	glPushMatrix();
	if (fenceAnimation == false) {
		glTranslated(0.4, 0.0, 0.4);
		glColor3f(0, 1, 1);
		drawBackFence(1, 0.02, 0.02, 0.3);
	}
	else {
		glTranslated(0, 0, zBackFenceAnimation);
		glTranslated(0.4, 0.0, 0.4);
		glColor3f(0, 1, 1);
		drawBackFence(1, 0.02, 0.02, 0.3);
	}
	glPopMatrix();

	//Left Fence
	glPushMatrix();
	if (fenceAnimation == false) {
		glTranslated(0.4, 0.0, 0.4);
		glColor3f(0, 1, 1);
		drawLeftFence(1, 0.02, 0.02, 0.3);
	}
	else {
		glTranslated(xLeftFenceAnimation, 0, 0);
		glTranslated(0.4, 0.0, 0.4);
		glColor3f(0, 1, 1);
		drawLeftFence(1, 0.02, 0.02, 0.3);
	}

	glPopMatrix();

	//the ground
	glPushMatrix();
	glColor3d(0.7, 0.3, 0);
	drawWall(0.02);
	glPopMatrix();

	//handling drawing presents,presents animation and presents collision
	if (fCollision == false||(GameOver==true)) {
		//draw the first present if it is not touched by the player
		if (present1Animation == false) {
			glPushMatrix();
			drawPresent(0.65, 0.08, 0.7);
			glPopMatrix();
		}
		else if(present1Animation == true&&fCollision==false) {
			glPushMatrix();
			glTranslated(0.0, yPresent1Animation, 0);
			drawPresent(0.65, 0.08, 0.7);
			glPopMatrix();
		}

	}
	if (sCollision == false||GameOver==true) {
		//draw the second present if it is not touched by the player
		if (present2Animation == false) {
			glPushMatrix();
			glTranslated(-0.5, 0, -0.3);
			drawPresent(0.65, 0.08, 0.7);
			glPopMatrix();
		}
		else if (present2Animation == true && sCollision == false) {
			glPushMatrix();
			glTranslated(0, yPresent2Animation, 0);
			glTranslated(-0.5, 0, -0.3);
			drawPresent(0.65, 0.08, 0.7);
			glPopMatrix();
		}

	}
	if (tCollision == false||GameOver==true) {
		//draw the third present if it is not touched by the player
		if (present3Animation == false) {
			glPushMatrix();
			glTranslated(-0.5, 0, 0);
			drawPresent(0.65, 0.08, 0.7);
			glPopMatrix();
		}
		else if (present3Animation == true && tCollision == false) {
			glPushMatrix();
			glTranslated(0, yPresent3Animation, 0);
			glTranslated(-0.5, 0, 0);
			drawPresent(0.65, 0.08, 0.7);
			glPopMatrix();
		}

	}



	//handling drawing the gate and its animation along z-axix
	if (gateAnimation == false) {//draw the gate
		glPushMatrix();
		drawGate();
		glPopMatrix();
	}
	else {
		//draw the gate
		glPushMatrix();
		glTranslated(0, 0, zGateAnimation);
		drawGate();
		glPopMatrix();
	}


	//draw the player and handling all its movements in all direction
	glPushMatrix();
	if (xRotate == 90) {
		glTranslated(xPlayer + xdist, 0, zPlayer + zdist);
		glRotated((xRotate), 0, 1, 0);
		glTranslated(-(xPlayer + xdist), 0, -(zPlayer + zdist));
		glTranslated(-zdist, 0, xdist);
		//fCollision = true;

	}
	//move left after rotating
	if (xRotate == -90) {
		glTranslated(xPlayer + xdist, 0, zPlayer + zdist);
		glRotated((xRotate), 0, 1, 0);
		glTranslated(-(xPlayer + xdist), 0, -(zPlayer + zdist));
		glTranslated(zdist, 0, -xdist);
	}
	//move forward after rotating
	if (xRotate == 360) {
		//fCollision = true;
		glTranslated(xPlayer + xdist, 0, zPlayer + zdist);
		glRotated((360), 0, 1, 0);
		glTranslated(-(xPlayer + xdist), 0, -(zPlayer + zdist));
		glTranslated(xdist, 0, zdist);
	}
	//move backward after rotating
	if (xRotate == 180) {
		glTranslated(xPlayer + xdist, 0, zPlayer + zdist);
		glRotated((180), 0, 1, 0);
		glTranslated(-(xPlayer + xdist), 0, -(zPlayer + zdist));
		glTranslated(-xdist, 0, -zdist);
	}

	//first present collision
	if (xPlayer + xdist >= xPresent1 - (0.09 * 2) && xPlayer + xdist <= xPresent1 - 0.02 &&
		zPlayer + zdist >= zPresent1 - (0.1) && zPlayer + zdist <= zPresent1 + (0.05)
		) {
		fCollision = true;
	}
	//second present collision
	if (xPlayer + xdist >= xPresent1 - 0.65 + 0.39 - 0.17 && xPlayer + xdist <= xPresent1 - 0.65 + 0.39 &&
		zPlayer + zdist >= 0.45 && zPlayer + zdist <= 0.45 + .16
		) {
		sCollision = true;
	}
	//third present collision
	if (xPlayer + xdist >= xPresent1 - 0.65 + 0.39 - 0.17 && xPlayer + xdist <= xPresent1 - 0.65 + 0.39 &&
		zPlayer + zdist >= zPresent1 - (0.1) && zPlayer + zdist <= zPresent1 + (0.05)
		) {
		tCollision = true;
	}
	/*if (xPlayer + xdist >= xPresent1 - 0.18-0.5&& zPlayer + zdist) {
		sCollision = true;
	}*/

	if (timeUp == false)drawPlayer(xPlayer + xdist, zPlayer + zdist);
	else  {
		glTranslated(0, yPlayer, 0);
		drawPlayer(xPlayer + xdist, zPlayer + zdist);
	}
	glPopMatrix();

	/*Player player;
	player.drawPlayer();*/

	//glPushMatrix();
	//glTranslated(0.5, 0.5 * thickness, 0.5);
	//glScaled(1.0, thickness, 1.0);
	////glColor3f(1, 0, 0);
	//glutSolidCube(1);
	//glPopMatrix();



	/*glPushMatrix();
	glTranslated(0, 0, 1.2);
	glutSolidSphere(0.2, 15, 15);
	glTranslated(0, 0, -2.4);
	glutSolidSphere(0.2, 15, 15);
	glPopMatrix();*/


	//Right wall
	//glPushMatrix();
	//glTranslated(1, 0.0, 0.0);
	//glRotated(90, 0, 0, 1);
	////glColor3f(1, 0, 0);
	//drawWall(0.02);
	//glPopMatrix();

	//left wall
	//glPushMatrix();
	////glTranslated(1, 0.0, 0.0);
	//glRotated(90, 0, 0, 1);
	////glColor3f(1, 0, 0);
	//drawWall(0.02);
	//glPopMatrix();

	//Back wall
	//glPushMatrix();
	//glRotated(-90, 1.0, 0.0, 0.0);
	////glColor3f(1, 0, 0);
	//drawWall(0.02);
	//glPopMatrix();

	//glPushMatrix();
	////glTranslated(0.4, 0.0, 0.4);
	//glRotated(90, 1.0, 0.0, 0.0);
	//drawWall(0.02);
	//glPopMatrix();
	/*glPushMatrix();
	glRotated(270, 1.0, 0, 0);
	drawWall(0.02);
	glPopMatrix();*/

	glFlush();
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
	float d = 0.01;

	switch (key) {

	case 'z':
		present1Animation = true;
		break;
	case 'Z':
		present1Animation = false;
		yPresent1Animation = 0;
		break;
	case 'x':
		present2Animation = true;
		break;
	case 'X':
		present2Animation = false;
		yPresent2Animation = 0;
		break;
	case 'c':
		present3Animation = true;
		break;
	case 'C':
		present3Animation = false;
		yPresent3Animation = 0;
		break;
	case 'v':
		gateAnimation = true;
		break;
	case 'V':
		gateAnimation = false;
		zGateAnimation = 0.0;
		break;
	case 'b':
		tree1Animation = true;
		break;
	case 'B':
		tree1Animation = false;
		yTree1Animation = 0.0;
		break;
	case 'n':
		tree2Aniamtion = true;
		break;
	case 'N':
		tree2Aniamtion = false;
		yTree2Animation = 0.0;
		break;
	case 'm':
		fenceAnimation = true;
		break;
	case 'M':
		fenceAnimation = false;
		xRightFenceAnimation = 0;
		xLeftFenceAnimation = 0;
		zBackFenceAnimation = 0;
		break;
	case 'l':
		snowManAnimation = true;
		break;
	case 'L':
		snowManAnimation = false;
		ySnowManAniamtion = 0.0;
		break;
	case 'f':
		FrontView = true;
		SideView = false;
		TopView = false;
		break;
	case 'g':
		SideView = true;
		FrontView = false;
		TopView = false;
		break;
	case 'h':
		TopView = true;
		FrontView = false;
		SideView = false;
		break;
	case 'w':
		if (FrontView == true)camera.moveY(d);
		else if (SideView == true)sideView.moveY(d);
		else if (TopView == true)topView.moveY(d);
		break;
	case 's':
		if (FrontView == true)camera.moveY(-d);
		else if (SideView == true)sideView.moveY(-d);
		else if (TopView == true)topView.moveY(-d);
		break;
	case 'a':
		if (FrontView == true)camera.moveX(d);
		else if (SideView == true)sideView.moveX(d);
		else if (TopView == true)topView.moveX(d);
		break;
	case 'd':
		if (FrontView == true)camera.moveX(-d);
		else if (SideView == true)sideView.moveX(-d);
		else if (TopView == true)topView.moveX(-d);
		break;
	case 'q':
		if (FrontView == true)camera.moveZ(d);
		else if (SideView == true)sideView.moveZ(d);
		else if (TopView == true)topView.moveZ(d);
		break;
	case 'e':
		if (FrontView == true)camera.moveZ(-d);
		else if (SideView == true)sideView.moveZ(-d);
		else if (TopView == true)topView.moveZ(-d);
		break;
	case '6':
		xRotate = 90;
		/*xPlayer += d;
		zPlayer -= d;*/
		if (xPlayer + xdist <= 0.65)xdist += d;
		break;
	case '4':
		xRotate = -90;
		//xPlayer -= d;
		if (xPlayer + xdist >= 0.3)xdist -= d;
		break;
	case '2':
		if (zPlayer + zdist <= 0.8)zdist += d;
		//zPlayer += d;
		xRotate = 360;
		break;
	case '8':
		if (zPlayer + zdist >= 0.35)zdist -= d;
		//zPlayer += d;
		xRotate = 180;
		break;
	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	glutPostRedisplay();
}
void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		if (FrontView == true)camera.rotateX(a);
		else if (SideView == true)sideView.rotateX(a);
		else if (TopView == true)topView.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		if (FrontView == true)camera.rotateX(-a);
		else if (SideView == true)sideView.rotateX(-a);
		else if (TopView == true)topView.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		if (FrontView == true)camera.rotateY(a);
		else if (SideView == true)sideView.rotateY(a);
		else if (TopView == true)topView.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		if (FrontView == true)camera.rotateY(-a);
		else if (SideView == true)sideView.rotateY(-a);
		else if (TopView == true)topView.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}

void Time(int val)
{

	counter++;
	std::cout << counter << " ";
	srand(time(0));
	rColor = rand() % 9;
	gColor = rand() % 9;
	bColor = rand() % 9;
	glutTimerFunc(100, Time, 0);
	//still playing
	if (counter < 100 && !(fCollision == true && sCollision == true && tCollision == true)) {
		if (present1Animation == true) {
			yPresent1Animation += 0.01;
		}
		if (present2Animation == true) {
			yPresent2Animation += 0.01;
		}
		if (present3Animation == true) {
			yPresent3Animation += 0.01;
		}
		if (gateAnimation == true) {
			zGateAnimation -= 0.05;
		}
		if (tree1Animation == true) {
			yTree1Animation += 0.01;
		}
		if (tree2Aniamtion == true) {
			yTree2Animation += 0.01;
		}
		if (fenceAnimation == true) {
			xRightFenceAnimation += 0.01;
			xLeftFenceAnimation -= 0.01;
			zBackFenceAnimation -= 0.01;
		}
		if (snowManAnimation == true) {
			ySnowManAniamtion += 0.01;
		}
	}

	//winning before time ends
	else if ((fCollision == true && sCollision == true && tCollision == true)) {
		//glClearColor(1 - rColor, 1 - gColor,  bColor, 0.0f);
		timeUp = true;
		playerWin = true;
		yPlayer += 0.05;

	}
	//Game Over
	else if (counter > 100 && playerWin == false) {
		glClearColor(0, 0, 0, 0.0f);
		timeUp = true;
		//yPlayer += 0.01;
		GameOver = true;
		present1Animation = true;
		present2Animation = true;
		present3Animation = true;
		yPresent1Animation += 0.05;
		yPresent2Animation += 0.05;
		yPresent3Animation += 0.05;
		/*present1Animation = true;
		present2Animation = true;
		present3Animation = true;*/
	}
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Lab 5");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(0.3f, 0.3f, 0.5f, 0.0f);

	glutTimerFunc(100, Time, 0);
	//glutTimerFunc(500, TimeDelay, 0);
	//glutKeyboardFunc(Keyboard);
	/*srand(time(0));
	rColor = rand() % 9;
	gColor = rand() % 9;
	bColor = rand() % 9;*/


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}
