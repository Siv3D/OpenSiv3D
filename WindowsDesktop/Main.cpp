#include <Siv3D.hpp>

void Main()
{
	JSON bad_person = UR"({
    "name": "Albert",
    "age": 42,
    "object": {}
})"_json;

	JSON good_person = UR"({
    "name": "Albert",
    "age": 42,
    "object": {
        "string": "string"
    }
})"_json;

	JSONValidator schema = UR"({
    "title": "A person",
    "properties": {
        "name": {
            "description": "Name",
            "type": "string"
        },
        "age": {
            "description": "Age of the person",
            "type": "number",
            "minimum": 2,
            "maximum": 200
        },
        "object": {
            "type": "object",
            "properties": {
                "string": {
                    "type": "string"
                }
            },
            "required": [
                "string"
            ]
        }
    },
    "required": [
        "name",
        "age",
        "object"
    ],
    "type": "object"
})"_jsonValidator;

	Console << U"\n[Test 1]";

	for (auto& person : {bad_person, good_person})
	{
		Console << U"---";

		if (schema.validate(person))
		{
			Console << U"OK";
		}
		else
		{
			Console << U"NG";
		}
	}

	Console << U"---\n[Test 2]";

	for (auto& person : {bad_person, good_person})
	{
		JSONValidator::ValidationError err;

		Console << U"---";

		if (schema.validate(person, err))
		{
			Console << U"OK";
			Console << err.isOK();
		}
		else
		{
			Console << U"NG";
			Console << err.isOK();
			Console << err;
		}
	}

	Console << U"---\n[Test 3]";

	for (auto& person : {bad_person, good_person})
	{
		Console << U"---";

		try
		{
			schema.validationAssert(person);
			Console << U"OK";
		}
		catch (const JSONValidator::ValidationError& err)
		{
			Console << U"NG";
			Console << err;
		}
	}

	Console << U"---";

	const auto json = UR"({
	"aa~/a" : {
		"b" : [5, 6, 7, 8, 9]
	}
})"_json;

	JSONPointer pointer;

	// ~ や / がキーに含まれる場合も問題なく扱える
	pointer /= U"aa~/a";

	Print << pointer;

	// 型レベルの識別をすることで、operator[] のオーバーロードが可
	Print << json[pointer];

	// 従来の String による json pointer でも出来ない訳では無いが
	// ネストしたプロパティへのアクセスが楽に
	Print << json[pointer / U"/b/1"_jsonPointer];

	while (System::Update())
	{
	}
}
