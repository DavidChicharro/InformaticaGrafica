//**************************************************************************
// Práctica 5 usando objetos
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
	void	draw_seleccion_color(int r, int g, int b);
	void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:
	float r,g,b;
	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:
	float r,g,b;
	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase triangulo
//*************************************************************************

class _triangulo: public _triangulos3D
{
public:
  float r,g,b;
  _triangulo(float base=0.5, float al=0.75);
};


//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D{
public:
	       _rotacion();
	void  parametros(vector<_vertex3f> perfil1, int num, int tapa);
	void  parametros_cono(float radio, float altura, int num);
	void  parametros_esfera(vector<_vertex3f> perfil, int num, double radio);

	vector<_vertex3f> perfil; 
	int num;
};

//*************************************************************************
// clase cilindro
//*************************************************************************

class _cilindro: public _rotacion
{
public:
  _cilindro(float radio, float altura);

  float r,g,b;
  vector<_vertex3f> perfil; 
  int num;
};

//*************************************************************************
// clase esfera
//*************************************************************************

class _esfera: public _rotacion
{
public:
  _esfera(float radio, int latitud, int longitud);

  float r,g,b;
  vector<_vertex3f> perfil; 
  int num;
};

//*************************************************************************
// clase cono
//*************************************************************************

class _cono: public _rotacion
{
public:
  _cono(float radio, float altura);

  float r,g,b;
  int num;
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

