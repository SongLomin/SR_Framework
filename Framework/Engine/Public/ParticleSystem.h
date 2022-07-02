#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CTransform;
class CRenderer;

class ENGINE_DLL CParticleSystem :
    public CGameObject
{
public:
	struct ParticleDesc
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 velocity = D3DXVECTOR3(0.f, 0.f, 0.f);
		D3DXVECTOR3 acceleration;
		float       lifeTime;     // how long the particle lives for before dying  
		float       age = 0.f;          // current age of the particle  
		D3DXCOLOR   color;        // current color of the particle   
		D3DXCOLOR   colorFade;    // how the color fades with respect to time
		bool        isAlive = true;
	};

protected:
	explicit CParticleSystem() = default;
    virtual ~CParticleSystem() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	//���� ���� �۾� ���� (������� ����)
	virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr);
	virtual HRESULT Render();


public:
	virtual void Reset();
	virtual void ResetParticle(ParticleDesc* attribute) = 0;
	virtual void AddParticle();

	bool IsEmpty();
	bool IsDead();

protected:
	virtual void RemoveDeadParticles();

protected:
	CTransform*				m_pTransform = nullptr;
	CRenderer*				m_pRenderer = nullptr;


protected:
	D3DXVECTOR3             m_origin;
	float                   m_emitRate;   // rate new particles are added to system
	float                   m_size;       // size of particles
	IDirect3DVertexBuffer9* m_vb = nullptr;
	std::list<ParticleDesc> m_particles;
	int                     m_maxParticles; // max allowed particles system can have

private:
	DWORD m_vbSize;      // size of vb
	DWORD m_vbOffset;    // offset in vb to lock   
	DWORD m_vbBatchSize; // number of vertices to lock starting at _vbOffset

public:
    virtual void Free() override;
};

END