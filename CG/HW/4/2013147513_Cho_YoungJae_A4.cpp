//  Computer Graphics Project 4 Starter Code

#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include "SOIL.h"
using namespace std;


typedef enum{
	Grayscale,
	ContrastStretching,
	HistogramEqualization,
	GaussianFilter,
	MedianFilter3,
	MedianFilter7
}MODE;

MODE m = Grayscale;

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
	// histogram array
	int histogram[256] = { 0, };
	// transform function
	int transform[256] = { 0, };
	// lowest & highest grayscale value
	int lowthresh, highthresh;
	// obtaining a histogram
	for (int i = 0; i < width*height; i++){
		histogram[(int)image[i]]++;
	}
	// obtaining lowthreshold, highthreshold
	for (int i = 0; i < 256; i++){
		if (histogram[i]){
			lowthresh = i;
			break;
		}
	}
	for (int i = 255; i > 0; i--){
		if (histogram[i]){
			highthresh = i;
			break;
		}
	}

	// initializing by 0 under lowthreshold
	// index:  [0] [1] [2]        [lowthresh]
	//          |   |   |          |
	// array: | 0 | 0 | 0 |..| 0 | 0 |...
	for (int i = 0; i < lowthresh; i++)
		transform[i] = 0;	
	// initializing by 255 over highthreshold
	// index:     [highthresh]                [254] [255] 
	//              |		                    |     |
	// array:  ...| 254 | 255 | 255 | 255 |...| 255 | 255 |
	for (int i = 255; i > highthresh; i--)
		transform[i] = 255;
	// constantly increases value between lowthreshold and highthreshold
	// index:    [lowthresh]                                  [highthresh]
	//              |  <---------gradually increasing ------->   |
	// array:  ...| 0 | 1 | 2 | gra | dual | incr | ease | ... | 254 | 255 | ... | 255 | 255 |
	for (int i = lowthresh; i <= highthresh; i++)
		transform[i] = (int)((255.0 / (highthresh - lowthresh)) * (i - lowthresh));

	//transforming
	for (int i = 0; i < width*height; i++){
		resultImage[i] = transform[image[i]];
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
	float histogram[256] = { 0, };
	// transform function
	float transform[256] = { 0, };
	// obtaining a histogram
	for (int i = 0; i < width*height; i++){
		histogram[(int)image[i]]++;
	}
	// normalizing a histogram
	for (int i = 0; i < 255; i++)
		histogram[i] /= (width*height);
	// obtaining a transform function
	for (int i = 1; i < 255; i++){
		transform[i] = transform[i - 1] + histogram[i];
	}
	// transform function has value between 0.0 ~ 1.0
	// scaling it by multiplying 255 to get corresponding grayscale
	for (int i = 0; i < 255; i++)
		transform[i] *= 255;
	
	// transforming
	for (int i = 0; i < width*height; i++){
		resultImage[i] = (int)transform[image[i]];
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
	// your code here...
	float maskGaussian[5][5] =  { { 1, 4, 7, 4, 1 },
								{ 4, 16, 26, 16, 4 },
								{ 7, 26, 41, 26, 7 },
								{ 4, 16, 26, 16, 4 },
								{ 1, 4, 7, 4, 1 } };
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			maskGaussian[i][j] /= 273.0;

	for (int i = 0; i < width*height; i++)
		filteredImage[i] = 0;

	for (int i = 2; i < height - 2; i++)
		for (int j = 2; j < width - 2; j++){
			for (int x = -2; x < 3; x++)
				for (int y = -2; y < 3; y++)
					filteredImage[height*i + j] += image[height*(i + x) + j + y]*maskGaussian[x+2][y+2];
		}
	return filteredImage;
}

/* Median Filter */
int compare(const void *first, const void *second)
{
	if (*(int*)first > *(int*)second)
		return 1;
	else if (*(int*)first < *(int*)second)
		return -1;
	else
		return 0;
}

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

	unsigned char* filteredImage = new unsigned char[width * height];
	// your code here...
	switch (m){
	case MedianFilter3:
		// initialize filteredImage
		for (int i = 0; i < width*height; i++)
			filteredImage[i] = 0;

		char filter1[9];
		for (int i = 1; i < height - 1; i++)
			for (int j = 1; j < width - 1; j++){
				// obtain a filter
				for (int x = 0; x < 3; x++)
					for (int y = 0; y < 3; y++){
						filter1[x*3 + y] = image[height*(i + x - 1) + j + y - 1];
					}
				// sort the filter
				qsort(filter1, sizeof(filter1), sizeof(char), compare);
				filteredImage[height*i + j] = filter1[4];
			}
		break;
	case MedianFilter7:
		// initialize filteredImage
		for (int i = 0; i < width*height; i++)
			filteredImage[i] = 0;

		char filter2[49];
		for (int i = 3; i < height - 3; i++)
			for (int j = 3; j < width - 3; j++){
				// obtain a filter
				for (int x = 0; x < 7; x++)
					for (int y = 0; y < 7; y++){
						filter2[x * 7 + y] = image[height*(i + x - 3) + j + y - 3];
					}
				// sort the filter
				qsort(filter2, sizeof(filter2), sizeof(char), compare);
				filteredImage[height*i + j] = filter2[4];
			}
		break;
	default:
		printf("MedianFilter Error!\n");
		break;
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
		unsigned char* finalImage;
		const char* ofile;
		switch (m){
		case Grayscale:
			finalImage = flippedImage;
			ofile = "output.bmp";
			break;
		case ContrastStretching:
			finalImage = contrastStretchingGrayscale(flippedImage, width, height);
			ofile = "contrastStretch.bmp";
			break;
		case HistogramEqualization:
			finalImage = histogramEqualizationGrayscale(flippedImage, width, height);
			ofile = "histogramEqualization.bmp";
			break;
		case GaussianFilter:
			finalImage = gaussianFilterGrayscale(flippedImage, width, height);
			ofile = "gaussianFilter.bmp";
			break;
		case MedianFilter3:
			finalImage = medianFilterGrayscale(flippedImage, width, height);
			ofile = "medianFilter_3X3.bmp";
			break;
		case MedianFilter7:
			finalImage = medianFilterGrayscale(flippedImage, width, height);
			ofile = "medianFilter_7X7.bmp";
			break;
		}

		//unsigned char* finalImage = contrastStretchingGrayscale(flippedImage, width, height); // Edit this line, e.g. unsigned char* finalImage = GaussianFilterGrayscale(flippedImage, width, height);


												  // Draw final image on screen
		glDrawPixels(width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, finalImage /* manipulated image to display */);
		// Save the result
		int saveResult = SOIL_save_image(ofile,
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
	switch (key) {
	case 27:  /*  Escape Key  */
		exit(0);
		break;
	case '1':
		m = Grayscale;
		display();
		break;
	case '2':
		m = ContrastStretching;
		display();
		break;
	case '3':
		m = HistogramEqualization;
		display();
		break;
	case '4':
		m = GaussianFilter;
		display();
		break;
	case '5':
		m = MedianFilter3;
		display();
		break;
	case '6':
		m = MedianFilter7;
		display();
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
	printf("[1]: Default Grayscale\n");
	printf("[2]: Contrast Stretching\n");
	printf("[3]: Histogram Equalization\n");
	printf("[4]: Gaussian Filter\n");
	printf("[5]: 3x3 Median Filter\n");
	printf("[6]: 7x7 Median Filter\n");
	init();
	glutReshapeFunc(reshape);       // register respace (anytime window changes)
	glutKeyboardFunc(keyboard);     // register keyboard (anytime keypressed)                                        
	glutDisplayFunc(display);       // register display function
	//glutIdleFunc(idle);             // reister idle function
	glutMainLoop();
	return 0;
}
