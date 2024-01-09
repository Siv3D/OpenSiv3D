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
# include "PointVector.hpp"
# include "Scene.hpp"
# include "Easing.hpp"

namespace s3d
{
	/// @brief 軌跡
	class Trail
	{
	public:

		/// @brief サイズを計算する関数のポインタ型
		using ScaleFunction = double (*)(double);

		/// @brief アルファ値を計算する関数のポインタ型
		using AlphaFunction = double (*)(double);

		/// @brief アクティブな点の最大数
		static constexpr size_t MaxPointCount = (1 << 8);

		/// @brief 軌跡の点情報
		struct Point
		{
			/// @brief 位置
			Float2 pos;

			/// @brief 残り寿命（秒）
			float lifeTime;

			/// @brief サイズの半分
			float halfThickness;

			/// @brief 色
			Float4 color;
		};

		/// @brief 軌跡を作成します。
		/// @param lifeTime 点の基本寿命（秒）
		/// @param scaleFunc 残り寿命 0.0 ～ 1.0 を受け取り、点のスケールを返す関数
		/// @param alphaFunc 残り寿命 0.0 ～ 1.0 を受け取り、点のアルファ値を返す関数
		SIV3D_NODISCARD_CXX20
		explicit Trail(double lifeTime = 0.5, ScaleFunction scaleFunc = EaseInQuad, AlphaFunction alphaFunc = EaseInQuad) noexcept;

		/// @brief 点の基本寿命（秒）を設定します。
		/// @param lifeTime 点の基本寿命（秒）
		void setLifeTime(double lifeTime) noexcept;

		/// @brief 点の基本寿命（秒）を返します。
		/// @return 点の基本寿命（秒）
		[[nodiscard]]
		float getLifeTime() const noexcept;

		/// @brief 残り寿命 0.0 ～ 1.0 を受け取り、点のスケールを返す関数を設定します。
		/// @param scaleFunc 点のスケールを返す関数
		void setScaleFunction(ScaleFunction scaleFunc) noexcept;

		/// @brief 残り寿命 0.0 ～ 1.0 を受け取り、点のスケールを返す関数を返します。
		/// @return 点のスケールを返す関数
		[[nodiscard]]
		ScaleFunction getScaleFunction() const noexcept;

		/// @brief 残り寿命 0.0 ～ 1.0 を受け取り、点のアルファ値を返す関数を設定します。
		/// @param alphaFunc 点のアルファ値を返す関数
		void setAlphaFunction(AlphaFunction alphaFunc) noexcept;

		/// @brief 残り寿命 0.0 ～ 1.0 を受け取り、点のアルファ値を返す関数を返します。
		/// @return 点のアルファ値を返す関数
		[[nodiscard]]
		AlphaFunction getAlphaFunction() const noexcept;

		/// @brief 軌跡に含まれるアクティブな点の個数を返します。
		/// @return 軌跡に含まれるアクティブな点の個数
		size_t num_points() const noexcept;

		/// @brief 軌跡に点を追加します。
		/// @param pos 位置
		/// @param color 色
		/// @param size サイズ
		/// @remark 末尾と位置が同じ場合、点は追加せず末尾の点を更新します。
		/// @remark 軌跡に含まれるアクティブな点の個数が MaxPointCount を超えた場合、古い点から削除されます。
		void add(const Float2& pos, const ColorF& color, double size);

		/// @brief 軌跡を更新します。
		/// @param deltaTime 前回の更新から経過した時間（秒）
		/// @remark 各点の残り寿命を更新し、寿命が尽きた点を削除します。
		void update(double deltaTime = Scene::DeltaTime()) noexcept;

		/// @brief 軌跡を消去します。
		/// @remark 軌跡に含まれるアクティブな点をすべて削除します。
		void clear() noexcept;

		/// @brief アクティブな先頭の点（最も古い点）を返します。
		/// @return アクティブな先頭の点
		/// @remark アクティブな点がない場合に呼び出してはいけません。
		[[nodiscard]]
		const Point& front() const noexcept;

		/// @brief アクティブな末尾の点（最も新しい点）を返します。
		/// @return アクティブな末尾の点
		/// @remark アクティブな点がない場合に呼び出してはいけません。
		[[nodiscard]]
		const Point& back() const noexcept;

		/// @brief アクティブな点を返します。
		/// @param index 点のインデックス
		/// @return アクティブな点
		/// @remark index は 0 以上 `num_points()` 未満である必要があります。
		[[nodiscard]]
		const Point& point(size_t index) const noexcept;

		/// @brief 軌跡を描画します。
		void draw() const;

		/// @brief 軌跡を描画します。
		/// @param texture テクスチャ
		void draw(const Texture& texture) const;

	private:

		class RingBuffer
		{
		public:

			RingBuffer();

			[[nodiscard]]
			bool isEmpty() const noexcept;

			[[nodiscard]]
			bool isFull() const noexcept;

			[[nodiscard]]
			size_t size() const noexcept;

			void push(const Point& point) noexcept;

			void update(float deltaTime) noexcept;

			void clear() noexcept;

			[[nodiscard]]
			const Point& front() const noexcept;

			[[nodiscard]]
			const Point& back() const noexcept;

			[[nodiscard]]
			Point& back() noexcept;

			[[nodiscard]]
			const Point& point(size_t index) const noexcept;

		private:

			void pop_front_non_empty() noexcept;

			static constexpr size_t MaxPoints = (1 << 8);

			static constexpr size_t PointMask = (MaxPoints - 1);

			static_assert(MaxPointCount == MaxPoints);

			Array<Point> m_points;

			size_t m_startIndex = 0;

			size_t m_size = 0;

		} m_ringBuffer;

		float m_baseLifeTime = 0.5f;

		ScaleFunction m_scaleFunc = EaseInQuad;

		AlphaFunction m_alphaFunc = EaseInQuad;
	};
}
