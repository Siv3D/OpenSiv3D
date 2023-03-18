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
# include <Siv3D/Blob.hpp>
# include <Siv3D/IAudioEncoder.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DAudioEncoder
	{
	public:

		static ISiv3DAudioEncoder* Create();

		virtual ~ISiv3DAudioEncoder() = default;

		virtual void init() = 0;

		virtual String getEncoderNameFromExtension(StringView extension) const = 0;

		virtual bool save(const Wave& wave, StringView encoderName, FilePathView path) const = 0;

		virtual bool encode(const Wave& wave, StringView encoderName, IWriter& writer) const = 0;

		virtual Blob encode(const Wave& wave, StringView encoderName) const = 0;

		virtual bool add(std::unique_ptr<IAudioEncoder>&& Encoder) = 0;

		virtual void remove(StringView name) = 0;

		virtual const Array<std::unique_ptr<IAudioEncoder>>& enumEncoder() const noexcept = 0;
	};
}
