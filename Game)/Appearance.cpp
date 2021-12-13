#include "Appearance.h"

void Appearance::SetSpriteTextureRect(const int left, const int top, const int width, const int height)
{
    sprite.setTextureRect(IntRect(left, top, width, height));
}

void Appearance::SwapSprite(int skinId)
{
}