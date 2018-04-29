#ifndef RAYTRACER_MESH_H
#define RAYTRACER_MESH_H

#include <vector>
#include "Vector3.h"
#include "Triangle.h"//yeni ekledin

class Mesh {
public:
    int modelId;
    int modelType;
    std::vector<Triangle> *triangles=NULL;//yeni ekledin
    std::vector<int> transformIds;
    std::vector<string> transformTypes;
    
    friend std::istream& operator>>(std::istream &stream,Mesh& mesh);
    
    friend std::ostream& operator<<(std::ostream &stream,Mesh& mesh){
        stream<<"Model"<<endl;
        vector<Triangle> &triangles = *mesh.triangles;
        for (int i = 0; i < mesh.triangles->size(); ++i)
        {
            stream<< triangles[i];
        }
        return stream;
    }
    
    Mesh(){
        triangles=new std::vector<Triangle>;
    }
    Mesh(const Mesh& rhs): modelId(rhs.modelId),modelType(rhs.modelType)//,triangles(rhs.triangles)
    {
        delete triangles;
        triangles=new std::vector<Triangle>(rhs.triangles->begin(),rhs.triangles->end());
    }
    ~Mesh(){
        delete triangles;
    }
    void set();
};

#endif //RAYTRACER_MESH_H
