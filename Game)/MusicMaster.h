#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>

class MusicMaster {
private:
	sf::SoundBuffer runBuffer;
	sf::SoundBuffer jumpBuffer;
	sf::SoundBuffer punchBuffer;
	sf::SoundBuffer brokenBuffer;
	sf::SoundBuffer deathBuffer;

	sf::Sound runsound;
	sf::Sound jumpsound;
	sf::Sound punchsound;
	sf::Sound brokensound;
	sf::Sound deathsound;

	void LoadMainSounds();
	void CreateMainSounds();
	void SetLoopedFonMusic();

	sf::Music music;
public:
	
	//методы доступа
	sf::Sound& RunSound();
	sf::Sound& JumpSound();
	sf::Sound& PunchSound();
	sf::Sound& BrokenSound();
	sf::Sound& DeathSound();

	void PauseFonMusic();
	void PlayFonMusic();
	void PauseNeededSound(sf::Sound& mySound);
	void PlayNeededSound(sf::Sound& mySound);
	void InitializeMusic();
};