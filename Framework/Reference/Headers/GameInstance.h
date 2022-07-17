#pragma once

#include "Graphic_Device.h"
#include "Level_Manager.h"
#include "Object_Manager.h"
#include "Component_Manager.h"
#include "Render_Manager.h"
#include "Resource_Manager.h"
#include "Time_Manager.h"
#include "Input_Manager.h"
#include "Camera_Manager.h"
#include "Picking.h"
#include "Collision_Manager.h"
#include "ImguiMgr.h"
#include "ZFrustum.h"
#include "Math_Utillity.h"
#include "Sound_Manager.h"

/* 1. 게임내에 필요한 객체(매니져등)들을 모아서 보관한다. */
/* 2. 클라이언트 개발자가 접근하기좋은 루트를 제공해준다. 나. */
/* 3. 진짜 필요한 함수만 클라잉언트개발자에게 ㅇ오픈해주낟. */

BEGIN(Engine)

class ENGINE_DLL CGameInstance final : public CBase
{
public:
	DECLARE_SINGLETON(CGameInstance)
public:
	CGameInstance();
	virtual ~CGameInstance() = default;

public:
	HRESULT Initialize_Engine(HINSTANCE hInst, _uint iNumLevels, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut);
	HRESULT Tick_Engine(_float fTimeDelta);
	HRESULT Render_Engine();
	HRESULT Clear(_uint iLevelID);

	HWND	Get_Window_Handle() const { return  m_Graphic_Desc.hWnd; } 
	GRAPHICDESC Get_Graphic_Desc() const { return m_Graphic_Desc; }

	void Set_TimeScale(const _float& _fTimeScale) { m_fTimeScale = _fTimeScale; }
	_float Get_TimeScale() { return m_fTimeScale; }

	_float Get_UnScaledTimeDelta() { return m_fUnScaledTimeDelta; }

public: /* For.Graphic_Device */	
	void		Render_Begin(void);
	void		Render_End(HWND hWnd = NULL);
	//void		Deferred_Begin();
	//void		
	LPDIRECT3DDEVICE9* Get_Device(void);
	HRESULT		Add_Text(_point _Pos, _point _AfterPos, _float _Speed, D3DXCOLOR _Color, _float _CountTime, _tchar* _tString, int _iParamCnt, ...);
	HRESULT		Add_Text(_point _Pos, D3DXCOLOR _Color, _float _CountTime, _tchar* _tString, int _iParamCnt, ...);
	HRESULT		Add_Text(_point _Pos, _tchar* _tString, int _iParamCnt, ...);

public: /* For.Level_Manager */
	HRESULT Open_Level(_uint iLevelID, class CLevel* pLevel);
	HRESULT	Register_OpenLevelEvent(_uint iLevelID, CLevel* pLevel);
	void	Set_CurrentLevelIndex(_uint iLevelID);
	_uint	Get_CurrentLevelIndex();
	CLevel* Get_CurrentLevel();

public: /* For.Object_Manager */
	template <typename T>
	HRESULT Add_Prototype_GameObject()
	{
		if (nullptr == m_pObject_Manager)
			return E_FAIL;

		if (!m_pObject_Manager->Add_Prototype<T>())
			return E_FAIL;

		return S_OK;
	}
	template <typename T>
	CGameObject* Add_GameObject(_uint iLevelIndex, const _tchar* pLayerTag, CTransform* pParent = nullptr, void* pArg = nullptr, _bool _bMemoryPool = false)
	{
		return m_pObject_Manager->Add_GameObject<T>(iLevelIndex, pLayerTag, pParent, pArg, _bMemoryPool);
	}

	template <typename T>
	CGameObject* Get_ParticleSystem(_uint iLevelIndex, const _tchar* pLayerTag, CTransform* pParent = nullptr, void* pArg = nullptr)
	{
		return m_pObject_Manager->Get_ParticleSystem<T>(iLevelIndex, pLayerTag, pParent, pArg);
	}

	CGameObject* Get_Player_GameObject();
	list<CGameObject*>* Find_Layer(_uint iLevelIndex, const _tchar* pLayerTag);


public: /* For.Component_Mananger */
	HRESULT Add_Prototype_Component(const _char* pPrototypeTag, class CComponent* pPrototype);
	template <typename T>
	T* Clone_Component(void* pArg = nullptr)
	{
		if (nullptr == m_pComponent_Manager)
			return nullptr;

		return m_pComponent_Manager->Clone_Component<T>(pArg);
	}

public: /* For.Render_Mananger */
	HRESULT Add_RenderGroup(RENDERGROUP eGroup, class CGameObject* pGameObject);
	HRESULT Draw_RenderGroup();
	HRESULT Add_Light(CLight* _pLight);
	void	Add_BlurWidth();
	void	Reset_BlurWidth();

public: /* For.Resource_Mananger */
	HRESULT Remove_Textures_By_MemoryType(MEMORY_TYPE _eMemType);

	HRESULT Load_Textures(const _tchar * _strKey, const _tchar * pTextureFilePath, TEXTURE_TYPE eType = TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE eMemType = MEMORY_TYPE::MEMORY_STATIC);
	HRESULT Load_Shader(const _tchar* _strKey, const _tchar* pShaderFilePath, MEMORY_TYPE eMemType = MEMORY_TYPE::MEMORY_STATIC);

	vector<LPDIRECT3DBASETEXTURE9>* Get_Textures_From_Key(const _tchar * _Str_Key, MEMORY_TYPE _eType = MEMORY_TYPE::MEMORY_END);
	ID3DXEffect** Get_Shader_From_Key(const _tchar* _Str_Key, MEMORY_TYPE _eType = MEMORY_TYPE::MEMORY_END);


public: /* For.Time_Manager */
	HRESULT Add_Timer(_uint eTimer);
	HRESULT Add_TimerEvent(_uint _iEventNum, CBase* _Instance, _float _fTime, _bool _bLoop = false, _bool _bUseTimeScale = false, _bool _bAlwaysCall = false);
	_float Compute_Timer(_uint eTimer);

public: /* For.Input_Manager */
	bool Is_KeyState(KEY _Key, KEY_STATE _KeyState);
	_byte Get_DIMouseKeyState(MOUSEBUTTON eMouseButtonID);
	_long Get_DIMouseMoveState(MOUSEMOVE eMouseMove);

public: /* For.Camera_Manager */
	void Register_Camera(const _tchar* _CameraTag, CCamera* _CameraCom);
	void Set_Camera_Target(CTransform* _Target = nullptr, const _tchar* _CameraTag = TEXT(""));
	CCamera* Get_Camera(const _tchar* _CameraTag = TEXT(""));
	void Set_Current_Camera(const _tchar* _CameraTag = TEXT(""));
	void Update_MovingCam();
	void Set_MovingCam(CGameObject* _pMovingCam);
	CGameObject* Get_MovingCam();
	void Swap_Camera();
	void Add_Shaking(_float _fOffset, _float _fInclination);
	void Switch_Camera(const _tchar* _CameraTag, _float _fTime);
	void Switch_Player(CTransform* _pCurCamera, CTransform* _pNextCamera, const _tchar* _NextCameraTag, _float fTime);

public: /* For.Sound_Manager */
	int  VolumeUp(CHANNELID eID, _float _vol);
	int  VolumeDown(CHANNELID eID, _float _vol);
	int  BGMVolumeUp(_float _vol);
	int  BGMVolumeDown(_float _vol);
	int  Pause(CHANNELID eID);
	_uint PlaySoundW(TCHAR* pSoundKey, _float _vol);
	_uint PlaySoundW(TCHAR* pSoundKey, _uint _iIndex , _float _vol);
	void PlayBGM(TCHAR* pSoundKey, _float _vol);
	void StopSound(_uint _iChannelIndex);
	void StopAll();


public: /* For.IMGUI_Manager */
	HRESULT ImGuiImplHandle(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public: /* For. Collision_Manager */
	void Add_Collider(CCollider* pCollider);
	void Erase_Collider(CCollider* pCollider);

public:/* For.ZFrustum*/
	_bool IsIn(D3DXVECTOR3* pv);
	_bool IsInSphere(D3DXVECTOR3* pv, float radius);
	_bool Draw_Frustum();



private:
	CGraphic_Device*				m_pGraphic_Device = nullptr;
	CLevel_Manager*					m_pLevel_Manager = nullptr;
	CObject_Manager*				m_pObject_Manager = nullptr;
	CComponent_Manager*				m_pComponent_Manager = nullptr;
	CRender_Manager*				m_pRender_Manager = nullptr;
	CResource_Manager*				m_pResource_Manager = nullptr;
	CTime_Manager*					m_pTime_Manager = nullptr;
	CInput_Manager*					m_pInput_Manager = nullptr;
	CCamera_Manager*				m_pCamera_Manager = nullptr;
	//CImguiMgr*						m_pIMGUI_Manager = nullptr;
	CCollision_Manager*				m_pCollision_Manager = nullptr;
	CSound_Manager*                 m_pSound_Manager = nullptr;
	CZFrustum*						m_pZFrustum = nullptr;
	
private:
	GRAPHICDESC						m_Graphic_Desc;
	_float							m_fTimeScale = 1.f;
	_float							m_fUnScaledTimeDelta;

public:
	static void Release_Engine();
	virtual void Free() override;
};

END