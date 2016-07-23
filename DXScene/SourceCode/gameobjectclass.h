////////////////////////////////////////////////////////////////////////////////
// Filename: gameobjectclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GAMEOBJECTCLASS_H_
#define _GAMEOBJECTCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>

#include "modelinfo.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: GameObject
// The gameobject class allows for gameplay features to be decoupled from 
// graphical rendering, allowing easy portability between graphics engines.
// It also allows for the same object to be rendered in multiple locations by
// passing in a list of positions where the object would be rendered.
////////////////////////////////////////////////////////////////////////////////
class GameObject
{
public:
	GameObject();
	GameObject(const GameObject&);
	~GameObject();

	virtual bool Initialise(char* ModelPath, wchar_t* TexturePath,  list<Vector3> );
	virtual bool Initialise(char* ModelPath, wchar_t* TexturePath, wchar_t* NormalMapPath,  list<Vector3> );

	virtual bool Initialise(char* ModelPath, wchar_t* TexturePath, list<Vector3> , Vector3 Scale);
	virtual bool Initialise(char* ModelPath, wchar_t* TexturePath, wchar_t* NormalMapPath, list<Vector3>, Vector3 Scale);
	virtual void Shutdown();
	ModelInfo* modelInfo;

private:

};

#endif
