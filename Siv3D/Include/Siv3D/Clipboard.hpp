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

# pragma once
# include "Fwd.hpp"

namespace s3d
{
	/// <summary>
	/// クリップボード
	/// </summary>
	/// <remarks>
	/// クリップボードに関する機能を提供します。
	/// </remarks>
	namespace Clipboard
	{
		bool HasChanged();

		bool HasText();

		bool HasImage();

		bool HasFilePaths();

		const String& GetText();

		const Image& GetImage();

		const Array<FilePath>& GetFilePaths();

		void SetText(const String& text);

		void SetImage(const Image& image);

		void Clear();
	}
}
