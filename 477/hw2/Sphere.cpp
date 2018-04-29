#include "Sphere.h"
#include "Scene.h"

//Scene* CurrentScene;//yeni sildin
#define one_over_2pi .159154943092f
#define one_over_pi  .318309886184f
#define twopi        6.28318530718f
# define M_PI           3.14159265358979323846  /* pi */


bool Sphere::Intersect(const Ray& ray, RayHitInfo& hitInfo,int _id) const{

     if(_id!=sphere_id){

        //Vector3 vector(1.5,1.5,1.5);
        Vector3 d=ray.Direction();
        Vector3 e=ray.Origin();
        Vector3 e_minus_c=e-center;
        //e_minus_c.normalize();
        
        float a=d.dot(d);
        float b = d.dot(e_minus_c) *2;
        float c = e_minus_c.dot(e_minus_c) - radius * radius ;
        float disc = b*b - a*c*4 ;
        //std::cout<<"sphere id: "<<sphere_id <<",disc: " <<disc <<std::endl;
        /*std::cout<<"Sphere center:"<<std::endl;
         center.Print();*/
        
        if(disc<0){
            return false;
        }else{
            float sqrt_disc = sqrt(disc);
            float t2 = (-b - sqrt_disc) / (2*a) ;
            if(t2<hitInfo.Parameter && t2>0){
                hitInfo.Parameter=t2;
                hitInfo.Material=material_id;
                Vector3 intersection=e + d*hitInfo.Parameter;//e_minus_c + d*hitInfo.Parameter idi
                hitInfo.Position= intersection;
                hitInfo.Normal=  (intersection - center ).normalize();//(intersection - center ) / radius idi
                hitInfo.oid=sphere_id;
                hitInfo.tex=tex;
                hitInfo.uv=uv(intersection);
                hitInfo.sid=0;
                return true;
            }
            return false;
        }

    }
    return false;
    
}

void Sphere::nofleaves()const{
    std::cout<<type()<<std::endl;
}


void Sphere::set_id(int _id){
    sphere_id=_id;
}

void Sphere::set_box(){
    float minx,maxx,miny,maxy,minz,maxz;
    minx = center._data[0] - radius;
    maxx = center._data[0] + radius;
    miny = center._data[1] - radius;
    maxy = center._data[1] + radius;
    minz = center._data[2] - radius;
    maxz = center._data[2] + radius;
    Surface::mins=Vector3(minx,miny,minz);
    Surface::maxs=Vector3(maxx,maxy,maxz);

}

float* Sphere::uv(Vector3 point)const{

   

    Vector3 wcpy=(point-center).normalize();//tamam

    float theta = acos( (y-center).normalize().dot(wcpy)     );

    //Vector3 pcpy=( (point-center)*  sin( (double)theta ) ).normalize();


    Vector3 pcpy =( (point-center).normalize() - ( (y-center).normalize() *  (point-center).normalize().dot((y-center).normalize()) )    ).normalize();

    //acosun ici <=-1 ise fi=pi >=1 ise fi=0

    float angle=(x-center).normalize().dot(pcpy) ;
    float fi;
    if(angle<= -1){
        fi=M_PI;
    }else if(angle>=1){
        fi=0;
    }else{
        fi    = acos( (x-center).normalize().dot(pcpy)     );
    }



    /*float theta = acos( (point[1]-center[1]) / ((point-center).length()) );
    float fi = (float) atan2( ( (double) point[2]- (double) center[2]) , ( (double) point[0]- (double) center[0]) ) ;*/


    //std::cout<<theta<<" "<<fi<<std::endl;

    float u=(M_PI - fi)  / (2* M_PI)  ; 
    float v=1- ((M_PI - theta) / M_PI );
    float* uv=new float[2];
    uv[0]=u;uv[1]=v;

    return uv;

}

void Sphere::Translate(const Vector3& vector){

    center= center + vector;
    y= y + vector;
    x= x + vector; 

    //y.Print();
    //x.Print();
    //cout<<radius<<endl;

}

void Sphere::Scale(const Vector3& vector){

    radius=radius * vector[0];

    y = ( (y - center) * vector[0] ) + center;

    x = ( (x - center) * vector[0] ) + center;

   //y.Print();

   // x.Print();
}

void Sphere::Rotate(const float& angle,const Vector3& vector){
    Vector3 rs=vector;
    rs.normalize();

    float angle4=(angle * 3.14159265358979323846) / 180;

    /*float d= sqrt( rs[1] * rs[1] + rs[2] * rs[2]);

    float angle2=acos( rs[2] / d );//alpha
    float angle3=acos( d );//beta

    c1=Vector3(c1[0],c1[1]*cos(angle2) - c1[2]*sin(angle2),c1[1]*sin(angle2) + c1[2]*cos(angle2));
    c2=Vector3(c2[0],c2[1]*cos(angle2) - c2[2]*sin(angle2),c2[1]*sin(angle2) + c2[2]*cos(angle2));
    c3=Vector3(c3[0],c3[1]*cos(angle2) - c3[2]*sin(angle2),c3[1]*sin(angle2) + c3[2]*cos(angle2));
    center=Vector3(center[0],center[1]*cos(angle2) - center[2]*sin(angle2),center[1]*sin(angle2) + center[2]*cos(angle2));//tamam

    c1=Vector3(c1[0]*cos(angle3) + c1[2]*sin(angle3),c1[1],( c1[0] * -1  * sin(angle3) ) + (c1[2] * cos(angle3)) );
    c2=Vector3(c2[0]*cos(angle3) + c2[2]*sin(angle3),c2[1],( c2[0] * -1  * sin(angle3) ) + (c2[2] * cos(angle3)) );
    c3=Vector3(c3[0]*cos(angle3) + c3[2]*sin(angle3),c3[1],( c3[0] * -1  * sin(angle3) ) + (c3[2] * cos(angle3)) );
    center=Vector3(center[0]*cos(angle3) + center[2]*sin(angle3),center[1],( center[0] * -1  * sin(angle3) ) + (center[2] * cos(angle3)) );//tamam

    c1=Vector3(c1[0] * cos(angle4) - c1[1] * sin(angle4) , c1[0] * sin(angle4) + c1[1] * cos(angle4) , c1[2]);
    c2=Vector3(c2[0] * cos(angle4) - c2[1] * sin(angle4) , c2[0] * sin(angle4) + c2[1] * cos(angle4) , c2[2]);
    c3=Vector3(c3[0] * cos(angle4) - c3[1] * sin(angle4) , c3[0] * sin(angle4) + c3[1] * cos(angle4) , c3[2]);
    center=Vector3(center[0] * cos(angle4) - center[1] * sin(angle4) , center[0] * sin(angle4) + center[1] * cos(angle4) , center[2]);//tamam

    c1=Vector3(c1[0]*cos(-angle3) + c1[2]*sin(-angle3),c1[1],( c1[0] * -1  * sin(-angle3) ) + (c1[2] * cos(-angle3)) );
    c2=Vector3(c2[0]*cos(-angle3) + c2[2]*sin(-angle3),c2[1],( c2[0] * -1  * sin(-angle3) ) + (c2[2] * cos(-angle3)) );
    c3=Vector3(c3[0]*cos(-angle3) + c3[2]*sin(-angle3),c3[1],( c3[0] * -1  * sin(-angle3) ) + (c3[2] * cos(-angle3)) );
    center=Vector3(center[0]*cos(-angle3) + center[2]*sin(-angle3),center[1],( center[0] * -1  * sin(-angle3) ) + (center[2] * cos(-angle3)) );

    c1=Vector3(c1[0],c1[1]*cos(-angle2) - c1[2]*sin(-angle2),c1[1]*sin(-angle2) + c1[2]*cos(-angle2));
    c2=Vector3(c2[0],c2[1]*cos(-angle2) - c2[2]*sin(-angle2),c2[1]*sin(-angle2) + c2[2]*cos(-angle2));
    c3=Vector3(c3[0],c3[1]*cos(-angle2) - c3[2]*sin(-angle2),c3[1]*sin(-angle2) + c3[2]*cos(-angle2));
    center=Vector3(center[0],center[1]*cos(-angle2) - center[2]*sin(-angle2),center[1]*sin(-angle2) + center[2]*cos(-angle2));*/


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





    y=Vector3(y[0]*a1 + y[1]*a2 + y[2]*a3,
               y[0]*b1 + y[1]*b2 + y[2]*b3, 
               y[0]*d1 + y[1]*d2 + y[2]*d3);

    x=Vector3(x[0]*a1 + x[1]*a2 + x[2]*a3,
               x[0]*b1 + x[1]*b2 + x[2]*b3, 
               x[0]*d1 + x[1]*d2 + x[2]*d3);

    center=Vector3(center[0]*a1 + center[1]*a2 + center[2]*a3,
                   center[0]*b1 + center[1]*b2 + center[2]*b3, 
                   center[0]*d1 + center[1]*d2 + center[2]*d3);


 }