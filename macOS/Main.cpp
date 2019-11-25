
# include <Siv3D.hpp>

void Main()
{
	const Array<SerialPortInfo> infos = System::EnumerateSerialPorts();
	const Array<String> options = infos.map([](const SerialPortInfo& info)
	{
		return U"{} ({})"_fmt(info.port, info.description);
	}) << U"none";

	Serial serial;
	size_t index = (options.size() - 1);

	while (System::Update())
	{
		const bool isOpened = serial.isOpened();

		if (SimpleGUI::Button(U"Write 0", Vec2(100, 20), 120, isOpened))
		{
			serial.writeByte(0);
		}

		if (SimpleGUI::Button(U"Write 1", Vec2(240, 20), 120, isOpened))
		{
			serial.writeByte(1);
		}

		if (SimpleGUI::Button(U"Write 2", Vec2(380, 20), 120, isOpened))
		{
			serial.writeByte(2);
		}

		if (SimpleGUI::RadioButtons(index, options, Vec2(100, 60)))
		{
			ClearPrint();

			if (index == (options.size() - 1))
			{
				serial = Serial();
			}
			else
			{
				Print << U"Open {}"_fmt(infos[index].port);

				if (serial.open(infos[index].port))
				{
					Print << U"Succeeded";
				}
				else
				{
					Print << U"Failed";
				}
			}
		}

		if (const size_t available = serial.available())
		{
			Print << U"READ: " << serial.readBytes();
		}
	}
}
