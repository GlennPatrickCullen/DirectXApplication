#include "gameobjectclass.h"

GameObject::GameObject()
{
	modelInfo = 0;
}

GameObject::GameObject(const GameObject&)
{

}

GameObject::~GameObject()
{

}

bool GameObject::Initialise(char* ModelPath, wchar_t* TexturePath, list<Vector3> Position)
{
	modelInfo = new ModelInfo;
	modelInfo->Initialise(ModelPath, TexturePath, Position);

	if(!modelInfo)
	{
		return false;
	}

	return true;
}

bool GameObject::Initialise(char* ModelPath, wchar_t* TexturePath, wchar_t* NormalMapPath, list<Vector3>  Position)
{
	modelInfo = new ModelInfo;
	modelInfo->Initialise(ModelPath, TexturePath, NormalMapPath, Position);

	if(!modelInfo)
	{
		return false;
	}

	return true;
}

bool GameObject::Initialise(char* ModelPath, wchar_t* TexturePath,  list<Vector3> Position , Vector3 Scale )
{
	modelInfo = new ModelInfo;
	modelInfo->Initialise(ModelPath, TexturePath, Position,Scale);

	if(!modelInfo)
	{
		return false;
	}

	return true;
}

bool GameObject::Initialise(char* ModelPath, wchar_t* TexturePath, wchar_t* NormalMapPath, list<Vector3> Position, Vector3 Scale)
{
	modelInfo = new ModelInfo;
	modelInfo->Initialise(ModelPath, TexturePath, NormalMapPath, Position,Scale);

	if(!modelInfo)
	{
		return false;
	}

	return true;
}

void GameObject::Shutdown()
{
	modelInfo->Shutdown();
	delete modelInfo;
	modelInfo = 0; 
}