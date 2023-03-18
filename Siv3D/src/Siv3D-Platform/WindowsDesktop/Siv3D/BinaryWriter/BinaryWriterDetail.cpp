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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/FormatUtility.hpp>
# include "BinaryWriterDetail.hpp"

namespace s3d
{
	namespace detail
	{
		inline constexpr DWORD MakeCreationDispotion(const OpenMode openMode) noexcept
		{
			DWORD creationDispotion = 0;

			if (openMode & OpenMode::Append)
			{
				creationDispotion = OPEN_ALWAYS;
			}
			else if (openMode & OpenMode::Trunc)
			{
				creationDispotion = CREATE_ALWAYS;
			}

			return creationDispotion;
		}
	}

	BinaryWriter::BinaryWriterDetail::BinaryWriterDetail() = default;

	BinaryWriter::BinaryWriterDetail::~BinaryWriterDetail()
	{
		close();
	}

	bool BinaryWriter::BinaryWriterDetail::open(const FilePathView path, const OpenMode openMode)
	{
		LOG_TRACE(U"BinaryWriter::BinaryWriterDetail::open(\"{0}\", {1})"_fmt(
			path, FromEnum(openMode)));

		close();

		if (not path)
		{
			LOG_FAIL(U"❌ BinaryWriter: path is empty");
			return false;
		}

		if (FileSystem::IsResourcePath(path))
		{
			LOG_FAIL(U"❌ BinaryWriter: path is a resource path");
			return false;
		}

		FilePath fullPath;
		const FilePath parentFilePath = FileSystem::ParentPath(path, 0, fullPath);

		if (parentFilePath && (not FileSystem::Exists(parentFilePath)) && (not FileSystem::CreateDirectories(parentFilePath)))
		{
			LOG_FAIL(U"❌ BinaryWriter: Failed to create parent directories \"{0}\""_fmt(parentFilePath));
			return false;
		}

		// ファイルのオープン
		{
			HANDLE handle = ::CreateFileW(path.toWstr().c_str(), GENERIC_WRITE, 0, nullptr,
				detail::MakeCreationDispotion(openMode),
				FILE_ATTRIBUTE_NORMAL, nullptr);

			if (handle == INVALID_HANDLE_VALUE) [[unlikely]]
			{
				LOG_FAIL(U"❌ BinaryWriter: Failed to open the file `{0}`. {1}"_fmt(
					path, Platform::Windows::GetLastErrorMessage()));
				return false;
			}

			m_file =
			{
				.handle = handle
			};

			if (openMode & OpenMode::Append)
			{
				LARGE_INTEGER distance = { 0, 0 };

				::SetFilePointerEx(m_file.handle, distance, nullptr, FILE_END);
			}

			m_info =
			{
				.fullPath = fullPath,
				.isOpen = true,
			};

			LOG_INFO(U"📤 BinaryWriter: File `{0}` opened"_fmt(
				m_info.fullPath));
		}

		return true;
	}

	void BinaryWriter::BinaryWriterDetail::close()
	{
		if (not m_info.isOpen) [[unlikely]]
		{
			return;
		}

		flush();

		m_buffer = {};

		::CloseHandle(m_file.handle);
		m_file = {};

		LOG_INFO(U"📥 BinaryWriter: File `{0}` closed"_fmt(
			m_info.fullPath));

		m_info = {};
	}

	bool BinaryWriter::BinaryWriterDetail::isOpen() const noexcept
	{
		return m_info.isOpen;
	}

	void BinaryWriter::BinaryWriterDetail::flush()
	{
		if (m_buffer.currentWritePos == 0)
		{
			return;
		}

		DWORD written = 0;

		::WriteFile(m_file.handle, m_buffer.data.get(),
			static_cast<uint32>(m_buffer.currentWritePos), &written, nullptr);

		m_buffer.currentWritePos = 0;
	}

	void BinaryWriter::BinaryWriterDetail::clear()
	{
		if (not m_info.isOpen) [[unlikely]]
		{
			return;
		}

		m_buffer.currentWritePos = 0;

		setPos(0);

		::SetEndOfFile(m_file.handle);
	}

	int64 BinaryWriter::BinaryWriterDetail::size()
	{
		if (not m_info.isOpen) [[unlikely]]
		{
			return 0;
		}

		flush();

		return FileSystem::FileSize(m_info.fullPath);
	}

	int64 BinaryWriter::BinaryWriterDetail::setPos(const int64 clampedPos)
	{
		if (not m_info.isOpen) [[unlikely]]
		{
			return 0;
		}

		flush();

		const LARGE_INTEGER distance = { .QuadPart = clampedPos };
		LARGE_INTEGER newPos;
		::SetFilePointerEx(m_file.handle, distance, &newPos, FILE_BEGIN);
		return newPos.QuadPart;
	}

	int64 BinaryWriter::BinaryWriterDetail::getPos()
	{
		if (not m_info.isOpen) [[unlikely]]
		{
			return 0;
		}

		flush();

		const LARGE_INTEGER distance = { 0, 0 };
		LARGE_INTEGER currentPos;
		::SetFilePointerEx(m_file.handle, distance, &currentPos, FILE_CURRENT);
		return currentPos.QuadPart;
	}

	int64 BinaryWriter::BinaryWriterDetail::write(const NonNull<const void*> src, const size_t size)
	{
		if (not m_info.isOpen) [[unlikely]]
		{
			return 0;
		}

		if (const size_t room = (BufferSize - m_buffer.currentWritePos);
			size <= room)
		{
			return fillBuffer(src, size);
		}
		
		flush();

		DWORD writtenBytes;
		::WriteFile(m_file.handle, src.pointer, static_cast<uint32>(size), &writtenBytes, nullptr);

		return writtenBytes;
	}

	const FilePath& BinaryWriter::BinaryWriterDetail::path() const noexcept
	{
		return m_info.fullPath;
	}

	int64 BinaryWriter::BinaryWriterDetail::fillBuffer(const NonNull<const void*> src, const size_t size)
	{
		if (!m_buffer.data)
		{
			m_buffer.data = std::make_unique<Byte[]>(BufferSize);
		}

		std::memcpy(m_buffer.data.get() + m_buffer.currentWritePos, src.pointer, size);

		m_buffer.currentWritePos += size;

		return size;
	}
}
