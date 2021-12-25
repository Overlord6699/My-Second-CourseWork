#pragma once
#include "AbstractEnemyFactory.h"
#include "NoJumpAnimEnemy.h"

class NoJumpEnemyFactory: public AbstractEnemyFactory
{
public:
	NoJumpAnimEnemy* CreateNoJumpEnemy(Texture& image,const float dist,
		const float b, const int enemyX, const int enemyY) const 
	{
		return new NoJumpAnimEnemy(image, dist, b, enemyX, enemyY);
	}
};