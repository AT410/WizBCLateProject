#pragma once
#include "stdafx.h"

#ifdef _BaseLua
namespace BaseLua
{
	//----------------------------------------------------------------------------
	//例外クラス
	//----------------------------------------------------------------------------
	class LuaException : public exception
	{
		// メッセージ変数
		wstring m_Message;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	m1  第1メッセージ（警告文）
		@param[in]	m2  第2メッセージ（問題となったデータ）
		@param[in]	m3  第3メッセージ（発生した位置）
		*/
		//--------------------------------------------------------------------------------------
		LuaException(const wstring&  m1, const wstring&  m2, const wstring& m3) {
			m_Message = m1;
			m_Message += L"\r\n";
			m_Message += m2;
			m_Message += L"\r\n";
			m_Message += m3;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief メッセージの取得
		@return	メッセージ文字列の参照
		*/
		//--------------------------------------------------------------------------------------
		const wstring& what_w() const throw() {
			return m_Message;
		}
	};

	enum class LuaParamType
	{
		Nil,
		Number,
		String,
		Boolean
	};

	class LuaFuncParamItem
	{
	public:
		
		LuaFuncParamItem();

		// -- Number --
		LuaFuncParamItem(const int num);
		// -- String --
		LuaFuncParamItem(const string& str);
		// -- Boolean --
		LuaFuncParamItem(const bool flag);

		LuaParamType GetType() { return m_type; }

		string GetStr() { return m_str; }
		int GetNumber() { return m_number; }
		bool GetFlag() { return m_flag; }

	private:
		LuaParamType m_type;

		string m_str;
		int m_number;
		bool m_flag;
	};

	class LuaFuncParam :public std::enable_shared_from_this<LuaFuncParam>
	{
	private:
		vector<LuaFuncParamItem> m_Items;

	public:
		LuaFuncParam();

		// -- パラメータ設定 --
		shared_ptr<LuaFuncParam> SetNil();

		shared_ptr<LuaFuncParam> SetNumber(const int number);

		shared_ptr<LuaFuncParam> SetString(const string& str);

		shared_ptr<LuaFuncParam> SetBoolean(const bool flag);

		// -- 配列クリア --
		void Clear() { m_Items.clear(); }

		int Count() { return static_cast<int>(m_Items.size()); }

		vector<LuaFuncParamItem>& GetItems(){ return m_Items; }

		std::shared_ptr<LuaFuncParam> GetThis()
		{
			return shared_from_this();
		}

	};
}
#endif // _BaseLua
