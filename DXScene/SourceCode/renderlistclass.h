////////////////////////////////////////////////////////////////////////////////
// Filename: renderlistclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _RENDERLISTCLASS_H
#define _RENDERLISTCLASS_H


//////////////
// INCLUDES //
//////////////
#include "gameobjectclass.h"
#include "scenegraphobjectclass.h"
#include "d3dclass.h"


#include <vector>
using namespace std;
////////////////////////////////////////////////////////////////////////////////
// Class name: RenderList
////////////////////////////////////////////////////////////////////////////////

//Contains a list of scenegraph objects that must be rendered in the scene.
// Gameobjects can be added here to be rendered.
// An application can have multiple renderlists for different graphical passes
class RenderList
{
public:
	RenderList();
	//RenderList(const RenderList&);
	~RenderList();
	bool Initialise(D3DClass* D3D, HWND* hwnd);
	void Shutdown();

	bool AddRenderTarget(GameObject* newtarget);
	SceneGraphObject ReturnObject(int index);
public:
	vector<SceneGraphObject>* RenderTargets;

private:
	D3DClass* m_D3D;
	HWND* m_HWND;
};

#endif