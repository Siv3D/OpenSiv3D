
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

void Main()
{
	JSONWriter json;

	json.startObject();
	{
		json.key(U"Window").startObject();
		{
			json.key(U"title").write(U"My application");
			json.key(U"width").write(800);
			json.key(U"height").write(600);
			json.key(U"sizable").write(false);
		}
		json.endObject();

		json.key(U"Scene").startObject();
		{
			json.key(U"background").write(ColorF(0.8, 0.9, 1.0));
		}
		json.endObject();

		json.key(U"Array").startObject();
		{
			json.key(U"values").writeArray({ 11, 22, 33, 44, 55 });
		}
		json.endObject();

		json.key(U"Items").startArray();
		{
			json.startObject();
			{
				json.key(U"label").write(U"Forest");

				json.key(U"pos").startObject();
				{
					json.key(U"x").write(100);
					json.key(U"y").write(100);
				}
				json.endObject();
			}
			json.endObject();

			json.startObject();
			{
				json.key(U"label").write(U"Ocean");

				json.key(U"pos").startObject();
				{
					json.key(U"x").write(300);
					json.key(U"y").write(200);
				}
				json.endObject();
			}
			json.endObject();

			json.startObject();
			{
				json.key(U"label").write(U"Mountain");

				json.key(U"pos").startObject();
				{
					json.key(U"x").write(500);
					json.key(U"y").write(100);
				}
				json.endObject();
			}
			json.endObject();
		}
		json.endArray();
	}
	json.endObject();

	json.save(U"test.json");

	while (System::Update())
	{

	}
}
