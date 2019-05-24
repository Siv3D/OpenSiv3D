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
# include <mutex>
# include <DragDrop/IDragDrop.hpp>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

namespace s3d
{
	class CDragDrop : public ISiv3DDragDrop
	{
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


		void internal_entered(bool isFilePath, const Point& pos);

		void internal_updated(const Point& pos);

		void internal_exited();

		void internal_textDropped(const String& text, const Point& pos);

		void internal_filePathsDropped(const Array<FilePath>& paths, const Point& pos);
	};
}
