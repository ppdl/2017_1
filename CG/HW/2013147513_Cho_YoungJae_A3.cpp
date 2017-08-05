#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAXOBJ			50
#define SHAPEVARIETY	6
#define PI				3.141592
#define BULLETSPEED		10
#define	PANSPEED		0.05
#define OBJDENSITY		5
	
enum VMODE{ FIRST_PERSON_VIEW, BIRD_VIEW } VIEWMODE;
enum SMODE{ NORMAL_MODE, SELECTION_MODE } SELECTMODE;
enum LMODE{ DAY_NIGHT, CUSTOM } LIGHTMODE;
typedef enum{ SPHERE, TEAPOT, TORUS, CUBE, CONE, BULLET } SHAPE;

GLfloat custom_ambient[] = { 0.2, 0.2, 0.2, 0.8 };
GLfloat custom_diffuse[] = { 0.5, 0.5, 0.5, 0.8 };
GLfloat custom_specular[] = { 0.8, 0.8, 0.8, 1 };
GLfloat custom_shinny[] = { 8 };
GLfloat zero[] = { 0, 0, 0, 1 };

GLfloat light_init_pos[] = { 0, 0, 0, 1 };
GLfloat moon_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat moon_diffuse[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat moon_specular[] = { 0.12, 0.12, 0.12, 1 };

int timelapse = 0;
int tx, ty;

struct coord{
	float x;
	float y;
	float z;
};

struct viewer{
	coord position;
	coord direction;
	float theta;
} v;

struct STUFF{
	bool noStuff;
	SHAPE s;
	coord position;
	//coord direction;
	float speed;
	float r, g, b;
	float theta;
	bool isSelected;
};

STUFF obj[MAXOBJ];
STUFF customLight;
STUFF bullet[5];

class GUN{
public:
	bool magazine[5];

	GUN(){
		for (int i = 0; i < 5; i++){
			bullet[i].s = BULLET;
			bullet[i].noStuff = true;
			magazine[i] = true;
		}
	}
	void shoot()
	{
		for (int i = 0; i < 5; i++){
			if (magazine[i]){
				magazine[i] = false;
				bullet[i].noStuff = false;
				bullet[i].position.x = v.position.x;
				bullet[i].position.y = v.position.y;
				bullet[i].position.z = v.position.z;
				bullet[i].theta = v.theta;
				break;
			}
		}
	}
} gun;
void createCylinder(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius, GLfloat h)
{
//reference: http://evir.tistory.com/entry/OpenGL%EA%B0%84%EB%8B%A8%ED%95%9C-%EC%9B%90%EA%B8%B0%EB%91%A5-%EB%A7%8C%EB%93%9C%EB%8A%94-%ED%95%A8%EC%88%98
// centerx, centery, centerz: center coordinate of base
// radius: radius of base
//      h: cylinder's height
	GLfloat x, y, angle;

	glBegin(GL_TRIANGLE_FAN); 
	glNormal3f(0.0f, 0.0f, -1.0f);
	glColor3ub(139, 69, 19);
	glVertex3f(centerx, centery, centerz);

		for (angle = 0.0f; angle < (2.0f*PI); angle += (PI / 8.0f))
		{
			x = centerx + radius*sin(angle);
			y = centery + radius*cos(angle);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(x, y, centerz);
		}
	glEnd();

	glBegin(GL_QUAD_STRIP); 
	for (angle = 0.0f; angle < (2.0f*PI); angle += (PI / 8.0f))
	{
		x = centerx + radius*sin(angle);
		y = centery + radius*cos(angle);
		glNormal3f(sin(angle), cos(angle), 0.0f);
		glVertex3f(x, y, centerz);
		glVertex3f(x, y, centerz + h);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN); 
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(centerx, centery, centerz + h);
	for (angle = (2.0f*PI); angle > 0.0f; angle -= (PI / 8.0f))
	{
		x = centerx + radius*sin(angle);
		y = centery + radius*cos(angle);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(x, y, centerz + h);
	}
	glEnd();
}
void drawBullet()
{
	createCylinder(0, 0, 0, 4, 1.6);
	createCylinder(0, 0, 1.6, 3.2, 2.4);
	createCylinder(0, 0, 4, 4, 20);
	glPushMatrix();
	glTranslatef(0, 0, 24);
	glutSolidCone(4, 16, 30, 30);
	glPopMatrix();

}
void generateObj()
{
	srand(time(NULL));
	for (int i = 0; i < MAXOBJ; i++){
		obj[i].s = static_cast<SHAPE>(rand() % SHAPEVARIETY);
		obj[i].r = (float)(rand() % 1001) / 1000.0;
		obj[i].g = (float)(rand() % 1001) / 1000.0;
		obj[i].b = (float)(rand() % 1001) / 1000.0;
		obj[i].theta = 0.0;
		obj[i].position.x = (rand() % 1021) - 510;
		obj[i].position.z = (rand() % 1021) - 510;
		if (rand() % (1 + OBJDENSITY) == 0)
			obj[i].noStuff = true;
		else obj[i].noStuff = false;
		obj[i].speed = rand() % 10;
		obj[i].isSelected = false;
	}
}
double getDist(int x1, int y1, int x2, int y2)
{
	//approximate distance
	return abs(x1 - x2) + abs(y1 - y2);
}
void trajectory()
{
	GLfloat bullet_ambient[] = { 0.8, 0.8, 0.0, 1.0 };
	GLfloat bullet_specular[] = { 0.8, 0.8, 0.8, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, bullet_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, bullet_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, zero);
	glMaterialfv(GL_FRONT, GL_SHININESS, custom_shinny);
	for (int i = 0; i < 5; i++){
		if (bullet[i].noStuff)continue;
		bullet[i].position.x += cos(bullet[i].theta) * BULLETSPEED;
		bullet[i].position.z += sin(bullet[i].theta) * BULLETSPEED;
		//bullet goes out of bound. erase the bullet
		if (bullet[i].position.x > 512 || bullet[i].position.x < -512 || bullet[i].position.z > 512 || bullet[i].position.z < -512){
			bullet[i].noStuff = true;
			gun.magazine[i] = true;
		}
	}
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < MAXOBJ; j++){
			if (obj[j].noStuff) continue;
			double d = getDist(bullet[i].position.x, bullet[i].position.z, obj[j].position.x, obj[j].position.z);
			//bullet collides with object. erase the bullet and the object
			if (d < 20){
				bullet[i].noStuff = true;
				gun.magazine[i] = true;
				obj[j].noStuff = true;
			}
		}
	}
	//draw flying bullets
	for (int i = 0; i < 5; i++){
		if (bullet[i].noStuff) continue;
		glPushMatrix();
		glTranslatef(bullet[i].position.x, bullet[i].position.y, bullet[i].position.z);
		glRotatef(-bullet[i].theta *57.296 + 90, 0.0, 1.0, 0.0);
		glScalef(0.3, 0.3, 0.3);
		drawBullet();
		glPopMatrix();
	}
}

void lighting(){

	if (LIGHTMODE == DAY_NIGHT){
		glDisable(GL_LIGHT2);
		if (timelapse < 180){
			glDisable(GL_LIGHT1);
			glEnable(GL_LIGHT0);
			glDisable(GL_LIGHTING);
			glColor3f(1, 1, 0.8);
			glPushMatrix();
			glRotatef(timelapse, 1, 0, 0);
			glTranslatef(0.0, 0.0, -540.0);
			glutSolidSphere(30, 30, 30);
			glPopMatrix();
			glEnable(GL_LIGHTING);

			GLfloat ambient = -(0.6 / 90.0)*abs(timelapse - 90) + 0.7;
			GLfloat diffuse = -(0.38 / 90.0)*abs(timelapse - 90) + 0.5;
			GLfloat specular = -(0.68 / 90.0)*abs(timelapse - 90) + 0.8;
			GLfloat sun_ambient[] = { ambient, ambient, ambient, 1.0 };
			GLfloat sun_diffuse[] = { diffuse, diffuse, diffuse, 1.0 };
			GLfloat sun_specular[] = { specular, specular, specular, 1.0 };

			glPushMatrix();
			glRotatef(timelapse, 1, 0, 0);
			glTranslatef(0.0, 0.0, -540.0);
			glLightfv(GL_LIGHT0, GL_AMBIENT, sun_ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_diffuse);
			glLightfv(GL_LIGHT0, GL_SPECULAR, sun_specular);
			glLightfv(GL_LIGHT0, GL_POSITION, light_init_pos);
			glPopMatrix();
		}
		else{
			glDisable(GL_LIGHT0);
			glEnable(GL_LIGHT1);

			glDisable(GL_LIGHTING);
			glColor3f(0.5, 0.5, 0.05);
			glPushMatrix();
			glRotatef(timelapse - 180, 1, 0, 0);
			glTranslatef(0.0, 0.0, -540.0);
			glutSolidSphere(15, 30, 30);
			glPopMatrix();
			glEnable(GL_LIGHTING);

			glPushMatrix();
			glRotatef(timelapse - 180, 1, 0, 0);
			glTranslatef(0.0, 0.0, -540.0);
			glLightfv(GL_LIGHT1, GL_AMBIENT, moon_ambient);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, moon_diffuse);
			glLightfv(GL_LIGHT1, GL_SPECULAR, moon_specular);
			glLightfv(GL_LIGHT1, GL_POSITION, light_init_pos);
			glPopMatrix();
		}
		timelapse++;
		if (timelapse > 360) timelapse = 0;
	}

	else if (LIGHTMODE == CUSTOM){
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT2);

		glDisable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(customLight.position.x, 190, customLight.position.z);
		glutSolidSphere(15, 30, 30);
		glPopMatrix();
		glEnable(GL_LIGHTING);

		glPushMatrix();
		glTranslatef(customLight.position.x, 190, customLight.position.z);
		glLightfv(GL_LIGHT2, GL_AMBIENT, custom_ambient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, custom_diffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, custom_specular);
		glLightfv(GL_LIGHT2, GL_POSITION, light_init_pos);
		glPopMatrix();
	}
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (VIEWMODE == FIRST_PERSON_VIEW){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0, 1.0, 3.0, 800);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(v.position.x, v.position.y, v.position.z,
			v.position.x + v.direction.x, v.position.y + v.direction.y, v.position.z + v.direction.z,
			0, 1, 0);
		
		//draw aim
		glPushMatrix();		
		glTranslatef(5 * v.direction.x, v.direction.y, 5 * v.direction.z);
		glTranslatef(v.position.x, v.position.y, v.position.z);
		glDisable(GL_LIGHTING);
		glColor3f(1, 0, 0);
		glutSolidSphere(0.05, 30, 30);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
	else if (VIEWMODE == BIRD_VIEW){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-512, 512, -512, 512, -512, 512);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 100, 0, 0, 0, 0, 0, 0, 1);
	}

	glDisable(GL_LIGHTING);
	if (SELECTMODE == SELECTION_MODE)
		glColor3f(0.1, 0.1, 0.1);
	else
		glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_POLYGON);
	glVertex3f(500.0, 0.0, 500.0);
	glVertex3f(500.0, 0.0, -500.0);
	glVertex3f(-500.0, 0.0, -500.0);
	glVertex3f(-500.0, 0.0, 500.0);
	glEnd();
	glEnable(GL_LIGHTING);

	lighting();

	for (int i = 0; i < MAXOBJ; i++){
		if (obj[i].noStuff) continue;

		glColor3f(obj[i].r, obj[i].g, obj[i].b);
		GLfloat obj_ambient[] = { obj[i].r, obj[i].g, obj[i].b, 0.6 };
		GLfloat obj_specular[] = { obj[i].r*1.3, obj[i].g*1.3, obj[i].b*1.3, 1.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, obj_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, obj_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, zero);
		glMaterialfv(GL_FRONT, GL_SHININESS, custom_shinny);
		glPushMatrix();
		switch (obj[i].s){
		case SPHERE:
			glTranslatef(obj[i].position.x, 15, obj[i].position.z);
			glutSolidSphere(15, 30, 30);
			glPopMatrix();
			break;
		case TEAPOT:
			glTranslatef(obj[i].position.x, 10, obj[i].position.z);
			glRotatef(obj[i].theta, 0, 1, 0);
			obj[i].theta += obj[i].speed;
			if (obj[i].theta > 360) obj[i].theta = 0;
			glutSolidTeapot(15);
			glPopMatrix();
			break;
		case TORUS:
			glTranslatef(obj[i].position.x, 30, obj[i].position.z);
			glRotatef(obj[i].theta, 0, 1, 0);
			obj[i].theta += obj[i].speed;
			if (obj[i].theta > 360) obj[i].theta = 0;
			glRotatef(90, 0.0, 1.0, 0.0);
			glutSolidTorus(7.5, 20.0, 40, 40);
			glPopMatrix();
			break;
		case CUBE:
			glTranslatef(obj[i].position.x, 15, obj[i].position.z);
			glRotatef(obj[i].theta, 0, 1, 0);
			obj[i].theta += obj[i].speed;
			if (obj[i].theta > 360) obj[i].theta = 0;
			glutSolidCube(30);
			glPopMatrix();
			break;
		case CONE:
			glTranslatef(obj[i].position.x, 0, obj[i].position.z);
			glRotatef(-90, 1.0, 0.0, 0.0);
			glutSolidCone(15, 40, 20, 20);
			glPopMatrix();
			break;
		case BULLET:
			glTranslatef(obj[i].position.x, 23, obj[i].position.z);
			glRotatef(obj[i].theta, 0, 1, 0);
			obj[i].theta += obj[i].speed;
			if (obj[i].theta > 360) obj[i].theta = 0;
			glRotatef(45, 0.0, 1.0, 1.0);
			glTranslatef(0, -20, 0);
			glRotatef(-90, 1.0, 0.0, 0.0);
			drawBullet();
			glPopMatrix();
			break;
		default:
			printf("Not permitted shape!\n");
			exit(0);
			break;
		}
	}

	if (VIEWMODE == BIRD_VIEW){
		glPushMatrix();
		glTranslatef(v.position.x, v.position.y, v.position.z);
		glRotatef(-v.theta*57.296, 0, 1, 0);
		glutSolidTeapot(15);
		glPopMatrix();
	}
	trajectory();

	glutSwapBuffers();
	
}

void idle()
{
	glutPostRedisplay();
}


void mousePress(GLint button, GLint state, GLint inx, GLint iny)
{
	if (SELECTMODE != SELECTION_MODE){
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			gun.shoot();
		}
	}
}

void mousePassiveMotion(int inx, int iny)
{
	int x = (inx - 256)*(-2);
	int z = (256 - iny) * 2;
	if (SELECTMODE != SELECTION_MODE){
		if (tx - x > 0){
			v.theta += PANSPEED;
			v.direction.x = cos(v.theta);
			v.direction.z = sin(v.theta);
		}
		else if(tx -x < 0) {
			v.theta -= PANSPEED;
			v.direction.x = cos(v.theta);
			v.direction.z = sin(v.theta);
		}
		tx = x;
	}
	else if (VIEWMODE == BIRD_VIEW && SELECTMODE == SELECTION_MODE){
		int d;
		for (int i = 0; i < MAXOBJ; i++){
			if (obj[i].noStuff) continue;
			d = getDist(x, z, obj[i].position.x, obj[i].position.z);
			if (d < 20){
				obj[i].isSelected = true;
			}
			else
				obj[i].isSelected = false;
		}
		d = getDist(x, z, customLight.position.x, customLight.position.z);
		if (d < 20)
			customLight.isSelected = true;
		else
			customLight.isSelected = false;
	}
}
void mouseMotion(int inx, int iny)
{
	int x = (inx - 256)*(-2);
	int z = (256 - iny) * 2;
	if (SELECTMODE == SELECTION_MODE){
		for (int i = 0; i < MAXOBJ; i++){
			if (obj[i].isSelected){
				obj[i].position.x = x;
				obj[i].position.z = z;
			}
		}
		if (customLight.isSelected){
			customLight.position.x = x;
			customLight.position.z = z;
		}
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:  /*  Escape Key  */
		exit(0);
		break;
	case ' ':
		if (VIEWMODE == FIRST_PERSON_VIEW)
		{
			VIEWMODE = BIRD_VIEW;
		}
		else
		{
			VIEWMODE = FIRST_PERSON_VIEW;
		}
		break;
	case 'r':
	case 'R':
		generateObj();
		break;
	case 'l':
	case 'L':
		if (LIGHTMODE == DAY_NIGHT)
			LIGHTMODE = CUSTOM;
		else
			LIGHTMODE = DAY_NIGHT;
		break;
	case '1':
		if (SELECTMODE == NORMAL_MODE)
			SELECTMODE = SELECTION_MODE;
		else
			SELECTMODE = NORMAL_MODE;
	case 'w':
	case 'W':
		v.position.x += v.direction.x * 3;
		v.position.z += v.direction.z * 3;
		break;
	case 's':
	case 'S':
		v.position.x -= v.direction.x * 3;
		v.position.z -= v.direction.z * 3;
		break;
	case 'a':
	case 'A':
		v.position.x += v.direction.z * 3;
		v.position.z -= v.direction.x * 3;
		break;
	case 'd':
	case 'D':
		v.position.x -= v.direction.z * 3;
		v.position.z += v.direction.x * 3;
		break;
	}
}

void init(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	VIEWMODE = FIRST_PERSON_VIEW;
	SELECTMODE = NORMAL_MODE;
	LIGHTMODE = CUSTOM;
	v.position.x = 0.0;
	v.position.y = 5.0;
	v.position.z = 0.0;
	v.direction.x = 0.0;
	v.direction.y = 0.0;
	v.direction.z = -1.0;
	v.theta = 0.07;
	generateObj();

	customLight.noStuff = false;
	customLight.position.x = 0.0;
	customLight.position.y = 190;
	customLight.position.z = 0.0;
	customLight.s = SPHERE;
	customLight.r = 0.8;
	customLight.g = 0.8;
	customLight.b = 0.0;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("3d");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mousePress);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mousePassiveMotion);
	glutIdleFunc(idle);
	printf("* [Space]:\n");
	printf("   toggle first-person view, bird-view mode\n");
	printf("   avatar is at center. Teapot's spout is viewing direction\n");
	printf("* [1]:\n");
	printf("   Convert to select mode. ground becomes dark\n");
	printf("* [R]:\n");
	printf("   Regenerate objects\n");
	printf("* [W, A, S, D]:\n");
	printf("   Move viewer\n");
	printf("* [Left Click and Drag in Selection mode]:\n");
	printf("   You can move light source as well as objects\n");
	printf("   (In bird-view mode, white circle at the center is light source)\n");
	printf("* [L]:\n");
	printf("   Toggle customLight mode and day-night mode\n");
	printf("   In day-night mode, sun and moon rise and set\n");
	printf("* [Left Click]:\n");
	printf("   When not in selection mode, fires bullet\n");
	printf("   Bullets dissaper when they collide with objects or go outside of window\n");
	printf("* [Mouse motion]:\n");
	printf("   Move view\n");
	glutMainLoop();

	return 0;
}