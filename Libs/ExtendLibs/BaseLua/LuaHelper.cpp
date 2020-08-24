#include "stdafx.h"

#ifdef _BaseLua
namespace BaseLua
{
	LuaFuncParamItem::LuaFuncParamItem()
		:m_type(LuaParamType::Nil)
	{

	}

	LuaFuncParamItem::LuaFuncParamItem(const int num)
		:m_type(LuaParamType::Number)
	{
		m_number = num;
	}

	LuaFuncParamItem::LuaFuncParamItem(const string& str)
		: m_type(LuaParamType::String)
	{
		m_str = str;
	}

	LuaFuncParamItem::LuaFuncParamItem(const bool flag)
		: m_type(LuaParamType::Boolean)
	{
		m_flag = flag;
	}

	//----------------------------------------------------------------------------
	//LuaFuncParam
	//----------------------------------------------------------------------------
	LuaFuncParam::LuaFuncParam()
		:m_Items()
	{

	}

	shared_ptr<LuaFuncParam> LuaFuncParam::SetNil()
	{
		try
		{
			m_Items.push_back(LuaFuncParamItem());
			return GetThis();
		}
		catch (...)
		{
			throw;
		}
	}

	shared_ptr<LuaFuncParam> LuaFuncParam::SetNumber(const int number)
	{
		try
		{
			m_Items.push_back(LuaFuncParamItem(number));
			return GetThis();
		}
		catch (...)
		{
			throw;
		}
	}

	shared_ptr<LuaFuncParam> LuaFuncParam::SetString(const string& str)
	{
		try
		{
			m_Items.push_back(LuaFuncParamItem(str));
			return GetThis();
		}
		catch (...)
		{
			throw;
		}
	}

	shared_ptr<LuaFuncParam> LuaFuncParam::SetBoolean(const bool flag)
	{
		try
		{
			m_Items.push_back(LuaFuncParamItem(flag));
			return GetThis();
		}
		catch (...)
		{
			throw;
		}
	}
}
#endif // _BaseLua
