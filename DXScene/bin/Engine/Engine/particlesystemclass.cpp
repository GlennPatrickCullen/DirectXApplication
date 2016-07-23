////////////////////////////////////////////////////////////////////////////////
// Filename: particlesystemclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "particlesystemclass.h"
#include <iostream>

bool ParticleSystemClass::CompareParticles(const ParticleType& particleOne, const ParticleType& particleTwo)
{
	//true if first argument should go before second (ie: has a higher distance)
	if( particleOne.distanceFromCamera <= particleTwo.distanceFromCamera)
	{
		return false;
	}
	else
	{
		return true;
	}
}


ParticleSystemClass::ParticleSystemClass()
{
	m_Texture = 0;
	m_particleList = 0;
	m_vertices = 0;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}


ParticleSystemClass::ParticleSystemClass(const ParticleSystemClass& other)
{
}


ParticleSystemClass::~ParticleSystemClass()
{
}

bool ParticleSystemClass::Initialize(ID3D11Device* device, WCHAR* textureFilename)
{
	bool result;


	// Load the texture that is used for the particles.
	result = LoadTexture(device, textureFilename);
	if(!result)
	{
		return false;
	}

	// Initialize the particle system.
	result = InitializeParticleSystem();
	if(!result)
	{
		return false;
	}

	// Create the buffers that will be used to render the particles with.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	return true;
}

void ParticleSystemClass::Shutdown()
{
	// Release the buffers.
	ShutdownBuffers();

	// Release the particle system.
	ShutdownParticleSystem();

	// Release the texture used for the particles.
	ReleaseTexture();

	return;
}

bool ParticleSystemClass::Frame(float frameTime, ID3D11DeviceContext* deviceContext, CameraClass* camera)
{
	bool result;


	// Release old particles.
	KillParticles();

	// Emit new particles.
	EmitParticles(frameTime);
	
	// Update the position of the particles.
	UpdateParticles(frameTime, camera);

	// Update the dynamic vertex buffer with the new position of each particle.
	result = UpdateBuffers(deviceContext, camera);
	if(!result)
	{
		return false;
	}

	return true;
}

void ParticleSystemClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}

ID3D11ShaderResourceView* ParticleSystemClass::GetTexture()
{
	return m_Texture->GetTexture();
}

int ParticleSystemClass::GetIndexCount()
{
	return m_indexCount;
}

bool ParticleSystemClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;


	// Create the texture object.
	m_Texture = new TextureClass;
	if(!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if(!result)
	{
		return false;
	}

	return true;
}

void ParticleSystemClass::ReleaseTexture()
{
	// Release the texture object.
	if(m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}

bool ParticleSystemClass::InitializeParticleSystem()
{
	int i;


	// Set the random deviation of where the particles can be located when emitted.
	m_particleDeviationX = 200.5f;
	m_particleDeviationY = 0.1f;
	m_particleDeviationZ = 200.0f;

	// Set the speed and speed variation of particles.
	m_particleVelocity = 3.0f;
	m_particleVelocityVariation = 0.2f;

	// Set the physical size of the particles.
	m_particleSize = 0.2f;

	// Set the number of particles to emit per second.
	m_particlesPerSecond = 100.0f;

	// Set the maximum number of particles allowed in the particle system.
	m_maxParticles = 400;


	// Create the particle list.
	m_particleList = new std::list<ParticleType>;
	if(!m_particleList)
	{
		return false;
	}



	// Initialize the particle list.
	/*
	for(i=0; i<m_maxParticles; i++)
	{
		m_particleList[i].active = false;
	}*/

	// Initialize the current particle count to zero since none are emitted yet.
	m_currentParticleCount = 0;

	// Clear the initial accumulated time for the particle per second emission rate.
	m_accumulatedTime = 0.0f;

	return true;
}

void ParticleSystemClass::ShutdownParticleSystem()
{
	// Release the particle list.
	if(m_particleList)
	{
		delete m_particleList;
		m_particleList = 0;
	}

	return;
}

bool ParticleSystemClass::InitializeBuffers(ID3D11Device* device)
{
	unsigned long* indices;
	int i;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;


	// Set the maximum number of vertices in the vertex array.
	m_vertexCount = m_maxParticles * 6;

	// Set the maximum number of indices in the index array.
	m_indexCount = m_vertexCount;

	// Create the vertex array for the particles that will be rendered.
	m_vertices = new VertexType[m_vertexCount];
	if(!m_vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(m_vertices, 0, (sizeof(VertexType) * m_vertexCount));

	// Initialize the index array.
	for(i=0; i<m_indexCount; i++)
	{
		indices[i] = i;
	}

	// Set up the description of the dynamic vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = m_vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now finally create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the index array since it is no longer needed.
	delete [] indices;
	indices = 0;

	return true;
}

void ParticleSystemClass::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

void ParticleSystemClass::EmitParticles(float frameTime)
{
	bool emitParticle, found;
	float positionX, positionY, positionZ, velocity, red, green, blue;
	int index, i, j;


	// Increment the frame time.
	m_accumulatedTime += frameTime*1000.0f;

	// Set emit particle to false for now.
	emitParticle = false;
	
	// Check if it is time to emit a new particle or not.
	if(m_accumulatedTime > (1000.0f / m_particlesPerSecond))
	{
		m_accumulatedTime = 0.0f;
		emitParticle = true;
	}

	// If there are particles to emit then emit one per frame.
	if((emitParticle == true) && (m_currentParticleCount < (m_maxParticles - 1)))
	{
			m_currentParticleCount++;

			// Now generate the randomized particle properties.
			positionX = (((float)rand()-(float)rand())/RAND_MAX) * m_particleDeviationX;
			positionY = 50;//(((float)rand()-(float)rand())/RAND_MAX) * m_particleDeviationY;
			positionZ = (((float)rand()-(float)rand())/RAND_MAX) * m_particleDeviationZ;

			velocity = m_particleVelocity + (((float)rand()-(float)rand())/RAND_MAX) * m_particleVelocityVariation;

			/*
			red   = (((float)rand()-(float)rand())/RAND_MAX) + 0.5f;
			green = (((float)rand()-(float)rand())/RAND_MAX) + 0.5f;
			blue  = (((float)rand()-(float)rand())/RAND_MAX) + 0.5f;
			*/
			red = 1;
			green = 1;
			blue = 1;

			// Now since the particles need to be rendered from back to front for blending we have to sort the particle array.
			// We will sort using Z depth so we need to find where in the list the particle should be inserted.
			//index = 0;
			//found = false;

			ParticleType particle;
			particle.positionX = positionX;
			particle.positionY = positionY;
			particle.positionZ = positionZ;
			particle.red       = red;
			particle.green     = green;
			particle.blue      = blue;
			particle.velocity  = velocity;
			particle.active    = true;

			m_particleList->push_front(particle);
			cout<< "" << m_currentParticleCount << endl;
	}

	return;
}

void ParticleSystemClass::UpdateParticles(float frameTime, CameraClass* camera)
{
	static int i = 0;

	// Each frame we update all the particles by making them move downwards using their position, velocity, and the frame time.

	for(std::list<ParticleType>::iterator it1 = m_particleList->begin(); it1 != m_particleList->end(); ++it1)
	{
		it1->rotationY = camera->GetRotation().y;
		it1->positionY = it1->positionY - (it1->velocity *frameTime);

		//calculate distance from camear for depth sorting
		float xdis, ydis, zdis;
		xdis = camera->GetPosition().x - it1->positionX;
		ydis = camera->GetPosition().y - it1->positionY;
		zdis = camera->GetPosition().z - it1->positionZ;

		it1->distanceFromCamera = (xdis*xdis)+(ydis*ydis)+(zdis*zdis);
	}

	//m_particleList->sort(CompareParticles);
	if (i>20)
	{ 
		i=0;
		m_particleList->sort(CompareParticles);
	}
	else
	{
		i++;
	}
	return;
}

void ParticleSystemClass::KillParticles()
{
	int i, j;


	for(std::list<ParticleType>::iterator it1 = m_particleList->begin(); it1 != m_particleList->end(); )
	{
		if(it1->positionY < -3.0f)
		{
			it1 = m_particleList->erase(it1);
			m_currentParticleCount--;
		}
		else
		{
			++it1;
		}

	}

	return;
}

bool ParticleSystemClass::UpdateBuffers(ID3D11DeviceContext* deviceContext, CameraClass* camera)
{
	int index, i;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;

	D3DXVECTOR3 rotPos;

	
	// Initialize vertex array to zeros at first.
	memset(m_vertices, 0, (sizeof(VertexType) * m_vertexCount));

	// Now build the vertex array from the particle list array.  Each particle is a quad made out of two triangles.
	index = 0;

	float tempRot = camera->GetRotation().y;

	int y;

	for(std::list<ParticleType>::iterator it1 = m_particleList->begin(); it1 != m_particleList->end(); ++it1)
	{	

		rotPos.x = sin(D3DXToRadian((90-it1->rotationY+180)))*m_particleSize;
		rotPos.z = sin(D3DXToRadian(it1->rotationY+180))*m_particleSize;


		// Bottom left.
		m_vertices[index].position = D3DXVECTOR3(it1->positionX - rotPos.x, it1->positionY - m_particleSize, it1->positionZ + rotPos.z);
		m_vertices[index].texture = D3DXVECTOR2(0.0f, 1.0f);
		m_vertices[index].color = D3DXVECTOR4(it1->red,it1->green, it1->blue, 1.0f);
		index++;

		// Top left.
		m_vertices[index].position = D3DXVECTOR3(it1->positionX -rotPos.x,it1->positionY + m_particleSize, it1->positionZ + rotPos.z);
		m_vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
		m_vertices[index].color = D3DXVECTOR4(it1->red,it1->green, it1->blue, 1.0f);
		index++;

		// Bottom right.
		m_vertices[index].position = D3DXVECTOR3(it1->positionX + rotPos.x, it1->positionY - m_particleSize,it1->positionZ - rotPos.z);
		m_vertices[index].texture = D3DXVECTOR2(1.0f, 1.0f);
		m_vertices[index].color = D3DXVECTOR4(it1->red, it1->green, it1->blue, 1.0f);
		index++;

		// Bottom right.
		m_vertices[index].position = D3DXVECTOR3(it1->positionX + rotPos.x,it1->positionY - m_particleSize, it1->positionZ - rotPos.z);
		m_vertices[index].texture = D3DXVECTOR2(1.0f, 1.0f);
		m_vertices[index].color = D3DXVECTOR4(it1->red,it1->green, it1->blue, 1.0f);
		index++;

		// Top left.
		m_vertices[index].position = D3DXVECTOR3(it1->positionX - rotPos.x,it1->positionY + m_particleSize,it1->positionZ + rotPos.z);
		m_vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
		m_vertices[index].color = D3DXVECTOR4(it1->red, it1->green, it1->blue, 1.0f);
		index++;

		// Top right.
		m_vertices[index].position = D3DXVECTOR3(it1->positionX + rotPos.x, it1->positionY + m_particleSize,it1->positionZ - rotPos.z);
		m_vertices[index].texture = D3DXVECTOR2(1.0f, 0.0f);
		m_vertices[index].color = D3DXVECTOR4(it1->red,it1->green, it1->blue, 1.0f);
		index++;
	}
	
	// Lock the vertex buffer.
	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (VertexType*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)m_vertices, (sizeof(VertexType) * m_vertexCount));

	// Unlock the vertex buffer.
	deviceContext->Unmap(m_vertexBuffer, 0);

	return true;
}

void ParticleSystemClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

