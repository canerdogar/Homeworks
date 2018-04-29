#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "Vector3.h"
#include "Image.h"
#include <string>
#include <cmath>
#include "Mesh.h"

class Camera {
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

    std::string _outputFile;
    
    int _cid;

public:

    /*
     * BEWARE! You should render each camera by using this function, we will grade it according to regulations!
     */
    Image Rasterize() const;
    
    Camera(const std::vector<Mesh>& _meshes ){
        for (int i=0; i<_meshes.size(); i++) {
            Mesh mesh(_meshes[i]);
            meshes.push_back(mesh);
        }
    }
    
    std::vector <Mesh> meshes;

    void Culling() const;

    void camera() const;

    void projection() const;

    void viewPort() const;

    const std::string& OutputFile() const
    {
        return _outputFile;
    }
    
    friend std::istream& operator>>(std::istream& stream, Camera& camera){
        std::string dummy;
        stream>>dummy;
        stream >> camera._cid >> camera._position >> camera._gaze >> camera._space.Up >> camera._imagePlane.Left >> camera._imagePlane.Right;
        stream>>camera._imagePlane.Bottom >> camera._imagePlane.Top  ;
        stream>> camera._imagePlane.near >>camera._imagePlane.far >> camera._imagePlane.Width >> camera._imagePlane.Height;
        stream>>camera._outputFile;
        
        camera._space.Up.normalize();
        camera._gaze.normalize();
        camera._space.Forward= camera._gaze* -1;
        
        camera._space.Forward.normalize();
        camera._space.Left=camera._space.Up.cross(camera._space.Forward);
        camera._space.Left.normalize();
        
        camera._space.Up=camera._space.Forward.cross(camera._space.Left);
        camera._space.Up.normalize();
        
        return stream;
    }
    
    friend std::ostream& operator<<(std::ostream& stream, const Camera& camera){
        stream << camera._cid <<std::endl;
        stream << camera._position <<camera._gaze << camera._space.Up ;
        stream << camera._imagePlane.Left <<" "<< camera._imagePlane.Right << std::endl;
        stream << camera._imagePlane.Bottom << " "<<camera._imagePlane.Top  << std::endl;
        stream << camera._imagePlane.near << " "<<camera._imagePlane.far << std::endl;
        stream << camera._imagePlane.Width << " " <<camera._imagePlane.Height << std::endl;
        stream << camera._outputFile << std::endl;;
        return stream;
    }

};



#endif //RAYTRACER_CAMERA_H
