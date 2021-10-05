#pragma once
#include "mydrawengine.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "SoundFX.h"
#include "GameManager.h"

class Spaceship: public GameObject
{
private:
	Vector2D velocity; 
	ObjectManager* pObjectManager;
	GameManager* pGameManager;
	SoundFX* pSoundFX;
	int health;
	int ammo;
	float shootTimer;
	float invulnerableTimer;
	Circle2D hitbox;
public:
	Spaceship();
	void Initialise(Vector2D startPosition, ObjectManager* pOM, SoundFX* pSFX, GameManager* pGameManager);
	void Update(float frameTime);
	IShape2D& GetShape();
	void ProcessColision(GameObject& other);
	void DrawHitbox();
	void ProcessMessage(Message msg);
};

