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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FileSystem.hpp>
# include "CToastNotification.hpp"
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <ThirdParty/WinToast/wintoastlib.h>

namespace s3d
{
	using namespace WinToastLib;

	class ToastHandler : public IWinToastHandler
	{
	public:

		explicit ToastHandler(size_t index)
			: m_index{ index } {}

		void toastActivated() const override
		{
			if (auto p = SIV3D_ENGINE(ToastNotification))
			{
				p->onStateUpdate(m_index, ToastNotificationState::Activated, none);
			}
		}

		void toastActivated(int actionIndex) const
		{
			if (auto p = SIV3D_ENGINE(ToastNotification))
			{
				p->onStateUpdate(m_index, ToastNotificationState::Activated, actionIndex);
			}
		}

		void toastDismissed(const WinToastDismissalReason state) const override
		{
			if (auto p = SIV3D_ENGINE(ToastNotification))
			{
				if (state == IWinToastHandler::UserCanceled)
				{
					p->onStateUpdate(m_index, ToastNotificationState::UserCanceled, none);
				}
				else if (state == IWinToastHandler::ApplicationHidden)
				{
					p->onStateUpdate(m_index, ToastNotificationState::ApplicationHidden, none);
				}
				else
				{
					p->onStateUpdate(m_index, ToastNotificationState::TimedOut, none);
				}
			}
		}

		void toastFailed() const override
		{
			if (auto p = SIV3D_ENGINE(ToastNotification))
			{
				p->onStateUpdate(m_index, ToastNotificationState::Error, none);
			}
		}

	private:

		size_t m_index = 0;
	};

	CToastNotification::CToastNotification() {}

	CToastNotification::~CToastNotification()
	{
		LOG_SCOPED_TRACE(U"CToastNotification::~CToastNotification()");

		clear();
	}

	void CToastNotification::init()
	{
		LOG_SCOPED_TRACE(U"CToastNotification::init()");

		m_available = WinToast::isCompatible();

		if (m_available)
		{
			LOG_INFO(U"ℹ️ ToastNotification is available");
		}
		else
		{
			LOG_INFO(U"ℹ️ ToastNotification is not available");
		}

		const std::wstring appName = FileSystem::BaseName(FileSystem::ModulePath()).toWstr();
		WinToast::instance()->setAppName(appName);

		const auto aumi = WinToast::configureAUMI(L"Siv3D", appName, L"app");
		WinToast::instance()->setAppUserModelId(aumi);
	}

	bool CToastNotification::isAvailable() const
	{
		return m_available;
	}

	NotificationID CToastNotification::show(const ToastNotificationItem& item)
	{
		if (not setup())
		{
			return -1;
		}

		WinToastTemplate templ = WinToastTemplate(WinToastTemplate::ImageAndText02);
		if (item.imagePath && FileSystem::Exists(item.imagePath))
		{
			templ.setImagePath(FileSystem::FullPath(item.imagePath).toWstr());
		}
		templ.setTextField(item.title.toWstr(), WinToastTemplate::FirstLine);
		templ.setTextField(item.message.toWstr(), WinToastTemplate::SecondLine);
		for (const auto& action : item.actions)
		{
			templ.addAction(action.toWstr());
		}

		WinToast::WinToastError error = WinToast::NoError;
		const NotificationID id = WinToast::instance()->showToast(templ, std::make_unique<ToastHandler>(m_indexCount), &error);
		if (id != -1)
		{
			std::lock_guard lock{ m_mutex };

			ToastState toast;
			toast.id = id;
			toast.state = ToastNotificationState::Shown;

			m_toastIDTable.emplace(id, m_indexCount);
			m_toasts.emplace(m_indexCount, toast);

			++m_indexCount;
		}

		return id;
	}

	ToastNotificationState CToastNotification::getState(NotificationID id)
	{
		if (!m_initialized.has_value() || !m_initialized.value())
		{
			return ToastNotificationState::_None;
		}

		std::lock_guard lock(m_mutex);

		const auto itTable = m_toastIDTable.find(id);

		if (itTable == m_toastIDTable.end())
		{
			return ToastNotificationState::_None;
		}

		const size_t index = itTable->second;

		auto it = m_toasts.find(index);

		if (it == m_toasts.end())
		{
			return ToastNotificationState::_None;
		}

		return it->second.state;
	}

	Optional<size_t> CToastNotification::getAction(NotificationID id)
	{
		if (!m_initialized.has_value() || !m_initialized.value())
		{
			return none;
		}

		std::lock_guard lock(m_mutex);

		const auto itTable = m_toastIDTable.find(id);

		if (itTable == m_toastIDTable.end())
		{
			return none;
		}

		const size_t index = itTable->second;

		auto it = m_toasts.find(index);

		if (it == m_toasts.end())
		{
			return none;
		}

		return it->second.action;
	}

	void CToastNotification::hide(NotificationID id)
	{
		if (!m_initialized.has_value() || !m_initialized.value())
		{
			return;
		}

		{
			std::lock_guard lock(m_mutex);

			const auto itTable = m_toastIDTable.find(id);

			if (itTable == m_toastIDTable.end())
			{
				return;
			}

			const size_t index = itTable->second;

			auto it = m_toasts.find(index);

			if (it == m_toasts.end())
			{
				return;
			}

			if (it->second.state != ToastNotificationState::Shown)
			{
				return;
			}
		}

		WinToast::instance()->hideToast(id);
	}

	void CToastNotification::clear()
	{
		if (!m_initialized.has_value() || !m_initialized.value())
		{
			return;
		}

		WinToast::instance()->clear();
	}

	void CToastNotification::onStateUpdate(size_t index, ToastNotificationState state, const Optional<int32>& option)
	{
		std::lock_guard lock(m_mutex);

		auto it = m_toasts.find(index);

		if (it == m_toasts.end())
		{
			return;
		}

		it->second.state = state;

		if (state == ToastNotificationState::Activated && option.has_value())
		{
			it->second.action = option.value();
		}
	}

	bool CToastNotification::setup()
	{
		if (m_initialized.has_value())
		{
			return *m_initialized;
		}

		if (!m_available)
		{
			m_initialized = false;

			return false;
		}

		WinToast::WinToastError error = WinToast::NoError;

		if (!WinToast::instance()->initialize(&error))
		{
			m_initialized = false;
		}
		else
		{
			m_initialized = true;
		}

		return *m_initialized;
	}
}
