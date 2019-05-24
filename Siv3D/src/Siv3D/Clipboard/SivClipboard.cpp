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
# include <Siv3D/Clipboard.hpp>
# include "IClipboard.hpp"

namespace s3d
{
	namespace Clipboard
	{
		bool HasChanged()
		{
			return Siv3DEngine::Get<ISiv3DClipboard>()->hasChanged();
		}

		bool GetText(String& text)
		{
			return Siv3DEngine::Get<ISiv3DClipboard>()->getText(text);
		}

		bool GetImage(Image& image)
		{
			return Siv3DEngine::Get<ISiv3DClipboard>()->getImage(image);
		}

		bool GetFilePaths(Array<FilePath>& paths)
		{
			return Siv3DEngine::Get<ISiv3DClipboard>()->getFilePaths(paths);
		}

		void SetText(const String& text)
		{
			Siv3DEngine::Get<ISiv3DClipboard>()->setText(text);
		}

		void SetImage(const Image& image)
		{
			Siv3DEngine::Get<ISiv3DClipboard>()->setImage(image);
		}

		void Clear()
		{
			Siv3DEngine::Get<ISiv3DClipboard>()->clear();
		}
	}
}
