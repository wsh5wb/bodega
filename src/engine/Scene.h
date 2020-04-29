#ifndef SCENE_H
#define SCENE_H

#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Player.h"
#include "DemoSprite.h"
#include "Object.h"
#include "Layer.h"
#include "Jelly.h"
#include "Urchin.h"
#include "Spirit.h"
#include "Portal.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Scene : public DisplayObjectContainer{

public:
	Scene();
	~Scene();
	/* Load scene from a file */
	void loadScene(string sceneFilePath);

	/*Save scene to a file, used for testing*/
	void saveScene(string sceneFilePath);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);


private:

};

#endif
