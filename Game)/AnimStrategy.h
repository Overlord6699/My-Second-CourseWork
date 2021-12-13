#pragma once

class AnimStrategy
{
protected:
public:
    virtual ~AnimStrategy() {};

    virtual void Animate(const bool right, Sprite& sprite) {};
    virtual bool ProcessAnimation(const float time, const float speed, const bool isForPlayer) {
        return true;
    };
};