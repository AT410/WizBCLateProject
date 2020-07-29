#include "stdafx.h"

namespace basecross
{
	unique_ptr<ImApp,ImApp::ImAppDeleter> ImApp::m_Instance;

	ImApp::ImApp(HWND hWnd)
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

	}

	void ImApp::CreateApp(HWND hWnd)
	{
		if (m_Instance.get() == 0)
		{
			m_Instance.reset(new ImApp(hWnd));
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

		
		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
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