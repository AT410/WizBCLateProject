/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	Test::Test(const shared_ptr<Stage>& StagePtr)
		:GameObject(StagePtr),m_cosole(false)
	{
		m_state = luaL_newstate();
	}

	void Test::OnCreate()
	{
		// コンソールを作成する
		AllocConsole();
		// 標準入出力に割り当てる
		FILE* fp = NULL;
		// 昔のコード
		//freopen("CONOUT$", "w", stdout);
		//freopen("CONIN$", "r", stdin);
		// 現在のコード
		freopen_s(&fp, "CONOUT$", "w", stdout);
		freopen_s(&fp, "CONIN$", "r", stdin);
		wcout << L"テストですよ" << endl;

		luaL_openlibs(m_state);

		// Luaファイルを開いて読み込み
		// これでLuaステートに関数が登録されます
		//if (luaL_dofile(m_state, "test.lua")) 
		//{
		//	printf("%s\n", lua_tostring(m_state, lua_gettop(m_state)));
		//	lua_close(m_state);
		//	return;
		//}

		lua_pushboolean(m_state, 1);
		lua_pushnumber(m_state, 100.0);
		lua_pushstring(m_state, "Marupeke");
		
		

		int ret= luaL_dostring(m_state, "print('hello lua script!!')");;
		if (ret != 0)
		{
			cout << "Error:" << lua_tostring(m_state, -1) << endl;
			lua_pop(m_state, 1);
		}

		cout << "Test:" << lua_tostring(m_state, -1) << endl;

		FreeConsole();


		m_cosole = true;
	}

	void Test::OnUpdate()
	{
		auto key = App::GetApp()->GetInputDevice().GetKeyState();
		if (key.m_bPressedKeyTbl[VK_RETURN]&&m_cosole)
		{
			FreeConsole();
			m_cosole = false;
		}
	}

	void Test::OnDestroy()
	{
		lua_close(m_state);
	}
	
	DebugTest::DebugTest(const shared_ptr<Stage>& StagePtr)
		:GameObject(StagePtr)
	{
	}


	void DebugTest::OnCreate()
	{
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetTextRect(Rect2D<float>(16.0f, 50.0f, 640.0f, 480.0f));

		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);
	}

	void DebugTest::OnUpdate()
	{
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring fpsStr(L"テストですよ。\nFPS: ");
		fpsStr += Util::UintToWStr(fps);
		fpsStr += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		fpsStr += Util::FloatToWStr(ElapsedTime);
		fpsStr += L"\n";

		wstring updatePerStr(L"UpdatePerformance:\t");
		updatePerStr += Util::FloatToWStr(GetStage()->GetUpdatePerformanceTime());
		updatePerStr += L"\tmillisecond\n";

		wstring drawPerStr(L"DrawPerformance:\t");
		drawPerStr += Util::FloatToWStr(GetStage()->GetDrawPerformanceTime());
		drawPerStr += L"\tmillisecond\n";

		wstring collPerStr(L"CollisionPerform:\t");
		collPerStr += Util::FloatToWStr(GetStage()->GetCollisionPerformanceTime(), 5);
		collPerStr += L"\tmillisecond\n";

		wstring collMiscStr(L"ColMiscPerform:\t");
		collMiscStr += Util::FloatToWStr(GetStage()->GetCollisionManager()->GetMiscPerformanceTime(), 5);
		collMiscStr += L"\tmillisecond\n";

		wstring collTernCountStr(L"CollisionCountOfTern:\t");
		collTernCountStr += Util::UintToWStr(GetStage()->GetCollisionManager()->GetCollisionCountOfTern());
		collTernCountStr += L"\n";

		wstring ObjCount(L"ObjectCount:\t");
		ObjCount += Util::UintToWStr((UINT)GetStage()->GetGameObjectVec().size());
		ObjCount += L"\n";

		wstring str = fpsStr + updatePerStr + drawPerStr + collPerStr + collMiscStr
			+ collTernCountStr + ObjCount;

		//文字列コンポーネントの取得
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);

	}

	void TestGui::OnInit()
	{

	}

	void TestGui::OnGUI()
	{
		auto col = App::GetApp()->GetScene<SceneBase>()->GetClearColor();

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin(u8"Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text(u8"This is some useful text.");               // Display some text (you can use a format strings too)

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&col); // Edit 3 floats representing a color

			if (ImGui::Button(u8"テスト"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			if (ImGui::Button(u8"減少"))
				counter--;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::ProgressBar(0.5f);

			auto img = App::GetApp()->GetResource<TextureResource>(L"TestTex");
			auto size = img->GetWidthHeight();
			ImGui::Text("size = %d x %d", size.first, size.second);
			ImGui::Image((void*)img->GetShaderResourceView().Get(), ImVec2(size.first, size.second));

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::BeginChild("Test", ImVec2(100, 100), true, ImGuiWindowFlags_::ImGuiWindowFlags_ChildWindow);
			ImGui::EndChild();

			

			ImGui::End();
		}

		App::GetApp()->GetScene<SceneBase>()->SetClearColor(col);
	}
}
//end basecross
