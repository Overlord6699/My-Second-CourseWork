#pragma once
#include "AbstractEnemyFactory.h"
#include "NoJumpAnimEnemy.h"

class NoJumpEnemyFactory: public AbstractEnemyFactory
{
public:
	NoJumpAnimMoveEnemy* CreateNoJumpEnemy(Texture& image,const float dist,
		const float b, const int enemyX, const int enemyY) const 
	{
		return new NoJumpAnimMoveEnemy(image, dist, b, enemyX, enemyY);
	}
};