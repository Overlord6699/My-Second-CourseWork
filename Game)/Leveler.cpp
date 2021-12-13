#include "Leveler.h"

void Leveler::OnLevelUp()
{
    SetFullHP();
}

void Leveler::SetLevel(const int level)
{
    for (int i = 0; i < level; i++)
    {
        OnLevelUp();
    }
}