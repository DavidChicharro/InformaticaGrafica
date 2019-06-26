#include "objetos_p4.h"


//*************************************************************************
// normales a las caras para la iluminación plana
//*************************************************************************

void _triangulos3D::calcular_normales_caras(){
	normales_caras.resize(caras.size());

	for(unsigned long i=0 ; i<caras.size() ; i++){
		//obtener dos vectores en el triángulo y calcular el producto vectorial
		_vertex3f
			a1=vertices[caras[i]._1] - vertices[caras[i]._0],
			a2=vertices[caras[i]._2] - vertices[caras[i]._0],
			n=a1.cross_product(a2);

		// modulo
		float m=sqrt(n.x*n.x + n.y*n.y + n.z*n.z);

		// normalización
		normales_caras[i] = _vertex3f(n.x/m, n.y/m, n.z/m);
	}

	b_normales_caras=true;
}


//*************************************************************************
// normales a los vértices para la iluminación suave
//*************************************************************************

void _triangulos3D::calcular_normales_vertices(){
	int i, j;
	if(b_normales_vertices==false){
		if(b_normales_caras==false)
			calcular_normales_caras();
		
		normales_vertices.resize(vertices.size());
		
		for(i=0 ; i<vertices.size() ; i++){
			normales_vertices[i].x=0.0;
			normales_vertices[i].y=0.0;
			normales_vertices[i].z=0.0;
		}
		for(i=0 ; i<caras.size() ; i++){
			normales_vertices[caras[i]._0] += normales_caras[i];
			normales_vertices[caras[i]._1] += normales_caras[i];
			normales_vertices[caras[i]._2] += normales_caras[i];
		}
		for(j=0 ; j<vertices.size() ; j++)
			normales_vertices[j].normalize();

		b_normales_vertices=true;
	}
}

template <class T>
void ordenar(vector<T> v){
	T aux;
	for (int i=0 ; i<v.size()-1 ; i++){
	   for (int j=i+1 ; j<v.size() ; j++){
			if(v[i].x > v[j].x){
		     	aux = v[i];
		     	v[i] = v[j];
		     	v[j] = aux;
	    	}
	  	}
	}
}

//*************************************************************************
// dibujar en modo iluminación plana
//*************************************************************************

void _triangulos3D::draw_iluminacion_plana( ) {
	int i;
	GLfloat ambient_component[4]={1,1,1,1};

	if(b_normales_caras==false)
		calcular_normales_caras();

	//glEnable(GL_CULL_FACE)
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_component);	// proporciona brillo
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glShadeModel(GL_FLAT);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat*) &ambiente_difusa);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat*) &especular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat*) &brillo);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);

	// Para ver mitad y mitad
	for(i=0 ; i<caras.size() ; i++){
		glNormal3fv((GLfloat *) &normales_caras[i]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}

	glEnd();
	glDisable(GL_LIGHTING);
	//glDisable(GL_CULL_FACE);
}


//*************************************************************************
// dibujar en modo iluminación suave
//*************************************************************************

void _triangulos3D::draw_iluminacion_suave( ) {
	int i;
	GLfloat ambient_component[4] = {1,1,1,1};

    if(b_normales_vertices==false)
        calcular_normales_vertices();

    //glEnable(GL_CULL_FACE);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_component);	// proporciona brillo
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glShadeModel(GL_SMOOTH);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); 
  	glEnable(GL_LIGHT1); 
    glEnable(GL_NORMALIZE);
	
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat *) &brillo);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);


    for(i=0 ; i<caras.size() ; i++){
    	glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }

    glEnd();
    glDisable(GL_LIGHTING);
    //glDisable(GL_CULL_FACE);
}



//*************************************************************************
// luz
//*************************************************************************

luz::luz(GLenum p_luz_ind, _vertex4f p_luz_punto, _vertex4f p_luz_ambiente,
			_vertex4f p_luz_difusa, _vertex4f p_luz_especular){
	//Asignar parámetros de luz
	luz_ind=p_luz_ind;

	luz_punto=p_luz_punto;
	luz_ambiente=p_luz_ambiente;
	luz_difusa=p_luz_difusa;
	luz_especular=p_luz_especular;
}

void luz::activar(){
	glEnable(GL_LIGHTING);
	glEnable(luz_ind);

	glLightfv(luz_ind, GL_AMBIENT, (GLfloat*) &luz_ambiente);
	glLightfv(luz_ind, GL_DIFFUSE, (GLfloat*) &luz_difusa);
	glLightfv(luz_ind, GL_SPECULAR, (GLfloat*) &luz_especular);
	glLightfv(luz_ind, GL_POSITION, (GLfloat*) &luz_punto);
}

void luz::desactivar(){
	glDisable(luz_ind);
}

void luz::transformar(GLenum p_luz_ind, float ang, int a, int b, int c,
										float x, float y, float z){
	glPushMatrix();
	glRotatef(ang,a,b,c);
	glTranslatef(x,y,z);
	glLightfv(p_luz_ind, GL_POSITION, (GLfloat*) &luz_punto);
	glPopMatrix();
}