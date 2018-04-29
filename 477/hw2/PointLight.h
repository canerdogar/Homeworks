#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H

#include "Vector3.h"

class PointLight {
public:
    Vector3 _position;
    Vector3 _intensity;
};
inline std::istream &operator>>(std::istream &stream, PointLight& pointlight) {
    stream >> pointlight._position;
    stream >> pointlight._intensity;
    return stream;
};

#endif //RAYTRACER_POINTLIGHT_H
