#include "GameInstance.h"
#include "ImguiMgr.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "Get_Lucky.h"

IMPLEMENT_SINGLETON(CImguiMgr)

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

CImguiMgr::CImguiMgr()
	: show_demo_window(false)
{
}

HRESULT CImguiMgr::Initialize()
{
	

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\malgun.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesKorean());
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	
	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(GAMEINSTANCE->Get_Window_Handle());
	ImGui_ImplDX9_Init(DEVICE);
	Get_Lucky::Get_Instance();

	return S_OK;
}

void CImguiMgr::Tick(float fTimeDelta)
{
}

HRESULT CImguiMgr::Render(void)
{
	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	

	if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin(u8"서로서로 도와요");                          // Create a window called "Hello, world!" and append into it.

		//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		
		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

		if (ImGui::Button(u8"힘이 나는 버튼"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		{
			GAMEINSTANCE->Add_Text(
				_point{ 400, 300 },
				D3DCOLOR_ARGB(255, 130, 255, 0),
				1.9f,
				L"에버스페이스 팀 화이팅!!!!!!!!!!!!!!!!",
				0);

			Get_Lucky::Get_Instance()->Team_EverSpace();
		}
		//ImGui::SameLine();
		//ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
	
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return S_OK;
}

HRESULT CImguiMgr::ImGuiImplHandle(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	

	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return S_OK;

	return E_FAIL;
}

void CImguiMgr::Free()
{
	__super::Free();

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	Get_Lucky::Get_Instance()->Destroy_Instance();

	delete this;
}
