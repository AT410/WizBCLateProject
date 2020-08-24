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

	int l_Add(lua_State* state)
	{
		//第1引数 intとして取得
		lua_Integer x = luaL_checkinteger(state, -2);
		//第2引数
		lua_Integer y = luaL_checkinteger(state, -1);
		lua_Integer result = x + y;

		//戻り値をスタックに積む
		lua_pushnumber(state, result);
		return 1; //戻り値の数を指定
	}

	void Test::OnCreate()
	{
		BaseLua::LuaApp::CreateApp();
		BaseLua::LuaApp::GetApp()->CreateState(L"TEST");

		BaseLua::LuaApp::GetApp()->SetFunction(L"TEST", "add", l_Add);
		BaseLua::LuaApp::GetApp()->SetFunction(L"TEST", "Edit", luaTest::lGenerateEdit);


		//luaL_openlibs(m_state);

		////l_add関数をadd関数としてLuaに登録
		//lua_register(m_state, "add", l_Add);
		//lua_register(m_state, "Edit", luaTest::lGenerateEdit);

		// Luaファイルを開いて読み込み
		// これでLuaステートに関数が登録されます
		wstring mediaPath;
		App::GetApp()->GetDataDirectory(mediaPath);
		string path;
		Util::ConvertWstringtoUtf8(mediaPath, path);

		path += "test.lua";

		BaseLua::LuaApp::GetApp()->DoFileFunction(path);
		//if (luaL_dofile(m_state, path.c_str()))
		//{
		//	printf("%s\n", lua_tostring(m_state, lua_gettop(m_state)));
		//	lua_close(m_state);
		//	return;
		//}

		//lua_pushboolean(m_state, 1);
		//lua_pushnumber(m_state, 100.0);
		//lua_pushstring(m_state, "Marupeke");
		
		shared_ptr<BaseLua::LuaFuncParam> param = make_shared<BaseLua::LuaFuncParam>();
		param->Clear();
		param->SetNumber(1)->SetNumber(1);

		shared_ptr<BaseLua::LuaFuncParam> result = make_shared<BaseLua::LuaFuncParam>();
		result->Clear();

		BaseLua::LuaApp::GetApp()->CallFunction("Calc", param, 1, result);

		//// 関数を呼ぶためにスタックに値を積む
		//lua_getglobal(m_state, "Calc"); // 関数名を積む
		//lua_pushnumber(m_state, 1); // 第 1 引数の値を積む
		//lua_pushnumber(m_state, 1); // 第 2 引数

		//// 関数を呼ぶ. 引数 (二つ), 戻り値 (一つ).
		//lua_call(m_state, 2, 1);

		//// 関数の結果を得る
		//int n = lua_tointeger(m_state, -1);
		//lua_pop(m_state, 1);
		int n = result->GetItems()[0].GetNumber();
		MessageBox(0, Util::IntToWStr(n).c_str(), 0, 0);
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
		ptrString->SetFont(L"暗黒ゾン字", 36);

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

			ImGui::Begin(m_key.c_str());                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text(u8"This is some useful text.");               // Display some text (you can use a format strings too)

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&col); // Edit 3 floats representing a color

				// Buttons return true when clicked (most widgets return true when edited/activated)
			if (ImGui::Button(u8"テスト"))
			{
				counter++;
			}
			ImGui::SameLine();
			if (ImGui::Button(u8"減少"))
				counter--;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::ProgressBar(f);

			auto img = App::GetApp()->GetResource<TextureResource>(L"TestTex");
			auto size = img->GetWidthHeight();
			ImGui::Text("size = %d x %d", size.first, size.second);
			ImGui::Image((void*)img->GetShaderResourceView().Get(), ImVec2(size.first, size.second));

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			ImGui::End();
		}

		App::GetApp()->GetScene<SceneBase>()->SetClearColor(col);
	}
}
//end basecross
