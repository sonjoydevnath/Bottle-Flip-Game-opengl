#include<stdio.h>
#include <iostream>
#include <stdlib.h>
#include <glut.h>
#include<math.h>
#include "imageloader.h"

using namespace std;


GLuint _textureId;

float _angle;		//Angle, on which object will be rotated;
float _angInc;		//Incremented Angle With respect to time;
float X = -1.5;		//Initial value of X axis of the subject; 
float Y = -1.4;		//Initial value of X axis of the subject; 
float v;			//Initial velocity ;
float theta;        //Angle,on which object will be thrown;
float incrT;
float time;
float r = 0.0005;  //radius of circular path
//int flag; 


void bottle()
{
	glPushMatrix();

	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(X, Y, -6.0);
	glRotatef(_angle, 0.0, 0.0, 1.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	GLUquadricObj *obj3 = gluNewQuadric();             //main body
	gluCylinder(obj3, 0.09, 0.09, 0.4, 100, 360);
	glutSolidSphere(0.09, 100, 360);                   //round
	glTranslatef(0.0, 0.0, -0.27);                     //bottol upper cylinder
	GLUquadricObj *obj4 = gluNewQuadric();
	gluCylinder(obj4, 0.04, 0.04, 0.4, 100, 360);
	glColor3f(0.0, 0.0, 0.82);
	GLUquadricObj *obj5 = gluNewQuadric();             //cap
	gluCylinder(obj5, 0.041, 0.03, 0.4, 100, 360);
	glPopMatrix();

}
/*void plane()
{
glPushMatrix();

glColor3f(0.4, 0.1, 0.7);

glTranslatef(0.0, -1.9, -6.3);
//glRotatef(_angle, 0.0, 0.0, 1.0);

glRotatef(90, 1.0, 0.0, 0.0);


glBegin(GL_POLYGON);

glVertex3f(0.0, 0.0, 0.0);
glVertex3f(2.0, 0.0, 0.0);
glVertex3f(2.0, 1.0, 0.0);
glVertex3f(0.0, 1.0, 0.0);


glPopMatrix();

}*/




void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glTranslatef(0.0, 0.0, -12.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-5, -5, 0.0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-5, 5, 0.0);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(5, 5, 0.0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(5, -5, 0.0);

	glEnd();

	glPopMatrix();

	glPushMatrix();


	glColor3f(1.0, 1.0, 1.0);//bottle

	bottle();
	//plane();
	glEnd();

	glPushMatrix();

	glutSwapBuffers();
}

void update(int value)
{
	_angle += _angInc;
	if (_angle > 360)
	{
		_angle -= 360;
	}

	time = time + 0.01;

	float Wi = (v / r) * 2 * 3.1416;                                 //Angular velocity count and convertion the value in radian;

	float alpha = (0 - Wi) / (time);

	/*if (flag == 0) {
	_angInc = (((Wi*time) + (.5*alpha*time*time))) - _angle;
	//_angle = time*Wi;
	}

	else if(flag == 2)
	{
	return;
	}*/

	if (Y >= -1.4) {
		_angInc = (((Wi*time) + (.5*alpha*time*time))) - _angle;       //angle will incremented until it touch the plane to be landed;
	}
	else {
		_angInc = 0;
	}


	glutPostRedisplay();
	glutTimerFunc(1, update, 0);




}

void calculate(float time)
{

	float p = (theta*3.14159) / 180.0;           //given angle of throwing converted into radian;
	float Vix = v*cosf(p);                      //vertical component of motion;
	float Viy = v*sinf(p);						//horizontal component of motion
	float g = -.098;							//gravitational accelaration;
	cout << Vix << endl;
	cout << Viy << endl;
	float Yt = (Viy*time) + (0.5*g*time*time);   //Y axis's position on specific time;
	float Xt = (Vix*time);                       //X axis's position on specific time;
	cout << Yt << endl;
	cout << Xt << endl;
	X += Xt;                                  //xIncr;
	Y += Yt;                                  //yIncr;
	cout << "Value  of  X :" << X << endl;

	cout << "Value  of  Y :" << Y << endl;
}


void incraseAxis(int value)
{

	incrT += .01;
	calculate(incrT);
	if (Y <= -1.5)// && X >= 0.5 && X <= 2.5)
	{
		_angInc = 0.0;
		//printf("%f", _angle);
		if (_angle <= 10.0)
		{
			//success();
			printf("*****SuccessFully Landed");

			_angle = 0.0;

		}
		else if (_angle >= 350.0)
		{
			//success();
			printf("*****SuccessFully 1 Landed");
			//_angInc = -0.4;
			_angle = 0.0;
			//Y = -1.8;

		}
		else if (_angle>180 && _angle<330)
		{
			_angle = 270.0;
			Y = -1.8;
			//_angInc = -0.4;
			printf("*******failed to land");
			//break;


		}
		else if (_angle>22 && _angle <= 179)
		{
			_angle = 90.0;
			Y = -1.8;
			//_angInc = -0.4;
			printf("*******failed to land");
			//break;

		}

		return;
	}
	else
	{
		//if (Y <= -2.3)
		//{

		//	cout << "" << endl;
		//return;
		//}
	}

	glutTimerFunc(10, incraseAxis, 0);

}



GLuint loadTexture(Image* image) {
GLuint textureId;
glGenTextures(1, &textureId); //Make room for our texture
glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
//Map the image to the texture
glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
0,                            //0 for now
GL_RGB,                       //Format OpenGL uses for image
image->width, image->height,  //Width and height
0,                            //The border of the image
GL_RGB, //GL_RGB, because pixels are stored in RGB format
GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
//as unsigned numbers
image->pixels);               //The actual pixel data
return textureId; //Returns the id of the texture
}

void initialize() {

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, 1.00, 1.0, 100.0);
	Image* image = loadBMP("C:\\Users\\Sonjoy DEVNATH\\Documents\\Visual Studio 2013\\Projects\\earthSunAssignment\\earthSunAssignment\\bg.bmp");

	_textureId = loadTexture(image);

	delete image;
}

void lightSetting()
{

	GLfloat ambientIntensity[4] = { 0.6, 0.6, 0.6, 1.0 };

	GLfloat position[4] = { 0.0, 1.0, 0.0, 0.0 };

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientIntensity);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	//input 

	//input 

	cout << "Input your  velocity Between 0 to 100" << endl;
	while (cin >> v)
	{
		if (v <= 100.0 && v >= 0.0)
		{
			v = v / 1000;
			break;
		}
		else
		{
			cout << "Error..Input again... velocity should be between 0 to 100" << endl;
		}
	}
	cout << "Input your  Angle between 0 to 90 degree" << endl;
	while (cin >> theta)
	{
		if (theta <= 90.0 && theta >= 0.0)
		{
			break;
		}
		else
		{
			cout << "Error..Input again...Angle should be between 0 to 90 degree" << endl;
		}


	}


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(650, 600);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("Bottle Flipping");

	initialize();
	lightSetting();
	glutDisplayFunc(drawScene);
	glutTimerFunc(1, update, 0);
	glutTimerFunc(10, incraseAxis, 0);
	glutMainLoop();

	return 0;
}









