﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Logger.hpp>
# include "CBinaryReader_macOS.hpp"

namespace s3d
{
    BinaryReader::CBinaryReader::CBinaryReader()
    {
        
    }
    
    BinaryReader::CBinaryReader::~CBinaryReader()
    {
        close();
    }
    
    bool BinaryReader::CBinaryReader::open(const FilePath& path)
    {
        if (isOpened())
        {
            close();
        }
        
        m_pFile = std::fopen(path.narrow().c_str(), "r");
        
        if (!m_pFile)
        {
			LOG_FAIL(U"❌ BinaryReader: Failed to open file \"{0}\""_fmt(path));

            return false;
        }
        
		m_size = FileSystem::FileSize(path);
        
        m_fullPath = FileSystem::FullPath(path);

		LOG_DEBUG(U"📤 BinaryReader: Opened file \"{0}\" size: {1}"_fmt(m_fullPath, FMTBYTES(m_size)));
        
        return true;
    }
    
    void BinaryReader::CBinaryReader::close()
    {
        if (!isOpened())
        {
            return;
        }

        std::fclose(m_pFile);

		LOG_DEBUG(U"📥 BinaryReader: Closed file \"{0}\""_fmt(m_fullPath));
        
        m_pFile = nullptr;

        m_size = 0;
        
        m_fullPath.clear();
    }
    
    bool BinaryReader::CBinaryReader::isOpened() const noexcept
    {
        return m_pFile != nullptr;
    }
    
    int64 BinaryReader::CBinaryReader::size() const noexcept
    {
        return m_size;
    }
    
    int64 BinaryReader::CBinaryReader::setPos(const int64 pos)
    {
        if (!isOpened())
        {
            return 0;
        }

        std::fseek(m_pFile, pos, SEEK_SET);
        
        return std::ftell(m_pFile);
    }
    
    int64 BinaryReader::CBinaryReader::getPos()
    {
        if (!isOpened())
        {
            return 0;
        }
        
        return std::ftell(m_pFile);
    }
    
    int64 BinaryReader::CBinaryReader::read(void* const buffer, const int64 size)
    {
		assert(buffer != nullptr || size == 0);
        
        return std::fread(buffer, 1, size, m_pFile);
    }
    
    int64 BinaryReader::CBinaryReader::read(void* const buffer, const int64 pos, const int64 size)
    {
		assert(buffer != nullptr || size == 0);
        
        setPos(pos);
        
        return std::fread(buffer, 1, size, m_pFile);
    }
    
    int64 BinaryReader::CBinaryReader::lookahead(void* const buffer, const int64 size)
    {
        assert(buffer != nullptr || size == 0);
        
        const auto previousPos = getPos();
        
        const auto readSize = std::fread(buffer, 1, size, m_pFile);
        
        setPos(previousPos);
        
        return readSize;
    }
    
    int64 BinaryReader::CBinaryReader::lookahead(void* const buffer, const int64 pos, const int64 size)
    {
        assert(buffer != nullptr || size == 0);
        
        const auto previousPos = getPos();

        setPos(pos);        
        
        const auto readSize = std::fread(buffer, 1, size, m_pFile);
        
        setPos(previousPos);
        
        return readSize;
    }
    
    const FilePath& BinaryReader::CBinaryReader::path() const
    {
        return m_fullPath;
    }
}

# endif
