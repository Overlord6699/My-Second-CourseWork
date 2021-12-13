#pragma once
#include "Leveler.h"
#include "Mover.h"

class Spawner : public Leveler, public Mover
{
protected:
	int spawnPointX;
	int spawnPointY;

public:
	virtual void Spawn();
	virtual void Respawn();
	void GetSpawnPoint(const int pointX, const int pointY);
};