#include "TextBox.h"
#include <iostream>
TextBox::TextBox() : DisplayObject(){

}
// next steps: 1) make sure that if the text is longer than a certain length that it gets divided up.
// we then render each load font
// then create something where text is only rendered for a certain period of time, then it gets removed
// and then updated with the next batch of text. If no next batch of text exists, then stop displaying the textbox
// (or potentially delete the textBox)


TextBox::TextBox(string path,
                 const string &font_path,
                 int font_size,
                 const string &message_text,
                 const SDL_Color &color): DisplayObject("TextBox", path){
    text_texture = loadFont(font_path, font_size, message_text, color);
    SDL_QueryTexture(text_texture, nullptr, nullptr, &text_rect.w, &text_rect.h);
    position.x = 350;
    position.y = -250;
    setScale(1.25, 1.5);
}

void TextBox::draw(AffineTransform &at){
    DisplayObject::draw(at);
    auto current_x = dstrect.x;
    auto current_y = dstrect.y;
    text_rect.x = current_x + 40;
    text_rect.y = current_y + 50;
    if(count < 100){
    SDL_RenderCopy(Game::renderer, text_texture, nullptr, &text_rect);
    count++;
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
