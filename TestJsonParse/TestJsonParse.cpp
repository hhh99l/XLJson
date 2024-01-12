#include "pch.h"
#include "CppUnitTest.h"
#include "../MyJson/JsonParse.h"
#include "../MyJson/JsonValue.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


XLJSON::Value Parser_Helper(const std::string& str)
{
	XLJSON::Value value;
	XLJSON::Parse par;
	if (!par.ParseJsonStr(str, value))
	{
		Logger::WriteMessage(L"����JSON�ַ���ʧ���� ");
		Logger::WriteMessage(str.c_str());
		return XLJSON::Value();
	}
	return value;
}

bool Parser_Helper2(const std::string& str)
{
	XLJSON::Value value;
	XLJSON::Parse par;
	if (!par.ParseJsonStr(str, value))
	{
		return false;
	}
	return true;;
}


namespace TestJsonParse
{
	TEST_CLASS(TestJsonParse)
	{
	public:
		
		TEST_METHOD(���Խ���BOOL��NULL����ֵ)
		{
			Assert::IsTrue(Parser_Helper("false") ==XLJSON::Value(false), L"ֵ������Ԥ��eg1");
			Assert::IsTrue(Parser_Helper("true") == XLJSON::Value(true), L"ֵ������Ԥ��eg2");
			Assert::IsTrue(Parser_Helper("null") == XLJSON::Value(), L"ֵ������Ԥ��eg3");

			Assert::IsTrue(!Parser_Helper2("falsefalse") , L"ֵ������Ԥ��eg4");
			Assert::IsTrue(!Parser_Helper2("false  false") , L"ֵ������Ԥ��eg5");
			Assert::IsTrue(!Parser_Helper2("truetrue") , L"ֵ������Ԥ��eg6");
			Assert::IsTrue(!Parser_Helper2("true true"), L"ֵ������Ԥ��eg7");
			Assert::IsTrue(!Parser_Helper2("nullnull") , L"ֵ������Ԥ��eg8");
			Assert::IsTrue(!Parser_Helper2("null null") , L"ֵ������Ԥ��eg9");
		};

		TEST_METHOD(���Խ���������)
		{
			Assert::IsTrue(Parser_Helper("[]") == XLJSON::Value(XLJSON::ValueArray), L"ֵ������Ԥ�� eg1");
			Assert::IsTrue(Parser_Helper("[ ]") == XLJSON::Value(XLJSON::ValueArray), L"ֵ������Ԥ�� eg2");
			Assert::IsTrue(Parser_Helper("[      \n\t]") == XLJSON::Value(XLJSON::ValueArray), L"ֵ������Ԥ�� eg3");
			Assert::IsTrue(Parser_Helper("[ ][]") == XLJSON::Value(XLJSON::ValueNull), L"ֵ������Ԥ�� eg4 ");
			Assert::IsTrue(Parser_Helper("[ ]]") == XLJSON::Value(XLJSON::ValueNull), L"ֵ������Ԥ�� eg5");
		}

		TEST_METHOD(���Խ����ն���)
		{
			Assert::IsTrue(Parser_Helper("{}") == XLJSON::Value(XLJSON::ValueObject), L"ֵ������Ԥ�� eg1");
			Assert::IsTrue(Parser_Helper("{ }") == XLJSON::Value(XLJSON::ValueObject), L"ֵ������Ԥ�� eg2");
			Assert::IsTrue(Parser_Helper("{  }}") == XLJSON::Value(XLJSON::ValueNull), L"ֵ������Ԥ�� eg3");
			Assert::IsTrue(Parser_Helper("{  }{}") == XLJSON::Value(XLJSON::ValueNull), L"ֵ������Ԥ�� eg4");
		}

		TEST_METHOD(���Խ�����������ֵ)
		{
			std::string str = R"([123,1231,"123",123])";
			XLJSON::Value val(XLJSON::ValueObject);
			XLJSON::Parse par;
			if (!par.ParseJsonStr(str, val))
			{
				Assert::Fail(L"����JSON�ַ���ʧ��");
			}

			str = val.ToString();
			if(str.empty())
			{
				Assert::Fail(L"����JSON�ַ���ʧ��");
			}

			
		}
	};

	
}
