#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>

using namespace std;

typedef struct paleta_de_cores{ //estrutura criada com a finalidade de manter a paleta de cores a ser utilizada na função MidPointCircle
	GLfloat cores[3];
}cor;

cor paleta;

void reshape(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
}

void write_pixel(GLfloat x, GLfloat y, cor paleta){ //funçao que pinta um pixel na tela
	glBegin(GL_POINTS);
	glColor3f(paleta.cores[0],paleta.cores[1],paleta.cores[2]);
	glVertex2i(x,y);
	glEnd();
}

void CirclePoints(int x, int y, cor paleta){ //A função MidPointCircle apenas desenha um quadrante da circunferência, portanto essa função é necessária para achar os outros pontos que completam a cincunferência
	write_pixel( x, y, paleta);
	write_pixel( x, -y, paleta);
	write_pixel(-x, y, paleta);
	write_pixel(-x, -y, paleta);
	write_pixel( y, x, paleta);
	write_pixel( y, -x, paleta);
	write_pixel(-y, x, paleta);
	write_pixel(-y, -x, paleta);
}/*end CirclePoints*/

//Punto medio
void MidPointCircle(int r, cor paleta){
    int x, y;
    float d;
    /*Valores iniciales */
    x = 0;
    y = r;
    d = 5/4 - r;
    CirclePoints(x, y, paleta);
    while (y > x ){
        if (d < 0){
            /* Seleccione E */
            d = d + 2 * x + 3;
            x++;
        }else {
            /* Selecone SE */
            d = d + 2 * (x - y ) + 5;
            x++;
            y--;
        }

        CirclePoints(x, y, paleta);

    }/* end while */
}

void display() {
   //glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
   //glColor3f(1.0f, 0.0f, 0.0f); // Red
   //glLoadIdentity();

   //glBegin(GL_POINTS);
   srand(time(0));
	paleta.cores[0]=(rand() % 255)/100;
	paleta.cores[1]=(rand() % 255)/100;
	paleta.cores[2]=(rand() % 255)/100;
    
    MidPointCircle(200, paleta);
    
   //glEnd();

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