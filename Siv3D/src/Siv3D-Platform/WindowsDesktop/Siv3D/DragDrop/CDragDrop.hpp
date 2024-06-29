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

# pragma once
# include <mutex>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/DragDrop/IDragDrop.hpp>

namespace s3d
{
	namespace detail
	{
		class DropTarget;
	}

	class CDragDrop final : public ISiv3DDragDrop
	{
	public:

		CDragDrop();

		~CDragDrop() override;

		void init() override;

		void update() override;

		void acceptFilePaths(bool accept) override;

		void acceptText(bool accept) override;

		Optional<DragStatus> dragOver() const override;

		bool hasNewFilePaths() const override;

		bool hasNewText() const override;

		void clear() override;

		Array<DroppedFilePath> getDroppedFilePaths() override;

		Array<DroppedText> getDroppedText() override;

		void makeDragDrop(const Array<FilePath>& paths) override;

		void process();

	private:

		HWND m_hWnd = nullptr;

		bool m_initialized = false;

		detail::DropTarget* m_pDropTarget = nullptr;

		Array<DroppedFilePath> m_droppedFilePaths;

		Array<DroppedText> m_droppedTexts;

		DragItemType m_itemType = DragItemType::FilePaths;

		Point m_dragOverPos = Point::Zero();

		bool m_dragOver = false;

		//////////
		//
		std::mutex m_mutex;

		Array<FilePath> m_newDragPaths;
		//
		//////////
	};
}
