#include "Chicken.h"

Chicken::Chicken() : GameObject(ObjectType::CHICKEN)
{
	isActive = true;
	transparency = 0;
	size = 0.9f;
	angle = 0;
	image = -1;
	lifetime = 0;
}

void Chicken::Initialise(Vector2D startPosition, Vector2D startVelocity)
{
	LoadImage(L"Assets/chicken.bmp");
	velocity = startVelocity;
	position = startPosition;
	lifetime = 3.5f;
}

void Chicken::Update(float frameTime)
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

IShape2D& Chicken::GetShape()
{
	hitbox.PlaceAt(position, GetImageSize() * 40.0f);
	return hitbox;
}

void Chicken::ProcessColision(GameObject& other)
{
	if (other.TYPE == ObjectType::SHIP)
	{
		Deactivate();
	}
}

void Chicken::DrawHitbox()
{
	MyDrawEngine::GetInstance()->FillCircle(hitbox.GetCentre(), hitbox.GetRadius(), MyDrawEngine::LIGHTGREEN);
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}
void Chicken::ProcessMessage(Message msg)
{
	//has no message functionality
}