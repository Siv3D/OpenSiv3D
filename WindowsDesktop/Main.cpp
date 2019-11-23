
# include <Siv3D.hpp>
# include <serial/serial.h>

namespace s3d
{
	class Serial
	{
	private:

		serial::Serial m_serial;

		String m_port;

		int32 m_baudrate = 0;

	public:

		Serial() = default;

		explicit Serial(const String& port, int32 baudrate = 9600)
			: m_serial(port.narrow(), static_cast<uint32>(baudrate))
			, m_port(port)
			, m_baudrate(baudrate)
		{

		}

		bool open(const String& port, int32 baudrate = 9600)
		{
			if (isOpened())
			{
				close();
			}

			m_serial.setPort(port.narrow());
			m_serial.setBaudrate(static_cast<uint32>(baudrate));
			m_serial.open();
			m_port = port;
			m_baudrate = baudrate;
			return m_serial.isOpen();
		}

		void close()
		{
			m_serial.close();
			m_port.clear();
			m_baudrate = 0;
		}

		[[nodiscard]] bool isOpened() const
		{
			return m_serial.isOpen();
		}

		[[nodiscard]] explicit operator bool() const
		{
			return isOpened();
		}

		[[nodiscard]] int32 baudrate() const
		{
			return m_baudrate;
		}

		[[nodiscard]] const String& port() const
		{
			return m_port;
		}

		[[nodiscard]] size_t available()
		{
			return m_serial.available();
		}

		void clearInput()
		{
			m_serial.flushInput();
		}

		void clearOutput()
		{
			m_serial.flushOutput();
		}

		void clear()
		{
			m_serial.flush();
		}

		size_t read(void* dst, size_t size)
		{
			return m_serial.read(static_cast<uint8*>(dst), size);
		}

		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		bool read(Type& to)
		{
			return read(std::addressof(to), sizeof(Type)) == sizeof(Type);
		}

		size_t write(const void* src, size_t size)
		{
			return m_serial.write(static_cast<const uint8*>(src), size);
		}

		bool writeByte(uint8 byte)
		{
			return write(byte);
		}

		bool writeByte(Byte byte)
		{
			return write(byte);
		}

		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		bool write(const Type& from)
		{
			return (write(std::addressof(from), sizeof(Type))) == sizeof(Type);
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
	Print << serial.isOpened();

	while (System::Update())
	{
		ClearPrint();
		//Print << serial.available();

		if (SimpleGUI::Button(U"LED 点灯", Vec2(20, 20)))
		{
			serial.writeByte(49);
		}

		if (SimpleGUI::Button(U"LED 消灯", Vec2(20, 60)))
		{
			serial.writeByte(48);
		}
	}
}
