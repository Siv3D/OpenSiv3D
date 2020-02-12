
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	// シリアルポートの一覧を取得
	const Array<SerialPortInfo> infos = System::EnumerateSerialPorts();
	const Array<String> options = infos.map([](const SerialPortInfo& info)
		{
			return U"{} ({})"_fmt(info.port, info.description);
		}) << U"none";

	Serial serial;
	size_t index = (options.size() - 1);

	while (System::Update())
	{
		MicrosecClock ms;
		const bool isOpen = serial.isOpen();
		ms.print();
		Window::SetTitle(isOpen);
		
		//if (SimpleGUI::Button(U"Write 0", Vec2(200, 20), 120, isOpen))
		//{
		//	// 1 バイトのデータ (0) を書き込む
		//	serial.writeByte(0);
		//}

		//if (SimpleGUI::Button(U"Write 1", Vec2(340, 20), 120, isOpen))
		//{
		//	// 1 バイトのデータ (1) を書き込む
		//	serial.writeByte(1);
		//}

		//if (SimpleGUI::Button(U"Write 2", Vec2(480, 20), 120, isOpen))
		//{
		//	// 1 バイトのデータ (2) を書き込む
		//	serial.writeByte(2);
		//}

		if (SimpleGUI::RadioButtons(index, options, Vec2(200, 60)))
		{
			//ClearPrint();

			if (index == (options.size() - 1))
			{
				serial = Serial();
			}
			else
			{
				Print << U"Open {}"_fmt(infos[index].port);

				// シリアルポートをオープン
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

		//if (const size_t available = serial.available())
		//{
		//	// シリアル通信で受信したデータを読み込んで表示
		//	Print << U"READ: " << serial.readBytes();
		//}
	}
}
