
#include "Const.h"
#include "graphics.h"



sf::Texture charger_texture(std::string file) {
    sf::Texture texture;
    if (!texture.loadFromFile(file));
    return texture;
}


sf::Sprite creer_sprite(sf::Texture texture,int sizeX,int sizeY,bool scale) {
    sf::Sprite sprite;

    sprite.setTexture(texture);

    if (scale == true) {
        float scale_min = std::min((float)sizeX / texture.getSize().x, (float)sizeY / texture.getSize().y);
        sprite.setScale(scale_min,scale_min);
    }
    else sprite.setScale((float)sizeX / texture.getSize().x, (float)sizeY / texture.getSize().y);

    return sprite;
}


int afficher_sprite(sf::RenderWindow* window, sf::Sprite* sprite,sf::Texture texture, int x, int y) {
    sprite->setTexture(texture);
    sprite->setPosition(x,y);
    window->draw(*sprite);
    return EXIT_SUCCESS;
}