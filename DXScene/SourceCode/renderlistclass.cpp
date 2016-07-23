
#include "renderlistclass.h"


RenderList::RenderList()
{
	RenderTargets = 0;
	m_D3D = 0;
	m_HWND = 0;
}

RenderList::~RenderList()
{


}

bool RenderList::Initialise(D3DClass* D3D, HWND* hwnd)
{
	RenderTargets = new vector<SceneGraphObject>;
	m_D3D = D3D;
	m_HWND = hwnd;
	
	if(!RenderTargets || !m_D3D || ! m_HWND)
	{
		return false;
	}


	return true;
}

void RenderList::Shutdown()
{
	delete RenderTargets;
	RenderTargets = 0;
	m_D3D = 0;
	m_HWND = 0;
}

bool RenderList::AddRenderTarget(GameObject* newtarget)
{
	if(RenderTargets)
	{
		SceneGraphObject newSceneObject;
		bool result = newSceneObject.Initialise(newtarget,m_D3D,*m_HWND);
		if(!result)
		{
			MessageBox(*m_HWND, L"Could not initialize the Graph object.", L"Error", MB_OK);
			return false;
		}
		//RenderTargets->insert(RenderTargets->begin(),newSceneObject);
		RenderTargets->push_back(newSceneObject);
		return true;
	}
	return false;
}

SceneGraphObject RenderList::ReturnObject(int index)
{
	return (*RenderTargets)[index];

}