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
# include <Siv3D/Unicode.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/Cursor.hpp>
# include "CDragDrop.hpp"

extern "C"
{
	using namespace s3d;

	CDragDrop* pDragDrop = nullptr;

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

	void s3d_DraggingExited(void)
	{
		if (pDragDrop)
		{
			pDragDrop->internal_exited();
		}
	}

	void s3d_ItemDropped(const char* text)
	{
		if (pDragDrop)
		{
			pDragDrop->internal_itemDropped(Unicode::Widen(text), Cursor::Pos());
		}
	}
}

namespace s3d
{
	CDragDrop::CDragDrop()
	{
		pDragDrop = this;
	}

	CDragDrop::~CDragDrop()
	{
		LOG_SCOPED_TRACE(U"CDragDrop::~CDragDrop()");

		pDragDrop = nullptr;
	}

	void CDragDrop::init()
	{
		LOG_SCOPED_TRACE(U"CDragDrop::init()");
	}


	void CDragDrop::update()
	{
		std::lock_guard resourceGuard{ m_mutex };

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
	}

	void CDragDrop::acceptFilePaths(const bool accept)
	{
		std::lock_guard resourceGuard{ m_mutex };

		m_acceptFilePath = accept;
	}

	void CDragDrop::acceptText(const bool accept)
	{
		std::lock_guard resourceGuard{ m_mutex };

		m_acceptText = accept;
	}

	Optional<DragStatus> CDragDrop::dragOver() const
	{
		if (not m_dragOver)
		{
			return none;
		}

		return DragStatus{ m_itemType, m_dragOverPos };
	}

	bool CDragDrop::hasNewFilePaths() const
	{
		return !m_droppedFilePaths.isEmpty();
	}

	bool CDragDrop::hasNewText() const
	{
		return !m_droppedTexts.isEmpty();
	}

	void CDragDrop::clear()
	{
		m_droppedFilePaths.clear();

		m_droppedTexts.clear();
	}

	Array<DroppedFilePath> CDragDrop::getDroppedFilePaths()
	{
		Array<DroppedFilePath> dropped(std::move(m_droppedFilePaths));

		return dropped;
	}

	Array<DroppedText> CDragDrop::getDroppedText()
	{
		Array<DroppedText> dropped(std::move(m_droppedTexts));

		return dropped;
	}

	void CDragDrop::makeDragDrop(const Array<FilePath>&)
	{
		// [Siv3D ToDo]
	}

	void CDragDrop::internal_entered(const bool isFilePath, const Point& pos)
	{
		std::lock_guard resourceGuard{ m_mutex };

		if ((!m_acceptFilePath && isFilePath) || (!m_acceptText && !isFilePath))
		{
			return;
		}

		m_internal.dragOver = true;
		m_internal.dragOverPos = pos;
		m_internal.itemType = isFilePath ? DragItemType::FilePaths : DragItemType::Text;
	}

	void CDragDrop::internal_updated(const Point& pos)
	{
		std::lock_guard resourceGuard{ m_mutex };

		m_internal.dragOverPos = pos;
	}

	void CDragDrop::internal_exited()
	{
		std::lock_guard resourceGuard{ m_mutex };

		m_internal.dragOver = false;
	}

	void CDragDrop::internal_itemDropped(const String& text, const Point& pos)
	{
		if (m_internal.itemType == DragItemType::Text)
		{
			std::lock_guard resourceGuard{ m_mutex };

			m_internal.dragOver = false;

			m_internal.droppedTexts.push_back({ text, pos, Time::GetMillisec() });
		}
		else if (m_internal.itemType == DragItemType::FilePaths)
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

			std::lock_guard resourceGuard{ m_mutex };

			m_internal.dragOver = false;

			const uint64 timeMillisec = Time::GetMillisec();

			for (const auto& path : paths)
			{
				m_internal.droppedFilePaths.push_back({ path, pos, timeMillisec });
			}
		}
	}
}
