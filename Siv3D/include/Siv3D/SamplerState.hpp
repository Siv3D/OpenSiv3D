//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# if  __has_include(<bit>)
#	include <bit>
# endif
# include <cstring>
# include <functional>
# include "Common.hpp"
# include "Utility.hpp"
# include "PointVector.hpp"
# include "TextureFilter.hpp"

namespace s3d
{
	/// @brief テクスチャアドレスモード
	enum class TextureAddressMode : uint8
	{
		/// @brief 繰り返し
		Repeat,

		/// @brief ミラーで繰り返し
		Mirror,

		/// @brief 繰り返しなし
		Clamp,

		/// @brief 繰り返しなしで範囲外は境界色
		Border,
	};

	/// @brief サンプラーステート
	struct SamplerState
	{
	private:

		enum class Predefined
		{
			RepeatNearest,
			
			RepeatLinear,
			
			RepeatAniso,
			
			MirrorNearest,
			
			MirrorLinear,
			
			MirrorAniso,
			
			ClampNearest,
			
			ClampLinear,
			
			ClampAniso,

			BorderNearest,

			BorderLinear,

			BorderAniso,
			
			Default2D = ClampLinear,
			
			Default3D = RepeatAniso,
		};

	public:

		static constexpr uint32 MaxSamplerCount = 8;

		static constexpr uint32 DefaultMaxAnisotropy = 4;

		using storage_type = std::array<uint32, 6>;

		TextureAddressMode addressU : 4 = TextureAddressMode::Clamp;

		TextureAddressMode addressV : 4 = TextureAddressMode::Clamp;

		TextureAddressMode addressW : 4 = TextureAddressMode::Clamp;

		TextureFilter min : 1	= TextureFilter::Linear;

		TextureFilter mag : 1	= TextureFilter::Linear;

		TextureFilter mip : 1	= TextureFilter::Linear;

		uint8 maxAnisotropy		= 1;

		float lodBias			= 0.0f;

		Float4 borderColor		= Float4{ 0, 0, 0, 0 };

		SIV3D_NODISCARD_CXX20
		explicit constexpr SamplerState(
			TextureAddressMode address,
			TextureFilter filter,
			uint8 _maxAnisotropy = 1,
			float _lodBias = 0.0f,
			Float4 _borderColor = Float4{ 0, 0, 0, 0 }) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr SamplerState(
			TextureAddressMode _addressU = TextureAddressMode::Clamp,
			TextureAddressMode _addressV = TextureAddressMode::Clamp,
			TextureAddressMode _addressW = TextureAddressMode::Clamp,
			TextureFilter _min = TextureFilter::Linear,
			TextureFilter _mag = TextureFilter::Linear,
			TextureFilter _mip = TextureFilter::Linear,
			uint8 _maxAnisotropy = 1,
			float _lodBias = 0.0f,
			Float4 _borderColor = Float4{ 0, 0, 0, 0 }) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr SamplerState(Predefined predefined) noexcept;

		[[nodiscard]]
		storage_type asValue() const noexcept;

		[[nodiscard]]
		bool operator ==(const SamplerState& other) const noexcept;

		[[nodiscard]]
		bool operator !=(const SamplerState& other) const noexcept;

		static constexpr Predefined RepeatNearest = Predefined::RepeatNearest;

		static constexpr Predefined RepeatLinear = Predefined::RepeatLinear;

		static constexpr Predefined RepeatAniso = Predefined::RepeatAniso;

		static constexpr Predefined MirrorNearest = Predefined::MirrorNearest;

		static constexpr Predefined MirrorLinear = Predefined::MirrorLinear;

		static constexpr Predefined MirrorAniso = Predefined::MirrorAniso;

		static constexpr Predefined ClampNearest = Predefined::ClampNearest;

		static constexpr Predefined ClampLinear = Predefined::ClampLinear;

		static constexpr Predefined ClampAniso = Predefined::ClampAniso;

		static constexpr Predefined BorderNearest = Predefined::BorderNearest;

		static constexpr Predefined BorderLinear = Predefined::BorderLinear;

		static constexpr Predefined BorderAniso = Predefined::BorderAniso;

		/// @brief 2D 描画時のデフォルト
		static constexpr Predefined Default2D = Predefined::Default2D;

		/// @brief 3D 描画時のデフォルト
		static constexpr Predefined Default3D = Predefined::Default3D;
	};
	static_assert(sizeof(SamplerState) == sizeof(SamplerState::storage_type));
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

template <>
struct std::hash<s3d::SamplerState>
{
	[[nodiscard]]
	size_t operator ()(const s3d::SamplerState& value) const noexcept
	{
		return s3d::Hash::FNV1a(&value, sizeof(value));
	}
};

# include "detail/SamplerState.ipp"
