#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "objecttypes.h"
#include "Message.h"

class GameObject
{	
protected:
	PictureIndex image;
	Vector2D position;
	float angle;
	float size;
	float transparency;
	bool isActive;
public:
	//type of object
	const ObjectType TYPE;

	bool recieveMessages;

	//constructor
	explicit GameObject(ObjectType type);

	//destructor
	virtual ~GameObject();

	// set isActive to false. Object will be deleted by engine
	void Deactivate();

	float GetImageSize() const;

	// check if object is active
	inline bool IsActive() const
	{
		return isActive;
	}

	// draw the object on screen for the first time
	virtual void Render();

	// draw the object using myDrawEngine
	void LoadImage(const wchar_t* filename);
	
	// get position of object
	Vector2D GetPosition() const;

	// process every frame
	virtual void Update(float frametime) = 0;

	virtual IShape2D& GetShape() = 0;

	virtual void ProcessColision(GameObject& other) = 0;

	virtual void DrawHitbox() = 0;

	virtual void ProcessMessage(Message msg) = 0;
};

