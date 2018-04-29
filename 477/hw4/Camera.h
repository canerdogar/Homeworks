#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "Vector3.h"
#include <cmath>

class Camera {

public:
    struct {
        Vector3 Forward, Up, Left;
    } _space;

    struct {
        float Left, Right, Bottom, Top;
        float near,far;
        
        int Width;
        int Height;

    } _imagePlane;

    Vector3 _position;
    Vector3 _gaze;

    
    friend std::istream& operator>>(std::istream& stream, Camera& camera){
        stream >> camera._position >> camera._gaze >> camera._space.Up >> camera._imagePlane.Left >> camera._imagePlane.Right;
        stream>>camera._imagePlane.Bottom >> camera._imagePlane.Top  ;
        stream>> camera._imagePlane.near >>camera._imagePlane.far >> camera._imagePlane.Width >> camera._imagePlane.Height;
        camera._gaze.normalize();
        camera._space.Forward=camera._gaze * -1;
        camera._space.Left=camera._space.Up.cross(camera._space.Forward).normalize();
        camera._space.Up=camera._space.Forward.cross(camera._space.Left).normalize();
        
        return stream;
    }
    
    friend std::ostream& operator<<(std::ostream& stream, const Camera& camera){
        stream << camera._position <<camera._gaze << camera._space.Up ;
        stream << camera._imagePlane.Left <<" "<< camera._imagePlane.Right << std::endl;
        stream << camera._imagePlane.Bottom << " "<<camera._imagePlane.Top  << std::endl;
        stream << camera._imagePlane.near << " "<<camera._imagePlane.far << std::endl;
        stream << camera._imagePlane.Width << " " <<camera._imagePlane.Height << std::endl;
        return stream;
    }

};



#endif //RAYTRACER_CAMERA_H
