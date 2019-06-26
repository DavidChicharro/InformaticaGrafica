//**************************************************************************
// Práctica 4 usando objetos
//**************************************************************************

#include "objetos_p4.h"


// IDENTIFICADOR DE TEXTURA
GLuint textura_id;

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
/*
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size());
*/

	int i;
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
	b_normales_caras=false;
	b_normales_vertices=false;
	b_textura_coord=false;
	ambiente_difusa=_vertex4f(0.3,0.4,0.0,1.0);		//coeficientes ambiente y difuso
	especular=_vertex4f(0.7,0.7,0.7,1.0);
	brillo=40;

	// ruby
	ambiente_difusa_2=_vertex4f(0.6,0.04,0.04,0.55);		//coeficientes ambiente y difuso
	especular_2=_vertex4f(0.727811,0.626959,0.626959,0.55);
	brillo_2=76.8;

	//oro
	/*
	ambiente_difusa=_vertex4f(0.75164,0.60648,0.22648,1.0);		//coeficientes ambiente y difuso
	especular=_vertex4f(0.628281,0.555802,0.366065,1.0);
	brillo=51.2;
	*/

	//generación automática de coords. de textura activada por defecto
	modo_text=true;
		
	/*
	for(int i=0 ; i<4 ; i++){
		plano_s[i] = plano_t[i] = 0.0;
	}
	plano_s[0];
	plano_t[1];*/
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
/*
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);
*/

	int i;
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
// dibujar en modo sólido con textura
//*************************************************************************

void _triangulos3D::draw_textura ( ){
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textura_id);
	
	glVertexPointer(2, GL_FLOAT, 0, &vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, &textura_coord);

	glDrawArrays(GL_QUADS, 0, 4);
	glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	glBegin(GL_TRIANGLES);
	glNormal3f(0.0,0.0,1.0);
	for(int i=0 ; i<caras.size() ; i++){
		glTexCoord2f(textura_coord[caras[i]._0].s,textura_coord[caras[i]._0].t);
		glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
		glTexCoord2f(textura_coord[caras[i]._1].s,textura_coord[caras[i]._1].t);
		glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
		glTexCoord2f(textura_coord[caras[i]._2].s,textura_coord[caras[i]._2].t);
		glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
	}
	glEnd();

	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
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
		case SOLID_ILLUMINATED_FLAT:draw_iluminacion_plana( ); break;
		case SOLID_ILLUMINATED_GOURAUD:draw_iluminacion_suave( ); break;
		case TEXTURE:draw_textura( ); break;
	}
}


//*************************************************************************
// Prepara la imagen para la textura
//*************************************************************************

void prepara_textura (char *archivo){
	std::vector<unsigned char> data;

	CImg<unsigned char> logo(archivo);   
	//logo.load(archivo);
   
	// empaquetamos bien los datos
	for (long y = 0; y < logo.height(); y ++)
		for (long x = 0; x < logo.width(); x ++){
			unsigned char *r = logo.data(x, y, 0, 0);
			unsigned char *g = logo.data(x, y, 0, 1);
			unsigned char *b = logo.data(x, y, 0, 2);
			data.push_back(*r);
			data.push_back(*g);
			data.push_back(*b);
		}

	glGenTextures(1, &textura_id);
	glBindTexture(GL_TEXTURE_2D, textura_id);

	glActiveTexture(GL_TEXTURE0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// TRASFIERE LOS DATOS A GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, logo.width(), logo.height(),
		0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}

//*************************************************************************
// libera la textura
//*************************************************************************

void libera_textura (void)
{
   glDeleteTextures(1, &textura_id);
}

//*************************************************************************
// clase malla
//*************************************************************************

_malla::_malla(int filas, int columnas){
	int tam = (filas+1)*(columnas+1);
	int cont = 0;
	float x=0.3, y=0.3;

	// vertices
	vertices.resize(tam);
	for(int i=0 ; i<=filas ; i++){
		for(int j=0 ; j<=columnas ; j++){
			vertices[cont].x = j*x;
			vertices[cont].y = i*(-y);
			vertices[cont].z = 0.0;

			cont++;
		}
	}

	// caras
	cont=0;
	int lim = ((filas+1)*columnas)-1;

	caras.resize(2*filas*columnas);
	for(int i=0 ; i<lim ; i++)
		if((i+1)%(columnas+1) != 0){
			caras[cont]._0 = i;
			caras[cont]._1 = i + filas + 2;
			caras[cont]._2 = i + 1;

			caras[cont+1]._0 = i;
			caras[cont+1]._1 = i + filas + 1;
			caras[cont+1]._2 = i + filas + 2;

			cont+=2;
		}

	// textura
	textura_coord.resize(vertices.size());
	cont = 0;
	for(int i=0 ; i<=filas ; i++)
		for(int j=0 ; j<=columnas ; j++){
			textura_coord[cont].s = j;
			textura_coord[cont].t = i;
			cont++;
		}
};

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
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


//*************************************************************************
// clase skybox
//*************************************************************************

_skybox::_skybox(float tam){
	//vertices
	vertices.resize(14);
	vertices[0].x=0;vertices[0].y=0;vertices[0].z=0;
	vertices[1].x=tam;vertices[1].y=0;vertices[1].z=0;
	vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=0;
	vertices[3].x=0;vertices[3].y=tam;vertices[3].z=0;
	vertices[4].x=0;vertices[4].y=0;vertices[4].z=tam;
	vertices[5].x=tam;vertices[5].y=0;vertices[5].z=tam;
	vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=tam;
	vertices[7].x=0;vertices[7].y=tam;vertices[7].z=tam;

	vertices[8]=vertices[7];
	vertices[9]=vertices[4];
	vertices[10]=vertices[3];
	vertices[11]=vertices[0];
	vertices[12]=vertices[7];
	vertices[13]=vertices[4];

	// triangulos
	caras.resize(12);
	caras[0]._0=0;caras[0]._1=2;caras[0]._2=1;
	caras[1]._0=0;caras[1]._1=3;caras[1]._2=2;
	caras[2]._0=1;caras[2]._1=6;caras[2]._2=5;
	caras[3]._0=1;caras[3]._1=2;caras[3]._2=6;
	caras[4]._0=4;caras[4]._1=5;caras[4]._2=7;
	caras[5]._0=5;caras[5]._1=6;caras[5]._2=7;
	/*
	caras[6]._0=7;caras[6]._1=6;caras[6]._2=2;
	caras[7]._0=7;caras[7]._1=2;caras[7]._2=3;
	caras[8]._0=4;caras[8]._1=7;caras[8]._2=0;
	caras[9]._0=7;caras[9]._1=3;caras[9]._2=0;
	caras[10]._0=4;caras[10]._1=0;caras[10]._2=5;
	caras[11]._0=0;caras[11]._1=1;caras[11]._2=5;
	*/
	caras[6]._0=8;caras[6]._1=6;caras[6]._2=2;
	caras[7]._0=8;caras[7]._1=2;caras[7]._2=10;
	caras[8]._0=13;caras[8]._1=12;caras[8]._2=0;
	caras[9]._0=12;caras[9]._1=3;caras[9]._2=0;
	caras[10]._0=9;caras[10]._1=11;caras[10]._2=5;
	caras[11]._0=11;caras[11]._1=1;caras[11]._2=5;

	// textura
	textura_coord.resize(14);
	textura_coord[0].s=0.75; textura_coord[0].t=0.5; 
	textura_coord[1].s=0.5; textura_coord[1].t=0.5; 
	textura_coord[2].s=0.5; textura_coord[2].t=0.25; 
	textura_coord[3].s=0.75; textura_coord[3].t=0.25; 
	textura_coord[4].s=0.0; textura_coord[4].t=0.5; 
	textura_coord[5].s=0.25; textura_coord[5].t=0.5; 
	textura_coord[6].s=0.25; textura_coord[6].t=0.25; 
	textura_coord[7].s=0.0; textura_coord[7].t=0.25; 
	textura_coord[8].s=0.25; textura_coord[8].t=0.0; 
	textura_coord[9].s=0.25; textura_coord[9].t=0.75; 
	textura_coord[10].s=0.5; textura_coord[10].t=0.0; 
	textura_coord[11].s=0.5; textura_coord[11].t=0.75; 
	textura_coord[12].s=1.0; textura_coord[12].t=0.25; 
	textura_coord[13].s=1.0; textura_coord[13].t=0.5;
}

_skypyramid::_skypyramid(float tam, float al){
	//vertices 
	vertices.resize(8); 
	vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
	vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
	vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
	vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
	vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;
	vertices[5]=vertices[4];
	vertices[6]=vertices[4];
	vertices[7]=vertices[4];

	// caras
	caras.resize(6);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
	caras[1]._0=1;caras[1]._1=2;caras[1]._2=5;
	caras[2]._0=2;caras[2]._1=3;caras[2]._2=6;
	caras[3]._0=3;caras[3]._1=0;caras[3]._2=7;
	caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
	caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;

	// textura
	textura_coord.resize(8);
	textura_coord[0].s=0.3223; textura_coord[0].t=0.3223; 
	textura_coord[1].s=0.6768; textura_coord[1].t=0.3223; 
	textura_coord[2].s=0.6768; textura_coord[2].t=0.6768; 
	textura_coord[3].s=0.3223; textura_coord[3].t=0.6768; 
	textura_coord[4].s=0.5; textura_coord[4].t=0.0; 
	textura_coord[5].s=1.0; textura_coord[5].t=0.5; 
	textura_coord[6].s=0.5; textura_coord[6].t=1.0; 
	textura_coord[7].s=0.0; textura_coord[7].t=0.5;
}

_abeto::_abeto(float tam, float al){
	//vertices 
	vertices.resize(16); 
	vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
	vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
	vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
	vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
	vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;
	vertices[5]=vertices[4];
	vertices[6]=vertices[4];
	vertices[7]=vertices[4];

	vertices[8].x=-tam;vertices[8].y=(2.0*-al)/3.0;vertices[8].z=tam;
	vertices[9].x=tam;vertices[9].y=(2.0*-al)/3.0;vertices[9].z=tam;
	vertices[10].x=tam;vertices[10].y=(2.0*-al)/3.0;vertices[10].z=-tam;
	vertices[11].x=-tam;vertices[11].y=(2.0*-al)/3.0;vertices[11].z=-tam;
	vertices[12].x=0;vertices[12].y=al/2.0;vertices[12].z=0;
	vertices[13]=vertices[12];
	vertices[14]=vertices[12];
	vertices[15]=vertices[12];


	// caras
	caras.resize(12);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
	caras[1]._0=1;caras[1]._1=2;caras[1]._2=5;
	caras[2]._0=2;caras[2]._1=3;caras[2]._2=6;
	caras[3]._0=3;caras[3]._1=0;caras[3]._2=7;
	caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
	caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;

	caras[6]._0=8;caras[6]._1=9;caras[6]._2=12;
	caras[7]._0=9;caras[7]._1=10;caras[7]._2=13;
	caras[8]._0=10;caras[8]._1=11;caras[8]._2=14;
	caras[9]._0=11;caras[9]._1=8;caras[9]._2=15;
	caras[10]._0=11;caras[10]._1=9;caras[10]._2=8;
	caras[11]._0=11;caras[11]._1=10;caras[11]._2=9;

	// textura
	textura_coord.resize(16);
	textura_coord[0].s=0.0; textura_coord[0].t=1.0; 
	textura_coord[1].s=1.0; textura_coord[1].t=1.0; 
	textura_coord[2].s=0.0; textura_coord[2].t=1.0; 
	textura_coord[3].s=1.1; textura_coord[3].t=1.0; 
	textura_coord[4].s=0.5; textura_coord[4].t=0.0; 
	textura_coord[5].s=0.5; textura_coord[5].t=0.0; 
	textura_coord[6].s=0.5; textura_coord[6].t=0.0; 
	textura_coord[7].s=0.5; textura_coord[7].t=0.0;

	textura_coord[8].s=0.0; textura_coord[8].t=1.0; 
	textura_coord[9].s=1.0; textura_coord[9].t=1.0; 
	textura_coord[10].s=0.0; textura_coord[10].t=1.0; 
	textura_coord[11].s=1.1; textura_coord[11].t=1.0; 
	textura_coord[12].s=0.5; textura_coord[12].t=0.0; 
	textura_coord[13].s=0.5; textura_coord[13].t=0.0; 
	textura_coord[14].s=0.5; textura_coord[14].t=0.0; 
	textura_coord[15].s=0.5; textura_coord[15].t=0.0;
	
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
// clase cilindro
//*************************************************************************

_cilindro::_cilindro(float radio, float altura/*, int num_lados*/){
  //_rotacion rotacion;

  vertices.resize(2);
  vertices[0].x=radio;  vertices[0].y=0;       vertices[0].z=0;
  vertices[1].x=radio;  vertices[1].y=altura;  vertices[1].z=0;

  for(unsigned i=0 ; i<vertices.size() ; i++)
    perfil.push_back(vertices[i]);
  

  parametros(perfil,10);
}


//*************************************************************************
// clase esfera
//*************************************************************************

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

//*************************************************************************
// clase esfera
//*************************************************************************

_cono::_cono(float radio, float altura){
	parametros_cono(radio, altura, 30);
}


//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
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
	if (fabs(perfil[0].x)>0.0)
	  {
		_vertex3f vertice_inferior;
		vertice_inferior.x=0;
		vertice_inferior.y=perfil[0].y;
		vertice_inferior.z=0;

		vertices.push_back(vertice_inferior);
		for(int i=0 ; i<num ; i++){
			cara_aux._0 = i*num_aux;
			cara_aux._1 = vertices.size()-1;
			cara_aux._2 = (num_aux*(i+1))%(num*num_aux);
			caras.push_back(cara_aux);
		}
	}
	 
	// tapa superior
	if (fabs(perfil[num_aux-1].x)>0.0)
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
      cara_aux._0 = i*num_aux;
      cara_aux._1 = vertices.size()-1;
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
    cara_aux._1=(j+1)%num;
    cara_aux._2=j;
    caras.push_back(cara_aux);
  }

  //tapa inferior
  vertice_aux.x=0.0;
  vertice_aux.y=0.0;
  vertice_aux.z=0.0;
  vertices.push_back(vertice_aux);

  for(int i=0 ; i<num ; i++){
    cara_aux._0 = vertices.size()-1;
    cara_aux._1 = i;
    cara_aux._2 = (i+1)%num;
    caras.push_back(cara_aux);
  }
}
