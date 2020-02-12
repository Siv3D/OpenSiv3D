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

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Utility.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FormatUtility.hpp>
# include "BinaryReaderDetail.hpp"

namespace s3d
{
	BinaryReader::BinaryReaderDetail::BinaryReaderDetail()
	{

	}

	BinaryReader::BinaryReaderDetail::~BinaryReaderDetail()
	{
		close();
	}

	bool BinaryReader::BinaryReaderDetail::open(const FilePathView path)
	{
		if (m_opened)
		{
			close();
		}

		if (FileSystem::IsResource(path))
		{
			HMODULE hModule = ::GetModuleHandleW(nullptr);

			const std::wstring pathW = Unicode::ToWString(path);

			if (HRSRC hrs = ::FindResourceW(hModule, &pathW[1], L"FILE"))
			{
				m_pResource = ::LockResource(::LoadResource(hModule, hrs));

				m_size = ::SizeofResource(hModule, hrs);

				LOG_DEBUG(U"📤 BinaryReader: Opened resource \"{0}\" size: {1}"_fmt(path, FormatDataSize(m_size)));

				m_opened = true;

				m_fullPath = path;

				return true;
			}
			else
			{
				LOG_FAIL(U"❌ BinaryReader: Failed to open resource \"{0}\""_fmt(path));

				return false;
			}
		}
		else
		{
			m_handle = ::CreateFileW(Unicode::ToWString(path).c_str(), GENERIC_READ, (FILE_SHARE_READ | FILE_SHARE_WRITE), nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

			m_opened = (m_handle != INVALID_HANDLE_VALUE);

			if (!m_opened)
			{
				LOG_FAIL(U"❌ BinaryReader: Failed to open file \"{0}\""_fmt(path));

				return false;
			}

			m_fullPath = FileSystem::FullPath(path);

			LARGE_INTEGER size;

			::GetFileSizeEx(m_handle, &size);

			m_size = size.QuadPart;

			LOG_DEBUG(U"📤 BinaryReader: Opened file \"{0}\" size: {1}"_fmt(m_fullPath, FormatDataSize(m_size)));

			return true;
		}
	}

	void BinaryReader::BinaryReaderDetail::close()
	{
		if (!m_opened)
		{
			return;
		}

		if (m_pResource)
		{
			m_pResource = nullptr;

			LOG_DEBUG(U"📥 BinaryReader: Closed resource \"{0}\""_fmt(m_fullPath));
		}
		else if(m_handle != INVALID_HANDLE_VALUE)
		{
			::CloseHandle(m_handle);

			m_handle = INVALID_HANDLE_VALUE;

			LOG_DEBUG(U"📥 BinaryReader: Closed file \"{0}\""_fmt(m_fullPath));
		}

		m_opened = false;

		m_size = 0;

		m_fullPath.clear();
	}

	bool BinaryReader::BinaryReaderDetail::isOpen() const noexcept
	{
		return m_opened;
	}

	int64 BinaryReader::BinaryReaderDetail::size() const noexcept
	{
		return m_size;
	}

	int64 BinaryReader::BinaryReaderDetail::read(void* const buffer, const int64 size)
	{
		assert(buffer != nullptr || size == 0);

		if (m_pResource)
		{
			const int64 readSize = Clamp(size, 0LL, m_size - m_resourcePos);

			std::memcpy(buffer, static_cast<const Byte*>(m_pResource) + m_resourcePos, static_cast<size_t>(readSize));

			m_resourcePos += readSize;

			return readSize;
		}
		else
		{
			DWORD readBytes;

			if (!::ReadFile(m_handle, buffer, static_cast<DWORD>(size), &readBytes, nullptr))
			{
				LOG_DEBUG(U"❌ BinaryReader: Failed ::ReadFile() \"{0}\""_fmt(m_fullPath));

				return 0;
			}

			return readBytes;
		}
	}

	int64 BinaryReader::BinaryReaderDetail::read(void* const buffer, const int64 pos, const int64 size)
	{
		assert(buffer != nullptr || size == 0);

		if (m_pResource)
		{
			const int64 readSize = Clamp(size, 0LL, m_size - pos);

			std::memcpy(buffer, static_cast<const Byte*>(m_pResource) + pos, static_cast<size_t>(readSize));

			m_resourcePos = pos + readSize;

			return readSize;
		}
		else
		{
			DWORD readBytes;

			setPos(pos);

			if (!::ReadFile(m_handle, buffer, static_cast<DWORD>(size), &readBytes, nullptr))
			{
				LOG_FAIL(U"❌ BinaryReader: Failed ::ReadFile() \"{0}\""_fmt(m_fullPath));

				return 0;
			}

			return readBytes;
		}
	}

	int64 BinaryReader::BinaryReaderDetail::setPos(const int64 pos)
	{
		if (m_pResource)
		{
			return m_resourcePos = Clamp(pos, 0LL, m_size);
		}
		else
		{
			LARGE_INTEGER distance, newPos;

			distance.QuadPart = pos;

			::SetFilePointerEx(m_handle, distance, &newPos, FILE_BEGIN);

			return newPos.QuadPart;
		}
	}

	int64 BinaryReader::BinaryReaderDetail::getPos()
	{
		if (m_pResource)
		{
			return m_resourcePos;
		}
		else
		{
			LARGE_INTEGER distance = { 0, 0 }, currentPos;

			::SetFilePointerEx(m_handle, distance, &currentPos, FILE_CURRENT);

			return currentPos.QuadPart;
		}
	}

	int64 BinaryReader::BinaryReaderDetail::lookahead(void* const buffer, const int64 size)
	{
		assert(buffer != nullptr || size == 0);

		if (m_pResource)
		{
			const int64 readSize = Clamp(size, 0LL, m_size - m_resourcePos);

			std::memcpy(buffer, static_cast<const Byte*>(m_pResource) + m_resourcePos, static_cast<size_t>(readSize));

			return readSize;
		}
		else
		{
			const auto current = getPos();

			DWORD readBytes;

			if (!::ReadFile(m_handle, buffer, static_cast<DWORD>(size), &readBytes, nullptr))
			{
				LOG_FAIL(U"❌ BinaryReader: Failed ::ReadFile() \"{0}\""_fmt(m_fullPath));

				return 0;
			}

			setPos(current);

			return readBytes;
		}
	}

	int64 BinaryReader::BinaryReaderDetail::lookahead(void* const buffer, const int64 pos, const int64 size)
	{
		assert(buffer != nullptr || size == 0);

		if (m_pResource)
		{
			const int64 readSize = Clamp(size, 0LL, m_size - pos);

			std::memcpy(buffer, static_cast<const Byte*>(m_pResource) + pos, static_cast<size_t>(readSize));

			return readSize;
		}
		else
		{
			const auto current = getPos();

			DWORD readBytes;

			setPos(pos);

			if (!::ReadFile(m_handle, buffer, static_cast<DWORD>(size), &readBytes, nullptr))
			{
				LOG_FAIL(U"❌ BinaryReader: Failed ::ReadFile() \"{0}\""_fmt(m_fullPath));

				return 0;
			}

			setPos(current);

			return readBytes;
		}
	}

	const FilePath& BinaryReader::BinaryReaderDetail::path() const
	{
		return m_fullPath;
	}
}
