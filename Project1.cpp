﻿/*==================================================================================================[a]
PROGRAMMERS:                        Alisha Greer, Dan West
COURSE:                                        CSC 525/625
LAST MODIFIED BY:                Dan West
LAST MODIFIED DATE:                10/13/2016
DESCRIPTION:                        Project1: 2d design
FILES:                                        Project1.cpp, project1_input.txt, savedImg.txt[b]
Partner 1 (Alisha):                Created overall design of the
program. (i.e. circles, bitmap,pattern, text and lines)
Partner 2 (Dan):                Setup functions and basic program structure (main(), init(), draw functions).
Constructed pixel map .txt file and read/save functions
IDE/COMPILER:                        MicroSoft Visual Studio 2013
INSTRUCTION FOR COMPILATION AND EXECUTION:[c]
1.                Make sure the savedImg.txt and project1_input.txt are in your c:\temp folder
2.                Double click on projProject.sln        to OPEN the project
3.                Press Ctrl+F7                                        to COMPILE
4.                Press Ctrl+Shift+B                                to BUILD (COMPILE+LINK)
5.                Press Ctrl+F5                                        to EXECUTE
==================================================================================================*/
#include <iostream>
#include <fstream>
#include <GL/glut.h>                                // include GLUT library
#include <math.h>
#include <string>
#include <vector>
using namespace std;
//GLOBAL VARIABLES*******************************************************************
GLubyte pattern[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xFC, 0xFC, 0x00, 0x00, 0x78, 0x78, 0x00,
        0xE3, 0x00, 0x03, 0x1C, 0x00, 0xFC, 0xFC, 0x00,
        0xE7, 0x00, 0x03, 0x9C, 0xE7, 0x00, 0x03, 0x9C,
        0xE7, 0xFF, 0xFF, 0x9C, 0xE7, 0xFF, 0xFF, 0x9C,
        0xFF, 0xFF, 0xFF, 0xFC, 0xE7, 0xFF, 0xFF, 0x9C,
        0x3F, 0xBF, 0xF7, 0xF0, 0xFF, 0xFF, 0xFF, 0xFC,
        0x1F, 0x1F, 0xE3, 0xE0, 0x1F, 0x1F, 0xE3, 0xE0,
        0x07, 0xFF, 0xFF, 0x80, 0x07, 0xFF, 0xFF, 0x80,
        0x00, 0xE0, 0x1C, 0x00, 0x07, 0xFF, 0xFF, 0x80,
        0x00, 0xE0, 0x1C, 0x00, 0x00, 0xE0, 0x1C, 0x00,
        0x07, 0x00, 0x03, 0x80, 0x07, 0x00, 0x03, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


const GLubyte bitmap[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        , 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00
        , 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00
        , 0x00, 0x00, 0x00, 0x7e, 0x7e, 0x00, 0x00, 0x00
        , 0x00, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0x00
        , 0x00, 0x00, 0x03, 0x83, 0xc3, 0xc0, 0x00, 0x00
        , 0x00, 0x00, 0x1f, 0x3f, 0xfc, 0xf8, 0x00, 0x00
        , 0x00, 0x1c, 0xf0, 0x3e, 0xfd, 0x0f, 0x30, 0x00
        , 0x00, 0x1f, 0x8f, 0x70, 0x0c, 0xe1, 0xf8, 0x00
        , 0x00, 0x30, 0x7f, 0x7f, 0xfe, 0xfe, 0x0c, 0x00
        , 0x00, 0x37, 0xff, 0x6f, 0xf6, 0xff, 0xec, 0x00
        , 0x00, 0x6f, 0xfe, 0xec, 0x37, 0x7f, 0xf6, 0x00
        , 0x00, 0x5f, 0xfe, 0xfc, 0x37, 0x7f, 0xf6, 0x00
        , 0x00, 0xdf, 0xe3, 0xdf, 0xfb, 0xc7, 0xfa, 0x00
        , 0x00, 0xbf, 0x1f, 0xdf, 0xfb, 0xf8, 0xfb, 0x00
        , 0x01, 0xbf, 0xff, 0xdf, 0xfb, 0xfe, 0xfd, 0x00
        , 0x01, 0x7e, 0xff, 0x9f, 0xf9, 0xff, 0x7d, 0x80
        , 0x01, 0x7d, 0xff, 0xbf, 0xf9, 0xff, 0x7e, 0x80
        , 0x02, 0x7d, 0xff, 0xbf, 0xfd, 0xff, 0xbe, 0xc0
        , 0x1e, 0xfb, 0xff, 0x3b, 0xdc, 0xff, 0x9f, 0x78
        , 0x1e, 0xfb, 0xff, 0x31, 0x9c, 0xff, 0xdf, 0x78
        , 0x11, 0xf3, 0xff, 0x38, 0x1c, 0xff, 0xcf, 0x98
        , 0x11, 0xf7, 0xf8, 0xff, 0xff, 0x1f, 0xef, 0x98
        , 0x13, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xd8
        , 0x1b, 0xef, 0xf7, 0xff, 0xff, 0xef, 0xf7, 0xd8
        , 0x1b, 0xcf, 0xf7, 0xff, 0xff, 0xef, 0xf3, 0xd8
        , 0x1b, 0xcf, 0xf7, 0xeb, 0xf7, 0xef, 0xf3, 0xd8
        , 0x1b, 0xdf, 0xe7, 0xfb, 0xd7, 0xe7, 0xf3, 0xd8
        , 0x1b, 0xdf, 0xe7, 0xdf, 0xfb, 0xe7, 0xfb, 0xd0
        , 0x0b, 0xdf, 0xef, 0xdf, 0xfb, 0xe7, 0xf3, 0xd0
        , 0x0b, 0xdf, 0xe7, 0xef, 0xe7, 0xe7, 0xf7, 0xd0
        , 0x0b, 0xef, 0xf3, 0xe3, 0xcf, 0xcf, 0xf7, 0xd0
        , 0x3b, 0xef, 0xf9, 0xf0, 0x0f, 0xbf, 0xf7, 0xdc
        , 0x33, 0xef, 0x7e, 0xf8, 0x1f, 0x7e, 0xe7, 0xcc
        , 0x13, 0xe7, 0xbf, 0x18, 0x18, 0xfd, 0xe7, 0xc8
        , 0x0b, 0xe3, 0xde, 0x00, 0x00, 0x7b, 0xc7, 0x90
        , 0x0d, 0xf3, 0xc7, 0x1c, 0x38, 0xe3, 0x8f, 0x30
        , 0x18, 0xf9, 0xf0, 0xfc, 0x3f, 0x0f, 0x9e, 0x10
        , 0x1b, 0x3c, 0xff, 0xf1, 0x8f, 0xff, 0x7c, 0xd8
        , 0x17, 0x9f, 0x7f, 0xc7, 0xe3, 0xfc, 0xf9, 0xe8
        , 0x17, 0xef, 0x9f, 0x1f, 0xf8, 0xf9, 0xf7, 0xe8
        , 0x17, 0xf7, 0xe0, 0x7f, 0xfe, 0x07, 0xef, 0xe8
        , 0x17, 0xbb, 0xf3, 0xff, 0xff, 0x8f, 0xdd, 0xd8
        , 0x1b, 0xb3, 0xff, 0xff, 0xff, 0xff, 0xcd, 0xd8
        , 0x1b, 0xd3, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xd8
        , 0x0b, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xd0
        , 0x0b, 0xf3, 0xff, 0xfe, 0xff, 0xff, 0xcf, 0xb0
        , 0x0d, 0xff, 0xdf, 0xfe, 0xff, 0xfb, 0xff, 0x30
        , 0x06, 0x7f, 0x8f, 0xfe, 0x7f, 0xf1, 0xfe, 0x60
        , 0x03, 0xbf, 0x27, 0xfe, 0x7f, 0xe4, 0xfd, 0xc0
        , 0x01, 0xc4, 0xf1, 0xfe, 0x7f, 0x0f, 0x23, 0x80
        , 0x00, 0x7f, 0x9f, 0x03, 0x81, 0xf1, 0xfe, 0x00
        , 0x00, 0x1f, 0x07, 0xff, 0xff, 0xe0, 0xf8, 0x00
        , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


float pixelMap[512][512][3]; //[width][height][RGB values]
const int mapSize = 512 * 512 * 3;
float savedPixelMap[mapSize]; //width*height*rgb
const int text_font = (int)GLUT_BITMAP_TIMES_ROMAN_24;
string text = "MSU Invader";


//DRAW FUNCTIONS*********************************************************************


void drawCircle() {
        int radius, xOffset, yOffset;


        xOffset = -20;
        yOffset = 80;
        radius = 25;


        //draws a circle using point coordinates
        glPointSize(3);
        glBegin(GL_POINTS);
        glColor3f(128, 0, 0);                        // color: Maroon
        for (int x = -180; x <= 180; x++) {
                glVertex2i(radius + 100 * sin(x*3.14 / 180) + xOffset, radius - 10 * cos(x*3.14 / 180) + yOffset);                //draws a circle that with a 25 pt radius
        }
        glEnd();


        xOffset = -300;
        yOffset = 80;
        radius = 25;


        //draws a circle using point coordinates
        glPointSize(3);
        glBegin(GL_POINTS);
        for (int x = -180; x <= 180; x++) {
                glVertex2i(radius + 100 * sin(x*3.14 / 180) + xOffset, radius - 10 * cos(x*3.14 / 180) + yOffset);                //draws a circle that with a 50 pt radius
        }
        glEnd();


        xOffset = 300;
        yOffset = 80;
        radius = 25;


        //draws a circle using point coordinates
        glPointSize(3);
        glBegin(GL_POINTS);
        for (int x = -180; x <= 180; x++) {
                glVertex2i(radius + 100 * sin(x*3.14 / 180) + xOffset, radius - 10 * cos(x*3.14 / 180) + yOffset);                //draws a circle that with a 50 pt radius
        }
        glEnd();
}


void drawLines() {
        glLineWidth(3);
        glColor3f(128, 0, 0); //Maroon


        glBegin(GL_LINES);
        glVertex2i(0, 150);
        glVertex2i(0, 200);
        glEnd();


        glBegin(GL_LINES);
        glVertex2i(0, 0);
        glVertex2i(0, -50);
        glEnd();


        glBegin(GL_LINES);
        glVertex2i(0, -150);
        glVertex2i(0, -100);
        glEnd();


        glBegin(GL_LINES);
        glVertex2i(0, -300);
        glVertex2i(0, -250);
        glEnd();
}
void drawFilledPolygon() {
        glEnable(GL_POLYGON_STIPPLE);
        glPolygonStipple(pattern);
        glColor3f(128, 0, 0); //Maroon
        glLineWidth(1);
        glBegin(GL_POLYGON);
        glVertex2f(-250, 512);
        glVertex2f(250, 512);
        glVertex2f(250, 250);
        glVertex2f(-250, 250);
        glEnd();


        glDisable(GL_POLYGON_STIPPLE);
}
void readMapInfo(){
        string file_name, red, green, blue;
        ifstream inputFile;
        cout << "charging lasers..." << endl; //fun message to let user know it's loading
        //MAKE SURE TEXT FILE IS IN YOUR C:\TEMP FOLDER!
        file_name = "c:\\temp\\project1_input.txt";
        inputFile.open(file_name);


        //push file contents into a vector
        for (int y = 0; y < 512; y++) {        //height of image
                for (int x = 0; x < 512; x++) {        //width of image
                        inputFile >> red >> green >> blue;
                        pixelMap[y][x][0] = stof(red);
                        pixelMap[y][x][1] = stof(green);
                        pixelMap[y][x][2] = stof(blue);
                }
        }
        cout << "charging admission..." << endl; //another fun load message
}
void savePixelMap() {
        ofstream outputFile;
        const int width = 512;
        const int height = 512;
        GLenum format = GL_RGB;
        GLenum type = GL_FLOAT;
        string file_name = "c:\\temp\\savedImg.txt";
        float val;


        glReadPixels(0, 0, width, height, format, type, savedPixelMap);


        outputFile.open(file_name);
        cout << "recording high scores..." << endl; //yet another fun load message
        for (int x = 0; x < mapSize; x++) {
                outputFile << savedPixelMap[x] << " ";
        }
        cout << "file saved!" << endl;
        outputFile.close();
}
void drawText()
{
        glColor3f(1, 0, 0);//Red
        glRasterPos2i(-500, -500);
        for (int lcv = 0; lcv < text.length(); lcv++) {        //lcv: loop control variable
                glutBitmapCharacter((void*)text_font, text[lcv]);
        }


}
void drawPixelMap()
{
        cout << "invaders incoming!" << endl;//load message; also fun
        glRasterPos2i(-512, -512);//set raster to be top left coordinate
        glDrawPixels(512, 512, GL_RGB, GL_FLOAT, pixelMap);
}
void drawBitmap()
{
        glColor3f(128, 0, 0);//Maroon
        glRasterPos2i(0, -450);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glBitmap(64, 64, 30, 30, 0, 0, bitmap);
}
//GLUT FUNCTIONS*********************************************************************
void myInit()
{
        glClearColor(0, 0, 0, 0);                        // specify a background clor: white
        gluOrtho2D(-512, 512, -512, 512);  // specify a viewing area
}


void myDisplayCallback()
{
        glClear(GL_COLOR_BUFFER_BIT);        // clears the canvase; builds white background
        drawPixelMap();
        glFlush();        // flush out the buffer contents
        drawCircle();
        drawLines();
        drawBitmap();
        drawFilledPolygon();
        drawText();
        glFlush();


        savePixelMap();
        cout << "Invasion complete. Please come again." << endl;
}


//***********************************************************************************
void main()
{
        //if using a text file to store a bitmap or pattern. call here before glutDisplayFunc
        readMapInfo();


        glutInitWindowSize(512, 512);        // specify a window size
        glutInitWindowPosition(100, 0);        // specify a window position
        glutCreateWindow("Project 1");        // create a titled window


        myInit();        // setting up


        glutDisplayFunc(myDisplayCallback);        // register a callback


        glutMainLoop();                                                        // get into an infinite loop


}




[a]Added more of maroon and red colors so it's easier to see.
[b]Added text files to files needed section.
[c]updated instructions.