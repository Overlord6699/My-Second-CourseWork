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

sf::Sound& MusicMaster::RunSound()
{
	return runsound;
}

sf::Sound& MusicMaster::JumpSound()
{
	return jumpsound;
}

sf::Sound& MusicMaster::PunchSound()
{
	return punchsound;
}

sf::Sound& MusicMaster::BrokenSound()
{
	return brokensound;
}

sf::Sound& MusicMaster::DeathSound()
{
	return deathsound;
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

void MusicMaster::InitializeMusic() {
	SetLoopedFonMusic();
	LoadMainSounds();
	CreateMainSounds();
}
