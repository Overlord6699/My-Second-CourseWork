#include "Jumper.h"


void Jumper::ProcessMultiJump(GameManager& gameManager, MusicMaster& musMaster)
{
    if (!playerOnGround && multijump) {
        musMaster.PlayNeededSound(musMaster.jumpsound);

        dy = 0;
        dy -= gameManager.jumpCooldawn;
        gameManager.jumpCooldawn2 -= 0.005;

        if (gameManager.jumpCooldawn2 < 0.05)
            multijump = false;
    }
}

void Jumper::DisableVerticalMovement()
{
    dy = 0;
}


void Jumper::ProcessFallDirection()
{   
    if (right) //надеваем другой спрайт
        SetSpriteTextureRect(JUMP_PICT_TILE_X, JUMP_PICT_TILE_Y,
            JUMP_PICT_WIDTH, JUMP_PICT_HEIGHT);
    else
        SetSpriteTextureRect(JUMP_PICT_TILE_X + JUMP_PICT_WIDTH,
            JUMP_PICT_TILE_Y, -JUMP_PICT_WIDTH, JUMP_PICT_HEIGHT);
}

void Jumper::Jump(const GameManager& gameManager, MusicMaster& musMaster)
{
    if (playerOnGround) {
        musMaster.PlayNeededSound(musMaster.jumpsound);

        dy = 0;
        dy -= gameManager.jumpCooldawn;
    }
}

void Jumper::ResetJump(GameManager& gameManager)
{
    if (multijumptr) {
        multijump = true;
        gameManager.jumpCooldawn2 = gameManager.jumpCooldawn1;
    }
}

void Jumper::AllowJumping(GameManager& gameManager)
{
    if (!multijumptr)
    {
        multijump = true;
        multijumptr = true;
        gameManager.jumpCooldawn1 -= JUMP_DELTA;
    }
}

void Jumper::Fall(const float time, GameManager& gameManager)
{
    if (dy < MAX_FREE_FALL_SPEED)
        dy = dy + gameManager.GetFallSpeed() * time;
}

void Jumper::ProcessVerticalOffset(const float time)
{
    rect.top += dy * time;
}
