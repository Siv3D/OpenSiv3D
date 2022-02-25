//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
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

		inline double Hand::pinchDistance() const noexcept
		{
			return m_hand.pinch_distance;
		}

		inline double Hand::grabAngle() const noexcept
		{
			return m_hand.grab_angle;
		}

		inline double Hand::pinchStrength() const noexcept
		{
			return m_hand.pinch_strength;
		}

		inline double Hand::grabStrength() const noexcept
		{
			return m_hand.grab_strength;
		}

		inline Vec3 Hand::palmPosition() const noexcept
		{
			return toVec3(m_hand.palm.position);
		}

		//inline Vec3 Hand::stabilizedPalmPosition() const noexcept
		//{
		//	return toVec3(m_hand.palm.stabilized_position);
		//}

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

		//inline Quaternion Hand::palmQuaternion() const noexcept
		//{
		//	return toQuaternion(m_hand.palm.orientation);
		//}

		inline Bone Hand::fingerBone(const size_t fingerIndex, const size_t boneIndex) const noexcept
		{
			assert(fingerIndex < 5);
			assert(boneIndex < 4);
			const auto& bone = m_hand.digits[fingerIndex].bones[boneIndex];
			return{ toVec3(bone.prev_joint), toVec3(bone.next_joint), bone.width };
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

		//inline Quaternion Hand::armQuaternion() const noexcept
		//{
		//	return toQuaternion(m_hand.arm.rotation);
		//}

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
				return{ -v.x, -v.y, -v.z };
			}
		}

		inline Quaternion Hand::toQuaternion(const LEAP_QUATERNION& q) noexcept
		{
			// [Siv3D ToDo]
			return{ q.x, q.y, q.z, q.w };
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

				m_thread = std::jthread{ OnUpdate, this };

				m_initialized = true;
			}

			~ConnectionDetail()
			{
				if (m_thread.joinable())
				{
					m_thread.request_stop();

					m_thread.join();
				}
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

			static void OnUpdate(std::stop_token stop_token, ConnectionDetail* self)
			{
				for (;;)
				{
					if (stop_token.stop_requested())
					{
						LeapCloseConnection(self->m_connection);
						LeapDestroyConnection(self->m_connection);
						return;
					}

					LEAP_CONNECTION_MESSAGE message;

					if (eLeapRS result = LeapPollConnection(self->m_connection, 100, &message);
						result == eLeapRS_Success)
					{
						switch (message.type)
						{
						case eLeapEventType_Connection:
							LeapSetTrackingMode(self->m_connection, static_cast<eLeapTrackingMode>(self->m_trackingMode.load()));
							self->m_trackingModeChanged = true;
							self->m_connected = true;
							break;
						case eLeapEventType_ConnectionLost:
							self->m_connected = false;
							break;
						case eLeapEventType_Device:
							break;
						case eLeapEventType_DeviceLost:
							break;
						case eLeapEventType_DeviceFailure:
							break;
						case eLeapEventType_Tracking:
							self->handleTrackingEvent(message.tracking_event);
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
							self->m_deviceTrackingMode = static_cast<TrackingMode>(message.tracking_mode_event->current_tracking_mode);
							self->m_trackingModeChanged = false;
							break;
						default:
							break;
						}
					}

					if (self->m_connected && (not self->m_trackingModeChanged) && self->m_deviceTrackingMode != self->m_trackingMode)
					{
						LeapSetTrackingMode(self->m_connection, static_cast<eLeapTrackingMode>(self->m_trackingMode.load()));
						self->m_trackingModeChanged = true;
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

			std::jthread m_thread;

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
