//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include "../Siv3DEngine.hpp"
# include "../Window/IWindow.hpp"
# include "CDragDrop_macOS.hpp"
# include "../Siv3D_macOS.h"
# include <Siv3D/Time.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Logger.hpp>

extern "C"
{
	using namespace s3d;

	CDragDrop_macOS* pDragDrop = nullptr;
	
	void s3d_DraggingEntered(bool isFilePath, int x, int y)
	{
		if (pDragDrop)
		{
			pDragDrop->internal_entered(isFilePath, Point(x, y));
		}
	}
	
	void s3d_DraggingUpdated(int x, int y)
	{
		if (pDragDrop)
		{
			pDragDrop->internal_updated(Point(x, y));
		}
	}
	
	void s3d_DraggingExited(void)
	{
		if (pDragDrop)
		{
			pDragDrop->internal_exited();
		}
	}
	
	void s3d_TextDropped(const char* text, int x, int y)
	{
		if (pDragDrop)
		{
			pDragDrop->internal_textDropped(Unicode::Widen(text), Point(x, y));
		}
	}
	
	void s3d_FilePathsDropped(int count, const char** paths, int x, int y)
	{
		if (pDragDrop)
		{
			Array<FilePath> results(count);
			
			for (int32 i = 0; i < count; ++i)
			{
				results[i] = FileSystem::FullPath(Unicode::Widen(paths[i]));
			}
			
			pDragDrop->internal_filePathsDropped(results, Point(x, y));
		}
	}
}

namespace s3d
{
	CDragDrop_macOS::CDragDrop_macOS()
	{
		pDragDrop = this;
	}

	CDragDrop_macOS::~CDragDrop_macOS()
	{
		pDragDrop = nullptr;
	}

	bool CDragDrop_macOS::init()
	{
		LOG_INFO(U"ℹ️ DragDrop initialized");

		return true;
	}
	
	bool CDragDrop_macOS::update()
	{
		std::lock_guard<std::mutex> resourceGuard(m_mutex);
		
		if (m_acceptFilePath)
		{
			m_droppedFilePaths.insert(m_droppedFilePaths.end(), m_internal.droppedFilePaths.begin(), m_internal.droppedFilePaths.end());
		}
		
		m_internal.droppedFilePaths.clear();
		
		if (m_acceptText)
		{
			m_droppedTexts.insert(m_droppedTexts.end(), m_internal.droppedTexts.begin(), m_internal.droppedTexts.end());
		}
		
		m_internal.droppedTexts.clear();
		
		m_dragOver = m_internal.dragOver;
		
		m_itemType = m_internal.itemType;
		
		m_dragOverPos = m_internal.dragOverPos;
		
		return true;
	}
	
	void CDragDrop_macOS::acceptFilePaths(bool accept)
	{
		std::lock_guard<std::mutex> resourceGuard(m_mutex);
		
		m_acceptFilePath = accept;
	}
	
	void CDragDrop_macOS::acceptText(bool accept)
	{
		std::lock_guard<std::mutex> resourceGuard(m_mutex);
		
		m_acceptText = accept;
	}
	
	Optional<DragStatus> CDragDrop_macOS::dragOver() const
	{
		if (!m_dragOver)
		{
			return none;
		}
		
		return DragStatus{ m_itemType, m_dragOverPos };
	}
	
	bool CDragDrop_macOS::hasNewFilePaths() const
	{
		return !m_droppedFilePaths.isEmpty();
	}
	
	bool CDragDrop_macOS::hasNewText() const
	{
		return !m_droppedTexts.isEmpty();
	}
	
	void CDragDrop_macOS::clear()
	{
		m_droppedFilePaths.clear();
		
		m_droppedTexts.clear();
	}
	
	Array<DroppedFilePath> CDragDrop_macOS::getDroppedFilePaths()
	{
		Array<DroppedFilePath> dropped(std::move(m_droppedFilePaths));
		
		return dropped;
	}
	
	Array<DroppedText> CDragDrop_macOS::getDroppedText()
	{
		Array<DroppedText> dropped(std::move(m_droppedTexts));
		
		return dropped;
	}
	
	void CDragDrop_macOS::internal_entered(const bool isFilePath, const Point& pos)
	{
		std::lock_guard<std::mutex> resourceGuard(m_mutex);
	
		if ((!m_acceptFilePath && isFilePath)
			|| (!m_acceptText && !isFilePath))
		{
			return;
		}
		
		m_internal.dragOver = true;
		
		m_internal.dragOverPos = pos;
		
		m_internal.itemType = isFilePath ? DragItemType::FilePaths : DragItemType::Text;
	}
	
	void CDragDrop_macOS::internal_updated(const Point& pos)
	{
		std::lock_guard<std::mutex> resourceGuard(m_mutex);
		
		m_internal.dragOverPos = pos;
	}
	
	void CDragDrop_macOS::internal_exited()
	{
		std::lock_guard<std::mutex> resourceGuard(m_mutex);
		
		m_internal.dragOver = false;
	}
	
	void CDragDrop_macOS::internal_textDropped(const String& text, const Point& pos)
	{
		std::lock_guard<std::mutex> resourceGuard(m_mutex);
		
		m_internal.dragOver = false;
		
		m_internal.droppedTexts.push_back({ text, pos, Time::GetMillisec() });
	}
	
	void CDragDrop_macOS::internal_filePathsDropped(const Array<FilePath>& paths, const Point& pos)
	{
		std::lock_guard<std::mutex> resourceGuard(m_mutex);
		
		m_internal.dragOver = false;

		const uint64 timeMillisec = Time::GetMillisec();
		
		for (const auto& path : paths)
		{
			m_internal.droppedFilePaths.push_back({ path, pos, timeMillisec });
		}
	}
}

# endif
