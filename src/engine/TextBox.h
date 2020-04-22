#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Sprite.h"
#include "DisplayObject.h"
#include "Game.h"
#include "TweenJuggler.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string>
#include <ctime>

using namespace std;

class TextBox : public DisplayObject{
public:
  TextBox();
	TextBox(string path, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);
	//Particle(int red, int green, int blue, int w, int h);
	//Particle(string id, string path);
	//TextBox(string path, int x, int y, int timeout, double scaleX, double scaleY);
	//Particle(string path, int x, int y, int lowX, int highX, int lowY, int highY, int timeout, double scaleX, double scaleY);

  virtual void draw(AffineTransform &at);
	virtual void update(set<SDL_Scancode> pressedKeys);
  static SDL_Texture* loadFont(const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);
  void chunkString(string s, int chunkSize);

	std::clock_t start;
	int timeout;

private:
  bool text_active = true;
  int current_print_loc = 0;
  string fontPath, fullMessageText;
  int font_size;
  vector<string> all_strings;
  string current_print;
  SDL_Color textColor;
  SDL_Texture * text_texture;
  SDL_Rect text_rect;
};

#endif
