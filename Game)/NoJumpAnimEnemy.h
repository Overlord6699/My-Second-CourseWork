#pragma once
#include "AbstractNoJumpEnemy.h"
#include "AnimationMove.h"
#include "AnimationAttack.h"

//этот класс предоставляет нужный конструктор для абстракции,
//а также необходимые анимации(бег)
class NoJumpAnimMoveEnemy: public AbstractNoJumpAnimEnemy, public AnimationMove, public AnimationAttack
{
private:
	void InitBehaviour();
public:
	NoJumpAnimMoveEnemy(Texture& image, const float dist,
		const float b, const int enemyX, const int enemyY);
};