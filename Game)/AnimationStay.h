#pragma once
#include "AnimStrategy.h"

class AnimationStay : public AnimStrategy
{
private:
    float currentFramestay = 0;
    
    const int STAY_ANIM_TIME = 4;
    const float NORM_SPEED = 0.005;

    const int STAY_PICT_TILE_OFFSET_X = 60, STAY_PICT_TILE_Y = 0, STAY_PICT_WIDTH = 57,
        STAY_PICT_HEIGHT = 64;

public:
	void Animate(const bool right, Sprite& sprite)
	{
        if (right)
            sprite.setTextureRect(IntRect(STAY_PICT_TILE_OFFSET_X *
                int(currentFramestay), STAY_PICT_TILE_Y, STAY_PICT_WIDTH, STAY_PICT_HEIGHT));
        else
            sprite.setTextureRect(IntRect(STAY_PICT_TILE_OFFSET_X *
                int(currentFramestay) + STAY_PICT_WIDTH, STAY_PICT_TILE_Y,
                -STAY_PICT_WIDTH, STAY_PICT_HEIGHT));
	}

    bool ProcessAnimation(const float time, const float speed, const bool isForPlayer) override
    {
        currentFramestay += speed * time;

        if (currentFramestay > STAY_ANIM_TIME) {
            currentFramestay -= STAY_ANIM_TIME;
            return true;
        }

        return false;
    }
};