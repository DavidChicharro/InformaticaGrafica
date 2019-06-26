//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
  unsigned i;
  glPointSize(grosor);
  glColor3f(r,g,b);
  glBegin(GL_POINTS);
  for (i=0;i<vertices.size();i++){
  	glVertex3fv((GLfloat *) &vertices[i]);
  	}
  glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
  unsigned i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glLineWidth(grosor);
  glColor3f(r,g,b);
  glBegin(GL_TRIANGLES);
  for (i=0;i<caras.size();i++){
  	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
  	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
  	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
  unsigned i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glColor3f(r,g,b);
  glBegin(GL_TRIANGLES);
  for (i=0;i<caras.size();i++){
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
  unsigned i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glColor3f(r1,g1,b1);
  glBegin(GL_TRIANGLES);
  for (i=0;i<caras.size();i++)
    if(i%2==0){
      glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
      glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
      glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();

  glColor3f(r2,g2,b2);
  glBegin(GL_TRIANGLES);
    for (i=0;i<caras.size();i++)
      if(i%2!=0){
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
      }
  glEnd();

}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices


// triangulos

}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}

_cilindro::_cilindro(float radio, float altura/*, int num_lados*/){
  //_rotacion rotacion;
/*
  vertices.resize(4);
  vertices[0].x=0.1;      vertices[0].y=0;       vertices[0].z=0;
  vertices[1].x=radio;  vertices[1].y=0;       vertices[1].z=0;
  vertices[2].x=radio;  vertices[2].y=altura;  vertices[2].z=0;
  vertices[3].x=0.1;      vertices[3].y=altura;  vertices[3].z=0;
*/

  vertices.resize(2);
  vertices[0].x=radio;  vertices[0].y=0;       vertices[0].z=0;
  vertices[1].x=radio;  vertices[1].y=altura;  vertices[1].z=0;

  for(unsigned i=0 ; i<vertices.size() ; i++)
    perfil.push_back(vertices[i]);
  

  parametros(perfil,10);
}

_cono::_cono(float radio, float altura){
  parametros_cono(radio, altura, 30);
}

_esfera::_esfera(float radio, int latitud, int longitud){
  _vertex3f vertice_aux;

  for(int i=1 ; i<latitud ; i++){
    vertice_aux.x = radio*cos(-M_PI/2+i*M_PI/latitud);
    vertice_aux.y = radio*sin(-M_PI/2+i*M_PI/latitud);
    vertice_aux.z = 0.0;

    perfil.push_back(vertice_aux);
  }
  
  parametros_esfera(perfil,longitud,radio);
}


int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

//if (n_ver<3 || n_car<1){
//	printf("Error %d %d\n",__FILE__,__LINE__);
//	exit(-1);
//	}

vertices.resize(n_ver);
caras.resize(n_car);

_vertex3f ver_aux;
_vertex3i car_aux;

for (int i=0;i<n_ver;i++)
	{ver_aux.x=ver_ply[i*3];
	 ver_aux.y=ver_ply[i*3+1];
	 ver_aux.z=ver_ply[i*3+2];
	 vertices[i]=ver_aux;
	}

for (int i=0;i<n_car;i++)
	{car_aux.x=car_ply[i*3];
	 car_aux.y=car_ply[i*3+1];
	 car_aux.z=car_ply[i*3+2];
	 caras[i]=car_aux;
	}

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}

void _rotacion::parametros_cono(float radio, float altura, int num){
  int j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;

  //tratamiento de los vértices
  vertices.resize(num);
  for (j=0;j<num;j++){
    vertice_aux.x=radio*cos(2.0*M_PI*j/(1.0*num));
    vertice_aux.z=radio*sin(2.0*M_PI*j/(1.0*num));
    vertice_aux.y=0;
    vertices[j]=vertice_aux;
  }

  //tratamiento de las caras
  vertice_aux.x=0;
  vertice_aux.y=altura;
  vertice_aux.z=0;
  vertices.push_back(vertice_aux);
  for (j=0;j<num;j++){
    cara_aux._0=num;
    cara_aux._1=j;
    cara_aux._2=(j+1)%num;
    caras.push_back(cara_aux);
  }

  //tapa inferior
  vertice_aux.x=0;
  vertice_aux.y=0;
  vertice_aux.z=0;
  vertices.push_back(vertice_aux);

  for(int i=0 ; i<num ; i++){
    cara_aux._0 = vertices.size()-1;
    cara_aux._1 = i;
    cara_aux._2 = (i+1)%num;
    caras.push_back(cara_aux);
  }
}

void _rotacion::parametros_esfera(vector<_vertex3f> perfil, int num, double radio){
  int i,j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;

  // tratamiento de los vértice
  num_aux=perfil.size();
  vertices.resize(num_aux*num);
  for (j=0;j<num;j++){
    for (i=0;i<num_aux;i++){
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
    }
  }

  // tratamiento de las caras
  for (j=0;j<num;j++){
    for (i=0;i<num_aux-1;i++){
      cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);
      
      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
    }
  }

  // tapa inferior
  if (fabs(perfil[0].x)>0.0){
    _vertex3f vertice_inferior;
    vertice_inferior.x=0;
    vertice_inferior.y=-radio;
    vertice_inferior.z=0;

    vertices.push_back(vertice_inferior);

    for(int i=0 ; i<num ; i++){
      cara_aux._0 = vertices.size()-1;
      cara_aux._1 = i*num_aux;
      cara_aux._2 = ((i+1)%num)*num_aux;

      caras.push_back(cara_aux);
    }
  }
   
   // tapa superior
  
  if (fabs(perfil[num_aux-1].x)>0.0){
    _vertex3f vertice_superior;
    vertice_superior.x=0;
    vertice_superior.y=radio;
    vertice_superior.z=0;

    vertices.push_back(vertice_superior);

    for(int i=1 ; i<=num ; i++){
      cara_aux._0 = vertices.size()-1;
      cara_aux._1 = (i*num_aux)-1;
      cara_aux._2 = (num_aux*(i+1)-1)%(num*num_aux);

      caras.push_back(cara_aux);
    }
  }
}

void _rotacion::parametros(vector<_vertex3f> perfil, int num)
{
  int i,j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;

  // tratamiento de los vértice
  num_aux=perfil.size();
  vertices.resize(num_aux*num);
  for (j=0;j<num;j++){
    for (i=0;i<num_aux;i++){
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
    }
  }

  // tratamiento de las caras
  for (j=0;j<num;j++){
    for (i=0;i<num_aux-1;i++){
      cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);
      
      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
    }
  }
     
  // tapa inferior
  if (fabs(perfil[0].x)>0.0){
    _vertex3f vertice_inferior;
    vertice_inferior.x=0;
    vertice_inferior.y=perfil[0].y;
    vertice_inferior.z=0;

    vertices.push_back(vertice_inferior);
    for(int i=0 ; i<num ; i++){
      cara_aux._0 = vertices.size()-1;
      cara_aux._1 = i*num_aux;
      cara_aux._2 = (num_aux*(i+1))%(num*num_aux);
      caras.push_back(cara_aux);
    }
  }
   
  // tapa superior
  if (fabs(perfil[num_aux-1].x)>0.0){
    _vertex3f vertice_superior;
    vertice_superior.x=0;
    vertice_superior.y=perfil[num_aux-1].y;
    vertice_superior.z=0;
    vertices.push_back(vertice_superior);

    for(int i=1 ; i<=num ; i++){
      cara_aux._0 = vertices.size()-1;
      cara_aux._1 = (i*num_aux)-1;
      cara_aux._2 = (num_aux*(i+1)-1)%(num*num_aux);
      caras.push_back(cara_aux);
    }
  }
}

