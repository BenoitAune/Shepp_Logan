//http://www.ntu.edu.sg/home/ehchua/programming/opengl/CG_examples.html

/*
 * OGL01Shape3D.cpp: 3D Shapes
 */
#include <math.h>
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

/* Global variables */
char title[] = "3D Shapes";

double rotx =0;
double roty=0;
double rotz=0;
double a=1;
/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void Rafraichir(void)
{
  glClear(GL_COLOR_BUFFER_BIT);	// Effacer la surface graphique

}
/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
   glEnable(GL_BLEND) ;
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                 // Reset the model-view matrix
   gluLookAt(3,3,3,0,0,0,0,1,0);

   glRotated(rotx *180/3.14,1,0,0);
   glRotated(roty *180/3.14,0,1,0);
   glRotated(rotz *180/3.14,0,0,1);
   glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles

     // Front
     glColor4f(1.0f, 0.0f, 0.0f,a*1.0f);     // Red
     glVertex3f( 0.0f, 0.0f, 1.0f);
     glVertex3f(2*sqrt(2)/3, 0.0f, -1/3);
     glVertex3f(-sqrt(2)/3, -sqrt(2)/sqrt(3), -1/3);

     // Right
     glColor4f(0.0f, 0.0f, 1.0f,a*1.0f);     // Blue
     glVertex3f(-sqrt(2)/3, sqrt(2)/sqrt(3), -1/3);
     glVertex3f(2*sqrt(2)/3, 0.0f, -1/3);
     glVertex3f( 0.0f, 0.0f, 1.0f);

     // Left
     glColor4f(0.0f,1.0f,0.0f,a*1.0f);       // Green
     glVertex3f(-sqrt(2)/3, -sqrt(2)/sqrt(3), -1/3);
     glVertex3f(2*sqrt(2)/3, 0.0f, -1/3);
     glVertex3f(-sqrt(2)/3, sqrt(2)/sqrt(3), -1/3);

     // Bottom
     glColor4f(1.0f, 1.0f, 1.0f,a*1.0f);     // White
     glVertex3f(-sqrt(2)/3, -sqrt(2)/sqrt(3), -1/3);
     glVertex3f(-sqrt(2)/3, sqrt(2)/sqrt(3), -1/3);
     glVertex3f( 0.0f, 0.0f, 1.0f);

   glEnd();   // Done drawing the pyramid

   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

// Action sur frappe d'une touche au clavier
void Clavier(unsigned char key, int x, int y)
{
  switch(key) {
    case 'm' : exit(0); // m => « quitter »

    case 'q' : rotx=rotx- 0.05; break;
    case 'd' : rotx=rotx+ 0.05; break;
    case 'z' : roty=roty+ 0.05; break;
    case 's' : roty=roty- 0.05; break;

    case 'a' : rotz=rotz- 0.05; break;
    case 'e' : rotz=rotz+ 0.05; break;
    case 'r' : a=a+ 0.01; if (a>1) a=1; break;
    case 'f' : a=a- 0.01; if (a<0) a=0; break;
  }
  display();


}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();                        // Our own OpenGL initialization
   glutKeyboardFunc(Clavier); 		// Callback du clavier
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
