#include "graphics.h"
#include "Offset.h"
#include "proc.h"

#ifndef PLAYER_H

#define PLAYER_H

#define MAX_PLAYER_COUNT 10

class Player
{
public:
	int CreatePlayer(Player* PlayerInstance, int PlayerID);
	int RefreshPlayer(Player* );
private:

	uintptr_t AdresseX;
	uintptr_t AdresseY;
	uintptr_t Name;
	uintptr_t Impostor;

	sf::Sprite Sprite;
	sf::Texture Texture;

};

#endif // !PLAYER_H