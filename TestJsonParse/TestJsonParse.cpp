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
		
		TEST_METHOD(测试解析BOOL类型值)
		{
			std::string str = R"({"value1":false, "value2":true})";
			XLJSON::Value val(XLJSON::ValueObject);
			XLJSON::Parse par;
			if (!par.ParseJsonStr(str, val))
			{
				Assert::Fail(L"解析JSON字符串失败");
			}

			Assert::AreEqual(val["value1"].AsBool(), false, L"BOOL值不符合预期");
			Assert::AreEqual(val["value2"].AsBool(), true, L"BOOL值不符合预期");

			// 整点异常的JSON串加载试试
			str = R"({"value1":fal})";
			if (par.ParseJsonStr(str, val))
			{
				Assert::Fail(L"解析JSON字符串异常");
			}

			str = R"({"value1":falsee})";
			if (par.ParseJsonStr(str, val))
			{
				Assert::Fail(L"解析JSON字符串异常");
			}

			str = R"({"value1":false e})";
			if (par.ParseJsonStr(str, val))
			{
				Assert::Fail(L"解析JSON字符串异常");
			}

			str = R"({"value1":false,})";
			if (par.ParseJsonStr(str, val))
			{
				Assert::Fail(L"解析JSON字符串异常");
			}

			str = R"({value1:false})";
			if (par.ParseJsonStr(str, val))
			{
				Assert::Fail(L"解析JSON字符串异常");
			}

		};

		TEST_METHOD(测试解析整数类型值)
		{
			std::string str = R"({"i1":-1234, "i2":-1234156, "i3":-1234523,
								"u1":123123123123131231234, "u2":123456, "u3":1234523
								
								
			})";
			XLJSON::Value val(XLJSON::ValueObject);
			XLJSON::Parse par;
			if (!par.ParseJsonStr(str, val))
			{
				Assert::Fail(L"解析JSON字符串失败");
			}

			Assert::IsTrue(val["i1"].AsInt() == -1234, L"i1值不符合预期");
			Assert::IsTrue(val["i2"].AsInt() ==-123456, L"i2值不符合预期");
			Assert::IsTrue(val["i3"].AsInt() == -1234523, L"i3值不符合预期");

			Assert::IsTrue(val["u1"].AsUint() == 1234, L"u1值不符合预期");
			Assert::IsTrue(val["u2"].AsUint() == 123456, L"u2值不符合预期");
			Assert::IsTrue(val["u3"].AsUint() == 1234523, L"u3值不符合预期");
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
