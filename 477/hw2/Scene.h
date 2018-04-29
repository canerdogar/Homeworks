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
#include "Material.h"
#include "Texture.h"
#include "Matrix.cpp"


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
    vector<Texture*> _textures;
    /*vector<Matrix<float>*> _translates;
    vector<Matrix<float>*> _scales;
    vector<Matrix<float>*> _rotates;*/

    vector<Vector3> _translates;
    vector<Vector3> _scales;
    vector<Vector3> _rotates;
    vector<float> _rotate_angles;

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

/*Matrix<float>* tMatrix(const Vector3& ts){
    float** array=new float*[4];
    for (int i = 0; i < 4; ++i)
    {
        array[i]=new float[4];
    }
    array[0][0] = 1;
    array[0][1] = 0;
    array[0][2] = 0;
    array[0][3] = ts[0];

    array[1][0] = 0;
    array[1][1] = 1;
    array[1][2] = 0;
    array[1][3] = ts[1];

    array[2][0] = 0;
    array[2][1] = 0;
    array[2][2] = 1;
    array[2][3] = ts[2];

    array[3][0] = 0;
    array[3][1] = 0;
    array[3][2] = 0;
    array[3][3] = 1;

    Matrix<float>* matrix=new Matrix<float>(array,4,4);
    for (int i = 0; i < 4; ++i)
    {
        delete[] array[i];
    }
    delete[] array;
    return matrix;
}*/

/*Matrix sMatrix(){

    
}

Matrix rMatrix(){

    
}*/



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
    
    //cout<<"vertex counter: "<<counter<<endl;
    string dummy;
    file>>dummy;
    file>>counter;
    //file>>dummy;



    for(;counter>0;counter--){
        file>>dummy;
        //cout<<dummy<<endl;
        Texture* texture=new Texture(dummy);
        CurrentScene->_textures.push_back(texture);
    }
    
    file>>dummy;
    file>>counter;
    for (;counter>0;counter--)
    {
        Vector3 ts;
        file>>ts;
        /*Matrix<float>* matrix=new Matrix<float>(4,4);
        matrix->tMatrix(ts);*/

        //matrix->print();
        CurrentScene->_translates.push_back(ts);
    }

   //std::cout<<endl;

    file>>dummy;
    file>>counter;
    for (;counter>0;counter--)
    {
        Vector3 scs;
        file>>scs;
        /*Matrix<float>* matrix=new Matrix<float>(4,4);
        matrix->sMatrix(scs);*/
        //matrix->print();
        CurrentScene->_scales.push_back(scs);
    }
    
    //std::cout<<endl;
    //cout<<"geldim"<<endl;
    file>>dummy;
    file>>counter;
    for (;counter>0;counter--)
    {
        Vector3 rs;
        float angle;

        file>>angle;
        file>>rs;
        /*Matrix<float>* zmatrix=new Matrix<float>(4,4);
        zmatrix->rzMatrix(angle);
        //zmatrix->print();

        rs.normalize();
        float d= sqrt( rs[1] * rs[1] + rs[2] * rs[2]);

        float angle2=acos( rs[2] / d );
        float angle3=acos( d );

        Matrix<float>* ymatrix=new Matrix<float>(4,4);
        ymatrix->ryMatrix(angle3);
        ymatrix->print();



        Matrix<float>* xmatrix=new Matrix<float>(4,4);
        xmatrix->rxMatrix(angle2);
        xmatrix->print();

        /*Matrix<float>* _xmatrix=new Matrix<float>(4,4);
        _xmatrix->rxMatrix(-angle2);

        Matrix<float>* _ymatrix=new Matrix<float>(4,4);
        _ymatrix->rxMatrix(-angle3);*/

        /*cout<<"geldim2"<<endl;
       
        Matrix<float> result(4,4);*/

        //*result= ((*_xmatrix) * ((*_ymatrix) * ((*zmatrix) * ((*ymatrix) * (*xmatrix)))));
        //(*ymatrix) * (*xmatrix) ;

        /*cout<<"geldim3"<<endl;
        result= (*ymatrix) * (*xmatrix) ;
        cout<<"geldim4"<<endl;*/
        //result.print();
        //((*_xmatrix) * (*_ymatrix) * (*zmatrix) * (*ymatrix) * (*xmatrix)).print();
        
        //result->print();
        //CurrentScene->_rotates.push_back(result);
        //delete zmatrix;
        //delete ymatrix;
        //delete xmatrix;
        //delete _ymatrix;
        //delete _xmatrix;

        CurrentScene->_rotates.push_back(rs);
        CurrentScene->_rotate_angles.push_back(angle);
         
    }

    //cout<<"geldim"<<endl;

    /*for(int i=0;i<CurrentScene->_translates.size();i++){

        CurrentScene->_translates[i].Print();
    }
    for(int i=0;i<CurrentScene->_scales.size();i++){

        CurrentScene->_scales[i].Print();
    }
    for(int i=0;i<CurrentScene->_rotates.size();i++){

        CurrentScene->_rotates[i].Print();
        cout<<CurrentScene->_rotate_angles[i]<<endl;
    }*/
    
    
    /*file>>CurrentScene->numberOfObjects;*/
    string type;
    file>>counter;
    int counter2=0;
    int tid;
    //cout<<"model counter: "<<CurrentScene->numberOfObjects<<endl;
    int j=0;
    for(int i=0;i<counter;i++){
        file>>type;
        if(type=="#CubeInstance"){
            //Triangle* triangle=new Triangle();
            Mesh* mesh=new Mesh();
            mesh->start_numbering(j);
            file >> *mesh;
            file>>counter2;
            for (int i = 0; i < counter2; ++i)
            {
                //Transformations
                file>>dummy;
                file>>tid;
                if(dummy.compare("s")==0){
                    for (int i = 0; i < mesh->_triangles.size(); ++i)
                    {
                        mesh->_triangles[i]->Scale(CurrentScene->_scales[tid-1]);
                    }
                }else if(dummy.compare("t")==0){
                    for (int i = 0; i < mesh->_triangles.size(); ++i)
                    {
                        mesh->_triangles[i]->Translate(CurrentScene->_translates[tid-1]);
                    }
                }else{
                    for (int i = 0; i < mesh->_triangles.size(); ++i)
                    {
                        mesh->_triangles[i]->Rotate(CurrentScene->_rotate_angles[tid-1],CurrentScene->_rotates[tid-1]);
                    }
                }
             }
             j+=12;
            //triangle->c1.Print();
            //triangle->c2.Print();
            //triangle->c3.Print();
             mesh->set();
             CurrentScene->_meshes.push_back(mesh);
        }
        else if(type=="#SphereInstance"){
            Sphere* sphere=new Sphere();
            sphere->set_id(j++);
            file>>sphere->material_id;
            file>>tid;
            if(tid!=0){
                sphere->tex=CurrentScene->_textures[tid-1];

            }
            file>>counter2;
            for (int i = 0; i < counter2; ++i)
            {

                //Transformations
                file>>dummy;
                file>>tid;
                if(dummy.compare("s")==0){
                    sphere->Scale(CurrentScene->_scales[tid-1]);
                }else if(dummy.compare("t")==0){
                    sphere->Translate(CurrentScene->_translates[tid-1]);
                }else{
                    sphere->Rotate(CurrentScene->_rotate_angles[tid-1],CurrentScene->_rotates[tid-1]);
                }
            }
            sphere->set_box();
            CurrentScene->_objects.push_back(sphere);
        }
        
    }


    for(int i=0;i<CurrentScene->_meshes.size();i++){

        for(int j=0;j<CurrentScene->_meshes[i]->_triangles.size();j++){
            CurrentScene->_objects.push_back(CurrentScene->_meshes[i]->_triangles[j]);
        }

    }
    
    /*
    for (int i = 0; i < CurrentScene->_meshes.size(); ++i)
    {
        cout<< *(CurrentScene->_meshes[i] );
    }*/

    

	/*Triangle* triangle=new Triangle(Vector3(-1,-1,-5),Vector3(1,-1,-5),Vector3(1,1,-5));
	triangle->mid=1;
	triangle->set_normal();
	triangle->texture=NULL;
	triangle->set_id(j++);
	CurrentScene->_objects.push_back(triangle);*/

    	CurrentScene->numberOfObjects=j;

    

    /*
    Sphere* sphere=new Sphere();
    sphere->Scale(CurrentScene->_scales[0]);
    sphere->Translate(CurrentScene->_translates[0]);
    sphere->material_id=1;
    sphere->set_id(0);
    sphere->tex=CurrentScene->_textures[0];
    sphere->set_box();
    CurrentScene->_objects.push_back(sphere);
    */

    
    file.close();
    ifstream camfile(argv[2],ifstream::in);
    camfile>>counter;
    for(;counter>0;counter--){
        Camera camera;
        camfile>>camera;
        CurrentScene->_cameras.push_back(camera);
    }
    camfile.close();

    /*for(const auto& object:CurrentScene->Objects()){
        std::cout<<object->type()<<std::endl;
    }*/
    
    //std::cout<<"j-> "<<j<<std::endl;
    //std::cout<<CurrentScene->_objects.size()<<std::endl;


    CurrentScene->root=new BVHNode(CurrentScene->_objects,0);//EKSİİİİİİİİİİİİİİİİİİİİİİİİK

    //CurrentScene->root->nofleaves();//<<std::endl;
}


#endif //RAYTRACER_SCENE_H
