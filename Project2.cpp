/*==================================================================================================
PROGRAMMERS:			Alisha Greer, Dan West
COURSE:					CSC 525/625
LAST MODIFIED BY:		Alisha Greer
LAST MODIFIED DATE:		11/10/2016
DESCRIPTION:			Project2: text editor
FILES:					Project2.cpp, typed.txt
Partner 1 (Alisha): //Trace folder: Alisha923
	Contribution: 50% Created overall program layout/template. Created menus, windows and buttons.
	Created menu callback, info display and keyboard callback. 
Partner 2 (Dan): //Trace folder: West777
	Contribution: 50% Wrote editorDisplay, myMouseCallback, and SaveTextToFile functions. Added ENTER 
	functionality to keyboard events. Added Save menu item.
IDE/COMPILER:			MicroSoft Visual Studio 2013
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Make sure type.txt is in your c:\temp folder
2.		Double click on projProject.sln	to OPEN the project
3.		Press Ctrl+F7					to COMPILE
4.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
5.		Press Ctrl+F5					to EXECUTE
==================================================================================================*/
#include <iostream>
#include <fstream>
#include <GL/glut.h>				// include GLUT library
#include <math.h>
#include <string>
#include <vector>
using namespace std;

//STURCTURES*************************************************************************
struct Character {
	char value;
	int width;
	int color_mode;
	void* font;
};

//GLOBAL VARIABLES*******************************************************************
//Windows
int info_window, edit_window;
//Menus
int font_menu, info_menu, color_menu, exit_menu, main_menu;
//Buttons
bool press_left = false;
bool press_right = false;
bool press_enter = false;
//Colors
bool color1 = false;
bool color2 = false;
bool color3 = false;
//Fonts
bool font1 = false;
bool font2 = false;
bool font3 = false;
//Mouse position
int mouse_x = 0;
int mouse_y = 0;
//Storing characters
vector<Character> current_key;

//Window Dimensions
const int text_win_height = 750;
const int text_win_width = 750;
const int info_win_height = 400;
const int info_win_width = 400;
//Cursor Coordinate Used For Printing
//each has some padding build in to it 
int origin_x = -text_win_width + 10;
int origin_y = text_win_height - 50;
//Row Height
int row_height = 48;
//String that collects users input for output to file
string raw_input;
//Info Text
const int text_font = (int)GLUT_BITMAP_HELVETICA_18;
string text1 = "INSTRUCTION FOR COMPILATION AND EXECUTION:";
string text2 = "1.Double click on labProj.sln to OPEN the project";
string text3 = "2.Press Ctrl+F7 to COMPILE";
string text4 = "3.Press Ctrl + Shift + B to BUILD(COMPILE + LINK)";
string text5 = "4.Press Ctrl + F5  to EXECUTE";
string text6 = "-----------------------------------------------------------------------------";
string text7 = "-This program is a text editor that allows you to type text in mutiple colors and fonts.";
string text8 = "-If you would like to change the text color, right click the editor window and select a color.";
string text9 = "-If you would like to change the font, right click the editor window and select a font.";
string text10 = "-If you would like to move the text to another line, left click on a location or press the enter key.";
string text11 = "-If you would like to close or hide the info menu, right click the editor window and select your choice.";
string text12 = "-If you would like to save what you have typed, right click the editor window and select save.";
string text13 = "-If you would like to retrieve your saved file , go to C:\\temp\\ and the file is named typed.txt";

//***********************************************************************************
void drawAxes(int win_width, int win_height) {
	glPointSize(1);		// change point size back to 1

	glBegin(GL_POINTS);	// use points to form X-/Y-axes
	glColor3f(0, 0, 1);	// change drawing color to blue
	for (int x = -text_win_width; x <= text_win_width; x++) // draw X-axis
		glVertex2i(x, 0);
	for (int y = -text_win_height; y <= text_win_height; y++) // draw Y-axis
		glVertex2i(0, y);
	glEnd();

	glColor3f(0, 0, 0);//change color to black
	glRasterPos2s(win_width - 30, 0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 120); //print 'x'
	glRasterPos2s(0, win_height - 30);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 121); //print 'y'
}

//***********************************************************************************
void InfoDisplay() {
	glColor3f(0, 0, 0);//Black
	glutShowWindow();
	glRasterPos2i(-400, 300);
	for (int lcv = 0; lcv < text1.length(); lcv++) {	//lcv: loop control variable
		glutBitmapCharacter((void*)text_font, text1[lcv]);
	}
	glRasterPos2i(-400, 270);
	for (int lcv = 0; lcv < text2.length(); lcv++) {	//lcv: loop control variable
		glutBitmapCharacter((void*)text_font, text2[lcv]);
	}
	glRasterPos2i(-400, 240);
	for (int lcv = 0; lcv < text3.length(); lcv++) {	//lcv: loop control variable
		glutBitmapCharacter((void*)text_font, text3[lcv]);
	}
	glRasterPos2i(-400, 210);
	for (int lcv = 0; lcv < text4.length(); lcv++) {	//lcv: loop control variable
		glutBitmapCharacter((void*)text_font, text4[lcv]);
	}
	glRasterPos2i(-400, 180);
	for (int lcv = 0; lcv < text5.length(); lcv++) {	//lcv: loop control variable
		glutBitmapCharacter((void*)text_font, text5[lcv]);
	}
	glRasterPos2i(-400, 120);
	for (int lcv = 0; lcv < text6.length(); lcv++) {	//lcv: loop control variable
		glutBitmapCharacter((void*)text_font, text6[lcv]);
	}
	glRasterPos2i(-400, 60);
	for (int lcv = 0; lcv < text7.length(); lcv++) {	//lcv: loop control variable
		glutBitmapCharacter((void*)text_font, text7[lcv]);
	}
	glRasterPos2i(-400, 0);
	for (int lcv = 0; lcv < text8.length(); lcv++) {	//lcv: loop control variable
		glutBitmapCharacter((void*)text_font, text8[lcv]);
	}
	glRasterPos2i(-400, -60);
	for (int lcv = 0; lcv < text9.length(); lcv++) {	//lcv: loop control variable
		glutBitmapCharacter((void*)text_font, text9[lcv]);
	}
	glRasterPos2i(-400, -120);
	for (int lcv = 0; lcv < text10.length(); lcv++) {	//lcv: loop control variable
		glutBitmapCharacter((void*)text_font, text10[lcv]);
	}

	glRasterPos2i(-400, -180);
	for (int lcv = 0; lcv < text11.length(); lcv++) {	//lcv: loop control variable
		glutBitmapCharacter((void*)text_font, text11[lcv]);
	}

	glRasterPos2i(-400, -240);
	for (int lcv = 0; lcv < text12.length(); lcv++) {	//lcv: loop control variable
		glutBitmapCharacter((void*)text_font, text12[lcv]);
	}

	glRasterPos2i(-400, -300);
	for (int lcv = 0; lcv < text13.length(); lcv++) {	//lcv: loop control variable
		glutBitmapCharacter((void*)text_font, text13[lcv]);
	}
}

//***********************************************************************************
void EditorDisplay(vector<Character> key){
	int cursor_x = origin_x;
	int cursor_y = origin_y;
	int word_length = 0;
	vector<Character> current_word;
	//make sure current word is empty when this method is called.
	current_word.clear();
	
	//drawAxes(text_win_width, text_win_height);

	//move raster to origin for pringint text (top left or where user clicked)
	glRasterPos2s(origin_x, origin_y); 

	//print the contents of key to the text editor window
	for (int i = 0; i < key.size(); i++) {
		//an empty space or new line character signifies the end of a word.
		//print contents of current_word
		if (key[i].value == '\n' || key[i].value == ' ') {
			//print current word
			for (int c = 0; c < current_word.size(); c++) {
				//set color
				if (current_word[c].color_mode == 1) { glColor3f(1, 0, 0); }
				else if (current_word[c].color_mode == 2) { glColor3f(0, 0, 1); }
				else if (current_word[c].color_mode == 3) { glColor3f(0, 1, 0); }
				else { glColor3f(0, 0, 0); }
				//print character and move cursor
				glRasterPos2i(cursor_x, cursor_y);
				glutBitmapCharacter(current_word[c].font, current_word[c].value);
				cursor_x += current_word[c].width;
			}//if new line character move cursor to next line
			if (key[i].value == '\n') {
				cursor_x = origin_x;
				cursor_y -= row_height;
			}
			else if (key[i].value == ' ') {
				//print the space character and clear current_word
				cursor_x += key[i].width;
			}
			current_word.clear();
			word_length = 0;
		}
		else {
			//add current character to current_word if it is not a space or new line char
			current_word.push_back(key[i]);
			word_length += key[i].width;
		}
		//if current word would print off the screen go to a new line
		if (cursor_x + word_length >= text_win_width -10){
			//in the event of a very long word... (1/4 the screen)
			if (word_length >= text_win_width / 2) {
				//print part of the word on the first line
				for (int c = 0; c < current_word.size(); c++) {
					//set color
					if (current_word[c].color_mode == 1) { glColor3f(1, 0, 0); }
					else if (current_word[c].color_mode == 2) { glColor3f(0, 0, 1); }
					else if (current_word[c].color_mode == 3) { glColor3f(0, 1, 0); }
					else { glColor3f(0, 0, 0); }
					//if cursor is about to move to last space on line
					if (cursor_x + current_word[c].width >= text_win_width - 10) {
						//print '-' and move cursor to right
						glRasterPos2i(cursor_x, cursor_y);
						glutBitmapCharacter(current_word[c].font, '-');
						cursor_y -= row_height;
						cursor_x = origin_x;
					}
					//print character and move cursor to right
					glRasterPos2i(cursor_x, cursor_y);
					glutBitmapCharacter(current_word[c].font, current_word[c].value);
					cursor_x += current_word[c].width;
				}
				//clear current word variables afterin printing
				current_word.clear();
				word_length = 0;
			}
			else {//otherwise just move down a line
				cursor_x = origin_x;
				cursor_y -= row_height;
			}
		}
		//if there are no more characters left to print, print the last instance of current_word
		if (i == key.size() - 1) {
			//print contents of current_word
			for (int c = 0; c < current_word.size(); c++) {
				//set color
				if (current_word[c].color_mode == 1) { glColor3f(1, 0, 0); }
				else if (current_word[c].color_mode == 2) { glColor3f(0, 0, 1); }
				else if (current_word[c].color_mode == 3) { glColor3f(0, 1, 0); }
				else { glColor3f(0, 0, 0); }
				//print character and move cursor
				glRasterPos2i(cursor_x, cursor_y);
				glutBitmapCharacter(current_word[c].font, current_word[c].value);
				cursor_x += current_word[c].width;
			}
			current_word.clear();
			word_length = 0;
		}
	}
}

//***********************************************************************************
void saveTextToFile() {
	ofstream output_file;
	output_file.open("C:\\temp\\typed.txt");

	if (!output_file.is_open()) {
		cout << "Unable to find result.txt. Please check your C:\\temp folder and try again." << endl;
	}
	else {
		output_file << raw_input;
	}
	output_file.close();
}

//***********************************************************************************
void myInit(){
	glClearColor(1, 1, 1, 0);			// specify a background clor: white 
	gluOrtho2D(-text_win_width, text_win_width, -text_win_height, text_win_height);  // specify a viewing area
}

void myInit2(){
	glClearColor(1, 1, 1, 0);			// specify a background clor: white 
	gluOrtho2D(-400, 400, -400, 400);  // specify a viewing area
}

//***********************************************************************************
void myDisplayCallback1(){
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background
	InfoDisplay();
	glFlush(); // flush out the buffer contents
}

//***********************************************************************************
void myDisplayCallback2(){
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background
	EditorDisplay(current_key);
	glFlush(); // flush out the buffer contents
}

//***********************************************************************************
void myKeyboardEventCallback(unsigned char key, int cursorX, int cursorY){
	Character entered_key;
	//build the current key structure
	//set color of current key
	if (color1) { entered_key.color_mode = 1; }
	else if (color2) { entered_key.color_mode = 2; }
	else if (color3) { entered_key.color_mode = 3; }
	else { entered_key.color_mode = 0; }//default color: black
	//set font and character width
	if (font1) {
		entered_key.font = GLUT_BITMAP_HELVETICA_18;
		entered_key.width = 36;
	}
	else if (font2) {
		entered_key.font = GLUT_BITMAP_TIMES_ROMAN_24;
		entered_key.width = 48;
	}
	else {
		entered_key.font = GLUT_BITMAP_9_BY_15;
		entered_key.width = 30;
	}

	mouse_x = 400 - (800 - (cursorX * 2));
	mouse_y = -400 + (800 - (cursorY * 2));

	if (key == 8) {//if backspace

		if (current_key.size() != 0)//if you still have characters
		{
			current_key.pop_back();//remove character
			raw_input.pop_back();
		}
	}
	else if (key == 13) { //if ENTER
		entered_key.value = '\n';
		current_key.push_back(entered_key);
		raw_input += '\n';
	}
	else{//print normally
		entered_key.value = key;
		current_key.push_back(entered_key);
		raw_input += key;
	}

	glutSetWindow(edit_window);//Display on Edit window
	myDisplayCallback2();
}

//***********************************************************************************
void myMenuCallback(int item){
	switch (item) {
	case 1:
		glutSetWindow(edit_window); font1 = true; font2 = false; font3 = false; myDisplayCallback2(); break;
	case 2:
		glutSetWindow(edit_window); font1 = false; font2 = true; font3 = false; myDisplayCallback2(); break;
	case 3:
		glutSetWindow(edit_window); font1 = false; font2 = false; font3 = true; myDisplayCallback2(); break;
	case 4:
		glutSetWindow(edit_window); color1 = true; color2 = false; color3 = false; myDisplayCallback2(); break;
	case 5:
		glutSetWindow(edit_window); color1 = false; color2 = true; color3 = false; myDisplayCallback2(); break;
	case 6:
		glutSetWindow(edit_window); color1 = false; color2 = false; color3 = true; myDisplayCallback2(); break;
	case 7:
		glutSetWindow(info_window); glutHideWindow(); break;
	case 8:
		glutSetWindow(info_window); glutShowWindow(); break;
	case 9:
		exit(1);//exit program
	case 10:
		saveTextToFile(); break;
	}
}

//***********************************************************************************
void myMouseCallback(int buttonName, int state, int cursorX, int cursorY) {
	if ((buttonName == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {
		origin_x = cursorX*2 - text_win_width;
		origin_y = text_win_height - cursorY*2;
	}
}

//MAIN*******************************************************************************
void main(){
	//Window 1
	glutInitWindowSize(850, 400);				// specify a window size
	glutInitWindowPosition(830, 0);			// specify a window position
	info_window = glutCreateWindow("Info");	// create a titled window
	myInit2();									// setting up W1
	glutDisplayFunc(myDisplayCallback1);		// register a callback

	//Window 2
	glutInitWindowSize(text_win_width, text_win_height);// specify a window size
	glutInitWindowPosition(70, 0);			// specify a window position
	edit_window = glutCreateWindow("Text Editor");	// create a titled window
	myInit();									// setting up W2
	glutDisplayFunc(myDisplayCallback2);		// register a callback
	glutKeyboardFunc(myKeyboardEventCallback);
	glutMouseFunc(myMouseCallback);
	//Menu
	exit_menu = glutCreateMenu(myMenuCallback);
	//Entries
	glutAddMenuEntry("Exit program", 9);

	//Menu
	font_menu = glutCreateMenu(myMenuCallback);
	//Entries
	glutAddMenuEntry("Times New Roman", 1);
	glutAddMenuEntry("Helvetica", 2);
	glutAddMenuEntry("Standard", 3);

	//Menu
	color_menu = glutCreateMenu(myMenuCallback);
	//Entries
	glutAddMenuEntry("Red", 4);
	glutAddMenuEntry("Blue", 5);
	glutAddMenuEntry("Green", 6);

	//Menu
	info_menu = glutCreateMenu(myMenuCallback);
	//Entries
	glutAddMenuEntry("Hide info", 7);
	glutAddMenuEntry("Show info", 8);

	//Menu
	main_menu = glutCreateMenu(myMenuCallback);//Menu that all subMenus go into

   //SubMenus
	glutAddSubMenu("Text Font", font_menu);
	glutAddSubMenu("Text color", color_menu);
	glutAddSubMenu("Info Window", info_menu);
	glutAddSubMenu("Exit", exit_menu);
	glutAddMenuEntry("Save", 10);

	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();							// get into an infinite loop
}