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

# include <Siv3D/DragDrop.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/DragDrop/IDragDrop.hpp>

namespace s3d
{
	namespace DragDrop
	{
		void AcceptFilePaths(const bool accept)
		{
			SIV3D_ENGINE(DragDrop)->acceptFilePaths(accept);
		}

		void AcceptText(const bool accept)
		{
			SIV3D_ENGINE(DragDrop)->acceptText(accept);
		}

		Optional<DragStatus> DragOver()
		{
			return SIV3D_ENGINE(DragDrop)->dragOver();
		}

		bool HasNewFilePaths()
		{
			return SIV3D_ENGINE(DragDrop)->hasNewFilePaths();
		}

		bool HasNewText()
		{
			return SIV3D_ENGINE(DragDrop)->hasNewText();
		}

		void Clear()
		{
			SIV3D_ENGINE(DragDrop)->clear();
		}

		Array<DroppedFilePath> GetDroppedFilePaths()
		{
			return SIV3D_ENGINE(DragDrop)->getDroppedFilePaths();
		}

		Array<DroppedText> GetDroppedText()
		{
			return SIV3D_ENGINE(DragDrop)->getDroppedText();
		}
	}

# if SIV3D_PLATFORM(WINDOWS)

	namespace Platform::Windows::DragDrop
	{
		void MakeDragDrop(const FilePathView path)
		{
			const Array<FilePath> paths = { FilePath{ path } };

			SIV3D_ENGINE(DragDrop)->makeDragDrop(paths);
		}

		void MakeDragDrop(const Array<FilePath>& paths)
		{
			SIV3D_ENGINE(DragDrop)->makeDragDrop(paths);
		}
	}

# endif
}
