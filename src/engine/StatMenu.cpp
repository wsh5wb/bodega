#include "StatMenu.h"
#include "Player.h"
#include <iostream>
#include <ctype.h>

using namespace std;
// next steps: 1) make sure that if the text is longer than a certain length that it gets divided up.
// we then render each load font
// then create something where text is only rendered for a certain period of time, then it gets removed
// and then updated with the next batch of text. If no next batch of text exists, then stop displaying the textbox
// (or potentially delete the textBox)

//current Max Allotment per line: 20 characters, 60 overall

StatMenu::StatMenu(): DisplayObject("StatMenu", "./resources/miscellaneous/tablet.png"){
  position.x = 350;
  position.y = 0;
  setScale(.8,.8);
  my_at = new AffineTransform();
  generateText();
}

StatMenu::~StatMenu(){
  delete my_at;
}
// Stats I want to Display: Health (out of Max), Speed, Damage,
void StatMenu::draw(AffineTransform &at){
    DisplayObject::draw(*my_at);
    auto current_x = dstrect.x;
    auto current_y = dstrect.y;
    title_rect.x = current_x + 150;
    title_rect.y = current_y + 50;
    health_rect.x = current_x + 50;
    health_rect.y = current_y + 125;
    speed_rect.x = current_x + 50;
    speed_rect.y = current_y + 150;
    damage_rect.x = current_x + 50;
    damage_rect.y = current_y + 175;
    modifiers_title_rect.x = current_x + 250;
    modifiers_title_rect.y = current_y + 100;
    SDL_RenderCopy(Game::renderer, title_texture, nullptr, &title_rect);
    SDL_RenderCopy(Game::renderer, health_texture, nullptr, &health_rect);
    SDL_RenderCopy(Game::renderer, speed_texture, nullptr, &speed_rect);
    SDL_RenderCopy(Game::renderer, damage_texture, nullptr, &damage_rect);
    SDL_RenderCopy(Game::renderer, modifiers_title_texture, nullptr, &modifiers_title_rect);
}

void StatMenu::generateText(){
  //int x = Player::getPlayer()->getHealth();// this line destroys everything????
  title_texture = loadFont(font_path, title_font_size, overall_title, textColor);
  SDL_QueryTexture(title_texture, nullptr, nullptr, &title_rect.w, &title_rect.h);
  health_texture = loadFont(font_path, font_size, health, textColor);
  SDL_QueryTexture(health_texture, nullptr, nullptr, &health_rect.w, &health_rect.h);
  speed_texture = loadFont(font_path, font_size, speed, textColor);
  SDL_QueryTexture(speed_texture, nullptr, nullptr, &speed_rect.w, &speed_rect.h);
  damage_texture = loadFont(font_path, font_size, damage, textColor);
  SDL_QueryTexture(damage_texture, nullptr, nullptr, &damage_rect.w, &damage_rect.h);
  modifiers_title_texture = loadFont(font_path, font_size, modifiers_title, textColor);
  SDL_QueryTexture(modifiers_title_texture, nullptr, nullptr, &modifiers_title_rect.w, &modifiers_title_rect.h);
}

void StatMenu::update(set<SDL_Scancode> pressedKeys){
  DisplayObject::update(pressedKeys);
  for (auto k : pressedKeys){
		if (k == SDL_SCANCODE_I) {
      if (this->alpha == 0){
        TweenJuggler * juggle = TweenJuggler::getInstance();
        Tween * alpha_tween = new Tween(this);
        alpha_tween->animate(TWEEN_ALPHA, this->alpha, 255, 30, TWEEN_QUADRATIC, EASE_IN);
        juggle->add(alpha_tween);
        generateText();
      }
        else if (this->alpha == 255){
        TweenJuggler * juggle = TweenJuggler::getInstance();
        Tween * alpha_tween = new Tween(this);
        alpha_tween->animate(TWEEN_ALPHA, this->alpha, 0, 30, TWEEN_QUADRATIC, EASE_OUT);
        juggle->add(alpha_tween);
        SDL_DestroyTexture(title_texture);
        SDL_DestroyTexture(health_texture);
        SDL_DestroyTexture(speed_texture);
        SDL_DestroyTexture(damage_texture);
        SDL_DestroyTexture(modifiers_title_texture);
      }
    }
  }
  /* TweenJuggler * juggle = TweenJuggler::getInstance();
  Tween * alpha_tween = new Tween(this);
  alpha_tween->animate(TWEEN_ALPHA, this->alpha, 0, 30, TWEEN_SINE, EASE_OUT);
  juggle->add(alpha_tween);
  SDL_DestroyTexture(text_texture);*/
}

void StatMenu::chunkString(string message, int chunkSize){
     for(int i = 0; i < message.length(); i+=chunkSize){
        string s = message.substr(i, chunkSize) + "...";
        //all_strings.push_back(s);
        printf("%s \n", message.substr(i, chunkSize).c_str());
        printf("Start: %x \n", i);
     }
}

SDL_Texture* StatMenu::loadFont(const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color){
  TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
  if (!font){
    cout<< "Failed to load font"<<endl;
  }
  //This fits about 16 characters per line.
  auto text_surface = TTF_RenderText_Blended_Wrapped(font, message_text.c_str(), color, 300);
  if (!text_surface){
    cout<< "Failed to create text surface"<<endl;
  }
  auto text_texture = SDL_CreateTextureFromSurface(Game::renderer, text_surface);
  if (!text_texture){
    cout<< "Failed to create text texture"<<endl;
  }
  SDL_FreeSurface(text_surface);
  return text_texture;
}