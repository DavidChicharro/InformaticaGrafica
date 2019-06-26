//**************************************************************************
// Práctica IG usando objetos
//**************************************************************************

#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"
#include "CImg.h"
#include <jpeglib.h>
#include <cstring>
#include <string>

using namespace std;
using namespace cimg_library;
#define cimg_use_jpeg

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,SOLID_ILLUMINATED_FLAT,
             SOLID_ILLUMINATED_GOURAUD, TEXTURE} _modo;

// FUNCIÓN QUE PREPARA LA TEXTURA
void prepara_textura(char *archivo);

// FUNCIÓN QUE LIBERA LA TEXTURA DE GPU
void libera_textura(void);

//*************************************************************************
// clase luz
//*************************************************************************

class luz{
public:
  luz( GLenum p_luz_ind, _vertex4f p_luz_punto, _vertex4f p_luz_ambiente,
    _vertex4f p_luz_difusa, _vertex4f p_luz_especular);

  void activar();
  void desactivar();
  void transformar (GLenum p_luz_ind, float ang, int a, int b, int c,
                    float x, float y, float z);

protected:
  GLenum luz_ind;     // indice de la fuente de luz (entre GL_LIGHT0 y GL_LIGHT7)
  _vertex4f luz_punto;  // posición o vector de dirección de la luz, según sea el último componente 1 o 0

  _vertex4f luz_ambiente;   // componente ambiental de la luz
  _vertex4f luz_difusa;   // componente difusa de la luz
  _vertex4f luz_especular;  // componente especular de la luz

};


//*************************************************************************
// clase textura
//*************************************************************************

class textura{
public:
  // lee una imagen para usarla como textura con OpenGL
  textura(char *archivo);
};


//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void  draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void  draw_textura( );
void 	draw_iluminacion_plana( );
void 	draw_iluminacion_suave( );

void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

void	calcular_normales_caras();
void 	calcular_normales_vertices();

vector<_vertex3i> caras;

vector<_vertex3f> normales_caras;
vector<_vertex3f> normales_vertices;
vector<_vertex2f> textura_coord;		// texels

bool b_normales_caras;
bool b_normales_vertices;
bool b_textura_coord;

_vertex4f ambiente_difusa;     //coeficientes ambiente y difuso
_vertex4f especular;           //coeficiente especular
float brillo;                  //exponente del brillo 

_vertex4f ambiente_difusa_2;
_vertex4f especular_2;
float brillo_2;

bool modo_text;
GLfloat plano_s[4], plano_t[4];

};

//*************************************************************************
// clase malla
//*************************************************************************

class _malla: public _triangulos3D
{
public:

  _malla(int filas, int columnas);
};

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};

class _skybox: public _triangulos3D
{
public:

  _skybox(float tam=1.0);
  void generar_textura_skybox();
};

//void generar_textura_skybox();


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase skypyramid
//*************************************************************************

class _skypyramid: public _triangulos3D
{
public:

  _skypyramid(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase abeto
//*************************************************************************

class _abeto: public _triangulos3D
{
public:

  _abeto(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num);
void  parametros_cono(float radio, float altura, int num);
void  parametros_esfera(vector<_vertex3f> perfil, int num, double radio);

vector<_vertex3f> perfil; 
int num;
};

class _cilindro: public _rotacion
{
public:
  _cilindro(float radio, float altura);

  vector<_vertex3f> perfil; 
  int num;
};

class _esfera: public _rotacion
{
public:
  _esfera(float radio, int latitud, int longitud);

  vector<_vertex3f> perfil; 
  int num;
};

class _cono: public _rotacion
{
public:
  _cono(float radio, float altura);

  int num;
};


//************************************************************************
// objeto articulado: tanque
//************************************************************************

class _chasis: public _triangulos3D
{
public:
       _chasis();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;

protected:
_rotacion  rodamiento;
_cubo  base;
};

//************************************************************************

class _torreta: public _triangulos3D
{
public:
       _torreta();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;
float anchura;

protected:
_cubo  base;
_piramide parte_trasera;
};

//************************************************************************

class _tubo: public _triangulos3D
{
public:
       _tubo();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_rotacion tubo_abierto; // caña del cañón
};

//************************************************************************

class _tanque: public _triangulos3D
{
public:
       _tanque();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float giro_tubo;
float giro_torreta;

float giro_tubo_min;
float giro_tubo_max;

protected:
_chasis  chasis;
_torreta  torreta;
_tubo     tubo;
};
