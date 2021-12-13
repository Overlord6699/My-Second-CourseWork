#include "Fighter.h"

 
void Fighter::ReceiveDamage(Damage dmg)
{
    HP -= dmg.damageAmount;

    if (HP <= 0)
    {
        HP = 0;
        Die();
    }
}


void Fighter::SetFullHP()
{
    HP = HP_MAX;
}

void Fighter::CheckHP()
{

}

int Fighter::GetHP()
{
    return HP;
}

void Fighter::SetAttackState(const bool state)
{
    attack = state;
}

bool Fighter::IsAttacking()
{
    return attack;
}

bool Fighter::IsAlive()
{
    return isAlive;
}

void Fighter::Heal(int healingAmount)
{
    if (HP == HP_MAX)
        return;

    HP += healingAmount;
    if (HP > HP_MAX)
        HP = HP_MAX;
    //gameManager.instance.ShowText("+" + healingAmount.ToString() + "hp", 25, Color.green, transform.position, Vector3.up * 30, 1f);
    //gameManager.OnHitpointChange();
}

void Fighter::Die()
{
    isAlive = false;
}
