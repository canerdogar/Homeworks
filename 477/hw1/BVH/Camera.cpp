#include "Camera.h"
#include "Ray.h"
#include "Scene.h"

Image Camera::Render() const{
    Image image(_imagePlane.Width,_imagePlane.Height);
    int oid=CurrentScene->get_numberOfObjects();
    
    for(int i=0;i<_imagePlane.Width;i++){

        float y=_imagePlane.Left+(_imagePlane.Right - _imagePlane.Left)*(i+0.5) /_imagePlane.Width;

        for(int j=0;j<_imagePlane.Height;j++){
                
            
            float x=_imagePlane.Top-(_imagePlane.Top - _imagePlane.Bottom)*(j+0.5) /_imagePlane.Height;
            Vector3 direction = _gaze * _imagePlane.Distance + _space.Left * y+  _space.Up * x;
            Ray ray(_position,direction);
             
            
            /*float t=INFINITY;
            float t2=t;*/
            RayHitInfo rhi;
            
             /*for (const auto& sphere : CurrentScene->Spheres())
             {
                 sphere.Intersect(ray,rhi,t,numberOfObjects,j,i);
                 if(t2!=t){
                     t2=t;
                     oid=sphere.sphere_id;
                 }
             }
    
             for (const auto& mesh : CurrentScene->Meshes())
             {
                 for(const auto& triangle : mesh.Triangles()){
                     triangle.Intersect(ray,rhi,t,mesh.material_id,numberOfObjects);
                     if(t2!=t){
                         t2=t;
                         oid=triangle._id;
                     }
                 }
                 
             }*/
            
            CurrentScene->root->Intersect(ray,rhi,oid);
     
            if(rhi.Parameter!=INFINITY){
                Material material=CurrentScene->Materials()[rhi.Material - 1];
                image.Pixel(j,i)= material.get_ambient() * CurrentScene->get_ambient();
                //image.Pixel(j,i)=Color(255,255,255);
                
                /*if (rhi.oid==1 || rhi.oid==0) {
                    image.Pixel(j,i)=Color(255,255,255);
                }else{
                    image.Pixel(j,i)=Color(100,100,100);
                }*/
                
                /*if(j==720-367 && i==435){
                    std::cout<<"->"<<oid;
                }*/
                image.Pixel(j,i)=image.Pixel(j,i)+material.calculate(0,rhi.Position,rhi.Normal,(_position-rhi.Position).normalize(),rhi.oid);
            }else{
                image.Pixel(j,i)= CurrentScene->get_background();
            }
            //image.Pixel(j,i)=Color(0,0,0);
     
         }
     }
    /*image.Pixel(384,250)=Color(255,255,255);
    image.Pixel(384,251)=Color(255,255,255);
    image.Pixel(384,252)=Color(255,255,255);
    image.Pixel(384,253)=Color(255,255,255);
    image.Pixel(384,254)=Color(255,255,255);
    image.Pixel(384,255)=Color(255,255,255);
    image.Pixel(384,256)=Color(255,255,255);
    image.Pixel(384,257)=Color(255,255,255);
    
    
    
    
    image.Pixel(600,320)=Color(255,255,255);
    image.Pixel(600,321)=Color(255,255,255);
    image.Pixel(600,322)=Color(255,255,255);
    image.Pixel(600,323)=Color(255,255,255);
    image.Pixel(600,324)=Color(255,255,255);
    image.Pixel(600,325)=Color(255,255,255);
    image.Pixel(600,326)=Color(255,255,255);*/
    
    return image;
}
