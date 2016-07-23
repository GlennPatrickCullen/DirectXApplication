////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Skybox = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_RenderTexture = 0;
	m_DebugWindow = 0;
	m_TextureShader = 0;
	//m_ModelObject =0;
	m_ModelGraphObject =0;
	m_3DLightRenderList =0;
	//m_ModelObjectSphere =0;
	m_NormalMapShader = 0;
	m_ParticleShader = 0;
	m_ParticleSystem = 0;

	m_SkyDome = 0;
	m_SkyDomeShader = 0;
}



GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	

	bumbToggle = false;
	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	//m_Camera->SetPosition(0.0f, 0.0f, -20.0f);
	// create test gameobject
	
	//create 3d render list
	m_3DLightRenderList = new RenderList;
	if(!m_3DLightRenderList)
	{
		return false;
	}
	result = m_3DLightRenderList->Initialise(m_D3D, &hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the 3dLightRenderList object.", L"Error", MB_OK);
		return false;
	}

	m_Skybox = new ModelClass;
	if (!m_Skybox)
	{
		return false;
	}

	result = m_Skybox->Initialize(m_D3D->GetDevice(),"../Engine/data/cube.txt", L"../Engine/data/stone01.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the skybox object.", L"Error", MB_OK);
		return false;
	}

	// add the ModelGraphObject to the 3d Render list
	
	/*
	m_3DLightRenderList->AddRenderTarget(m_ModelObject);
	m_3DLightRenderList->AddRenderTarget(m_ModelObjectSphere);
	*/

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.3f, -1.0f, 1.0f);
	m_Light->SetAmbientColor(0.2, 0.2, 0.2, 0.20);
	
	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->RenderForText();
	m_Camera->GetViewMatrix(baseViewMatrix);
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	// Create the text object.
	m_Text = new TextClass;
	if(!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}


	// Create the sky dome object.
	m_SkyDome = new SkyDomeClass;
	if(!m_SkyDome)
	{
		return false;
	}

	// Initialize the sky dome object.
	result = m_SkyDome->Initialize(m_D3D->GetDevice());
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky dome shader object.
	m_SkyDomeShader = new SkyDomeShaderClass;
	if(!m_SkyDomeShader)
	{
		return false;
	}

	// Initialize the sky dome shader object.
	result = m_SkyDomeShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome shader object.", L"Error", MB_OK);
		return false;
	}

		// Create the render to texture object.
	m_RenderTexture = new RenderTextureClass;
	if(!m_RenderTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if(!result)
	{
		return false;
	}

	// Create the debug window object.
	m_DebugWindow = new DebugWindowClass;
	if(!m_DebugWindow)
	{
		return false;
	}

	// Initialize the debug window object.
	result = m_DebugWindow->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, 100, 100);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the debug window object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the bump map shader object.
	m_NormalMapShader = new NormalMapShaderClass;
	if(!m_NormalMapShader)
	{
		return false;
	}

	// Initialize the bump map shader object.
	result = m_NormalMapShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the bump map shader object.", L"Error", MB_OK);
		return false;
	}

		// Create the particle shader object.
	m_ParticleShader = new ParticleShaderClass;
	if(!m_ParticleShader)
	{
		return false;
	}

	// Initialize the particle shader object.
	result = m_ParticleShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the particle system object.
	m_ParticleSystem = new ParticleSystemClass;
	if(!m_ParticleSystem)
	{
		return false;
	}

	// Initialize the particle system object.
	result = m_ParticleSystem->Initialize(m_D3D->GetDevice(), L"../Engine/data/star.dds");
	if(!result)
	{
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{

		// Release the sky dome shader object.
	if(m_SkyDomeShader)
	{
		m_SkyDomeShader->Shutdown();
		delete m_SkyDomeShader;
		m_SkyDomeShader = 0;
	}

	// Release the sky dome object.
	if(m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}

		// Release the particle system object.
	if(m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}

	// Release the particle shader object.
	if(m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}

	// Release the bump map shader object.
	if(m_NormalMapShader)
	{
		m_NormalMapShader->Shutdown();
		delete m_NormalMapShader;
		m_NormalMapShader = 0;
	}

	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}
	if(m_3DLightRenderList)
	{
		m_3DLightRenderList->Shutdown();
		delete m_3DLightRenderList;
		m_3DLightRenderList =0;
	}
	if(m_ModelGraphObject)
	{
		m_ModelGraphObject->Shutdown();
		delete m_ModelGraphObject;
		m_ModelGraphObject =0;
	}
	// Release the debug window object.
	if(m_DebugWindow)
	{
		m_DebugWindow->Shutdown();
		delete m_DebugWindow;
		m_DebugWindow = 0;
	}

	// Release the render to texture object.
	if(m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}
	// Release the text object.
	if(m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}
	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the model object.
	if(m_Skybox)
	{
		m_Skybox->Shutdown();
		delete m_Skybox;
		m_Skybox = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame(InputClass *Input, int fps, int cpu, float deltaTime)
{
	bool result;
	static float rotation = 0.0f;
	static float delta =0.0f;

	// Run the frame processing for the particle system.
	

	// Set the frames per second.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Update the rotation variable each frame.
	//rotation += (float)D3DX_PI * 0.01f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Update the delta variable each frame. (keep this between 0 and 1)
	//delta += 0.001;
	if(delta >1.0f)
	{
		delta -=1.0f;
	}
	/*
	if(Input->IsKeyPressed(DIK_D))
	{
		m_Camera->MovePosition(10*deltaTime,0,0);
	}
	if(Input->IsKeyPressed(DIK_A))
	{
		m_Camera->MovePosition(-10*deltaTime,0,0);
	}
	*/
	m_Camera->CameraControl(Input, deltaTime);

	m_ParticleSystem->Frame(deltaTime, m_D3D->GetDeviceContext(), m_Camera);
	// Render the graphics scene.
	result = Render(rotation, delta, deltaTime);
	if(!result)
	{
		return false;
	}

	if(Input->IsKeyPressed(DIK_N) && bumbToggle == false)
	{
		bumbToggle = true;
	}
	else if (Input->IsKeyPressed(DIK_L) && bumbToggle == true)
	{
		bumbToggle = false;
	}

	return true;
}


bool GraphicsClass::Render(float rotation, float deltavalue, float deltaTime)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	//D3DXVECTOR3 cameraPosition;
	bool result;
	m_Camera->Render();
	// Render the entire scene to the texture first.
	result = RenderToTexture(worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, rotation, deltavalue);
	if(!result)
	{
		return false;
	}


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	RenderScene(worldMatrix,viewMatrix,projectionMatrix,orthoMatrix,rotation, deltavalue);
	
	//TEXT
	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();
	// Get the world, view, and ortho matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Put the debug window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_DebugWindow->Render(m_D3D->GetDeviceContext(), 50, 50);
	if(!result)
	{
		return false;
	}

	

	// Render the debug window using the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_DebugWindow->GetIndexCount(), worldMatrix, baseViewMatrix,
					orthoMatrix, m_RenderTexture->GetShaderResourceView());
	if(!result)
	{
		return false;
	}

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();
	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix, deltaTime);
	if(!result)
	{
		return false;
	}
	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	m_D3D->TurnOnparticleAlphaBlending();
	m_D3D->GetWorldMatrix(worldMatrix);
	// Put the particle system vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ParticleSystem->Render(m_D3D->GetDeviceContext());

	// Render the model using the texture shader.
	result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
					  m_ParticleSystem->GetTexture());
	if(!result)
	{
		return false;
	}

	// Turn off alpha blending.
	m_D3D->TurnOffAlphaBlending();
	
	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::RenderToTexture(D3DXMATRIX &worldMatrix, D3DXMATRIX &viewMatrix, D3DXMATRIX &projectionMatrix, D3DXMATRIX &orthoMatrix, float rotation,  float deltavalue)
{
	bool result;


	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView());
	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 1.0f, 1.0f);

	// Render the scene now and it will draw to the render to texture instead of the back buffer.
	result = RenderScene(worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, rotation, deltavalue);
	if(!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	return true;
}

bool GraphicsClass::RenderScene(D3DXMATRIX &worldMatrix, D3DXMATRIX &viewMatrix, D3DXMATRIX &projectionMatrix, D3DXMATRIX &orthoMatrix, float rotation, float deltavalue)
{

	D3DXVECTOR3 cameraPosition;
	
	bool result;
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

		m_D3D->GetWorldMatrix(worldMatrix);

	// Get the position of the camera.
	cameraPosition  = m_Camera->GetPosition();

	// Translate the sky dome to be centered around the camera position.
	D3DXMatrixTranslation(&worldMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z);
	//D3DXMatrixTranslation(&worldMatrix, 1, 1,1);

	// Turn off back face culling.
	m_D3D->TurnCullingOff();

	// Turn off the Z buffer.
	m_D3D->TurnZBufferOff();


	// Render the sky dome using the sky dome shader.
	m_SkyDome->Render(m_D3D->GetDeviceContext());
	m_SkyDomeShader->Render(m_D3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
				m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());


	// Turn back face culling back on.
	m_D3D->TurnCullingOn();

	// Turn the Z buffer back on.
	m_D3D->TurnZBufferOn();

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);
	
	for each(SceneGraphObject var in *(m_3DLightRenderList->RenderTargets))
	{
		list<Vector3> posList = var.objectRef->modelInfo->GetPosition();
		for each(Vector3 pos in posList)
		{
			D3DXMatrixIdentity(&worldMatrix);
			D3DXMATRIX yrot;
			D3DXMatrixRotationY(&yrot,rotation);
			worldMatrix = worldMatrix * yrot;

			D3DXMATRIX scaleM;
			D3DXMatrixIdentity(&scaleM);
			D3DXMatrixScaling(&scaleM,var.objectRef->modelInfo->GetScale().xP,var.objectRef->modelInfo->GetScale().yP,var.objectRef->modelInfo->GetScale().zP);
			worldMatrix = worldMatrix*scaleM;

			D3DXMATRIX transM;
			D3DXMatrixIdentity(&transM);
			D3DXMatrixTranslation(&transM,pos.xP,pos.yP,pos.zP);
			worldMatrix = worldMatrix * transM;

	

			//D3DXMatrixTranslation(&worldMatrix,var.objectRef->modelInfo->GetPosition().xP,var.objectRef->modelInfo->GetPosition().yP,var.objectRef->modelInfo->GetPosition().zP);
		
			var.Render(m_D3D->GetDeviceContext());
			if(!bumbToggle)
			{
				result = m_LightShader->Render(m_D3D->GetDeviceContext(), var.model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Light->GetDirection(), m_Light->GetDiffuseColor(),m_Light->GetAmbientColor(), deltavalue, var.model->GetTexture());
				if(!result)
				{
					return false;
				}
			}
			else if(bumbToggle)
			{
				result = m_NormalMapShader->Render(m_D3D->GetDeviceContext(), var.model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, var.model->GetTextureArray(), m_Light->GetDirection(),m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
				if(!result)
				{
					return false;
				}
			}
		
			// Turn on alpha blending.
		}
	
	}
	return true;
}


void GraphicsClass::AddRenderTargets(list<GameObject*> objects)
{
	for each (GameObject* obj in objects)
	{
		m_3DLightRenderList->AddRenderTarget(obj);
	}
}