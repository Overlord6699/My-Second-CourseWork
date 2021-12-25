#pragma once
#include <string>
#include "Mover.h"
#include "MusicMaster.h"
using namespace std;

class Map {
	

public:
	static const int BLOCK_SIZE = 32;
	static const int MAX_BLOCK_HP = 3000;

	void RepeatMap(const int FON_WIDTH, const int FON_HEIGHT, Mover& player);
	void ReturnBonuses();

	//урон при атаке по блоку
	void DealDamageToBlock(const float time);
	//урон при пробегании по блоку
	void DealDamageToBlockByRun(const float time);

	void CheckBlockHealth(MusicMaster& musMaster, const int i, const int j);

	//1 - мгновенное хп блока, 2 - присваивается при переходе на новый блок
	int blockHP = 0, blockHP_Temp = 0;

	//для изменения фона (облака)
	int count = 1;
	int countY = 1;

	static const int H = 89;
	static const int W = 141;

	string TileMap[H] = {
"O                       /   /                                                                                  /   /                       O",//О-Невидимый физический блок
"O                       /   /                                                                                  /   /                       O",//B-обычный физический нерушимый блок
"O                       /   /                                                                                  /   /                       O",//J-бонус мультипрыжок
"O//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////O",//K-бонус увеличивает высоту прыжка
"O                       /   /                                                                                  /   /                       O",//L-Объект, при касании с которым вы проигрываете
"O                       /   /                                                                                  /   /                       O",//0-увеличивает счёт ваших очков
"O                       /   /                                                                                  /   /                       O",//S-бонус увеличивает скорость игры
"O                       /   /                                                                                  /   /                       O",//M-уменьшает скорость игры
"O                       /   /                                                                                  /   /                       O",//U-видимый разрушимый физический блок
"O                       /   /                                                                                  /   /                       O",//Y-точка сохранения
"O                       /   /                                                                                  /   /                       O",//P-уменьшает высоту вашего прыжка
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                          LLLLLLLLLLLLLL                          /   /                       O",
"O                       /   /            LLLLLLLLLLLL                                                          /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                          LLLLLLLLLLLLLLLLLLLLLLLL/   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"OLLLLLLLLLLLLLLLL       /   /                                                                                  /   /LLLLLLLLLLLLLLLL       O",
"O                       /   /                                                                 S  J  Y     M/ P /   /                       O",
"O                       /   /                                                            BBBBBBBBBBBBB   BBBBBB/   /                       O",
"O                       /   /        BBBBBBBBBBBBBBBB                                                          /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                     BB/   /                                                                                  /   /                     BBO",
"O                     BB/   /                                                                                  /   /                     BBO",
"O                     BB/   /                          E                                   K    Y    0         /   /                     BBO",
"OBBBBB         BBBBBBBBB/   /  BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB    BBBB   /BBBBB         BBBBBBBBBO",
"O             BB        /   /  BB                                                                              /   /             BB        O",
"O            BB         /   /  BB                                                                              /   /            BB         O",
"O           BB          /   /  BB                                                                              /   /           BB          O",
"O          BB           /   /  BB                                                                              /   /          BB           O",
"O                       /   /  BB                                                                              /   /                       O",
"O                       /   /  BB                                        E                                     /   /                       O",
"OBB                     /   /  BB              BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB       /   /BB                     O",
"O BB                    /   /  BB                                                                              /   / BB                    O",
"O  BB                   /   /  BB                                                                              /   /  BB                   O",
"O   BB                  /   /  BB                                                                              /   /   BB                  O",
"O    BB                 /   /  BB                                                                              /   /    BB                 O",
"O     BB                /   /  BB                                                                              /   /     BB                O",
"O      BB               /   /  BB                                                                              /   /      BB               O",
"O       BB              /   /  BB                                                                              /   /       BB              O",
"O        BB             /   /  BB                                                                              /   /        BB             O",
"O         BB            /   /  BB                                                                    UUUUUUU   /   /         BB            O",
"O          BB           /   /  UU                                                                    UU K UU   /   /          BB           O",
"O           BB          /   /  UU                        E                            E              UUUUUUU   /   /           BB          O",
"OBBBBBBBBBBBBBB    BBBBB/   / BBBBBBBBBBBBBBBBBBBBBBBBBUUUUUUBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB/   /BBBBBBBBBBBBBB    BBBBBO",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                    S 0      E      0 K                                           /   /                       O",
"O                       /   /                   BBBBBBBBBBBBBBBBBBBBBB                                         /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"OBBBBBBBBBBBBBBBBBBBBBBB/   /                                                            BBBBBBBBBBBBBBBBBBBBBB/   /BBBBBBBBBBBBBBBBBBBBBBBO",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O                       /   /                                                                                  /   /                       O",
"O//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////O" };
};