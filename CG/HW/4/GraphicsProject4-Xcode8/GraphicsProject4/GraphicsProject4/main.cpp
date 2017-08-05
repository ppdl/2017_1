//  Computer Graphics Project 4 Starter Code

#include <iostream>
#include <GLUT/glut.h>
#include "SOIL.h"

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
    
    return filteredImage;
}

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
    
    unsigned char* filteredImage = new unsigned char[width * height];
    // your code here...
    
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
        unsigned char* finalImage = flippedImage; // Edit this line, e.g. unsigned char* finalImage = GaussianFilterGrayscale(flippedImage, width, height);
        
        
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
