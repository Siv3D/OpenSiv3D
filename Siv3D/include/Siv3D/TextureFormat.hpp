//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# if  __has_include(<compare>)
#	include <compare>
# endif
# include "Common.hpp"
# include "TexturePixelFormat.hpp"
# include "StringView.hpp"

namespace s3d
{
	class TextureFormat
	{
	public:

		TextureFormat() = default;

		constexpr TextureFormat(TexturePixelFormat value) noexcept;

		[[nodiscard]]
		constexpr TexturePixelFormat value() const noexcept;

		[[nodiscard]]
		StringView name() const noexcept;

		[[nodiscard]]
		int32 DXGIFormat() const noexcept;

		[[nodiscard]]
		int32 GLInternalFormat() const noexcept;

		[[nodiscard]]
		int32 GLFormat() const noexcept;

		[[nodiscard]]
		int32 GLType() const noexcept;

		// 1 ピクセル当たりのサイズ
		[[nodiscard]]
		uint32 pixelSize() const noexcept;

		// チャンネル数
		[[nodiscard]]
		uint32 num_channels() const noexcept;

		[[nodiscard]]
		bool isSRGB() const noexcept;

	# if __cpp_impl_three_way_comparison

		[[nodiscard]]
		friend constexpr bool operator ==(TextureFormat lhs, TextureFormat rhs) noexcept
		{
			return (lhs.value() == rhs.value());
		}

		[[nodiscard]]
		friend constexpr auto operator <=>(TextureFormat lhs, TextureFormat rhs) noexcept
		{
			return (lhs.value() <=> rhs.value());
		}

	# else

		[[nodiscard]]
		friend constexpr bool operator ==(const TextureFormat& lhs, const TextureFormat& rhs) noexcept
		{
			return (lhs.m_value == rhs.m_value);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const TextureFormat& lhs, const TextureFormat& rhs) noexcept
		{
			return (lhs.m_value != rhs.m_value);
		}

		[[nodiscard]]
		friend constexpr bool operator <(const TextureFormat& lhs, const TextureFormat& rhs) noexcept
		{
			return (lhs.m_value < rhs.m_value);
		}

		[[nodiscard]]
		friend constexpr bool operator <=(const TextureFormat& lhs, const TextureFormat& rhs) noexcept
		{
			return (lhs.m_value <= rhs.m_value);
		}

		[[nodiscard]]
		friend constexpr bool operator >(const TextureFormat& lhs, const TextureFormat& rhs) noexcept
		{
			return (lhs.m_value > rhs.m_value);
		}

		[[nodiscard]]
		friend constexpr bool operator >=(const TextureFormat& lhs, const TextureFormat& rhs) noexcept
		{
			return (lhs.m_value >= rhs.m_value);
		}

	# endif

		static constexpr TexturePixelFormat Unknown = TexturePixelFormat::Unknown;

		static constexpr TexturePixelFormat R8G8B8A8_Unorm = TexturePixelFormat::R8G8B8A8_Unorm;

		static constexpr TexturePixelFormat R8G8B8A8_Unorm_SRGB = TexturePixelFormat::R8G8B8A8_Unorm_SRGB;

		static constexpr TexturePixelFormat R16G16_Float = TexturePixelFormat::R16G16_Float;

		static constexpr TexturePixelFormat R32_Float = TexturePixelFormat::R32_Float;

		static constexpr TexturePixelFormat R10G10B10A2_Unorm = TexturePixelFormat::R10G10B10A2_Unorm;

		static constexpr TexturePixelFormat R11G11B10_UFloat = TexturePixelFormat::R11G11B10_UFloat;

		static constexpr TexturePixelFormat R16G16B16A16_Float = TexturePixelFormat::R16G16B16A16_Float;

		static constexpr TexturePixelFormat R32G32_Float = TexturePixelFormat::R32G32_Float;

		static constexpr TexturePixelFormat R32G32B32A32_Float = TexturePixelFormat::R32G32B32A32_Float;

	private:

		TexturePixelFormat m_value = TexturePixelFormat::Unknown;
	};
}

# include "detail/TextureFormat.ipp"
