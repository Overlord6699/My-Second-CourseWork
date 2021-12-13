#include "Camera.h"

void Camera::KeepPlayerAtTheCenter(const int GAME_WINDOW_WIDTH, const int GAME_WINDOW_HEIGHT, Mover& player)
{	
	/*
	* if (player.rect.left > 350 && player.rect.left < 325 + Map::W * 27)
		player.offsetX = player.rect.left - GAME_WINDOW_WIDTH / 2;

	if (player.rect.top > 200 && player.rect.top < Map::H * 23)
		player.offsetY = player.rect.top - GAME_WINDOW_HEIGHT / 2;
	*/
	player.offsetX = player.rect.left - GAME_WINDOW_WIDTH / 2;
	player.offsetY = player.rect.top - GAME_WINDOW_HEIGHT / 2;
}