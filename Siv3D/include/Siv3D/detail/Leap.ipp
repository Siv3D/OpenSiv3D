//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	namespace Leap
	{
		inline Hand::Hand(const LEAP_HAND& hand, const TrackingMode trackingMode)
			: m_hand{ hand }
			, m_trackingMode{ trackingMode } {}

		inline uint32 Hand::id() const noexcept
		{
			return m_hand.id;
		}

		inline bool Hand::isLeftHand() const noexcept
		{
			return (m_hand.type == eLeapHandType_Left);
		}

		inline bool Hand::isRightHand() const noexcept
		{
			return (m_hand.type == eLeapHandType_Right);
		}

		inline Duration Hand::trackedDuration() const noexcept
		{
			return SecondsF{ m_hand.visible_time / (1'000'000.0) };
		}

		inline Vec3 Hand::palmPosition() const noexcept
		{
			return toVec3(m_hand.palm.position);
		}

		inline Vec3 Hand::stabilizedPalmPosition() const noexcept
		{
			return toVec3(m_hand.palm.stabilized_position);
		}

		inline Vec3 Hand::palmVelocity() const noexcept
		{
			return toVec3(m_hand.palm.velocity);
		}

		inline Vec3 Hand::palmNormal() const noexcept
		{
			return toVec3(m_hand.palm.normal);
		}

		inline double Hand::palmWidth() const noexcept
		{
			return m_hand.palm.width;
		}

		inline Vec3 Hand::palmDirection() const noexcept
		{
			return toVec3(m_hand.palm.direction);
		}

		inline Quaternion Hand::palmQuaternion() const noexcept
		{
			return ToQuaternion(m_hand.palm.orientation);
		}

		inline Bone Hand::fingerBone(const size_t fingerIndex, const size_t boneIndex) const noexcept
		{
			assert(fingerIndex < 5);
			assert(boneIndex < 4);
			const auto& bone = m_hand.digits[fingerIndex].bones[boneIndex];
			return{ toVec3(bone.prev_joint), toVec3(bone.next_joint), bone.width, ToQuaternion(bone.rotation) };
		}

		inline bool Hand::isExtended(const size_t fingerIndex) const noexcept
		{
			assert(fingerIndex < 5);
			return m_hand.digits[fingerIndex].is_extended;
		}

		inline Vec3 Hand::armFrom() const noexcept
		{
			return toVec3(m_hand.arm.prev_joint);
		}

		inline Vec3 Hand::armTo() const noexcept
		{
			return toVec3(m_hand.arm.next_joint);
		}

		inline double Hand::armWidth() const noexcept
		{
			return m_hand.arm.width;
		}

		inline Quaternion Hand::armQuaternion() const noexcept
		{
			return ToQuaternion(m_hand.arm.rotation);
		}

		inline Vec3 Hand::toVec3(const LEAP_VECTOR& v) const noexcept
		{
			if (m_trackingMode == TrackingMode::Desktop)
			{
				return{ v.x, v.y, -v.z };
			}
			else if (m_trackingMode == TrackingMode::HeadMounted)
			{
				return{ -v.x, -v.z, v.y };
			}
			else
			{
				return{ v.x, -v.z, -v.y };
			}
		}

		class Connection::ConnectionDetail
		{
		public:

			ConnectionDetail() = default;

			explicit ConnectionDetail(TrackingMode trackingMode)
			{
				if (eLeapRS result = LeapCreateConnection(nullptr, &m_connection);
					result != eLeapRS_Success)
				{
					return;
				}

				if (eLeapRS result = LeapOpenConnection(m_connection);
					result != eLeapRS_Success)
				{
					return;
				}

				m_trackingMode = trackingMode;

				m_task = Async(OnUpdate, std::ref(*this));

				System::Sleep(2s);

				m_initialized = true;
			}

			~ConnectionDetail()
			{
				m_abort = true;

				m_task.get();

				LeapCloseConnection(m_connection);

				LeapDestroyConnection(m_connection);
			}

			bool isOpen() const noexcept
			{
				return m_initialized;
			}

			TrackingMode getTrackingMode() const noexcept
			{
				return m_trackingMode;
			}

			void setTrackingMode(const TrackingMode trackingMode)
			{
				m_trackingMode = trackingMode;
			}

			void update()
			{
				std::lock_guard lock{ m_mutex };

				if (m_currentTrackingFrameID < m_newTrackingFrameID)
				{
					m_currentHands.swap(m_newHands);
					m_currentTrackingFrameID = m_newTrackingFrameID;
				}
			}

			int64 trackingID() const noexcept
			{
				return m_currentTrackingFrameID;
			}

			const Array<Hand>& getHands() const noexcept
			{
				return m_currentHands;
			}

		private:

			static void OnUpdate(ConnectionDetail& self)
			{
				for (;;)
				{
					if (self.m_abort)
					{
						return;
					}

					LEAP_CONNECTION_MESSAGE message;

					if (eLeapRS result = LeapPollConnection(self.m_connection, 100, &message);
						result == eLeapRS_Success)
					{
						switch (message.type)
						{
						case eLeapEventType_Connection:
							LeapSetTrackingMode(self.m_connection, static_cast<eLeapTrackingMode>(self.m_trackingMode.load()));
							self.m_trackingModeChanged = true;
							self.m_connected = true;
							break;
						case eLeapEventType_ConnectionLost:
							self.m_connected = false;
							break;
						case eLeapEventType_Device:
							break;
						case eLeapEventType_DeviceLost:
							break;
						case eLeapEventType_DeviceFailure:
							break;
						case eLeapEventType_Tracking:
							self.handleTrackingEvent(message.tracking_event);
							break;
						case eLeapEventType_ImageComplete:
							break;
						case eLeapEventType_ImageRequestError:
							break;
						case eLeapEventType_LogEvent:
							break;
						case eLeapEventType_Policy:
							break;
						case eLeapEventType_ConfigChange:
							break;
						case eLeapEventType_ConfigResponse:
							break;
						case eLeapEventType_Image:
							break;
						case eLeapEventType_PointMappingChange:
							break;
						case eLeapEventType_LogEvents:
							break;
						case eLeapEventType_HeadPose:
							break;
						case eLeapEventType_TrackingMode:
							self.m_deviceTrackingMode = static_cast<TrackingMode>(message.tracking_mode_event->current_tracking_mode);
							self.m_trackingModeChanged = false;
							break;
						default:
							break;
						}
					}

					if (self.m_connected && (not self.m_trackingModeChanged) && self.m_deviceTrackingMode != self.m_trackingMode)
					{
						LeapSetTrackingMode(self.m_connection, static_cast<eLeapTrackingMode>(self.m_trackingMode.load()));
						self.m_trackingModeChanged = true;
					}
				}
			}

			void handleTrackingEvent(const LEAP_TRACKING_EVENT* e)
			{
				std::lock_guard lock{ m_mutex };

				m_newHands.clear();
				m_newTrackingFrameID = e->tracking_frame_id;

				for (uint32 i = 0; i < e->nHands; ++i)
				{
					m_newHands.emplace_back(e->pHands[i], m_trackingMode);
				}
			}

			bool m_initialized = false;

			LEAP_CONNECTION m_connection = nullptr;

			bool m_connected = false;

			std::atomic<TrackingMode> m_trackingMode{ TrackingMode::HeadMounted };

			std::atomic<bool> m_trackingModeChanged{ false };

			AsyncTask<void> m_task;

			std::atomic<bool> m_abort{ false };

			Array<Hand> m_currentHands;

			int64 m_currentTrackingFrameID = -1;

			TrackingMode m_deviceTrackingMode = TrackingMode::HeadMounted;

			///////////////////////////
			//
			std::mutex m_mutex;

			Array<Hand> m_newHands;

			int64 m_newTrackingFrameID = -1;
			//
			///////////////////////////
		};

		inline Connection::Connection()
			: pImpl{ std::make_shared<ConnectionDetail>() } {}

		inline Connection::Connection(const TrackingMode trackingMode)
			: pImpl{ std::make_shared<ConnectionDetail>(trackingMode) } {}

		inline bool Connection::isOpen() const noexcept
		{
			return pImpl->isOpen();
		}

		inline Connection::operator bool() const noexcept
		{
			return pImpl->isOpen();
		}

		inline TrackingMode Connection::getTrackingMode() const noexcept
		{
			return pImpl->getTrackingMode();
		}

		inline void Connection::setTrackingMode(const TrackingMode trackingMode)
		{
			pImpl->setTrackingMode(trackingMode);
		}

		inline void Connection::update()
		{
			pImpl->update();
		}

		inline int64 Connection::trackingID() const noexcept
		{
			return pImpl->trackingID();
		}

		inline const Array<Hand>& Connection::getHands() const noexcept
		{
			return pImpl->getHands();
		}
	}
}
