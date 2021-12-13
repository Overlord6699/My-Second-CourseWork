#pragma once
#include <list>
#include "Map.h"
#include "MusicMaster.h"
#include "Spawner.h"
#include "Enemy.h"
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "AbstractNoJumpEnemy.h"
#include "AbstractEnemyFactory.h"
#include "NoJumpEnemyFactory.h"
using namespace std;

class GameManager
{
private:
    //константы для одного типа противника
    const int NUM_OF_NOJUMP_ENEMIES = 3;
    const float NOJUMP_ENEMY_DISTANCE = 0.25, NOJUMP_ENEMY_OFFSET = 0.005;
    const float NORMAL_PLAYER_SPEED = 0.0005;
    //

    //для игрока
    const float DEFAULT_JUMP_CULDAWN = 0.35;
    const int DEFAULT_JUMPSCORE = 1, DEFAULT_SPEEDSCORE = 1, DEFAULT_SPEED = 500, FULL_HP = 3000;

    int spawnPointX = 20 * 32;
    int spawnPointY = 35 * 32;
    //

    const int NORMAL_GRAVITY = 100, MAX_GAME_SPEED = 500, MIN_GAME_SPEED = 150, GAME_SPEED_DELTA = 25;

    vector<int> xpTables;

    //скорость  игры(сложность)
    int speed = DEFAULT_SPEED;
    //скорость падения игрока
    double freeFallSpeed = NORMAL_PLAYER_SPEED;


    int speedscore = DEFAULT_SPEEDSCORE;
    int jumpscore = DEFAULT_JUMPSCORE;
    int playerScore = 0;
    int playerHP = FULL_HP;
    int experience = 0;
   
    float gravity = NORMAL_GRAVITY;
public:
    //если игрок умер
    bool isDied = false;
    //справка
    bool reminderIsOpen = false;
    //меню
    bool isPaused = false;
   
    //кулдаун после прыжка
    double jumpCooldawn = DEFAULT_JUMP_CULDAWN;
    double jumpCooldawn1 = DEFAULT_JUMP_CULDAWN;
    double jumpCooldawn2 = DEFAULT_JUMP_CULDAWN;



    //дают информацию другим классам
    float GetFallSpeed();
    int GetPlayerHP();
    void ChangeJumpScore(const bool increase);
    int GetScore();
    int GetSpeedScore();
    int GetJumpScore();
    int GetPlayerSpawnPointX();
    int GetPlayerSpawnPointY();

    void GetEnemySpawnPoint(int& enemyX, int& enemyY, Map& map);
    void CreateEnemies(vector<AbstractNoJumpAnimEnemy>& enemies, Texture& image,
        const AbstractEnemyFactory& factory, Map& map);

    //EXPERIENCE
    int GetCurrentLevel();
    int GetXpToLevel(int level);
    void GrantXp(const int xp, Leveler& player);
    void OnLevelUp(Leveler& player);

    void Respawn(GameManager& gameManager, Spawner& player);

    int GetSpeed();
    void SpeedUp();
    void SpeedDown();

    void ChangeGravity(const float time);
    void SetNormalFallSpeed();

    void SaveState(Mover& player);
    void LoadState(Mover& player);

    void ProcessMap(Mover& player, RenderWindow& gameWindow, RectangleShape& playerRect,
        const Map& map, Sprite& tile);
    
    void SetDefaultValues(Mover& player);

    void OnPlayerDie();
    void OnScoreChange(const int score);
    void OnHitpointChange(const float hp);
    void ChangeSpawnPoint(const int pointX, const int pointY); 
};
