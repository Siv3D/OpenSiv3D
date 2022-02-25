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
# include "Common.hpp"
# include "ColorHSV.hpp"
# include "Graphics3D.hpp"
# include "Mesh.hpp"

namespace s3d
{
	/// @brief 天空レンダリングエンジン
	class Sky
	{
	public:

		/// @brief 空のてっぺんの色（リニアカラー）
		ColorF zenithColor{ 0.15, 0.24, 0.56 };

		/// @brief 地平線の色（リニアカラー）
		ColorF horizonColor{ 0.3, 0.3, 0.4 };

		/// @brief 雲の色（リニアカラー）
		ColorF cloudColor{ 1.0, 1.0, 1.0 };

		/// @brief 雲の移動に使う基準時刻
		double cloudTime = 0.0;

		/// @brief 雲量（快晴 [0.0, 1.0] 曇天）
		double cloudiness = 0.2; // [0.0, 1.0]

		/// @brief 雲のスケール
		double cloudScale = 0.5;

		/// @brief 雲の底面の高度 (m)
		double cloudPlaneHeight = 1000.0;

		/// @brief 雲が流れる方向（北 0_deg, ... 東 90_deg, ...）
		double cloudOrientation = 0_deg;

		/// @brief フォグの強さ
		double fogHeightSky = 0.0;

		/// @brief 星の可視レベル [0.0, 1.0]
		double starBrightness = 0.0;

		/// @brief 星の光の強さ [0.0, 1.0]
		double starBrightnessFactor = 1.0;

		/// @brief 星の色味の強さ [0.0, 1.0]
		double starSaturation = 0.6;

		/// @brief 天球の回転の軸
		Vec3 starRotationAxis = Vec3{ 0, 0.5, 1 }.normalized();

		/// @brief 星の移動に使う基準時刻
		double starTime = 0.0;

		/// @brief 星のパターンを変えるオフセット
		Vec2 starOffset{ 0.123, 0.456 };

		/// @brief 太陽の描画を有効にするか
		bool sunEnabled = true;

		/// @brief 雲の描画を有効にするか
		bool cloudsEnabled = true;

		/// @brief 太陽の方向に基づく雲のライティングを有効にするか
		bool cloudsLightingEnabled = true;

		/// @brief 天空レンダリングエンジンを作成します。
		/// @param sphereRadius スカイスフィアの半径 (m)
		SIV3D_NODISCARD_CXX20
		explicit Sky(double sphereRadius = 8000.0);

		/// @brief 天空をレンダリングします。
		/// @param exposure 露光スケール
		/// @remark ピクセルシェーダの定数バッファ slot4 を上書きします。
		void draw(double exposure = 1.0) const;

	private:

		struct PSConstantsSky
		{
			Float3 zenithColor;
			float fogHeightSky;

			Float3 horizonColor;
			float cloudiness;

			Float3 cloudUVTransform;
			float cloudScale;

			float cloudTime;
			float cloudPlaneHeight;
			float starBrightness;
			uint32 option;

			Float3 cloudColor;
			float skyExposure;

			Float4 starsRoation[3];

			Float3 starOffset;
			float starSaturation;
		};

		Mesh m_skySphere;

		mutable ConstantBuffer<PSConstantsSky> m_constants;

		PixelShader m_pixelShader;

		PSConstantsSky toConstants(double exposure) const;
	};
}
