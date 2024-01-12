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
		Logger::WriteMessage(L"解析JSON字符串失败了 ");
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
		
		TEST_METHOD(测试解析BOOL和NULL类型值)
		{
			Assert::IsTrue(Parser_Helper("false") ==XLJSON::Value(false), L"值不符合预期eg1");
			Assert::IsTrue(Parser_Helper("true") == XLJSON::Value(true), L"值不符合预期eg2");
			Assert::IsTrue(Parser_Helper("null") == XLJSON::Value(), L"值不符合预期eg3");

			Assert::IsTrue(!Parser_Helper2("falsefalse") , L"值不符合预期eg4");
			Assert::IsTrue(!Parser_Helper2("false  false") , L"值不符合预期eg5");
			Assert::IsTrue(!Parser_Helper2("truetrue") , L"值不符合预期eg6");
			Assert::IsTrue(!Parser_Helper2("true true"), L"值不符合预期eg7");
			Assert::IsTrue(!Parser_Helper2("nullnull") , L"值不符合预期eg8");
			Assert::IsTrue(!Parser_Helper2("null null") , L"值不符合预期eg9");
		};

		TEST_METHOD(测试解析空数组)
		{
			Assert::IsTrue(Parser_Helper("[]") == XLJSON::Value(XLJSON::ValueArray), L"值不符合预期 eg1");
			Assert::IsTrue(Parser_Helper("[ ]") == XLJSON::Value(XLJSON::ValueArray), L"值不符合预期 eg2");
			Assert::IsTrue(Parser_Helper("[      \n\t]") == XLJSON::Value(XLJSON::ValueArray), L"值不符合预期 eg3");
			Assert::IsTrue(Parser_Helper("[ ][]") == XLJSON::Value(XLJSON::ValueNull), L"值不符合预期 eg4 ");
			Assert::IsTrue(Parser_Helper("[ ]]") == XLJSON::Value(XLJSON::ValueNull), L"值不符合预期 eg5");
		}

		TEST_METHOD(测试解析空对象)
		{
			Assert::IsTrue(Parser_Helper("{}") == XLJSON::Value(XLJSON::ValueObject), L"值不符合预期 eg1");
			Assert::IsTrue(Parser_Helper("{ }") == XLJSON::Value(XLJSON::ValueObject), L"值不符合预期 eg2");
			Assert::IsTrue(Parser_Helper("{  }}") == XLJSON::Value(XLJSON::ValueNull), L"值不符合预期 eg3");
			Assert::IsTrue(Parser_Helper("{  }{}") == XLJSON::Value(XLJSON::ValueNull), L"值不符合预期 eg4");
		}

		TEST_METHOD(测试解析数组类型值)
		{
			std::string str = R"([123,1231,"123",123])";
			XLJSON::Value val(XLJSON::ValueObject);
			XLJSON::Parse par;
			if (!par.ParseJsonStr(str, val))
			{
				Assert::Fail(L"解析JSON字符串失败");
			}

			str = val.ToString();
			if(str.empty())
			{
				Assert::Fail(L"解析JSON字符串失败");
			}

			
		}
	};

	
}
