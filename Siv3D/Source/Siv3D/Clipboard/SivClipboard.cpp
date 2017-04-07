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

		bool HasText()
		{
			return Siv3DEngine::GetClipboard()->hasText();
		}

		bool HasImage()
		{
			return Siv3DEngine::GetClipboard()->hasImage();
		}

		bool HasFilePaths()
		{
			return Siv3DEngine::GetClipboard()->hasFilePaths();
		}

		const String& GetText()
		{
			return Siv3DEngine::GetClipboard()->getText();
		}

		const Image& GetImage()
		{
			return Siv3DEngine::GetClipboard()->getImage();
		}

		const Array<FilePath>& GetFilePaths()
		{
			return Siv3DEngine::GetClipboard()->getFilePaths();
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
