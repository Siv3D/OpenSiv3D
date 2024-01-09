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
# include "Common.hpp"
# include "Trail.hpp"

namespace s3d
{
	/// @brief 軌跡のモーション
	class TrailMotion
	{
	public:

		/// @brief 最小の軌跡更新間隔（Hz）
		static constexpr double MinFrequency = 1.0;

		/// @brief デフォルトの軌跡更新間隔（Hz）
		static constexpr double DefaultFrequency = 120.0;

		/// @brief 最大の軌跡更新間隔（Hz）
		static constexpr double MaxFrequency = 512.0;

		/// @brief 自動軌跡アニメーションを作成します。
		/// @param lifeTime 軌跡の基本寿命（秒）
		/// @param frequency 軌跡更新間隔（Hz）
		/// @param scaleFunc 残り寿命 0.0 ～ 1.0 を受け取り、点のスケールを返す関数
		/// @param alphaFunc 残り寿命 0.0 ～ 1.0 を受け取り、点のアルファ値を返す関数
		SIV3D_NODISCARD_CXX20
		explicit TrailMotion(double lifeTime = 0.5, double frequency = DefaultFrequency, Trail::ScaleFunction scaleFunc = EaseInQuad, Trail::AlphaFunction alphaFunc = EaseInQuad);

		/// @brief 点の基本寿命（秒）を設定します。
		/// @param lifeTime 点の基本寿命（秒）
		/// @return *this
		TrailMotion& setLifeTime(double lifeTime) noexcept;

		/// @brief 点の基本寿命（秒）を返します。
		/// @return 点の基本寿命（秒）
		[[nodiscard]]
		float getLifeTime() const noexcept;

		/// @brief 残り寿命 0.0 ～ 1.0 を受け取り、点のスケールを返す関数を設定します。
		/// @param scaleFunc 点のスケールを返す関数
		/// @return *this
		TrailMotion& setScaleFunction(Trail::ScaleFunction scaleFunc) noexcept;

		/// @brief 残り寿命 0.0 ～ 1.0 を受け取り、点のスケールを返す関数を返します。
		/// @return 点のスケールを返す関数
		[[nodiscard]]
		Trail::ScaleFunction getScaleFunction() const noexcept;

		/// @brief 残り寿命 0.0 ～ 1.0 を受け取り、点のアルファ値を返す関数を設定します。
		/// @param alphaFunc 点のアルファ値を返す関数
		/// @return *this
		TrailMotion& setAlphaFunction(Trail::AlphaFunction alphaFunc) noexcept;

		/// @brief 残り寿命 0.0 ～ 1.0 を受け取り、点のアルファ値を返す関数を返します。
		/// @return 点のアルファ値を返す関数
		[[nodiscard]]
		Trail::AlphaFunction getAlphaFunction() const noexcept;

		/// @brief 軌跡に含まれるアクティブな点の個数を返します。
		/// @return 軌跡に含まれるアクティブな点の個数
		size_t num_points() const noexcept;

		/// @brief 軌跡の更新間隔を設定します。
		/// @param frequency 更新間隔（Hz）
		/// @return *this
		TrailMotion& setFrequency(double frequency);

		/// @brief 軌跡の更新間隔（Hz）を返します。
		/// @return 軌跡の更新間隔（Hz）
		[[nodiscard]]
		double getFrequency() const noexcept;

		/// @brief 軌跡の位置オフセットを設定します。
		/// @param x 軌跡の位置オフセットの X 座標
		/// @param y 軌跡の位置オフセットの Y 座標
		/// @return *this
		/// @remark 軌跡の点は座標関数の戻り値にオフセットを足した位置に追加されます。
		/// @remark 古い点は移動しないため、全体を移動させる場合は Transformer2D を使ってください。
		TrailMotion& setCenter(double x, double y) noexcept;

		/// @brief 軌跡の位置オフセットを設定します。
		/// @param center 軌跡の位置オフセット
		/// @return *this
		/// @remark 軌跡の点は座標関数の戻り値にオフセットを足した位置に追加されます。
		/// @remark 古い点は移動しないため、全体を移動させる場合は Transformer2D を使ってください。
		TrailMotion& setCenter(const Vec2& center) noexcept;

		/// @brief 軌跡の位置オフセットを返します。
		/// @return 軌跡の位置オフセット
		[[nodiscard]]
		const Vec2& getCenter() const noexcept;

		/// @brief 時間（秒）を受け取り、点の位置を返す関数を設定します。
		/// @param positionFunction 点の位置を返す関数
		/// @return *this
		TrailMotion& setPositionFunction(const std::function<Vec2(double)>& positionFunction);

		/// @brief 時間（秒）を受け取り、点の位置を返す関数を返します。
		/// @return 点の位置を返す関数
		[[nodiscard]]
		const std::function<Vec2(double)>& getPositionFunction() const noexcept;

		/// @brief 点の色を固定色に設定します。
		/// @param color 点の色
		/// @return *this
		TrailMotion& setColor(const ColorF& color);

		/// @brief 時間（秒）を受け取り、点の色を返す関数を設定します。
		/// @param colorFunction 点の色を返す関数
		/// @return *this
		TrailMotion& setColorFunction(const std::function<ColorF(double)>& colorFunction);

		/// @brief 時間（秒）を受け取り、点の色を返す関数を返します。
		/// @return 点の色を返す関数
		[[nodiscard]]
		const std::function<ColorF(double)>& getColorFunction() const noexcept;

		/// @brief 点の大きさを固定値に設定します。
		/// @param size 点の大きさ
		/// @return *this
		TrailMotion& setSize(double size);

		/// @brief 時間（秒）を受け取り、点の大きさを返す関数を設定します。
		/// @param sizeFunction 点の大きさを返す関数
		/// @return *this
		TrailMotion& setSizeFunction(const std::function<double(double)>& sizeFunction);

		/// @brief 時間（秒）を受け取り、点の大きさを返す関数を返します。
		/// @return 点の大きさを返す関数
		[[nodiscard]]
		const std::function<double(double)>& getSizeFunction() const noexcept;

		/// @brief 軌跡のアニメーションを更新します。
		/// @param deltaTime 前回の更新から経過した時間（秒）
		void update(double deltaTime = Scene::DeltaTime());

		/// @brief 軌跡を描画します。
		void draw() const;

		/// @brief 軌跡を描画します。
		/// @param texture 軌跡のテクスチャ
		void draw(const Texture& texture) const;

		/// @brief 軌跡を消去します。
		void clear() noexcept;

	private:

		Trail m_trail;

		double m_time = 0.0;

		double m_accumulatedTime = 0.0;

		double m_frequency = DefaultFrequency;

		Vec2 m_center{ 0.0, 0.0 };

		std::function<Vec2(double)> m_positionFunction = [](double) { return Vec2{ 0, 0 }; };

		std::function<ColorF(double)> m_colorFunction = [](double) { return ColorF{ 1.0 }; };

		std::function<double(double)> m_sizeFunction = [](double) { return 20.0; };
	};
}
