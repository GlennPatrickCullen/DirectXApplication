////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "textclass.h"
#include "rendertextureclass.h"
#include "debugwindowclass.h"
#include "textureshaderclass.h"
#include "gameobjectclass.h"
#include "scenegraphobjectclass.h"
#include "renderlistclass.h"
#include "inputclass.h"
#include "normalmapshaderclass.h"
#include "particleshaderclass.h"
#include "particlesystemclass.h"
#include "skydomeclass.h"
#include "skydomeshaderclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(InputClass* , int, int ,float);
	bool Render();
	void AddRenderTargets(list<GameObject*> objects);
	CameraClass* m_Camera;
private:
	bool Render(float , float , float);
	bool RenderToTexture(D3DXMATRIX &worldMatrix, D3DXMATRIX &viewMatrix, D3DXMATRIX &projectionMatrix, D3DXMATRIX &orthoMatrix, float rotation,  float deltavalue);
	bool RenderScene(D3DXMATRIX &worldMatrix, D3DXMATRIX &viewMatrix, D3DXMATRIX &projectionMatrix, D3DXMATRIX &orthoMatrix, float rotation,  float deltavalue);

private:
	D3DClass* m_D3D;
	
	ModelClass* m_Skybox;
	
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	
	TextClass* m_Text;
	
	RenderTextureClass* m_RenderTexture;
	DebugWindowClass* m_DebugWindow;
	TextureShaderClass* m_TextureShader;
	
	
	SceneGraphObject* m_ModelGraphObject;
	RenderList* m_3DLightRenderList;

	NormalMapShaderClass* m_NormalMapShader;

	ParticleShaderClass* m_ParticleShader;
	ParticleSystemClass* m_ParticleSystem;

	SkyDomeClass* m_SkyDome;
	SkyDomeShaderClass* m_SkyDomeShader;

	bool bumbToggle;

	D3DXMATRIX baseViewMatrix;
};

#endif