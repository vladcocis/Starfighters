#include "Laser.h"

Laser::Laser() : GameObject(ObjectType::LASER)
{
	isActive = true;
	transparency = 0;
	size = 0.9f;
	angle = 0;
	image = -1;
	lifetime = 0;
}

void Laser::Initialise(Vector2D startPosition, Vector2D startVelocity)
{
	LoadImage(L"Assets/plasma.bmp");
	velocity = startVelocity;
	position = startPosition;
	lifetime = 5.0f;
}

void Laser::Update(float frameTime)
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

IShape2D& Laser::GetShape()
{
	hitbox.PlaceAt(position, GetImageSize() * 18.0f);
	return hitbox;
}

void Laser::ProcessColision(GameObject& other)
{
	if (other.TYPE == ObjectType::SHIP)
	{
		Deactivate();
	}
}

void Laser::DrawHitbox()
{
	MyDrawEngine::GetInstance()->FillCircle(hitbox.GetCentre(), hitbox.GetRadius(), MyDrawEngine::LIGHTGREEN);
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

void Laser::ProcessMessage(Message msg)
{
	//has no message functionality
}