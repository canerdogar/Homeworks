#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H

#include "Ray.h"
#include "Surface.h"
#include <string>

using namespace std;

class Triangle : public Surface
{
public:
    // This function gets a ray, and if the triangle intersects with the ray, returns true and fills the hitInfo struct
    // Else return false and leave hitInfo unchanged
    Vector3 normal;
    Vector3 c1,c2,c3;
    int tid,mid;
    float a,b,c,d,e,f;
    bool Intersect(const Ray& ray, RayHitInfo& hitInfo,int _id) const;
    
    void set_normal();
    
    void set_id(int i);
    
    void nofleaves()const;
    
    friend std::istream& operator>>(std::istream& stream,Triangle& triangle){
        int c1_id,c2_id,c3_id;
        stream >>c1_id>>c2_id>>c3_id;
        triangle.set_corners(c1_id,c2_id,c3_id);
        triangle.set_normal();
        triangle.a=triangle.c2._data[0] - triangle.c3._data[0];
        triangle.b=triangle.c2._data[1] - triangle.c3._data[1];
        triangle.c=triangle.c2._data[2] - triangle.c3._data[2];
        
        triangle.d=triangle.c2._data[0] - triangle.c1._data[0];
        triangle.e=triangle.c2._data[1] - triangle.c1._data[1];
        triangle.f=triangle.c2._data[2] - triangle.c1._data[2];

        return stream;
    }

    string type()const{
        return "T-> "+ to_string(tid);
    }
    
    void set_corners(int c1_id,int c2_id,int c3_id);
};

#endif //RAYTRACER_TRIANGLE_H

