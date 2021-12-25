#pragma once
#include "AbstractNoJumpEnemy.h"
#include "AnimationMove.h"
#include "AnimationAttack.h"

//���� ����� ������������� ������ ����������� ��� ����������,
//� ����� ����������� ��������(���)
class NoJumpAnimEnemy: public AbstractNoJumpAnimEnemy, public AnimationMove, public AnimationAttack
{
private:
	void InitBehaviour();
public:
	NoJumpAnimEnemy(Texture& image, const float dist,
		const float b, const int enemyX, const int enemyY);
};