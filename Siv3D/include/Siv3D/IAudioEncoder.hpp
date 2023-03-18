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
# include "Common.hpp"
# include "Blob.hpp"
# include "Wave.hpp"

namespace s3d
{
	struct IAudioEncoder
	{
		virtual ~IAudioEncoder() = default;

		[[nodiscard]]
		virtual StringView name() const = 0;

		[[nodiscard]]
		virtual const Array<String>& possibleExtensions() const = 0;

		virtual bool save(const Wave& wave, FilePathView path) const = 0;

		virtual bool encode(const Wave& wave, IWriter & writer) const = 0;

		[[nodiscard]]
		virtual Blob encode(const Wave& wave) const = 0;
	};
}
