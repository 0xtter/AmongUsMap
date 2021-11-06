#pragma once




#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <algorithm>



sf::Texture charger_texture(std::string file);

sf::Sprite creer_sprite(sf::Texture texture, int sizeX, int sizeY, bool scale);

int afficher_sprite(sf::RenderWindow* window, sf::Sprite* sprite, sf::Texture texture, int x, int y);


