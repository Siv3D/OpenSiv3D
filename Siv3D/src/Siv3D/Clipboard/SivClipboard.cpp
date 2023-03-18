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

# include <Siv3D/Clipboard.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Clipboard/IClipboard.hpp>

namespace s3d
{
	namespace Clipboard
	{
		bool HasChanged()
		{
			return SIV3D_ENGINE(Clipboard)->hasChanged();
		}

		bool GetText(String& text)
		{
			return SIV3D_ENGINE(Clipboard)->getText(text);
		}

		bool GetImage(Image& image)
		{
			return SIV3D_ENGINE(Clipboard)->getImage(image);
		}

		bool GetFilePaths(Array<FilePath>& paths)
		{
			return SIV3D_ENGINE(Clipboard)->getFilePaths(paths);
		}

		void SetText(const String& text)
		{
			SIV3D_ENGINE(Clipboard)->setText(text);
		}

		void SetImage(const Image& image)
		{
			SIV3D_ENGINE(Clipboard)->setImage(image);
		}

		void Clear()
		{
			SIV3D_ENGINE(Clipboard)->clear();
		}
	}
}
