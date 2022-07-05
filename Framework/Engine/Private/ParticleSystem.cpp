#include "ParticleSystem.h"
#include "GameInstance.h"
#include "Math_Utillity.h"



HRESULT CParticleSystem::Initialize(void* pArg)
{
	m_pTransform = Add_Component<CTransform>();
	WEAK_PTR(m_pTransform);
	m_pRenderer = Add_Component<CRenderer>();
	WEAK_PTR(m_pRenderer);


	HRESULT hr = 0;

	hr = DEVICE->CreateVertexBuffer(
		m_vbSize * sizeof(VTXONLYCOLOR),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		VTXONLYCOLOR::FVF,
		D3DPOOL_DEFAULT, // D3DPOOL_MANAGED can't be used with D3DUSAGE_DYNAMIC 
		&m_vb,
		0);

	if (FAILED(hr))
	{
		//버텍스 생성 오류.
		assert(false);
	}

	return S_OK;
}

void CParticleSystem::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CParticleSystem::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CParticleSystem::Render_Begin(ID3DXEffect** Shader)
{
	if (!Get_Enable())
		return E_FAIL;

	if (m_particles.empty())
		return E_FAIL;

	__super::Render_Begin(Shader);


	return S_OK;
}

HRESULT CParticleSystem::Render()
{
	if (!Get_Enable())
		return E_FAIL;

	if (m_particles.empty())
		return E_FAIL;

	__super::Render();
	
	DEVICE->SetFVF(VTXONLYCOLOR::FVF);
	DEVICE->SetStreamSource(0, m_vb, 0, sizeof(VTXONLYCOLOR));

	//
	// render batches one by one
	//

	// start at beginning if we're at the end of the vb
	if (m_vbOffset >= m_vbSize)
		m_vbOffset = 0;

	VTXONLYCOLOR* v = 0;

	m_vb->Lock(
		m_vbOffset * sizeof(VTXONLYCOLOR),
		m_vbBatchSize * sizeof(VTXONLYCOLOR),
		(void**)&v,
		m_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

	DWORD numParticlesInBatch = 0;

	//
	// Until all particles have been rendered.
	//
	std::list<ParticleDesc>::iterator i;
	for (i = m_particles.begin(); i != m_particles.end(); i++)
	{
		if (i->isAlive)
		{
			//
			// Copy a batch of the living particles to the
			// next vertex buffer segment
			//
			v->vPosition = i->position;
			v->DColor = i->color;
			v++; // next element;

			numParticlesInBatch++; //increase batch counter

			// if this batch full?
			if (numParticlesInBatch == m_vbBatchSize)
			{
				//
				// Draw the last batch of particles that was
				// copied to the vertex buffer. 
				//
				m_vb->Unlock();

				DEVICE->DrawPrimitive(
					D3DPT_POINTLIST,
					m_vbOffset,
					m_vbBatchSize);

				//
				// While that batch is drawing, start filling the
				// next batch with particles.
				//

				// move the offset to the start of the next batch
				m_vbOffset += m_vbBatchSize;

				// don't offset into memory thats outside the vb's range.
				// If we're at the end, start at the beginning.
				if (m_vbOffset >= m_vbSize)
					m_vbOffset = 0;

				m_vb->Lock(
					m_vbOffset * sizeof(VTXONLYCOLOR),
					m_vbBatchSize * sizeof(VTXONLYCOLOR),
					(void**)&v,
					m_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

				numParticlesInBatch = 0; // reset for new batch
			}
		}
	}

	m_vb->Unlock();

	// its possible that the LAST batch being filled never 
	// got rendered because the condition 
	// (numParticlesInBatch == _vbBatchSize) would not have
	// been satisfied.  We draw the last partially filled batch now.

	if (numParticlesInBatch)
	{
		DEVICE->DrawPrimitive(
			D3DPT_POINTLIST,
			m_vbOffset,
			numParticlesInBatch);
	}

	// next block
	m_vbOffset += m_vbBatchSize;

	//
	// reset render states
	//


	return S_OK;
}


void CParticleSystem::Reset()
{
	std::list<ParticleDesc>::iterator i;
	for (i = m_particles.begin(); i != m_particles.end(); i++)
	{
		ResetParticle(&(*i));
	}
}

void CParticleSystem::AddParticle(int num)
{
	ParticleDesc Desc;

	for (_int i = 0; i < num; i++)
	{
		ResetParticle(&Desc);

		m_particles.push_back(Desc);
	}
}

void CParticleSystem::AddParticle(int num, CTransform* _pTransformCom)
{
	ParticleDesc Desc;

	m_pTransform->Set_LocalMatrix(_pTransformCom->Get_WorldMatrix());

	for (_int i = 0; i < num; i++)
	{
		ResetParticle(&Desc);

		m_particles.push_back(Desc);
	}

}

void CParticleSystem::AddParticle(int num, _float3 _Pos)
{
	ParticleDesc Desc;

	m_pTransform->Set_State(CTransform::STATE_POSITION, _Pos);

	for (_int i = 0; i < num; i++)
	{
		ResetParticle(&Desc);

		m_particles.push_back(Desc);
	}
}

bool CParticleSystem::IsEmpty()
{
	return m_particles.empty();
}

bool CParticleSystem::IsDead()
{
	std::list<ParticleDesc>::iterator i;
	for (i = m_particles.begin(); i != m_particles.end(); i++)
	{
		// is there at least one living particle?  If yes,
		// the system is not dead.
		if (i->isAlive)
			return false;
	}
	// no living particles found, the system must be dead.
	return true;
}

void CParticleSystem::RemoveDeadParticles()
{
	std::list<ParticleDesc>::iterator i;

	i = m_particles.begin();

	while (i != m_particles.end())
	{
		if (i->isAlive == false)
		{
			// erase returns the next iterator, so no need to
			// incrememnt to the next one ourselves.
			i = m_particles.erase(i);
		}
		else
		{
			i++; // next in list
		}
	}

}

void CParticleSystem::Free()
{
	__super::Free();

	if (m_vb)
		m_vb->Release();
}