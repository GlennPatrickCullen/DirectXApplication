////////////////////////////////////////////////////////////////////////////////
// Filename: scenegraphobjectclass
////////////////////////////////////////////////////////////////////////////////
#ifndef _SCENEGRAPHOBJECTCLASS_H_
#define _SCENEGRAPHOBJECTCLASS_H_

#include "modelclass.h"
#include "gameobjectclass.h"
#include "d3dclass.h"
#include <d3d11.h>

using namespace std;

//An Object to be saved in the renderlist.
//Contains all graphic specific funtions and is instantiated from a GameObject (which is graphic system agnostic)
//Currently implements a DirectX rendering implementation.

class SceneGraphObject
{
public:
	SceneGraphObject();
	//SceneGraphObject(const SceneGraphObject&);
	~SceneGraphObject();

	bool Initialise(GameObject* Object, D3DClass* D3D, HWND hwnd);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);
	ModelClass* model;
	GameObject* objectRef;
private:
	
	
};

#endif