#include "JsonParse.h"

bool XLJSON::Parse::ParseJsonStr(const std::string& strInput, XLJSON::Value& value)
{
	// ��һ���ַ�����Ϣ
	m_nLength = strInput.length();
	m_pBegin = strInput.c_str();
	m_pEnd = m_pBegin + strInput.length();
	
	return ParseVaule(value);;
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
	case '1':
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
	case 't':
	case 'n':
		bok = ParseBoolAndNull(value);
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
			UpdateErrorMsg("when parseing object value name,we don't find the symbol of beginned\"");
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
			UpdateErrorMsg("when parseing object ,we don't find the symbol of :");
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
		// ƥ���������
		

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

bool XLJSON::Parse::ParseBoolAndNull(XLJSON::Value& valOut)
{
	int nOffset = 0;
	if (m_pBegin + 5 <= m_pEnd)
	{
		nOffset = 5;
		if (!strncmp(m_pBegin, "false", 5))
		{
			valOut = XLJSON::Value(false);
			goto sucess;
		}
	}

	if (m_pBegin + 4 <= m_pEnd)
	{
		nOffset = 4;
		if (!strncmp(m_pBegin, "true", 4))
		{
			valOut = XLJSON::Value(true);
			goto sucess;
		}
		else if (!strncmp(m_pBegin, "null", 4))
		{
			goto sucess;
		}
	}
	UpdateErrorMsg("ParseBoolAndNull Error");
	return false;

sucess:
	m_pBegin = m_pBegin + nOffset;

	return true;
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
	NumberType eNumType = Number_UInt;
	std::string strNum;
	char ch = GetCurChar();
	// ��ȡ����
	if (ch == '-')
	{
		eNumType = Number_Int;
		strNum += ch;
		ModeStrPtr();
	}

	// ��ȡ������������
	ch = GetCurChar();
	if (ch < '0' || ch > '9')
	{
		UpdateErrorMsg("-���ź���û������");
		return false;
	}

	do
	{
		strNum += ch;
		ModeStrPtr();
		ch = GetCurChar();
	} while (ch >= '0' && ch <= '9');
	
	// ��ȡС������
	if (ch == '.')
	{
		eNumType = Number_Double;
		strNum += ch;
		char ch = GetNextChar();
		if (ch < '0' || ch > '9')
		{
			UpdateErrorMsg("С�������Ī������");
			return false;
		}

		do
		{
			strNum += ch;
			ModeStrPtr();
			ch = GetCurChar();
		} while (ch >= '0' && ch <= '9');
	}

	// Todo ��ȡָ������
	
	
	switch (eNumType)
	{
	case XLJSON::Number_Double:
	{
		double dNum = std::stod(strNum.c_str());
		valOut = XLJSON::Value(dNum);
		break;
	}
	case XLJSON::Number_UInt:
	{
		unsigned int nNum = std::stoul(strNum.c_str());
		valOut = XLJSON::Value(nNum);
		break;
	}
	case XLJSON::Number_Int:
	{
		int nNum = std::stoi(strNum.c_str());
		valOut = XLJSON::Value(nNum); 
		break;
	}
	default:
		break;
	}

	return true;
}

void XLJSON::Parse::SkipWhiteSpace()
{
	while(*m_pBegin == ' ' || *m_pBegin == '\r' || *m_pBegin == '\t' ||*m_pBegin == '\n')
	{
		++m_pBegin;
	}
}

void XLJSON::Parse::UpdateErrorMsg(const std::string& strMsg)
{
	// ����Ѿ����ڴ�����Ϣ���򲻸��´�����Ϣ
	if (m_strErrorMsg.empty())
	{
		m_strErrorMsg = strMsg;
	}
}

inline char XLJSON::Parse::GetCurChar()
{
	if (m_pBegin == m_pEnd)
		return 0;

	return *m_pBegin;
}

inline char XLJSON::Parse::GetNextChar()
{
	if (m_pBegin + 1 == m_pEnd)
		return 0;

	return *(m_pBegin + 1);
}

inline bool XLJSON::Parse::ModeStrPtr(unsigned int nIndex)
{
	if (m_pBegin + nIndex <= m_pEnd)
	{
		m_pBegin = m_pBegin + nIndex;
		return true;
	}
		

	return false;
}
