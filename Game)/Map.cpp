#include "Map.h"

void Map::DealDamageToBlock(const float time)
{
	//пускай пока урон будет = 1
	blockHP_Temp -= 1 * time;
}

void Map::DealDamageToBlockByRun(const float time)
{
	blockHP -= 1 * time;
}

void Map::CheckBlockHealth(MusicMaster& musMaster, const int i, const int j)
{
	if (blockHP_Temp < 0)
	{
        musMaster.PlayNeededSound(musMaster.brokensound);
        TileMap[i][j] = 'u';

		blockHP_Temp = 1500;
	}
}

void Map::ReturnBonuses()
{
    for (int i = 0; i < Map::H; i++)
        for (int j = 0; j < Map::W; j++)
        {
            if (TileMap[i][j] == '1')
                TileMap[i][j] = '0';

            if (TileMap[i][j] == 'k')
                TileMap[i][j] = 'K';

            if (TileMap[i][j] == 's')
                TileMap[i][j] = 'S';

            if (TileMap[i][j] == 'm')
                TileMap[i][j] = 'M';

            if (TileMap[i][j] == 'u')
                TileMap[i][j] = 'U';

            if (TileMap[i][j] == 'p')
                TileMap[i][j] = 'P';
        }

    countY = 1;
}

void Map::RepeatMap(const int FON_WIDTH, const int FON_HEIGHT, Mover& player)
{
	if (0 > FON_WIDTH * (count) - player.offsetX)
		count++;
	if (0 < FON_WIDTH * (count - 1) - player.offsetX)
		count--;
	if (0 > FON_HEIGHT * (countY) - player.offsetY)
		countY++;
	if (0 < FON_HEIGHT * (countY - 1) - player.offsetY)
		countY--;
}
