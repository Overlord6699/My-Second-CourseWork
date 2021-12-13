#pragma once
#include "AbstractNoJumpEnemy.h"

class AbstractEnemyFactory 
{
public: 
	virtual AbstractNoJumpAnimEnemy* CreateNoJumpEnemy(Texture& image, const float dist,
		const float b, const int enemyX, const int enemyY) const = 0;
};