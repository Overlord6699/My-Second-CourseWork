#pragma once
#include "Spawner.h"
#include "GameManager.h"

class Jumper: public Spawner 
{
private:
    

protected:
    const float MAX_FREE_FALL_SPEED = 0.26;

    const float JUMP_HEIGHT_BONUSE = 0.0125, NORMAL_JUMP_HEIGHT = 0.1875,
        JUMP_DELTA = 0.17;

    const int JUMP_PICT_WIDTH = 65, JUMP_PICT_HEIGHT = 85;
    const int JUMP_PICT_TILE_X = 180, JUMP_PICT_TILE_Y = 510;


    float dy = 0;
    bool multijump = false;

    void DisableVerticalMovement();
public:

    //ниндзя крутые и делают больше одного прыжка
    void ProcessMultiJump(GameManager& gameManager, MusicMaster& musMaster);
    void ProcessFallDirection();
    void Jump(const GameManager& gameManager, MusicMaster& musMaster);
    void ResetJump(GameManager& gameManager);
    void AllowJumping(GameManager& gameManager);
    void Fall(const float time, GameManager& gameManager);
    void ProcessVerticalOffset(const float time);
};
