#include "Spawner.h"

void Spawner::Spawn()
{
    rect.top = spawnPointY;
    rect.left = spawnPointX;
}

void Spawner::Respawn()
{
    Heal(HP_MAX);
    isAlive = true;

    Spawn();
}

void Spawner::GetSpawnPoint(const int pointX, const int pointY)
{
    spawnPointX = pointX;
    spawnPointY = pointY;
}



