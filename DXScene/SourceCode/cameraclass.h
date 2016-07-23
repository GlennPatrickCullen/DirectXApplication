////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>

#include "inputclass.h"
#include "soundclass.h"
////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void MovePosition(float dx, float dy, float dz);

	void SetRotation(float, float, float);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void Render();
	void RenderForText();
	void GetViewMatrix(D3DXMATRIX&);
	D3DXMATRIX GetBaseViewMatrix();
	void Rotate(float x, float y, float z);
	bool CameraControl(InputClass* Input, float dtime);
	bool playSound;
private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	D3DXMATRIX m_viewMatrix;
	D3DXMATRIX m_baseViewMatrix;

	void SetYPR(float x, float y, float z);
	float Yaw;
	float Pitch;
	float Roll;
	D3DXVECTOR3 up, position, lookAt, forward, side;
	float CosYaw,CosPitch,CosRoll;
	float SinYaw,SinPitch,SinRoll;
		
	float PI;


};

#endif