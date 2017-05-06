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
				/// アンリエイリアスされた Line3D 描画
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

		RasterizerState(Predefined predefined)
		{
			static const RasterizerState predefinedStates[7] =
			{
				RasterizerState{ FillMode::Solid,		CullMode::Back },	// SolidCullBack
				RasterizerState{ FillMode::Solid,		CullMode::Front },	// SolidCullFront
				RasterizerState{ FillMode::Solid,		CullMode::None },	// SolidCullNone
				RasterizerState{ FillMode::Wireframe,	CullMode::Back },	// WireframeCullBack
				RasterizerState{ FillMode::Wireframe,	CullMode::Front },	// WireframeCullFront
				RasterizerState{ FillMode::Wireframe,	CullMode::None },	// WireframeCullNone
				RasterizerState{ FillMode::Solid,		CullMode::None, false, true }, // AntialiasedLine3D
			};

			*this = predefinedStates[static_cast<size_t>(predefined)];
		}

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

		static const Predefined AntialiasedLine3D = Predefined::AntialiasedLine3D;

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
