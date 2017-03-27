//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include "CBinaryWriter_Linux.hpp"

namespace s3d
{
	BinaryWriter::CBinaryWriter::CBinaryWriter()
	{

	}

	BinaryWriter::CBinaryWriter::~CBinaryWriter()
	{
		close();
	}

	int64 BinaryWriter::CBinaryWriter::fillBuffer(const void* src, const size_t size)
	{
		if (!m_pBuffer)
		{
			m_pBuffer = static_cast<uint8*>(::malloc(BufferSize));
		}

		::memcpy(m_pBuffer + m_currentBufferPos, src, size);

		m_currentBufferPos += size;

		return size;
	}

	bool BinaryWriter::CBinaryWriter::open(const FilePath& path, const OpenMode openMode)
	{
		if (!m_pFile)
		{
			close();
		}

		if (path.isEmpty())
		{
			return false;
		}

		FilePath fullPath;

		const FilePath parentFilePath = FileSystem::ParentPath(path, 0, &fullPath);

		if (!FileSystem::Exists(parentFilePath) && !FileSystem::CreateDirectories(parentFilePath))
		{
			return false;
		}

		const bool append = (openMode == OpenMode::Append && FileSystem::Exists(fullPath));

		m_pFile = std::fopen(fullPath.narrow().c_str(), (append ? "r+" : "w"));

		if (!m_pFile)
		{
			return false;
		}

		if (append)
		{
			std::fseek(m_pFile, 0, SEEK_END);
		}

		m_fullPath = fullPath;

		return true;
	}

	void BinaryWriter::CBinaryWriter::flush()
	{
		if (m_currentBufferPos == 0)
		{
			return;
		}

		std::fwrite(m_pBuffer, 1, m_currentBufferPos, m_pFile);

		m_currentBufferPos = 0;
	}

	void BinaryWriter::CBinaryWriter::close()
	{
		if (!m_pFile)
		{
			return;
		}

		flush();

		::free(m_pBuffer);

		m_pBuffer = nullptr;

		std::fclose(m_pFile);

		m_pFile = nullptr;

		m_fullPath.clear();
	}

	bool BinaryWriter::CBinaryWriter::isOpened() const noexcept
	{
		return m_pFile != nullptr;
	}

	void BinaryWriter::CBinaryWriter::clear()
	{
		if (!m_pFile)
		{
			return;
		}

		m_currentBufferPos = 0;

		std::fclose(m_pFile);

		m_pFile = std::fopen(m_fullPath.narrow().c_str(), "w");

		if (!m_pFile)
		{
			m_fullPath.clear();
		}
	}

	int64 BinaryWriter::CBinaryWriter::size()
	{
		if (!m_pFile)
		{
			return 0;
		}

		flush();

		return FileSystem::Size(m_fullPath);
	}

	int64 BinaryWriter::CBinaryWriter::setPos(int64 pos)
	{
		if (!m_pFile)
		{
			return 0;
		}

		flush();

		std::fseek(m_pFile, pos, SEEK_SET);

		return std::ftell(m_pFile);
	}

	int64 BinaryWriter::CBinaryWriter::getPos()
	{
		if (!m_pFile)
		{
			return 0;
		}

		flush();

		return std::ftell(m_pFile);
	}

	int64 BinaryWriter::CBinaryWriter::write(const void* src, size_t size)
	{
		if (!m_pFile)
		{
			return 0;
		}

		assert(src || !size);

		if (size < BufferSize)
		{
			if (m_currentBufferPos + size > BufferSize)
			{
				flush();
			}

			return fillBuffer(src, size);
		}
		else
		{
			flush();
		}

		return std::fwrite(src, 1, size, m_pFile);
	}

	const FilePath& BinaryWriter::CBinaryWriter::path() const
	{
		return m_fullPath;
	}
}

# endif
