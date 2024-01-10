#include"JsonValue.h"
#include "JsonParse.h"
#include <iostream>

int main()
{
	XLJSON::Value val(XLJSON::ValueObject);
	std::string str1 = "{\"value1\":10211, \"value2\":3.1415926, \"value3\":-10211.1, \"value4\":-3.1415926}";
	XLJSON::Parse par;
	par.ParseJsonStr(str1, val);
	std::string str;
	str = val.ToString();

	return 0;
}