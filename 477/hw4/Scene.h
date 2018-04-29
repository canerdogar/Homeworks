#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <cstdlib>
#include <vector>
#include "Camera.h"
#include "Mesh.h"
#include "Color.h"
#include <fstream>
#include "PointLight.h"
#include "Material.h"

using namespace std;

class Scene {

public:
	std::vector<Vector3> translates;
	std::vector<Vector3> scales;
	std::vector<Vector3> rotates;
	std::vector<float> rotateAngles;
	std::vector<Mesh> meshes;
    std::vector<PointLight> lights;
    std::vector<Material> materials;
	Camera camera;
	GLfloat* vertexPos=NULL;
	GLfloat background[4]={0,0,0,1.0};
	GLfloat ambient[4]={0,0,0,1.0};
    Vector3* normals=NULL;
    GLfloat* normalValues=NULL;
    int howmany;
    //////////////////////////////
    // READ SCENE FUNCTIONS HERE !
    //////////////////////////////
    
    friend void ReadScene(int argc, char** argv);
};

extern Scene* CurrentScene;





inline void ReadScene(int argc, char** argv)
{

    CurrentScene=new Scene();
    ifstream file(argv[1],ifstream::in);
    file>>CurrentScene->background[0];
    file>>CurrentScene->background[1];
    file>>CurrentScene->background[2];
    //cout<<CurrentScene->background[0]<<" "<<CurrentScene->background[1]<<" "<<CurrentScene->background[2]<<endl;
    file>>CurrentScene->ambient[0];
    file>>CurrentScene->ambient[1];
    file>>CurrentScene->ambient[2];
    //cout<<CurrentScene->ambient[0]<<" "<<CurrentScene->ambient[1]<<" "<<CurrentScene->ambient[2]<<endl;
    
    int counter;
 	char dummy;
 	float dummyi;

    file >>counter;//lights
    //cout<<counter<<endl;
    for (int i=0; i<counter; i++) {
    	for (int i = 0; i < 6; ++i)
	    {
	        file>>dummy;
	    }
    	file>>dummyi;
        //cout<<dummyi<<endl;

    	PointLight light;
        file>>light;
        CurrentScene->lights.push_back(light);
    }

	file>> counter;//materials
    for (int i=0; i<counter; i++) {
        for (int i = 0; i < 9; ++i)
	    {
	        file>>dummy;
            //cout<<dummy;
	    }//cout<<endl;
        Material m;
        file>>m;
        CurrentScene->materials.push_back(m); 	
    }
    
    for (int i = 0; i < 13; ++i)
    {
        file>>dummy;
        //cout<<dummy;
    }//cout<<endl;
    file >> counter;
    //cout<<"translates"<<endl;
    for (;counter>0;counter--)
    {
        Vector3 ts;
        file>> ts;
        //ts.Print();
        CurrentScene->translates.push_back(ts);
    }


    for (int i = 0; i < 9; ++i)
    {
        file>>dummy;
    }
    file>>counter;
    //cout<<"scales"<<endl;
    for (;counter>0;counter--)
    {
        Vector3 scs;
        file>>scs;
        //scs.Print();
        CurrentScene->scales.push_back(scs);
    }
    
    for (int i = 0; i < 10; ++i)
    {
        file>>dummy;
    }
    file>>counter;
    //cout<<"rotates"<<endl;
    for (;counter>0;counter--)
    {
        Vector3 rs;
        float angle;

        file>>angle;
        file>>rs;

        /*cout<<angle<<endl;
        rs.Print();*/
        
        CurrentScene->rotates.push_back(rs);
        CurrentScene->rotateAngles.push_back(angle);
         
    }

    file >> counter;
    for (int i = 0; i < 9; ++i)
    {
        file>>dummy;
        //cout<<dummy;
    }//cout<<endl;
    
    ////////////////7yeni///////////////////7
    CurrentScene->normals=new Vector3[counter];
    for (int i = 0; i < counter; ++i)
    {
        CurrentScene->normals[i]=Vector3(0,0,0);
    }
    ////////////////////////////////////////

    CurrentScene->vertexPos=new GLfloat[counter*3];
    CurrentScene->howmany=counter*3;
    for (int i=0;i<counter*3;i++){
        /*if(i%3==0){
            cout<<endl;
        }*/
       file >> CurrentScene->vertexPos[i];
       //cout<<CurrentScene->vertexPos[i]<<" ";
    }

    file >> counter;
    //cout<<"kac tane mesh var-> "<< counter<<endl;
    for (;counter>0;counter--)
    {
    	Mesh mesh;
    	file >> mesh;
    	CurrentScene->meshes.push_back(mesh);
    }

    file.close();

    //////////////////yeni///////////////////////////
    for (int i = 0; i < CurrentScene->howmany / 3; ++i)
    {
        CurrentScene->normals[i].normalize();
    }

    /*for (int i = 0; i < CurrentScene->howmany /3; ++i)
    {
        CurrentScene->normals[i].Print();
    }*/


    CurrentScene->normalValues=new GLfloat[CurrentScene->howmany];
    int k=0;
    for (int i = 0; i < CurrentScene->howmany/3; ++i)
    {
        CurrentScene->normalValues[k++]=CurrentScene->normals[i][0];
        CurrentScene->normalValues[k++]=CurrentScene->normals[i][1];
        CurrentScene->normalValues[k++]=CurrentScene->normals[i][2];
    }
    delete CurrentScene->normals;
    ////////////////////////7777///////////////77
    
    ifstream camfile(argv[2],ifstream::in);

        camfile>>CurrentScene->camera;
    

    //cout<<CurrentScene->camera;
    camfile.close();

}


#endif //RAYTRACER_SCENE_H
