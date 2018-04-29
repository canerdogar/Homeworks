#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <cstdlib>
#include <vector>
#include "Camera.h"
#include "Mesh.h"
#include "Color.h"
#include <fstream>


using namespace std;

class Scene {

public:
    std::vector<Camera> cameras;
    std::vector<Mesh> meshes;
    std::vector<Color> colors;
    Color background;
    vector<Vector3> pos;
    vector<Vector3> translates;
    vector<Vector3> scales;
    vector<Vector3> rotates;
    vector<float> rotateAngles;

    int numberOfObjects;
    const vector<Camera>& Cameras()const;
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
    file>>CurrentScene -> background;
    
    string dummy;
    int counter;
    
    file>>dummy;
    file >>counter;
    
    file >> dummy;
    for (int i=0; i<counter; i++) {
        Color color;
        file >> color;
        CurrentScene->colors.push_back(color);
    }
    
    file>>dummy;
    for (int i=0; i<counter; i++) {
        Vector3 pos;
        file >> pos;
        CurrentScene->pos.push_back(pos);
    }
    
    file >> dummy;
    file >> counter;
    for (;counter>0;counter--)
    {
        Vector3 ts;
        file>> ts;
        CurrentScene->translates.push_back(ts);
    }


    file>>dummy;
    file>>counter;
    for (;counter>0;counter--)
    {
        Vector3 scs;
        file>>scs;
        CurrentScene->scales.push_back(scs);
    }
    
    file>>dummy;
    file>>counter;
    for (;counter>0;counter--)
    {
        Vector3 rs;
        float angle;

        file>>angle;
        file>>rs;
        
        CurrentScene->rotates.push_back(rs);
        CurrentScene->rotateAngles.push_back(angle);
         
    }

    
    file >> dummy;
    file >> counter;
    for (;counter>0;counter--){
        Mesh mesh;
        file >> mesh;
        CurrentScene->meshes.push_back(mesh);
    }
    file.close();

    /*for (int i=0; i<CurrentScene->meshes.size(); i++) {
        cout<< CurrentScene -> meshes[i] ;
    }*/
    
    ifstream camfile(argv[2],ifstream::in);
    camfile>>counter;
    for(;counter>0;counter--){
        Camera camera(CurrentScene->meshes);
        camfile>>camera;
        //cout<< camera ;
        CurrentScene->cameras.push_back(camera);
    }
    camfile.close();

}


#endif //RAYTRACER_SCENE_H
