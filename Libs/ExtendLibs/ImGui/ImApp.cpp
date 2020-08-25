#include "stdafx.h"

#ifdef _BSImGui
namespace basecross
{
	unique_ptr<ImApp,ImApp::ImAppDeleter> ImApp::m_Instance;

	ImApp::ImApp(HWND hWnd,int MaxImCount)
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Control

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer bindings
		ImGui_ImplWin32_Init(hWnd);

		auto DeviceRes = App::GetApp()->GetDeviceResources();
		auto D3DDevice = DeviceRes->GetD3DDevice();
		auto D3DDeviceContext = DeviceRes->GetD3DDeviceContext();

		ImGui_ImplDX11_Init(D3DDevice, D3DDeviceContext);
		
		ImFontConfig config;
		config.MergeMode = true;
		io.Fonts->AddFontDefault();
		io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, &config, io.Fonts->GetGlyphRangesJapanese());

		m_maxImCount = MaxImCount > 0 ? MaxImCount : 1;
		m_guiObjects.clear();
	}

	void ImApp::CreateApp(HWND hWnd,const int MaxImCount)
	{
		if (m_Instance.get() == 0)
		{
			m_Instance.reset(new ImApp(hWnd,MaxImCount));
			// -- 初期生成時の処理はここへ --
		}
	}
	
	bool ImApp::ChackApp()
	{
		if (m_Instance.get() != 0)
		{
			return true;
		}
		return false;
	}

	unique_ptr<ImApp, ImApp::ImAppDeleter>& ImApp::GetApp()
	{
		if (m_Instance.get() != 0)
		{
			return m_Instance;
		}
		else
		{
			throw(BaseException(
				L"IMGUIアプリケーションがまだ作成されてません",
				L"if (m_instance.get() == 0)",
				L"ImApp::GetApp()"
			));
		}
	}

	void ImApp::DeleteApp()
	{
		if (m_Instance.get() != 0)
		{
			m_Instance->OnShutdown();
			m_Instance.reset();
		}
	}

	// -- 更新処理 --
	void ImApp::OnUpdate()
	{
		// Start the Dear ImGui frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		for (auto uObj : m_guiObjects)
		{
			// -- 描画処理 --
			uObj->OnGUI();
		}
		// Rendering
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void ImApp::OnShutdown()
	{
		// Cleanup
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}
}
#endif // !_BSImGui