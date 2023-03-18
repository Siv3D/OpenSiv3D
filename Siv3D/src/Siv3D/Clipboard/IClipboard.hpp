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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Clipboard.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DClipboard
	{
	public:

		static ISiv3DClipboard* Create();

		virtual ~ISiv3DClipboard() = default;

		virtual void init() = 0;

		virtual bool hasChanged() = 0;

		virtual bool getText(String& text) = 0;

		virtual bool getImage(Image& image) = 0;

		virtual bool getFilePaths(Array<FilePath>& paths) = 0;

		virtual void setText(const String& text) = 0;

		virtual void setImage(const Image& image) = 0;

		virtual void clear() = 0;
	};
}
