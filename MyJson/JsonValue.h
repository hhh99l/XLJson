#pragma once
#include <map>
#include <string>
#include <stdexcept>
#include <cassert>
#include <map>

#define JSON_THROW_ERROR(message) throw std::runtime_error( message );

namespace XLJSON
{

	enum ValueType
	{
		ValueNull,
		ValueInt,
		ValueUInt,
		ValueReal,
		ValueBool,
		ValueString,
		ValueArray,
		ValueObject
	};

	class NodeKey
	{
	public:
		NodeKey(int nValue) : m_nValue(nValue), m_strValue("") {};
		NodeKey(std::string str) : m_nValue(0), m_strValue(str) {};
		~NodeKey() {};

		bool operator=(const NodeKey& other);
		bool operator==(const NodeKey& other) const;
		bool operator<(const NodeKey& other) const;

		std::string GetString() const;
	private:
		int			m_nValue;
		std::string	m_strValue;
	};

	class Value
	{
	public:
		Value() {};
		Value(ValueType value);
		Value(int value);
		Value(unsigned int value);
		Value(double value);
		Value(bool value);
		Value(const char* value);
		Value(std::string value);
		Value(const Value& value);

		Value& operator[](const std::string strValue);


		void Swap(Value& val);
		ValueType GetValueType() const;

		int				AsInt() const;
		unsigned int	AsUint() const;
		double			AsReal() const;
		bool			AsBool() const;
		std::string		AsString()const;
		std::string		ToString()const;

		void Append(const Value& value);		// 用于Array追加元素
		bool IsMember(std::string value);

		std::map<NodeKey, Value> GetMember()const;
	private:
		ValueType					m_eType;

		int							m_iValue;
		unsigned int				m_uValue;
		double						m_dValue;
		bool						m_bValue;
		std::string					m_strValue;
		std::map<NodeKey, Value>	m_mapNode;
	};

}


