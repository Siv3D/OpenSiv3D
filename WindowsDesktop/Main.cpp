
# include <Siv3D.hpp>
# include <serial/serial.h>

namespace s3d
{
	class Serial
	{
	private:

		serial::Serial m_serial;

	public:

		Serial() = default;

		explicit Serial(const String& port, uint32 baudrate = 9600)
			: m_serial(port.narrow(), baudrate)
		{

		}

		bool isConnected() const
		{
			return m_serial.isOpen();
		}

		size_t available()
		{
			return m_serial.available();
		}

		void write(uint8 byte)
		{
			m_serial.write(&byte, 1);
		}
	};
}

void Main()
{
	String port;

	for (const auto& info : System::EnumerateSerialPorts())
	{
		Print << info.port;
		Print << info.description;
		Print << info.hardwareID;

		port = info.port;
		break;
	}

	Serial serial(port);
	Print << serial.isConnected();

	while (System::Update())
	{
		ClearPrint();
		//Print << serial.available();

		if (SimpleGUI::Button(U"LED 点灯", Vec2(20, 20)))
		{
			serial.write(49);
		}

		if (SimpleGUI::Button(U"LED 消灯", Vec2(20, 60)))
		{
			serial.write(48);
		}
	}
}
