#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
using namespace sf;

class Appearance 
{
public:
	FloatRect rect;
	Sprite sprite;

	void SwapSprite(int skinId);
	void SetSpriteTextureRect(const int left, const int top, const int width, const int height);
};