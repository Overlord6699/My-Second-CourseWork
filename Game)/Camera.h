#pragma once
#include "Map.h"

static class Camera {
public:
	static void KeepPlayerAtTheCenter(const int GAME_WINDOW_WIDTH, const int GAME_WINDOW_HEIGHT, Mover& player);
};