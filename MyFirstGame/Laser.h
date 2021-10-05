#pragma once
#include "GameObject.h"

class Laser : public GameObject
{
private:
	Vector2D velocity;
	float lifetime;
	Circle2D hitbox;
public:
	Laser();
	void Initialise(Vector2D startPosition, Vector2D startVelocity);
	void Update(float frameTime);
	IShape2D& GetShape();
	void ProcessColision(GameObject& other);
	void DrawHitbox();
	void ProcessMessage(Message msg);
};


