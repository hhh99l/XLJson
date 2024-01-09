#pragma once
#include"JsonValue.h"
#include <string>

namespace XLJSON
{
	class JsonWriter
	{
	public:
		std::string Write(const Value& value);


	private:
		void AddIndent();		// 增加缩进
		void DecIndent();		// 减少缩进
		void WriteIndext();

		std::string StringToquoteString(const std::string& str);	//	普通字符串转换成带双引号的字符串

		unsigned int m_iIndentation{ 0 };	//缩进值
		std::string m_strIndent;			//缩进字符串
		std::string m_strVaule;
	};
}

