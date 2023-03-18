//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/ToastNotification.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DToastNotification
	{
	public:

		static ISiv3DToastNotification* Create();

		virtual ~ISiv3DToastNotification() = default;

		virtual void init() = 0;

		virtual bool isAvailable() const = 0;

		virtual ToastNotificationID show(const ToastNotificationItem& item) = 0;

		virtual ToastNotificationState getState(ToastNotificationID id) = 0;

		virtual Optional<size_t> getAction(ToastNotificationID id) = 0;

		virtual void hide(ToastNotificationID id) = 0;

		virtual void clear() = 0;

		virtual void onStateUpdate(size_t index, ToastNotificationState state, const Optional<int32>& option) = 0;
	};
}
