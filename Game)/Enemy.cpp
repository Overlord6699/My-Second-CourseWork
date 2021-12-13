#include "Enemy.h"
	
Enemy::Enemy(Texture& image, const float dist, const float b, const int enemyX, const int enemyY)
{
	spawnPointX = enemyX;
	spawnPointY = enemyY;

	sprite.setTexture(image);
	//rect = FloatRect(enemyX, enemyY, ENEMY_RECT_WIDTH, ENEMY_RECT_HEIGHT);

	distance = dist;
	dx = 0;
	ddx = b;

	animator = new Animation(nullptr, false);
	InitBehaviour();
}

void Enemy::InitBehaviour()
{
	animator->Set_strategy(new AnimationMove);
}

void Enemy::Animate(const int id)
{
	animator->Animate(right, sprite, id);
}

void Enemy::ProcessAnimation(const float time, const int id)
{
	animator->ProcessAnim(time, NORMAL_SPEED, id);
}

void Enemy::SetAnimationState(const bool state)
{
	animator->SetAnimationState(state);
}

void Enemy::update(const float time, Mover& player)
{
	if (isAlive)
	{
		Move(time);

		//ограничение движения в углах карты
		if (dx > -distance && !right)
			dx -= NORMAL_SPEED;
		else
			right = true;

		if (dx < distance && right)
			dx += NORMAL_SPEED;
		else
			right = false;

	
		sprite.setPosition(rect.left - player.offsetX, rect.top - player.offsetY);

		ProcessAnimation(time, 0);
		Animate(0);
	}
	else
	{
		//заставляет противника просто лежать на карте
		sprite.setPosition(rect.left - player.offsetX, rect.top - player.offsetY);
		sprite.setTextureRect(IntRect(705, 38, 64, 38));
	}
}


void Enemy::Die()
{
	Fighter::Die();

	rect.top += Map::BLOCK_SIZE;
}
