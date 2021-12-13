#include "UIMaster.h"
#include "Camera.h"
using namespace sf;

/*
void returnObjectsForDebug(Map& map)
{
	for (int i = 0; i < Map::H; i++)
		for (int j = 0; j < Map::W; j++)
		{
			if (map.TileMap[i][j] == '1')
				map.TileMap[i][j] = '0';

			if (map.TileMap[i][j] == 'k')
				map.TileMap[i][j] = 'K';

			if (map.TileMap[i][j] == 's')
				map.TileMap[i][j] = 'S';

			if (map.TileMap[i][j] == 'm')
				map.TileMap[i][j] = 'M';

			if (map.TileMap[i][j] == 'u')
				map.TileMap[i][j] = 'U';

			if (map.TileMap[i][j] == 'p')
				map.TileMap[i][j] = 'P';
		}
}

void getEnemySpawnPoint(int& enemyX, int& enemyY, const Map& map)
{
	for (int i = 0; i < Map::H; i++)
		for (int j = 0; j < Map::W; j++)
			if (map.TileMap[i][j] == 'E') {
				enemyX = j * Map::BLOCK_SIZE;
				enemyY = (i - 1) * Map::BLOCK_SIZE + 5;
			}
}

*/

int main()
{
	const int FON_WIDTH = 920, FON_HEIGHT = 596,
		GAME_WINDOW_WIDTH = 900, GAME_WINDOW_HEIGHT = 600,
		MENU_WINDOW_WIDTH = 600, MENU_WINDOW_HEIGHT = 400,
		MAP_WIDTH = 720, MAP_HEIGHT = 651,
		ENEMY_SPAWN_POINT_X = 270, ENEMY_SPAWN_POINT_Y = 150;

	int enemyX = 0, enemyY = 0;

	GameManager gameManager;
	Map map;
	UIMaster windowMaster;
	
	

	Texture menuTexture;
	Sprite menuFon;

	RenderWindow window(VideoMode(MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT),
		"Play!", Style::Close | Style::Titlebar);
	windowMaster.CreateMenu(window, map, gameManager);
	
	return 0;
}