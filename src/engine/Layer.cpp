#include "Layer.h"

Layer::Layer() {

}

Layer::Layer(double s) :
        DisplayObjectContainer() {
    setScale(s);
}

double Layer::setScale(double s){
    scale = s;
    DisplayObjectContainer::setScale(s,s);
}


void Layer::saveSelf(vector<string> &objects, vector<string> &dependencies) {
    string desc;
    stringstream sstm;
    int px0 = pivot.x, px1 = position.x, py0 = pivot.y, py1 = position.y;
    sstm << "6 " << id << " " << scale << "\n";
    desc = sstm.str();
    objects.push_back(desc);
    for (DisplayObject *child : children) {
        string dep = id + " " + child->id + "\n";
        dependencies.push_back(dep);
        child->saveSelf(objects, dependencies);
    }
}
