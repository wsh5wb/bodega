#ifndef LAYER_H
#define LAYER_H

#include "DisplayObjectContainer.h"

using namespace std;

class Layer : public DisplayObjectContainer{

public:

    Layer();
    Layer(double s);

    double setScale(double s);

    virtual void saveSelf(vector<string> &objects, vector<string> &dependencies);

private:
    double scale;
};

#endif
