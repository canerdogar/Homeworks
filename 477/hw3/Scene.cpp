#include "Scene.h"
#include <fstream>

Scene* CurrentScene;//yeni ekledin

const vector<Camera>& Scene::Cameras()const{
    return CurrentScene->cameras;
}