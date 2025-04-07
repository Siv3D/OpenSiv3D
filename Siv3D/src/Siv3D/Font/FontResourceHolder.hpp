﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>

# if SIV3D_PLATFORM(WINDOWS)

# include <Siv3D/Windows/Windows.hpp>

namespace s3d
{
	class FontResourceHolder
	{
	public:

		SIV3D_NODISCARD_CXX20
		FontResourceHolder() = default;

		SIV3D_NODISCARD_CXX20
		explicit FontResourceHolder(FilePathView path)
		{
			HMODULE hModule = ::GetModuleHandleW(nullptr);

			const std::wstring pathW = path.toWstr();

			if (HRSRC hrs = ::FindResourceW(hModule, &pathW[1], L"FILE"))
			{
				if (HGLOBAL resource = ::LoadResource(hModule, hrs))
				{
					m_pResource = ::LockResource(resource);

					m_size = ::SizeofResource(hModule, hrs);
				}
			}
		}

		~FontResourceHolder()
		{
			m_pResource = nullptr;

			m_size = 0;
		}

		[[nodiscard]]
		const void* data() const noexcept
		{
			return m_pResource;
		}

		[[nodiscard]]
		int64 size() const noexcept
		{
			return m_size;
		}

	private:

		int64 m_size = 0;

		const void* m_pResource = nullptr;
	};
}

# endif
