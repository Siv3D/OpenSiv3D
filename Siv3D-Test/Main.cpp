
# include <Siv3D.hpp>

void Main()
{
	for (const auto& gamepad : System::EnumerateGamepads())
	{
		Print << gamepad.index;
		Print << gamepad.name;
	}

	while (System::Update())
	{
		const JoyCon joyConL = JoyCon::JoyConL(0);
		const JoyCon joyConR = JoyCon::JoyConR(0);

		ClearPrint();
		Print << joyConL.button0.pressed();
		Print << joyConR.button0.pressed();

		Print << joyConL.button1.pressed();
		Print << joyConR.button1.pressed();

		Print << joyConL.button2.pressed();
		Print << joyConR.button2.pressed();

		Print << joyConL.button3.pressed();
		Print << joyConR.button3.pressed();
	}
}
