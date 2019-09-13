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

# pragma once
# include "Fwd.hpp"
# include "StringView.hpp"

namespace s3d
{
	enum class TextureFormatValue
	{
		Unknown,

		// 32
		R8G8B8A8_Unorm,

		// 32
		R8G8B8A8_Unorm_SRGB,

		// 32
		R16G16_Float,

		// 32
		R32_Float,

		// 32
		R10G10B10A2_Unorm,

		// 32
		R11G11B10_UFloat,

		// 64
		R16G16B16A16_Float,

		// 64
		R32G32_Float,

		// 128
		R32G32B32A32_Float,
	};

	class TextureFormat
	{
	private:

		TextureFormatValue m_value = TextureFormatValue::Unknown;

	public:

		TextureFormat() = default;

		constexpr TextureFormat(TextureFormatValue value) noexcept
			: m_value(value) {}

		[[nodiscard]] constexpr TextureFormatValue value() const noexcept
		{
			return m_value;
		}

		[[nodiscard]] StringView name() const noexcept;

		[[nodiscard]] int32 DXGIFormat() const noexcept;

		[[nodiscard]] int32 GLInternalFormat() const noexcept;

		[[nodiscard]] int32 GLFormat() const noexcept;

		[[nodiscard]] int32 GLType() const noexcept;

		// 1 ピクセル当たりのサイズ
		[[nodiscard]] uint32 pixelSize() const noexcept;

		// チャンネル数
		[[nodiscard]] uint32 num_channels() const noexcept;

		[[nodiscard]] bool isSRGB() const noexcept;

		[[nodiscard]] constexpr bool operator ==(const TextureFormat& other) const noexcept
		{
			return m_value == other.m_value;
		}

		[[nodiscard]] constexpr bool operator !=(const TextureFormat& other) const noexcept
		{
			return m_value != other.m_value;
		}

		static constexpr TextureFormatValue Unknown = TextureFormatValue::Unknown;

		static constexpr TextureFormatValue R8G8B8A8_Unorm = TextureFormatValue::R8G8B8A8_Unorm;

		static constexpr TextureFormatValue R8G8B8A8_Unorm_SRGB = TextureFormatValue::R8G8B8A8_Unorm_SRGB;

		static constexpr TextureFormatValue R16G16_Float = TextureFormatValue::R16G16_Float;

		static constexpr TextureFormatValue R32_Float = TextureFormatValue::R32_Float;

		static constexpr TextureFormatValue R10G10B10A2_Unorm = TextureFormatValue::R10G10B10A2_Unorm;

		static constexpr TextureFormatValue R11G11B10_UFloat = TextureFormatValue::R11G11B10_UFloat;

		static constexpr TextureFormatValue R16G16B16A16_Float = TextureFormatValue::R16G16B16A16_Float;

		static constexpr TextureFormatValue R32G32_Float = TextureFormatValue::R32G32_Float;

		static constexpr TextureFormatValue R32G32B32A32_Float = TextureFormatValue::R32G32B32A32_Float;
	};
}
