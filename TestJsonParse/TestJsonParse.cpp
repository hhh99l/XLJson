#include "pch.h"
#include "CppUnitTest.h"
#include "../MyJson/JsonParse.h"
#include "../MyJson/JsonValue.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestJsonParse
{
	TEST_CLASS(TestJsonParse)
	{
	public:
		
		TEST_METHOD(���Խ���BOOL����ֵ)
		{
			std::string str = R"({"value1":false, "value2":true})";
			XLJSON::Value val(XLJSON::ValueObject);
			XLJSON::Parse par;
			if (!par.ParseJsonStr(str, val))
			{
				Assert::Fail(L"����JSON�ַ���ʧ��");
			}

			Assert::AreEqual(val["value1"].AsBool(), false, L"BOOLֵ������Ԥ��");
			Assert::AreEqual(val["value2"].AsBool(), true, L"BOOLֵ������Ԥ��");

			// �����쳣��JSON����������
			str = R"({"value1":fal})";
			if (par.ParseJsonStr(str, val))
			{
				Assert::Fail(L"����JSON�ַ����쳣");
			}

			str = R"({"value1":falsee})";
			if (par.ParseJsonStr(str, val))
			{
				Assert::Fail(L"����JSON�ַ����쳣");
			}

			str = R"({"value1":false e})";
			if (par.ParseJsonStr(str, val))
			{
				Assert::Fail(L"����JSON�ַ����쳣");
			}

			str = R"({"value1":false,})";
			if (par.ParseJsonStr(str, val))
			{
				Assert::Fail(L"����JSON�ַ����쳣");
			}

			str = R"({value1:false})";
			if (par.ParseJsonStr(str, val))
			{
				Assert::Fail(L"����JSON�ַ����쳣");
			}

		};

		TEST_METHOD(���Խ�����������ֵ)
		{
			std::string str = R"({"i1":-1234, "i2":-1234156, "i3":-1234523,
								"u1":123123123123131231234, "u2":123456, "u3":1234523
								
								
			})";
			XLJSON::Value val(XLJSON::ValueObject);
			XLJSON::Parse par;
			if (!par.ParseJsonStr(str, val))
			{
				Assert::Fail(L"����JSON�ַ���ʧ��");
			}

			Assert::IsTrue(val["i1"].AsInt() == -1234, L"i1ֵ������Ԥ��");
			Assert::IsTrue(val["i2"].AsInt() ==-123456, L"i2ֵ������Ԥ��");
			Assert::IsTrue(val["i3"].AsInt() == -1234523, L"i3ֵ������Ԥ��");

			Assert::IsTrue(val["u1"].AsUint() == 1234, L"u1ֵ������Ԥ��");
			Assert::IsTrue(val["u2"].AsUint() == 123456, L"u2ֵ������Ԥ��");
			Assert::IsTrue(val["u3"].AsUint() == 1234523, L"u3ֵ������Ԥ��");
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
