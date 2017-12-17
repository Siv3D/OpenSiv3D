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
		Mat3x2 value = Mat3x2::Identity();
		Print << value;
		writer(value);
	}
	{
		Deserializer<BinaryReader> reader(U"serialize-test.bin");
		Mat3x2 value;
		reader(value);
		Print << value;
	}

	while (System::Update())
	{

	}
}
