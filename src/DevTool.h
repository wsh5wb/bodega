#ifndef DEVTOOL_H
#define DEVTOOL_H

#include <sdlgui/screen.h>
#include <sdlgui/window.h>
#include <sdlgui/layout.h>
#include <sdlgui/label.h>
#include <sdlgui/checkbox.h>
#include <sdlgui/button.h>
#include <sdlgui/toolbutton.h>
#include <sdlgui/popupbutton.h>
#include <sdlgui/combobox.h>
#include <sdlgui/dropdownbox.h>
#include <sdlgui/progressbar.h>
#include <sdlgui/entypo.h>
#include <sdlgui/messagedialog.h>
#include <sdlgui/textbox.h>
#include <sdlgui/slider.h>
#include <sdlgui/imagepanel.h>
#include <sdlgui/imageview.h>
#include <sdlgui/vscrollpanel.h>
#include <sdlgui/colorwheel.h>
#include <sdlgui/graph.h>
#include <sdlgui/tabwidget.h>
#include <sdlgui/switchbox.h>
#include <sdlgui/formhelper.h>
#include <sdlgui/AffineTransform.h>
#include <sdlgui/AnimatedSprite.h>
#include <sdlgui/Animations.h>
#include <sdlgui/DisplayObjectContainer.h>
#include <sdlgui/DisplayObject.h>
#include <sdlgui/Game.h>
#include <sdlgui/jsonConversions.h>
#include <sdlgui/json.hpp>
#include <sdlgui/Mouse.h>
#include <sdlgui/Scene.h>
#include <sdlgui/Sprite.h>
#include <sdlgui/ResourceBar.h>
#include <memory>

#if defined(_WIN32)
#include <windows.h>
#endif
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

using std::set;

using namespace sdlgui;

class DevTool : public Game, Screen{
public:
	DevTool();
	virtual ~DevTool();
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
private:
	ResourceBar* resourceBar;
	DisplayObject* draggable = NULL;
};

#endif
