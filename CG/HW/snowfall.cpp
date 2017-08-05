#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <time.h>

#include <vector>
using namespace std;

//----- Global Variables -----//
struct snowflake{
	double x;
	double y;
	double radius;
	double velocity;
	double melt;
};

int window_width;
int window_height;

double DIRECTION = 0.0;

static vector<snowflake*> SNOWFLAKES;

bool pause = false;
bool stop = false;

// snow quantity
//[light snow] 0 ~ 10 [Heavy snow]
int snow_quantity = 10;

// generate snowflake periodically
int snow_generate = 0;

// disappearing time
int melt_time = 100;

// prototype
void Timer(int extra);


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
	glMatrixMode(GL_PROJECTION);  // set the projection matrix (will talk about this later)
	glLoadIdentity();             // This clear any existing matrix

	// This is a common approach in OpenGL  -- the world does is always the same, no matter
	// the window dim.  So, we need to normalize in case the width and height 
	if (w <= h)                    // normalize by which dimensin is longer 
		gluOrtho2D(-50.0, 50.0,
		-50.0*(GLfloat)h / (GLfloat)w, 50.0*(GLfloat)h / (GLfloat)w);
	else
		gluOrtho2D(-50.0*(GLfloat)w / (GLfloat)h,
		50.0*(GLfloat)w / (GLfloat)h, -50.0, 50.0);

	glMatrixMode(GL_MODELVIEW);    // set model transformation
	glLoadIdentity();              // to be empty (will talk about this later
}

snowflake* generateSnowflake(){
	snowflake* s = (snowflake*)malloc(sizeof(snowflake));
	if (s == NULL) return 0;
	s->x = double(rand() % 100 - 50);
	s->y = 50.0 * window_height / 512;
	s->radius = double(rand() % 50) / 10;
	s->velocity = 0.0;
	s->melt = 0;
	return s;
}

void drawCircle(double x_in, double y_in, double r)
{
	
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
		drawCircle((*iter)->x, (*iter)->y, (*iter)->radius);
		glEnd();
		if (pause) {
			iter++;
			continue;
		}
		//Snowflake reaches at bottom
		if ((*iter)->y <= -50 * window_height / 512){
			(*iter)->velocity = 0;
			(*iter)->melt += 1;\
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
				(*iter)->velocity += 0.01 - 0.005*(*iter)->radius*(*iter)->radius*(*iter)->velocity;
			}
			(*iter)->y -= (*iter)->velocity;
			(*iter)->x += DIRECTION;
			//after reaching terminal velocity, linearly increases velocity
			if ((*iter)->velocity <= 1.0){
				(*iter)->velocity += 0.03;
			}
			iter++;
		}
	}
	glFlush();
}

/* Display Function */
void display(void)
{
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

	glutSwapBuffers();   // Using double-buffer, swap the buffer to display
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
			DIRECTION = -0.1;
		else if (DIRECTION == 0.1)
			DIRECTION = 0.0;
		break;
	case 'd':   /*   Blow wind to the right   */
	case 'D':
		if (DIRECTION == -0.1)
			DIRECTION = 0;
		else if (DIRECTION == 0)
			DIRECTION = 0.1;
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
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);   // not necessary unless on Unix
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	window_width = 512;
	window_height = 800;
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Snowy");
	init();

	glutReshapeFunc(reshape);       // register respace (anytime window changes)
	glutKeyboardFunc(keyboard);     // register keyboard (anytime keypressed)                                        
	glutDisplayFunc(display);       // register display function
	glutTimerFunc(0, Timer, 0);     // call first Timer, 0 wait, value passed = 0
	glutMainLoop();
	return 0;
}
