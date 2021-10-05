#include "Boss.h"
#include "gamecode.h"
#include "Laser.h"
#include "Chicken.h"
#include "Explosion.h"

const float TURN_SPEED = 0.02f;

Boss::Boss() : GameObject(ObjectType::ENEMY_BOSS)
{
	isActive = true;
	health = 100;
	transparency = 0.1f;
	size = 1.0f;
	angle = 0;
	image = -1;
	pObjectManager = 0;
	pSoundFX = 0;
	pParticleSystem = 0;
	pGameManager = 0;
	shootTimer = 2.0f;
	recieveMessages = true;
	downTimer = 1.8f;
}

void Boss::Initialise(Vector2D startPosition, Vector2D startVelocity, float startSize, ObjectManager* pOM, SoundFX* pSFX, Particles* pPart, GameManager* pGM)
{
	LoadImage(L"Assets/boss1.bmp");
	pObjectManager = pOM;
	pSoundFX = pSFX;
	pParticleSystem = pPart;
	position = startPosition;
	velocity = startVelocity;
	size = startSize;
	pGameManager = pGM;
	health = 100;
}

void Boss::Update(float frameTime)
{
	Rectangle2D screen = MyDrawEngine::GetInstance()->GetViewport();

	if (position.YValue > screen.GetTopLeft().YValue && velocity.YValue > 0)
		velocity.YValue = -velocity.YValue;

	if (position.YValue < screen.GetBottomRight().YValue && velocity.YValue < 0)
		velocity.YValue = -velocity.YValue;
	

	if (position.XValue > screen.GetBottomRight().XValue && velocity.XValue > 0)
		velocity.XValue = -velocity.XValue;

	if (position.XValue < screen.GetTopLeft().XValue && velocity.XValue < 0)
		velocity.XValue = -velocity.XValue;

	shootTimer -= frameTime;
	position = position + velocity * frameTime;

	if (shootTimer <= 0)
	{
		pSoundFX->PlayBossShoot();

		for (int i = 0; i < 10; i++)
		{
			Laser* pLaser = new Laser();
			Vector2D vel;
			vel.setBearing(0.628f*(i+1), 500.0f);
			Vector2D pos;
			pos.setBearing(0.628f * (i + 1), 45.0f);
			pos = pos + position;

			pLaser->Initialise(pos, vel);

			if (pObjectManager)
				pObjectManager->Add(pLaser);
		}
		shootTimer = 1.8f;
	}
}

IShape2D& Boss::GetShape()
{
	hitbox.PlaceAt(Vector2D(position.XValue+105.0f, position.YValue+241.0f), Vector2D(position.XValue-105.0f, position.YValue-236.0f));
	return hitbox;
}

void Boss::ProcessColision(GameObject& other)
{
	if (other.TYPE == ObjectType::BULLET)
	{
		health -= 10;
		pSoundFX->PlayBossHit();

		if (health <= 0)
		{
			Deactivate();
			pGameManager->AddScore(5);
			Explosion* pExp = new Explosion();
			pExp->Initialise(position, 4.0f, 0.5f, Vector2D(0, 0));
			pObjectManager->Add(pExp);
			pSoundFX->PlayBossExplosion();

			if (pParticleSystem)
			{
				pParticleSystem->AddParticles(position, 400, MyDrawEngine::WHITE, 10);
				pParticleSystem->AddParticles(position, 400, MyDrawEngine::YELLOW, 10);
				pParticleSystem->AddParticles(position, 400, MyDrawEngine::RED, 10);

			}

			pGameManager->AddScore(995);
		}
		Game::instance.StopHit();

	}

}

void Boss::DrawHitbox()
{
	MyDrawEngine::GetInstance()->FillRect(hitbox, MyDrawEngine::LIGHTGREEN);
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

void Boss::ProcessMessage(Message msg)
{
	// has no message functionality
}

int Boss::GetHealth() 
{
	return health;
}

void Boss::Render()
{
	GameObject::Render();
	MyDrawEngine* pDraw = MyDrawEngine::GetInstance();
	pDraw->WriteText(Vector2D(-150.0f, +952.0f), L"Boss Health: ", MyDrawEngine::LIGHTRED);

	Rectangle2D bar;
	bar.PlaceAt(920.0f, 80.0f, 940.0f, float(health/10*50));
	if(health>10)
		pDraw->FillRect(bar, MyDrawEngine::LIGHTBLUE);
	else
		pDraw->FillRect(bar, MyDrawEngine::LIGHTRED);
}