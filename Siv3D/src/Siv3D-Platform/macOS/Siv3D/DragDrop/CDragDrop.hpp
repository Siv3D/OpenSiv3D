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
# include <Siv3D/DragDrop/IDragDrop.hpp>

namespace s3d
{
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
		
		//
		//	macOS
		//
		
		void internal_entered(bool isFilePath, const Point& pos);
		
		void internal_updated(const Point& pos);
		
		void internal_exited();
		
		void internal_textDropped(const String& text, const Point& pos);
		
		void internal_filePathsDropped(const Array<FilePath>& paths, const Point& pos);

	private:

		std::mutex m_mutex;
		
		struct Internal
		{
			Array<DroppedFilePath> droppedFilePaths;
			
			Array<DroppedText> droppedTexts;
			
			DragItemType itemType = DragItemType::FilePaths;
			
			Point dragOverPos = Point::Zero();
			
			bool dragOver = false;
			
		} m_internal;
		
		Array<DroppedFilePath> m_droppedFilePaths;
		
		Array<DroppedText> m_droppedTexts;
		
		DragItemType m_itemType = DragItemType::FilePaths;
		
		Point m_dragOverPos = Point::Zero();
		
		bool m_dragOver = false;
		
		bool m_acceptFilePath = true;
		
		bool m_acceptText = false;
	};
}
