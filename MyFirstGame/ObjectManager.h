#pragma once
#include <list>
#include "GameObject.h"
#include "Message.h"

class ObjectManager
{
private:
	std::list<GameObject*> pObjectList;
	int enemyCounter = 0;
public:
	~ObjectManager();
	void Add(GameObject* pObject);
	void RenderAll();
	void UpdateAll(float frameTime);
	void DeleteAll();
	void DeleteInactiveObjects();
	void CheckCollisions();
	int GetNumberOfEnemies();
	void HandleMessage(Message msg);
};

