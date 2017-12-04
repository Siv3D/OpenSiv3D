//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <cassert>

namespace s3d
{
	class ISiv3DLicenseManager;
	class ISiv3DLogger;
	class ISiv3DSystem;
	class ISiv3DCPU;
	class ISiv3DConsole;

	template <class Interface>
	class Siv3DComponent
	{
	private:

		Interface * pInterface = nullptr;

	public:

		Siv3DComponent()
			: pInterface(Interface::Create()) {}

		~Siv3DComponent()
		{
			assert(pInterface == nullptr);
		}

		Interface* get()
		{
			return pInterface;
		}

		void release()
		{
			delete pInterface;

			pInterface = nullptr;
		}
	};

	class Siv3DEngine
	{
	private:

		inline static Siv3DEngine* pEngine = nullptr;

		Siv3DComponent<ISiv3DLicenseManager> m_licenseManager;

		Siv3DComponent<ISiv3DLogger> m_logger;

		Siv3DComponent<ISiv3DSystem> m_system;

		Siv3DComponent<ISiv3DCPU> m_cpu;

		Siv3DComponent<ISiv3DConsole> m_console;

	public:

		Siv3DEngine();

		~Siv3DEngine();

		static bool isActive()
		{
			return pEngine != nullptr;
		}

		static ISiv3DLicenseManager* GetLicenseManager()
		{
			return pEngine->m_licenseManager.get();
		}

		static ISiv3DLogger* GetLogger()
		{
			return pEngine->m_logger.get();
		}

		static ISiv3DSystem* GetSystem()
		{
			return pEngine->m_system.get();
		}

		static ISiv3DCPU* GetCPU()
		{
			return pEngine->m_cpu.get();
		}

		static ISiv3DConsole* GetConsole()
		{
			return pEngine->m_console.get();
		}
	};
}
