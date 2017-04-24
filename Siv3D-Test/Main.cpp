# include <Siv3D.hpp>

void Main()
{
	Timer timer{ 60s };

	while (System::Update())
	{
		if (MouseL.down())
		{
			timer.start();
		}

		Window::SetTitle(timer, L" @ ", timer.progress0_1());
	}
}