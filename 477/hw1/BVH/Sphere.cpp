#include "Sphere.h"
#include "Scene.h"

//Scene* CurrentScene;//yeni sildin

bool Sphere::Intersect(const Ray& ray, RayHitInfo& hitInfo,int _id) const{

     if(_id!=sphere_id){

        Vector3 center = CurrentScene->Vertices()[center_vid-1].Position();
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
    float minx,maxx,miny,maxy,minz,maxz;
    Vector3 pos=CurrentScene->Vertices()[center_vid-1].Position();
    minx = pos._data[0] - radius;
    maxx = pos._data[0] + radius;
    miny = pos._data[1] - radius;
    maxy = pos._data[1] + radius;
    minz = pos._data[2] - radius;
    maxz = pos._data[2] + radius;
    Surface::mins=Vector3(minx,miny,minz);
    Surface::maxs=Vector3(maxx,maxy,maxz);
    sphere_id=_id;
}


