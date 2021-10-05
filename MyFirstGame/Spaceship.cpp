#include "Spaceship.h"
#include "myinputs.h"
#include "mydrawengine.h"
#include "Bullet.h"
#include "Explosion.h"

Spaceship::Spaceship() : GameObject(ObjectType::SHIP)
{
	isActive = true;
	health = 100;
	ammo = 100;
	transparency = 0.1f;
	size = 2.0f;
	angle = 0;
	image = -1;
	position.set(0, 0);
	velocity.set(0, 0);
	pObjectManager = 0;
	pSoundFX = 0;
	shootTimer = 0;
	pGameManager = 0;
	invulnerableTimer = 2.0f;
}

void Spaceship::Initialise(Vector2D startPosition, ObjectManager* pOM, SoundFX* pSFX, GameManager* pGM)
{
	pObjectManager = pOM;
	pSoundFX = pSFX;
	pGameManager = pGM;
	LoadImage(L"Assets/ship.bmp");
	position = startPosition;
}

void Spaceship::Update(float frameTime)
{
	MySoundEngine* pSE = MySoundEngine::GetInstance();
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();

	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

	const float TURN_SPEED = 5.0f * frameTime;
	const float FRICTION = 0.02f * frameTime;
	const float SPEED = 19000.0f;

	static bool wPressed = false;
	static bool sPressed = false;


	Rectangle2D screen = MyDrawEngine::GetInstance()->GetViewport();

	if (invulnerableTimer > 0)
		transparency = 0.5f;
	else
		transparency = 0.1f;

	if (position.YValue > screen.GetTopLeft().YValue)
		position.YValue = screen.GetBottomRight().YValue;

	if (position.YValue < screen.GetBottomRight().YValue)
		position.YValue = screen.GetTopLeft().YValue;

	if (position.XValue > screen.GetBottomRight().XValue)
		position.XValue = screen.GetTopLeft().XValue;

	if (position.XValue < screen.GetTopLeft().XValue)
		position.XValue = screen.GetBottomRight().XValue;



	velocity = velocity - velocity * velocity.magnitude() * FRICTION;
	position = position + velocity * frameTime;

	shootTimer -= frameTime;
	invulnerableTimer -= frameTime;

	if (pGameManager->GetLevelNumber() == 1)
	{
		if (pInputs->KeyPressed(DIK_A))
		{
			Vector2D acceleration;
			acceleration.setBearing(-1.57f, SPEED);
			velocity = velocity + acceleration * frameTime;
		}

		if (pInputs->KeyPressed(DIK_D))
		{
			Vector2D acceleration;
			acceleration.setBearing(1.57f, SPEED);
			velocity = velocity + acceleration * frameTime;
		}

		if (pInputs->KeyPressed(DIK_SPACE) && shootTimer <= 0)
		{
			pSoundFX->PlayShoot();

			Bullet* pBullet = new Bullet();
			Vector2D vel;
			vel.setBearing(0, 1500.0f);

			Vector2D pos;
			pos.setBearing(0, 45.0f);
			pos = pos + position;

			pBullet->Initialise(pos, vel);

			if (pObjectManager)
				pObjectManager->Add(pBullet);

			shootTimer = 1.0f;
		}
	}
	else
	{
		if (pInputs->KeyPressed(DIK_W))
		{
			if (wPressed == false)
				pSoundFX->StartThruster();
			Vector2D acceleration;
			acceleration.setBearing(angle, SPEED);
			velocity = velocity + acceleration * frameTime;
			wPressed = true;

			Explosion* pExpl = new Explosion();
			Vector2D jet;
			jet.setBearing(angle + 3.14f, 36.0f);
			jet = jet + position;

			Vector2D jetvel;
			jetvel.setBearing(angle + 3.14f, 500.0f);
			jetvel = jetvel + velocity;

			pExpl->Initialise(jet, 0.4f, 0.5f, jetvel);
			pObjectManager->Add(pExpl);
		}
		else
		{
			if (wPressed)
				pSoundFX->StopThruster();
			wPressed = false;
		}

		if (pInputs->KeyPressed(DIK_S))
		{
			if (sPressed == false)
				pSoundFX->StartThruster();
			Vector2D acceleration;
			acceleration.setBearing(angle, -SPEED);
			velocity = velocity + acceleration * frameTime;
			sPressed = true;
		}
		else
		{
			if (sPressed)
				pSoundFX->StopThruster();
			sPressed = false;
		}

		if (pInputs->KeyPressed(DIK_A))
		{
			angle -= TURN_SPEED;
		}

		if (pInputs->KeyPressed(DIK_D))
		{
			angle += TURN_SPEED;
		}



		if (pInputs->KeyPressed(DIK_SPACE) && shootTimer <= 0)
		{
			pSoundFX->PlayShoot();

			Bullet* pBullet = new Bullet();
			Vector2D vel;
			vel.setBearing(angle, 1500.0f);
			vel = vel + velocity;
			Vector2D pos;
			pos.setBearing(angle, 45.0f);
			pos = pos + position;

			pBullet->Initialise(pos, vel);

			if (pObjectManager)
				pObjectManager->Add(pBullet);

			shootTimer = 1.0f;
		}
	}
}

IShape2D& Spaceship::GetShape()
{
	hitbox.PlaceAt(position, GetImageSize() * 24.0f);
	return hitbox;
}

void Spaceship::ProcessColision(GameObject& other)
{
	if (invulnerableTimer<=0)
		if ((other.TYPE == ObjectType::ENEMY_ASTEROID) || (other.TYPE == ObjectType::LASER) || (other.TYPE == ObjectType::ENEMY_SHIP) || (other.TYPE == ObjectType::ENEMY_BOSS))
		{
			Deactivate();
			pSoundFX->StopThruster();
			Explosion* pExp = new Explosion();
			pExp->Initialise(position, 4.0f, 0.5f, Vector2D(0, 0));
			pObjectManager->Add(pExp);
			pSoundFX->PlayShipExplosion();

			pGameManager->PlayerDead();

		}

	if (other.TYPE == ObjectType::CHICKEN)
	{

		pSoundFX->PlayCrunch();
		pGameManager->AddScore(20);

	}
}

void Spaceship::DrawHitbox()
{
	MyDrawEngine::GetInstance()->FillCircle(hitbox.GetCentre(), hitbox.GetRadius(), MyDrawEngine::LIGHTGREEN);
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

void Spaceship::ProcessMessage(Message msg)
{
	//has no message functionality
}