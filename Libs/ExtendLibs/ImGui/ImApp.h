#pragma once
#include "stdafx.h"

#ifdef _BSImGui
namespace basecross
{
	class ImGuiObject
	{
	public:
		ImGuiObject() {}

		// -- 初期化処理 --
		virtual void OnInit() = 0;

		// -- 描画処理 --
		virtual void OnGUI() = 0;
	};

	class ImApp
	{
	private:
		// デリーター
		struct ImAppDeleter
		{
			void operator()(ImApp *p) { delete p; }
		};

		static unique_ptr<ImApp, ImAppDeleter> m_Instance;		//<-インスタンス

		vector<shared_ptr<ImGuiObject>> m_guiObjects;

		int m_maxImCount;

		ImApp(HWND hWnd,const int MaxImCount);

	public:
		// -- staic --
		static void CreateApp(HWND hWnd, const int MaxImCount = 10);

		static bool ChackApp();
		
		static unique_ptr<ImApp, ImAppDeleter>& GetApp();

		static void DeleteApp();
		
		void OnUpdate();

		void OnShutdown();

		template<typename T,typename ...Ts>
		shared_ptr<T> AddImGuiObject(Ts&&...params)
		{
			shared_ptr<T> ptr = shared_ptr<T>(new T(params...));
			ptr->OnInit();

			if (m_guiObjects.size() <= m_maxImCount)
			{
				m_guiObjects.push_back(ptr);
			}
			return ptr;
		}

		void RemoveAllImGuiObject()
		{
			m_guiObjects.clear();
		}
	};
}
#endif // !_BSImGui