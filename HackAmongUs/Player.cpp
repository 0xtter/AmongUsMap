#include "Player.h"


int Player::CreatePlayer(Player* PlayerInstance, int PlayerID )
{

	PlayerInstance->Texture = charger_texture("crewmate.png");

	PlayerInstance->Sprite = creer_sprite(PlayerInstance->Texture, 25, 25, true);

	PlayerInstance->Sprite.setOrigin(PlayerInstance->Texture.getSize().x / 2, PlayerInstance->Texture.getSize().y / 2);

	return 1;
}

int Player::RefreshPlayer(Player* PlayerInstance)
{
	return 0;
}