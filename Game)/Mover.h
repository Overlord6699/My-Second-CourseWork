#pragma once
#include "Appearance.h"
using namespace sf;

class Mover: public Appearance
{

protected:
    const float NORMAL_SPEED = 0.005, SHIFT_SPEED = 0.05;
    
    const float BRAKING_SPEED = 0.1 / 50, MAX_SPEED = 0.1, MAX_SHIFT_SPEED = 0.2;

    //движение
    float dx = 0;
    //направление
    bool right = true;
    //идёт игрок
    bool mov = false;
    //игрок бежит = нажат шифт
    bool shift = false;
    
    //нужно для связи с GameManager
    //возможность сделать multijump(возвращает значение для multijump)
    bool multijumptr = false;

    virtual void CheckMoveDirection();
    virtual void Move(const float time);
    //попробовать оптимизировать
    virtual void Shift();
    virtual void DisableHorizontalMovement();

public:
   
    //смещение персонажа
    float offsetX = 0, offsetY = 0;
    bool playerOnGround = false;

    bool CanMultiJump();
    void SetMultiJump(const bool state);

    void SetLeftDirection();
    void SetRightDirection();

    void CheckShifting();
    bool IsMoving();
    bool IsSprinting();
    void SetMoveState(const bool state);
    void SetSprintState(const bool state);
};
