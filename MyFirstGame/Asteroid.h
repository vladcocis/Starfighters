#pragma once
#include "mydrawengine.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "SoundFX.h"
#include "Particles.h"

class Asteroid : public GameObject
{
private:
	int health;
	Vector2D velocity;
	Circle2D hitbox;
	ObjectManager* pObjectManager;
	GameManager* pGameManager;
	SoundFX* pSoundFX;
	Particles* pParticleSystem;

public:
	Asteroid();
	void Initialise(Vector2D startPosition, Vector2D startVelocity, float startSize, ObjectManager* pOM, SoundFX* pSFX, Particles* pPart, GameManager* pGameManager);
	void Update(float frameTime);
	IShape2D& GetShape();
	void ProcessColision(GameObject& other);
	void DrawHitbox();
	void ProcessMessage(Message msg);
};
