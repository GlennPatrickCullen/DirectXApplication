////////////////////////////////////////////////////////////////////////////////
// Filename: particlesystemclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _PARTICLESYSTEMCLASS_H_
#define _PARTICLESYSTEMCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <list>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"
#include "cameraclass.h"
#include "d3dclass.h"

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// Class name: ParticleSystemClass
////////////////////////////////////////////////////////////////////////////////
class ParticleSystemClass
{
private:
	
	struct ParticleType
	{
		float positionX, positionY, positionZ;
		float rotationY;
		float red, green, blue;
		float velocity;
		bool active;
		float distanceFromCamera;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR4 color;
	};

public:
	ParticleSystemClass();
	ParticleSystemClass(const ParticleSystemClass&);
	~ParticleSystemClass();

		bool Initialize(ID3D11Device*, WCHAR*);
	void Shutdown();
	bool Frame(float frameTime, ID3D11DeviceContext* deviceContext, CameraClass* camera);
	void Render(ID3D11DeviceContext*);

	ID3D11ShaderResourceView* GetTexture();
	int GetIndexCount();

private:
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	bool InitializeParticleSystem();
	void ShutdownParticleSystem();

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();

	void EmitParticles(float);
	void UpdateParticles(float frameTime, CameraClass* camera );
	void KillParticles();

	bool UpdateBuffers(ID3D11DeviceContext* deviceContext, CameraClass* camera);

	void RenderBuffers(ID3D11DeviceContext*);

	static bool CompareParticles(const ParticleType & particleOne, const ParticleType & particleTwo);
private:

	float m_particleDeviationX, m_particleDeviationY, m_particleDeviationZ;
	float m_particleVelocity, m_particleVelocityVariation;
	float m_particleSize, m_particlesPerSecond;
	int m_maxParticles;

	int m_currentParticleCount;
	float m_accumulatedTime;

	TextureClass* m_Texture;

	//ParticleType* m_particleList;

	std::list<ParticleType>* m_particleList;

	int m_vertexCount, m_indexCount;
	VertexType* m_vertices;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
};

#endif