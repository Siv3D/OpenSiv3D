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

# include <Siv3DEngine.hpp>
# include <Siv3D/DragDrop.hpp>
# include <Siv3D/Optional.hpp>
# include "IDragDrop.hpp"

namespace s3d
{
	namespace DragDrop
	{
		void AcceptFilePaths(const bool accept)
		{
			Siv3DEngine::Get<ISiv3DDragDrop>()->acceptFilePaths(accept);
		}

		void AcceptText(const bool accept)
		{
			Siv3DEngine::Get<ISiv3DDragDrop>()->acceptText(accept);
		}

		Optional<DragStatus> DragOver()
		{
			return Siv3DEngine::Get<ISiv3DDragDrop>()->dragOver();
		}

		bool HasNewFilePaths()
		{
			return Siv3DEngine::Get<ISiv3DDragDrop>()->hasNewFilePaths();
		}

		bool HasNewText()
		{
			return Siv3DEngine::Get<ISiv3DDragDrop>()->hasNewText();
		}

		void Clear()
		{
			Siv3DEngine::Get<ISiv3DDragDrop>()->clear();
		}

		Array<DroppedFilePath> GetDroppedFilePaths()
		{
			return Siv3DEngine::Get<ISiv3DDragDrop>()->getDroppedFilePaths();
		}

		Array<DroppedText> GetDroppedText()
		{
			return Siv3DEngine::Get<ISiv3DDragDrop>()->getDroppedText();
		}
	}

# if defined(SIV3D_TARGET_WINDOWS)

	namespace Platform::Windows::DragDrop
	{
		Optional<int32> MakeDragDrop(const FilePath& path)
		{
			return Siv3DEngine::Get<ISiv3DDragDrop>()->makeDragDrop(path);
		}
	}

# endif
}
