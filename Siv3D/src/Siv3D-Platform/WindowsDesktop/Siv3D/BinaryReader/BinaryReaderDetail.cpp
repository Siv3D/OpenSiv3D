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
# include "BinaryReaderDetail.hpp"

namespace s3d
{
	BinaryReader::BinaryReaderDetail::BinaryReaderDetail() = default;

	BinaryReader::BinaryReaderDetail::~BinaryReaderDetail()
	{
		close();
	}

	bool BinaryReader::BinaryReaderDetail::open(const FilePathView path)
	{
		LOG_TRACE(U"BinaryReader::BinaryReaderDetail::open(\"{0}\")"_fmt(path));

		close();

		if (FileSystem::IsResourcePath(path))
		{
			HMODULE hModule = ::GetModuleHandleW(nullptr);
			const std::wstring pathW = path.toWstr();

			if (HRSRC hrs = ::FindResourceW(hModule, &pathW[1], L"FILE")) [[likely]]
			{
				m_resource =
				{
					.pointer = static_cast<const Byte*>(::LockResource(::LoadResource(hModule, hrs)))
				};

				m_info =
				{
					.isOpen		= true,
					.size		= ::SizeofResource(hModule, hrs),
					.fullPath	= FilePath(path)
				};

				LOG_INFO(U"📤 BinaryReader: Opened resource \"{0}\" size: {1}"_fmt(
					m_info.fullPath, FormatDataSize(m_info.size)));

				return true;
			}
			else
			{
				LOG_FAIL(U"❌ BinaryReader: Failed to open resource \"{0}\""_fmt(
					path));
				return false;
			}
		}
		else
		{
			// ファイルのオープン
			{
				m_file.file.open(path.toWstr(), std::ios_base::binary);
				m_file.pos = 0;

				if (not m_file.file) [[unlikely]]
				{
					LOG_FAIL(U"❌ BinaryReader: Failed to open the file `{0}`"_fmt(path));
					return false;
				}
			}

			m_info =
			{
				.isOpen		= true,
				.size		= FileSystem::FileSize(path),
				.fullPath	= FileSystem::FullPath(path)
			};

			LOG_INFO(U"📤 BinaryReader: File `{0}` opened (size: {1})"_fmt(
				m_info.fullPath, FormatDataSize(m_info.size)));
		}

		return true;
	}

	void BinaryReader::BinaryReaderDetail::close()
	{
		if (not m_info.isOpen) [[unlikely]]
		{
			return;
		}

		if (isResource())
		{
			m_resource = {};
			LOG_INFO(U"📥 BinaryReader: Resource `{0}` closed"_fmt(
				m_info.fullPath));
		}
		else
		{
			m_file.file.close();
			m_file.pos = 0;
			LOG_INFO(U"📥 BinaryReader: File `{0}` closed"_fmt(
				m_info.fullPath));
		}

		m_info = {};
	}

	bool BinaryReader::BinaryReaderDetail::isOpen() const noexcept
	{
		return m_info.isOpen;
	}

	int64 BinaryReader::BinaryReaderDetail::size() const noexcept
	{
		return m_info.size;
	}

	int64 BinaryReader::BinaryReaderDetail::setPos(const int64 clampedPos)
	{
		if (not m_info.isOpen) [[unlikely]]
		{
			return 0;
		}

		assert(InRange<int64>(clampedPos, 0, size()));

		if (isResource())
		{
			return (m_resource.pos = clampedPos);
		}
		else
		{
			m_file.file.seekg(clampedPos);
			m_file.pos = clampedPos;
			return m_file.pos;
		}
	}

	int64 BinaryReader::BinaryReaderDetail::getPos()
	{
		if (isResource())
		{
			return m_resource.pos;
		}
		else
		{
			return m_file.pos;
		}
	}

	int64 BinaryReader::BinaryReaderDetail::read(const NonNull<void*> dst, const int64 size)
	{
		if (isResource())
		{
			const int64 readBytes = Clamp(size, 0LL, (m_info.size - m_resource.pos));
			std::memcpy(dst.pointer, (m_resource.pointer + m_resource.pos), static_cast<size_t>(readBytes));
			m_resource.pos += readBytes;
			return readBytes;
		}
		else
		{
			const int64 readBytes = Clamp(size, 0LL, (m_info.size - m_file.pos));

			if (readBytes)
			{
				if (not m_file.file.read(static_cast<char*>(dst.pointer), readBytes))
				{
					m_file.pos = m_file.file.tellg();

					if (m_file.file.eof())
					{
						return readBytes;
					}

					LOG_FAIL(U"❌ BinaryReader `{0}`: ReadFile() failed"_fmt(m_info.fullPath));
					return 0;
				}
			}

			m_file.pos += readBytes;
			return readBytes;
		}
	}

	int64 BinaryReader::BinaryReaderDetail::read(const NonNull<void*> dst, const int64 pos, const int64 size)
	{
		if (isResource())
		{
			const int64 readBytes = Clamp(size, 0LL, (m_info.size - pos));
			std::memcpy(dst.pointer, (m_resource.pointer + pos), static_cast<size_t>(readBytes));
			m_resource.pos = (pos + readBytes);
			return readBytes;
		}
		else
		{
			if (pos != setPos(pos))
			{
				return 0;
			}

			const int64 readBytes = Clamp(size, 0LL, (m_info.size - m_file.pos));

			if (readBytes)
			{
				if (not m_file.file.read(static_cast<char*>(dst.pointer), readBytes))
				{
					m_file.pos = m_file.file.tellg();

					if (m_file.file.eof())
					{
						return readBytes;
					}

					LOG_FAIL(U"❌ BinaryReader `{0}`: ReadFile() failed"_fmt(m_info.fullPath));
					return 0;
				}
			}

			m_file.pos += readBytes;
			return readBytes;
		}
	}

	int64 BinaryReader::BinaryReaderDetail::lookahead(const NonNull<void*> dst, const int64 size)
	{
		if (isResource())
		{
			const int64 readBytes = Clamp(size, 0LL, (m_info.size - m_resource.pos));
			std::memcpy(dst.pointer, (m_resource.pointer + m_resource.pos), static_cast<size_t>(readBytes));
			return readBytes;
		}
		else
		{
			const auto previousPos = getPos();

			const int64 readBytes = Clamp(size, 0LL, (m_info.size - m_file.pos));

			if (readBytes)
			{
				if (not m_file.file.read(static_cast<char*>(dst.pointer), readBytes))
				{
					if (m_file.file.eof())
					{
						setPos(previousPos);
						return readBytes;
					}

					LOG_FAIL(U"❌ BinaryReader `{0}`: ReadFile() failed"_fmt(m_info.fullPath));

					setPos(previousPos); 
					return 0;
				}
			}

			setPos(previousPos);
			return readBytes;
		}
	}

	int64 BinaryReader::BinaryReaderDetail::lookahead(const NonNull<void*> dst, const int64 pos, const int64 size)
	{
		if (isResource())
		{
			const int64 readBytes = Clamp(size, 0LL, (m_info.size - pos));
			std::memcpy(dst.pointer, (m_resource.pointer + pos), static_cast<size_t>(readBytes));
			return readBytes;
		}
		else
		{
			const auto previousPos = getPos();

			if (pos != setPos(pos))
			{
				return 0;
			}

			const int64 readBytes = Clamp(size, 0LL, (m_info.size - m_file.pos));

			if (readBytes)
			{
				if (not m_file.file.read(static_cast<char*>(dst.pointer), readBytes))
				{
					if (m_file.file.eof())
					{
						setPos(previousPos);
						return readBytes;
					}

					LOG_FAIL(U"❌ BinaryReader `{0}`: ReadFile() failed"_fmt(m_info.fullPath));

					setPos(previousPos);
					return 0;
				}
			}

			setPos(previousPos);
			return readBytes;
		}
	}

	const FilePath& BinaryReader::BinaryReaderDetail::path() const noexcept
	{
		return m_info.fullPath;
	}

	bool BinaryReader::BinaryReaderDetail::isResource() const noexcept
	{
		return (m_resource.pointer != nullptr);
	}
}
