#include "Triangle.h"
#include "Scene.h"
#include <algorithm>

using namespace std;

bool Triangle::Intersect(const Ray& ray, RayHitInfo& hitInfo,int _id) const{

    
   

    if(tid!=_id){
        
        Vector3 direction=ray.Direction();
        Vector3 origin=ray.Origin();
        float j=c2._data[0] - origin._data[0];
        float k=c2._data[1] - origin._data[1];
        float l=c2._data[2] - origin._data[2];
        
        float g=direction._data[0];
        float h=direction._data[1];
        float i=direction._data[2];
        
        float ei_hf=(e*i - h*f);
        float gf_hi=(g*f - d*i);
        float dh_eg=(d*h - e*g);
        float ak_jb=(a*k - j*b);
        float jc_al=(j*c - a*l);
        float bl_kc=(b*l - k*c);
        float M= a* ei_hf + b* gf_hi + c* dh_eg;
        
        float gama=(i* ak_jb + h* jc_al + g* bl_kc)/M;
        if(gama<0 || gama>1){
            return false;
        }
        float beta=(j* ei_hf + k* gf_hi + l* dh_eg)/M;
        if(beta<0 || beta > 1-gama){
            return false;
        }
        float t= - (f* ak_jb + e* jc_al + d* bl_kc)/M;
        if(t<hitInfo.Parameter && t>0){
            //cout<<"everything is fine until here"<<endl;
            hitInfo.Parameter=t;
            hitInfo.Position=origin+ (direction*t);
            hitInfo.Normal=normal;
            hitInfo.Material=mid;
            hitInfo.oid=tid;
            hitInfo.uv=uv(beta,gama);//yeni ekledin
            hitInfo.tex=texture;//yeni ekledin
            hitInfo.sid=sid;
	    //cout<<"triangle sid: "<<hitInfo.sid<<endl;
            return true;
        }

    }
    return false;
}

void Triangle::nofleaves()const{
    std::cout<<type()<<std::endl;
}


void Triangle::set_id(int i){
    tid=i;
}

void Triangle::set_normal(){
    normal=((c3-c2).cross(c1-c2)).normalize();
    a=c2[0]-c3[0];
    b=c2[1]-c3[1];
    c=c2[2]-c3[2];
    d=c2[0]-c1[0];
    e=c2[1]-c1[1];
    f=c2[2]-c1[2];
    float bbminx, bbminy, bbminz, bbmaxx, bbmaxy, bbmaxz;
    bbminx = min(min(c1[0], c2[0]), c3[0]);
    bbminy = min(min(c1[1], c2[1]), c3[1]);
    bbminz = min(min(c1[2], c2[2]), c3[2]);
    bbmaxx = max(max(c1[0], c2[0]), c3[0]);
    bbmaxy = max(max(c1[1], c2[1]), c3[1]);
    bbmaxz = max(max(c1[2], c2[2]), c3[2]);
    if (bbmaxx == bbminx) {
        bbmaxx += 0.001;
    }
    if (bbmaxy == bbminy) {
        bbmaxy += 0.001;
    }
    if (bbmaxz == bbminz) {
        bbmaxz += 0.001;
    }
    Surface::mins=Vector3(bbminx,bbminy,bbminz);
    Surface::maxs=Vector3(bbmaxx,bbmaxy,bbmaxz);
}

/*void Triangle::set_corners(int c1_id,int c2_id,int c3_id){

    c1=CurrentScene->Vertices()[c1_id-1].Position();
    c2=CurrentScene->Vertices()[c2_id-1].Position();
    c3=CurrentScene->Vertices()[c3_id-1].Position();
    
}*/


float* Triangle::uv(const float& beta,const float& gama)const{
    float* uv=new float[2];
    uv[0]=uv[1]=0;
    //u=ua + beta * (ub - ua) + gama * (uc - ua);
   /*if(sid==1){
	uv[0]=0 +  gama * (1.0/3.0);//
	uv[1]=(1.0/2.0) + beta * (1.0/2.0) + gama * (1.0/2.0);//
    }else if(sid==3){
	uv[0]=(1.0/3.0) + gama * (1.0/3.0);//
	uv[1]=(1.0/2.0) + beta * (1.0/2.0) + gama * (1.0/2.0);//
    }else if(sid==5){
	uv[0]=(2.0/3.0) + gama * (1.0/3.0);//
	uv[1]=(1.0/2.0) + beta * (1.0/2.0) + gama * (1.0/2.0);//
    }
    else if(sid==7){
	uv[0]=0 + gama * (1.0/3.0);//
	uv[1]=0 + beta * (1.0/2.0) + gama * (1.0/2.0);//
    }
    else if(sid==11){
	uv[0]=(1.0/3.0) + gama * (1.0/3.0);//
	uv[1]=0 + beta * (1.0/2.0) + gama * (1.0/2.0);//
    }
    else if(sid==9){
	uv[0]=(2.0/3.0) + gama * (1.0/3.0);//
	uv[1]=0 + beta * (1.0/2.0) + gama * (1.0/2.0);//
    }
    else if(sid==2){
	uv[0]=0 + beta * (1.0/3.0) + gama * (1.0/3.0);//
	uv[1]=(1.0/2.0) + beta * (1.0/2.0);//
    }
    else if(sid==4){
	uv[0]=(1.0/3.0) + beta * (1.0/3.0) + gama * (1.0/3.0);//
        uv[1]=(1.0/2.0) + beta * (1.0/2.0);//
    }
    else if(sid==6){
	uv[0]=(2.0/3.0) + beta * (1.0/3.0) + gama * (1.0/3.0);//
	uv[1]=(1.0/2.0) + beta * (1.0/2.0);//
    }
    else if(sid==8){
	uv[0]=0 + beta * (1.0/3.0) + gama * (1.0/3.0);//
	uv[1]=beta * (1.0/2.0);//
    }
    else if(sid==12){
	uv[0]=(1.0/3.0) + beta * (1.0/3.0) + gama * (1.0/3.0);//
	uv[1]=beta * (1.0/2.0);//
    }
    else if(sid==10){
	uv[0]=(2.0/3.0) + beta * (1.0/3.0) + gama * (1.0/3.0);//
	uv[1]=beta * (1.0/2.0);//
    }
	//uv[1]=0.5;
	//cout<<uv[0]<<" "<<uv[1]<<endl;
	
    
	//cout<<sid<<" "<<beta<<" "<<gama<<endl;*/
    
    
    
    if( sid%2 == 1 ){//alttaki
        uv[0]= beta ;
        uv[1]=  1 - gama;
    }
    else{//ustteki
        uv[0]= 1 - gama;
        uv[1]=1 - beta - gama;
    }
    return uv;
}

void Triangle::Translate(const Vector3& vector){

    c1= c1 + vector;
    c2= c2 + vector;
    c3= c3 + vector; 

    //y.Print();
    //x.Print();
    //cout<<radius<<endl;

}

void Triangle::Scale(const Vector3& vector){
    c1= c1- center;
    c2= c2- center;
    c3= c3- center;
    c1=Vector3(c1[0]*vector[0],c1[1]*vector[1],c1[2]*vector[2]);
    c2=Vector3(c2[0]*vector[0],c2[1]*vector[1],c2[2]*vector[2]);
    c3=Vector3(c3[0]*vector[0],c3[1]*vector[1],c3[2]*vector[2]);
    center=Vector3(center[0]*vector[0],center[1]*vector[1],center[2]*vector[2]);
    c1= c1+ center;
    c2= c2+ center;
    c3= c3+ center;
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

    center=Vector3(center[0]*a1 + center[1]*a2 + center[2]*a3,
                   center[0]*b1 + center[1]*b2 + center[2]*b3, 
                   center[0]*d1 + center[1]*d2 + center[2]*d3);


 }
