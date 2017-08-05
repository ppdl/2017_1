#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <time.h>

#include <vector>
using namespace std;

//----- Global Variables -----//
GLfloat v[4][3] = { { 0.0, 0.0, 1.0 * 30 },
{ 0.0, 0.942809 * 30, -0.33333 * 30 },
{ -0.816497 * 30, -0.471405 * 30, -0.333333 * 30},
{ 0.816497 * 30, -0.471405 * 30, -0.333333 * 30} };

int n = 4;

struct snowflake{
	double x;
	double y;
	double radius;
	double velocity;
	double melt;
	double r, g, b;
};

int window_width;
int window_height;

double DIRECTION = 0.0;

static vector<snowflake*> SNOWFLAKES;

bool randomCOLOR = false;
bool pause = false;
bool stop = false;

// snow quantity
//[light snow] 0 ~ 10 [Heavy snow]
int snow_quantity = 10;

// generate snowflake periodically
int snow_generate = 0;

// disappearing time
int melt_time = 50;

// prototype
void Timer(int extra);

void triangle(GLfloat *a, GLfloat *b, GLfloat *c)
/* display one triangle */
{
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}

void tetrahedron(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
/* display one tetrahedron */
{
	glColor3f(1.0, 0.0, 0.0);
	triangle(a, b, c);
	glColor3f(0.0, 1.0, 0.0);
	triangle(a, b, d);
	glColor3f(0.0, 0.0, 1.0);
	triangle(a, c, d);
	glColor3f(1.0, 1.0, 1.0);
	triangle(b, c, d);
}

void divide_tetrahedron(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m)
{

	GLfloat v1[3], v2[3], v3[3], v4[3], v5[3], v6[3];
	int j;
	if (m>0)
	{
		for (j = 0; j<3; j++) v1[j] = (a[j] + b[j]) / 2;
		for (j = 0; j<3; j++) v2[j] = (a[j] + c[j]) / 2;
		for (j = 0; j<3; j++) v3[j] = (b[j] + c[j]) / 2;
		for (j = 0; j<3; j++) v4[j] = (b[j] + d[j]) / 2;
		for (j = 0; j<3; j++) v5[j] = (c[j] + d[j]) / 2;
		for (j = 0; j<3; j++) v6[j] = (a[j] + d[j]) / 2;
		divide_tetrahedron(a, v1, v2, v6, m - 1);
		divide_tetrahedron(v1, b, v3, v4, m - 1);
		divide_tetrahedron(v2, v3, c, v5, m - 1);
		divide_tetrahedron(v6, v4, v5, d, m - 1);
	}
	else(tetrahedron(a, b, c, d)); /* draw tetrahedron at end of recursion */
}

void init(void)
{
	// setup opengl state
	glClearColor(0, 0, 0, 1.0);
	glColor3f(1.0, 1.0, 1.0);

}

// Setup the viewing transform
// This setup up a display with coordiantes x axis -50 to 50, y axis -50 to 50 
// This callback is called anytime the window size changes (for example, you resize)
// in Windows. 
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);  // set the projection matrix (will talk about this later)
	glLoadIdentity();             // This clear any existing matrix

	// This is a common approach in OpenGL  -- the world does is always the same, no matter
	// the window dim.  So, we need to normalize in case the width and height 
	if (w <= h)                    // normalize by which dimensin is longer 
		glOrtho(-50.0, 50.0,
		-50.0*(GLfloat)h / (GLfloat)w, 50.0*(GLfloat)h / (GLfloat)w, -250.0, 250.0);
	else
		glOrtho(-50.0*(GLfloat)w / (GLfloat)h,
		50.0*(GLfloat)w / (GLfloat)h, -50.0, 50.0, -250.0, 250.0);

	glMatrixMode(GL_MODELVIEW);    // set model transformation
	glLoadIdentity();              // to be empty (will talk about this later
	glutPostRedisplay();
}

snowflake* generateSnowflake(){
	snowflake* s = (snowflake*)malloc(sizeof(snowflake));
	if (s == NULL) return 0;
	s->x = double(rand() % 400 - 200);
	s->y = 50.0 * window_height / 512;
	s->radius = double(rand() % 50) / 10;
	s->velocity = 0.0;
	s->melt = 0;
	if (randomCOLOR){
		s->r = double((rand() % 51) / 100.0) + 0.5;
		s->g = double((rand() % 51) / 100.0) + 0.5;
		s->b = double((rand() % 51) / 100.0) + 0.5;
	}
	else{
		s->r = 1.0;
		s->g = 1.0;
		s->b = 1.0;
	}
	return s;
}

void drawCircle(double x_in, double y_in, double r, double R, double G, double B)
{
	glColor3f(R, G, B);
	for (int i = 0; i < 360; i++){
		glVertex2f(x_in, y_in);
		double x = x_in + r*cos(double(3.141592 / 180)*i);
		double y = y_in + r*sin(double(3.141592 / 180)*i);
		glVertex2f(x, y);
	}
}

void drawSnowflake()
{
	for (vector<snowflake*>::iterator iter = SNOWFLAKES.begin(); iter != SNOWFLAKES.end();){
		//Draw a snowflake
		glBegin(GL_LINE_LOOP);
		drawCircle((*iter)->x, (*iter)->y, (*iter)->radius, (*iter)->r, (*iter)->g, (*iter)->b);
		glEnd();
		if (pause) {
			iter++;
			continue;
		}
		//Snowflake reaches at bottom
		if ((*iter)->y <= -50 * window_height / 512){
			(*iter)->velocity = 0;
			(*iter)->melt += 1; \
				if ((*iter)->melt >= melt_time){
					free((*iter));
					iter = SNOWFLAKES.erase(iter);
				}
				else
					iter++;
		}
		//snowflake fall according to velocity and direction
		else{
			//before reaching termianl velocity, increases velocity by the physics formula
			if ((*iter)->velocity <= 1 / ((*iter)->radius*(*iter)->radius)){
				(*iter)->velocity += 0.01 - 0.005*pow((*iter)->radius,2.0)*(*iter)->velocity;
			}
			(*iter)->y -= (*iter)->velocity;
			(*iter)->x += DIRECTION*(*iter)->velocity;;
			//after reaching terminal velocity, linearly increases velocity
			if ((*iter)->velocity <= 1.0){
				(*iter)->velocity += 0.03;
			}
			iter++;
		}
	}
	glFlush();
}

void display_tetrahedron(void)
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glBegin(GL_TRIANGLES);
	divide_tetrahedron(v[0], v[1], v[2], v[3], n);
	glEnd();
	glFlush();
}

/* Display Function */
void display_snowing(void)
{
	glDisable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	if (!pause){
		if (!stop){
			if (snow_generate >= 31 - 3 * snow_quantity){
				SNOWFLAKES.push_back(generateSnowflake());
				snow_generate = 0;
			}
			snow_generate++;
		}
		drawSnowflake();
	}
	else{
		drawSnowflake();
	}
}
// Timer function
void Timer(int extra)   // ignore varialbe extra
{
	glutPostRedisplay();
	glutTimerFunc(15, Timer, 0);  //   setnext timer to go off
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case ' ':
		if (!pause)
			pause = true;
		else if (pause)
			pause = false;
		break;
	case 'a':	/*   Blow wind to the left   */
	case 'A':
		if (DIRECTION == 0)
			DIRECTION = -1.0;
		else if (DIRECTION == 1.0)
			DIRECTION = 0.0;
		break;
	case 'd':   /*   Blow wind to the right   */
	case 'D':
		if (DIRECTION == -1.0)
			DIRECTION = 0;
		else if (DIRECTION == 0)
			DIRECTION = 1.0;
		break;
	case 'w':   /*   More snow   */
	case 'W':
		if (snow_quantity < 10){
			if (snow_quantity == 0)
				stop = false;
			snow_quantity++;
		}
		break;
	case 's':   /*   Less snow   */
	case 'S':
		if (snow_quantity > 0){
			if (snow_quantity == 1)
				stop = true;
			snow_quantity--;
		}
		break;
	case '1':
		glutDisplayFunc(display_tetrahedron);
		break;
	case '2':
		glutDisplayFunc(display_snowing);
		break;
	case 'r':
	case 'R':
		if (randomCOLOR)
			randomCOLOR = false;
		else
			randomCOLOR = true;
		break;
	case 27:  /*  Escape Key  */
		exit(0);
		break;
	default:
		break;
	}
}

/*  Main Loop
*  Open window with initial window size, title bar,
*  RGB display mode, and handle input events.
*
*  We have registered a keyboard function.  The animation of the
*  square is updated each time you press ' '.
*/

int main(int argc, char** argv)
{
	// Guide
	printf("////////////////////////////////////////////\n");
	printf("// Press [1]  : Tetrahedron Division      //\n");
	printf("// Press [2]  : Snow                      //\n");
	printf("//             - [a]: blow left wind      //\n");
	printf("//             - [b]: blow right wind     //\n");
	printf("//             - [w]: more snow           //\n");
	printf("//             - [s]: less left           //\n");
	printf("//             - [r]: random color ON/OFF //\n");
	printf("//             - [space]: pause           //\n");
	printf("// Press [ESC]: Quit                      //\n");
	printf("////////////////////////////////////////////\n");
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);   // not necessary unless on Unix
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	window_width = 512;
	window_height = 800;
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Snowy");
	init();

	glutReshapeFunc(reshape);       // register respace (anytime window changes)
	glutKeyboardFunc(keyboard);     // register keyboard (anytime keypressed)                                        
	glutDisplayFunc(display_tetrahedron);       // register display function
	glutTimerFunc(0, Timer, 0);     // call first Timer, 0 wait, value passed = 0
	glutMainLoop();
	return 0;
}
