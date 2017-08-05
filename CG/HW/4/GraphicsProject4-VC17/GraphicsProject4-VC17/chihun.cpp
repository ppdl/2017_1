//  Computer Graphics Project 4 Starter Code

#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <list>
#include "SOIL.h"
using namespace std;
typedef enum{
	basic,
	contrastStretch,
	histogramEqualizer,
	gaussianFilter,
	medianFilter_3by3,
	medianFilter_7by7
}VIEW_MODE;
VIEW_MODE view;
/* Flip Image (since OpenGL's origin is left-bottom) */
unsigned char* flipImageY(unsigned char* image, int width, int height, int channels) {
	unsigned char* flipImage = new unsigned char[width * height * channels];
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < channels; k++) {
				flipImage[(i + j * width) * channels + k] = image[(i + (height - 1 - j) * width) * channels + k];
			}
		}
	}
	return flipImage;
}

/* Contrast Stretching */
unsigned char* contrastStretchingGrayscale(unsigned char* image, int width, int height) {
	// Apply contrast stretching to an image
	//
	// Input:
	//      image - grayscale image
	//      width - width of the input image
	//      height - height of the input image
	//
	// Output:
	//      resultImage - an constrast-stretched image
	//

	unsigned char* resultImage = new unsigned char[width * height];
	// your code here...
	int max = -1, min = 257;
	for (int i = 0; i < width*height; i++){
		if (image[i] <= min){
			min = image[i];
		}
		if (image[i] >= max){
			max = image[i];
		}
	}
	//min is 24, max is 245
	for (int i = 0; i < width*height; i++){
		resultImage[i] = 255 * (image[i] - min) / (max - min);
	}
	return resultImage;
}

/* Histogram Equalization */
unsigned char* histogramEqualizationGrayscale(unsigned char* image, int width, int height) {
	// Apply histogram equalization to an image
	//
	// Input:
	//      image - grayscale image
	//      width - width of the input image
	//      height - height of the input image
	//
	// Output:
	//      resultImage - an histogram-equalized image
	//


	unsigned char* resultImage = new unsigned char[width * height];
	// your code here...
	int histogram[256];
	int sum[256];
	for (int i = 0; i < 256; i++){
		histogram[i] = 0;
		sum[i] = 0;
	}

	for (int i = 0; i < width*height; i++){
		histogram[(int)image[i]]++;
	}

	for (int i = 0; i < 256; i++){
		for (int j = 0; j <= i; j++) sum[i] += histogram[j];
	}

	for (int i = 0; i < width*height; i++){
		resultImage[i] = (int)(((double)sum[(int)image[i]] / (double)(width*height)) * 255.0);
	}
	return resultImage;
}

/* Gaussian Filter */
unsigned char* gaussianFilterGrayscale(unsigned char* image, int width, int height) {
	// Apply a gaussian filter to an image
	//
	// Input:
	//      image - grayscale image
	//      width - width of the input image
	//      height - height of the input image
	//
	// Output:
	//      filteredImage - an image filtered with a gaussian filter
	//
	unsigned char* filteredImage = new unsigned char[width * height];
	for (int i = 0; i <= width*height; i++){
		filteredImage[i] = 0;
	}
	// your code here...
	double G[5][5] = { 0 };
	double PI = 3.141592;
	double sigma = 1;
	double sum = 0, sum2 = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			G[i][j] = exp(-((pow(i - 2, 2) + pow(j - 2, 2)) / (2 * pow(sigma, 2)))) / 2 * PI*pow(sigma, 2);
			sum += G[i][j];
		}
	}
	for (int i = 2; i <= height - 3; i++){
		for (int j = 2; j <= width - 3; j++){
			for (int row = 0; row < 5; row++){
				for (int col = 0; col < 5; col++){
					sum2 += (image[width*(i - 2 + row) + (j - 2 + col)] * G[row][col]);
				}
			}
			filteredImage[width*i + j] = (int)(sum2 / sum);
			sum2 = 0;
		}
	}
	return filteredImage;
}
/*
do {
sorted = true;
for (int k = 0; k < 3*3 - 1; k++) {
if (sorting[k] > sorting[k + 1]) {
temp = sorting[k];
sorting[k] = sorting[k + 1];
sorting[k + 1] = temp;
sorted = false;
}
}
} while (!sorted);
*/
/* Median Filter */
unsigned char* medianFilterGrayscale(unsigned char* image, int width, int height) {
	// Apply a median filter to an image
	//
	// Input:
	//      image - grayscale image
	//      width - width of the input image
	//      height - height of the input image
	//
	// Output:
	//      filteredImage - an image filtered with a median filter
	//

	bool flag;
	int sorting[9]; int cnt9 = 0; int temp;
	int sorting2[49]; int cnt49 = 0;
	unsigned char* filteredImage = new unsigned char[width * height];
	for (int i = 0; i < width*height; i++){
		filteredImage[i] = 0;
	}
	// your code here...
	if (view == medianFilter_3by3){

		for (int i = 1; i < height - 1; i++){
			for (int j = 1; j < width - 1; j++){
				for (int row = 0; row < 3; row++){
					for (int col = 0; col < 3; col++){
						sorting[3 * row + col] = image[width*(i - 1 + row) + (j - 1 + col)];
					}
				}
				for (int i = 0; i < 8; i++){
					flag = false;
					for (int j = 0; j < 8 - i; j++){
						if (sorting[j] > sorting[j + 1]){
							flag = true;
							temp = sorting[j];
							sorting[j] = sorting[j + 1];
							sorting[j + 1] = temp;
						}
					}
					if (flag == false) break;
				}
				
				filteredImage[width*i + j] = sorting[4];
			}
		}
	}
	if (view == medianFilter_7by7){
		for (int i = 3; i <= height - 4; i++){
			for (int j = 3; j <= width - 4; j++){
				for (int row = 0; row < 7; row++){
					for (int col = 0; col < 7; col++){
						sorting2[7 * row + col] = image[width*(i - 3 + row) + (j - 3 + col)];
					}
				}
				for (int i = 0; i < 49; i++){
					flag = false;
					for (int j = 0; j < 49 - i; j++){
						if (sorting2[j] > sorting2[j + 1]){
							flag = true;
							temp = sorting2[j];
							sorting2[j] = sorting2[j + 1];
							sorting2[j + 1] = temp;
						}
					}
					if (flag == false) break;
				}
				filteredImage[width*i + j] = sorting2[24];
			}
		}
	}
	return filteredImage;
}

/* Display Function
*
* You may edit this function to solve multiple tasks.
*
*/
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	int width, height;
	int numChannels = 1; // 1 for grayscale, 3 for RGB color
	// Load Image (CHECK THE IMAGE'S PATH!)
	unsigned char* image = SOIL_load_image("Lenna.png" /* Check image path! */, &width, &height, 0, numChannels);
	if (image != NULL) {
		// Flip image (due to the upside-down property of OpenGL)
		unsigned char* flippedImage = flipImageY(image, width, height, numChannels);

		SOIL_free_image_data(image); // free memory

		// Image Processing Operation
		// Set this 'finalImage' variable to the resulting image of operation
		//unsigned char* finalImage = flippedImage; // Edit this line, e.g. unsigned char* finalImage = GaussianFilterGrayscale(flippedImage, width, height);
		//unsigned char* finalImage = contrastStretchingGrayscale(flippedImage, width, height);
		unsigned char* finalImage;
		switch (view){
		case basic:
			finalImage = flippedImage;
			break;
		case contrastStretch:
			finalImage = contrastStretchingGrayscale(flippedImage, width, height);
			break;
		case histogramEqualizer:
			finalImage = histogramEqualizationGrayscale(flippedImage, width, height);
			break;
		case gaussianFilter:
			finalImage = gaussianFilterGrayscale(flippedImage, width, height);
			break;
		case medianFilter_3by3:
			finalImage = medianFilterGrayscale(flippedImage, width, height);
			break;
		case medianFilter_7by7:
			finalImage = medianFilterGrayscale(flippedImage, width, height);
			break;
		default:
			finalImage = flippedImage;
			break;
		}

		// Draw final image on screen
		glDrawPixels(width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, finalImage /* manipulated image to display */);
		// Save the result
		int saveResult = SOIL_save_image("output.bmp",
			SOIL_SAVE_TYPE_BMP,
			width,
			height,
			numChannels,
			flipImageY(finalImage, width, height, numChannels)
			); // re-flip image before saving
		if (saveResult == 0) {
			std::cout << "Image save failed" << std::endl;
		}
		SOIL_free_image_data(flippedImage); // free memory
	}
	else {
		// CHECK THE IMAGE'S PATH!
		std::cout << "Image read failed" << std::endl;
	}
	glutSwapBuffers();
}

/****************************************************************/
/* Common OpenGL functions to open a window                     */
/****************************************************************/
void init(void)
{
	glClearColor(0, 0, 0, 1.0);
	view = basic;
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);       // maps to window 0,0, width * height
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);    // set model transformation
	glLoadIdentity();
}

/* Setup Keyboard */
void keyboard(unsigned char key, int x, int y)
{
	printf("%d\n", key);
	switch (key) {
	case 27:  /*  Escape Key  */
		exit(0);
		break;
	case 49: // case 1
		view = basic;
		glutPostRedisplay();
		break;
	case 50: // case 2
		view = contrastStretch;
		glutPostRedisplay();
		break;
	case 51: // case 3
		view = histogramEqualizer;
		glutPostRedisplay();
		break;
	case 52: // case 4
		view = gaussianFilter;
		glutPostRedisplay();
		break;
	case 53: // case 5
		view = medianFilter_3by3;
		glutPostRedisplay();
		break;
	case 54: // case 6
		view = medianFilter_7by7;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

/* Idle call back */
void idle()
{
	// We don't need to constantly update the screen; just show an static image
	//glutPostRedisplay();
}

/*  Main Loop
*  Open window with initial window size, title bar,
*  RGB display mode, and handle input events.
*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);   // not necessary unless on Unix
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(512, 512);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);       // register respace (anytime window changes)
	glutKeyboardFunc(keyboard);     // register keyboard (anytime keypressed)                                        
	glutDisplayFunc(display);       // register display function
	glutIdleFunc(idle);             // reister idle function
	glutMainLoop();
	return 0;
}