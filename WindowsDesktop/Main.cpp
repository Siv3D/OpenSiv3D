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

	Console << U"\n[Test 2]";

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

	Console << U"\n[Test 3]";

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

#define JSONINIT UR"({"a~/a": {"b": [5, 6, 7, 8, 9]}})"_json;

	auto json = JSONINIT;

	const auto f = []<class T>(T& json) {
		// デフォルトコンストラクタは JSON 全体を指すパス（空文字列）
		JSONPointer pointer;
		Print << json[pointer];

		// ~ や / がキーに含まれる場合、エスケープしていないキーを
		//  operator/
		//  operator/=
		//  push_back
		// でキー単位で追加することが可能
		Print << json[pointer / U"a~/a"];

		// 型レベルの識別をすることで、operator[] のオーバーロードが可
		//  operator[](const JSONPointer&) JSONPointer でアクセス
		//  operator[](StringView)         JSON キーでアクセス（エスケープ不要）
		//  operator[](size_t)             インデックスでアクセス
		// 注: JSONPointer コンストラクタは JSON Pointer（エスケープ）が必要
		Print << json[U"/a~0~1a"_jsonPtr][U"b"][0];

		// ネストしたプロパティへのアクセスが楽に
		Print << json[U"/a~0~1a/b/0"_jsonPtr];

		if constexpr (std::same_as<T, JSON>)
		{
			// 書き換えテスト
			json[pointer]          = UR"({"c": [5, 6, 7, 8, 9]})"_json;
			json[pointer][U"c"]    = UR"([10, 11, 12, 13, 14])"_json;
			json[pointer][U"c"][5] = 15;

			Print << json;

			json = JSONINIT;
		}
	};

	// JSON&
	f(json);

	// const JSON&
	f(std::as_const(json));

	while (System::Update())
	{
	}
}
