#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "Color.h"
#include "Vector3.h"

class Scene;

class Material {
    //////////////////
    /// PUT YOUR VARIABLES, HELPER FUNCTIONS HERE !
    //////////////////
    int mid;
    Vector3 _ambient;
    Vector3 _diffuse;
    Vector3 _specular;
    float phong;
    Vector3 _reflectance;
public:

    /*
     * Implement a Calculate function that does Diffuse, Specular and Ambient, Reflective shading
     */

    friend std::istream& operator>>(std::istream& stream, Material& mat);
    const Vector3& get_ambient()const{
        return _ambient;
    }
    const Vector3& get_diffuse()const{
        return _diffuse;
    }
    const Vector3& get_specular()const{
        return _specular;
    }
    const Vector3& get_reflectance()const{
        return _reflectance;
    }
    float get_phong()const{
        return phong;
    }
    int get_mid()const{
        return mid;
    }
    Color calculate(int count,const Vector3& intersection_point,const Vector3& normal,const Vector3& wo,int oid)const;
};

using MaterialId = int;

inline std::istream& operator>>(std::istream& stream, Material& mat){
    std::string dummy;
    stream >>dummy;
    stream >>mat.mid;stream >>mat._ambient;stream >>mat._diffuse;stream >>mat._specular;stream >>mat.phong;stream >>mat._reflectance;
    return stream;
}


#endif //RAYTRACER_MATERIAL_H
