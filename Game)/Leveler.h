#pragma once
#include "Fighter.h"

class Leveler: public Fighter
{
public:
	 void SetLevel(const int level);
	 void OnLevelUp();
};