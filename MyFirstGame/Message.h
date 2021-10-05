#pragma once
#include "messagetypes.h"
#include "vector2D.h"
class GameObject;

struct Message
{
public:
	MessageType type;

	Vector2D location;

	GameObject* pSource;

	float other;

};

