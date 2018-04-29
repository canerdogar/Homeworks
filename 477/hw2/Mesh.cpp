#include "Mesh.h"
#include "Scene.h"
#include "Vector3.h"

std::istream& operator>>(std::istream &stream,Mesh& mesh){
        /*stream >>mesh.mesh_id;stream>>mesh.triangle_count;stream>>mesh.material_id;
        for(int i=0;i<mesh.triangle_count;i++){
            Triangle* vids=new Triangle();//degistirdin
            stream>> *vids;
            vids->set_id(mesh.start_number++);
            mesh._triangles.push_back(vids);//degistirdin
        }*/
        stream>>mesh.material_id;

        int texture_id;
        stream>>texture_id;
        
        Vector3 v0(0.5,0.5,0.5); //+++
        Vector3 v1(0.5,0.5,-0.5);//++-
        Vector3 v2(-0.5,0.5,-0.5);//-+-
        Vector3 v3(-0.5,0.5,0.5);//-++
        Vector3 v4(-0.5,-0.5,0.5);//--+
        Vector3 v5(0.5,-0.5,0.5);//+-+
        Vector3 v6(0.5,-0.5,-0.5);//+--
        Vector3 v7(-0.5,-0.5,-0.5);//---

        Triangle* vids=new Triangle(v3,v4,v5);
        vids->set_id(mesh.start_number++);
        vids->sid=1;

        Triangle* vids2=new Triangle(v3,v5,v0);
        vids2->set_id(mesh.start_number++);
        vids2->sid=2;

        Triangle* vids3=new Triangle(v0,v5,v6);
        vids3->set_id(mesh.start_number++);
        vids3->sid=3;
        
        Triangle* vids4=new Triangle(v0,v6,v1);
        vids4->set_id(mesh.start_number++);
        vids4->sid=4;
        
        Triangle* vids5=new Triangle(v2,v3,v0);
        vids5->set_id(mesh.start_number++);
        vids5->sid=5;
        
        Triangle* vids6=new Triangle(v2,v0,v1);
        vids6->set_id(mesh.start_number++);
        vids6->sid=6;
        
        Triangle* vids7=new Triangle(v2,v7,v4);
        vids7->set_id(mesh.start_number++);
        vids7->sid=7;

        Triangle* vids8=new Triangle(v2,v4,v3);
        vids8->set_id(mesh.start_number++);
        vids8->sid=8;

        Triangle* vids9=new Triangle(v4,v7,v6);//
        vids9->set_id(mesh.start_number++);
        vids9->sid=9;

        Triangle* vids10=new Triangle(v4,v6,v5);
        vids10->set_id(mesh.start_number++);
        vids10->sid=10;

        Triangle* vids11=new Triangle(v1,v6,v7);
        vids11->set_id(mesh.start_number++);
        vids11->sid=11;
        
        Triangle* vids12=new Triangle(v1,v7,v2);
        vids12->set_id(mesh.start_number++);
        vids12->sid=12;
    
        if(texture_id !=0){
            Texture* texture=CurrentScene->_textures[texture_id-1];
            vids->texture=texture;
            vids2->texture=texture;
            vids3->texture=texture;
            vids4->texture=texture;
            vids5->texture=texture;
            vids6->texture=texture;
            vids7->texture=texture;
            vids8->texture=texture;
            vids9->texture=texture;
            vids10->texture=texture;
            vids11->texture=texture;
            vids12->texture=texture;
        }//actin

        vids->mid=mesh.material_id;
        vids2->mid=mesh.material_id;
        vids3->mid=mesh.material_id;
        vids4->mid=mesh.material_id;
        vids5->mid=mesh.material_id;
        vids6->mid=mesh.material_id;
        vids7->mid=mesh.material_id;
        vids8->mid=mesh.material_id;
        vids9->mid=mesh.material_id;
        vids10->mid=mesh.material_id;
        vids11->mid=mesh.material_id;
        vids12->mid=mesh.material_id;

        mesh._triangles.push_back(vids);
        mesh._triangles.push_back(vids2);
        mesh._triangles.push_back(vids3);
        mesh._triangles.push_back(vids4);
        mesh._triangles.push_back(vids5);
        mesh._triangles.push_back(vids6);
        mesh._triangles.push_back(vids7);
        mesh._triangles.push_back(vids8);
        mesh._triangles.push_back(vids9);
        mesh._triangles.push_back(vids10);
        mesh._triangles.push_back(vids11);
        mesh._triangles.push_back(vids12);

        return stream;
    }
