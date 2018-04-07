# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	const Texture texture1(Icon(0xf441, 40));

	const Texture texture2(Icon(0xf099, 40));

	const Texture texture3(Icon(0xf1ec, 40));

	while (System::Update())
	{
		texture1.drawAt(200, 240);

		texture2.drawAt(300, 240);

		texture3.drawAt(400, 240);
	}
}
