#include "pch.h"
#include "CppUnitTest.h"
#include "../MyJson/JsonParse.h"
#include "../MyJson/JsonValue.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


XLJSON::Value Parser_Helper(const std::string& str)
{
	try
	{
		XLJSON::Value value;
		XLJSON::Parse par;
		if (!par.ParseJsonStr(str, value))
		{
			Logger::WriteMessage(L"解析JSON字符串失败了 ");
			Logger::WriteMessage(str.c_str());
			Logger::WriteMessage("\n");
			return XLJSON::Value();
		}
		return value;
	}
	catch (const std::exception&)
	{
		Assert::Fail(L"抛异常了");
		return XLJSON::Value();
	}
	
}

bool Parser_Helper2(const std::string& str)
{
	try
	{
		XLJSON::Value value;
		XLJSON::Parse par;
		if (!par.ParseJsonStr(str, value))
		{
			return false;
		}
		return true;;
	}
	catch (const std::exception&)
	{
		Assert::Fail(L"抛异常了");
		return false;
	}
}


namespace TestJsonParse
{
	TEST_CLASS(TestJson_SimpleParse)
	{
	public:
		TEST_METHOD(BOOLandNull)
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

		TEST_METHOD(Array)
		{
			Assert::IsTrue(Parser_Helper("[]") == XLJSON::Value(XLJSON::ValueArray), L"值不符合预期 eg1");
			Assert::IsTrue(Parser_Helper("[ ]") == XLJSON::Value(XLJSON::ValueArray), L"值不符合预期 eg2");
			Assert::IsTrue(Parser_Helper("[      \n\t]") == XLJSON::Value(XLJSON::ValueArray), L"值不符合预期 eg3");
			Assert::IsTrue(Parser_Helper("[      \n\t]\n\t\r ") == XLJSON::Value(XLJSON::ValueArray), L"值不符合预期 eg4");

			Assert::IsTrue(!Parser_Helper2("[ ][]"), L"值不符合预期 eg5 ");
			Assert::IsTrue(!Parser_Helper2("[ ]]]  "), L"值不符合预期 eg6");

			Assert::IsTrue(Parser_Helper("[true, false, null]") == XLJSON::Value{ true, false ,XLJSON::ValueNull}, L"值不符合预期 eg7");
		}

		TEST_METHOD(Object)
		{
			Assert::IsTrue(Parser_Helper("{}") == XLJSON::Value(XLJSON::ValueObject), L"值不符合预期 eg1");
			Assert::IsTrue(Parser_Helper("{ }") == XLJSON::Value(XLJSON::ValueObject), L"值不符合预期 eg2");
			Assert::IsTrue(Parser_Helper("{ }\r\n\t    ") == XLJSON::Value(XLJSON::ValueObject), L"值不符合预期 eg3");

			Assert::IsTrue(Parser_Helper("{  }}") == XLJSON::Value(XLJSON::ValueNull), L"值不符合预期 eg4");
			Assert::IsTrue(Parser_Helper("{  }{}") == XLJSON::Value(XLJSON::ValueNull), L"值不符合预期 eg5");

		}

		TEST_METHOD(number)
		{
			Assert::IsTrue(Parser_Helper("-128") == XLJSON::Value(-128), L"值不符合预期 eg1");
			Assert::IsTrue(Parser_Helper("-0") == XLJSON::Value(-0), L"值不符合预期 eg2");
			Assert::IsTrue(Parser_Helper("0") == XLJSON::Value(0u), L"值不符合预期 eg3");
			Assert::IsTrue(Parser_Helper("128") == XLJSON::Value(128u), L"值不符合预期 eg4");

			// 指数
			Assert::IsTrue(Parser_Helper("0e1") == XLJSON::Value(0e1), L"值不符合预期 eg5");
			Assert::IsTrue(Parser_Helper("0E1") == XLJSON::Value(0E1), L"值不符合预期 eg6");

			Assert::IsTrue(Parser_Helper("10000E-4") == XLJSON::Value(10000E-4), L"值不符合预期 eg7");
			Assert::IsTrue(Parser_Helper("10000E-3") == XLJSON::Value(10000E-3), L"值不符合预期 eg8");
			Assert::IsTrue(Parser_Helper("10000E-2") == XLJSON::Value(10000E-2), L"值不符合预期 eg9");
			Assert::IsTrue(Parser_Helper("10000E-1") == XLJSON::Value(10000E-1), L"值不符合预期 eg10");
			Assert::IsTrue(Parser_Helper("10000E-0") == XLJSON::Value(10000E-0), L"值不符合预期 eg11");
			Assert::IsTrue(Parser_Helper("10000E1") == XLJSON::Value(10000E1), L"值不符合预期 eg12");
			Assert::IsTrue(Parser_Helper("10000E2") == XLJSON::Value(10000E2), L"值不符合预期 eg13");
			Assert::IsTrue(Parser_Helper("10000E3") == XLJSON::Value(10000E3), L"值不符合预期 eg14");
			Assert::IsTrue(Parser_Helper("10000E4") == XLJSON::Value(10000E4), L"值不符合预期 eg15");

			Assert::IsTrue(Parser_Helper("10000e-4") == XLJSON::Value(10000e-4), L"值不符合预期 eg16");
			Assert::IsTrue(Parser_Helper("10000e-3") == XLJSON::Value(10000e-3), L"值不符合预期 eg17");
			Assert::IsTrue(Parser_Helper("10000e-2") == XLJSON::Value(10000e-2), L"值不符合预期 eg18");
			Assert::IsTrue(Parser_Helper("10000e-1") == XLJSON::Value(10000e-1), L"值不符合预期 eg19");
			Assert::IsTrue(Parser_Helper("10000e-0") == XLJSON::Value(10000e-0), L"值不符合预期 eg20");
			Assert::IsTrue(Parser_Helper("10000e1") == XLJSON::Value(10000e1), L"值不符合预期 eg21");
			Assert::IsTrue(Parser_Helper("10000e2") == XLJSON::Value(10000e2), L"值不符合预期 eg22");
			Assert::IsTrue(Parser_Helper("10000e3") == XLJSON::Value(10000e3), L"值不符合预期 eg23");
			Assert::IsTrue(Parser_Helper("10000e4") == XLJSON::Value(10000e4), L"值不符合预期 eg24");

			Assert::IsTrue(Parser_Helper("-0e1") == XLJSON::Value(-0e1), L"值不符合预期 eg25");
			Assert::IsTrue(Parser_Helper("-0E1") == XLJSON::Value(-0E1), L"值不符合预期 eg26");
			Assert::IsTrue(Parser_Helper("-0e123") == XLJSON::Value(-0e123), L"值不符合预期 eg27");

			Assert::IsTrue(Parser_Helper("12e0") == XLJSON::Value(12e0), L"值不符合预期 eg28");
			Assert::IsTrue(Parser_Helper("12e1") == XLJSON::Value(12e1), L"值不符合预期 eg29");
			Assert::IsTrue(Parser_Helper("12e2") == XLJSON::Value(12e2), L"值不符合预期 eg30");
			Assert::IsTrue(Parser_Helper("12e3") == XLJSON::Value(12e3), L"值不符合预期 eg31");
			Assert::IsTrue(Parser_Helper("12e4") == XLJSON::Value(12e4), L"值不符合预期 eg32");
			Assert::IsTrue(Parser_Helper("12e5") == XLJSON::Value(12e5), L"值不符合预期 eg33");
			Assert::IsTrue(Parser_Helper("12e-0") == XLJSON::Value(12e-0), L"值不符合预期 eg34");
			Assert::IsTrue(Parser_Helper("12e-1") == XLJSON::Value(12e-1), L"值不符合预期 eg35");
			Assert::IsTrue(Parser_Helper("12e-2") == XLJSON::Value(12e-2), L"值不符合预期 eg36");
			Assert::IsTrue(Parser_Helper("12e-3") == XLJSON::Value(12e-3), L"值不符合预期 eg37");
			Assert::IsTrue(Parser_Helper("12e-4") == XLJSON::Value(12e-4), L"值不符合预期 eg38");
			Assert::IsTrue(Parser_Helper("12e-5") == XLJSON::Value(12e-5), L"值不符合预期 eg39");
			Assert::IsTrue(Parser_Helper("12e-6") == XLJSON::Value(12e-6), L"值不符合预期 eg40");
			Assert::IsTrue(Parser_Helper("12e-7") == XLJSON::Value(12e-7), L"值不符合预期 eg41");
			Assert::IsTrue(Parser_Helper("12e-8") == XLJSON::Value(12e-8), L"值不符合预期 eg42");

		}
	};

	
}
