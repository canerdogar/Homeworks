#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>
#include "Camera.h"
#include "Sphere.h"
#include "Mesh.h"
#include "Color.h"
#include "PointLight.h"
#include "Vertex.h"
#include <fstream>
#include "BVHNode.h"

using namespace std;

class Scene {

    std::vector<Vertex> _vertices;

    std::vector<Camera> _cameras;
    std::vector<Sphere*> _spheres;
    std::vector<Mesh*>   _meshes;
    std::vector<Surface*> _objects;
    std::vector<Material> _materials;

    std::vector<PointLight> _lights;

    
    Color _background;
    Color _ambient;
    
    
    

public:
    BVHNode* root;
    int numberOfObjects;
    int _rayReflect;
    const std::vector<Camera>& Cameras() const;
    const std::vector<Sphere*>& Spheres() const;
    const std::vector<Mesh*>& Meshes() const;
    
    const std::vector<Surface*>& Objects() const;
    
    const std::vector<Vertex>& Vertices() const;
    const std::vector<Material>& Materials() const;
    const std::vector<PointLight>& Lights() const;
    Color get_background() const;
    Color get_ambient() const;
    int get_numberOfObjects()const;
    
    
    //////////////////////////////
    // READ SCENE FUNCTIONS HERE !
    //////////////////////////////
    
    friend void ReadScene(int argc, char** argv);
};

extern Scene* CurrentScene;

inline void ReadScene(int argc, char** argv)
{
    /*
     * Reads the scene and cameras from arguments
     * Then sets the CurrentScene pointer
     */
    
    ifstream file(argv[1],ifstream::in);
    CurrentScene=new Scene();
    file >> CurrentScene -> _rayReflect;
    file>>CurrentScene -> _background;
    file>>CurrentScene -> _ambient;
    
    //cout<< CurrentScene -> _background.R() <<" " <<CurrentScene -> _background.G() <<" " <<CurrentScene -> _background.B()<<endl;
    //cout<< CurrentScene -> _ambient.R() <<" " <<CurrentScene -> _ambient.G() <<" " <<CurrentScene -> _ambient.B()<<endl;
    
    int counter;
    file >>counter;
    //cout<<"counter: "<<counter<<endl;
    for(;counter>0;counter--){
        PointLight pl;
        file>>pl;
        CurrentScene->_lights.push_back(pl);
    }
    
    /*for(int counter=0;counter<CurrentScene->_lights.size();counter++){
     cout<< CurrentScene ->_lights[counter]._position._data[0] <<" " << CurrentScene ->_lights[counter]._position._data[1] <<" " << CurrentScene ->_lights[counter]._position._data[2]<<endl;
     cout<< CurrentScene ->_lights[counter]._intensity._data[0] <<" " << CurrentScene ->_lights[counter]._intensity._data[1] <<" " << CurrentScene ->_lights[counter]._intensity._data[2]<<endl;
     }*/
    
    file>>counter;
    //cout<<"material counter: "<<counter<<endl;
    for(;counter>0;counter--){
        Material material;
        file >>material;
        CurrentScene->_materials.push_back(material);
    }
    
    /*for (int i=0; i<CurrentScene->_materials.size(); i++) {
     cout<< "mid: "<<CurrentScene->_materials[i].get_mid()<<endl;
     cout<< "ambient: "<<CurrentScene->_materials[i].get_ambient();
     cout<< "diffuse: "<<CurrentScene->_materials[i].get_diffuse();
     cout<< "specular: "<<CurrentScene->_materials[i].get_specular();
     cout<< "phong: "<<CurrentScene->_materials[i].get_phong()<<endl;
     cout<< "reflectance: "<<CurrentScene->_materials[i].get_reflectance();
     }*/
    
    file>>counter;
    //cout<<"vertex counter: "<<counter<<endl;
    string dummy;
    file>>dummy;
    file>>dummy;
    for(;counter>0;counter--){
        Vertex vertex;
        file>>vertex;
        CurrentScene->_vertices.push_back(vertex);
    }
    
    
    file>>CurrentScene->numberOfObjects;
    string type;
    //cout<<"model counter: "<<CurrentScene->numberOfObjects<<endl;
    int j=0;
    for(int i=0;i<CurrentScene->numberOfObjects;i++){
        file>>type;
        if(type=="#Mesh"){
            int triangle_count,material_id;
            file>>triangle_count;
            file>>triangle_count;
            file>>material_id;
            for(int k=0;k<triangle_count;k++){
                Triangle* triangle=new Triangle();
                file >> *triangle;
                triangle->mid=material_id;
                triangle->set_id(j++);
                CurrentScene->_objects.push_back(triangle);
                //triangle->c1.Print();
                //triangle->c2.Print();
                //triangle->c3.Print();
            }
        }
        else if(type=="#Sphere"){
            Sphere* sphere=new Sphere();
            file>> *sphere;
            sphere->set_id(j++);
            CurrentScene->_objects.push_back(sphere);
        }
        
    }
    
    CurrentScene->numberOfObjects=j;
    /*cout<<"numberOfSpheres: "<<CurrentScene->_spheres.size()<<endl;
     for (int i=0; i<CurrentScene->_spheres.size(); i++) {
     cout<< CurrentScene->_spheres[i];
     }*/
    
    file.close();
    ifstream camfile(argv[2],ifstream::in);
    
    camfile>>counter;
    for(;counter>0;counter--){
        Camera camera;
        camfile>>camera;
        CurrentScene->_cameras.push_back(camera);
    }
    
    //cout<<"numberOfCameras: "<<CurrentScene->_cameras.size()<<endl;
    /*for (int i=0; i<CurrentScene->_cameras.size(); i++) {
     cout<< CurrentScene->_cameras[i];
     }*/
    
    camfile.close();
    
    /*for (const auto& mesh:CurrentScene->Meshes()) {
        for (const auto& triangle:mesh.Triangles()) {
            std::cout<<triangle._id<<std::endl;
        }
    }
    for (const auto& sphere:CurrentScene->Spheres()) {
        std::cout<<sphere.sphere_id<<std::endl;
    }*/
    
    //std::cout<<CurrentScene->Objects().size()<<std::endl;
    
    /*for(const auto& object:CurrentScene->Objects()){
        std::cout<<object->type()<<std::endl;
    }*/
    
    ///std::cout<<"j-> "<<j<<std::endl;
    //std::cout<<CurrentScene->_objects.size()<<std::endl;
    CurrentScene->root=new BVHNode(CurrentScene->_objects,0);//EKSİİİİİİİİİİİİİİİİİİİİİİİİK
    
    //std::cout<<"number-> "<<
    //CurrentScene->root->nofleaves();//<<std::endl;
}


#endif //RAYTRACER_SCENE_H
