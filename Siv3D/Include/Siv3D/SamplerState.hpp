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
# include <array>
# include <functional>
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "Hash.hpp"

namespace s3d
{
	enum class TextureFilter : bool
	{
		Nearest,

		Linear,
	};

	/// <summary>
	/// テクスチャアドレスモード
	/// </summary>
	enum class TextureAddressMode : uint8
	{
		/// <summary>
		/// 繰り返し
		/// </summary>
		Repeat,

		/// <summary>
		/// ミラーで繰り返し
		/// </summary>
		Mirror,

		/// <summary>
		/// 繰り返しなし
		/// </summary>
		Clamp,

		/// <summary>
		/// 繰り返しなしで範囲外は境界色
		/// </summary>
		Border,
	};

	/// <summary>
	/// サンプラーステート
	/// </summary>
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
			
			Default2D = RepeatLinear,
			
			Default3D = RepeatAniso,
		};

	public:

		static constexpr uint32 MaxSamplerCount = 8;

		using StorageType = std::array<uint32, 5>;

		S3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			struct
			{
				TextureAddressMode addressU : 2;

				TextureAddressMode addressV : 2;

				TextureAddressMode addressW : 2;

				TextureFilter min : 1;

				TextureFilter mag : 1;

				TextureFilter mip : 1;

				uint8 maxAnisotropy : 7;

				// [Siv3D ToDo] HalFloat に
				int16 lodBias;

				Float4 borderColor;
			};

			StorageType _data;
		};

		S3D_DISABLE_MSVC_WARNINGS_POP()

		explicit SamplerState(
			TextureAddressMode _addressU = TextureAddressMode::Repeat,
			TextureAddressMode _addressV = TextureAddressMode::Repeat,
			TextureAddressMode _addressW = TextureAddressMode::Repeat,
			TextureFilter _min = TextureFilter::Linear,
			TextureFilter _mag = TextureFilter::Linear,
			TextureFilter _mip = TextureFilter::Linear,
			uint8 _maxAnisotropy = 1,
			int16 _lodBias = 0,
			Float4 _borderColor = Float4(0, 0, 0, 0)) noexcept
			: addressU(_addressU)
			, addressV(_addressV)
			, addressW(_addressW)
			, min(_min)
			, mag(_mag)
			, mip(_mip)
			, maxAnisotropy(_maxAnisotropy)
			, lodBias(_lodBias)
			, borderColor(_borderColor) {}

		SamplerState(Predefined predefined);

		bool operator ==(const SamplerState& b) const noexcept
		{
			return _data == b._data;
		}

		bool operator !=(const SamplerState& b) const noexcept
		{
			return _data != b._data;
		}

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined RepeatNearest = Predefined::RepeatNearest;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined RepeatLinear = Predefined::RepeatLinear;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined RepeatAniso = Predefined::RepeatAniso;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined MirrorNearest = Predefined::MirrorNearest;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined MirrorLinear = Predefined::MirrorLinear;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined MirrorAniso = Predefined::MirrorAniso;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined ClampNearest = Predefined::ClampNearest;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined ClampLinear = Predefined::ClampLinear;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined ClampAniso = Predefined::ClampAniso;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined BorderNearest = Predefined::BorderNearest;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined BorderLinear = Predefined::BorderLinear;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined BorderAniso = Predefined::BorderAniso;

		/// <summary>
		/// 2D 描画時のデフォルト
		/// SamplerState::WrapLinear
		/// </summary>
		static constexpr Predefined Default2D = Predefined::Default2D;

		/// <summary>
		/// 3D 描画時のデフォルト
		/// SamplerState::WrapAniso
		/// </summary>
		static constexpr Predefined Default3D = Predefined::Default3D;
	};

	static_assert(sizeof(SamplerState) == sizeof(SamplerState::StorageType));
}

namespace std
{
	template <>
	struct hash<s3d::SamplerState>
	{
		size_t operator()(const s3d::SamplerState& keyVal) const
		{
			return s3d::Hash::FNV1a(keyVal._data);
		}
	};
}
