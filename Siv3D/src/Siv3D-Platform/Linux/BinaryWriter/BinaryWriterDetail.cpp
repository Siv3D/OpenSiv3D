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

# include <Siv3D/EngineLog.hpp>
# include "BinaryWriterDetail.hpp"

namespace s3d
{
	BinaryWriter::BinaryWriterDetail::BinaryWriterDetail()
	{
		
	}
	
	BinaryWriter::BinaryWriterDetail::~BinaryWriterDetail()
	{
		close();
	}
	
	int64 BinaryWriter::BinaryWriterDetail::fillBuffer(const void* src, const size_t size)
	{
		if (!m_pBuffer)
		{
			m_pBuffer = static_cast<Byte*>(std::malloc(BufferSize));
		}
		
		std::memcpy(m_pBuffer + m_currentBufferPos, src, size);
		
		m_currentBufferPos += size;
		
		return size;
	}
	
	bool BinaryWriter::BinaryWriterDetail::open(const FilePathView path, const OpenMode openMode)
	{
		if (!m_pFile)
		{
			close();
		}
		
		if (path.isEmpty())
		{
			LOG_FAIL(U"❌ BinaryWriter: path is empty");
			
			return false;
		}
		
		FilePath fullPath;
		
		const FilePath parentFilePath = FileSystem::ParentPath(path, 0, &fullPath);
		
		if (!FileSystem::Exists(parentFilePath) && !FileSystem::CreateDirectories(parentFilePath))
		{
			LOG_FAIL(U"❌ BinaryWriter: Failed to create parent directories \"{0}\""_fmt(parentFilePath));
			
			return false;
		}
		
		const bool append = (openMode == OpenMode::Append && FileSystem::Exists(fullPath));
		
		m_pFile = std::fopen(fullPath.narrow().c_str(), (append ? "r+" : "w"));
		
		if (!m_pFile)
		{
			LOG_FAIL(U"❌ BinaryWriter: Failed to open file \"{0}\""_fmt(path));
			
			return false;
		}
		
		if (append)
		{
			std::fseek(m_pFile, 0, SEEK_END);
		}
		
		m_fullPath = fullPath;
		
		LOG_DEBUG(U"📤 BinaryReader: Opened file \"{0}\""_fmt(m_fullPath));
		
		return true;
	}
	
	void BinaryWriter::BinaryWriterDetail::flush()
	{
		if (m_currentBufferPos == 0)
		{
			return;
		}
		
		std::fwrite(m_pBuffer, 1, m_currentBufferPos, m_pFile);
		
		m_currentBufferPos = 0;
	}
	
	void BinaryWriter::BinaryWriterDetail::close()
	{
		if (!m_pFile)
		{
			return;
		}
		
		flush();
		
		std::free(m_pBuffer);
		
		m_pBuffer = nullptr;
		
		std::fclose(m_pFile);
		
		m_pFile = nullptr;
		
		LOG_DEBUG(U"📥 BinaryWriter: Closed file \"{0}\""_fmt(m_fullPath));
		
		m_fullPath.clear();
	}
	
	bool BinaryWriter::BinaryWriterDetail::isOpened() const noexcept
	{
		return m_pFile != nullptr;
	}
	
	void BinaryWriter::BinaryWriterDetail::clear()
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
	
	int64 BinaryWriter::BinaryWriterDetail::size()
	{
		if (!m_pFile)
		{
			return 0;
		}
		
		flush();
		
		return FileSystem::Size(m_fullPath);
	}
	
	int64 BinaryWriter::BinaryWriterDetail::setPos(int64 pos)
	{
		if (!m_pFile)
		{
			return 0;
		}
		
		flush();
		
		std::fseek(m_pFile, pos, SEEK_SET);
		
		return std::ftell(m_pFile);
	}
	
	int64 BinaryWriter::BinaryWriterDetail::getPos()
	{
		if (!m_pFile)
		{
			return 0;
		}
		
		flush();
		
		return std::ftell(m_pFile);
	}
	
	int64 BinaryWriter::BinaryWriterDetail::write(const void* src, size_t size)
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
	
	const FilePath& BinaryWriter::BinaryWriterDetail::path() const
	{
		return m_fullPath;
	}
}
