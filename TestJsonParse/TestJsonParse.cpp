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
			Logger::WriteMessage(L"����JSON�ַ���ʧ���� ");
			Logger::WriteMessage(str.c_str());
			Logger::WriteMessage("\n");
			return XLJSON::Value();
		}
		return value;
	}
	catch (const std::exception&)
	{
		Assert::Fail(L"���쳣��");
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
		Assert::Fail(L"���쳣��");
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

		TEST_METHOD(Array)
		{
			Assert::IsTrue(Parser_Helper("[]") == XLJSON::Value(XLJSON::ValueArray), L"ֵ������Ԥ�� eg1");
			Assert::IsTrue(Parser_Helper("[ ]") == XLJSON::Value(XLJSON::ValueArray), L"ֵ������Ԥ�� eg2");
			Assert::IsTrue(Parser_Helper("[      \n\t]") == XLJSON::Value(XLJSON::ValueArray), L"ֵ������Ԥ�� eg3");
			Assert::IsTrue(Parser_Helper("[      \n\t]\n\t\r ") == XLJSON::Value(XLJSON::ValueArray), L"ֵ������Ԥ�� eg4");

			Assert::IsTrue(!Parser_Helper2("[ ][]"), L"ֵ������Ԥ�� eg5 ");
			Assert::IsTrue(!Parser_Helper2("[ ]]]  "), L"ֵ������Ԥ�� eg6");

			Assert::IsTrue(Parser_Helper("[true, false, null]") == XLJSON::Value{ true, false ,XLJSON::ValueNull}, L"ֵ������Ԥ�� eg7");
		}

		TEST_METHOD(Object)
		{
			Assert::IsTrue(Parser_Helper("{}") == XLJSON::Value(XLJSON::ValueObject), L"ֵ������Ԥ�� eg1");
			Assert::IsTrue(Parser_Helper("{ }") == XLJSON::Value(XLJSON::ValueObject), L"ֵ������Ԥ�� eg2");
			Assert::IsTrue(Parser_Helper("{ }\r\n\t    ") == XLJSON::Value(XLJSON::ValueObject), L"ֵ������Ԥ�� eg3");

			Assert::IsTrue(Parser_Helper("{  }}") == XLJSON::Value(XLJSON::ValueNull), L"ֵ������Ԥ�� eg4");
			Assert::IsTrue(Parser_Helper("{  }{}") == XLJSON::Value(XLJSON::ValueNull), L"ֵ������Ԥ�� eg5");

		}

		TEST_METHOD(number)
		{
			Assert::IsTrue(Parser_Helper("-128") == XLJSON::Value(-128), L"ֵ������Ԥ�� eg1");
			Assert::IsTrue(Parser_Helper("-0") == XLJSON::Value(-0), L"ֵ������Ԥ�� eg2");
			Assert::IsTrue(Parser_Helper("0") == XLJSON::Value(0u), L"ֵ������Ԥ�� eg3");
			Assert::IsTrue(Parser_Helper("128") == XLJSON::Value(128u), L"ֵ������Ԥ�� eg4");

			// ָ��
			Assert::IsTrue(Parser_Helper("0e1") == XLJSON::Value(0e1), L"ֵ������Ԥ�� eg5");
			Assert::IsTrue(Parser_Helper("0E1") == XLJSON::Value(0E1), L"ֵ������Ԥ�� eg6");

			Assert::IsTrue(Parser_Helper("10000E-4") == XLJSON::Value(10000E-4), L"ֵ������Ԥ�� eg7");
			Assert::IsTrue(Parser_Helper("10000E-3") == XLJSON::Value(10000E-3), L"ֵ������Ԥ�� eg8");
			Assert::IsTrue(Parser_Helper("10000E-2") == XLJSON::Value(10000E-2), L"ֵ������Ԥ�� eg9");
			Assert::IsTrue(Parser_Helper("10000E-1") == XLJSON::Value(10000E-1), L"ֵ������Ԥ�� eg10");
			Assert::IsTrue(Parser_Helper("10000E-0") == XLJSON::Value(10000E-0), L"ֵ������Ԥ�� eg11");
			Assert::IsTrue(Parser_Helper("10000E1") == XLJSON::Value(10000E1), L"ֵ������Ԥ�� eg12");
			Assert::IsTrue(Parser_Helper("10000E2") == XLJSON::Value(10000E2), L"ֵ������Ԥ�� eg13");
			Assert::IsTrue(Parser_Helper("10000E3") == XLJSON::Value(10000E3), L"ֵ������Ԥ�� eg14");
			Assert::IsTrue(Parser_Helper("10000E4") == XLJSON::Value(10000E4), L"ֵ������Ԥ�� eg15");

			Assert::IsTrue(Parser_Helper("10000e-4") == XLJSON::Value(10000e-4), L"ֵ������Ԥ�� eg16");
			Assert::IsTrue(Parser_Helper("10000e-3") == XLJSON::Value(10000e-3), L"ֵ������Ԥ�� eg17");
			Assert::IsTrue(Parser_Helper("10000e-2") == XLJSON::Value(10000e-2), L"ֵ������Ԥ�� eg18");
			Assert::IsTrue(Parser_Helper("10000e-1") == XLJSON::Value(10000e-1), L"ֵ������Ԥ�� eg19");
			Assert::IsTrue(Parser_Helper("10000e-0") == XLJSON::Value(10000e-0), L"ֵ������Ԥ�� eg20");
			Assert::IsTrue(Parser_Helper("10000e1") == XLJSON::Value(10000e1), L"ֵ������Ԥ�� eg21");
			Assert::IsTrue(Parser_Helper("10000e2") == XLJSON::Value(10000e2), L"ֵ������Ԥ�� eg22");
			Assert::IsTrue(Parser_Helper("10000e3") == XLJSON::Value(10000e3), L"ֵ������Ԥ�� eg23");
			Assert::IsTrue(Parser_Helper("10000e4") == XLJSON::Value(10000e4), L"ֵ������Ԥ�� eg24");

			Assert::IsTrue(Parser_Helper("-0e1") == XLJSON::Value(-0e1), L"ֵ������Ԥ�� eg25");
			Assert::IsTrue(Parser_Helper("-0E1") == XLJSON::Value(-0E1), L"ֵ������Ԥ�� eg26");
			Assert::IsTrue(Parser_Helper("-0e123") == XLJSON::Value(-0e123), L"ֵ������Ԥ�� eg27");

			Assert::IsTrue(Parser_Helper("12e0") == XLJSON::Value(12e0), L"ֵ������Ԥ�� eg28");
			Assert::IsTrue(Parser_Helper("12e1") == XLJSON::Value(12e1), L"ֵ������Ԥ�� eg29");
			Assert::IsTrue(Parser_Helper("12e2") == XLJSON::Value(12e2), L"ֵ������Ԥ�� eg30");
			Assert::IsTrue(Parser_Helper("12e3") == XLJSON::Value(12e3), L"ֵ������Ԥ�� eg31");
			Assert::IsTrue(Parser_Helper("12e4") == XLJSON::Value(12e4), L"ֵ������Ԥ�� eg32");
			Assert::IsTrue(Parser_Helper("12e5") == XLJSON::Value(12e5), L"ֵ������Ԥ�� eg33");
			Assert::IsTrue(Parser_Helper("12e-0") == XLJSON::Value(12e-0), L"ֵ������Ԥ�� eg34");
			Assert::IsTrue(Parser_Helper("12e-1") == XLJSON::Value(12e-1), L"ֵ������Ԥ�� eg35");
			Assert::IsTrue(Parser_Helper("12e-2") == XLJSON::Value(12e-2), L"ֵ������Ԥ�� eg36");
			Assert::IsTrue(Parser_Helper("12e-3") == XLJSON::Value(12e-3), L"ֵ������Ԥ�� eg37");
			Assert::IsTrue(Parser_Helper("12e-4") == XLJSON::Value(12e-4), L"ֵ������Ԥ�� eg38");
			Assert::IsTrue(Parser_Helper("12e-5") == XLJSON::Value(12e-5), L"ֵ������Ԥ�� eg39");
			Assert::IsTrue(Parser_Helper("12e-6") == XLJSON::Value(12e-6), L"ֵ������Ԥ�� eg40");
			Assert::IsTrue(Parser_Helper("12e-7") == XLJSON::Value(12e-7), L"ֵ������Ԥ�� eg41");
			Assert::IsTrue(Parser_Helper("12e-8") == XLJSON::Value(12e-8), L"ֵ������Ԥ�� eg42");

		}
	};

	
}
