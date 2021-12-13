#pragma once
#include "AnimStrategy.h"

class Animation
{
	//AnimStrategy* _strategy;
	vector<AnimStrategy*> _strategy;
	bool anima = false;
	bool isForPlayer = true;
public:
	bool IsAnimated()
	{
		return anima;
	}

	Animation(AnimStrategy* strategy, const bool isPlayer = true)
	{
		if (strategy != nullptr)
			_strategy.push_back(strategy);

		isForPlayer = isPlayer;
	}

	~Animation()
	{
		_strategy.clear();
	}

	void Set_strategy(AnimStrategy* strategy)
	{
		_strategy.push_back(strategy);
	}


	void SetAnimationState(const bool state)
	{
		anima = state;
	}
	virtual bool ProcessAnim(const float time, const float speed, const int id)
	{
		return this->_strategy[id]->ProcessAnimation(time, speed, isForPlayer);
	}
	virtual void Animate(const bool right, Sprite& sprite, const int id)
	{
		this->_strategy[id]->Animate(right, sprite);
	}
};