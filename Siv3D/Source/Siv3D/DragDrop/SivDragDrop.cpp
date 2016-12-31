//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../Siv3DEngine.hpp"
# include "IDragDrop.hpp"
# include <Siv3D/DragDrop.hpp>

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

		Array<DroppedText> GetDroppedTexts()
		{
			return Siv3DEngine::GetDragDrop()->getDroppedTexts();
		}
	}
}
