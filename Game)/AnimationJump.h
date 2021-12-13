#pragma once
#include "AnimStrategy.h"
#include <SFML/Graphics/Sprite.hpp>
using namespace sf;

class AnimationJump : public AnimStrategy
{
private:
	const float JUMP_ANIM_SPEED = 0.003;
	const int JUMP_ANIM_TIME = 4;

	const int JUMP_PICT_TILE_OFFSET_X = 60, JUMP_PICT_TILE_Y = 500,
		JUMP_PICT_WIDTH = 60, JUMP_PICT_HEIGHT = 94;

	float currentFrameJump = 0;
public:
	void Animate(const bool right, Sprite& sprite) override
	{
		if (right)
			sprite.setTextureRect(IntRect(JUMP_PICT_TILE_OFFSET_X * int(currentFrameJump),
				JUMP_PICT_TILE_Y, JUMP_PICT_WIDTH, JUMP_PICT_HEIGHT));
		else
			sprite.setTextureRect(IntRect(JUMP_PICT_TILE_OFFSET_X * int(currentFrameJump)
				+ JUMP_PICT_WIDTH, JUMP_PICT_TILE_Y, -JUMP_PICT_WIDTH, JUMP_PICT_HEIGHT));
	}

	bool ProcessAnimation(const float time, const float speed, const bool isForPlayer) override
	{
		currentFrameJump += JUMP_ANIM_SPEED * time;

		if (currentFrameJump > JUMP_ANIM_TIME) {
			currentFrameJump -= JUMP_ANIM_TIME;
			return true;
		}

		return false;
	}
};