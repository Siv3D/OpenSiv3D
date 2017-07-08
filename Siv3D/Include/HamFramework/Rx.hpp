//-----------------------------------------------
//
//	This file is part of the HamFramework for Siv3D.
//
//	Copyright (C) 2014-2017 HAMSTRO
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D.hpp>

namespace s3d
{
	namespace Rx
	{
		template <class Type>
		struct Message
		{
			uint64 timeMicrosec;

			Type value;
		};

		template <class Type, bool continuous>
		class IOperator
		{
		protected:

			virtual IOperator& setChild(const std::shared_ptr<IOperator<Type, continuous>>& child) = 0;

		public:

			virtual ~IOperator() = default;

			virtual void send(const Message<Type>& message) = 0;

			virtual void update(const uint64) = 0;

			IOperator<Type, continuous>& delay(const MicrosecondsF& delayMicrosec);

			IOperator<Type, continuous>& distinctUntilChanged();

			IOperator<Type, continuous>& filter(std::function<bool(Type)> filterFunction);

			void subscribe(std::function<void(Type)> func);
		};

		template <class Type, bool continuous>
		class DelayStream : public IOperator<Type, continuous>
		{
		private:

			Array<Message<Type>> m_stream;

			Optional<Message<Type>> m_lastSentMessage;

			uint64 m_delayTimeMicrosec = 0;

			std::shared_ptr<IOperator<Type, continuous>> m_child;

			IOperator<Type, continuous>& setChild(const std::shared_ptr<IOperator<Type, continuous>>& child) override
			{
				return *(m_child = child);
			}

		public:

			explicit DelayStream(uint64 delayTimeMicrosec)
				: m_delayTimeMicrosec(delayTimeMicrosec) {}

			void send(const Message<Type>& message) override
			{
				m_stream.push_back(message);
			}

			void update(const uint64 currentTimeMicrosec) override
			{
				S3D_DISABLE_MSVC_WARNINGS_PUSH(4127)

					if (continuous)
					{
						for (auto it = m_stream.begin(); it != m_stream.end();)
						{
							if ((currentTimeMicrosec - it->timeMicrosec) >= m_delayTimeMicrosec)
							{
								m_lastSentMessage = *it;

								it = m_stream.erase(it);
							}
							else
							{
								++it;
							}
						}

						if (m_child && m_lastSentMessage)
						{
							m_child->send(*m_lastSentMessage);
						}
					}
					else
					{
						for (auto it = m_stream.begin(); it != m_stream.end();)
						{
							if ((currentTimeMicrosec - it->timeMicrosec) >= m_delayTimeMicrosec)
							{
								if (m_child)
								{
									m_child->send(*it);
								}

								m_lastSentMessage = *it;

								it = m_stream.erase(it);
							}
							else
							{
								++it;
							}
						}
					}

				if (m_child)
				{
					m_child->update(currentTimeMicrosec);
				}

				S3D_DISABLE_MSVC_WARNINGS_POP()
			}
		};

		template <class Type, bool continuous>
		class DistinctUntilChanged : public IOperator<Type, continuous>
		{
		private:

			Array<Message<Type>> m_stream;

			Optional<Message<Type>> m_lastSentMessage;

			std::shared_ptr<IOperator<Type, continuous>> m_child;

			IOperator<Type, continuous>& setChild(const std::shared_ptr<IOperator<Type, continuous>>& child) override
			{
				return *(m_child = child);
			}

		public:

			DistinctUntilChanged() = default;

			void send(const Message<Type>& message) override
			{
				m_stream.push_back(message);
			}

			void update(const uint64 currentTimeMicrosec) override
			{
				for (auto it = m_stream.begin(); it != m_stream.end();)
				{
					if (m_lastSentMessage && it->value == m_lastSentMessage->value)
					{
						it = m_stream.erase(it);
					}
					else
					{
						m_child->send(*it);

						m_lastSentMessage = *it;

						it = m_stream.erase(it);

						m_child->update(currentTimeMicrosec);
					}
				}
			}
		};

		template <class Type, bool continuous>
		class Filter : public IOperator<Type, continuous>
		{
		private:

			std::shared_ptr<IOperator<Type, continuous>> m_child;

			std::function<bool(Type)> m_filterFunction;

			bool m_updated = false;

			IOperator<Type, continuous>& setChild(const std::shared_ptr<IOperator<Type, continuous>>& child) override
			{
				return *(m_child = child);
			}

		public:

			Filter() = default;

			explicit Filter(std::function<bool(Type)> filterFunction)
				: m_filterFunction(filterFunction) {}

			void send(const Message<Type>& message) override
			{
				if (!m_child)
				{
					return;
				}

				if (m_filterFunction && m_filterFunction(message.value))
				{
					m_child->send(message);

					m_updated = true;
				}
			}

			void update(const uint64 currentTimeMicrosec) override
			{
				if (!m_child)
				{
					return;
				}

				if (m_child && m_updated)
				{
					m_child->update(currentTimeMicrosec);

					m_updated = false;
				}
			}
		};

		template <class Type, bool continuous>
		class Subscriber : public IOperator<Type, continuous>
		{
		private:

			Array<Message<Type>> m_stream;

			using function_type = std::function<void(Type)>;

			function_type m_function;

			IOperator<Type, continuous>& setChild(const std::shared_ptr<IOperator<Type, continuous>>&) override
			{
				return *this;
			}

		public:

			Subscriber() = default;

			explicit Subscriber(function_type function)
				: m_function(function) {}

			void send(const Message<Type>& message) override
			{
				m_stream.push_back(message);
			}

			void update(const uint64) override
			{
				if (m_function)
				{
					for (const auto& stream : m_stream)
					{
						m_function(stream.value);
					}
				}

				m_stream.clear();
			}
		};

		template <class Type, bool continuous>
		IOperator<Type, continuous>& IOperator<Type, continuous>::delay(const MicrosecondsF& delayMicrosec)
		{
			return setChild(std::make_shared<DelayStream<Type, continuous>>(static_cast<uint64>(delayMicrosec.count())));
		}

		template <class Type, bool continuous>
		IOperator<Type, continuous>& IOperator<Type, continuous>::distinctUntilChanged()
		{
			return setChild(std::make_shared<DistinctUntilChanged<Type, continuous>>());
		}

		template <class Type, bool continuous>
		IOperator<Type, continuous>& IOperator<Type, continuous>::filter(std::function<bool(Type)> filterFunction)
		{
			return setChild(std::make_shared<Filter<Type, continuous>>(filterFunction));
		}

		template <class Type, bool continuous>
		void IOperator<Type, continuous>::subscribe(std::function<void(Type)> func)
		{
			setChild(std::make_shared<Subscriber<Type, continuous>>(func));
		}

		template <class Type, Type(*func)(), bool continuous>
		class InputStream
		{
		private:

			Array<std::shared_ptr<IOperator<Type, continuous>>> m_children;

		public:

			IOperator<Type, continuous>& delay(const MicrosecondsF& delayMicrosec)
			{
				m_children.push_back(std::make_shared<DelayStream<Type, continuous>>(static_cast<uint64>(delayMicrosec.count())));

				return *m_children.back();
			}

			IOperator<Type, continuous>& distinctUntilChanged()
			{
				m_children.push_back(std::make_shared<DistinctUntilChanged<Type, continuous>>());

				return *m_children.back();
			}

			IOperator<Type, continuous>& filter(std::function<bool(Type)> filterFunction)
			{
				m_children.push_back(std::make_shared<Filter<Type, continuous>>(filterFunction));

				return *m_children.back();
			}

			void subscribe(std::function<void(Type)> function)
			{
				m_children.push_back(std::make_shared<Subscriber<Type, continuous>>(function));
			}

			void send(const Message<Type>& message)
			{
				for (auto& child : m_children)
				{
					child->send(message);
				}
			}

			void update()
			{
				const uint64 currentTimeMicrosec = Time::GetMicrosec();

				for (auto& child : m_children)
				{
					child->send(Message<Type>{ currentTimeMicrosec, func() });

					child->update(currentTimeMicrosec);
				}
			}
		};

		template <uint8 key>
		bool KeyDown()
		{
			return Key{ InputDevice::Keyboard, key }.down();
		}

		using CursorPosStream = Rx::InputStream<Point, Cursor::Pos, true>;
		using Key0DownStream = Rx::InputStream<bool, KeyDown<0x30>, false>;
	}
}

/* example

# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Rx::CursorPosStream cps;
	cps
		.distinctUntilChanged() // 値が変化したときだけ
		.subscribe(Log);
	cps
		.delay(600ms) // 600ms 遅らせる
		.filter([](Point p) { return p.x < 320; }) // 条件を満たすとき
		.subscribe([](Point p) { Circle(p, 50).draw(Palette::Blue); });
	cps
		.delay(400ms) // 400ms 遅らせる
		.subscribe([](Point p) { Circle(p, 40).draw(Palette::Green); });
	cps
		.delay(200ms) // 200ms 遅らせる
		.subscribe([](Point p) { Circle(p, 30).draw(Palette::Red); });
	cps
		.subscribe([](Point p) { Circle(p, 20).draw(Palette::White); });

	while (System::Update())
	{
		cps.update();
	}
}
*/
