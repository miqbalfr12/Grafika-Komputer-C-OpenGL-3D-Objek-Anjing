#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
double rx = 0.0; 	// deklarasi rotasi sumbu x statik
double ry = 0.0; 	// sumbu y
double sc = 1;		// scaling
float light_position[] = { 0.0, 80.0, 0.0 }; // koordinat sumber cahaya
float n[] = { 0.0, -1.0, 0.0 };
float e[] = { 0.0, -60.0, 0.0 };
bool warna;			// boolean untuk aktifasi warna
int a,b,c;			// untuk variabel statik tranlasi

int screen_width=400;
int screen_height=400;


int anjing(bool warna){
    // membuat objek anjing

	glPushMatrix(); //kepala
		if(warna)glColor3f(0.6,0.6,0.6);
		glTranslatef(0, 0, 7);
	    glutSolidCube(25);
	    glTranslatef(0, 0, 15);
	    glutSolidCube(20);
	    glTranslatef(0, -6, 12);
	    glutSolidCube(7);
	    
	    //aksesoris kepala
	    glPushMatrix(); //kalung merah
		    if (warna)glColor3f(1,0.2,0.2);
		    glTranslatef(0, 6, -15);
		    glScaled(1,1,0.05);
		    glutSolidCube(25.5);
	    glPopMatrix();
	    
	    glPushMatrix(); // mulut
	    	if (warna) glColor3f(0.2,0.2,0.2);
		    glTranslatef(0,-2.2, 0);
		    glScaled(1,0.4,1);
		    glutSolidCube(7.2);
	    glPopMatrix();
	    
	    glPushMatrix(); // hidung
		    glTranslatef(0,2.2, 2.2);
		    glutSolidCube(3);
	    glPopMatrix();
	    
	   	glPushMatrix(); // mata
	   		glPushMatrix(); // mata kiri
		   		glTranslatef(-6, 9, -2);
			    glScaled(1,1,-0.1);
			    if(warna)glColor3f(1,1,1);
			    glutSolidCube(3);
			    glTranslatef(-3,-3, 0);
			    glutSolidCube(3);
			    glTranslatef(3,0, 0);
			    if(warna)glColor3f(0.2,0.2,0.2);
			    glutSolidCube(3);
			glPopMatrix();
			glPushMatrix(); // mata kanan
		   		glTranslatef(6, 9, -2);
			    glScaled(1,1,-0.1);
			    if(warna)glColor3f(1,1,1);
			    glutSolidCube(3);
			    glTranslatef(3,-3, 0);
			    glutSolidCube(3);
			    glTranslatef(-3,0, 0);
			    if(warna)glColor3f(0.2,0.2,0.2);
			    glutSolidCube(3);
			glPopMatrix();
	    glPopMatrix();
    glPopMatrix();

    glPushMatrix(); // badan
    	if (warna)glColor3f(0.6,0.6,0.6);
		glScaled(1,1,3);
		glutSolidCube(20);
    glPopMatrix();
    
    glPushMatrix(); // Telinga
		glTranslatef(6, 13, 20);
		glScaled(1,1,-0.5);
		glutSolidCube(7);
		glTranslatef(-12, 0, 0);
		glutSolidCube(7);
    glPopMatrix();
    
    glPushMatrix(); // Ekor
		glTranslatef(0, 0, -32);
		glRotatef(130,130,1,1);
		glScaled(1,1,3);
		glutSolidCube(5);

    glPopMatrix();
    
    glPushMatrix(); //Kaki
    	glPushMatrix(); //Kaki depan
		    glTranslatef(-5, -13, 13);
		    glScaled(1,3,1);
		    glutSolidCube(8);
			glTranslatef(10, 0, 0);
		    glutSolidCube(8);
		glPopMatrix();
	    glPushMatrix(); //Kaki belakang
		    glTranslatef(-5, -13, -23);
		    glScaled(1,3,1);
		    glutSolidCube(8);
			glTranslatef(10, 0, 0);
		    glutSolidCube(8);
    	glPopMatrix();
    glPopMatrix();
}

// membuat proyeksi bayangan
void glShadowProjection(float * l, float * e, float * n) {
    float d, c;
    float mat[16];
    d = n[0]*l[0] + n[1]*l[1] + n[2]*l[2];
    c = e[0]*n[0] + e[1]*n[1] + e[2]*n[2] - d;
    mat[0] = l[0]*n[0]+c; // membuat matrik. OpenGL menggunakan kolom matrik
    mat[4] = n[1]*l[0];
    mat[8] = n[2]*l[0];
    mat[12] = -l[0]*c-l[0]*d;
    mat[1] = n[0]*l[1];
    mat[5] = l[1]*n[1]+c;
    mat[9] = n[2]*l[1];
    mat[13] = -l[1]*c-l[1]*d;
    mat[2] = n[0]*l[2];
    mat[6] = n[1]*l[2];
    mat[10] = l[2]*n[2]+c;
    mat[14] = -l[2]*c-l[2]*d;
    mat[3] = n[0];
    mat[7] = n[1];
    mat[11] = n[2];
    mat[15] = -d;
    glMultMatrixf(mat); // kalikan matrik
}

void lantai(){
    glColor3f(0.5,1,0.5); //Lantai
    glBegin(GL_QUADS);
	    glNormal3f(0.0,1.0,0.0);
	    glVertex3f(-1300.0,e[1]-0.1, 1300.0);
	    glVertex3f( 1300.0,e[1]-0.1, 1300.0);
	    glVertex3f( 1300.0,e[1]-0.1,-1300.0);
	    glVertex3f(-1300.0,e[1]-0.1,-1300.0);
    glEnd();
}

void objek(){
    // untuk objek
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
	glTranslatef(a,b,c);
	    glPushMatrix();
		    glRotatef(ry,0,1,0);
		    glRotatef(rx,1,0,0);
		    glScalef(sc,sc,sc);
		    glEnable(GL_LIGHTING);
		    glColor3f(0,0,1);
		    anjing(1);
	    glPopMatrix();
	glPopMatrix();
    glFlush();
}

void bayangan(){
    // bayangan yang muncul
    glPushMatrix();
	    glPushMatrix();
		    glShadowProjection(light_position,e,n);
		    glTranslatef(a,b,c);
		    glRotatef(ry,0,1,0);
		    glRotatef(rx,1,0,0);
		    glScalef(sc,sc,sc);
		    glDisable(GL_LIGHTING);
		    glColor3f(0.4,0.4,0.4);
		    anjing(0);
	    glPopMatrix();
    glPopMatrix();
}

void render(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glClearColor(0.5,0.5,1,0.0); // latar belakang
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POINTS);
    glVertex3f(light_position[0],light_position[1],light_position[2]);
    glEnd();
    
    lantai();
    objek();
    bayangan();

    glutSwapBuffers();
}

void rotX(){
    rx+=0.1;
    render();
}
void rotY(){
    ry+=0.1;
    render();
}
void zoomIn(){
    sc+=0.001;
    render();
}
void zoomOut(){
    sc-=0.001;
    render();
}
void stop(){
    rx+=0;
    ry+=0;
    sc+=0;
    render();
}

void keypress(unsigned char c, int a, int b){
    if ( c==27 ) exit(0);
    else if ( c=='s' ) light_position[1]-=5.0;
    else if ( c=='w' ) light_position[1]+=5.0;
    else if ( c=='a' ) light_position[0]-=5.0;
    else if ( c=='d' ) light_position[0]+=5.0;
    else if ( c=='q' ) light_position[2]-=5.0;
    else if ( c=='e' ) light_position[2]+=5.0;
    else if ( c=='g' ) glutIdleFunc(rotY);
    else if ( c=='h' ) glutIdleFunc(rotX);
    else if ( c=='j' ) glutIdleFunc(stop);
    else if ( c=='k' ) glutIdleFunc(zoomIn);
    else if ( c=='l' ) glutIdleFunc(zoomOut);
}

void SpecialInput(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			c = c + 1;
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			c = c - 1;
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:
			a = a + 1;
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			a = a - 1;
			glutPostRedisplay();
			break;
		case GLUT_KEY_PAGE_UP:
			b = b + 1;
			glutPostRedisplay();
			break;	
		case GLUT_KEY_PAGE_DOWN:
			b = b - 1;
			glutPostRedisplay();
			break;
	}
}

void resize(int width,int height)
{
	 screen_width=width;
	 screen_height=height;
	
	 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	 glViewport(0,0,screen_width,screen_height);
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,1.0f,1000.0f);
	
	 glutPostRedisplay();
}

// Setup Pencahayaan
void SetupPencahayaan(){	
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};
    GLfloat light_diffuse[] ={1.0, 1.0, 1.0, 1.0};


    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 1.0, 1.0, 400.0);
	glMatrixMode(GL_MODELVIEW);
	// Reset koordinat sebelum dimodifikasi/diubah
    glLoadIdentity();
	glTranslatef(0.0, 0.0, -150.0);
}

int main(int argc, char * argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("kelompok 6 ");
    glutReshapeFunc(resize);
    glutReshapeWindow(700,700);
    glutKeyboardFunc(keypress);
    glutSpecialFunc(SpecialInput);
    SetupPencahayaan();
    glutDisplayFunc(render);
    glutMainLoop();
    return 0;
}
