# include <Siv3D.hpp>

struct Widget
{
	String title;
	Rect rect;
	ColorF color;
	Array<int32> values;

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(title, rect, color, values);
	}
};

void Main()
{
	{
		Serializer<BinaryWriter> writer(U"serialize-test.bin");
		const Widget w = { U"Siv3D App", Rect(100, 100, 200, 400), ColorF(0.3, 0.6, 1.0),{ 11,22,33,44 } };
		writer(w);
	}
	{
		Deserializer<BinaryReader> reader(U"serialize-test.bin");
		Widget w;
		reader(w);	
		Print << w.title;
		Print << w.rect;
		Print << w.color;
		Print << w.values;
	}

	while (System::Update())
	{

	}
}
