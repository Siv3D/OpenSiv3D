//-----------------------------------------------
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
# if defined(SIV3D_TARGET_LINUX)

# include "../Siv3DEngine.hpp"
# include "../Window/IWindow.hpp"
# include "CDragDrop_Linux.hpp"
# include "../Siv3D_Linux.h"
# include <Siv3D/Time.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Logger.hpp>

extern "C"
{
	using namespace s3d;

	CDragDrop_Linux* pDragDrop = nullptr;
	
	void s3d_DraggingEntered(bool isFilePath)
	{
		if (pDragDrop)
		{
			pDragDrop->internal_entered(isFilePath, Cursor::Pos());
		}
	}
	
	void s3d_DraggingUpdated()
	{
		if (pDragDrop)
		{
			pDragDrop->internal_updated(Cursor::Pos());
		}
	}
	
	void s3d_DraggingExited()
	{
		if (pDragDrop)
		{
			pDragDrop->internal_exited();
		}
	}
	
	void s3d_DataDropped(const char* text)
	{
		if (pDragDrop)
		{
			pDragDrop->internal_dataDropped(Unicode::Widen(text), Cursor::Pos());
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
		LOG_INFO(U"ℹ️ DragDrop initialized");

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
	
	void CDragDrop_Linux::internal_dataDropped(const String& text, const Point& pos)
	{
		if (m_internal.itemType == DragItemType::Text)
		{
			std::lock_guard<std::mutex> resourceGuard(m_mutex);

			m_internal.dragOver = false;

			m_internal.droppedTexts.push_back({ text, pos, Time::GetMillisec() });
		}
		if (m_internal.itemType == DragItemType::FilePaths)
		{
			Array<FilePath> paths = text.split(U'\n');
			auto itr = paths.begin();
			while (itr != paths.end())
			{
				(*itr).trim();
				if ((*itr).isEmpty() || (*itr)[0] == U'#')
				{
					itr = paths.erase(itr);
				}
				else
				{
					(*itr).erase(0, 7); // erase "file://"
					itr++;
				}
			}
			
			std::lock_guard<std::mutex> resourceGuard(m_mutex);

			m_internal.dragOver = false;

			const uint64 timeMillisec = Time::GetMillisec();

			for (const auto& path : paths)
			{
				m_internal.droppedFilePaths.push_back({ path, pos, timeMillisec });
			}
		}
	}
}

# endif
