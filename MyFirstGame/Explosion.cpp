#include "Explosion.h"

Explosion::Explosion() : GameObject(ObjectType::EXPLOSION)
{
	isActive = true;
	transparency = 0.1f;
	size = 1.0f;
	angle = 0;
	image = -1;
	animationSpeed = 0;
	currentImage = 0;
	images[1] = 0;
}

void Explosion::Initialise(Vector2D startPosition, float startSize, float startTime, Vector2D vel)
{
	position = startPosition;
	animationSpeed = 8 / startTime;
	size = startSize;
	velocity = vel;
	angle = (rand() % 628 / 100.0f);
	images[0] = MyDrawEngine::GetInstance()->LoadPicture(L"Assets/explosion1.bmp");
	images[1] = MyDrawEngine::GetInstance()->LoadPicture(L"Assets/explosion2.bmp");
	images[2] = MyDrawEngine::GetInstance()->LoadPicture(L"Assets/explosion3.bmp");
	images[3] = MyDrawEngine::GetInstance()->LoadPicture(L"Assets/explosion4.bmp");
	images[4] = MyDrawEngine::GetInstance()->LoadPicture(L"Assets/explosion5.bmp");
	images[5] = MyDrawEngine::GetInstance()->LoadPicture(L"Assets/explosion6.bmp");
	images[6] = MyDrawEngine::GetInstance()->LoadPicture(L"Assets/explosion7.bmp");
	images[7] = MyDrawEngine::GetInstance()->LoadPicture(L"Assets/explosion8.bmp");

	currentImage = 0;

	isActive = true;
}

void Explosion::Update(float frameTime)
{
	currentImage += frameTime * animationSpeed;
	if (currentImage > 8.0)
	{
		Deactivate();
	}
	position = position + velocity * frameTime;
}

void Explosion::Render()
{
	if (isActive)
		MyDrawEngine::GetInstance()->DrawAt(position, images[int(currentImage)], size, angle, transparency);

}

IShape2D& Explosion::GetShape()
{
	hitbox.PlaceAt(position, GetImageSize() * 64.0f);
	return hitbox;
}

void Explosion::ProcessColision(GameObject& other)
{
	// does not collide
}

void Explosion::DrawHitbox()
{
	//does not collide
}

void Explosion::ProcessMessage(Message msg)
{
	//has no message functionality
}