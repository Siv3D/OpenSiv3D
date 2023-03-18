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
# include "IImageEncoder.hpp"
# include <Siv3D/IImageEncoder.hpp>
# include <Siv3D/Array.hpp>

namespace s3d
{
	class CImageEncoder final : public ISiv3DImageEncoder
	{
	private:

		Array<std::unique_ptr<IImageEncoder>> m_encoders;

		Array<std::unique_ptr<IImageEncoder>>::const_iterator findEncoder(StringView encoderName) const;

	public:

		CImageEncoder() = default;

		~CImageEncoder();

		void init() override;

		String getEncoderNameFromExtension(StringView extension) const override;

		bool save(const Image& image, StringView encoderName, FilePathView path) const override;

		bool encode(const Image& image, StringView encoderName, IWriter& writer) const override;

		Blob encode(const Image& image, StringView encoderName) const override;

		bool add(std::unique_ptr<IImageEncoder>&& encoder) override;

		void remove(StringView name) override;

		const Array<std::unique_ptr<IImageEncoder>>& enumEncoder() const noexcept override;
	};
}
