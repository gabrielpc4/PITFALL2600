#include "PitfallGame.h"
#include "constants.h"
#include "glut.h"  //Custom glut.h fixed to work with stdlib.h
#include <gl/gl.h>


PitfallGame *pit;

void arrows_keys_func_down(int key, int x, int y)
{
	pit->handleKeyboardInput(key, DOWN);
}

void arrows_keys_func_up(int key, int x, int y)
{
	pit->handleKeyboardInput(key, UP);
}

void keyboard_func(unsigned char c, int x, int y)
{
	pit->handleKeyboardInput(c);
}
Polygon p(Color(RED));
Rect r(Point(50, 50), Point(100, 100));


Sprite s(50, 50);

void timer_func(int data)
{
	pit->run();
	glutTimerFunc(WAIT_TIME, timer_func, data);
	glutPostRedisplay();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear buffers to preset values (applies the color to the background)
	glLoadIdentity();									// Replace the current matrix with the identity matrix (Resets the matrix)		
	pit->drawAll();
	glutSwapBuffers();
}


void reshape_func(int w, int h)
{
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void idle_func()
{
	glutPostRedisplay();
}

/***************************************************************************************
* Function Name: init
* Description: Has to be called before draw anything,
*			   it defines the background color and configures the scale interpretation
****************************************************************************************/
void init()
{
	glClearColor(1.0, 1.0, 1.0, 0);		// Defines the background color (Black)
	glDisable(GL_DEPTH_TEST);			// The depth buffer is not updated if the depth test is disabled.
	glMatrixMode(GL_PROJECTION);		// Applies subsequent matrix operations to the projection matrix stack.
	glLoadIdentity();					// Replace the current matrix with the identity matrix (Resets the matrix)
	gluOrtho2D(0.0, (double)WORLD_WINDOW_WIDTH, 0.0, (double)WORLD_WINDOW_HEIGHT);	// Defines a 2D orthographic projection matrix (Sets the world coordinate window size)
	glMatrixMode(GL_MODELVIEW);			// Applies subsequent matrix operations to the modelview matrix stack.

}

int main(int argc, char* argv[])
{
	pit = new PitfallGame();
	p.push_back(r);
	s.push_back(p);
	glutInit(&argc, argv);							// Initializes the GLUT library.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	// Sets the initial display mode with a single buffered window and color scheme to RGB
	glutInitWindowSize(WORLD_WINDOW_WIDTH * MAGNIFICATION, WORLD_WINDOW_HEIGHT * MAGNIFICATION);// Sets the Display Window size
	glutCreateWindow("Pitfall 2600");				// Creates a top-level window. The name will be provided to the window system as the window's name.
	init();											// Custom function created to define the background color and configures the scale interpretation			
	glutDisplayFunc(display);						// Sets the display callback for the current window.		
	glutReshapeFunc(reshape_func);
	glutSpecialFunc(arrows_keys_func_down);;
	glutSpecialUpFunc(arrows_keys_func_up);
	glutKeyboardFunc(keyboard_func);
	glutTimerFunc(WAIT_TIME, timer_func, 1);

	glutMainLoop();									//  Enters the GLUT event processing loop.
	return 0;
}





