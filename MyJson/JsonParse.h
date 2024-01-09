#pragma once
#include "JsonValue.h"
namespace XLJSON
{
	enum TokenType
	{
		Token_ObjectBegin,
		Token_ObjectEnd,
		Token_ArrayBeigin,
		Token_ArrayEnd,

	};

	class Parse
	{
	public:
		bool ParseJsonStr(const std::string& strInput, XLJSON::Value& value);
		std::string GetLastErrorMsg();

	private:
		bool ParseVaule(XLJSON::Value &valOut);
		bool ParseObject(XLJSON::Value& valOut);

		bool ParseString(std::string& valOut);
		bool ParseNumber(XLJSON::Value& valOut);
		void SkipWhiteSpace();

		std::string m_strErrorMsg;
		const char* m_pBegin;
		const char* m_pEnd;

	};
}

