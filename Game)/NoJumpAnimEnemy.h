#pragma once
#include "AbstractNoJumpEnemy.h"
#include "AnimationMove.h"
#include "AnimationAttack.h"

//���� ����� ������������� ������ ����������� ��� ����������,
//� ����� ����������� ��������(���)
class NoJumpAnimMoveEnemy: public AbstractNoJumpAnimEnemy, public AnimationMove, public AnimationAttack
{
private:
	void InitBehaviour();
public:
	NoJumpAnimMoveEnemy(Texture& image, const float dist,
		const float b, const int enemyX, const int enemyY);
};