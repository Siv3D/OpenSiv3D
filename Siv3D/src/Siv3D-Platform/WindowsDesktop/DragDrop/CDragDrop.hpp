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

# pragma once
# include <Siv3D/Windows.hpp>
# include <DragDrop/IDragDrop.hpp>

namespace s3d
{
	namespace detail
	{
		class DropTarget;
	}

	class CDragDrop : public ISiv3DDragDrop
	{
	private:

		HWND m_hWnd = nullptr;

		detail::DropTarget* m_pDropTarget = nullptr;

		Array<DroppedFilePath> m_droppedFilePaths;

		Array<DroppedText> m_droppedTexts;

		DragItemType m_itemType = DragItemType::FilePaths;

		Point m_dragOverPos = Point::Zero();

		bool m_dragOver = false;

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

		Optional<int32> makeDragDrop(const FilePath& path) override;
	};
}
