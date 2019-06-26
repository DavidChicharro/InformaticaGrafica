//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"


_file_ply fichero_ply;
//**************************************************************************
// Funcciones para construir modelos sólidos poligonales
//**************************************************************************

void construir_cubo(float tam, solido *cubo){

	cubo->n_v=8;
	cubo->n_c=12;
	cubo->ver=(vertices *)malloc(8*sizeof(vertices));
	cubo->car=(caras *)malloc(12*sizeof(caras));

	cubo->ver[0].coord[0]=-tam;cubo->ver[0].coord[1]=-tam;cubo->ver[0].coord[2]=tam;
	cubo->ver[1].coord[0]=tam;cubo->ver[1].coord[1]=-tam;cubo->ver[1].coord[2]=tam;
	cubo->ver[2].coord[0]=tam;cubo->ver[2].coord[1]=tam;cubo->ver[2].coord[2]=tam;
	cubo->ver[3].coord[0]=-tam;cubo->ver[3].coord[1]=tam;cubo->ver[3].coord[2]=tam;
	cubo->ver[4].coord[0]=-tam;cubo->ver[4].coord[1]=-tam;cubo->ver[4].coord[2]=-tam;
	cubo->ver[5].coord[0]=tam;cubo->ver[5].coord[1]=-tam;cubo->ver[5].coord[2]=-tam;
	cubo->ver[6].coord[0]=tam;cubo->ver[6].coord[1]=tam;cubo->ver[6].coord[2]=-tam;
	cubo->ver[7].coord[0]=-tam;cubo->ver[7].coord[1]=tam;cubo->ver[7].coord[2]=-tam;

	cubo->car[0].ind_c[0]=0;cubo->car[0].ind_c[1]=1;cubo->car[0].ind_c[2]=3;
	cubo->car[1].ind_c[0]=3;cubo->car[1].ind_c[1]=1;cubo->car[1].ind_c[2]=2;
	cubo->car[2].ind_c[0]=1;cubo->car[2].ind_c[1]=5;cubo->car[2].ind_c[2]=2;
	cubo->car[3].ind_c[0]=5;cubo->car[3].ind_c[1]=6;cubo->car[3].ind_c[2]=2;
	cubo->car[4].ind_c[0]=5;cubo->car[4].ind_c[1]=4;cubo->car[4].ind_c[2]=6;
	cubo->car[5].ind_c[0]=4;cubo->car[5].ind_c[1]=7;cubo->car[5].ind_c[2]=6;
	cubo->car[6].ind_c[0]=0;cubo->car[6].ind_c[1]=7;cubo->car[6].ind_c[2]=4;
	cubo->car[7].ind_c[0]=0;cubo->car[7].ind_c[1]=3;cubo->car[7].ind_c[2]=7;
	cubo->car[8].ind_c[0]=3;cubo->car[8].ind_c[1]=2;cubo->car[8].ind_c[2]=7;
	cubo->car[9].ind_c[0]=2;cubo->car[9].ind_c[1]=6;cubo->car[9].ind_c[2]=7;
	cubo->car[10].ind_c[0]=0;cubo->car[10].ind_c[1]=1;cubo->car[10].ind_c[2]=4;
	cubo->car[11].ind_c[0]=1;cubo->car[11].ind_c[1]=5;cubo->car[11].ind_c[2]=4;  

}


void construir_piramide(float tam, float al, solido *piramide){
	piramide->n_v=5;
	piramide->n_c=6;
	piramide->ver=(vertices *)malloc(5*sizeof(vertices));
	piramide->car=(caras *)malloc(6*sizeof(caras));

	piramide->r=0.9;piramide->g=0.6;piramide->b=0.2;

	// asignar puntos y caras  
	piramide->ver[0].coord[0]=-tam;piramide->ver[0].coord[1]=0;piramide->ver[0].coord[2]=tam;
	piramide->ver[1].coord[0]=tam;piramide->ver[1].coord[1]=0;piramide->ver[1].coord[2]=tam;
	piramide->ver[2].coord[0]=tam;piramide->ver[2].coord[1]=0;piramide->ver[2].coord[2]=-tam;
	piramide->ver[3].coord[0]=-tam;piramide->ver[3].coord[1]=0;piramide->ver[3].coord[2]=-tam;
	piramide->ver[4].coord[0]=0;piramide->ver[4].coord[1]=al;piramide->ver[4].coord[2]=0;

	piramide->car[0].ind_c[0]=0;piramide->car[0].ind_c[1]=1;piramide->car[0].ind_c[2]=4;
	piramide->car[1].ind_c[0]=1;piramide->car[1].ind_c[1]=2;piramide->car[1].ind_c[2]=4;
	piramide->car[2].ind_c[0]=2;piramide->car[2].ind_c[1]=3;piramide->car[2].ind_c[2]=4;
	piramide->car[3].ind_c[0]=3;piramide->car[3].ind_c[1]=0;piramide->car[3].ind_c[2]=4;
	piramide->car[4].ind_c[0]=3;piramide->car[4].ind_c[1]=1;piramide->car[4].ind_c[2]=0;
	piramide->car[5].ind_c[0]=3;piramide->car[5].ind_c[1]=2;piramide->car[5].ind_c[2]=1;  
}


void construir_ply(char *file, solido *ply){
	vector<int> faces_ply;
	vector<float> vertices_ply;
		
	fichero_ply.open(file);
	fichero_ply.read(vertices_ply,faces_ply);
		
	// leido el fichero ply se convierte a una estructura tipo solido
	int n_v, n_c;
	n_v=vertices_ply.size()/3;
	n_c=faces_ply.size()/3;

	ply->n_v=n_v;
	ply->n_c=n_c;
	ply->ver=(vertices *)malloc(n_v*sizeof(vertices));
	ply->car=(caras *)malloc(n_c*sizeof(caras));

	for (int i=0;i<n_v;i++){
		ply->ver[i].coord[0]=vertices_ply[i*3];
		ply->ver[i].coord[1]=vertices_ply[i*3+1];
		ply->ver[i].coord[2]=vertices_ply[i*3+2];
	}

	for (int i=0;i<n_c;i++){
		ply->car[i].ind_c[0]=faces_ply[i*3];
		ply->car[i].ind_c[1]=faces_ply[i*3+1];
		ply->car[i].ind_c[2]=faces_ply[i*3+2];
	} 
}



//**************************************************************************
// Funciones de visualización
//**************************************************************************


void draw_puntos(vertices *ver, int n_v){
	glColor3f(0,0,0);
	glPointSize(10);

	glBegin(GL_POINTS);
	for (unsigned i=0;i<n_v;i++){
		glVertex3f(ver[i].coord[0],ver[i].coord[1],ver[i].coord[2]);
	}
	glEnd();
}


void draw_solido(solido *malla, float r, float g, float b, int modo){  
	int n_c,n_v,i;
	n_c=malla->n_c;

	if (modo==1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(r,g,b);
	glLineWidth(3);
	glBegin(GL_TRIANGLES);
	for (i=0;i<n_c;i++){
		n_v=malla->car[i].ind_c[0];
		glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
		n_v=malla->car[i].ind_c[1];
		glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
		n_v=malla->car[i].ind_c[2];
		glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
	}
	glEnd();  
}

void draw_solido_ajedrez(solido *malla, float r1, float g1, float b1, float r2, float g2, float b2)
{
  
  int n_c,n_v,i;
  n_c=malla->n_c;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_TRIANGLES);
	for (i=0;i<n_c;i++){
		if (i%2==0)
			glColor3f(r1,g1,b1);
	   else
	   	glColor3f(r2,g2,b2);  
	
		n_v=malla->car[i].ind_c[0];
		glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
		n_v=malla->car[i].ind_c[1];
		glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
		n_v=malla->car[i].ind_c[2];
		glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
	}
	glEnd();
  
}







//----------------------------------------------

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
//**** usando vertex_array ****
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size()); 

/*int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();*/
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
//**** usando vertex_array ****
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);

/*int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
int i;

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
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	if (i%2==0) glColor3f(r1,g1,b1);
	else glColor3f(r2,g2,b2);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_mode modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	}
}

_cubo::_cubo(float tam)
{
r=0.9; g=0.6; b=0.2;
//vertices
vertices.resize(8);
vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
caras[11]._0=1;caras[11]._1=5;caras[11]._2=4;  
}

//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tapa)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();
vertices.resize(num_aux*num);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras 

for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+((j+1)%num)*num_aux;
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
if (fabs(perfil[0].x)>0.0 && (tapa==1 || tapa==2))
  {
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
 if (fabs(perfil[num_aux-1].x)>0.0 && tapa==1)
  {
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

//************************************************************************
// objeto articulado: grúa
//************************************************************************

_chasis_grua::_chasis_grua()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.5;aux.y=-0.5;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.5;aux.y=0.5;aux.z=0.0;
perfil.push_back(aux);
ruedas.parametros(perfil,12,1);

altura=1.5;
};

void _chasis_grua::draw(_mode modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(8.0,1.0,4.0);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();


glPushMatrix();
glTranslatef(-3.75,-0.25,2.25);
glRotatef(90.0,1,0,0);
glScalef(1.0,0.5,1.0);
ruedas.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-3.75,-0.25,-2.25);
glRotatef(90.0,1,0,0);
glScalef(1.0,0.5,1.0);
ruedas.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(3.75,-0.25,2.25);
glRotatef(90.0,1,0,0);
glScalef(1.0,0.5,1.0);
ruedas.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(3.75,-0.25,-2.25);
glRotatef(90.0,1,0,0);
glScalef(1.0,0.5,1.0);
ruedas.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

}

_cabina::_cabina()
{
	// perfil para un cilindro
	vector<_vertex3f> perfil;
	_vertex3f aux;
	aux.x=2.0;aux.y=-0.5;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=2.0;aux.y=1.5;aux.z=0.0;
	perfil.push_back(aux);
	cabina.parametros(perfil,12,1);

	altura=2.0;
	radio=2.0;
};

void _cabina::draw(_mode modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	cabina.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}


_pieza1::_pieza1()
{
	an1=M_PI/6;
}

void _pieza1::draw(_mode modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	glRotatef(-30.0,0,0,1);
	glScalef(6,1,1);
	brazo1.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

_pieza2::_pieza2()
{
	an2=M_PI/6;
}

void _pieza2::draw(_mode modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();	
	glRotatef(30.0,0,0,1);
	glScalef(9,1,1);
	brazo2.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

_pieza3::_pieza3()
{
	an3=M_PI;
}

void _pieza3::draw(_mode modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();	
	glRotatef(90.0,0,0,1);
	glScalef(6,1,1);
	brazo3.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

_pieza4::_pieza4()
{
	an4=M_PI;
}

void _pieza4::draw(_mode modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();	
	glRotatef(90.0,0,0,1);
	glScalef(5.5,0.6,0.6);
	brazo4.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

_pieza5::_pieza5()
{
	an5=0.0;
}

void _pieza5::draw(_mode modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	glScalef(8,0.6,0.6);
	brazo5.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

_plataforma::_plataforma()
{
// perfil para un cilindro
	vector<_vertex3f> perfil;
	_vertex3f aux;
	aux.x=1.25;aux.y=0.0;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=1.25;aux.y=5.0;aux.z=0.0;
	perfil.push_back(aux);
	plataforma_hueca.parametros(perfil,4,2);

	altura=5.0;
	radio=1.25;
	anp=0.0;
}

void _plataforma::draw(_mode modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	plataforma_hueca.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}


_grua::_grua()
{
	giro_cabina=2.0;
	giro_pieza_2=1.0;
	giro_pieza_3=1.0;
	mov_pieza=1.0;
	giro_plataforma=1.0;

	giro_pieza_min=-9;
	giro_pieza_max=20;
	mov_pieza_min=-1;
  	mov_pieza_max=3;
};

void _grua::draw(_mode modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	int cont=1;
glPushMatrix();
	glLoadName(cont);
chasis_grua.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
	cont++;

glTranslatef(1.5,chasis_grua.altura*2.0/3.0,0.0);
glRotatef(giro_cabina,0,1,0);
glTranslatef(-1.5,-(chasis_grua.altura*2.0/3.0),0.0);
glPushMatrix();
glLoadName(cont);
glTranslatef(1.5,chasis_grua.altura*2.0/3.0,0.0);
cabina.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
cont++;

glPushMatrix();
glLoadName(cont);
glTranslatef(-3.0*cos(brazo1.an1),1.5+3.0*sin(brazo1.an1),0);
brazo1.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
cont++;

glTranslatef(-5.19,4.5,0.0);
glRotatef(giro_pieza_2,0,0,1);
glTranslatef(5.19,-4.5,0.0);
glPushMatrix();
glLoadName(cont);
glTranslatef(-5.16+4.5*cos(brazo2.an2),4.5+4.5*sin(brazo2.an2),0);
brazo2.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
cont++;

glTranslatef(2.6,9.0,0);
glRotatef(giro_pieza_3,0,0,1);
glTranslatef(-2.6,-9.0,0);
glPushMatrix();
glLoadName(cont);
glTranslatef(2.6,12.0,0.0);
brazo3.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
cont++;

glTranslatef(0,mov_pieza,0);
glPushMatrix();
glLoadName(cont);
glTranslatef(2.6,14.5,0.0);
brazo4.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
cont++;

glPushMatrix();
glLoadName(cont);
glTranslatef(-1.0,17.5,0.0);
brazo5.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
cont++;

glTranslatef(-5.4,17.5,0.0);
glRotatef(giro_plataforma,0,0,1);
glTranslatef(5.4,-17.5,0.0);
glPushMatrix();
glLoadName(cont);
glTranslatef(-5.5,16.0,0.0);
plataforma.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
cont++;

};