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
# include <memory>
# include "IAudioEncoder.hpp"
# include <Siv3D/IAudioEncoder.hpp>
# include <Siv3D/Array.hpp>

namespace s3d
{
	class CAudioEncoder final : public ISiv3DAudioEncoder
	{
	public:

		CAudioEncoder() = default;

		~CAudioEncoder();

		void init() override;

		String getEncoderNameFromExtension(StringView extension) const override;

		bool save(const Wave& wave, StringView encoderName, FilePathView path) const override;

		bool encode(const Wave& wave, StringView encoderName, IWriter& writer) const override;

		Blob encode(const Wave& wave, StringView encoderName) const override;

		bool add(std::unique_ptr<IAudioEncoder>&& encoder) override;

		void remove(StringView name) override;

		const Array<std::unique_ptr<IAudioEncoder>>& enumEncoder() const noexcept override;

	private:

		Array<std::unique_ptr<IAudioEncoder>> m_encoders;

		Array<std::unique_ptr<IAudioEncoder>>::const_iterator findEncoder(StringView encoderName) const;
	};
}
