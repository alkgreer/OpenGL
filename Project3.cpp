/*==================================================================================================
PROGRAMMER:				Alisha Greer & Dan West
COURSE:					CSC 525/625
LLAST MODIFIED BY:		Dan West
LAST MODIFIED DATE:		12/11/2016
DESCRIPTION:			Proj3 assignment is showing how to draw
a 3D polygon with OpenGL
Partner 1 (Alisha): //Trace folder: Alisha923
Contribution: 50% 
Partner 2 (Dan): //Trace folder: West777
Contribution: 50% 	-Logic for rotating object 
					-Created menus to rotate and change colors of object
					-Adjusted translation of ornaments
					-Logic for changing color of ornaments
					-Created Info Window and logic for displaying text
FILES:					lab5.cpp, (labProject.sln, ...)
IDE/COMPILER:			MicroSoft Visual Studio 2013
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on labProj.sln	to OPEN the project
2.		Press Ctrl+F7					to COMPILE
3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
4.		Press Ctrl+F5					to EXECUTE
==================================================================================================*/
#include <iostream>
#include <fstream>
#include <GL/glut.h>				// include GLUT library
#include <math.h>
#include <string>
#include <vector>
using namespace std;

//GLOBAL VARIABLES*******************************************************************
GLfloat ambient[] = { 1, 0, 0 };
GLfloat red[] = { 0.8,0,0 };
GLfloat green[] = { 0,0.75,0 };
GLfloat blue[] = { 0,0,0.8 };
GLfloat pink[] = { 1,0,0.8 };
GLfloat yellow[] = { 1,1,0 };
vector<vector<int>> rotation_stack;
const int text_font = (int)GLUT_BITMAP_9_BY_15;
int colorOption = 0; //ornamets are red by default
int infoWindowId;
//***********************************************************************************
void drawTree()
{
	/* future matrix manipulations should affect the modelview matrix */
	glMatrixMode(GL_MODELVIEW);

	/* draw scene */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, green);
	// Tree
	glPushMatrix();                   // Bottom
	glTranslatef(-2, -3.5, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(2.7, 1, 7, 8);
	glPopMatrix();

	glPushMatrix();                   // 1Middle
	glTranslatef(-2, -1.7, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(2.2, 1, 10, 8);
	glPopMatrix();
	//glPopMatrix();

	glPushMatrix();                   // 2Middle
	glTranslatef(-2, -.2, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(1.8, 1.5, 13, 8);
	glPopMatrix();
	//glPopMatrix();

	glPushMatrix();                   // Top
	glTranslatef(-2, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(1.4, 2, 10, 8);
	glPopMatrix();

	glFlush();
}
void drawOrnaments(){
	/* future matrix manipulations should affect the modelview matrix */
	glMatrixMode(GL_MODELVIEW);

	//change color
	if (colorOption == 0) { glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red); }
	else if (colorOption == 1) { glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blue); }
	else if (colorOption == 2) { glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, yellow); }
	else { glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pink); }

	//Bottom
	glPushMatrix();
	glTranslatef(-0.5, -3.2, 1.5);
	glRotatef(-90, 1, 0, 0);
	glutSolidSphere(.17, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, -3.2, 1.5);
	glRotatef(-90, 1, 0, 0);
	glutSolidSphere(.2, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, -3.2, -1.5);
	glRotatef(-90, 1, 0, 0);
	glutSolidSphere(.2, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, -3.2, -1.5);
	glRotatef(-90, 1, 0, 0);
	glutSolidSphere(.2, 20, 10);
	glPopMatrix();

	//Mid1
	glPushMatrix();
	glTranslatef(-0.75, -1.2, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidSphere(.2, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.25, -1.2, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidSphere(.17, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2, -1.2, 1.25);
	glRotatef(-90, 1, 0, 0);
	glutSolidSphere(.2, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2, -1.2, -1.25);
	glRotatef(-90, 1, 0, 0);
	glutSolidSphere(.2, 20, 10);
	glPopMatrix();

	//Mid2
	glPushMatrix();
	glTranslatef(-1.2, 0.45, 0.8);
	glRotatef(-90, 1, 0, 0);
	glutSolidSphere(.2, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.9, 0.4, 0.9);
	glRotatef(-90, 1, 0, 0);
	glutSolidSphere(.2, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.1, 0.4, -0.9);
	glRotatef(-90, 1, 0, 0);
	glutSolidSphere(.17, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.9, 0.4, -0.9);
	glRotatef(-90, 1, 0, 0);
	glutSolidSphere(.17, 20, 10);
	glPopMatrix();

	//Top
	glPushMatrix();
	glTranslatef(-1.25, 1.8, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidSphere(.15, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2, 1.8, .75);
	glRotatef(-90, 1, 0, 0);
	glutSolidSphere(.16, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.75, 1.8, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidSphere(.15, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2, 1.8, -.75);
	glRotatef(-90, 1, 0, 0);
	glutSolidSphere(.16, 20, 10);
	glPopMatrix();

	//flush drawing
	glFlush();
}
//RESET POSITION*********************************************************************
void resetPosition() {
	for (int move = rotation_stack.size() - 1; move >= 0; move--) {
		glRotatef(-rotation_stack[move][0],
			rotation_stack[move][1],
			rotation_stack[move][2],
			rotation_stack[move][3]);
	}
	rotation_stack.clear();
}
void undo() {
	if (rotation_stack.size() > 0) {
		glRotatef(-rotation_stack[rotation_stack.size() - 1][0],
			rotation_stack[rotation_stack.size() - 1][1],
			rotation_stack[rotation_stack.size() - 1][2],
			rotation_stack[rotation_stack.size() - 1][3]);
		rotation_stack.pop_back();
	}
}
//***********************************************************************************
void myInit()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.90, .90, .99, 0);					// specify a background clor: white
	glOrtho(-250, 250, -250, 250, -250, 250);  // specify a viewing volume
	gluLookAt(250, 250, 250, 0, 0, 0, 0, 1, 0);
	glEnable(GL_DEPTH_TEST);
}
void infoInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 0);			// specify a background clor: white 
	gluOrtho2D(0, 300, 400, 0);  // specify a viewing area
}
//***********************************************************************************
void drawInfoMessage() {
	int y = 15;
	int x = 10;
	string message = "We sell Christmas Trees!";
	message += "\nThat's right! For the low-low   price of $20 dollars!";
	message += "\nYou too can be the proud owner  of a digital";
	message += " Christmas Tree.";
	message += "\nIt's the time of year \nfor Holiday  Cheer!";
	message += "\nWhat are you waiting for?";
	message += "\n\n";
	message += "You can see what your tree would look like in the";
	message += " window on the  left. You can right-click \nanywhere";
	message += " in that window to \nrotate and change the color of ";
	message += " of the decorations.";
	message += "\nIf you're tired of seeing this \nwindow, just right-";
	message += "click \nanywhere in this window and \nclick Close.";

	glColor3f(0, 0.5, 0);
	for (int i = 0; i < message.length(); i++) {
		if (message[i] == '\n'|(x>=290 & message[i]==' ')) {
			y += 20;
			x = 10;
			continue;
		}
		if (x >= 290 ) {
			y += 20;
			x = 10;
		}
		glRasterPos2i(x, y);
		glutBitmapCharacter((void*)text_font, message[i]);
		x += 9;
	}
}
void infoDisplayCallback() {
	glClear(GL_COLOR_BUFFER_BIT);
	glutShowWindow();
	drawInfoMessage();
	glFlush();
}
void infoMenuCallback(int entryId) {
	switch (entryId) {
	case 99: glutHideWindow(); glutSetWindow(infoWindowId); break;
	}
	glFlush();
}
void createInfoMenu() {
	int mstrMenu = glutCreateMenu(infoMenuCallback);
	glutAddMenuEntry("Close Window", 99);
	//menu is triggered by right-clicking
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void createInfoWindow() {
	glutInitWindowSize(300, 400);
	glutInitWindowPosition(520, 0);
	infoWindowId = glutCreateWindow("Info:");
	//glutSetWindow(helpWnd);//set top window to mainWnd
	infoInit();
	glutDisplayFunc(infoDisplayCallback);
	createInfoMenu();
}
//***********************************************************************************
void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawTree();
	drawOrnaments();
	glFlush(); // flush out the buffer contents
}
void myMenuCallback(int entryId) {
	//glClear(GL_COLOR_BUFFER_BIT);	// draw the background
	switch (entryId) {
	case 00: resetPosition(); break;
	case 01: undo(); break;
	case 10: glRotatef(45, 1, 0, 0); rotation_stack.push_back({ 45, 1, 0, 0 }); break;
	case 11: glRotatef(-45, 1, 0, 0); rotation_stack.push_back({ -45, 1, 0, 0 }); break;
	case 20: glRotatef(45, 0, 1, 0); rotation_stack.push_back({ 45, 0, 1, 0 }); break;
	case 21: glRotatef(-45, 0, 1, 0); rotation_stack.push_back({ -45, 0, 1, 0 }); break;
	case 30: glRotatef(45, 0, 0, 1); rotation_stack.push_back({ 45, 0, 0, 1 }); break;
	case 31: glRotatef(-45, 0, 0, 1); rotation_stack.push_back({ -45, 0, 0, 1 }); break;
	case 70: colorOption = 0; break;
	case 71: colorOption = 1; break;
	case 72: colorOption = 2; break;
	case 73: colorOption = 3; break;
	case 90: createInfoWindow; break;
	case 99: exit(0);
	}
	myDisplayCallback();
}

//MENU*******************************************************************************
void createMenu() {
	//Transform X-Axis submenu
	int xAxisId = glutCreateMenu(myMenuCallback);
	glutAddMenuEntry("+45 Degrees", 10);
	glutAddMenuEntry("-45 Degrees", 11);
	//Transform Y-Axis submenu
	int yAxisId = glutCreateMenu(myMenuCallback);
	glutAddMenuEntry("+45 Degrees", 20);
	glutAddMenuEntry("-45 Degrees", 21);
	//Transform Z-Axis submenu
	int zAxisId = glutCreateMenu(myMenuCallback);
	glutAddMenuEntry("+45 Degrees", 30);
	glutAddMenuEntry("-45 Degrees", 31);
	//Transform - submenu
	int transformId = glutCreateMenu(myMenuCallback);
	glutAddSubMenu("Rotate X-Axis", xAxisId);
	glutAddSubMenu("Rotate Y-Axis", yAxisId);
	glutAddSubMenu("Rotate Z-Axis", zAxisId);
	//change ornament color
	int ornamentId = glutCreateMenu(myMenuCallback);
	glutAddMenuEntry("Red", 70);
	glutAddMenuEntry("Blue", 71);
	glutAddMenuEntry("Yellow", 72);
	glutAddMenuEntry("Pink", 73);
	//master menu
	int mstrMenu = glutCreateMenu(myMenuCallback);
	glutAddSubMenu("Change Ornament Color", ornamentId);
	glutAddSubMenu("Transform", transformId);
	glutAddMenuEntry("Undo", 01);
	glutAddMenuEntry("Reset Position", 00);
	glutAddMenuEntry("Show Info", 90);
	glutAddMenuEntry("Close App", 99);
	//menu is triggered by right-clicking
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void main()
{
	//window 1
	createInfoWindow();

	//Window 2
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	//create and set up a window
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Merry Christmas!!");

	myInit();
	glutDisplayFunc(myDisplayCallback);

	//set up depth-buffering 
	glEnable(GL_DEPTH_TEST);

	//lighting 
	GLfloat lightcolor[] = { 0.0, 1.0, 0.0 };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, lightcolor);

	//projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, 1, 4, 20);

	//viewing transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 5, 5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//menu will allow user to do transformation on the object
	createMenu();

	//loop
	glutMainLoop();

}
