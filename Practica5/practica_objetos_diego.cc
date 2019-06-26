//**************************************************************************
// Práctica 3 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B3.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, ARTICULADO, CILINDRO, CONO, ESFERA, PRACTICA5} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   t=POINTS;
int modos[4]={0,0,0,0}, cambio;

bool estadoRaton = false;  

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

int vision_actual;

int xc, yc;
// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;


// objetos
_cubo cubo;
_cubo cubo1;
_cubo cubo2;
_cubo cubo3;
_cubo cubo4;
_piramide piramide(0.5,0.75);
_objeto_ply  ply; 
_rotacion rotacion; 
_cilindro cilindro(3.5, 1);
_cono cono(1.3, 2.5);
_esfera esfera(2);
_robot robot;


//_tanque tanque;

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

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
if(vision_actual == 1){
	gluLookAt(0,1,0,0,0,0,1,0,0);
}
else{
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
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
        case CILINDRO: cilindro.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
        case CONO: cono.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
        case ESFERA: esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
       case ARTICULADO: robot.draw(modo,0.43,0.43,0.43,0.74,0.74,0.74,2);break;
       case PRACTICA5:

            glPushMatrix();
            glTranslatef(-0.5,0,0);
            cubo1.draw_solido(cubo1.r,cubo1.g,cubo1.b);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.5,0,0);
            cubo2.draw_solido(cubo2.r,cubo2.g,cubo2.b);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,1,0);
            cubo3.draw_solido(cubo3.r,cubo3.g,cubo3.b);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,2,0);
            cubo4.draw_solido(cubo4.r,cubo4.g,cubo4.b);
            glPopMatrix();
       break;
	}

}

void draw_objects_seleccion()
{
int inc=20;
   glPushMatrix();    
            glPushMatrix();
            glTranslatef(-0.5,0,0);
            cubo1.draw_seleccion_color(100,100,100);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.5,0,0);
            cubo2.draw_seleccion_color(100+inc,100+inc,100+inc);
            glPopMatrix();
            inc+=20;

            glPushMatrix();
            glTranslatef(0,1,0);
            cubo3.draw_seleccion_color(100+inc,100+inc,100+inc);
            glPopMatrix();
            inc+=20;

            glPushMatrix();
            glTranslatef(0,2,0);
            cubo4.draw_seleccion_color(100+inc,100+inc,100+inc);
            glPopMatrix();
   glPopMatrix();   
}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{


clean_window();
change_observer();
draw_axis();
draw_objects();
glDrawBuffer(GL_BACK);


clean_window();
change_observer();
draw_axis();
draw_objects_seleccion();
glDrawBuffer(GL_FRONT);

glFlush();


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

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':modo=POINTS;break;
	case '2':modo=EDGES;break;
	case '3':modo=SOLID;break;
	case '4':modo=SOLID_CHESS;break;
        case 'P':t_objeto=PIRAMIDE;break;
        case 'C':t_objeto=CUBO;break;
        case 'O':t_objeto=OBJETO_PLY;break;	
        case 'R':t_objeto=ROTACION;break;
        case 'A':t_objeto=ARTICULADO;break;
        case '5':t_objeto=CILINDRO;break;
        case '6':t_objeto=CONO;break;
        case '7':t_objeto=ESFERA;break;
        case 'Z':t_objeto=PRACTICA5;break;
        case 'S': if(vision_actual == 0) vision_actual=1; else vision_actual=0; break;
        case '8':robot.giro_antebrazo_izq+=5;
    			if(robot.giro_antebrazo_izq>robot.giro_antebrazo_izq_max) robot.giro_antebrazo_izq=robot.giro_antebrazo_izq_max;
    			break;
    	case '9':robot.giro_antebrazo_izq-=5;
    			if(robot.giro_antebrazo_izq<robot.giro_antebrazo_izq_min) robot.giro_antebrazo_izq=robot.giro_antebrazo_izq_min;
    			break;
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

	case GLUT_KEY_F1:robot.giro_cabeza+=5;break;
    	case GLUT_KEY_F2:robot.giro_cabeza-=5;break;

	case GLUT_KEY_F3:robot.giro_cuerpo+=5;break;
    	case GLUT_KEY_F4:robot.giro_cuerpo-=5;break;

    case GLUT_KEY_F6:robot.giro_brazo_dcho+=5;
    			if(robot.giro_brazo_dcho>robot.giro_brazo_dcho_max) robot.giro_brazo_dcho=robot.giro_brazo_dcho_max;
    			break;
    	case GLUT_KEY_F5:robot.giro_brazo_dcho-=5;
    			if(robot.giro_brazo_dcho<robot.giro_brazo_dcho_min) robot.giro_brazo_dcho=robot.giro_brazo_dcho_min;
    			break;

    case GLUT_KEY_F7:robot.giro_antebrazo_dcho+=5;
    			if(robot.giro_antebrazo_dcho>robot.giro_antebrazo_dcho_max) robot.giro_antebrazo_dcho=robot.giro_antebrazo_dcho_max;
    			break;
    	case GLUT_KEY_F8:robot.giro_antebrazo_dcho-=5;
    			if(robot.giro_antebrazo_dcho<robot.giro_antebrazo_dcho_min) robot.giro_antebrazo_dcho=robot.giro_antebrazo_dcho_min;
    			break;

    case GLUT_KEY_F9:robot.mover_espada+=0.5;
    			if(robot.mover_espada>robot.espada_max) robot.mover_espada=robot.espada_max;
    			break;
    	case GLUT_KEY_F10:robot.mover_espada-=0.5;
    			if(robot.mover_espada<robot.espada_min) robot.mover_espada=robot.espada_min;
    			break;

    case GLUT_KEY_F11:robot.giro_brazo_izq+=5;
    			if(robot.giro_brazo_izq>robot.giro_brazo_izq_max) robot.giro_brazo_izq=robot.giro_brazo_izq_max;
    			break;
    	case GLUT_KEY_F12:robot.giro_brazo_izq-=5;
    			if(robot.giro_brazo_izq<robot.giro_brazo_izq_min) robot.giro_brazo_izq=robot.giro_brazo_izq_min;
    			break;

    /*    case GLUT_KEY_F1:tanque.giro_tubo+=1;
                         if (tanque.giro_tubo>tanque.giro_tubo_max) tanque.giro_tubo=tanque.giro_tubo_max;
                         break;
        case GLUT_KEY_F2:tanque.giro_tubo-=1;
                         if (tanque.giro_tubo<tanque.giro_tubo_min) tanque.giro_tubo=tanque.giro_tubo_min;
                         break;break;
        case GLUT_KEY_F3:tanque.giro_torreta+=5;break;
        case GLUT_KEY_F4:tanque.giro_torreta-=5;break;*/
	}
glutPostRedisplay();
}

void procesar_color(unsigned char color[3])
{
 int i;
_cubo* obj = nullptr;
 
 switch (color[0])
      {case 100: obj=&cubo1;
                 if (modos[0]==0) 
                      {modos[0]=1;
                       cambio=1;
                      }
                  else 
                      {modos[0]=0;
                       cambio=0;
                      }
                  break; 
        case 120: obj=&cubo2;
                  if (modos[1]==0) 
                       {modos[1]=1;
                        cambio=1;
                       }
                  else 
                       {modos[1]=0;
                        cambio=0;
                       } 
                  break;
        case 140: obj=&cubo3;
                  if (modos[2]==0) 
                       {modos[2]=1;
                        cambio=1;
                       }
                  else 
                       {modos[2]=0;
                        cambio=0;
                       }
                  break; 
        case 160: obj=&cubo4;
                  if (modos[3]==0) 
                       {modos[3]=1;
                        cambio=1;
                       }
                  else 
                       {modos[3]=0;
                        cambio=0;
                       }
                  break;      
        }
    if(obj != nullptr){
        if (cambio==1) 
                  {obj->r=0.3;
                   obj->g=0.9;
                   obj->b=0.3;
                  }
        if (cambio==0)
                  {obj->r=0.9;
                   obj->g=0.6;
                   obj->b=0.2;
                  }
    }
                 
}

void pick_color(int x, int y)
{
GLint viewport[4];
unsigned char pixel[3];

glGetIntegerv(GL_VIEWPORT, viewport);
glReadBuffer(GL_BACK);
glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);
printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);

procesar_color(pixel);
glutPostRedisplay();
}


void getCamara (GLfloat *x, GLfloat *y)
{
*x=Observer_angle_x;
*y=Observer_angle_y;
}

/*************************************************************************/

void setCamara (GLfloat x, GLfloat y)
{
Observer_angle_x=x;
Observer_angle_y=y;
}

void clickRaton(int boton, int estado, int x, int y)
{
    if(boton == GLUT_RIGHT_BUTTON){
        if(estado == GLUT_DOWN){
            estadoRaton = true;
            xc=x;
            yc=y;
        }
        else{
            estadoRaton = false;
        }
    }
    if(boton == 3){
        Observer_distance--;
    }
    if(boton == 4){
        Observer_distance++;
    }
    if(boton == GLUT_LEFT_BUTTON){
        if(estado == GLUT_DOWN){
            estadoRaton = false;
            xc=x;
            yc=y;
            pick_color(xc,yc);
        }
    }
    glutPostRedisplay();
}

void ratonMovido(int x, int y){
float x0, y0, xn, yn;
    if (estadoRaton == true){
        getCamara(&x0,&y0);
        yn=y0+(y-yc);
        xn=x0-(x-xc);
        setCamara(xn, yn);
        xc=x;
        yc=y;
        glutPostRedisplay();
    }
}






//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{


for(int i=0; i<4; i++){
	modos[i]=0;
}
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

ply.parametros(argv[1]);


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
//rotacion.parametros(perfil2,6,1);


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
