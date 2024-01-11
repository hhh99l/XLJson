#pragma once
#include "JsonValue.h"
namespace XLJSON
{
	enum NumberType
	{
		Number_Double,
		Number_UInt,
		Number_Int
	};

	class Parse
	{
	public:
		bool ParseJsonStr(const std::string& strInput, XLJSON::Value& value);
		std::string GetLastErrorMsg();

	private:
		bool ParseVaule(XLJSON::Value &valOut);
		bool ParseObject(XLJSON::Value& valOut);
		bool ParseArray(XLJSON::Value& valOut);
		bool ParseBoolAndNull(XLJSON::Value& valOut);
		bool ParseString(XLJSON::Value& valOut);
		bool ParseString(std::string& strOut);
		bool ParseNumber(XLJSON::Value& valOut);

		void UpdateErrorMsg(const std::string& strMsg);
		void SkipWhiteSpace();

		inline char GetCurChar();
		inline char GetNextChar();
		inline bool MoveStrPtr(unsigned int nIndex = 1);
		std::string m_strErrorMsg;
		const char* m_pBegin;
		const char* m_pEnd;

	};
}

