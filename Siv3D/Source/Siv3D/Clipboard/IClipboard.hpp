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
# include <utility>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Array.hpp>

namespace s3d
{
	class ISiv3DClipboard
	{
	public:

		static ISiv3DClipboard* Create();

		virtual ~ISiv3DClipboard() = default;

		virtual bool init() = 0;

		virtual void update() = 0;

		virtual bool hasChanged() = 0;

		virtual bool hasText() = 0;

		virtual bool hasImage() = 0;

		virtual bool hasFilePaths() = 0;

		virtual const String& getText() = 0;

		virtual const Image& getImage() = 0;

		virtual const Array<FilePath>& getFilePaths() = 0;

		virtual void setText(const String& text) = 0;

		virtual void setImage(const Image& image) = 0;

		virtual void clear() = 0;
	};
}
