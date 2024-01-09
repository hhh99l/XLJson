#include "JsonWriter.h"

std::string XLJSON::JsonWriter::Write(const Value& value)
{
	
	switch (value.GetValueType())
	{
	case ValueNull:
		m_strVaule.append("null");
		break;
	case ValueInt:
		m_strVaule.append(std::to_string(value.AsInt()));
		break;
	case ValueUInt:
		m_strVaule.append(std::to_string(value.AsUint()));
		break;
	case ValueReal:
		m_strVaule.append(std::to_string(value.AsReal()));
		break;
	case ValueBool:
		m_strVaule.append(value.AsBool() ? "true" : "false");
		break;
	case ValueString:
		m_strVaule.append(StringToquoteString(value.AsString()));
		break;
	case ValueArray:
	{
		auto member(value.GetMember());
		if (member.size() == 0)
		{
			m_strVaule.append("[]");
		}
		else
		{
			m_strVaule.append("[");
			AddIndent();
			for (auto iter : member)
			{

				m_strVaule.append("\n");
				WriteIndext();
				Write(iter.second);
				m_strVaule.append(",");
			}

			// 删除最后一个逗号
			m_strVaule.resize(m_strVaule.size() - 1);
			m_strVaule.append("\n");

			DecIndent();
			WriteIndext();
			m_strVaule.append("]");
		}
		break;
	}
	case ValueObject:
	{
		auto member(value.GetMember());
		if (member.size() == 0)
		{
			m_strVaule.append("{}");
		}
		else
		{
			m_strVaule.append("{");
			AddIndent();
			for (auto iter : member)
			{
				m_strVaule.append("\n");
				WriteIndext();
				std::string strName = iter.first.GetString();
				m_strVaule.append(StringToquoteString(strName));
				m_strVaule.append(" : ");
				Write(iter.second);
				m_strVaule.append(",");
			}
			// 删除最后一个逗号
			m_strVaule.resize(m_strVaule.size() - 1);
			m_strVaule.append("\n");

			DecIndent();
			WriteIndext();
			m_strVaule.append("}");
		}
		break;
	}
	default:
		break;
	}

	return m_strVaule;
}

void XLJSON::JsonWriter::AddIndent()
{
	m_iIndentation = m_iIndentation + 3;
	m_strIndent = std::string(m_iIndentation, ' ');
}

void XLJSON::JsonWriter::DecIndent()
{
	if (m_iIndentation >= 3)
	{
		m_iIndentation = m_iIndentation - 3;
		m_strIndent = std::string(m_iIndentation, ' ');
	}
}

void XLJSON::JsonWriter::WriteIndext()
{
	m_strVaule.append(m_strIndent);
}

std::string XLJSON::JsonWriter::StringToquoteString(const std::string& str)
{
	return "\"" + str + "\"";
}
