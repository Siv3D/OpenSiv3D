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

# pragma once
# include <Siv3D/Fwd.hpp>
# include <Siv3D/DragDrop.hpp>

namespace s3d
{
	class ISiv3DDragDrop
	{
	public:

		static ISiv3DDragDrop* Create();

		virtual ~ISiv3DDragDrop() = default;

		virtual bool init() = 0;
		
		virtual bool update() = 0;

		virtual void acceptFilePaths(bool accept) = 0;

		virtual void acceptText(bool accept) = 0;

		virtual Optional<DragStatus> dragOver() const = 0;

		virtual bool hasNewFilePaths() const = 0;

		virtual bool hasNewText() const = 0;

		virtual void clear() = 0;

		virtual Array<DroppedFilePath> getDroppedFilePaths() = 0;

		virtual Array<DroppedText> getDroppedText() = 0;

		virtual Optional<int32> makeDragDrop(const FilePath& path) = 0;
	};
}
