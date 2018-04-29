#include "Triangle.h"
#include "Scene.h"
#include <algorithm>
#include "Color.h"
#include <math.h>

using namespace std;


float Triangle::f(float x,float y,float x0,float y0,float x1,float y1)const{

    return x * (y0-y1)+ y * (x1-x0) + (x0 * y1) - (y0 * x1); 

}



void Triangle::draw(Image& image,const int& type)const{

    
    if(type == 1){

        int xmin = std::min(std::min(c1[0],c2[0]),c3[0]);
        int ymin = std::min(std::min(c1[1],c2[1]),c3[1]);
        int xmax = std::max(std::max(c1[0],c2[0]),c3[0]);
        int ymax = std::max(std::max(c1[1],c2[1]),c3[1]);

        float gama=0,alpha=0,beta=0;

        for (int y = ymin; y < ymax; ++y)
         {
             for (int x = xmin; x < xmax; ++x)
             {
                 alpha=f(x,y,c2[0],c2[1],c3[0],c3[1])/f(c1[0],c1[1],c2[0],c2[1],c3[0],c3[1]);
                 beta=f(x,y,c3[0],c3[1],c1[0],c1[1])/f(c2[0],c2[1],c3[0],c3[1],c1[0],c1[1]);
                 gama=f(x,y,c1[0],c1[1],c2[0],c2[1])/f(c3[0],c3[1],c1[0],c1[1],c2[0],c2[1]);

                 if (alpha>=0 && beta>=0 && gama>=0)
                 {

                    float zvalue=(c1[2] * alpha) + (c2[2] * beta) + (c3[2] * gama);

                    if (image.zBuffer(y,x)>  zvalue ){

                        image.zBuffer(y,x)=zvalue;

                        Color color= (color1 * alpha) + (color2 * beta) + (color3 * gama); 
                    
                        image.Pixel(y,x)= color;

                    }
   
                 }
             
             }
         } 

    }else {

         /*cout<<"geldi"<<endl;
         c1.Print();
         c2.Print();
         c3.Print();*/
        lineDraw(image,c1,c2,color1,color2);

        lineDraw(image,c2,c3,color2,color3);

        lineDraw(image,c3,c1,color3,color1);

        //cout<<"cikti"<<endl;
       
    }
}




void Triangle::lineDraw(Image& image,const Vector3& v1,const Vector3& v2,const Color& c1,const Color& c2)const{

    float slope=(v2[1] - v1[1]) / (v2[0]-v1[0]);

    float r=c1.R(),g=c1.G(),b=c1.B();

    float z= v1[2];

    //cout<<"girdi"<<endl;

    if(0< slope && slope <1){

        //cout<<"0<slope<1"<<endl;

        int y = v1[1];

        if(v1[0]<v2[0]){//tamam

            //cout<<"x1<x2"<<endl;

            float d= (v1[1] - v2[1]) + 0.5 * (v2[0]-v1[0]);


            float dr=( c2.R()-c1.R() ) / (v2[0] - v1[0]);
            float dg=( c2.G()-c1.G() ) / (v2[0] - v1[0]);
            float db=( c2.B()-c1.B() ) / (v2[0] - v1[0]);
            float dz=( v2[2]-v1[2] ) / (v2[0] - v1[0]);

            for (int x = v1[0]; x < v2[0]; ++x)
            {

                if (image.zBuffer(y,x)>  z ){

                    image.zBuffer(y,x)=z;

                    image.Pixel(y,x)=Color(r,g,b);
                
                }

                if(d<0){
                    y++;
                    d+= (v1[1]-v2[1]) + (v2[0]-v1[0]);
                }else
                    d+=(v1[1]-v2[1]);

                r+=dr;
                g+=dg;
                b+=db;
                z+=dz;

            }

        }else{//tamam

            //cout<<"x1>x2"<<endl;

            float d= -(v1[1] - v2[1]) - 0.5 * (v2[0]-v1[0]);

            float dr=( c2.R()-c1.R() ) / -(v2[0] - v1[0]);
            float dg=( c2.G()-c1.G() ) / -(v2[0] - v1[0]);
            float db=( c2.B()-c1.B() ) / -(v2[0] - v1[0]);
            float dz=( v2[2]-v1[2] ) / -(v2[0] - v1[0]);

            for (int x = v1[0]; x > v2[0]; --x)
            {
                if (image.zBuffer(y,x)>  z ){

                    image.zBuffer(y,x)=z;

                    image.Pixel(y,x)=Color(r,g,b);
                
                }

                if(d<0){
                    y--;
                    d+= -(v1[1]-v2[1]) - (v2[0]-v1[0]);
                }else
                    d+=-(v1[1]-v2[1]);

                r+=dr;
                g+=dg;
                b+=db;
                z+=dz;

            }

        }

        

    }else if(slope>1){

        //cout<<"slope>1"<<endl;

        int x = v1[0];

        if(v1[0]<v2[0]){//tamam

            //cout<<"x1<x2"<<endl;

            float d= 0.5 * (v1[1] - v2[1]) +  (v2[0]-v1[0]);

            float dr=( c2.R()-c1.R() ) / (v2[1] - v1[1]);
            float dg=( c2.G()-c1.G() ) / (v2[1] - v1[1]);
            float db=( c2.B()-c1.B() ) / (v2[1] - v1[1]);
            float dz=( v2[2]-v1[2] ) / (v2[1] - v1[1]);

            for (int y = v1[1]; y < v2[1]; ++y)
            {
                if (image.zBuffer(y,x)>  z ){

                    image.zBuffer(y,x)=z;

                    image.Pixel(y,x)=Color(r,g,b);
                
                }
                if(d>0){
                    x++;
                    d+= (v1[1]-v2[1]) + (v2[0]-v1[0]);
                }else
                    d+=(v2[0]-v1[0]);

                r+=dr;
                g+=dg;
                b+=db;
                z+=dz;

            }

        }else{//tamam

            //cout<<"x1>x2"<<endl;

            float d= -0.5 * (v1[1] - v2[1]) -  (v2[0]-v1[0]);

            float dr=( c2.R()-c1.R() ) / -(v2[1] - v1[1]);
            float dg=( c2.G()-c1.G() ) / -(v2[1] - v1[1]);
            float db=( c2.B()-c1.B() ) / -(v2[1] - v1[1]);
            float dz=( v2[2]-v1[2] ) / -(v2[1] - v1[1]);

            for (int y = v1[1]; y > v2[1]; --y)
            {
                if (image.zBuffer(y,x)>  z ){

                    image.zBuffer(y,x)=z;

                    image.Pixel(y,x)=Color(r,g,b);
                
                }

                if(d>0){
                    x--;
                    d+= -(v1[1]-v2[1]) - (v2[0]-v1[0]);
                }else
                    d+= -(v2[0]-v1[0]);

                r+=dr;
                g+=dg;
                b+=db;
                z+=dz;

            }

        }

        

    }else if(slope < -1){

        //cout<<"slope<-1"<<endl;

        int x = v1[0];

        if(v1[0]<v2[0]){//tamam

            //cout<<"x1<x2"<<endl;

            float d= 0.5*(v1[1] - v2[1]) -  (v2[0]-v1[0]);

            float dr=( c2.R()-c1.R() ) / -(v2[1] - v1[1]);
            float dg=( c2.G()-c1.G() ) / -(v2[1] - v1[1]);
            float db=( c2.B()-c1.B() ) / -(v2[1] - v1[1]);
            float dz=( v2[2]-v1[2] ) / -(v2[1] - v1[1]);

            for (int y = v1[1]; y > v2[1]; --y)
            {
                if (image.zBuffer(y,x)>  z ){

                    image.zBuffer(y,x)=z;

                    image.Pixel(y,x)=Color(r,g,b);
                
                }

                if(d<0){
                    x++;
                    d+= (v1[1]-v2[1]) - (v2[0]-v1[0]);
                }else
                    d+=-(v2[0]-v1[0]);

                r+=dr;
                g+=dg;
                b+=db;
                z+=dz;
            }   

        }else{//tamam

            //cout<<"x1>x2"<<endl;

            float d= -0.5*(v1[1] - v2[1]) +  (v2[0]-v1[0]);

            float dr=( c2.R()-c1.R() ) / (v2[1] - v1[1]);
            float dg=( c2.G()-c1.G() ) / (v2[1] - v1[1]);
            float db=( c2.B()-c1.B() ) / (v2[1] - v1[1]);
            float dz=( v2[2]-v1[2] ) / (v2[1] - v1[1]);
            for (int y = v1[1]; y < v2[1]; ++y)
            {
                if (image.zBuffer(y,x)>  z ){

                    image.zBuffer(y,x)=z;

                    image.Pixel(y,x)=Color(r,g,b);
                
                }
                if(d<0){
                    x--;
                    d+= -(v1[1]-v2[1]) + (v2[0]-v1[0]);
                }else
                    d+= (v2[0]-v1[0]);

                r+=dr;
                g+=dg;
                b+=db;
                z+=dz;
            }  

        }


    }else if(-1<slope && slope<0){

        //cout<<"-1<slope<0"<<endl;

        int y = v1[1];

        if(v1[0]<v2[0]){//tamam

            //cout<<"x1<x2"<<endl;

            float d= (v1[1] - v2[1]) - 0.5 * (v2[0]-v1[0]);

            float dr=( c2.R()-c1.R() ) / (v2[0] - v1[0]);
            float dg=( c2.G()-c1.G() ) / (v2[0] - v1[0]);
            float db=( c2.B()-c1.B() ) / (v2[0] - v1[0]);
            float dz=( v2[2]-v1[2] ) / (v2[0] - v1[0]);

            for (int x = v1[0]; x < v2[0]; ++x)
            {
                if (image.zBuffer(y,x)>  z ){

                    image.zBuffer(y,x)=z;

                    image.Pixel(y,x)=Color(r,g,b);
                
                }

                if(d>0){
                    y--;
                    d+= (v1[1]-v2[1]) - (v2[0]-v1[0]);
                }else
                    d+= (v1[1]-v2[1]);

                r+=dr;
                g+=dg;
                b+=db;
                z+=dz;

            }

        }else{//tamam

            //cout<<"x1>x2"<<endl;

            float d= -(v1[1] - v2[1]) + 0.5 * (v2[0]-v1[0]);

            float dr=( c2.R()-c1.R() ) / -(v2[0] - v1[0]);
            float dg=( c2.G()-c1.G() ) / -(v2[0] - v1[0]);
            float db=( c2.B()-c1.B() ) / -(v2[0] - v1[0]);
            float dz=( v2[2]-v1[2] ) / -(v2[0] - v1[0]);

            for (int x = v1[0]; x > v2[0]; --x)
            {
                if (image.zBuffer(y,x)>  z ){

                    image.zBuffer(y,x)=z;

                    image.Pixel(y,x)=Color(r,g,b);
                
                }

                if(d>0){
                    y++;
                    d+= -(v1[1]-v2[1]) + (v2[0]-v1[0]);
                }else
                    d+= -(v1[1]-v2[1]);

                r+=dr;
                g+=dg;
                b+=db;
                z+=dz;


            }

        }

    }

}


void Triangle::setNormal(){
    center= (c1 + c2 + c3) / 3 ;
    z[0]=c1[2];z[1]=c2[2];z[2]=c3[2];
    normal=((c3-c2).cross(c1-c2)).normalize();
}

void Triangle::setCorners(int _c1,int _c2,int _c3){

    c1=CurrentScene->pos[_c1-1];
    c2=CurrentScene->pos[_c2-1];
    c3=CurrentScene->pos[_c3-1];
    
}

void Triangle::setColors(int _c1,int _c2,int _c3){
    
    color1=CurrentScene->colors[_c1-1];
    color2=CurrentScene->colors[_c2-1];
    color3=CurrentScene->colors[_c3-1];
    
}



void Triangle::Translate(const Vector3& vector){

    c1= c1 + vector;
    c2= c2 + vector;
    c3= c3 + vector;
}

void Triangle::Scale(const Vector3& vector){
    c1=Vector3(c1[0]*vector[0],c1[1]*vector[1],c1[2]*vector[2]);
    c2=Vector3(c2[0]*vector[0],c2[1]*vector[1],c2[2]*vector[2]);
    c3=Vector3(c3[0]*vector[0],c3[1]*vector[1],c3[2]*vector[2]);
 }

 void Triangle::Rotate(const float& angle,const Vector3& vector){
    Vector3 rs=vector;
    rs.normalize();

    float angle4=(angle * 3.14159265358979323846) / 180;

    
    float a1,a2,a3,b1,b2,b3,d1,d2,d3;
    float _cos=cos(angle4),_sin=sin(angle4);
    a1=_cos + rs[0] * rs[0] * (1 - _cos);
    a2=rs[0]* rs[1] * (1- _cos) - rs[2] * _sin ;
    a3=rs[0] * rs[2] * (1- _cos) + rs[1] * _sin ;

    b1=rs[1]*rs[0]*(1-_cos) + rs[2]*_sin;
    b2=_cos + rs[1]*rs[1] * (1-_cos);
    b3=rs[1]*rs[2]*(1-_cos) - rs[0] * _sin;

    d1=rs[2]*rs[0]*(1-_cos) - rs[1] * _sin;
    d2=rs[2]*rs[1]*(1-_cos) + rs[0] * _sin;
    d3=_cos + rs[2] * rs[2] * (1- _cos);





    c1=Vector3(c1[0]*a1 + c1[1]*a2 + c1[2]*a3,
               c1[0]*b1 + c1[1]*b2 + c1[2]*b3, 
               c1[0]*d1 + c1[1]*d2 + c1[2]*d3);

    c2=Vector3(c2[0]*a1 + c2[1]*a2 + c2[2]*a3,
               c2[0]*b1 + c2[1]*b2 + c2[2]*b3, 
               c2[0]*d1 + c2[1]*d2 + c2[2]*d3);

    c3=Vector3(c3[0]*a1 + c3[1]*a2 + c3[2]*a3,
               c3[0]*b1 + c3[1]*b2 + c3[2]*b3, 
               c3[0]*d1 + c3[1]*d2 + c3[2]*d3);


 }
