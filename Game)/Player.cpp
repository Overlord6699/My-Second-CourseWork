#include "Player.h"


void Player::CheckMapBounds()
{
    if (rect.top / Map::BLOCK_SIZE < 1)
        rect.top = (Map::H - 5) * Map::BLOCK_SIZE;
    if (rect.left / Map::BLOCK_SIZE > Map::W - 12)
        rect.left = 14 * Map::BLOCK_SIZE;
    if (rect.left / Map::BLOCK_SIZE < 12)
        rect.left = (Map::W - 14) * Map::BLOCK_SIZE;
}

void Player::InitBehaviour()
{
    animator->Set_strategy(new AnimationStay);
    animator->Set_strategy(new AnimationMove);
    animator->Set_strategy(new AnimationAttack);
    animator->Set_strategy(new AnimationJump);
    animator->Set_strategy(new AnimationSprintAttack);
}

bool Player::IsAnimated()
{
    return animator->IsAnimated();
}

Player::Player(const Texture& image, const int spawnPointX, const int spawnPointY)
{
    animator = new Animation(nullptr);

    InitBehaviour();

    sprite.setTexture(image);
    rect = FloatRect(spawnPointX, spawnPointY, PLAYER_RECT_WIDTH, PLAYER_RECT_HEIGHT);

    GetSpawnPoint(spawnPointX, spawnPointY);
    Spawn();

    dx = dy = 0.1;
    playerOnGround = false;
}

void Player::CheckHP()
{
    if (!attack)
        SetFullHP();
}

void Player::Animate(const int id)
{
    animator->Animate(right, sprite, id);
}

void Player::ProcessAnimation(const float time, const int id)
{
    animator->ProcessAnim(time, NORMAL_SPEED, id);
}

void Player::SetAnimationState(const bool state)
{
    animator->SetAnimationState(state);
}

void Player::DisableMovement()
{
    DisableHorizontalMovement();
    DisableVerticalMovement();
}

void Player::Update(const float time, Player& player, vector<AbstractNoJumpAnimEnemy>& enemies,
    MusicMaster& musicMaster, GameManager& gameManager, Map& map)
{
    if (isAlive) {

        Move(time);

        CheckSprintDirection();

        //при пересечении с противником
        Collision(time, enemies, gameManager, musicMaster);
        //горизонтальная проверка плиток
        CheckGround(0, time, gameManager, map, musicMaster);

        gameManager.ChangeGravity(time);

        if (player.rect.top / Map::BLOCK_SIZE > Map::H - 4)
        {//возвращение всех бонусов при обновлении экрана
            map.ReturnBonuses();

            player.rect.top = 336;
        }

        CheckMapBounds();

        //если игрок не на земле
        if (!playerOnGround)
        {            
            //расчёт скорости падения
            CalculateFallSpeed(time, gameManager);

            if (!player.IsAttacking()) {
                //прыжок вверх
                if (dy < 0) {
                    player.Animate(3);
                    player.ProcessAnimation(time, 3);
                }
                else if (dy > 0) {
                    ProcessFallDirection();
                }
            }
        }
        else {
            gameManager.jumpCooldawn = gameManager.jumpCooldawn1;
            gameManager.SetNormalFallSpeed();
            //присвоение норм значения для прыжка
            ResetJump(gameManager);
        }
        //выставляем по умолчанию
        player.playerOnGround = false;

        ProcessVerticalOffset(time);

        if (IsMoving())
            SetAnimationState(true);


        //проверка коллизии
        Collision(time, enemies, gameManager, musicMaster);
        //вертикальная проверка плиток
        CheckGround(1, time, gameManager, map, musicMaster);

        if (player.playerOnGround && !player.attack)
        {	// анимация движение вправо и влево
            ProcessAnimation(time, 1);

            Animate(1);
        }
        if (!player.IsAnimated() && player.playerOnGround)
        {	//анимация стойки на месте
            ProcessAnimation(time, 0);

            Animate(0);
        }

        //надевает текстуру
        player.sprite.setPosition(player.rect.left - player.offsetX, player.rect.top - player.offsetY);
    }
}

void Player::MoveWithSound(const float time, Map& map, MusicMaster& musMaster)
{
    if (map.blockHP < 0 && playerOnGround && !IsAttacking())
    {
        musMaster.PlayNeededSound(musMaster.RunSound());
        //map.blockHP = map.MAX_BLOCK_HP;
    }
}

void Player::Die(GameManager& gameManager, MusicMaster& musMaster)
{
    Fighter::Die();

    DisableMovement();

    //SetSpriteTextureRect(680, 680, 58,78);
    musMaster.PauseNeededSound(musMaster.RunSound());
    musMaster.PlayNeededSound(musMaster.DeathSound());

    gameManager.OnPlayerDie();
}


void Player::Start(GameManager& gameManager)
{
    gameManager.OnHitpointChange(3000);
}

void Player::ReceiveDamage(const Damage& dmg, GameManager& gameManager)
{
    //посмотреть на наследование от Fighter
    if (!isAlive)
        return;
        
    Fighter::ReceiveDamage(dmg);
    gameManager.OnHitpointChange(HP);
}


void Player::CheckGround(const int dir, const float time, GameManager& gameManager, Map& map, MusicMaster& musicMaster)
{
    //dir = 0 - горизонтальное направление, 1 - вертик

    for (int i = rect.top / Map::BLOCK_SIZE; i < (rect.top + rect.height) / Map::BLOCK_SIZE; i++)
        for (int j = rect.left / Map::BLOCK_SIZE; j < (rect.left + rect.width) / Map::BLOCK_SIZE; j++)
        {
            //это физ.блоки, с которыми можно взаимодействовать
            if (map.TileMap[i][j] == 'B' || map.TileMap[i][j] == 'O' || map.TileMap[i][j] == 'U')
            {
                if (dx > 0 && dir == 0) {
                    rect.left = j * Map::BLOCK_SIZE - rect.width;
                    dx = 0;
                    musicMaster.PauseNeededSound(musicMaster.RunSound());
                }
                if (dx < 0 && dir == 0) {
                    rect.left = (j + 1) * Map::BLOCK_SIZE;
                    dx = 0;
                    musicMaster.PauseNeededSound(musicMaster.RunSound());
                }
                if (dy > 0 && dir == 1) {
                    rect.top = i * Map::BLOCK_SIZE - rect.height;
                    dy = 0;
                    playerOnGround = true;
                }
                if (dy < 0 && dir == 1) {
                    rect.top = (i + 1) * Map::BLOCK_SIZE;
                    dy = 0;
                    multijump = false;
                }
            }
            if (map.TileMap[i][j] == '0')
            {
                //замена в кастомных целях
                map.TileMap[i][j] = '1';
                gameManager.OnScoreChange(1);
            }
            if (map.TileMap[i][j] == 'J')
            {
                map.TileMap[i][j] = ' ';

                AllowJumping(gameManager);
            }
            if (map.TileMap[i][j] == 'K')
            {
                map.TileMap[i][j] = 'k';
                if (gameManager.jumpCooldawn1 < 1)
                {
                    gameManager.jumpCooldawn1 += JUMP_HEIGHT_BONUSE;
                    gameManager.ChangeJumpScore(true);
                }
            }
            if (map.TileMap[i][j] == 'P')
            {
                map.TileMap[i][j] = 'p';
                if (gameManager.jumpCooldawn1 > NORMAL_JUMP_HEIGHT)
                {
                    gameManager.jumpCooldawn1 -= JUMP_HEIGHT_BONUSE;
                    gameManager.ChangeJumpScore(false);
                }
            }
            if (map.TileMap[i][j] == 'L')
            {
                Die(gameManager, musicMaster);
            }
            if (map.TileMap[i][j] == 'S')
            {
                map.TileMap[i][j] = 's';
                //увеличение скорости игры
                gameManager.SpeedUp();
            }
            if (map.TileMap[i][j] == 'M')
            {
                map.TileMap[i][j] = 'm';
                //уменьшение скорости игры
                gameManager.SpeedDown();
            }
            if (map.TileMap[i][j] == 'U')
            {
                if (attack) {
                    map.DealDamageToBlock(time);
                    map.CheckBlockHealth(musicMaster, i, j);
                }
                /*
                * if (GetHP() < 2)
                {
                    musicMaster.PlayBrokenSound();
                    map.TileMap[i][j] = 'u';
                    SetFullHP();
                }
                */               
            }
            if (map.TileMap[i][j] == 'Y')
            {
                map.TileMap[i][j] = ' ';

                gameManager.ChangeSpawnPoint((j) * Map::BLOCK_SIZE, (i - 2) * Map::BLOCK_SIZE);
                GetSpawnPoint((j) * Map::BLOCK_SIZE, (i - 2) * Map::BLOCK_SIZE);
            }
        }
}

bool Player::CheckDistance(const FloatRect& enemyRect, const bool checkForPlayer = true)
{
    if (checkForPlayer) {
        if (abs(enemyRect.left - rect.left) < Map::BLOCK_SIZE / 2 &&
            abs(enemyRect.top - rect.top) < Map::BLOCK_SIZE / 2)
            return true;
    }
    else //для противника расстояние немного больше. Его также можно увеличивать по ходу игры
    {
        if (abs(enemyRect.left - rect.left) < Map::BLOCK_SIZE / 2 + 20 &&
            abs(enemyRect.top - rect.top) < Map::BLOCK_SIZE / 2 + 20)
            return true;
    }

    return false;
}

void Player::Collision(const float time, vector<AbstractNoJumpAnimEnemy>& enemies, GameManager& gameManager, MusicMaster& musMaster)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        if ((CheckDistance(enemies[i].rect, false) &&
            !attack && enemies[i].IsAlive() && isAlive) || enemies[i].IsAttacking())
        {
            if (enemies[i].rect.left > rect.left)
                enemies[i].SetLeftDirection();
            else
                enemies[i].SetRightDirection();

            enemies[i].SetMoveState(false);
            enemies[i].SetAttackState(true);

            //если прошла анимация атаки противника
            if (enemies[i].Attack(time)) {
                Die(gameManager, musMaster);//игрока убили

                enemies[i].SetAttackState(false);
                //enemy.SetMoveState(true);
            }

        }

        //убили противника
        if (enemies[i].IsAlive())
            if (CheckDistance(enemies[i].rect) && attack)
            {
                enemies[i].Die();
                gameManager.OnScoreChange(10);
                gameManager.GrantXp(10, *this);
            }
    }
}
