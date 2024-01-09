#include "JsonParse.h"

bool XLJSON::Parse::ParseJsonStr(const std::string& strInput, XLJSON::Value& value)
{
	m_pBegin = strInput.c_str();
	m_pEnd = m_pBegin + strInput.length();

	ParseVaule(value);
	


	return false;
}

std::string XLJSON::Parse::GetLastErrorMsg()
{
	return std::string();
}

bool XLJSON::Parse::ParseVaule(XLJSON::Value& valOut)
{
	SkipWhiteSpace();
	XLJSON::Value value(XLJSON::ValueNull);
	bool bok = true;
	switch (*m_pBegin)
	{
	case '-':
	case '0':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		bok = ParseNumber(value);
		break;
	case 'f':
		break;
	case 't':
		break;

	case '\"':
	{
		std::string str;
		bok = ParseString(str);
		if (!bok)
		{
			m_strErrorMsg = "ParseString Error";
			break;
		}
		value = XLJSON::Value(str);
		break;
	}

	case '{':
		ParseObject(value);

		break;

	case '[':
		break;
	case ']':
		break;
	}
	valOut = value;
	return bok;
}

bool XLJSON::Parse::ParseObject(XLJSON::Value& valOut)
{
	bool bOk = true;
	m_pBegin++;
	do
	{
		SkipWhiteSpace();
		if (*m_pBegin != '\"')
		{
			m_strErrorMsg = "when parseing object value name,we don't find the symbol of beginned\"";
			bOk =  false;
			break;
		}

		std::string strName;
		bOk = ParseString(strName);
		if(!bOk)
			break;

		SkipWhiteSpace();
		if (*m_pBegin != ':')
		{
			m_strErrorMsg = "when parseing object ,we don't find the symbol of :";
			bOk = false;
			break;
		}
		m_pBegin++;
		SkipWhiteSpace();
		XLJSON::Value value(XLJSON::ValueNull);
		bOk = ParseVaule(value);
		if (!bOk)
			break;

		SkipWhiteSpace();
		// ∆•≈‰ÕÍΩ· ¯¡À
		

		if (*m_pBegin != ',' && *m_pBegin != '}')
		{
			bOk = false;
			break;
		}
		valOut[strName] = value;
		if (*m_pBegin == '}')
			break;

		m_pBegin++;
	} while (1);

	return bOk;
}

bool XLJSON::Parse::ParseString(std::string& strOut)
{
	if (*m_pBegin != '\"')
		return false;
	
	const char* pStr = m_pBegin + 1;
	while (pStr <= m_pEnd)
	{
		if (*pStr == '\"')
		{
			m_pBegin = pStr +1;
			return true;
		}
		strOut += *pStr;
		pStr++;
	}

	strOut = "";
	return false;
}

bool XLJSON::Parse::ParseNumber(XLJSON::Value& valOut)
{
	return false;
}

void XLJSON::Parse::SkipWhiteSpace()
{
	while(*m_pBegin == ' ' || *m_pBegin == '\r' || *m_pBegin == '\t')
	{
		++m_pBegin;
	}
}
