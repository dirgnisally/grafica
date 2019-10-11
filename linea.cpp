#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>

using namespace std;

void reshape(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
}
//Incremental
void line3d(int x1, int y1, int x2, int y2){
    int x, y;
    float a;
    //int valor;
    a=static_cast<float>(y2-y1)/static_cast<float>((x2-x1));
    for (x=x1;x<=x2;x++){
        y = static_cast<int>(y1 + a*(x - x1));
        glVertex3f(x, y, 0.0f); //write_pixel(x, y, color);
    }
}
//Incremental
void line(int x1, int y1, int x2, int y2){
    int x, y;
    float a;
    //int valor;
    a=static_cast<float>(y2-y1)/static_cast<float>((x2-x1));
    for (x=x1;x<=x2;x++){
        y = static_cast<int>(y1 + a*(x - x1));
        glVertex2f(x, y); //write_pixel(x, y, color);
    }
}
//Punto medio
void lineM(int x1, int y1, int x2, int y2){
    GLfloat dx, dy, incE, incNE, d, x, y;
    dx = x2 - x1;
        dy = y2 - y1;
        d = 2 * dy-dx;
        incE = 2 * dy;
        incNE = 2 * (dy-dx);
        x=x1;
        y=y1;
        glVertex2f(x,y);
        while(x<x2){
            if(d<=0){
                d = d + incE;
                x++;
        }else{

            d = d + incNE;
            x++;
            y++;
        }
        glVertex2f(x,y);
        }
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
   glColor3f(1.0f, 0.0f, 0.0f); // Red
   glLoadIdentity();

   glBegin(GL_POINTS);
    //line(100, 150, 300, 250); //line(x1, y1, x2, y2) Incremental
    line3d(100, 150, 300, 250);
    //lineM(100, 150, 300, 250); //lineM(x1, y1, x2, y2) Punto medio
   glEnd();

   glFlush();  // Render now
}

void Init(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
   glutInit(&argc, argv);                 // Initialize GLUT
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutInitWindowSize(400, 400);   // Set the window's initial width & height
   glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
   Init();
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutReshapeFunc(reshape);
   glutMainLoop();           // Enter the event-processing loop
   return 0;
}