#pragma once
#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL ITimerEvent
{
public:
	ITimerEvent() = default;
	virtual ~ITimerEvent() = default;
	virtual void OnTimerEvent(_uint _iEvent_Number) PURE;
};

END