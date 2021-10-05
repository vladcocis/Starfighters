#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"

class Explosion : public GameObject
{
private:
	Vector2D velocity;
	Circle2D hitbox;
	float animationSpeed;
	float currentImage;
	PictureIndex images[8];
public:
	Explosion();
	void Initialise(Vector2D startPosition, float startSize, float startTime, Vector2D vel = Vector2D(0,0));
	void Update(float frameTime);
	void Render() override;
	IShape2D& GetShape();
	void ProcessColision(GameObject& other);
	void DrawHitbox();
	void ProcessMessage(Message msg);
};

