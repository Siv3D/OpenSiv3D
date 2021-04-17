//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "Optional.hpp"
# include "DragItemType.hpp"
# include "DragStatus.hpp"
# include "DroppedFilePath.hpp"
# include "DroppedText.hpp"

namespace s3d
{
	namespace DragDrop
	{
		void AcceptFilePaths(bool accept);

		void AcceptText(bool accept);

		[[nodiscard]]
		Optional<DragStatus> DragOver();

		[[nodiscard]]
		bool HasNewFilePaths();

		[[nodiscard]]
		bool HasNewText();

		void Clear();

		[[nodiscard]]
		Array<DroppedFilePath> GetDroppedFilePaths();

		[[nodiscard]]
		Array<DroppedText> GetDroppedText();
	}

# if SIV3D_PLATFORM(WINDOWS)

	namespace Platform::Windows::DragDrop
	{
		Optional<int32> MakeDragDrop(const FilePath& path);
	}

# endif
}
