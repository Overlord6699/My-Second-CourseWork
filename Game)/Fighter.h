#pragma once
#include "Damage.h"

class Fighter
{

public:
    
    //float pushRecoverySpeed = 0.2f;

    void SetAttackState(const bool state);

    bool IsAttacking();
    bool IsAlive();
protected:
    static const int HP_MAX = 3000;
    float HP = HP_MAX;

    bool attack = false;
    bool isAlive = true;

    //float immuneTime = 1;
    //float lastImmune;
    //Vector3 pushDirection;

    int GetHP();
    virtual void SetFullHP();
    virtual void Heal(int healingAmount);
    virtual void ReceiveDamage(Damage dmg);
    virtual void CheckHP();

    virtual void Die();
};
