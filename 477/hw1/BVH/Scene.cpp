#include "Scene.h"
#include <fstream>


const std::vector<Surface*>& Scene::Objects()const{
    return _objects;
}

const std::vector<Camera>& Scene::Cameras() const {
    return _cameras;
}

const std::vector<Sphere*>& Scene::Spheres() const {
    return _spheres;
}

const std::vector<Mesh*>& Scene::Meshes() const {
    return _meshes;
}

const std::vector<Vertex>& Scene::Vertices() const {
    return _vertices;
}

const std::vector<Material>& Scene::Materials() const{
    return _materials;
}

const std::vector<PointLight>& Scene::Lights() const{
    return _lights;
}

Color Scene::get_background() const{
    return _background;
}

Color Scene::get_ambient() const{
    return _ambient;
}

int Scene::get_numberOfObjects()const{
    return numberOfObjects;
}

Scene* CurrentScene;//yeni ekledin