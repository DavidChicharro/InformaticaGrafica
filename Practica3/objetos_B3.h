//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;

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
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
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
void  parametros(vector<_vertex3f> perfil1, int num1, int tapas);

vector<_vertex3f> perfil; 
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


//************************************************************************
// objeto articulado: grua
//************************************************************************

class _chasis_grua: public _triangulos3D
{
public:
       _chasis_grua();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;

protected:
_rotacion  ruedas;
_cubo  base;
};


class _cabina: public _triangulos3D
{
public:
      _cabina();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;
float radio;

protected:
_rotacion cabina;      
};

class _pieza1: public _triangulos3D
{
public:
  _pieza1();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float an1;

protected:
_cubo brazo1;  
  
};

class _pieza2: public _triangulos3D
{
public:
  _pieza2();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float an2;

protected:
_cubo brazo2;  
  
};

class _pieza3: public _triangulos3D
{
public:
  _pieza3();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float an3;

protected:
_cubo brazo3;  
  
};

class _pieza4: public _triangulos3D
{
public:
  _pieza4();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float an4;

protected:
_cubo brazo4;
  
};

class _pieza5: public _triangulos3D
{
public:
  _pieza5();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float an5;

protected:
_cubo brazo5;
  
};

class _plataforma: public _triangulos3D
{
public:
  _plataforma();
void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;
float radio;
float anp;

protected:
  _rotacion plataforma_hueca;
};

//*****************************************************************************************

class _grua: public _triangulos3D {
public:
  _grua();
  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  //base
  float giro_cabina;
  float giro_pieza_2;
  float giro_pieza_3;
  float mov_pieza;
  float giro_plataforma;

  float giro_pieza_min;
  float giro_pieza_max;
  float mov_pieza_min;
  float mov_pieza_max;
  /*
  float giro_pieza_2;
  float giro_pieza_3;
  float giro_pieza_4;
  float giro_pieza_5;
  float giro_pieza_6;
  float giro_pieza_7;*/

protected:
  _chasis_grua  chasis_grua;
  _cabina  cabina;
  _pieza1  brazo1;
  _pieza2  brazo2;
  _pieza3  brazo3;
  _pieza4  brazo4;
  _pieza5  brazo5;
  _plataforma plataforma;
};

