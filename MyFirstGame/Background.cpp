#include "Background.h"
Background::Background() : GameObject(ObjectType::BACKGROUND)
{
	isActive = true;
	transparency = 0;
	size = 0.5f;
	angle = 0;
	image = -1;
	velocity = Vector2D(0,0);
}

void Background::Initialise(Vector2D startPosition)
{
	LoadImage(L"Assets/background.jpg");
	position = startPosition;
}

void Background::Update(float frameTime)
{
	// does not update
}

IShape2D& Background::GetShape()
{
	hitbox.PlaceAt(position, GetImageSize() * 64.0f);
	return hitbox;
}

void Background::ProcessColision(GameObject& other)
{
	// does not collide
}

void Background::DrawHitbox()
{
	// has no hitbox
}
void Background::ProcessMessage(Message msg)
{
	//has no message functionality
}