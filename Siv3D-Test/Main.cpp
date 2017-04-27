#include <Siv3D.hpp>

namespace s3d
{
	namespace Rx
	{
		template <class Type>
		struct Message
		{
			uint64 time;

			Type value;
		};

		template <class Ret, Ret(*func)()>
		struct InputStream
		{
			using DelayFunc = std::function<void(Ret)>;

			using Delay = std::pair<DelayFunc, MillisecondsF>;

			Array<Message<std::decay_t<Ret>>> m_messages;

			uint64 m_previousUpdateTime = 0;

			uint64 m_currentUpdateTime = 0;

			Array<std::pair<DelayFunc, MillisecondsF>> m_delayFuncs;

			void add(Delay delayFunc)
			{
				m_delayFuncs.push_back(delayFunc);
			}

			void update()
			{
				m_previousUpdateTime = m_currentUpdateTime;

				m_currentUpdateTime = Time::GetMillisec();

				m_messages.push_back({ m_currentUpdateTime, func() });

				if (!m_delayFuncs.isEmpty())
				{
					for (const auto& df : m_delayFuncs)
					{
						for (size_t i = 0; i < m_messages.size(); ++i)
						{
							const size_t idx = m_messages.size() - 1 - i;

							if (m_currentUpdateTime - m_messages[idx].time > df.second.count())
							{
								df.first(m_messages[idx].value);
								break;
							}
						}
					}
				}
			}
		};


		using CursorPosStream = Rx::InputStream<Point, Cursor::Pos>;

		template <uint8 key>
		bool KeyDown()
		{
			return Key{ InputDevice::Keyboard, key }.down();
		}

		template <uint8 key>
		using KeyDownStream = Rx::InputStream<bool, KeyDown<key> > ;
	}
}

void Main()
{
	Rx::CursorPosStream cps;
	cps.add(Rx::CursorPosStream::Delay{ [](Point p) { Circle(p, 50).draw(Palette::Blue) ; }, 600ms });
	cps.add(Rx::CursorPosStream::Delay{ [](Point p) { Circle(p, 40).draw(Palette::Green); }, 400ms });
	cps.add(Rx::CursorPosStream::Delay{ [](Point p) { Circle(p, 30).draw(Palette::Red)  ; }, 200ms });
	cps.add(Rx::CursorPosStream::Delay{ [](Point p) { Circle(p, 20).draw(Palette::White); }, 0ms	  });
	Key0;

	Rx::KeyDownStream<0x30> kps;
	kps.add(Rx::KeyDownStream<0x30>::Delay{ [](bool p) { if(p)Rect(0,0, 40).draw(Palette::Yellow); }, 400ms });

	while (System::Update())
	{
		cps.update();
		kps.update();
	}
}