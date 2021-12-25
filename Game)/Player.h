#pragma once
#include "Jumper.h"

#include "Animation.h"
#include "AnimationAttack.h"
#include "AnimationMove.h"
#include "AnimationStay.h"
#include "AnimationJump.h"
#include "AnimationSprintAttack.h"

#include "AbstractNoJumpEnemy.h"


//#include <SFML/Graphics/Sprite.hpp>
using namespace sf;

class Player : public Jumper, public AnimationStay, public AnimationMove,
    public AnimationAttack, public AnimationJump
{
protected:
    

private:
    Animation* animator;

    const float PLAYER_RECT_WIDTH = 50, PLAYER_RECT_HEIGHT = 58;

    void CheckMapBounds();
    void InitBehaviour();
    bool CheckDistance(const FloatRect& enemyRect, const bool checkForPlayer);
public:  
    bool IsAnimated();

    Player(const Texture& image, const int spawnPointX, const int spawnPointY);
    
    void Update(const float time, Player& player, vector<AbstractNoJumpAnimEnemy>& enemies, MusicMaster& musicMaster, GameManager& gameManager, Map& map);
   
    void CheckGround(const int dir, const float time, GameManager& gameManager, Map& map, MusicMaster& musicMaster);
    void Collision(const float time, vector<AbstractNoJumpAnimEnemy>& enemies, GameManager& gameManager, MusicMaster& musMaster);

    void MoveWithSound(const float time, Map& map, MusicMaster& musMaster);
    void DisableMovement();

    void Die(GameManager& gameManager, MusicMaster& musMaster);

    void Start(GameManager& gameManager);

    void ReceiveDamage(const Damage& dmg, GameManager& gameManager);

    void CheckHP() override;

    void Animate(const int id);
    void ProcessAnimation(const float time, const int id);
    void SetAnimationState(const bool state);
};