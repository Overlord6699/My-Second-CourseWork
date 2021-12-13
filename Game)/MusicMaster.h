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

	void LoadMainSounds();
	void CreateMainSounds();
	void SetLoopedFonMusic();
public:
	sf::Music music;

	//нужно предоставить к ним доступ для выбора
	sf::Sound runsound;
	sf::Sound jumpsound;
	sf::Sound punchsound;
	sf::Sound brokensound;
	sf::Sound deathsound;

	void PauseFonMusic();
	void PlayFonMusic();
	void PauseNeededSound(sf::Sound& mySound);
	void PlayNeededSound(sf::Sound& mySound);
	void InitializeMusic();
	
	//костыли
	void PauseRunSound();
	void PlayBrokenSound();
};