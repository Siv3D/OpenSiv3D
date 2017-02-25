
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (Mouse::Wheel())
		{
			Log << L"V: " << Mouse::Wheel();
		}

		if (Mouse::WheelH())
		{
			Log << L"H: " << Mouse::WheelH();
		}
	}
}
