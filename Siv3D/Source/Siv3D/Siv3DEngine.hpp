//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <cassert>

namespace s3d
{
	template <class Interface>
	class Siv3DComponent
	{
	private:

		Interface* pInterface = nullptr;

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

		static Siv3DEngine* m_pEngine;

	public:

		Siv3DEngine();

		~Siv3DEngine();

		static bool isActive()
		{
			return m_pEngine != nullptr;
		}
	};
}