
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		ClearPrint();

		for (size_t i = 0; i < Gamepad.MaxUserCount; ++i)
		{
			if (ProController::IsProController(Gamepad(i)))
			{
				const ProController pro(Gamepad(i));

				for (size_t b = 0; b < Gamepad(i).buttons.size(); ++b)
				{
					if (Gamepad(i).buttons[b].pressed())
					{
						Print << b;
					}
				}

				Print << Gamepad(i).axes.size();
				Print << pro.povUp.pressed();
				Print << pro.povDown.pressed();
				Print << pro.povLeft.pressed();
				Print << pro.povRight.pressed();

				Print << pro.povD8();
				Print << pro.LStick();
				Print << pro.RStick();
			}
		}
	}
}
