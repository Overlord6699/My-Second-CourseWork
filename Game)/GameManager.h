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
    //��������� ��� ������ ���� ����������
    int NUM_OF_NOJUMP_ENEMIES = 3, curNumberOfEnemies = 0;
    const float NOJUMP_ENEMY_DISTANCE = 0.25, NOJUMP_ENEMY_OFFSET = 0.005;
    const float NORMAL_PLAYER_SPEED = 0.0005;
    //

    //��� ������
    const float DEFAULT_JUMP_CULDAWN = 0.35;
    const int DEFAULT_JUMPSCORE = 1, DEFAULT_SPEEDSCORE = 1, DEFAULT_SPEED = 500, FULL_HP = 3000;

    int spawnPointX = 19 * 32;
    int spawnPointY = 30 * 32;
    //

    const int NORMAL_GRAVITY = 100, MAX_GAME_SPEED = 500, MIN_GAME_SPEED = 150, GAME_SPEED_DELTA = 25;

    //���-�� ����� ��� ������ ������. �� ��������� ������ �������
    vector<int> xpTables = { 30, 70 };
    //���-�� ����������� ��� 0 - n ������
    vector<int> numOfEnemies = { 3, 3, 4, 5 };

    //��������  ����(���������)
    int speed = DEFAULT_SPEED;
    //�������� ������� ������
    double freeFallSpeed = NORMAL_PLAYER_SPEED;


    int speedscore = DEFAULT_SPEEDSCORE;
    int jumpscore = DEFAULT_JUMPSCORE;
    int playerScore = 0;
    int playerHP = FULL_HP;
    int experience = 0;
   
    float gravity = NORMAL_GRAVITY;
public:
    //���� ����� ����
    bool isDied = false;
    //�������
    bool reminderIsOpen = false;
    //����
    bool isPaused = false;
   
    //������� ����� ������
    double jumpCooldawn = DEFAULT_JUMP_CULDAWN;
    double jumpCooldawn1 = DEFAULT_JUMP_CULDAWN;
    double jumpCooldawn2 = DEFAULT_JUMP_CULDAWN;

    //����������
    vector<AbstractNoJumpAnimEnemy> enemies;

    //���� ���������� ������ �������
    float GetFallSpeed();
    int GetPlayerHP();
    void ChangeJumpScore(const bool increase);
    int GetScore();
    int GetSpeedScore();
    int GetJumpScore();
    int GetPlayerSpawnPointX();
    int GetPlayerSpawnPointY();

    void SpawnNewEnemies(Texture& image, Map& map);
    void RespawnEnemies();
    void GetEnemySpawnPoint(int& enemyX, int& enemyY, Map& map);
    void CreateEnemies(Texture& image, Map& map);
    void CreateCustomEnemies(Texture& image,
        const AbstractEnemyFactory& factory, Map& map);

    //����
    int GetCurrentLevel();
    int GetXpToLevel(int level);
    void GrantXp(const int xp, Leveler& player);
    void OnLevelUp(Leveler& player);

    void Respawn(Spawner& player);

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
