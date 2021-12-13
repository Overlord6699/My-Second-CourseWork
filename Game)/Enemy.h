#pragma once
//#include "GameManager.h"
#include "Spawner.h"
#include "Map.h"
#include "Animation.h"
#include "AnimationMove.h"
using namespace sf;

class Enemy : public Spawner, public AnimationMove
{
private:
	Animation* animator;

	const int ENEMY_RECT_WIDTH = 50, ENEMY_RECT_HEIGHT = 58;
	const float ENEMY_SPEED = 0.01;

	void InitBehaviour();
public:
	//const float ENEMY_RECT_SHAPE_WIDTH = 385, ENEMY_RECT_SHAPE_HEIGHT = 140;

	//ddx - ускорение и замедление
	//ограничители
	float ddx;
	float distance;


	Enemy(Texture& image, const float dist, const float b, const int enemyX, const int enemyY);

	void update(const float time, Mover& player);

	void Die() override;

	void Animate(const int id);
	void ProcessAnimation(const float time, const int id);
	void SetAnimationState(const bool state);
};