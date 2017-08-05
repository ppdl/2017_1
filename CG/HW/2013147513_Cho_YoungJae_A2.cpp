//  Example: mouseMotion.c
//

#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include <vector>
#include<gl\glut.h>
using namespace std;

void erasing();
void eraseall();

typedef enum {
	LINE,
	RECTANGLE,
	CIRCLE,
	TRIANGLE,
	PETAL,
	BUBBLE
} DRAW;

typedef enum {
	DRAWING,
	SELECT,
	MULTISELECT,
	SELECTED,
} ACTION;

typedef enum{
	NONE,
	MOVE,
	ROTATE,
	CHANGECOLOR_R,
	CHANGECOLOR_G,
	CHANGECOLOR_B
} TRANS;

typedef struct{
	int x;
	int y;
}coord;

typedef struct{
	//origin, destination coordinate
	coord o;
	coord d;
	DRAW draw;
	bool isSelected;
	bool isTranslated;
	bool isTranslating;
	bool cursorOn;
	//move, rotate coordinate
	coord m;
	int r;
}el;

void changeColor();

vector<el*> element_set;

DRAW	 draw_state = LINE;
ACTION	 action_state = DRAWING;
TRANS	 trans_state = NONE;
void drawBitmapText(char *s, float x, float y);
int tempx, tempy;
int linewidth = 1;
double red = 253.0, green = 141.0, blue = 141.0;
int winW, winH;   // <---- window's width (W) and height (H)

int dest_mouseX = 0, dest_mouseY = 0; // <-- use globals to know last mouse click location
int origin_mouseX = 0, origin_mouseY = 0;

bool isButtonPressed = false;
// Track Window Dimensions
void reshape(int w, int h)
{
	winW = w;
	winH = h;

	glMatrixMode(GL_PROJECTION);  // set the projection matrix (will talk about this later)
	glLoadIdentity();             // This clear any existing matrix

	gluOrtho2D(0, w, 0, h);     // use new windows coords as dimensions

	glMatrixMode(GL_MODELVIEW);    // set model transformation
	glLoadIdentity();              // to be empty (will talk about this later
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) // ASCII value 27 = ESC key
		exit(0);
	else if (key == 'l')
		draw_state = LINE;
	else if (key == 'c')
		draw_state = CIRCLE;
	else if (key == 'r')
		draw_state = RECTANGLE;
	else if (key == 't')
		draw_state = TRIANGLE;
	else if (key == 'p')
		draw_state = PETAL;
	else if (key == 'b')
		draw_state = BUBBLE;
	else if (key == '1')
		trans_state = CHANGECOLOR_R;
	else if (key == '2')
		trans_state = CHANGECOLOR_G;
	else if (key == '3')
		trans_state = CHANGECOLOR_B;
	else if (key == 'u')
		erasing();
	else if (key == '+' && linewidth < 11){
		linewidth++;
	}
	else if (key == '-' && linewidth > -1){
		linewidth--;
	}
	else if (key == 'e')
		eraseall();
	else if (key == 'd'){
		for (int i = 0; i < element_set.size(); i++)
		{
			element_set[i]->isSelected = false;
		}
		action_state = DRAWING;
		trans_state = NONE;
	}
	else if (key == 's'){
		for (int i = 0; i < element_set.size(); i++)
		{
			element_set[i]->isSelected = false;
		}
		action_state = SELECT;
		trans_state = NONE;
	}
	else if (key == 'm'){
		action_state = MULTISELECT;
		trans_state = NONE;
	}
	else if (key == 'o'){
		if (action_state == SELECTED)
			trans_state = ROTATE;
	}
}
void keyboardup(unsigned char key, int x, int y)
{
	if (key == 'm'){
		action_state = SELECTED;
		trans_state = MOVE;
	}
}

// MousePress: Called when mouse is pressed.  Most likely the mouseMotion func will
// be called immediately afterwards if the mouse button is still down.
// NOTE: a single click will cause this function to be called twice
// once for GLUT_DOWN and once for GLUT_UP
void mousePress(GLint button, GLint state, GLint x, GLint y)
{
	if (button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN)
	{
		if (action_state == DRAWING){
			element_set.push_back((el*)malloc(sizeof(el)));
		}
		tempx = origin_mouseX;
		tempy = origin_mouseY;
		isButtonPressed = true;
		dest_mouseX = x;
		dest_mouseY = winH - y;
		glutPostRedisplay();
	}
	if (button == GLUT_LEFT_BUTTON  && state == GLUT_UP)
	{
		if (trans_state == ROTATE)
			trans_state = NONE;
		isButtonPressed = false;
		if (!element_set.empty())
			element_set.back()->cursorOn = false;


		for (int i = 0; i < element_set.size(); i++){
			if (element_set[i]->isTranslating){
				element_set[i]->isTranslating = false;
				element_set[i]->isTranslated = true;
			}
		}

		dest_mouseX = x;
		dest_mouseY = winH - y;
		glutPostRedisplay();
	}

	if (button == GLUT_RIGHT_BUTTON  && state == GLUT_DOWN)
	{
		dest_mouseX = x;
		dest_mouseY = winH - y;
		glutPostRedisplay();
	}
	if (button == GLUT_RIGHT_BUTTON  && state == GLUT_UP)
	{
		dest_mouseX = x;
		dest_mouseY = winH - y;
		glutPostRedisplay();
	}

}

void drawCursorArrow()
{
	if (trans_state == ROTATE || trans_state == CHANGECOLOR_R || trans_state == CHANGECOLOR_G || trans_state == CHANGECOLOR_B){
		if (isButtonPressed){
			glColor3f(1, 1, 0);
			glBegin(GL_LINE_STRIP);
			int posX = dest_mouseX;
			int posY = dest_mouseY;
			glVertex2i(posX - 3, posY + 3);
			glVertex2i(posX - 6, posY + 6);
			glVertex2i(posX - 9, posY + 3);
			glEnd();
			glBegin(GL_LINE_STRIP);
			glVertex2i(posX - 6, posY + 6);
			glVertex2i(posX - 6, posY - 6);
			glEnd();
			glBegin(GL_LINE_STRIP);
			glVertex2i(posX - 3, posY - 3);
			glVertex2i(posX - 6, posY - 6);
			glVertex2i(posX - 9, posY - 3);
			glEnd();
		}
		else{
			glColor3f(1, 0, 0);
			glBegin(GL_LINE_STRIP);
			int posX = origin_mouseX;
			int posY = origin_mouseY;
			glVertex2i(posX - 3, posY + 3);
			glVertex2i(posX - 6, posY + 6);
			glVertex2i(posX - 9, posY + 3);
			glEnd();
			glBegin(GL_LINE_STRIP);
			glVertex2i(posX - 6, posY + 6);
			glVertex2i(posX - 6, posY - 6);
			glEnd();
			glBegin(GL_LINE_STRIP);
			glVertex2i(posX - 3, posY - 3);
			glVertex2i(posX - 6, posY - 6);
			glVertex2i(posX - 9, posY - 3);
			glEnd();
		}
	}
	glColor3f(double(red / 255), double(green / 255), double(blue / 255));
}



void drawCursorPoint(int x, int y)
{
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++){
		int cx = x + 5 * cos(double(3.141592 / 180)*i);
		int cy = y + 5 * sin(double(3.141592 / 180)*i);
		glVertex2i(cx, cy);
	}
	glEnd();
	glColor3f(double(red / 255), double(green / 255), double(blue / 255));
}

void drawCursorPointY(int x, int y)
{
	glColor3f(1, 1, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++){
		int cx = x + 5 * cos(double(3.141592 / 180)*i);
		int cy = y + 5 * sin(double(3.141592 / 180)*i);
		glVertex2i(cx, cy);
	}
	glEnd();
	glColor3f(double(red / 255), double(green / 255), double(blue / 255));
}

void changeColor()
{
	int nc;
	if (isButtonPressed && (action_state == SELECT || action_state == SELECTED)){
		switch (trans_state){
		case(CHANGECOLOR_R) :
			nc = dest_mouseY - tempy;
			if (red < 0)
				red = 0;
			else if (red > 255)
				red = 255;
			else
				red += nc;
			tempy = dest_mouseY;
			break;
		case(CHANGECOLOR_G) :
			nc = dest_mouseY - tempy;
			if (green < 0)
				green = 0;
			else if (green > 255)
				green = 255;
			else
				green += nc;
			tempy = dest_mouseY;
			break;
		case(CHANGECOLOR_B) :
			nc = dest_mouseY - tempy;
			if (blue < 0)
				blue = 0;
			else if (blue > 255)
				blue = 255;
			else
				blue += nc;
			tempy = dest_mouseY;
			break;
		default:break;
		}
	}
}


void colorState()
{
	glColor3d(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(420, 500);
	glVertex2i(445, 500);
	glVertex2i(445, 490);
	glVertex2i(420, 490);
	glEnd();
	glColor3d(0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2i(450, 500);
	glVertex2i(475, 500);
	glVertex2i(475, 490);
	glVertex2i(450, 490);
	glEnd();
	glColor3d(0, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2i(480, 500);
	glVertex2i(505, 500);
	glVertex2i(505, 490);
	glVertex2i(480, 490);
	glEnd();

	glColor3d(double(red / 255), 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(420, 485);
	glVertex2i(445, 485);
	glVertex2i(445, 463);
	glVertex2i(420, 463);
	glEnd();
	glColor3d(0, double(green / 255), 0);
	glBegin(GL_POLYGON);
	glVertex2i(450, 485);
	glVertex2i(475, 485);
	glVertex2i(475, 463);
	glVertex2i(450, 463);
	glEnd();
	glColor3d(0, 0, double(blue / 255));
	glBegin(GL_POLYGON);
	glVertex2i(480, 485);
	glVertex2i(505, 485);
	glVertex2i(505, 463);
	glVertex2i(480, 463);
	glEnd();

	glColor3d(double(red / 255), double(green / 255), double(blue / 255));
	glBegin(GL_POLYGON);
	glVertex2i(420, 460);
	glVertex2i(505, 460);
	glVertex2i(505, 446);
	glVertex2i(420, 446);
	glEnd();
}

void drawState(){
	glLoadIdentity();
	glColor3f(1, 1, 1);
	switch (draw_state){
	case(LINE) :
		drawBitmapText("FIGURE:LINE ", 300, 490);
		break;
	case(CIRCLE) :
		drawBitmapText("FIGURE:CIRCLE ", 300, 490);
		break;
	case(RECTANGLE) :
		drawBitmapText("FIGURE:RECTANGLE ", 300, 490);
		break;
	case(TRIANGLE) :
		drawBitmapText("FIGURE:TRIANGLE ", 300, 490);
		break;
	case(PETAL) :
		drawBitmapText("FIGURE:PETAL ", 300, 490);
		break;
	case(BUBBLE) :
		drawBitmapText("FIGURE:BUBBLE ", 300, 490);
		break;
	default:
		break;
	}
	switch (action_state){
	case(DRAWING) :
		drawBitmapText("ACTION:DRAWING ", 300, 470);
		break;
	case(SELECT) :
		drawBitmapText("ACTION:SELECT ", 300, 470);
		break;
	case(MULTISELECT) :
		drawBitmapText("ACTION:MULTISELECT ", 300, 470);
		break;
	case(SELECTED) :
		drawBitmapText("ACTION:SELECTED ", 300, 470);
		break;

	default:
		break;
	}
	switch (trans_state){
	case(NONE) :
		drawBitmapText("TRANSF:NONE ", 300, 450);
		break;
	case(MOVE) :
		drawBitmapText("TRANSF:MOVE ", 300, 450);
		break;
	case(ROTATE) :
		drawBitmapText("TRANSF:ROTATE ", 300, 450);
		break;
	case(CHANGECOLOR_R) :
		drawBitmapText("TRANSF:CHANGE_RED ", 300, 450);
		break;
	case(CHANGECOLOR_G) :
		drawBitmapText("TRANSF:CHANGE_GREN ", 300, 450);
		break;
	case(CHANGECOLOR_B) :
		drawBitmapText("TRANSF:CHANGE_BLUE ", 300, 450);
		break;
	}
}

void drawing(el *e)
{
	glLineWidth(linewidth);
	int r;
	if (e->cursorOn){
		drawCursorPoint(e->o.x, e->o.y);
		drawCursorPoint(e->d.x, e->d.y);
	}
	if (action_state == SELECTED || isButtonPressed){
		if (trans_state == MOVE){
			int difx = dest_mouseX - tempx;
			int dify = dest_mouseY - tempy;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(difx, dify, 0);
			tempx = dest_mouseX;
			tempy = dest_mouseY;
		}
	}
	else
		glLoadIdentity();

	if (trans_state == ROTATE && e->isSelected){
		int deg = dest_mouseY - tempy;
		int cx, cy;
		cx = (e->o.x + e->d.x) / 2;
		cy = (e->o.y + e->d.y) / 2;
		e->isTranslating = true;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(cx, cy, 0);
		glRotated(deg, 0, 0, 1);
		glTranslated(-cx, -cy, 0);
		e->r = deg;
	}
	else if (e->isTranslated){
		int cx = (e->o.x + e->d.x) / 2;
		int cy = (e->o.y + e->d.y) / 2;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(cx, cy, 0);
		glRotated(e->r, 0, 0, 1);
		glTranslated(-cx, -cy, 0);
	}
	else
		glLoadIdentity();


	switch (e->draw)
	{
	case LINE:
		glBegin(GL_LINE_LOOP);
		glVertex2i(e->o.x, e->o.y);
		glVertex2i(e->d.x, e->d.y);
		glEnd();
		break;
	case CIRCLE:
		glBegin(GL_LINE_LOOP);
		r = int(sqrt(pow(e->o.x - e->d.x, 2) + pow(e->o.y - e->d.y, 2)));
		for (int i = 0; i < 360; i++){
			int x = e->o.x + r*cos(double(3.141592 / 180)*i);
			int y = e->o.y + r*sin(double(3.141592 / 180)*i);
			glVertex2i(x, y);
		}
		glEnd();
		break;
	case RECTANGLE:
		glBegin(GL_LINE_LOOP);
		glVertex2i(e->o.x, e->o.y);
		glVertex2i(e->d.x, e->o.y);
		glVertex2i(e->d.x, e->d.y);
		glVertex2i(e->o.x, e->d.y);
		glEnd();
		break;
	case TRIANGLE:
		glBegin(GL_LINE_LOOP);
		glVertex2i(e->o.x, e->o.y);
		glVertex2i(e->d.x, e->d.y);
		glVertex2i(e->o.x, e->d.y);
		glEnd();
		break;
	case PETAL:
		glBegin(GL_LINE_LOOP);
		r = int(sqrt(pow(e->o.x - e->d.x, 2) + pow(e->o.y - e->d.y, 2)));
		for (int i = 0; i < 360; i++){
			int x = e->o.x + r*sin((double(3.141592 / 180)*i) * 2)*cos(double(3.141592 / 180)*i);
			int y = e->o.y + r*sin((double(3.141592 / 180)*i) * 2)*sin(double(3.141592 / 180)*i);
			glVertex2i(x, y);
		}
		glEnd();
		break;
	case BUBBLE:
		glBegin(GL_LINE_LOOP);
		int R = 30;
		r = int(sqrt(pow(e->o.x - e->d.x, 2) + pow(e->o.y - e->d.y, 2)));
		for (int i = 0; i < 360; i++){
			int x = e->o.x + (R - r)*cos(double(3.141592 / 180)*i) + 10 * cos(double(R - r / 1)*(double(3.141592 / 180)*i));
			int y = e->o.y + (R - r)*sin(double(3.141592 / 180)*i) + 10 * sin(double(R - r / 1)*(double(3.141592 / 180)*i));
			glVertex2i(x, y);
		}
		glEnd();
		break;
	}


	if ((action_state == SELECT || action_state == MULTISELECT || action_state == SELECTED) && e->isSelected){
		drawCursorPointY(e->o.x, e->o.y);
		drawCursorPointY(e->d.x, e->d.y);
	}
}

void selecting(int x, int y)
{
	if (element_set.empty()) return;
	if (action_state != SELECT && action_state != MULTISELECT) return;
	if (action_state == SELECTED) return;
	int close_dist = 20;
	int idx = -1;
	for (int i = 0; i < element_set.size(); i++){
		int dist1 = sqrt(pow(element_set[i]->o.x - x, 2) + pow(element_set[i]->o.y - y, 2));
		if (dist1 < close_dist){
			close_dist = dist1;
			idx = i;
		}
		int dist2 = sqrt(pow(element_set[i]->d.x - x, 2) + pow(element_set[i]->d.y - y, 2));
		if (dist2 < close_dist){
			close_dist = dist2;
			idx = i;
		}
	}
	if (idx >= 0 && !element_set[idx]->isSelected){
		drawCursorPoint(element_set[idx]->o.x, element_set[idx]->o.y);
		drawCursorPoint(element_set[idx]->d.x, element_set[idx]->d.y);
		if (isButtonPressed){
			element_set[idx]->isSelected = true;
			if (action_state != MULTISELECT){
				action_state = SELECTED;
				trans_state = MOVE;
			}
		}
	}
}


void moving(int x, int y)
{
	if (element_set.empty()) return;
	if (action_state == SELECTED && trans_state == MOVE){
		for (int i = 0; i < element_set.size(); i++){
			if (!element_set[i]->isSelected) continue;
			int mx = x - tempx;
			int my = y - tempy;
			element_set[i]->o.x += mx;
			element_set[i]->o.y += my;
			element_set[i]->d.x += mx;
			element_set[i]->d.y += my;
		}
	}
}


void erasing()
{
	if (element_set.size() == 0) return;
	free(element_set.back());
	element_set.pop_back();
}

void eraseall()
{
	for (int i = 0; i < element_set.size(); i++)
		free(element_set[i]);
	element_set.clear();
}

void drawBitmapText(char *string, float x, float y)
{
	char *c;
	glRasterPos2f(x, y);

	for (c = string; *c != ' '; c++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
}

// MouseMotion: Called anytime mouse moves and button _is_ pressed
// note that we don't know which button is pressed, so this works
// with left/right/middle button
// if we want to know which button, we need to set a global variable in the
// mousePress callback
// ´­·ÈÀ»¶§
void mouseMotion(int x, int y)
{
	if (action_state == DRAWING){
		element_set.back()->o.x = origin_mouseX;
		element_set.back()->o.y = origin_mouseY;
		element_set.back()->d.x = dest_mouseX;
		element_set.back()->d.y = dest_mouseY;
		element_set.back()->draw = draw_state;
		element_set.back()->isSelected = false;
		element_set.back()->isTranslated = false;
		element_set.back()->isTranslating = false;
		element_set.back()->cursorOn = true;
	}

	//if (action_state == SELECTED && (trans_state == MOVE || trans_state == ROTATE))
	//	moving(x, y);

	isButtonPressed = true;
	dest_mouseX = x;
	dest_mouseY = winH - y;
	glutPostRedisplay();
}

// call anytime mouse moves and no button presed
// ¾È´­·¶À»¶§
void mousePassiveMotion(int x, int y)
{
	printf("%d, %d\n", x, y);
	origin_mouseX = x;
	origin_mouseY = winH - y;
}

void display()
{
	glClearColor(0, 0, 0, 0);

	glClear(GL_COLOR_BUFFER_BIT);
	drawState();
	colorState();
	changeColor();
	drawCursorArrow();

	if (isButtonPressed && action_state == SELECTED){
		moving(dest_mouseX, dest_mouseY);
	}
	for (vector<el*>::iterator iter = element_set.begin(); iter != element_set.end(); iter++)
		drawing((*iter));
	selecting(origin_mouseX, origin_mouseY);
	glFlush();
	glutSwapBuffers();
}


// HEY, look, i'm ignoring the command line!
// 
int main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Paint");
	printf("*DRAW MODE:\n");
	printf("  [L]: LINE\n");
	printf("  [C]: CIRCLE\n");
	printf("  [R]: RECTANGLE\n");
	printf("  [T]: TRIANGLE\n");
	printf("  [P]: PETAL\n");
	printf("  [B]: BUBBLE\n");
	printf("*ACTION MODE:\n");
	printf("  [S]: SELECT\n");
	printf("  [M]: MULTISELECT\n");
	printf("*TRASITION MODE\n");
	printf("  [O]: ROTATE\n");
	printf("  [1]: CHANGE COLOR RED\n");
	printf("  [2]: CHANGE COLOR GREEN\n");
	printf("  [3]: CHANGE COLOR BLUE\n");
	printf("      -color can be modified in select, selected mode");
	glutReshapeFunc(reshape);       // register respace (anytime window changes)
	glutKeyboardFunc(keyboard);     // register keyboard func
	glutKeyboardUpFunc(keyboardup);
	glutMouseFunc(mousePress);      // register mouse press funct
	glutMotionFunc(mouseMotion);     // ** Note, the name is just glutMotionFunc (not glutMouseMotionFunc)
	glutPassiveMotionFunc(mousePassiveMotion); // Passive motion                 
	glutDisplayFunc(display);       // register display function
	glutIdleFunc(display);
	glutMainLoop();

	return 1;

}
