#include "JsonValue.h"
#include "JsonWriter.h"
bool XLJSON::NodeKey::operator==(const NodeKey& other)const
{
	if (!m_strValue.empty())
		return strcmp(m_strValue.c_str(), other.m_strValue.c_str()) == 0;

	return m_nValue == other.m_nValue;
}

bool XLJSON::NodeKey::operator=(const NodeKey& other)
{
	m_nValue = other.m_nValue;
	m_strValue = other.m_strValue;
	return true;
}

bool XLJSON::NodeKey::operator<(const NodeKey& other) const
{
	if (!m_strValue.empty())
		return strcmp(m_strValue.c_str(), other.m_strValue.c_str()) < 0;

	return m_nValue < other.m_nValue;
}

std::string XLJSON::NodeKey::GetString() const
{
	return m_strValue;
}

XLJSON::Value::Value(ValueType value)
{
	m_eType = value;
	m_iValue = 0;
	m_uValue = 0;
	m_dValue = 0.0;
	m_bValue = false;
}

XLJSON::Value::Value(int value)
{
	m_eType = ValueInt;
	m_iValue = value;
	m_uValue = 0;
	m_dValue = 0.0;
	m_bValue = false;
}

XLJSON::Value::Value(unsigned int value)
{
	m_eType = ValueUInt;
	m_iValue = 0;
	m_uValue = value;
	m_dValue = 0.0;
	m_bValue = false;
}

XLJSON::Value::Value(double value)
{
	m_eType = ValueReal;
	m_iValue = 0;
	m_uValue = 0;
	m_dValue = value;
	m_bValue = false;
}

XLJSON::Value::Value(bool value)
{
	m_eType = ValueBool;
	m_iValue = 0;
	m_uValue = 0;
	m_dValue = 0.0;
	m_bValue = value;
}

XLJSON::Value::Value(const char* value)
{
	m_eType = ValueString;
	m_iValue = 0;
	m_uValue = 0;
	m_dValue = 0.0;
	m_bValue = false;
	m_strValue = value;
}

XLJSON::Value::Value(std::string value)
{
	m_eType = ValueString;
	m_iValue = 0;
	m_uValue = 0;
	m_dValue = 0.0;
	m_bValue = false;
	m_strValue = value;
}


XLJSON::Value::Value(const Value& value)
{
	m_eType = value.m_eType;
	m_iValue = value.m_iValue;
	m_uValue = value.m_uValue;
	m_dValue = value.m_dValue;
	m_bValue = value.m_bValue;
	m_strValue = value.m_strValue;
	m_mapNode = value.m_mapNode;
}

XLJSON::Value& XLJSON::Value::operator[](const std::string strValue)
{
	/*if (m_eType != ValueObject)
	{
		XLJSON::Value val(ValueNull);
		return val;
	}*/

	if (m_eType == ValueNull)
	{
		m_eType = ValueObject;
	}
	NodeKey node(strValue);
	return m_mapNode[node];
}

XLJSON::ValueType XLJSON::Value::GetValueType()const
{
	return m_eType;
}

int XLJSON::Value::AsInt()const
{
	if (m_eType == ValueInt)
		return m_iValue;

	JSON_THROW_ERROR("value type is not expectation");
	return 0;
}

void XLJSON::Value::Swap(Value& val)
{
	Value valTemp(val);
	val = *this;
	*this = val;
}

unsigned int XLJSON::Value::AsUint()const
{
	if (m_eType == ValueUInt)
		return m_uValue;

	JSON_THROW_ERROR("value type is not expectation");
	return 0;
}

double XLJSON::Value::AsReal()const
{
	if (m_eType == ValueReal)
		return m_dValue;

	JSON_THROW_ERROR("value type is not expectation");
	return 0.0;
}

bool XLJSON::Value::AsBool()const
{
	if (m_eType == ValueBool)
		return m_bValue;

	JSON_THROW_ERROR("value type is not expectation");
	return false;
}

std::string XLJSON::Value::AsString()const
{
	if (m_eType == ValueString)
		return m_strValue;
	
	JSON_THROW_ERROR("value type is not expectation");
	return "";
}

std::map<XLJSON::NodeKey, XLJSON::Value> XLJSON::Value::GetMember() const
{
	return m_mapNode;
}

void XLJSON::Value::Append(const XLJSON::Value& value)
{
	if (m_eType == ValueArray)
	{
		NodeKey node(m_mapNode.size());
		m_mapNode[node] = value;
		return;
	}

	JSON_THROW_ERROR("Value::Append only support the type of jsonarray");
	return;
}

bool XLJSON::Value::IsMember(std::string value)
{
	if (m_eType != ValueObject)
		return false;

	NodeKey node(value);
	return m_mapNode.find(node) == m_mapNode.end();
}

std::string XLJSON::Value::ToString() const
{
	JsonWriter write;

	return write.Write(*this);
}

