#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;
class TextureManager
{
	static unordered_map<string, sf::Texture> textures;
	static void LoadTexture(string textureName);
public:
	static sf::Texture& GetTexture(string textureName);
	static void Clear(); 
	static void LoadDigits(string fileName);
	static sf::Texture& GetDigit(int digit);
	static sf::Texture& GetSign();
};

