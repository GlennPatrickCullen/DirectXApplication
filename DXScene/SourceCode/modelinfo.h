////////////////////////////////////////////////////////////////////////////////
// Filename: modelinfo.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELINFO_H_
#define _MODELINFO_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
#include <list>

using namespace std;

struct Vector3
{
	float xP,yP,zP;

	Vector3()
	{
		xP = yP= zP = 0.0f;
	}
	Vector3(float x, float y, float z)
	{
		xP = x;
		yP = y;
		zP = z;
	}
	void SetValues(float x, float y, float z)
	{
		xP = x;
		yP = y;
		zP = z;
	}
};

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelInfo
////////////////////////////////////////////////////////////////////////////////
class ModelInfo
{

public:
	ModelInfo();
	ModelInfo(const ModelInfo&);
	~ModelInfo();

	bool Initialise(char* ModelPath, wchar_t* TexturePath, list<Vector3>);
	bool Initialise(char* ModelPath, wchar_t* TexturePath, wchar_t* NormalMapPath, list<Vector3>);
	bool Initialise(char* ModelPath, wchar_t* TexturePath,  list<Vector3>, Vector3 Scale );
	bool Initialise(char* ModelPath, wchar_t* TexturePath, wchar_t* NormalMapPath,  list<Vector3>, Vector3 Scale);
	void Shutdown();
	list<Vector3> GetPosition();
	Vector3 GetScale();
	char* modelPath;
	wchar_t* texturePath;
	wchar_t* normalPath;

private:
	bool needsDisplayList;

	list<Vector3> position;
	Vector3* scale;
};

#endif
