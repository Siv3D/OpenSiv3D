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

# include "../Siv3DEngine.hpp"
# include "IDragDrop.hpp"
# include <Siv3D/DragDrop.hpp>
# include <Siv3D/Optional.hpp>

namespace s3d
{
	namespace DragDrop
	{
		void AcceptFilePaths(const bool accept)
		{
			Siv3DEngine::GetDragDrop()->acceptFilePaths(accept);
		}

		void AcceptText(const bool accept)
		{
			Siv3DEngine::GetDragDrop()->acceptText(accept);
		}

		Optional<DragStatus> DragOver()
		{
			return Siv3DEngine::GetDragDrop()->dragOver();
		}

		bool HasNewFilePaths()
		{
			return Siv3DEngine::GetDragDrop()->hasNewFilePaths();
		}

		bool HasNewText()
		{
			return Siv3DEngine::GetDragDrop()->hasNewText();
		}

		void Clear()
		{
			Siv3DEngine::GetDragDrop()->clear();
		}

		Array<DroppedFilePath> GetDroppedFilePaths()
		{
			return Siv3DEngine::GetDragDrop()->getDroppedFilePaths();
		}

		Array<DroppedText> GetDroppedText()
		{
			return Siv3DEngine::GetDragDrop()->getDroppedText();
		}
	}
}
