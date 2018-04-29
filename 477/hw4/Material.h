#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "Color.h"
#include "Vector3.h"

class Scene;

class Material {
    //////////////////
    /// PUT YOUR VARIABLES, HELPER FUNCTIONS HERE !
    //////////////////
    
public:
    int mid;
    Vector3 _ambient;
    Vector3 _diffuse;
    Vector3 _specular;
    float phong;
    /*
     * Implement a Calculate function that does Diffuse, Specular and Ambient, Reflective shading
     */

    friend std::istream& operator>>(std::istream& stream, Material& mat);
    
    
};


inline std::istream& operator>>(std::istream& stream, Material& mat){
    stream >>mat.mid;
	stream >>mat._ambient;
	stream >>mat._diffuse;
	stream >>mat._specular;
	stream >>mat.phong;
    return stream;
}


#endif //RAYTRACER_MATERIAL_H
