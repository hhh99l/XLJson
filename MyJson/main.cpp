#include"JsonValue.h"
#include "JsonParse.h"
#include <iostream>

int main()
{
	XLJSON::Value val(XLJSON::ValueObject);
	std::string str1 = "{\"value1\":\"123\",\"value2\":\"123\" , \"value3\":{\"value1\":\"123\",\"value2\":\"123\" }}";
	XLJSON::Parse par;
	par.ParseJsonStr(str1, val);


	return 0;
}