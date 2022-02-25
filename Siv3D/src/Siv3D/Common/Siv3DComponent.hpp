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
# include <cassert>

namespace s3d
{
	template <class Interface>
	class Siv3DComponent
	{
	private:

		Interface* pInterface = Interface::Create();

	public:

		~Siv3DComponent()
		{
			// must be released prior to the destructor executing
			assert(pInterface == nullptr);
		}

		[[nodiscard]]
		Interface* get() noexcept
		{
			return pInterface;
		}

		void release()
		{
			delete pInterface;
			pInterface = nullptr;
		}
	};
}
