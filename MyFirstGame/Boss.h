#pragma once
#include "mydrawengine.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "SoundFX.h"
#include "Particles.h"

class Boss : public GameObject
{
private:
	int health;
	Vector2D velocity;
	Rectangle2D hitbox;
	ObjectManager* pObjectManager;
	GameManager* pGameManager;
	SoundFX* pSoundFX;
	Particles* pParticleSystem;
	float shootTimer;
	float downTimer;

public:
	Boss();
	void Initialise(Vector2D startPosition, Vector2D startVelocity, float startSize, ObjectManager* pOM, SoundFX* pSFX, Particles* pPart, GameManager* pGameManager);
	void Update(float frameTime);
	IShape2D& GetShape();
	void ProcessColision(GameObject& other);
	void DrawHitbox();
	void ProcessMessage(Message msg);
	int GetHealth();
	void Render() override;
};