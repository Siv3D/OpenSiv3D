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
# include <functional>
# include "Fwd.hpp"

namespace s3d
{
	enum class FillMode : uint8
	{
		Wireframe = 2,
		
		Solid = 3,
	};

	enum class CullMode : uint8
	{
		None = 1,
		
		Front = 2,
		
		Back = 3,
	};

	/// <summary>
	/// ラスタライザーステート
	/// </summary>
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

		using StorageType = uint64;

		S3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			struct
			{
				/// <summary>
				/// 面の塗りつぶし方法
				/// </summary>
				FillMode fillMode : 2;

				/// <summary>
				/// カリングの基準
				/// </summary>
				CullMode cullMode : 2;

				/// <summary>
				/// シザーテストを有効にするかどうかを示します。 
				/// </summary>
				bool scissorEnable : 2;

				/// <summary>
				/// アンチエイリアスされた Line3D 描画
				/// </summary>
				bool antialiasedLine3D : 2;

				/// <summary>
				/// デプスのバイアス
				/// </summary>
				int32 depthBias;
			};

			StorageType _data;
		};

		S3D_DISABLE_MSVC_WARNINGS_POP()

		explicit RasterizerState(
			FillMode _fillMode = FillMode::Solid,
			CullMode _cullMode = CullMode::Back,
			bool _scissorEnable = false,
			bool _antialiasedLine3D = false,
			int32 _depthBias = 0
		)
			: fillMode(_fillMode)
			, cullMode(_cullMode)
			, scissorEnable(_scissorEnable)
			, antialiasedLine3D(_antialiasedLine3D)
			, depthBias(_depthBias) {}

		RasterizerState(Predefined predefined);

		bool operator ==(const RasterizerState& b) const noexcept
		{
			return _data == b._data;
		}

		bool operator !=(const RasterizerState& b) const noexcept
		{
			return _data != b._data;
		}

		/// <summary>
		/// ソリッド表示、裏向きの面をカリング
		/// RasterizerState{ FillMode::Solid, CullMode::Back }
		/// </summary>
		static const Predefined SolidCullBack = Predefined::SolidCullBack;

		/// <summary>
		/// ソリッド表示、表向きの面をカリング
		/// RasterizerState{ FillMode::Solid, CullMode::Front }
		/// </summary>
		static const Predefined SolidCullFront = Predefined::SolidCullFront;

		/// <summary>
		/// ソリッド表示、カリングなし
		/// RasterizerState{ FillMode::Solid, CullMode::None }
		/// </summary>
		static const Predefined SolidCullNone = Predefined::SolidCullNone;

		/// <summary>
		/// ワイヤフレーム表示、裏向きの面をカリング
		/// RasterizerState{ FillMode::Wireframe, CullMode::Back }
		/// </summary>
		static const Predefined WireframeCullBack = Predefined::WireframeCullBack;

		/// <summary>
		/// ワイヤフレーム表示、表向きの面をカリング
		/// RasterizerState{ FillMode::Wireframe, CullMode::Front }
		/// </summary>
		static const Predefined WireframeCullFront = Predefined::WireframeCullFront;

		/// <summary>
		/// ワイヤフレーム表示、カリングなし
		/// RasterizerState{ FillMode::Wireframe, CullMode::None }
		/// </summary>
		static const Predefined WireframeCullNone = Predefined::WireframeCullNone;

		/// <summary>
		/// アンチエイリアスされた Line3D 描画
		/// RasterizerState{ FillMode::Solid, CullMode::None, false, true }
		/// </summary>
		static const Predefined AntialiasedLine3D = Predefined::AntialiasedLine3D;

		/// <summary>
		/// ソリッド表示、裏向きの面をカリング、シザーテスト
		/// RasterizerState{ FillMode::Solid, CullMode::Back, true }
		/// </summary>
		static const Predefined SolidCullBackScissor = Predefined::SolidCullBackScissor;

		/// <summary>
		/// ソリッド表示、表向きの面をカリング、シザーテスト
		/// RasterizerState{ FillMode::Solid, CullMode::Front, true }
		/// </summary>
		static const Predefined SolidCullFrontScissor = Predefined::SolidCullFrontScissor;

		/// <summary>
		/// ソリッド表示、カリングなし、シザーテスト
		/// RasterizerState{ FillMode::Solid, CullMode::None, true }
		/// </summary>
		static const Predefined SolidCullNoneScissor = Predefined::SolidCullNoneScissor;

		/// <summary>
		/// ワイヤフレーム表示、裏向きの面をカリング、シザーテスト
		/// RasterizerState{ FillMode::Wireframe, CullMode::Back, true }
		/// </summary>
		static const Predefined WireframeCullBackScissor = Predefined::WireframeCullBackScissor;

		/// <summary>
		/// ワイヤフレーム表示、表向きの面をカリング、シザーテスト
		/// RasterizerState{ FillMode::Wireframe, CullMode::Front, true }
		/// </summary>
		static const Predefined WireframeCullFrontScissor = Predefined::WireframeCullFrontScissor;

		/// <summary>
		/// ワイヤフレーム表示、カリングなし、シザーテスト
		/// RasterizerState{ FillMode::Wireframe, CullMode::None, true }
		/// </summary>
		static const Predefined WireframeCullNoneScissor = Predefined::WireframeCullNoneScissor;
		
		/// <summary>
		/// アンチエイリアスされた Line3D 描画、シザーテスト
		/// RasterizerState{ FillMode::Solid, CullMode::None, true, true }
		/// </summary>
		static const Predefined AntialiasedLine3DScissor = Predefined::AntialiasedLine3DScissor;

		/// <summary>
		/// 2D 描画時のデフォルト
		/// RasterizerState::SolidNone
		/// </summary>
		static const Predefined Default2D = Predefined::Default2D;

		/// <summary>
		/// 3D 描画時のデフォルト
		/// RasterizerState::SolidBack
		/// </summary>
		static const Predefined Default3D = Predefined::Default3D;
	};

	static_assert(sizeof(RasterizerState) == sizeof(RasterizerState::StorageType));
}

namespace std
{
	template <>
	struct hash<s3d::RasterizerState>
	{
		size_t operator()(const s3d::RasterizerState& keyVal) const
		{
			return hash<s3d::RasterizerState::StorageType>()(keyVal._data);
		}
	};
}
