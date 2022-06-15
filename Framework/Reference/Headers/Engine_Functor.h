#pragma once

namespace Engine
{

	class CTag_Finder
	{
	private:
		const TCHAR*	m_pStr;

	public:
		CTag_Finder(const TCHAR* pStr)
			: m_pStr(pStr)
		{

		}

	public:
		template<typename T>
		bool	operator()(T& Pair)
		{
			if (!lstrcmp(m_pStr, Pair.first))
				return true;

			return false;
		}
	};

	class CTag_Finder_c_str
	{
	private:
		const char* m_pStr;

	public:
		CTag_Finder_c_str(const char* pStr)
			: m_pStr(pStr)
		{

		}

	public:
		template<typename T>
		bool	operator()(T& Pair)
		{
			if (!strcmp(m_pStr, Pair.first))
				return true;

			return false;
		}
	};

	static D3DXVECTOR3	Get_MousePos(HWND _hWnd)
	{
		POINT pt{};

		GetCursorPos(&pt);
		ScreenToClient(_hWnd, &pt);

		return D3DXVECTOR3(float(pt.x), float(pt.y), 0.f);
	}

}

