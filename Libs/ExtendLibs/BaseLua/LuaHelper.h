#pragma once
#include "stdafx.h"

#ifdef _BaseLua
namespace BaseLua
{
	//----------------------------------------------------------------------------
	//��O�N���X
	//----------------------------------------------------------------------------
	class LuaException : public exception
	{
		// ���b�Z�[�W�ϐ�
		wstring m_Message;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	m1  ��1���b�Z�[�W�i�x�����j
		@param[in]	m2  ��2���b�Z�[�W�i���ƂȂ����f�[�^�j
		@param[in]	m3  ��3���b�Z�[�W�i���������ʒu�j
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
		@brief ���b�Z�[�W�̎擾
		@return	���b�Z�[�W������̎Q��
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

		// -- �p�����[�^�ݒ� --
		shared_ptr<LuaFuncParam> SetNil();

		shared_ptr<LuaFuncParam> SetNumber(const int number);

		shared_ptr<LuaFuncParam> SetString(const string& str);

		shared_ptr<LuaFuncParam> SetBoolean(const bool flag);

		// -- �z��N���A --
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
