#pragma once
#include "GameObject.h"

class Background : public GameObject
{
private:
	Vector2D velocity;
	Circle2D hitbox;
public:
	Background();
	void Initialise(Vector2D startPosition);
	void Update(float frameTime);
	IShape2D& GetShape();
	void ProcessColision(GameObject& other);
	void DrawHitbox();
	void ProcessMessage(Message msg);
};
