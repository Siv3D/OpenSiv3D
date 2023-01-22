#include <Siv3D.hpp>

void Main()
{
	JSON bad_person = JSON::Parse(UR"({
    "name": "Albert",
    "age": 42,
    "object": {}
})");

	JSON good_person = JSON::Parse(UR"({
    "name": "Albert",
    "age": 42,
    "object": {
        "string": "string"
    }
})");

	JSONSchema schema = JSONSchema::Parse(UR"({
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
})");

	Print << U"\n[Test 1]";

	for (auto& person : { bad_person, good_person })
	{
		Print << U"---";

		if (schema.validate(person))
		{
			Print << U"OK";
		}
		else
		{
			Print << U"NG";
		}
	}

	Print << U"\n[Test 2]";

	for (auto& person : { bad_person, good_person })
	{
		JSONSchema::ValidationStatus err;

		Print << U"---";

		if (schema.validate(person, err))
		{
			Print << U"OK";
			Print << err.isOK();
		}
		else
		{
			Print << U"NG";
			Print << err.isOK();
			Print << err.message();
			Print << U"pointer: " << err.pointer();
			Console << err.instance();
		}
	}

	Print << U"\n[Test 3]";

	for (auto& person : { bad_person, good_person })
	{
		Print << U"---";

		try
		{
			schema.validationAssert(person);
			Print << U"OK";
		}
		catch (const JSONSchema::ValidationError& err)
		{
			Print << U"NG";
			Print << err;
		}
	}

	while (System::Update())
	{
	}
}
