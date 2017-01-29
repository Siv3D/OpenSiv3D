//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include "../Siv3DEngine.hpp"
# include "../Window/IWindow.hpp"
# include "CDragDrop_Linux.hpp"
//# include "../Siv3D_Linux.h"
# include <Siv3D/Time.hpp>
# include <Siv3D/FileSystem.hpp>

extern "C"
{
	using namespace s3d;

	CDragDrop_Linux* pDragDrop = nullptr;
	
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
	
	void s3d_DraggingExited()
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
			pDragDrop->internal_textDropped(CharacterSet::Widen(text), Point(x, y));
		}
	}
	
	void s3d_FilePathsDropped(int count, const char** paths, int x, int y)
	{
		if (pDragDrop)
		{
			Array<FilePath> results(count);
			
			for (int32 i = 0; i < count; ++i)
			{
				results[i] = FileSystem::FullPath(CharacterSet::Widen(paths[i]));
			}
			
			pDragDrop->internal_filePathsDropped(results, Point(x, y));
		}
	}
}

namespace s3d
{
	CDragDrop_Linux::CDragDrop_Linux()
	{
		pDragDrop = this;
	}

	CDragDrop_Linux::~CDragDrop_Linux()
	{
		pDragDrop = nullptr;
	}

	bool CDragDrop_Linux::init()
	{
		return true;
	}
	
	bool CDragDrop_Linux::update()
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
	
	void CDragDrop_Linux::acceptFilePaths(bool accept)
	{
		std::lock_guard<std::mutex> resourceGuard(m_mutex);
		
		m_acceptFilePath = accept;
	}
	
	void CDragDrop_Linux::acceptText(bool accept)
	{
		std::lock_guard<std::mutex> resourceGuard(m_mutex);
		
		m_acceptText = accept;
	}
	
	Optional<DragStatus> CDragDrop_Linux::dragOver() const
	{
		if (!m_dragOver)
		{
			return none;
		}
		
		return DragStatus{ m_itemType, m_dragOverPos };
	}
	
	bool CDragDrop_Linux::hasNewFilePaths() const
	{
		return !m_droppedFilePaths.isEmpty();
	}
	
	bool CDragDrop_Linux::hasNewText() const
	{
		return !m_droppedTexts.isEmpty();
	}
	
	void CDragDrop_Linux::clear()
	{
		m_droppedFilePaths.clear();
		
		m_droppedTexts.clear();
	}
	
	Array<DroppedFilePath> CDragDrop_Linux::getDroppedFilePaths()
	{
		Array<DroppedFilePath> dropped(std::move(m_droppedFilePaths));
		
		return dropped;
	}
	
	Array<DroppedText> CDragDrop_Linux::getDroppedText()
	{
		Array<DroppedText> dropped(std::move(m_droppedTexts));
		
		return dropped;
	}
	
	void CDragDrop_Linux::internal_entered(const bool isFilePath, const Point& pos)
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
	
	void CDragDrop_Linux::internal_updated(const Point& pos)
	{
		std::lock_guard<std::mutex> resourceGuard(m_mutex);
		
		m_internal.dragOverPos = pos;
	}
	
	void CDragDrop_Linux::internal_exited()
	{
		std::lock_guard<std::mutex> resourceGuard(m_mutex);
		
		m_internal.dragOver = false;
	}
	
	void CDragDrop_Linux::internal_textDropped(const String& text, const Point& pos)
	{
		std::lock_guard<std::mutex> resourceGuard(m_mutex);
		
		m_internal.dragOver = false;
		
		m_internal.droppedTexts.push_back({ text, pos, Time::GetMillisec() });
	}
	
	void CDragDrop_Linux::internal_filePathsDropped(const Array<FilePath>& paths, const Point& pos)
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
