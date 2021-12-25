#include "Mover.h"

bool Mover::CanMultiJump()
{
    return multijumptr;
}

void Mover::SetMultiJump(const bool state)
{
    multijumptr = state;
}

void Mover::SetLeftDirection()
{
    right = false;
}

void Mover::SetRightDirection()
{
    right = true;
}

void Mover::CheckShifting()
{
    if (shift)
        Shift();
    else
        (right)? dx = MAX_SPEED : dx = -MAX_SPEED;
}

bool Mover::IsMoving()
{
    if (dx != 0)
        return true;

    return false;
}

bool Mover::IsSprinting()
{
    return shift;
}

void Mover::SetMoveState(const bool state)
{
    mov = state;
}

void Mover::SetSprintState(const bool state)
{
    shift = state;
}

void Mover::CheckSprintDirection()
{
    if (dx > MAX_SPEED && !mov)
        dx -= BRAKING_SPEED; //жмём на тормоза
    else
        if (dx < -MAX_SPEED && !mov)
            dx += BRAKING_SPEED;
        else
            if (!mov)
            {
                dx = 0;
            }
}

void Mover::Move(const float time)
{
    //dx - смещение
    rect.left += dx * time;
}

void Mover::Shift()
{
    if (right) {
        if (dx < MAX_SHIFT_SPEED)
            if (right == true)
                dx += BRAKING_SPEED;
            else
                dx += SHIFT_SPEED;
    }
    else {
        if (dx > -MAX_SHIFT_SPEED)
            if (right == false)
                dx -= BRAKING_SPEED;
            else
                dx -= SHIFT_SPEED;
    }
}

void Mover::DisableHorizontalMovement()
{
    dx = 0;
}


