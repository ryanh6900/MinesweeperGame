#include "TextureManager.h"
#include <string>
using namespace std;
unordered_map<string, sf::Texture> TextureManager::textures;
void TextureManager::LoadTexture(string fileName) {
	string path = "images/";
	path += fileName + ".png";
	textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName) {
	if (textures.find(textureName) == textures.end())
		LoadTexture(textureName);
	return textures[textureName];
}

void TextureManager::Clear() {
	textures.clear();
}

void TextureManager::LoadDigits(string fileName) {
	sf::Image image;
	image.loadFromFile(fileName);
	textures["0"].loadFromImage(image, sf::IntRect(0,0,21,32));
	textures["1"].loadFromImage(image, sf::IntRect(21, 0, 21, 32));
	textures["2"].loadFromImage(image, sf::IntRect(42, 0, 21, 32));
	textures["3"].loadFromImage(image, sf::IntRect(63, 0, 21, 32));
	textures["4"].loadFromImage(image, sf::IntRect(84, 0, 21, 32));
	textures["5"].loadFromImage(image, sf::IntRect(105, 0, 21, 32));
	textures["6"].loadFromImage(image, sf::IntRect(126, 0, 21, 32));
	textures["7"].loadFromImage(image, sf::IntRect(147, 0, 21, 32));
	textures["8"].loadFromImage(image, sf::IntRect(168, 0, 21, 32));
	textures["9"].loadFromImage(image, sf::IntRect(189, 0, 21, 32));
	textures["-"].loadFromImage(image, sf::IntRect(210, 0, 21, 32));
	
	
}
sf::Texture& TextureManager::GetSign() {
		return textures["-"];
}
sf::Texture& TextureManager::GetDigit(int digit) {
	string textureName = to_string(digit);
	if (textures.find(textureName) == textures.end())
		LoadDigits("images/digits.png");
		return textures[textureName];
}

