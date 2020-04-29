#ifndef STATMENU_H
#define STATMENU_H

#include "DisplayObject.h"
#include "Game.h"
#include "AffineTransform.h"
#include "TweenJuggler.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string>
#include <ctime>
#include "EventListener.h"

using namespace std;

class StatMenu : public DisplayObject, EventListener{
public:
  StatMenu();
  ~StatMenu();
  //TextBox(const string &message_text);
	//TextBox(const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);
	//Particle(int red, int green, int blue, int w, int h);
	//Particle(string id, string path);
	//TextBox(string path, int x, int y, int timeout, double scaleX, double scaleY);
	//Particle(string path, int x, int y, int lowX, int highX, int lowY, int highY, int timeout, double scaleX, double scaleY);
  void generateText();
  virtual void draw(AffineTransform &at);
	virtual void update(set<SDL_Scancode> pressedKeys);
  virtual void handleEvent(Event* e);
  static SDL_Texture* loadFont(const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);
  void chunkString(string s, int chunkSize);

private:
  bool text_active = true;
  bool mapMode = false;
  string font_path = "resources/fonts/dtm.ttf";
  string default_path = "./resources/miscellaneous/tablet.png";
  string overall_title = "Attributes";
  string health = "Health:"; string speed = "Speed: "; string damage = "Damage: "; string modifiers_title = "Modifiers"; string attack_speed = "Attack Speed: "; string level = "Level: ";
  int title_font_size = 30;
  int font_size = 20;
  SDL_Color textColor = {0, 0, 0, 255};
  SDL_Texture * title_texture, * health_texture, * speed_texture, * damage_texture, * attack_speed_texture, *level_texture, *modifiers_title_texture;
  SDL_Rect title_rect, health_rect, speed_rect, damage_rect, attack_speed_rect, level_rect, modifiers_title_rect;
  AffineTransform * my_at;

};

#endif
