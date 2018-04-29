#include "Triangle.h"
#include "Scene.h"
#include <algorithm>

using namespace std;

bool Triangle::Intersect(const Ray& ray, RayHitInfo& hitInfo,int _id) const{

    //cout<<"everything is fine until here"<<endl;
   

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
            hitInfo.Parameter=t;
            hitInfo.Position=origin+ (direction*t);
            hitInfo.Normal=normal;
            hitInfo.Material=mid;
            hitInfo.oid=tid;
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

void Triangle::set_corners(int c1_id,int c2_id,int c3_id){

    c1=CurrentScene->Vertices()[c1_id-1].Position();
    c2=CurrentScene->Vertices()[c2_id-1].Position();
    c3=CurrentScene->Vertices()[c3_id-1].Position();
    
}


