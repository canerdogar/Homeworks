#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include <utility>
#include "Vector3.h"
#include <cmath>
#include "Texture.h"

using namespace std;

class Ray {
    Vector3 _origin;
    Vector3 _direction;

public:
    Ray(const Vector3& origin, const Vector3& direction) : _origin(origin), _direction(direction) {}

    const Vector3 &Origin() const {
        return _origin;
    }

    const Vector3 &Direction() const {
        return _direction;
    }
};

/////////////////
// BEWARE !
// When an intersection occurs, this struct should be filled !
/////////////////

struct RayHitInfo
{
    int         Material;
    Vector3     Position;
    Vector3     Normal;
    int         oid;
    Texture*    tex=NULL;
    float*      uv=NULL;
    int         sid=-1;
    
    float       Parameter=INFINITY;
};

#endif //RAYTRACER_RAY_H
