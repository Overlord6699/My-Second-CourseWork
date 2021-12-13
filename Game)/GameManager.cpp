#include "GameManager.h"

float GameManager::GetFallSpeed()
{
    return freeFallSpeed;
}

int GameManager::GetPlayerHP()
{
    return playerHP;
}

void GameManager::ChangeJumpScore(const bool increase)
{
    if (increase)
        jumpscore++;
    else
        jumpscore--;
}

int GameManager::GetScore() {
    return playerScore;
}

int GameManager::GetSpeedScore()
{
    return speedscore;
}

int GameManager::GetJumpScore()
{
    return jumpscore;
}

int GameManager::GetPlayerSpawnPointX()
{
    return spawnPointX;
}

int GameManager::GetPlayerSpawnPointY()
{
    return spawnPointY;
}

//EXPERIENCE
int GameManager::GetCurrentLevel()
{
    int level = 0;
    int add = 0;

    while (experience >= add)
    {
        add += xpTables[level];
        level++;

        if (level == xpTables.size())// max level
        {
            return level;
        }
    }

    return level;
}

int GameManager::GetXpToLevel(int level)
{
    int index = 0;
    int xp = 0;

    while (index < level)
    {
        xp += xpTables[index];
        index++;
    }

    return xp;
}

void GameManager::GrantXp(const int xp, Leveler& player)
{
    int currLevel = GetCurrentLevel();
    experience += xp;
    if (currLevel < GetCurrentLevel())
    {
        OnLevelUp(player);
    }
}

void GameManager::OnLevelUp(Leveler& player)
{
    player.OnLevelUp();
    OnHitpointChange(3000);
}

void GameManager::OnScoreChange(const int score)
{
    playerScore += score;
}

void GameManager::SetDefaultValues(Mover& player)
{
    playerScore = 0;
    speed = DEFAULT_SPEED;
    jumpCooldawn1 = DEFAULT_JUMP_CULDAWN;
    speedscore = DEFAULT_SPEEDSCORE;
    jumpscore = DEFAULT_JUMPSCORE;

    player.SetMultiJump(false);
}

void GameManager::OnPlayerDie()
{
    isDied = true;
}

//отрисовка карты
void GameManager::ProcessMap(Mover& player, RenderWindow& gameWindow, RectangleShape& playerRect,
    const Map& map, Sprite& tile)
{
    for (int i = 0; i < Map::H; i++)
        for (int j = 0; j < Map::W; j++)
        {

            if (map.TileMap[i][j] == 'O') {
                playerRect.setFillColor(Color::Transparent);
                playerRect.setPosition(j * 32 - player.offsetX, i * 32 - player.offsetY);
                gameWindow.draw(playerRect);
                continue;
            }
            else if (map.TileMap[i][j] == 'B') {
                tile.setTextureRect(IntRect(720, 651, 32, 32));
            }
            else if (map.TileMap[i][j] == 'J' && !player.CanMultiJump()) {
                tile.setTextureRect(IntRect(0, 32, 32, 32));
            }
            else if (map.TileMap[i][j] == 'K') {
                tile.setTextureRect(IntRect(0, 0, 32, 32));
            }
            else if (map.TileMap[i][j] == 'L') {
                tile.setTextureRect(IntRect(96, 0, 32, 32));
            }
            else if (map.TileMap[i][j] == '0') {
                tile.setTextureRect(IntRect(236, 458, 32, 32));
            }
            else if (map.TileMap[i][j] == 'S') {
                tile.setTextureRect(IntRect(64, 0, 32, 32));
            }
            else if (map.TileMap[i][j] == 'M') {
                tile.setTextureRect(IntRect(32, 0, 32, 32));
            }
            else if (map.TileMap[i][j] == 'U') {
                tile.setTextureRect(IntRect(230, 745, 32, 32));
            }
            else if (map.TileMap[i][j] == 'Y') {
                tile.setTextureRect(IntRect(750, 726, 32, 32));
            }
            else if (map.TileMap[i][j] == 'P') {
                tile.setTextureRect(IntRect(32, 32, 32, 32));
            }
            else if (map.TileMap[i][j] == ' ')
                continue;

            else
                continue;

            tile.setPosition(j * 32 - player.offsetX, i * 32 - player.offsetY);
            gameWindow.draw(tile);
        }
}



void GameManager::ChangeGravity(const float time)
{
    if (gravity > 0)
        gravity -= 0.1 * time;
}

void GameManager::GetEnemySpawnPoint(int& enemyX, int& enemyY, Map& map)
{
    for (int i = 0; i < Map::H; i++)
        for (int j = 0; j < Map::W; j++)
            if (map.TileMap[i][j] == 'E') {
                enemyX = j * Map::BLOCK_SIZE;
                enemyY = (i - 1) * Map::BLOCK_SIZE + 5;

                map.TileMap[i][j] = 'e';

                return;
            }
}

void GameManager::CreateEnemies(vector<AbstractNoJumpAnimEnemy>& enemies, Texture& image,
    const AbstractEnemyFactory& factory, Map& map)
{
    int enemyX, enemyY;

    for (int i = 0; i < NUM_OF_NOJUMP_ENEMIES; i++) {
        GetEnemySpawnPoint(enemyX, enemyY, map);

        AbstractNoJumpAnimEnemy* enemy = factory.CreateNoJumpEnemy(image,
            NOJUMP_ENEMY_DISTANCE, NOJUMP_ENEMY_OFFSET, enemyX, enemyY);

        enemies.push_back(*enemy);
    }
}

void GameManager::SetNormalFallSpeed()
{
    freeFallSpeed = NORMAL_PLAYER_SPEED;
}


void GameManager::OnHitpointChange(const float hp)
{
    playerHP = hp;
}

void GameManager::SaveState(Mover& player)
{
    std::ofstream out("saves//save.txt");
    if (out.is_open())
    {

        out << spawnPointX << "\n";
        out << spawnPointY << "\n";
        out << playerScore << "\n";
        out << speed << "\n";
        out << jumpCooldawn1 << "\n";
        out << player.CanMultiJump() << "\n";
        out << speedscore << "\n";
        out << jumpscore << "\n";
    }
    out.close();
        
}
//загрузка из файла
void GameManager::LoadState(Mover& player)
{
    string line;
    ifstream in("saves//save.txt");
    if (in.is_open())
    {
        int f = 0;
        while (getline(in, line))
        {
            if (f == 0)
                spawnPointX = stoi(line);
            if (f == 1)
                spawnPointY = stoi(line);
            if (f == 2)
                playerScore = stoi(line);
            if (f == 3)
                speed = stof(line);
            if (f == 4)
                jumpCooldawn1 = stof(line);
            if (f == 5)
                player.SetMultiJump(stoi(line));
            if (f == 6)
                speedscore = stoi(line);
            if (f == 7)
                jumpscore = stoi(line);

            f++;
        }
    }

    in.close();
}


void GameManager::Respawn(GameManager& gameManager, Spawner& player)
{
    player.Respawn();
}

int GameManager::GetSpeed() {
    return speed;
}

void GameManager::SpeedUp()
{
    if (speed > MIN_GAME_SPEED)
    {
        speed -= GAME_SPEED_DELTA;
        speedscore++;
    }
}

void GameManager::SpeedDown()
{
    if (speed < MAX_GAME_SPEED)
    {
        speed += GAME_SPEED_DELTA;
        speedscore--;
    }
}

void GameManager::ChangeSpawnPoint(const int pointX, const int pointY)
{
    spawnPointX = pointX;
    spawnPointY = pointY;
}


