#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "Vector3.h"
#include "Image.h"
#include <string>
#include <cmath>

class Camera {
    struct {
        Vector3 Forward, Up, Left;
    } _space;

    struct {
        float Left, Right, Bottom, Top;
        float Distance;

        int Width;
        int Height;

    } _imagePlane;

    Vector3 _position;
    Vector3 _gaze;

    std::string _outputFile;
    
    int _cid;

public:

    /*
     * BEWARE! You should render each camera by using this function, we will grade it according to regulations!
     */
    Image Render() const;

    const std::string& OutputFile() const
    {
        return _outputFile;
    }
    
    friend std::istream& operator>>(std::istream& stream, Camera& camera){
        std::string dummy;
        stream>>dummy;
        stream >> camera._cid >> camera._position >> camera._gaze >> camera._space.Up >> camera._imagePlane.Left >> camera._imagePlane.Right;
        stream>>camera._imagePlane.Bottom >> camera._imagePlane.Top  >> camera._imagePlane.Distance >> camera._imagePlane.Width >> camera._imagePlane.Height;
        stream>>camera._outputFile;
        
        camera._space.Up.normalize();
        //camera._gaze.normalize();
        camera._space.Forward= camera._gaze* -1;
        camera._space.Forward.normalize();
        camera._space.Left=camera._space.Up.cross(camera._space.Forward);
        camera._space.Left.normalize();
        
        /*camera._space.Up.Print();
        camera._space.Forward.Print();
        camera._space.Left.Print();*/
        
        return stream;
    }
    
    friend std::ostream& operator<<(std::ostream& stream, const Camera& camera){
        stream << camera._cid << std::endl<<camera._position << camera._gaze << camera._space.Up << camera._imagePlane.Left << camera._imagePlane.Right;
        stream<<camera._imagePlane.Bottom << camera._imagePlane.Top  << camera._imagePlane.Distance << camera._imagePlane.Width << camera._imagePlane.Height;
        stream<<camera._outputFile;
        return stream;
    }

};

/*Image Camera::Render() const{
    Image image(_imagePlane.Width,_imagePlane.Height);
    return image;
}*/

#endif //RAYTRACER_CAMERA_H
