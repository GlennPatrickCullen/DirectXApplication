#include "modelinfo.h"

ModelInfo::ModelInfo()
{
	modelPath = 0;
	texturePath = 0;
	normalPath =0;
	//position = 0;
	scale = 0;
}

ModelInfo::ModelInfo(const ModelInfo&)
{

}

ModelInfo::~ModelInfo()
{

}

bool ModelInfo::Initialise(char* ModelPath, wchar_t* TexturePath, list<Vector3> Position)
{
	delete modelPath;
	delete texturePath;
	modelPath = 0;
	texturePath = 0;

	//modelPath = new char;
	modelPath = ModelPath;

	texturePath = new wchar_t;
	texturePath = TexturePath;

	//position = new Vector3;
	//position->SetValues(Position.xP, Position.yP, Position.zP);
	for each (Vector3 pos in Position)
	{
		position.push_front(pos);
	}
	scale = new Vector3;
	scale ->SetValues(1,1,1);
	if (!modelPath || !texturePath || !scale)
	{
		return false;
	}
	
	return true;
}

bool ModelInfo::Initialise(char* ModelPath, wchar_t* TexturePath, list<Vector3> Position, Vector3 Scale )
{
	delete modelPath;
	delete texturePath;
	modelPath = 0;
	texturePath = 0;

	//modelPath = new char;
	modelPath = ModelPath;

	texturePath = new wchar_t;
	texturePath = TexturePath;

	for each (Vector3 pos in Position)
	{
		position.push_front(pos);
	}
	scale = new Vector3;
	scale ->SetValues(Scale.xP, Scale.yP, Scale.zP);

	if (!modelPath || !texturePath ||  !scale)
	{
		return false;
	}
	
	return true;
}

bool ModelInfo::Initialise(char* ModelPath, wchar_t* TexturePath, wchar_t* NormalMapPath, list<Vector3> Position)
{
	delete modelPath;
	delete texturePath;
	modelPath = 0;
	texturePath = 0;

	//modelPath = new char;
	modelPath = ModelPath;
	normalPath = NormalMapPath;
	texturePath = new wchar_t;
	texturePath = TexturePath;

	for each (Vector3 pos in Position)
	{
		position.push_front(pos);
	}
	scale = new Vector3;
	scale ->SetValues(1,1,1);
	if (!modelPath || !texturePath || !scale)
	{
		return false;
	}
	
	return true;
}

bool ModelInfo::Initialise(char* ModelPath, wchar_t* TexturePath, wchar_t* NormalMapPath,  list<Vector3> Position, Vector3 Scale)
{
	delete modelPath;
	delete texturePath;
	modelPath = 0;
	texturePath = 0;

	//modelPath = new char;
	modelPath = ModelPath;
	normalPath = NormalMapPath;
	texturePath = new wchar_t;
	texturePath = TexturePath;

	for each (Vector3 pos in Position)
	{
		position.push_front(pos);
	}
	scale = new Vector3;
	scale ->SetValues(Scale.xP, Scale.yP, Scale.zP);
	if (!modelPath || !texturePath || !scale)
	{
		return false;
	}
	
	return true;
}

void ModelInfo::Shutdown()
{
	//delete modelPath;
	//delete texturePath;
	//delete position;
	modelPath = 0;
	normalPath = 0;
	texturePath = 0;
	
	scale = 0;
}

list<Vector3> ModelInfo::GetPosition()
{
	return position;
}

Vector3 ModelInfo::GetScale()
{
	return *scale;
}