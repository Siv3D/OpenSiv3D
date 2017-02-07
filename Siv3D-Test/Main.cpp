
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		Log << Point(Mouse::Wheel(), Mouse::WheelH());
	}
}
