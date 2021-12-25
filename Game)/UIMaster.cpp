#include "UIMaster.h"


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

void UIMaster::LoadCustomIcon(RenderWindow& window)
{
	Image icon;

	icon.loadFromFile("pictures/icon1.png");
	window.setIcon(32, 32, icon.getPixelsPtr());
}

void UIMaster::Update(RenderWindow& gameWindow, GameManager& gameManager, Clock& clock,
	Player& player, MusicMaster& musMaster, Map& map, Sprite& fon, Sprite& tile, Text& text, Text& text1,
	Texture& persTileSet, RectangleShape& playerRect, RectangleShape& reminderRect)
{
	while (gameWindow.isOpen())
	{
		try
		{
			//получаем время
			float time = clock.getElapsedTime().asMicroseconds();
			clock.restart();

			time /= gameManager.GetSpeed();


			player.SetMoveState(false);

			//player.CheckHP();

			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				if (gameManager.isDied || gameManager.reminderIsOpen || gameManager.isPaused)
					musMaster.PlayFonMusic();

				gameManager.isPaused = false;
				gameManager.reminderIsOpen = false;

				if (gameManager.isDied)
				{
					//нужно возобновить противников
					gameManager.RespawnEnemies();

					musMaster.PauseNeededSound(musMaster.DeathSound());
					gameManager.Respawn((Spawner&)player);
					gameManager.SetDefaultValues((Mover&)player);

					gameManager.isDied = false;
				}
			}
			//закрытие игры
			Event event;
			while (gameWindow.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					gameManager.SaveState((Mover&)player);

					gameWindow.close();
				}
			}
			//пауза или смерть
			if (gameManager.isDied || gameManager.isPaused)
			{
				gameManager.SaveState((Mover&)player);

				musMaster.PauseFonMusic();

				player.DisableMovement();

				DrawRect(reminderRect, gameWindow, Color::Green,
					DEAD_WINDOW_X, DEAD_WINDOW_Y);

				if (gameManager.isPaused)
				{
					ShowDeadOrPauseMenu(gameWindow, text1, false);
				}
				if (gameManager.isDied)
				{
					ShowDeadOrPauseMenu(gameWindow, text1);
				}

				if (gameManager.reminderIsOpen)//справка
				{
					//отрисовка  окошка с текстом
					DrawReminder(reminderRect, text1, gameWindow);

				}
				gameWindow.display();
				continue;
			}

			player.SetAttackState(false);
			player.SetAnimationState(false);


			if (Keyboard::isKeyPressed(Keyboard::LShift))
			{
				player.SetSprintState(true);
			}
			else
				player.SetSprintState(false);

			if (Keyboard::isKeyPressed(Keyboard::LControl))//атака
			{
				musMaster.PauseNeededSound(musMaster.RunSound());
				musMaster.PlayNeededSound(musMaster.PunchSound());

				player.SetAttackState(true);
				player.SetAnimationState(true);

				if (player.IsSprinting()) {
					player.Animate(4);
					player.ProcessAnimation(time, 4);
				}
				else {
					player.Animate(2);
					player.ProcessAnimation(time, 2);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				player.MoveWithSound(time, map, musMaster);
				map.DealDamageToBlockByRun(time);

				player.SetMoveState(true);
				player.SetAnimationState(true);

				//идём влево
				player.SetLeftDirection();

				player.CheckShifting();
			}
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				player.MoveWithSound(time, map, musMaster);
				map.DealDamageToBlockByRun(time);

				player.SetMoveState(true);
				player.SetAnimationState(true);

				//идём вправо
				player.SetRightDirection();

				player.CheckShifting();
			}

			if (!player.IsMoving())
				musMaster.PauseNeededSound(musMaster.RunSound());

			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				player.Jump(gameManager, musMaster);
				player.ProcessMultiJump(gameManager, musMaster);

				musMaster.PauseNeededSound(musMaster.RunSound());
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				gameManager.isPaused = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::R))//респаун
			{
				gameManager.Respawn(player);
			}
#ifdef DEBUG
			if (Keyboard::isKeyPressed(Keyboard::Tab))
			{
				returnObjectsForDebug(map);
			}
#endif
			if (Keyboard::isKeyPressed(Keyboard::F1))
			{
				gameManager.reminderIsOpen = true;
				gameManager.isPaused = true;
			}

			player.Update(time, player, gameManager.enemies, musMaster, gameManager, map);

			for (int i = 0; i < gameManager.enemies.size(); i++)
				gameManager.enemies[i].Update(time, player.offsetX, player.offsetY);


			//удержание игрока в центре экрана
			if (player.IsAlive()) //проверка позволила избавиться от дёрганий после смерти
				Camera::KeepPlayerAtTheCenter(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, (Mover&)player);

			//обработка бесконечной карты
			map.RepeatMap(FON_WIDTH, FON_HEIGHT, (Mover&)player);
			RedrawFon(fon, gameWindow, map, player);

			//обработка правил на карте
			gameManager.ProcessMap((Mover&)player, gameWindow, playerRect, map, tile);

			//отрисовка данных каждый кадр
			ShowGameStatistics(text, gameWindow, gameManager, player);

			DrawReminderText(gameWindow, text);

			gameWindow.draw(player.sprite);

			for (int i = 0; i < gameManager.enemies.size(); i++)
				gameWindow.draw(gameManager.enemies[i].sprite);

			gameWindow.display();

			//проверка уровня для спавна новых противников
			gameManager.SpawnNewEnemies(persTileSet, map);
		}
		catch (...)
		{
			player.GetSpawnPoint(gameManager.GetPlayerSpawnPointX(), gameManager.GetPlayerSpawnPointY());
			player.Spawn();
		}
	}
}

void UIMaster::CreateMenu(Map& map, GameManager& gameManager) {
	Texture menuTexture;
	Sprite menuFon;

	RenderWindow gameWindow;

	RenderWindow window(VideoMode(MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT),
		GAME_NAME, Style::Close | Style::Titlebar);

	CreateUIElement(menuTexture, "pictures/play.png",
		menuFon, 0, 0, MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);

	window.draw(menuFon);
	window.display();

	LoadCustomIcon(window);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}//запуск игры

		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			window.close();

			StartGame(gameManager, map);
		}
	}
}

void UIMaster::StartGame(GameManager&  gameManager, Map& map)
{
	//для течения времени
	Clock clock;
	MusicMaster musMaster;
	Texture persTileSet;


	persTileSet.loadFromFile("pictures//pers.png");

	Player player(persTileSet, gameManager.GetPlayerSpawnPointX(), gameManager.GetPlayerSpawnPointY());

	gameManager.CreateEnemies(persTileSet, map);

	//хитбокс
	RectangleShape playerRect(Vector2f(Map::BLOCK_SIZE, Map::BLOCK_SIZE));
	RectangleShape reminderRect(Vector2f(REMINDER_RECT_WIDTH, REMINDER_RECT_HEIGHT));

	//загрузка данных
	gameManager.LoadState((Mover&)player);

	musMaster.InitializeMusic();

	//карта
	Sprite tile;
	Texture fonTileSet;
	CreateUIElement(fonTileSet, "pictures//blocks.png", tile,
		MAP_WIDTH, MAP_HEIGHT, Map::BLOCK_SIZE, Map::BLOCK_SIZE);

	Sprite fon;
	Texture backTexture;
	CreateUIElement(backTexture, "pictures//fon.png", fon, 0, 0, FON_WIDTH, FON_HEIGHT);

	Font font;
	font.loadFromFile("CyrilicOld.ttf");

	//создание текста		
	Text text("", font, 20);
	ModifyText(text, Color::Red, Text::Bold | Text::Underlined);

	Text text1("", font, 80);
	ModifyText(text1, Color::Black, Text::Bold | Text::Underlined);

	//создание окна игры
	RenderWindow gameWindow(VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT),
		GAME_NAME, Style::Close | Style::Titlebar);

	gameWindow.setVerticalSyncEnabled(true);
	// не рекомендуется, т.к. работает на основе sleep
	// и на разных мониторах может быть не совсем корректно
	//gameWindow.setFramerateLimit(60);

	LoadCustomIcon(gameWindow);

	//обработка  самой игры
	Update(gameWindow, gameManager, clock, player, musMaster, map, 
		fon, tile, text, text1, persTileSet, playerRect, reminderRect);
}
	

void UIMaster::DrawReminderText(RenderWindow& gameWindow, Text& text)
{
	DrawNeededText(text, "F1-reminder", gameWindow, F1_REMINDER_X, F1_REMINDER_Y);
}

void UIMaster::DrawReminder(RectangleShape& reminderRect, Text& text, RenderWindow& gameWindow)
{
	DrawRect(reminderRect, gameWindow, Color::Green,
		REMINDER_X, REMINDER_Y);

	DrawNeededText(text,
		"esc-pause\nctrl-attack\nr-character respawn\nshift - sprint",
		gameWindow, REMINDER_TEXT_X, REMINDER_Y);
}

void UIMaster::ModifyText(Text& myText, const Color& color, Uint32 style)
{
	myText.setFillColor(color);
	myText.setStyle(style);
}

//выводит текст на экран
void UIMaster::DrawNeededText(Text& myText, const String& str, RenderWindow& gameWindow, const float x, const float y)
{
	myText.setString(str);
	myText.setPosition(x, y);
	gameWindow.draw(myText);
}
//рисует нужную фигуру
void UIMaster::DrawRect(sf::RectangleShape& rect, RenderWindow& gameWindow, const sf::Color& color, const float x, const float y)
{
	rect.setFillColor(color);
	rect.setPosition(x, y);
	gameWindow.draw(rect);
}

//показывает окошко во время игры
void UIMaster::ShowGameStatistics(Text& myText, RenderWindow& gameWindow, GameManager& gameManager, Mover& player)
{
	std::ostringstream playerScoreString;
	std::ostringstream playerSpeedString;
	std::ostringstream playerJumpString;
	std::ostringstream playerHPString;

	playerScoreString << gameManager.GetScore();
	DrawNeededText(myText, "Score:" + playerScoreString.str(), gameWindow, 0, 0);

	playerSpeedString << gameManager.GetSpeedScore();
	DrawNeededText(myText, "Speed:" + playerSpeedString.str(), gameWindow, 0, 30);

	playerJumpString << gameManager.GetJumpScore();
	DrawNeededText(myText, "Jump:" + playerJumpString.str(), gameWindow, 0, 60);

	playerHPString << (int)gameManager.GetPlayerHP();
	DrawNeededText(myText, "HP:" + playerHPString.str(), gameWindow, 0, 90);

	/*
	if (player.CanMultiJump())
		DrawNeededText(myText, "multyJump: true", gameWindow, 0, 120);
	else
		DrawNeededText(myText, "multyJump: false", gameWindow, 0, 120);
		*/
}

void UIMaster::CreateUIElement(Texture& tex, const string path, Sprite& spr, const int left , const int top, const int width, const int height)
{
	tex.loadFromFile(path);
	spr.setTexture(tex);
	spr.setTextureRect(IntRect(left, top, width, height));
}

//показывает меню при смерти или паузе
void UIMaster::ShowDeadOrPauseMenu(RenderWindow& gameWindow, Text& text, const bool isPaused)
{//если не умер, то нажал паузу )
	text.setPosition(280, 140);

	if(isPaused)
		text.setString("Game Over");
	else {
		text.setString("Pause");
		text.setPosition(340, 140);
	}

	text.setCharacterSize(80);
	gameWindow.draw(text);
		
	text.setCharacterSize(30);
	DrawNeededText(text, "click space to continue", gameWindow, 320, 230);
}
	
//перерисовка облаков
void UIMaster::RedrawFon(Sprite& fon, RenderWindow& gameWindow, const Map& map, const Player& player)
{
	fon.setPosition(FON_WIDTH * (map.count - 1) - player.offsetX, FON_HEIGHT * (map.countY - 1) - player.offsetY);
	gameWindow.draw(fon);
		
	fon.setPosition(FON_WIDTH * map.count - player.offsetX, FON_HEIGHT * map.countY - player.offsetY);
	gameWindow.draw(fon);

	fon.setPosition(FON_WIDTH * map.count - player.offsetX, FON_HEIGHT * (map.countY - 1) - player.offsetY);
	gameWindow.draw(fon);
	
	fon.setPosition(FON_WIDTH * (map.count - 1) - player.offsetX, FON_HEIGHT * map.countY - player.offsetY);
	gameWindow.draw(fon);
}
