#pragma once
#include "stdafx.h"

namespace basecross
{
	class ImApp
	{
	private:
		// デリーター
		struct ImAppDeleter
		{
			void operator()(ImApp *p) { delete p; }
		};

		static unique_ptr<ImApp, ImAppDeleter> m_Instance;		//<-インスタンス

			// Our state
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


		ImApp(HWND hWnd);

	public:
		// -- staic --
		static void CreateApp(HWND hWnd);

		static bool ChackApp();
		
		static unique_ptr<ImApp, ImAppDeleter>& GetApp();

		static void DeleteApp();
		
		void OnUpdate();

		void OnShutdown();
	};
}