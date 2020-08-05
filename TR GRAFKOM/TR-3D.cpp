#include <windows.h>  
#include <GL/glut.h>

bool depan = true;

GLuint texid;
GLuint texwidth = 2;
GLuint texheight = 2;
GLubyte texData[16] =
{
	0xFF,0x00,0x00,0xFF, // red 
	0x00,0xFF,0x00,0xFF, // rgreen
	0x00,0x00,0xFF,0xFF, // blue
	0xFF,0xFF,0xFF,0xFF  // white 
};

void InitTexture()
{
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		4,
		texwidth,
		texheight,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		texData
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClearDepth(1.0f);                  
	glEnable(GL_DEPTH_TEST);   
	glDepthFunc(GL_LEQUAL);    
	glShadeModel(GL_SMOOTH);   
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
	InitTexture();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads

	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	if (depan) {
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	}

	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);


	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);


	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glutSwapBuffers();  
}

void reshape(GLsizei width, GLsizei height) { 
	if (height == 0) height = 1;              
	GLfloat aspect = (GLfloat)width / (GLfloat)height;


	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();             
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		//gerak ke kiri
	case 'b':
	case 'B':
		depan = false;
		break;
		//gerak ke kiri
	case 'v':
	case 'V':
		depan = true;
		break;
		//gerak ke kiri
	case 'a':
	case 'A':
		glTranslatef(-1.0, 0.0, 0.0);
		break;
		//gerak ke kanan
	case 'd':
	case 'D':
		glTranslatef(1.0, 0.0, 0.0);
		break;
		//gerak ke depan
	case 'w':
	case 'W':
		glTranslatef(0.0, 0.0, 1.0);
		break;
		//gerak ke belakang
	case 's':
	case 'S':
		glTranslatef(0.0, 0.0, -1.0);
		break;
		//gerak ke atas
	case 'q':
	case 'Q':
		glTranslatef(0.0, 1.0, 0.0);
		break;
		//gerak ke bawah
	case 'e':
	case 'E':
		glTranslatef(0.0, -1.0, 0.0);
		break;
		//rotate ke kiri
	case 'j':
	case 'J':
		glRotatef(1.0, 0.0, -5.0, 0.0);
		break;
		//rotate ke kanan
	case 'l':
	case 'L':
		glRotatef(1.0, 0.0, 5.0, 0.0);
		break;
		//rotate ke samping kanan
	case 'i':
	case 'I':
		glRotatef(1.0, 0.0, 0.0, -5.0);
		break;
		//rotate ke samping kiri
	case 'k':
	case 'K':
		glRotatef(1.0, 0.0, 0.0, 5.0);
		break;
		//rotate ke atas
	case 'o':
	case 'O':
		glRotatef(1.0, -5.0, 0.0, 0.0);
		break;
		//rotate ke bawah
	case 'u':
	case 'U':
		glRotatef(1.0, 5.0, 0.0, 0.0);
		break;
	}
	display();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);            
	glutInitDisplayMode(GLUT_DOUBLE); 

	glutInitWindowSize(640, 480);   
	glutInitWindowPosition(50, 50); 
	glutCreateWindow("3D");      

	glutDisplayFunc(display);      
	glutReshapeFunc(reshape);     
	glutKeyboardFunc(keyboard);

	initGL();                      
	glutMainLoop();       

	return 0;
}
