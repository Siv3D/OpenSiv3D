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
# include <Siv3D/Common.hpp>
# include <Siv3D/DragDrop.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DDragDrop
	{
	public:

		static ISiv3DDragDrop* Create();

		virtual ~ISiv3DDragDrop() = default;

		virtual void init() = 0;

		virtual void update() = 0;

		virtual void acceptFilePaths(bool accept) = 0;

		virtual void acceptText(bool accept) = 0;

		virtual Optional<DragStatus> dragOver() const = 0;

		virtual bool hasNewFilePaths() const = 0;

		virtual bool hasNewText() const = 0;

		virtual void clear() = 0;

		virtual Array<DroppedFilePath> getDroppedFilePaths() = 0;

		virtual Array<DroppedText> getDroppedText() = 0;

		virtual void makeDragDrop(const Array<FilePath>& paths) = 0;
	};
}
