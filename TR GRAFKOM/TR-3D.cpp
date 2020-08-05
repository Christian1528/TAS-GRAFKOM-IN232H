#include <GL/glut.h>
#include <Windows.h>

int windowWidth = 700,
windowHeight = 700;

void init() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

void reshape(int width, int height) {
	if (height == 0)height = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, width / height, 1.0, 400.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
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
	glutPostRedisplay();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - windowWidth) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - windowHeight) / 2);
	glutCreateWindow("3D");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}