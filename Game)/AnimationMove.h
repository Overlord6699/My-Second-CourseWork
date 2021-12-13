#pragma once
#include "AnimStrategy.h"

class AnimationMove : public AnimStrategy
{
    //В зависимости от кадра координата х будет меняться у спрайта
    const int MOVE_PICT_TILE_OFFSET_X = 65,
        MOVE_PICT_TILE_Y = 430, MOVE_PICT_WIDTH = 50, MOVE_PICT_HEIGHT = 60;

    const float PLAYER_ANIM_TIME = 6;
    const float NORM_SPEED = 0.005;

    float currentFrame = 0;
public:

    void Animate(const bool right, Sprite& sprite)
    {
        if (right)
            sprite.setTextureRect(IntRect(MOVE_PICT_TILE_OFFSET_X * int(currentFrame),
            MOVE_PICT_TILE_Y, MOVE_PICT_WIDTH, MOVE_PICT_HEIGHT));
       else
            sprite.setTextureRect(IntRect(MOVE_PICT_TILE_OFFSET_X * int(currentFrame)
            + MOVE_PICT_WIDTH, MOVE_PICT_TILE_Y, -MOVE_PICT_WIDTH, MOVE_PICT_HEIGHT));
    }

    bool ProcessAnimation(const float time, const float speed, const bool isForPlayer)
    {
        currentFrame += speed * time;

        if (currentFrame > PLAYER_ANIM_TIME) {
            currentFrame -= PLAYER_ANIM_TIME;
            return true;
        }

        return false;
    }
};