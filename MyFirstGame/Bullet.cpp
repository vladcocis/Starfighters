#include "Bullet.h"

Bullet::Bullet() : GameObject(ObjectType::BULLET)
{
	isActive = true;
	transparency = 0;
	size = 0.9f;
	angle = 0;
	image = -1;
	lifetime = 0;
}

void Bullet::Initialise(Vector2D startPosition, Vector2D startVelocity)
{
	LoadImage(L"Assets/plasma.bmp");
	velocity = startVelocity;
	position = startPosition;
	lifetime = 1.5f;
}

void Bullet::Update(float frameTime)
{
	position = position + velocity * frameTime;
	lifetime = lifetime - frameTime;
	if (lifetime < 1.0f)
	{
		transparency = 1 - lifetime;
		if (transparency > 1.0f)
			transparency = 1.0f;
	}
	if (lifetime <= 0)
		Deactivate();
}

IShape2D& Bullet::GetShape()
{
	hitbox.PlaceAt(position, GetImageSize() * 18.0f);
	return hitbox;
}

void Bullet::ProcessColision(GameObject& other)
{
	if ((other.TYPE == ObjectType::ENEMY_ASTEROID) || (other.TYPE == ObjectType::ENEMY_SHIP) || (other.TYPE == ObjectType::ENEMY_BOSS))
	{
		Deactivate();
	}
}

void Bullet::DrawHitbox()
{
	MyDrawEngine::GetInstance()->FillCircle(hitbox.GetCentre(), hitbox.GetRadius(), MyDrawEngine::LIGHTGREEN);
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}
void Bullet::ProcessMessage(Message msg)
{
	//has no message functionality
}