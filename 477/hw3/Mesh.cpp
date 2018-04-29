#include "Mesh.h"
#include "Scene.h"
#include "Vector3.h"

void Mesh::set(){
    
    for (int i = 0; i < triangles->size(); ++i)
    {
        triangles->operator[](i).setNormal();
    }
}

std::istream& operator>>(std::istream &stream,Mesh& mesh){
    
    stream >> mesh.modelId;
    stream >> mesh.modelType;
    
    int counter=0;
    stream >> counter;
    
    string transformType;
    int transformId;
    for (; counter>0; counter--) {
        stream >> transformType;
        stream >> transformId;
        mesh.transformTypes.push_back(transformType);
        mesh.transformIds.push_back(transformId);
    }
    
    stream>> counter;
    for (; counter>0; counter--) {
        int id1,id2,id3;
        stream >> id1 >> id2 >> id3;
        Triangle triangle(id1,id2,id3);
        mesh.triangles->push_back(triangle);
    }
    
    
    
    for (int i=0;i<mesh.transformTypes.size() ; i++) {
        
        for (int j=0; j< mesh.triangles->size(); j++) {
            
            if(mesh.transformTypes[i].compare("s")==0){
                mesh.triangles->operator[](j).Scale(CurrentScene->scales[mesh.transformIds[i] - 1]);
            }else if(mesh.transformTypes[i].compare("t")==0){
                mesh.triangles->operator[](j).Translate(CurrentScene->translates[mesh.transformIds[i] - 1]);
            }else{
                mesh.triangles->operator[](j).Rotate(CurrentScene->rotateAngles[mesh.transformIds[i] - 1] , CurrentScene-> rotates[mesh.transformIds[i] - 1]);
            }
            
        }
        
        
    }

    mesh.set();
    
    return stream;
}
