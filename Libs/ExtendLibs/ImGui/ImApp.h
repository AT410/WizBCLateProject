#pragma once
#include "stdafx.h"

namespace basecross
{
	class ImGuiObject
	{
	public:
		ImGuiObject() {}

		// -- ���������� --
		virtual void OnInit() = 0;

		// -- �`�揈�� --
		virtual void OnGUI() = 0;
	};

	class ImApp
	{
	private:
		// �f���[�^�[
		struct ImAppDeleter
		{
			void operator()(ImApp *p) { delete p; }
		};

		static unique_ptr<ImApp, ImAppDeleter> m_Instance;		//<-�C���X�^���X

		vector<shared_ptr<ImGuiObject>> m_guiObjects;

		int m_maxImCount;
			// Our state
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


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
	};
}