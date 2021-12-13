#pragma once
#include "Spawner.h"
#include "Map.h"
#include "Animation.h"

using namespace sf;

class AbstractNoJumpAnimEnemy: public Spawner
{
protected:
	Animation* animator;

	const int ENEMY_WIDTH = 50, ENEMY_HEIGHT = 58;

	const int ENEMY_LAY_PICT_LEFT = 705, ENEMY_LAY_PICT_TOP = 38,
		ENEMY_LAY_PICT_WIDTH = 64, ENEMY_LAY_PICT_HEIGHT = 38;

	const float ENEMY_SPEED = 0.01;

	//ddx - ускорение и замедление
	//ограничители
	float ddx;
	float distance;
private:
	void LayDown(const float playerOffsetX, const float playerOffsetY) {
		//заставляет противника просто лежать на земле
		sprite.setPosition(rect.left - playerOffsetX, rect.top - playerOffsetY);
		SetSpriteTextureRect(ENEMY_LAY_PICT_LEFT, ENEMY_LAY_PICT_TOP,
			ENEMY_LAY_PICT_WIDTH, ENEMY_LAY_PICT_HEIGHT);
	};
public:
	
	~AbstractNoJumpAnimEnemy() {};

	bool Attack(const float time)
	{
		Animate(1);
		return ProcessAnimation(time, 1);
	}

	void Die() override 
	{
		Fighter::Die();

		DisableHorizontalMovement();

		rect.top += Map::BLOCK_SIZE;
	};

	void UpdateMovement(const float time, const float playerOffsetX, const float playerOffsetY)
	{
		//ограничение движения в углах карты
		if (dx > -distance && !right)
			dx -= NORMAL_SPEED;
		else
			right = true;

		if (dx < distance && right)
			dx += NORMAL_SPEED;
		else
			right = false;

		
		if (mov) {
			Move(time);

			sprite.setPosition(rect.left - playerOffsetX, rect.top - playerOffsetY);

			ProcessAnimation(time, 0);
			Animate(0);
		}
	};

	void Update(const float time, const float playerOffsetX, const float playerOffsetY)
	{
		if (isAlive)
		{
			UpdateMovement(time, playerOffsetX, playerOffsetY);
		}
		else
		{
			LayDown(playerOffsetX, playerOffsetY);
		}
	};

	void Animate(const int id) {
			animator->Animate(right, sprite, id);
	};
	bool ProcessAnimation(const float time, const int id) {
		return animator->ProcessAnim(time, NORMAL_SPEED, id);
	};
	void SetAnimationState(const bool state) {
		animator->SetAnimationState(state);
	};
};