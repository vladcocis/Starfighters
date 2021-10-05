#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "SoundFX.h"

class GameManager: public GameObject
{
private:
	int levelNumber;
	int score;
	float respawnTimer;
	float endLevelTimer;
	int enemyCounter;
	int lives;
	bool playerActive;
	ObjectManager objectManager;
	SoundFX* pSoundFX;
	Point2D hitbox;
	
public:
	GameManager();
	void StartLevel();
	void NextLevel();
	void Render();
	int GetLevelNumber();
	void Update(float frameTime);
	void AddScore(int s);
	void PlayerDead();
	IShape2D& GetShape();
	void ProcessColision(GameObject& other);
	void ProcessMessage(Message msg);
	void DrawHitbox();
	void EndOfGame();
	int GetLives();
	ObjectManager& GetObjectManager();
};

