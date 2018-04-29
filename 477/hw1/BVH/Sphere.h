#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Ray.h"
#include "Surface.h"
#include "Vector3.h"
#include <string>

using namespace std;

class Sphere :public Surface{

public:
    // This function gets a ray, and if the sphere intersects with the ray, returns true and fills the hitInfo struct
    // Else return false and leave hitInfo unchanged
    int sphere_id,material_id,center_vid;
    float radius;

    bool Intersect(const Ray& ray, RayHitInfo& hitInfo,int _id) const;
    
    friend std::istream& operator>>(std::istream& stream,Sphere& sphere){
        stream>> sphere.sphere_id >>sphere.material_id >> sphere.radius >> sphere.center_vid;
        return stream;
    }
    
    friend std::ostream& operator<<(std::ostream& stream,Sphere& sphere){
        stream<< sphere.sphere_id << std::endl;
        stream<< sphere.material_id << std::endl;
        stream<< sphere.radius << std::endl;
        stream << sphere.center_vid << std::endl;
        return stream;
    }
        
    void set_id(int _id);
    
    string type()const{
        return "S-> "+ to_string(sphere_id);
    }
    
    void nofleaves()const;
    friend class Material;
    friend class Camera;
};


#endif //RAYTRACER_SPHERE_H
