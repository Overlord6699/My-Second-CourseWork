#include "MusicMaster.h"

void MusicMaster::SetLoopedFonMusic()
{
	music.openFromFile("sounds//music.wav");
	music.play();
	music.setLoop(true);
}

void MusicMaster::LoadMainSounds()
{
	runBuffer.loadFromFile("sounds//run.wav");
	jumpBuffer.loadFromFile("sounds//jump.wav");
	punchBuffer.loadFromFile("sounds//punch.wav");
	brokenBuffer.loadFromFile("sounds//broken.wav");
	deathBuffer.loadFromFile("sounds//death.wav");
}

void MusicMaster::CreateMainSounds()
{	
	//создание нужных звуков
	runsound = sf::Sound(runBuffer);
	jumpsound = sf::Sound(jumpBuffer);
	punchsound = sf::Sound(punchBuffer);
	brokensound = sf::Sound(brokenBuffer);
	deathsound = sf::Sound(deathBuffer);
}


void MusicMaster::PlayFonMusic()
{
	music.play();
}

void MusicMaster::PauseFonMusic()
{
	music.pause();
}

//PlaySound было зарезервировано))
void MusicMaster::PlayNeededSound(sf::Sound& mySound)
{
	mySound.play();
}

void MusicMaster::PauseNeededSound(sf::Sound& mySound)
{
	mySound.pause();
}

void MusicMaster::PauseRunSound() {
	runsound.pause();
}

void MusicMaster::PlayBrokenSound() {
	brokensound.play();
}

void MusicMaster::InitializeMusic() {
	SetLoopedFonMusic();
	LoadMainSounds();
	CreateMainSounds();
}
