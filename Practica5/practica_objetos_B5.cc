//**************************************************************************
// Práctica 5 - David Carrasco Chicharro
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B5.h"

using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, GRUA, TELE} _tipo_objeto;
_tipo_objeto t_objeto=TELE;
_modo   modo=POINTS;
int modos[4]={0,0,0,0};
bool cambio = false; 
bool estadoRaton = false;
bool vistas = false;
typedef enum{NORMAL, ALZADO, PLANTA, PERFIL} _tipo_vista;
_tipo_vista vision_actual = NORMAL;

int xc, yc;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;


// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;


// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply; 
_rotacion rotacion;
_grua grua;

_cubo base;
_cubo soporte;
_cubo pantalla;
_piramide punta;
_esfera esfera(0.5,12,12);

// _objeto_ply *ply1;


//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{
/*
// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);*/

	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-Observer_distance);

	switch(vision_actual){
		case NORMAL:
			glRotatef(Observer_angle_x,1,0,0);
			glRotatef(Observer_angle_y,0,1,0);
			break;
		case ALZADO: 
			gluLookAt(0,0,1,0,0,0,0,1,0);
			glOrtho(-1.0,1.0,-1.0,1.0,-100.0,100.0);
			break;
		case PERFIL: 
			gluLookAt(1,0,0,0,0,0,0,1,0); 
			glOrtho(-100.0,100.0,-1.0,1.0,-1.0,1.0);
			break;
		case PLANTA: 
			gluLookAt(0,1,0,0,0,0,0,0,1);
			glOrtho(-1.0, 1.0, -100.0, 100.0, -1.0,1.0);
			break;
	}
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
//glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


void draw_tele(){
	glPushMatrix();
	glScalef(1.0,0.1,1.0);
	base.draw_solido(base.r,base.g,base.b);
	base.draw_aristas(0,0,0,2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0.25,0);
	glScalef(0.25,0.4,0.2);
	soporte.draw_solido(soporte.r,soporte.g,soporte.b);
	soporte.draw_aristas(0,0,0,2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0.95,0.025);
	glScalef(2.0,1.0,0.25);
	pantalla.draw_solido(pantalla.r,pantalla.g,pantalla.b);
	pantalla.draw_aristas(0,0,0,2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,-0.05,0);
	glScalef(1.2,-0.85,1.2);
	punta.draw_solido(punta.r,punta.g,punta.b);
	punta.draw_aristas(0,0,0,2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,-1.15,0);
	glScalef(1,1,1);
	esfera.draw_solido(esfera.r,esfera.g,esfera.b);
	//esfera.draw_aristas(0,0,0,2);
	glPopMatrix();
}

//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

switch (t_objeto){
	case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
		case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
		case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
		case GRUA: grua.draw(modo,0.0,0.0,1.0,0.0,1.0,1.0,2);break;
		case TELE: draw_tele();break;

	}
}

//**************************************************************************
// Funcion que dibuja los objetos en el buffer trasero
//***************************************************************************

void draw_objects_seleccion(){
	int inc=20;
	glPushMatrix();
		glPushMatrix();
		glScalef(1.0,0.1,1.0);
		base.draw_seleccion_color(100,100,100);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0,0.25,0);
		glScalef(0.25,0.4,0.2);
		soporte.draw_seleccion_color(100+inc,100+inc,100+inc);
		glPopMatrix();
		inc+=20;

		glPushMatrix();
		glTranslatef(0,0.95,0.025);
		glScalef(2.0,1.0,0.25);
		pantalla.draw_seleccion_color(100+inc,100+inc,100+inc);
		glPopMatrix();
		inc+=20;

		glPushMatrix();
		glTranslatef(0,-0.05,0);
		glScalef(1.2,-0.85,1.2);
		punta.draw_seleccion_color(100+inc,100+inc,100+inc);
		glPopMatrix();
		inc+=20;

		glPushMatrix();
		glTranslatef(0,-1.15,0);
		glScalef(1,1,1);
		esfera.draw_seleccion_color(100+inc,100+inc,100+inc);
		glPopMatrix();

		 
	glPopMatrix();   
}

//***************************************************************************
// Funciones para la seleccion
//***************************************************************************

void accion_procesar(int i){
	if(modos[i]==0){
		modos[i]=1;
		cambio=true;
	}
	else{
		modos[i]=0;
		cambio=false;
	}
}

template <typename T>
void cambia(T obj){
	if(obj != nullptr){	         
		if (cambio){
			obj->r=0.3;
			obj->g=0.9;
			obj->b=0.3;
		}
		if (!cambio){
			obj->r=0.9;
			obj->g=0.6;
			obj->b=0.2;
		}
	}
}

void procesar_color(unsigned char color[3]){
	int i;
	
	_cubo* obj=nullptr;
	_piramide* objp=nullptr;
	_esfera* obje=nullptr;

	switch (color[0]){
		case 100: obj=&base;
			accion_procesar(0); break; 
		case 120: obj=&soporte;
			accion_procesar(1); break;
		case 140: obj=&pantalla;
			accion_procesar(2); break;
		case 160: objp=&punta;
			accion_procesar(3); break;
		case 180: obje=&esfera;
			accion_procesar(4); break;
	}

	cambia(obj);
	cambia(objp);
	cambia(obje);
	       
}


//**************************************************************************
//
//***************************************************************************

void draw(void){
	clean_window();

	if(!vistas){
		change_observer();
		draw_axis();
		draw_objects();

		glDrawBuffer(GL_BACK);
		clean_window();
		change_observer();
		draw_objects_seleccion();
		glDrawBuffer(GL_FRONT);

		glFlush();
	}
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y){
	switch (toupper(Tecla1)){
		case 'Q':exit(0);
		case '1':modo=POINTS;break;
		case '2':modo=EDGES;break;
		case '3':modo=SOLID;break;
		case '4':modo=SOLID_CHESS;break;
		case '7':vision_actual=ALZADO;break;
		case '8':vision_actual=PERFIL;break;
		case '9':vision_actual=PLANTA;break;
		case '0':vision_actual=NORMAL;break;
	        case 'P':t_objeto=PIRAMIDE;break;
	        case 'C':t_objeto=CUBO;break;
	        case 'O':t_objeto=OBJETO_PLY;break;	
	        case 'R':t_objeto=ROTACION;break;
	        case 'G':t_objeto=GRUA;break;
	        case 'T':t_objeto=TELE;break;
	}
	glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	    case GLUT_KEY_F3:grua.giro_cabina-=5;break;
	    case GLUT_KEY_F4:grua.giro_cabina+=5;break;
	    case GLUT_KEY_F5:grua.giro_pieza_2+=1;
	        if(grua.giro_pieza_2>grua.giro_pieza_max)   grua.giro_pieza_2=grua.giro_pieza_max; break;
	    case GLUT_KEY_F6:grua.giro_pieza_2-=1;
	       if(grua.giro_pieza_2<grua.giro_pieza_min)   grua.giro_pieza_2=grua.giro_pieza_min; break;
	    case GLUT_KEY_F7:grua.mov_pieza+=0.3;
	        if(grua.mov_pieza>grua.mov_pieza_max)   grua.mov_pieza=grua.mov_pieza_max; break;
	    case GLUT_KEY_F8:grua.mov_pieza-=0.3;
	       if(grua.mov_pieza<grua.mov_pieza_min)   grua.mov_pieza=grua.mov_pieza_min; break;
	    case GLUT_KEY_F9:grua.giro_plataforma+=0.5;
	        if(grua.giro_plataforma>grua.giro_pieza_max)   grua.giro_plataforma=grua.giro_pieza_max; break;
	    case GLUT_KEY_F10:grua.giro_plataforma-=0.5;
	       if(grua.giro_plataforma<grua.giro_pieza_min)   grua.giro_plataforma=grua.giro_pieza_min; break;
        
	}
	glutPostRedisplay();
}

void pick_color(int x, int y){
	
	GLint viewport[4];
	unsigned char pixel[3];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadBuffer(GL_BACK);
	glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);
	printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);

	procesar_color(pixel);
	glutPostRedisplay();
}




void getCamara (GLfloat *x, GLfloat *y){
	*x=Observer_angle_x;
	*y=Observer_angle_y;
}

/*************************************************************************/

void setCamara (GLfloat x, GLfloat y){
	Observer_angle_x=x;
	Observer_angle_y=y;
}

//***************************************************************************
// Funciones para manejo de eventos del ratón
//***************************************************************************

void clickRaton( int boton, int estado, int x, int y){
	if(boton == GLUT_RIGHT_BUTTON){
		if( estado == GLUT_DOWN) {
		   estadoRaton = true;
		   xc=x;
		   yc=y;
		}
		else
			estadoRaton = false;
	}
	if(boton == GLUT_LEFT_BUTTON){
		if( estado == GLUT_DOWN) {
			estadoRaton = false;
			xc=x;
			yc=y;
			pick_color(xc, yc);
		} 
	}
	if(boton == 3)
		Observer_distance/=1.2;
	if(boton == 4)
		Observer_distance*=1.2;

	glutPostRedisplay();
}

void ratonMovido( int x, int y ){
	float x0, y0, xn, yn; 
	if(estadoRaton){
		getCamara(&x0,&y0);
		yn=y0+(x-xc);
		xn=x0+(y-yc);
		setCamara(xn,yn);
		xc=x;
		yc=y;
		glutPostRedisplay();
	}
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void){

	// se inicalizan la ventana y los planos de corte
	Size_x=0.5;
	Size_y=0.5;
	Front_plane=1;
	Back_plane=1000;

	// se incia la posicion del observador, en el eje z
	Observer_distance=4*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

	// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1,1,1,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	change_projection();
	glViewport(0,0,Window_width,Window_high);

	for(int i=0 ; i<4 ; i++)
		modos[i]=0;

}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char **argv)
{
 

// creación del objeto ply
char file[]="beethoven";
ply.parametros(file);


// perfil 

vector<_vertex3f> perfil2;
_vertex3f aux;
aux.x=1.0;aux.y=-1.4;aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.0;aux.y=-1.1;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=-0.7;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4;aux.y=-0.4;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4;aux.y=0.5;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=0.6;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.3;aux.y=0.6;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=0.8;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.55;aux.y=1.0;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=1.2;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.3;aux.y=1.4;aux.z=0.0;
perfil2.push_back(aux);
rotacion.parametros(perfil2,6,1);


// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA 5");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

glutMouseFunc(clickRaton);
glutMotionFunc(ratonMovido);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
