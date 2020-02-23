#include "ResourceBar.h"

ResourceBar::ResourceBar() : DisplayObjectContainer(){
	//using recursive_directory_iterator = std:filesystem::recursive_directory_iterator;
	
	for (const auto& dirEntry : std::filesystem::recursive_directory_iterator("./resources"))
	     std::cout << dirEntry << std::endl;
}

ResourceBar::~ResourceBar() {

}