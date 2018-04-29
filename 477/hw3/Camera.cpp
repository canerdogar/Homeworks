#include "Camera.h"
#include "Scene.h"
#include <math.h>

Image Camera::Rasterize() const{

	//cout<<_imagePlane.Width<<" "<<_imagePlane.Height<<endl;

    Image image(_imagePlane.Width,_imagePlane.Height,CurrentScene->background);

    Culling();

    camera();

    projection();

    viewPort();

    for(int i=0; i< meshes.size(); i++){

		for (int j = 0; j < meshes[i].triangles->size(); j++)
		{

			if(!meshes[i].triangles->operator[](j).culled){
				meshes[i].triangles->operator[](j).draw(image,meshes[i].modelType);
			}


		}

	}

	
    return image;
}

void Camera::Culling()const{

	for(int i=0; i< meshes.size(); i++){

		for (int j = 0; j < meshes[i].triangles->size(); j++)
		{
			Vector3 w(meshes[i].triangles->operator[](j).center[0]-_position[0],
						meshes[i].triangles->operator[](j).center[1]-_position[1],
						meshes[i].triangles->operator[](j).center[2]-_position[2]);

			w.normalize();

			if(w.dot(meshes[i].triangles->operator[](j).normal) > 0){

				meshes[i].triangles->operator[](j).culled=true;

			}
		}

	}

}

void Camera::camera()const{

	float a,b,d;

	a= - (_space.Left[0] * _position[0] + _space.Left[1] * _position[1] + _space.Left[2] * _position[2]);

	b= - (_space.Up[0] * _position[0] + _space.Up[1] * _position[1] + _space.Up[2] * _position[2]);

	d= - (_space.Forward[0] * _position[0] + _space.Forward[1] * _position[1] + _space.Forward[2] * _position[2]);

	for(int i=0; i< meshes.size(); i++){

		for (int j = 0; j < meshes[i].triangles->size(); j++)
		{

				Vector3 result;

				//c1

				Vector3 c=meshes[i].triangles->operator[](j).c1;

				result[0]=c[0] *  _space.Left[0] + c[1] *  _space.Left[1] + c[2] *  _space.Left[2] + a;

				result[1]=c[0] *  _space.Up[0] + c[1] *  _space.Up[1] + c[2] *  _space.Up[2] + b;

				result[2]=c[0] *  _space.Forward[0] + c[1] *  _space.Forward[1] + c[2] *  _space.Forward[2] + d;

				meshes[i].triangles->operator[](j).c1 = result;

				//c2

				c=meshes[i].triangles->operator[](j).c2;

				result[0]=c[0] *  _space.Left[0] + c[1] *  _space.Left[1] + c[2] *  _space.Left[2] + a;

				result[1]=c[0] *  _space.Up[0] + c[1] *  _space.Up[1] + c[2] *  _space.Up[2] + b;

				result[2]=c[0] *  _space.Forward[0] + c[1] *  _space.Forward[1] + c[2] *  _space.Forward[2] + d;

				meshes[i].triangles->operator[](j).c2 = result;

				//c3

				c=meshes[i].triangles->operator[](j).c3;

				result[0]=c[0] *  _space.Left[0] + c[1] *  _space.Left[1] + c[2] *  _space.Left[2] + a;

				result[1]=c[0] *  _space.Up[0] + c[1] *  _space.Up[1] + c[2] *  _space.Up[2] + b;

				result[2]=c[0] *  _space.Forward[0] + c[1] *  _space.Forward[1] + c[2] *  _space.Forward[2] + d;

				meshes[i].triangles->operator[](j).c3 = result;


		}

	}	

}

void Camera::projection()const{

	float a,b,c,d,e,f;

	a= (2.0* _imagePlane.near) / (_imagePlane.Right - _imagePlane.Left);

	b= (_imagePlane.Right + _imagePlane.Left) / (_imagePlane.Right - _imagePlane.Left);

	c= (2.0* _imagePlane.near) / (_imagePlane.Top - _imagePlane.Bottom);

	d= (_imagePlane.Top + _imagePlane.Bottom) / (_imagePlane.Top - _imagePlane.Bottom);

	e= - (_imagePlane.far + _imagePlane.near) / (_imagePlane.far - _imagePlane.near);

	f= - (2.0* _imagePlane.near * _imagePlane.far) / (_imagePlane.far - _imagePlane.near);

	for(int i=0; i< meshes.size(); i++){

		for (int j = 0; j < meshes[i].triangles->size(); j++)
		{

			Vector3 result;

			Vector3 bozmaca;

			//c1

			Vector3 h=meshes[i].triangles->operator[](j).c1;

			result[0]= h[0] * a + h[2] *b ;

			result[1]= h[1] * c + h[2] *d ;

			bozmaca[0]=result[2]= h[2] * e + f ;

			meshes[i].triangles->operator[](j).c1 = result / (- h[2]);

			meshes[i].triangles->operator[](j).c1[2] = bozmaca[0];

			//c2

			h=meshes[i].triangles->operator[](j).c2;

			result[0]= h[0] * a + h[2] *b ;

			result[1]= h[1] * c + h[2] *d ;

			bozmaca[1]=result[2]= h[2] * e + f ;

			meshes[i].triangles->operator[](j).c2 = result / (- h[2]);

			meshes[i].triangles->operator[](j).c2[2] = bozmaca[1];

			//c3

			h=meshes[i].triangles->operator[](j).c3;

			result[0]= h[0] * a + h[2] *b ;

			result[1]= h[1] * c + h[2] *d ;

			bozmaca[2]=result[2]= h[2] * e + f ;

			meshes[i].triangles->operator[](j).c3 = result / (- h[2]);

			meshes[i].triangles->operator[](j).c3[2] = bozmaca[2];

		}

	}



}

void Camera::viewPort()const{

	float a,b;

	a=_imagePlane.Width / 2.0;

	b=_imagePlane.Height / 2.0;

	for(int i=0; i< meshes.size(); i++){

		for (int j = 0; j < meshes[i].triangles->size(); j++)
		{

			Vector3 result;

			//c1

			Vector3 c=meshes[i].triangles->operator[](j).c1;

			result[0]= round(c[0] * a + a);

			result[1]= round( _imagePlane.Height - (c[1] * b + b) );

			result[2]=   (c[2] / 2.0) + (1.0 / 2.0) ;

			meshes[i].triangles->operator[](j).c1=result;

			//c2

			c=meshes[i].triangles->operator[](j).c2;

			result[0]= round(c[0] * a + a);

			result[1]= round( _imagePlane.Height - (c[1] * b + b) );

			result[2]=   (c[2] / 2.0) + (1.0 / 2.0) ;

			meshes[i].triangles->operator[](j).c2=result;

			//c3

			c=meshes[i].triangles->operator[](j).c3;

			result[0]= round(c[0] * a + a);

			result[1]= round( _imagePlane.Height - (c[1] * b + b) );

			result[2]=   (c[2] / 2.0) + (1.0 / 2.0) ;

			meshes[i].triangles->operator[](j).c3=result;

		}

	}


}