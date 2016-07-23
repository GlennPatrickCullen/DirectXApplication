#include "scenegraphobjectclass.h"

SceneGraphObject::SceneGraphObject()
{
	objectRef =0;
	model =0;
}

/*
SceneGraphObject::SceneGraphObject(const SceneGraphObject&)
{

}*/

SceneGraphObject::~SceneGraphObject()
{

}

bool SceneGraphObject::Initialise(GameObject* Object, D3DClass* D3D, HWND hwnd)
{
	objectRef = Object;
	bool result;
	model = new ModelClass;
	if(!model)
	{
		return false;
	}

	if (Object->modelInfo->normalPath != 0)
	{
		result = model->Initialize(D3D->GetDevice(),(char*)objectRef->modelInfo->modelPath,(WCHAR*)objectRef->modelInfo->texturePath,(WCHAR*)objectRef->modelInfo->normalPath);
		if(!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}

	}
	else
	{
		result = model->Initialize(D3D->GetDevice(),(char*)objectRef->modelInfo->modelPath,(WCHAR*)objectRef->modelInfo->texturePath);
		if(!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
	}
	return true;
}

void SceneGraphObject::Shutdown()
{

	model->Shutdown();
	delete model;
	model = 0;

	objectRef = 0;
}

void SceneGraphObject::Render(ID3D11DeviceContext* deviceContext)
{
	model->Render(deviceContext);
}
