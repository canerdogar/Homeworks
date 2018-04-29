#include "Material.h"
#include "Scene.h"
#include <cmath>
#define PI 3.14159265358979323846
Color Material::calculate(int count,const RayHitInfo& rhi_arg,const Vector3& wo,int oid)const{
    Vector3 totalColor,reflectedColor;
    //bool bok_Hasan=true;
    
        for (const auto& light : CurrentScene->Lights()) {
        
            Vector3 wi=(light._position-rhi_arg.Position).normalize();
            //float t=INFINITY;
            //float t2=t;
            RayHitInfo rhi;
            //int flag=1;
            Ray ray(rhi_arg.Position,wi);
            float distance=( light._position-rhi_arg.Position).length();
            
            
            /*for (const auto& sphere : CurrentScene->Spheres())
            {
                sphere.Intersect(ray,rhi,t,oid,j,i);
                if(t2!=t){
                    if(rhi.Parameter > 0 && rhi.Parameter < distance){
                        flag=0;
                        break;
                    }
                }
            }
            for (const auto& mesh : CurrentScene->Meshes())
            {
                for(const auto& triangle : mesh.Triangles()){
                    triangle.Intersect(ray,rhi,t,mesh.material_id,oid);
                    if(t2!=t){
                        if(rhi.Parameter > 0 && rhi.Parameter < distance){
                            flag=0;
                            break;
                        }
                    }
                }
            }*/
            
            if(!CurrentScene->root->Intersect(ray,rhi,oid)){
                //if(t==INFINITY){
                
                float angle=rhi_arg.Normal.dot(wi);
                Vector3 radiance=light._intensity / (distance*distance *4*PI);//eminsin
                //float divider=distance*distance *4*PI;
                if(angle>0){
                    if(rhi_arg.tex!=NULL){
                        if(rhi_arg.uv!=NULL){
                            //totalColor=totalColor+Vector3(10,10,10);
			    //cout<<"material sid: "<<rhi.sid<<endl;
                            Vector3 diffuse=rhi_arg.tex->value(rhi_arg.uv,rhi_arg.sid);
                            //diffuse.Print();
                            //cout<<"geldim"<<endl;
                            totalColor=totalColor+ Vector3(_diffuse[0] * angle * diffuse[0],_diffuse[1] * angle * diffuse[1],_diffuse[2] * angle * diffuse[2]);
                        }
                        
                    }
                    else{
                        //cout<<"girdi"<<endl;
                        //totalColor=totalColor+Vector3(10,10,10);
                        //cout<<"girdin"<<endl;
                        totalColor=totalColor+ Vector3(radiance._data[0] * angle * _diffuse._data[0],radiance._data[1] * angle * _diffuse._data[1],radiance._data[2] * angle * _diffuse._data[2]);
                    }
                }
                Vector3 h= wi + wo;
                h.normalize();
                float angle2=rhi_arg.Normal.dot(h);
                if(angle2>0){
                    //std::cout<<angle2<<std::endl;
                    angle2=pow(angle2,phong);
                    totalColor=totalColor+ Vector3(radiance._data[0] * angle2 * _specular._data[0],radiance._data[1] * angle2 * _specular._data[1],radiance._data[2] * angle2 * _specular._data[2]);
                    

                }
                
                //}

            
            }
        
            
        }
    
    if( !(_reflectance==Vector3(0,0,0)) && count < CurrentScene->_rayReflect ){
        //wr = -wo + 2ncosΘ = -wo + 2n(n.wo)
        //bok_Hasan=false;
        Vector3 wr = wo * -1  + rhi_arg.Normal * rhi_arg.Normal.dot(wo) * 2 ;
        wr.normalize();
        
        /*float t=INFINITY;
        float t2=t;
        int sphere_id;*/
        RayHitInfo rhi;
        Ray ray(rhi_arg.Position,wr);
        
        CurrentScene->root->Intersect(ray,rhi,oid);
        /*for (const auto& sphere : CurrentScene->Spheres())
        {
            sphere.Intersect(ray,rhi,t,oid,j,i);
            if(t2!=t){
                t2=t;
                sphere_id=sphere.sphere_id;
            }
        }
        for (const auto& mesh : CurrentScene->Meshes())
        {
            for(const auto& triangle : mesh.Triangles()){
                triangle.Intersect(ray,rhi,t,mesh.material_id,oid);
                if(t2!=t){
                    t2=t;
                    sphere_id=triangle._id;
                }
                
            }
        }*/
        
        
        
        if(rhi.Parameter!=INFINITY && rhi.Parameter>0){
            //std::cout<< "j-> "<<j <<" i->"<<i<<std::endl;
            Material material=CurrentScene->Materials()[rhi.Material - 1];
            Color reflected=material.calculate(count+1,rhi,(rhi_arg.Position-rhi.Position).normalize(),rhi.oid);
            reflected=_reflectance*reflected;
            reflectedColor = reflectedColor + Vector3(reflected.R(),reflected.G(),reflected.B());
        }
        
    }

    

   
    return Color(totalColor._data[0]+reflectedColor._data[0],totalColor._data[1]+reflectedColor._data[1],totalColor._data[2]+reflectedColor._data[2]);
    //return Color(0,0,0);
}
