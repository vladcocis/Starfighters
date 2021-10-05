#include "EnemySpaceship.h"
#include "gamecode.h"
#include "Laser.h"
#include "Explosion.h"
#include "Chicken.h"

const float TURN_SPEED = 0.02f;

EnemySpaceship::EnemySpaceship() : GameObject(ObjectType::ENEMY_SHIP)
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
	shootTimer = 3.0f;
	recieveMessages = true;
	downTimer = 2.0f;
}

void EnemySpaceship::Initialise(Vector2D startPosition, Vector2D startVelocity, float startSize, ObjectManager* pOM, SoundFX* pSFX, Particles* pPart, GameManager* pGM)
{
	LoadImage(L"Assets/basic.bmp");
	pObjectManager = pOM;
	pSoundFX = pSFX;
	pParticleSystem = pPart;
	position = startPosition;
	velocity = startVelocity;
	size = startSize;
	pGameManager = pGM;
}

void EnemySpaceship::Update(float frameTime)
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();

	Rectangle2D screen = MyDrawEngine::GetInstance()->GetViewport();

	if ((position.XValue > screen.GetBottomRight().XValue && velocity.XValue > 0) || (position.XValue < screen.GetTopLeft().XValue && velocity.XValue < 0))
	{
		Message msg;
		msg.type = MessageType::TURN;
		msg.location = position;
		msg.pSource = this;
		pObjectManager->HandleMessage(msg);
	}

	shootTimer -= frameTime;
	downTimer -= frameTime;

	if (shootTimer <= 0)
	{
		pSoundFX->PlayEnemyShoot();

		Laser* pLaser = new Laser();
		Vector2D vel;
		vel.setBearing(3.14f, 500.0f);
		Vector2D pos;
		pos.setBearing(3.14f, 45.0f);
		pos = pos + position;

		pLaser->Initialise(pos, vel);

		if (pObjectManager)
			pObjectManager->Add(pLaser);

		shootTimer = 3.0f;
	}

	if (downTimer <= 0) {
		position = position + Vector2D(0, -2000.0f) * frameTime;
		downTimer = 2.0f;
	}

	position = position + velocity * frameTime;
	
}

IShape2D& EnemySpaceship::GetShape()
{
	hitbox.PlaceAt(position, GetImageSize() * 64.0f);
	return hitbox;
}

void EnemySpaceship::ProcessColision(GameObject& other)
{
	if (other.TYPE == ObjectType::BULLET)
	{
		Deactivate();
		pGameManager->AddScore(5);

		Explosion* pExp = new Explosion();
		pExp->Initialise(position, 4.0f, 0.5f, Vector2D(0, 0));
		pObjectManager->Add(pExp);
		pSoundFX->PlayShipExplosion();

		if (pParticleSystem)
		{
			pParticleSystem->AddParticles(position, 400, MyDrawEngine::WHITE, 10);
			pParticleSystem->AddParticles(position, 400, MyDrawEngine::YELLOW, 10);
			pParticleSystem->AddParticles(position, 400, MyDrawEngine::RED, 10);

		}
		Game::instance.StopHit();

		Chicken* pChicken = new Chicken();
		Vector2D vel;
		vel.setBearing(3.14f, 600.0f);
		Vector2D pos;
		pos.setBearing(3.14f, 45.0f);
		pos = pos + position;

		pChicken->Initialise(pos, vel);

		if (pObjectManager)
			pObjectManager->Add(pChicken);
	}

}

void EnemySpaceship::DrawHitbox()
{
	MyDrawEngine::GetInstance()->FillCircle(hitbox.GetCentre(), hitbox.GetRadius(), MyDrawEngine::LIGHTGREEN);
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

void EnemySpaceship::ProcessMessage(Message msg)
{
	if (msg.type == MessageType::TURN)
	{
		velocity.XValue = -velocity.XValue;
	}
}