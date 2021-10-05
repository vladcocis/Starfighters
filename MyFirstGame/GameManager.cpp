#include "GameManager.h"
#include "Spaceship.h"
#include "Particles.h"
#include "Asteroid.h"
#include "Boss.h"
#include "Background.h"
#include "EnemySpaceship.h"
#include "mydrawengine.h"
#include "gamecode.h"

const int NUM_SPACE_INVADERS = 10;
const int NUM_ROWS = 3;
const int NUM_ASTEROIDS = 5;

GameManager::GameManager() : GameObject(ObjectType::LEVELMANAGER)
{
	levelNumber = 0;
	score = 0;
	respawnTimer = 3.0f;
	endLevelTimer = 5.0f;
	lives = 3;
	pSoundFX = 0;
	enemyCounter = 0;
	playerActive = false;
}
void GameManager::StartLevel()
{
	Background* pBackground = new Background();
	pBackground->Initialise(Vector2D(0,0));
	objectManager.Add(pBackground);

	LoadImage(L"Assets/ship.bmp");

	levelNumber = 1;
	score = 0;
	lives = 3;

	Particles* pParticles = new Particles();
	pParticles->Initialise();
	objectManager.Add(pParticles);

	pSoundFX = new SoundFX();
	pSoundFX->LoadSounds();

	Spaceship* pShip = new Spaceship();
	pShip->Initialise(Vector2D(0, -700), &objectManager, pSoundFX, &*this);
	objectManager.Add(pShip);
	playerActive = true;

	

	for (int rows = 0; rows < NUM_ROWS; rows++)
	{
		for (int i = 0; i < NUM_SPACE_INVADERS; i++)
		{
			EnemySpaceship* pEnemy = new EnemySpaceship();
			Vector2D pos(float(-1300 + (300 * i)), float(850 - 250 * rows));
			Vector2D vel;
			vel.setBearing(1.57f, 100.0f);
			pEnemy->Initialise(pos, vel, 2.0f, &objectManager, pSoundFX, pParticles, &*this);
			objectManager.Add(pEnemy);
		}
	}
}

void GameManager::NextLevel()
{
	levelNumber++;
	if (levelNumber == 2)
	{
		Particles* pParticles = new Particles();
		pParticles->Initialise();
		objectManager.Add(pParticles);

		for (int i = 0; i < NUM_ASTEROIDS; i++)
		{
			Asteroid* pAsteroid = new Asteroid();
			Vector2D pos;
			pos.setBearing(rand() % 600 / 100.0f, float(rand() % 600 + 800));
			Vector2D vel;
			vel.setBearing(rand() % 628 / 100.0f, float(rand() % 1000));
			pAsteroid->Initialise(pos, vel, 2.0f, &objectManager, pSoundFX, pParticles, &*this);
			objectManager.Add(pAsteroid);
		}
	}
	if (levelNumber == 3)
	{
		Particles* pParticles = new Particles();
		pParticles->Initialise();
		objectManager.Add(pParticles);

		Boss* pBoss = new Boss();
		Vector2D pos;
		pos.setBearing(0, 400.0f);
		Vector2D vel;
		vel.setBearing(rand() % 628 / 100.0f, 750.0f);
		pBoss->Initialise(pos, vel, 2.0f, &objectManager, pSoundFX, pParticles, &*this);
		objectManager.Add(pBoss);
	}

	if (levelNumber == 4)
	{
		EndOfGame();
	}
}


void GameManager::Render()
{
	MyDrawEngine* pDraw = MyDrawEngine::GetInstance();
	pDraw->WriteText(Vector2D(-1750.0f, -880.0f), L"Level: ", MyDrawEngine::LIGHTRED);
	pDraw->WriteInt(Vector2D(-1650.0f, -880.0f), levelNumber, MyDrawEngine::LIGHTRED);

	pDraw->WriteText(Vector2D(-1750.0f, -820.0f), L"Score: ", MyDrawEngine::LIGHTRED);
	pDraw->WriteInt(Vector2D(-1645.0f, -820.0f), score, MyDrawEngine::LIGHTRED);

	pDraw->WriteText(Vector2D(1400.0f, -880.0f), L"Lives: ", MyDrawEngine::LIGHTRED);
	for (int i = 0; i < lives; i++)
	{
		pDraw->DrawAt(Vector2D(float(1550 + 80 * i), -900.0f), image);
	}

}

void GameManager::Update(float frameTime)
{
	objectManager.UpdateAll(frameTime);
	objectManager.RenderAll();
	objectManager.CheckCollisions();
	objectManager.DeleteInactiveObjects();
	enemyCounter = objectManager.GetNumberOfEnemies();
	MyDrawEngine* pDraw = MyDrawEngine::GetInstance();

	if (!playerActive)
	{
		if (lives)
		{
			pDraw->WriteText(890, 400, L"Respawn in: ", MyDrawEngine::LIGHTRED);
			pDraw->WriteInt(1000, 400, int(respawnTimer) + 1, MyDrawEngine::LIGHTRED);
			respawnTimer -= frameTime;
			if (respawnTimer <= 0) {
				Spaceship* pShip = new Spaceship();
				pShip->Initialise(Vector2D(0, -700), &objectManager, pSoundFX, &*this);
				objectManager.Add(pShip);
				playerActive = true;
			}
		}
		else
		{
			EndOfGame();
		}
	}

	

	if (enemyCounter <= 0)
	{
		endLevelTimer -= frameTime;

		if (levelNumber == 1)
		{
			pDraw->WriteText(670, 500, L"Advanced movement capabilities unlocked, dodge those asteroids ", MyDrawEngine::LIGHTRED);
		}

		if (levelNumber == 2)
		{
			pDraw->WriteText(850, 500, L"Get ready for boss fight ", MyDrawEngine::LIGHTRED);
		}

		if (levelNumber == 3)
		{
			pDraw->WriteText(850, 500, L"Congratulations, you win ", MyDrawEngine::LIGHTRED);
		}

		if (endLevelTimer <= 0)
		{
			NextLevel();
			endLevelTimer = 5.0f;
		}
	}
}

void GameManager::AddScore(int s)
{
	score += s;
}


void GameManager::PlayerDead()
{
	lives--;
	playerActive = false;
	respawnTimer = 3.0f;
}

IShape2D& GameManager::GetShape()
{
	return hitbox;
}

void GameManager::ProcessColision(GameObject& other)
{
	// Does not collide
}

void GameManager::ProcessMessage(Message msg)
{
	// does not have message functionality
}

void GameManager::DrawHitbox()
{
	// does not have hitbox
}

void GameManager::EndOfGame()
{
	objectManager.DeleteAll();

	delete pSoundFX;
	pSoundFX = nullptr;

	Game::instance.PlayerDead(score);
}

int GameManager::GetLives()
{
	return lives;
}

int GameManager::GetLevelNumber()
{
	return levelNumber;
}

ObjectManager& GameManager::GetObjectManager()
{
	return objectManager;
}