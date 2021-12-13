#pragma once
#include "AnimStrategy.h"

class AnimationSprintAttack : public AnimStrategy
{
private:
	const float ATTACK_ANIM_SPEED = 0.003;
	const int ATTACK_ANIM_TIME = 5;

	const int ATTACK_PICT_TILE_OFFSET_X = 95, ATTACK_PICT_TILE_Y = 360,
		ATTACK_PICT_WIDTH = 78, ATTACK_PICT_HEIGHT = 67;

	float currentFrameAttack = 0;
public:
	void Animate(const bool right, Sprite& sprite) override
	{
		if (right)
			sprite.setTextureRect(IntRect(ATTACK_PICT_TILE_OFFSET_X * int(currentFrameAttack),
				ATTACK_PICT_TILE_Y, ATTACK_PICT_WIDTH, ATTACK_PICT_HEIGHT));
		else
			sprite.setTextureRect(IntRect(ATTACK_PICT_TILE_OFFSET_X * int(currentFrameAttack)
				+ ATTACK_PICT_WIDTH, ATTACK_PICT_TILE_Y, -ATTACK_PICT_WIDTH, ATTACK_PICT_HEIGHT));
	}

	bool ProcessAnimation(const float time, const float speed, const bool isForPlayer) override
	{
		currentFrameAttack += ATTACK_ANIM_SPEED * time;

		if (currentFrameAttack > ATTACK_ANIM_TIME) {
			currentFrameAttack -= ATTACK_ANIM_TIME;
			return true;
		}

		return false;
	}
};