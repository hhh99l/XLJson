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
		void AddIndent();		// ��������
		void DecIndent();		// ��������
		void WriteIndext();

		std::string StringToquoteString(const std::string& str);	//	��ͨ�ַ���ת���ɴ�˫���ŵ��ַ���

		unsigned int m_iIndentation{ 0 };	//����ֵ
		std::string m_strIndent;			//�����ַ���
		std::string m_strVaule;
	};
}

