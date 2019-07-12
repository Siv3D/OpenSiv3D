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
# include <Siv3D/FileSystem.hpp>
# include <ByteArray/ByteArrayDetail.hpp>

namespace s3d
{
	bool ByteArray::ByteArrayDetail::createFromFile(const FilePathView path)
	{
		release();

		if (FileSystem::IsResource(path))
		{
			HMODULE hModule = ::GetModuleHandleW(nullptr);
			const std::wstring pathW = Unicode::ToWString(path);

			if (HRSRC hrs = ::FindResourceW(hModule, &pathW[1], L"FILE"))
			{
				m_view = static_cast<const Byte*>(::LockResource(::LoadResource(hModule, hrs)));
				m_size = ::SizeofResource(hModule, hrs);
				return true;
			}

			return false;
		}

		if (!m_memoryMapping.open(path))
		{
			return false;
		}

		m_view = m_memoryMapping.data();
		m_size = m_memoryMapping.fileSize();

		return true;
	}
}
