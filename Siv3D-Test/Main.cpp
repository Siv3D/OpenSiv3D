
# include <Siv3D.hpp>

struct Widget
{
	int32 n = 0;

	int32 b = 255;
};

void Main()
{
	Widget widget;

	Console << ByteArrayView(widget).toHex();

	while (System::Update())
	{
		
	}
}
