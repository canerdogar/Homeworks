#ifndef RAYTRACER_MESH_H
#define RAYTRACER_MESH_H

#include <vector>
#include "Vector3.h"
#include "Triangle.h"//yeni ekledin

class Mesh {
public:
    int material_id;
    int start_number;
    
    //std::vector<Vector3> _vertices;//comment attın
    std::vector<Triangle*> _triangles;//yeni ekledin

    
    friend std::istream& operator>>(std::istream &stream,Mesh& mesh);
    
    friend std::ostream& operator<<(std::ostream &stream,Mesh& mesh){
        stream<<"Cube"<<endl;
        for (int i = 0; i < mesh._triangles.size(); ++i)
        {
            stream<< *mesh._triangles[i];
        }
        return stream;
    }

    const std::vector<Triangle*>& Triangles() const {
        return _triangles;
    }
    
    void start_numbering(int from){
        start_number=from;
    }
    
    void set(){

        for (int i = 0; i < _triangles.size(); ++i)
        {
            _triangles[i]->set_normal();
        }
    }

    /*friend std::ostream& operator<<(std::ostream &stream,Mesh& mesh){
        stream <<"#Mesh "<<mesh.mesh_id;
        stream<< mesh.triangle_count<<std::endl;
        stream<<mesh.material_id<<std::endl;
        for(int i=0;i<mesh.triangle_count;i++){
            stream<<mesh._vertices[i];
        }
        return stream;
    }*/

};

#endif //RAYTRACER_MESH_H
