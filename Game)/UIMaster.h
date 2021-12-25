#pragma once
#include "GameManager.h"
#include "Player.h"
#include <Windows.h>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "Camera.h"
#include "NoJumpEnemyFactory.h"
#include "AbstractNoJumpEnemy.h"
#include "AbstractEnemyFactory.h"

class UIMaster {
private:
	const string GAME_NAME = "Ninja Attack";

	const int FON_WIDTH = 920, FON_HEIGHT = 596,
		GAME_WINDOW_WIDTH = 900, GAME_WINDOW_HEIGHT = 600,
		MENU_WINDOW_WIDTH = 600, MENU_WINDOW_HEIGHT = 400,
		MAP_WIDTH = 720, MAP_HEIGHT = 651,
		ENEMY_SPAWN_POINT_X = 270, ENEMY_SPAWN_POINT_Y = 150;

	const int F1_REMINDER_X = 0, F1_REMINDER_Y = 575;

	void DrawReminderText(RenderWindow& gameWindow, Text& text);
	void LoadCustomIcon(RenderWindow& window);

	void Update(RenderWindow& gameWindow, GameManager& gameManager, Clock& clock,
		Player& player, MusicMaster& musMaster, Map& map, Sprite& fon, Sprite& tile, Text& text, Text& text1,
		Texture& persTileSet, RectangleShape& playerRect, RectangleShape& reminderRect);
public:
	const int REMINDER_X = 270, REMINDER_Y = 90, REMINDER_TEXT_X = 320,
		REMINDER_TEXT_Y = 90, REMINDER_RECT_WIDTH = 385, REMINDER_RECT_HEIGHT = 140,
		DEAD_WINDOW_X = 270, DEAD_WINDOW_Y = 150;

	void DrawReminder(RectangleShape& reminderRect, Text& text, RenderWindow& gameWindow);
	void ModifyText(Text& myText, const Color& color, Uint32 style);
	void DrawNeededText(Text& myText, const String& str, RenderWindow& gameWindow, const float x, const float y);
	void DrawRect(sf::RectangleShape& rect, RenderWindow& gameWindow, const sf::Color& color, const float x, const float y);
	void ShowGameStatistics(Text& myText, RenderWindow& gameWindow, GameManager& gameManager, Mover& player);
	void ShowDeadOrPauseMenu(RenderWindow& gameWindow, Text& text, const bool isDead = true);

	void RedrawFon(Sprite& fon, RenderWindow& gameWindow, const Map& map, const Player& player);

	void CreateUIElement(Texture& tex, const string path, Sprite& spr, const int left, const int top, const int width, const int height);
	void CreateMenu(Map& map, GameManager& gameManager);
	void StartGame(GameManager& gameManager, Map& map);
};
