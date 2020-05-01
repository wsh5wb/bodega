#include "TextBox.h"
#include <iostream>
#include <ctype.h>

TextBox::TextBox() : DisplayObject(){
  this->start = std::clock();
  this->timeout = 300;
}
// next steps: 1) make sure that if the text is longer than a certain length that it gets divided up.
// we then render each load font
// then create something where text is only rendered for a certain period of time, then it gets removed
// and then updated with the next batch of text. If no next batch of text exists, then stop displaying the textbox
// (or potentially delete the textBox)

//current Max Allotment per line: 20 characters, 60 overall

TextBox::TextBox(const string &message_text): DisplayObject("TextBox", "./resources/miscellaneous/pixelart.png"){
  this->fullMessageText = message_text;
  position.x = 32;
  position.y = -32;
  setScale(.125, .15);
  this->start = std::clock();
  this->timeout = 2000;
  chunkString(fullMessageText, 60);
  current_print = all_strings[current_print_loc];
  current_print_loc ++;
  text_texture = loadFont(font_path, font_size, current_print, textColor);
  SDL_QueryTexture(text_texture, nullptr, nullptr, &text_rect.w, &text_rect.h);
}

TextBox::TextBox(const string &font_path,
                 int font_size,
                 const string &message_text,
                 const SDL_Color &color): DisplayObject("TextBox", "./resources/miscellaneous/pixelart.png"){
    this->fullMessageText = message_text;
    this->font_path = font_path;
    this->font_size = font_size;
    this->textColor = color;
    position.x = 32;
    position.y = -32;
    setScale(.125, .15);
    this->start = std::clock();
    this->timeout = 2000;
    chunkString(message_text, 60);
    current_print = all_strings[current_print_loc];
    current_print_loc ++;
    text_texture = loadFont(font_path, font_size, current_print, color);
    SDL_QueryTexture(text_texture, nullptr, nullptr, &text_rect.w, &text_rect.h);
}

void TextBox::draw(AffineTransform &at){
  if(text_active){
    DisplayObject::draw(at);
    auto current_x = dstrect.x;
    auto current_y = dstrect.y;
    text_rect.x = current_x + 45;
    text_rect.y = current_y + 60;
    SDL_RenderCopy(Game::renderer, text_texture, nullptr, &text_rect);
  }

}

void TextBox::update(set<SDL_Scancode> pressedKeys){
  DisplayObject::update(pressedKeys);
  text_active = true;
  if(pressedKeys.find(SDL_SCANCODE_M) != pressedKeys.end()){
    text_active = false;
    return;
  }
  if((((std::clock() - start ) / (double) CLOCKS_PER_SEC)*1000) > timeout){
    this->start = std::clock();
    if(current_print_loc < all_strings.size()){
      current_print = all_strings[current_print_loc];
      text_texture = loadFont(font_path, font_size, current_print, textColor);
      SDL_QueryTexture(text_texture, nullptr, nullptr, &text_rect.w, &text_rect.h);
      this->current_print_loc ++;
    }
    else if(current_print_loc > all_strings.size() && text_active){
      text_active = false;
      TweenJuggler * juggle = TweenJuggler::getInstance();
      Tween * alpha_tween = new Tween(this);
      alpha_tween->animate(TWEEN_ALPHA, this->alpha, 0, 30, TWEEN_SINE, EASE_OUT);
      juggle->add(alpha_tween);
      SDL_DestroyTexture(text_texture);
    }
    else if (text_active){
      current_print_loc++;
    }
  }
}

void TextBox::chunkString(string message, int chunkSize){
     for(int i = 0; i < message.length(); i+=chunkSize){
        string s = message.substr(i, chunkSize) + "...";
        all_strings.push_back(s);
        printf("%s \n", message.substr(i, chunkSize).c_str());
        printf("Start: %x \n", i);
     }
}

SDL_Texture* TextBox::loadFont(const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color){
  TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
  if (!font){
    cout<< "Failed to load font"<<endl;
  }
  //This fits about 16 characters per line.
  auto text_surface = TTF_RenderText_Blended_Wrapped(font, message_text.c_str(), color, 180);
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

void TextBox::addMessagetoDisplay(string message){
  this->fullMessageText = fullMessageText + message;
  chunkString(message, 60);
  text_active = true;
}
