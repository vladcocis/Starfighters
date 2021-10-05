#pragma once
#include "GameObject.h"

class Particles: public GameObject
{
	static const int NUMPARTICLES = 200;
private:
	Vector2D positions[NUMPARTICLES];
	Vector2D velocities[NUMPARTICLES];
	unsigned int colours[NUMPARTICLES];
	int nextParticle;
	Point2D hitbox;
public:
	Particles();
	void Initialise();
	void Update(float frameTime);
	void Render() override;
	IShape2D& GetShape();
	void ProcessColision(GameObject& other);
	void DrawHitbox();
	void AddParticle(Vector2D posiion, Vector2D velocity, unsigned int colour);
	void AddParticles(Vector2D position, float maxVelocity, unsigned int colour, int numParticles);
	void ProcessMessage(Message msg);
};


