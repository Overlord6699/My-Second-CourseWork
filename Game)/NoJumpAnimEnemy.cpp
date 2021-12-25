#include "NoJumpAnimEnemy.h"

NoJumpAnimEnemy::NoJumpAnimEnemy(Texture& image, const float dist,
	const float b, const int enemyX, const int enemyY)
{
	spawnPointX = enemyX;
	spawnPointY = enemyY;

	sprite.setTexture(image);
	SetSpriteTextureRect(65, 430, 60, 50);

	rect = FloatRect(enemyX, enemyY, ENEMY_WIDTH, ENEMY_HEIGHT);

	GetSpawnPoint(enemyX, enemyY);
	Spawn();

	distance = dist;
	dx = 0;
	ddx = b;
	mov = true;

	animator = new Animation(nullptr, false);
	InitBehaviour();
}

void NoJumpAnimEnemy::InitBehaviour()
{
	animator->Set_strategy(new AnimationMove);
	animator->Set_strategy(new AnimationAttack);
}


