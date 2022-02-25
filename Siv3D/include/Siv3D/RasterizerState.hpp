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

namespace s3d
{
	enum class FillMode : uint8
	{
		Wireframe = 2,
		
		Solid = 3,
	};

	enum class CullMode : uint8
	{
		Off = 1,
		
		Front = 2,
		
		Back = 3,
	};

	/// @brief ラスタライザーステート
	struct RasterizerState
	{
	private:

		enum class Predefined
		{
			SolidCullBack,
			
			SolidCullFront,
			
			SolidCullNone,
			
			WireframeCullBack,
			
			WireframeCullFront,
			
			WireframeCullNone,
			
			AntialiasedLine3D,

			SolidCullBackScissor,

			SolidCullFrontScissor,

			SolidCullNoneScissor,

			WireframeCullBackScissor,

			WireframeCullFrontScissor,

			WireframeCullNoneScissor,

			AntialiasedLine3DScissor,
			
			Default2D = SolidCullNone,
			
			Default3D = SolidCullBack,
		};

	public:

		using storage_type = uint64;

		/// @brief 面の塗りつぶし方法
		FillMode fillMode : 2	= FillMode::Solid;

		/// @brief カリングの基準
		CullMode cullMode : 2	= CullMode::Back;

		/// @brief シザーテストの有効無効
		bool scissorEnable : 2	= false;

		/// @brief アンチエイリアスされた Line3D 描画
		bool antialiasedLine3D : 2	= false;

		/// @brief 深度バイアス
		int32 depthBias	= 0;

		SIV3D_NODISCARD_CXX20
		explicit constexpr RasterizerState(
			FillMode _fillMode = FillMode::Solid,
			CullMode _cullMode = CullMode::Back,
			bool _scissorEnable = false,
			bool _antialiasedLine3D = false,
			int32 _depthBias = 0
		);

		SIV3D_NODISCARD_CXX20
		constexpr RasterizerState(Predefined predefined) noexcept;

		[[nodiscard]]
		storage_type asValue() const noexcept;

		[[nodiscard]]
		bool operator ==(const RasterizerState& other) const noexcept;

		[[nodiscard]]
		bool operator !=(const RasterizerState& other) const noexcept;

		/// @brief ソリッド表示、裏向きの面をカリング
		/// @remark RasterizerState{ FillMode::Solid, CullMode::Back }
		static const Predefined SolidCullBack = Predefined::SolidCullBack;

		/// @brief ソリッド表示、表向きの面をカリング
		/// @remark RasterizerState{ FillMode::Solid, CullMode::Front }
		static const Predefined SolidCullFront = Predefined::SolidCullFront;

		/// @brief ソリッド表示、カリングなし
		/// @remark RasterizerState{ FillMode::Solid, CullMode::Off }
		static const Predefined SolidCullNone = Predefined::SolidCullNone;

		/// @brief ワイヤフレーム表示、裏向きの面をカリング
		/// @remark RasterizerState{ FillMode::Wireframe, CullMode::Back }
		static const Predefined WireframeCullBack = Predefined::WireframeCullBack;

		/// @brief ワイヤフレーム表示、表向きの面をカリング
		/// @remark RasterizerState{ FillMode::Wireframe, CullMode::Front }
		static const Predefined WireframeCullFront = Predefined::WireframeCullFront;

		/// @brief ワイヤフレーム表示、カリングなし
		/// @remark RasterizerState{ FillMode::Wireframe, CullMode::Off }
		static const Predefined WireframeCullNone = Predefined::WireframeCullNone;

		/// @brief アンチエイリアスされた Line3D 描画
		/// @remark RasterizerState{ FillMode::Solid, CullMode::Off, false, true }
		static const Predefined AntialiasedLine3D = Predefined::AntialiasedLine3D;

		/// @brief ソリッド表示、裏向きの面をカリング、シザーテスト
		/// @remark RasterizerState{ FillMode::Solid, CullMode::Back, true }
		static const Predefined SolidCullBackScissor = Predefined::SolidCullBackScissor;

		/// @brief ソリッド表示、表向きの面をカリング、シザーテスト
		/// @remark RasterizerState{ FillMode::Solid, CullMode::Front, true }
		static const Predefined SolidCullFrontScissor = Predefined::SolidCullFrontScissor;

		/// @brief ソリッド表示、カリングなし、シザーテスト
		/// @remark RasterizerState{ FillMode::Solid, CullMode::Off, true }
		static const Predefined SolidCullNoneScissor = Predefined::SolidCullNoneScissor;

		/// @brief ワイヤフレーム表示、裏向きの面をカリング、シザーテスト
		/// @remark RasterizerState{ FillMode::Wireframe, CullMode::Back, true }
		static const Predefined WireframeCullBackScissor = Predefined::WireframeCullBackScissor;

		/// @brief ワイヤフレーム表示、表向きの面をカリング、シザーテスト
		/// @remark RasterizerState{ FillMode::Wireframe, CullMode::Front, true }
		static const Predefined WireframeCullFrontScissor = Predefined::WireframeCullFrontScissor;

		/// @brief ワイヤフレーム表示、カリングなし、シザーテスト
		/// @remark RasterizerState{ FillMode::Wireframe, CullMode::Off, true }
		static const Predefined WireframeCullNoneScissor = Predefined::WireframeCullNoneScissor;

		/// @brief アンチエイリアスされた Line3D 描画、シザーテスト
		/// @remark RasterizerState{ FillMode::Solid, CullMode::Off, true, true }
		static const Predefined AntialiasedLine3DScissor = Predefined::AntialiasedLine3DScissor;

		/// @brief 2D 描画時のデフォルト
		/// @remark RasterizerState::SolidNone
		static const Predefined Default2D = Predefined::Default2D;

		/// @brief 3D 描画時のデフォルト
		/// @remark RasterizerState::SolidBack
		static const Predefined Default3D = Predefined::Default3D;
	};
	static_assert(sizeof(RasterizerState) == sizeof(RasterizerState::storage_type));
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

template <>
struct std::hash<s3d::RasterizerState>
{
	[[nodiscard]]
	size_t operator ()(const s3d::RasterizerState& value) const noexcept
	{
		return hash<s3d::RasterizerState::storage_type>()(value.asValue());
	}
};

# include "detail/RasterizerState.ipp"
