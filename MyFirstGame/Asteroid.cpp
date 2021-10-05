#include "Asteroid.h"
#include "gamecode.h"
const float TURN_SPEED = 0.02f;

Asteroid::Asteroid() : GameObject(ObjectType::ENEMY_ASTEROID)
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
}

void Asteroid::Initialise(Vector2D startPosition, Vector2D startVelocity, float startSize, ObjectManager* pOM, SoundFX* pSFX, Particles* pPart, GameManager* pGM)
{
	LoadImage(L"Assets/rock1.bmp");
	pObjectManager = pOM;
	pSoundFX = pSFX;
	pParticleSystem = pPart;
	position = startPosition;
	velocity = startVelocity;
	size = startSize;
	pGameManager = pGM;
}

void Asteroid::Update(float frameTime)
{
	Rectangle2D screen = MyDrawEngine::GetInstance()->GetViewport();

	if (position.YValue > screen.GetTopLeft().YValue-50 && velocity.YValue > 0)
	{
		velocity.YValue = -velocity.YValue;
		velocity = velocity * 0.7;
	}

	if (position.YValue < screen.GetBottomRight().YValue+50 && velocity.YValue < 0)
	{
		velocity.YValue = -velocity.YValue;
		velocity = velocity * 0.7;
	}

	if (position.XValue > screen.GetBottomRight().XValue-50 && velocity.XValue > 0)
	{
		velocity.XValue = -velocity.XValue;
		velocity = velocity * 0.7;
	}

	if (position.XValue < screen.GetTopLeft().XValue+50 && velocity.XValue < 0)
	{
		velocity.XValue = -velocity.XValue;
		velocity = velocity * 0.7;
	}

	position = position + velocity*frameTime;
	angle += TURN_SPEED* frameTime;
}

IShape2D& Asteroid::GetShape()
{
	hitbox.PlaceAt(position, GetImageSize()*64.0f);
	return hitbox;
}

void Asteroid::ProcessColision(GameObject& other)
{
	if (other.TYPE == ObjectType::BULLET)
	{
		Deactivate();
		pGameManager->AddScore(5);
		pSoundFX->PlayAsteroidExplosion();
		int children = rand() % 3+1;
		if (size > 0.8f)
		{
			for (int i = 0; i < children; i++)
			{
				Asteroid* pAst = new Asteroid();
				Vector2D pos = position + Vector2D(float(rand() % 150 - 75), float((rand() % 150 - 75)));
				Vector2D vel(float(rand() % 200 - 100), float(rand() % 200 - 100));
				pAst->Initialise(pos, vel + velocity, size / 2.0f, pObjectManager, pSoundFX, pParticleSystem, pGameManager);
				if (pObjectManager)
				{
					pObjectManager->Add(pAst);
				}
			}
		}
		if (pParticleSystem)
		{
			pParticleSystem->AddParticles(position, 400, MyDrawEngine::WHITE, 10);
			pParticleSystem->AddParticles(position, 400, MyDrawEngine::YELLOW, 10);
			pParticleSystem->AddParticles(position, 400, MyDrawEngine::RED, 10);

		}
		Game::instance.StopHit();
	}

	if (other.TYPE == ObjectType::ENEMY_ASTEROID)
	{
		Vector2D normal = (position - other.GetPosition()).unitVector();
		if (normal * velocity < 0)
		{
			velocity = velocity - 2 * (velocity * normal) * normal;
			velocity = 0.7f * velocity;
		}
	}
}

void Asteroid::DrawHitbox()
{
	MyDrawEngine::GetInstance()->FillCircle(hitbox.GetCentre(), hitbox.GetRadius(), MyDrawEngine::LIGHTGREEN);
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

void Asteroid::ProcessMessage(Message msg)
{
	// has no message functionality
}