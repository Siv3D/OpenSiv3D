//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Windows.hpp>
# include <WinToast/wintoastlib.h>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CToastNotification.hpp"
# include "Siv3DEngine.hpp"

namespace s3d
{
	using namespace WinToastLib;

	class ToastHandler : public IWinToastHandler
	{
	private:

		size_t m_index = 0;

	public:

		explicit ToastHandler(size_t index)
			: m_index(index)
		{

		}

		void toastActivated() const override
		{
			if (auto p = Siv3DEngine::Get<ISiv3DToastNotification>())
			{
				p->onStateUpdate(m_index, ToastNotificationState::Activated, none);
			}
		}

		void toastActivated(int actionIndex) const
		{
			if (auto p = Siv3DEngine::Get<ISiv3DToastNotification>())
			{
				p->onStateUpdate(m_index, ToastNotificationState::Activated, actionIndex);
			}
		}

		void toastDismissed(const WinToastDismissalReason state) const override
		{
			if (auto p = Siv3DEngine::Get<ISiv3DToastNotification>())
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
			if (auto p = Siv3DEngine::Get<ISiv3DToastNotification>())
			{
				p->onStateUpdate(m_index, ToastNotificationState::Error, none);
			}
		}
	};

	CToastNotification::CToastNotification()
	{

	}

	CToastNotification::~CToastNotification()
	{
		clear();

		LOG_TRACE(U"CToastNotification::~CToastNotification()");
	}

	void CToastNotification::init()
	{
		LOG_TRACE(U"CToastNotification::init()");

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

		LOG_INFO(U"ℹ️ CToastNotification initialized");
	}

	bool CToastNotification::isAvailable() const
	{
		return m_available;
	}

	NotificationID CToastNotification::show(const ToastNotificationProperty& prop)
	{
		if (!setup())
		{
			return -1;
		}

		WinToastTemplate templ = WinToastTemplate(WinToastTemplate::ImageAndText02);
		if (prop.imagePath && FileSystem::Exists(prop.imagePath))
		{
			templ.setImagePath(FileSystem::FullPath(prop.imagePath).toWstr());
		}
		templ.setTextField(prop.title.toWstr(), WinToastTemplate::FirstLine);
		templ.setTextField(prop.message.toWstr(), WinToastTemplate::SecondLine);
		for (const auto& action : prop.actions)
		{
			templ.addAction(action.toWstr());
		}

		WinToast::WinToastError error = WinToast::NoError;
		const NotificationID id = WinToast::instance()->showToast(templ, std::make_unique<ToastHandler>(m_indexCount), &error);
		if (id != -1)
		{
			std::lock_guard lock(m_mutex);

			ToastState toast;
			toast.id = id;
			toast.state = ToastNotificationState::Shown;
			
			m_toastIDTable.emplace(id, m_indexCount);
			m_toasts.emplace(m_indexCount, toast);

			++m_indexCount;
		}

		return id;
	}

	ToastNotificationState CToastNotification::getState(const NotificationID id)
	{
		if (!m_initialized.has_value() || !m_initialized.value())
		{
			return ToastNotificationState::None;
		}

		std::lock_guard lock(m_mutex);

		const auto itTable = m_toastIDTable.find(id);

		if (itTable == m_toastIDTable.end())
		{
			return ToastNotificationState::None;
		}

		const size_t index = itTable.value();

		auto it = m_toasts.find(index);

		if (it == m_toasts.end())
		{
			return ToastNotificationState::None;
		}

		return it.value().state;
	}

	Optional<size_t> CToastNotification::getAction(const NotificationID id)
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

		const size_t index = itTable.value();

		auto it = m_toasts.find(index);

		if (it == m_toasts.end())
		{
			return none;
		}

		return it.value().action;
	}

	void CToastNotification::hide(const NotificationID id)
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

			const size_t index = itTable.value();

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

	void CToastNotification::onStateUpdate(const size_t index, const ToastNotificationState state, const Optional<int32>& option)
	{
		std::lock_guard lock(m_mutex);

		auto it = m_toasts.find(index);

		if (it == m_toasts.end())
		{
			return;
		}

		it.value().state = state;

		if (state == ToastNotificationState::Activated && option.has_value())
		{
			it.value().action = option.value();
		}
	}

	bool CToastNotification::setup()
	{
		if (m_initialized.has_value())
		{
			return m_initialized.value();
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

		return m_initialized.value();
	}
}
