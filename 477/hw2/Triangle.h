#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H

#include "Ray.h"
#include "Surface.h"
#include <string>
#include "Texture.h"

using namespace std;

class Triangle : public Surface
{
public:
    // This function gets a ray, and if the triangle intersects with the ray, returns true and fills the hitInfo struct
    // Else return false and leave hitInfo unchanged
    Vector3 normal;
    Vector3 c1,c2,c3;
    Vector3 center;
    Texture* texture=NULL;
    int tid,mid;
    int sid;
    float a,b,c,d,e,f;
    Triangle(const Vector3& _c1,const Vector3& _c2,const Vector3& _c3){
        c1=_c1;
        c2=_c2;
        c3=_c3;
        center= (c1+c2+c3) / 3;
    }
    bool Intersect(const Ray& ray, RayHitInfo& hitInfo,int _id) const;
    
    void set_normal();
    
    void set_id(int i);
    
    void nofleaves()const;
    
    /*friend std::istream& operator>>(std::istream& stream,Triangle& triangle){
        int c1_id,c2_id,c3_id;
        stream >>c1_id>>c2_id>>c3_id;
        //triangle.set_corners(c1_id,c2_id,c3_id);
        triangle.set_normal();
        triangle.a=triangle.c2._data[0] - triangle.c3._data[0];
        triangle.b=triangle.c2._data[1] - triangle.c3._data[1];
        triangle.c=triangle.c2._data[2] - triangle.c3._data[2];
        
        triangle.d=triangle.c2._data[0] - triangle.c1._data[0];
        triangle.e=triangle.c2._data[1] - triangle.c1._data[1];
        triangle.f=triangle.c2._data[2] - triangle.c1._data[2];

        return stream;
    }*/

    friend std::ostream& operator<<(std::ostream& stream,Triangle& triangle)
    {

        stream<<"Triangle "<<triangle.tid<<" materialid "<<triangle.mid<<endl;
        stream<<"c1:"<<triangle.c1[0]<<" "<<triangle.c1[1]<<" "<<triangle.c1[2]<<endl;
        stream<<"c2:"<<triangle.c2[0]<<" "<<triangle.c2[1]<<" "<<triangle.c2[2]<<endl;
        stream<<"c3:"<<triangle.c3[0]<<" "<<triangle.c3[1]<<" "<<triangle.c3[2]<<endl;
        stream<<"center:"<<triangle.center[0]<<" "<<triangle.center[1]<<" "<<triangle.center[2]<<endl;
        if(triangle.texture!=NULL){
            stream<<"texture var"<<endl;
        }
        return stream;

    }

    string type()const{
        return "T-> "+ to_string(tid);
    }
    
    //void set_corners(int c1_id,int c2_id,int c3_id);

    float* uv(const float& beta,const float& gama)const;

    void Translate(const Vector3& vector);

    void Scale(const Vector3& vector);

    void Rotate(const float& angle,const Vector3& vector);
};

#endif //RAYTRACER_TRIANGLE_H

