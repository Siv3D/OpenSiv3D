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

# include "../Siv3DEngine.hpp"
# include "IClipboard.hpp"
# include <Siv3D/Clipboard.hpp>

namespace s3d
{
	namespace Clipboard
	{
		bool HasChanged()
		{
			return Siv3DEngine::GetClipboard()->hasChanged();
		}

		bool GetText(String& text)
		{
			return Siv3DEngine::GetClipboard()->getText(text);
		}

		bool GetImage(Image& image)
		{
			return Siv3DEngine::GetClipboard()->getImage(image);
		}

		bool GetFilePaths(Array<FilePath>& paths)
		{
			return Siv3DEngine::GetClipboard()->getFilePaths(paths);
		}

		void SetText(const String& text)
		{
			Siv3DEngine::GetClipboard()->setText(text);
		}

		void SetImage(const Image& image)
		{
			Siv3DEngine::GetClipboard()->setImage(image);
		}

		void Clear()
		{
			Siv3DEngine::GetClipboard()->clear();
		}
	}
}
