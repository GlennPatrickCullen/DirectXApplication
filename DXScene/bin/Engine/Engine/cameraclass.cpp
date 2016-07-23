////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"


CameraClass::CameraClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = -10.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
	
	Yaw = 0.0f;
	Pitch = 0.0f;
	Roll = 0.0f;

	PI = 3.14159265359f;
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}

void CameraClass::MovePosition(float dx, float dy, float dz)
{
	m_positionX += dx;
	m_positionY += dy;
	m_positionZ += dz;
	return;
}

void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}

void CameraClass::Rotate(float x, float y, float z)
{
	m_rotationX += x;
	m_rotationY -= y;
	m_rotationZ -= z;
	return;
}


D3DXVECTOR3 CameraClass::GetPosition()
{
	return D3DXVECTOR3(m_positionX, m_positionY, m_positionZ);
}


D3DXVECTOR3 CameraClass::GetRotation()
{
	return D3DXVECTOR3(m_rotationX, m_rotationY, m_rotationZ);
}


void CameraClass::Render()
{
	D3DXMATRIX rotationMatrix;

	CosYaw = cosf(Yaw*PI/180) ;
	CosPitch = cosf(Pitch*PI/180) ;
	CosRoll = cosf(Roll*PI/180) ;

	SinYaw = sinf(Yaw*PI/180);
	SinPitch = sinf(Pitch*PI/180);
	SinRoll = sinf(Roll*PI/180);



	// Setup the vector that points upwards.
	up.x = -CosYaw*SinRoll - SinYaw*SinPitch * CosRoll;
	up.y = CosPitch*CosRoll;
	up.z = -SinYaw*SinRoll - SinPitch*CosRoll *-CosYaw;

	forward.x = SinYaw * CosPitch;
	forward.y = SinPitch;
	forward.z = CosPitch * -CosYaw;

	//side vector
	side.x = (forward.y * up.z)-(forward.z * up.y);
	side.y = -(forward.x * up.z)-(forward.z * up.x);
	side.z = (forward.x * up.y)-(forward.y * up.x);

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, Yaw, Pitch, Roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&forward, &forward, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);
	D3DXVec3TransformCoord(&side, &side, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + forward;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up);


	return;
}

bool CameraClass::CameraControl(InputClass* Input, float dtime)
{
	static float walkTime = 0;
	bool walking = false;
	if(Input->IsKeyPressed(DIK_W))
		{
			m_positionX += forward.x ;
			m_positionY += forward.y;
			m_positionZ += forward.z;
			walking = true;
		}
	if(Input->IsKeyPressed(DIK_S))
		{
			m_positionX -= forward.x ;
			m_positionY -= forward.y;
			m_positionZ -= forward.z;
			walking = true;
		}
	if(Input->IsKeyPressed(DIK_D))
		{
			m_positionX -= side.x ;
			m_positionY -= side.y;
			m_positionZ -= side.z;
			walking = true;
		}
	if(Input->IsKeyPressed(DIK_A))
		{
			m_positionX += side.x ;
			m_positionY += side.y;
			m_positionZ += side.z;
			walking = true;
		}

	//Input->XYDifference();
	float deltaX, deltaY;
	Input->GetMouseDelta(deltaX,deltaY);
	//Rotate(deltaX,deltaY,0);
	SetYPR(deltaX,deltaY,0);

	if (walking == true)
	{
		walkTime += dtime;
		if (walkTime>0.75f)
		{
			walkTime = 0;
			playSound = true;
		}
	}
	return true;

}


void CameraClass::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}

void CameraClass::SetYPR(float x, float y, float z)
	{
		Yaw +=(x/5)*0.0174532925f;
		Pitch -=(y/5)*0.0174532925f;
		Roll -=(z/5)*0.0174532925f;
		
		m_rotationX = D3DXToDegree(Pitch);///0.0174532925f;
		m_rotationY = D3DXToDegree(Yaw);
		m_rotationZ = D3DXToDegree(Roll);
	}


void CameraClass::RenderForText()
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw   = m_rotationY * 0.0174532925f;
	roll  = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up);

	return;
}