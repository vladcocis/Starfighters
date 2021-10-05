#include "GameObject.h"
#include "myinputs.h"

//constructor
GameObject::GameObject(ObjectType type) : TYPE(type)
{
	isActive = true;
	size = 1.0;
	angle = 0;
	transparency = 0;
	image = -1;
	recieveMessages = false;
}

// return the position of the object
Vector2D GameObject::GetPosition() const
{
	return position;
}

//destructor
GameObject::~GameObject()
{
	isActive = false;
}

//deactivate a game object
void GameObject::Deactivate()
{
	isActive = false;
}

float GameObject::GetImageSize() const
{
	return size;
}

// load image
void GameObject::LoadImage(const wchar_t* filename)
{
	image = MyDrawEngine::GetInstance()->LoadPicture(filename);
}

// render
void GameObject::Render()
{
	if(isActive)
		MyDrawEngine::GetInstance()->DrawAt(position, image, size, angle, transparency);
}

