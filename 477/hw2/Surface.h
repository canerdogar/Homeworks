#ifndef surface_h
#define surface_h

#include "Ray.h"
#include "Vector3.h"
#include <string>
using namespace std;
class Surface{
    public:
    Vector3 mins,maxs;
    virtual bool Intersect(const Ray& ray, RayHitInfo& hitInfo,int _id) const =0; // override by subclasses
    virtual string type()const=0;
    virtual void nofleaves()const=0;
    virtual ~Surface(){} // constructor
    bool box_intersect(const Ray& ray)const{
        float txmin,txmax,tymin,tymax;
        
        float a=1/ray.Direction()[0];
        if(a>=0){
            txmin=a*(mins[0]-ray.Origin()[0]);
            txmax=a*(maxs[0]-ray.Origin()[0]);
        }else{
            txmin=a*(maxs[0]-ray.Origin()[0]);
            txmax=a*(mins[0]-ray.Origin()[0]);
        }
        
        a=1/ray.Direction()[1];
        if(a>=0){
            tymin=a*(mins[1]-ray.Origin()[1]);
            tymax=a*(maxs[1]-ray.Origin()[1]);
        }else{
            tymin=a*(maxs[1]-ray.Origin()[1]);
            tymax=a*(mins[1]-ray.Origin()[1]);
        }
        
        if(txmin>tymax || tymin> txmax){
            return false;
        }
        
        float tzmin,tzmax;
        
        a=1/ray.Direction()[2];
        if(a>=0){
            tzmin=a*(mins[2]-ray.Origin()[2]);
            tzmax=a*(maxs[2]-ray.Origin()[2]);
        }else{
            tzmin=a*(maxs[2]-ray.Origin()[2]);
            tzmax=a*(mins[2]-ray.Origin()[2]);
        }
        
        if(txmin > tzmax || tzmin > txmax){
            return false;
        }
        if(tymin>tzmax || tzmin > tymax){
            return false;
        }
        
        return true;
        
    }
};

#endif /* surface_h */