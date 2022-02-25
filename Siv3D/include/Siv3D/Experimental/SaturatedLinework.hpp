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
// s3d::SaturatedLinework is originally created by Yuta Ishii (OpenSiv3D Project)
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Random.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/OffsetCircular.hpp>
# include <Siv3D/MathConstants.hpp>

namespace s3d
{
	/// @brief 集中線描画クラス
	/// @tparam TargetShape 集中線で囲む図形の形状を表す型
	/// @tparam URNG 使用する乱数エンジンの型
	template <class TargetShape = Ellipse, class URNG = DefaultRNG>
	class SaturatedLinework
	{
	public:

		/// @brief デフォルトコンストラクタ
		SaturatedLinework();

		/// @brief 集中線を作成します。
		/// @param targetShape 集中線の輪郭
		explicit SaturatedLinework(const TargetShape& targetShape);

		/// @brief 集中線を作成します。
		/// @param targetShape 集中線の輪郭
		/// @param outerShape 集中線の描画範囲
		SaturatedLinework(const TargetShape& targetShape, const Rect& outerShape);

		/// @brief 集中線の輪郭を設定します。
		/// @param targetShape 集中線の輪郭
		/// @return *this
		SaturatedLinework& setTargetShape(const TargetShape& targetShape);

		/// @brief 集中線の輪郭を返します。
		/// @return 集中線の輪郭
		[[nodiscard]]
		const TargetShape& getTargetShape() const noexcept;

		/// @brief 集中線の描画範囲を設定します。
		/// @param outerRect 集中線の描画範囲
		/// @return *this
		SaturatedLinework& setOuterRect(const Rect& outerRect);

		/// @brief 集中線の描画範囲を返します
		/// @return 	集中線の描画範囲
		[[nodiscard]]
		const Rect& getOuterRect() const noexcept;

		/// @brief 線の本数を設定します。
		/// @param lineCount 線の本数
		/// @return *this
		SaturatedLinework& setLineCount(size_t lineCount);

		/// @brief 線の本数を返します。
		/// @return 線の本数
		[[nodiscard]]
		size_t getLineCount() const noexcept;

		/// @brief 線が最も太くなる部分の太さの下限値を設定します。
		/// @param minThickness 最も太くなる部分の太さの下限値
		/// @return *this
		SaturatedLinework& setMinThickness(double minThickness);

		/// @brief 線の太さの下限値を返します。
		/// @return 線の太さの下限値
		[[nodiscard]]
		double getMinThickness() const noexcept;

		/// @brief 線が最も太くなる部分の太さの上限値を設定します。
		/// @param maxThickness 最も太くなる部分の太さの上限値
		/// @return *this
		SaturatedLinework& setMaxThickness(double maxThickness);

		/// @brief 線の太さの上限値を返します。
		/// @return 線の太さの上限値
		[[nodiscard]]
		double getMaxThickness() const noexcept;

		/// @brief 線の太さを設定します。
		/// @param minThickness 最も太くなる部分の太さの下限値
		/// @param maxThickness 最も太くなる部分の太さの上限値
		/// @return *this
		SaturatedLinework& setThickness(double minThickness, double maxThickness);

		/// @brief 輪郭のばらけ具合を設定します
		/// @param offsetRange ばらける範囲
		/// @return *this
		SaturatedLinework& setOffsetRange(double offsetRange);

		/// @brief 輪郭のばらけ具合を返します。
		/// @return 輪郭のばらけ具合	
		[[nodiscard]]
		double getOffsetRange() const noexcept;

		/// @brief 乱数のシード値を設定します。
		/// @param seed シード値
		/// @return *this
		SaturatedLinework& setSeed(uint64 seed);

		/// @brief 乱数のシード値を返します。
		/// @return 乱数のシード値	
		[[nodiscard]]
		uint64 getSeed() const noexcept;

		/// @brief 集中線を生成し、キャッシュします。
		void generate() const;

		/// @brief 集中線を描画します。
		/// @remark 集中線がキャッシュされていない場合、関数内で `generate()` を呼びます。
		/// @param color 集中線の色
		void draw(const ColorF& color = Palette::Black) const;

	private:

		// 内側の図形
		TargetShape m_targetShape;

		// 内側の図形
		Rect m_outerRect;

		// 線の数
		size_t m_lineCount = 70;

		// 線の太さの最小幅
		double m_minThickness = 7.0;

		// 線の太さの最大幅
		double m_maxThickness = 10.0;

		// 出現位置のランダム幅
		double m_offsetRange = 0.0;

		// 乱数エンジンのシード値
		uint64 m_seed = 12345;

		// 乱数エンジン
		mutable URNG m_rng;

		// 集中線の中身
		mutable Array<Triangle> m_triangles;

		mutable bool m_isDirty = true;

		// innerShape　が outerShape に含まれているか簡単なチェック
		template <class _TargetShape>
		[[nodiscard]]
		static bool IsValid(const _TargetShape& targetShape, const Rect& outerShape);
	};
}

# include "detail/SaturatedLinework.ipp"

/*

// example

# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.98, 0.96, 0.94 });
	const Texture texture{ U"🦀"_emoji };

	Ellipse target{ 400, 300, 180, 120 };
	Rect outer = Scene::Rect();
	double minThickness = 3.0, maxThickness = 10.0;
	double lineCount = 150;
	double offsetRange = 60.0;

	SaturatedLinework<Ellipse> linework{ target, outer };
	linework
		.setThickness(minThickness, maxThickness)
		.setLineCount(static_cast<size_t>(lineCount))
		.setOffsetRange(offsetRange);

	while (System::Update())
	{
		if (MouseR.down())
		{
			target.setCenter(Cursor::Pos());
			linework.setTargetShape(target);
		}

		texture.scaled(1.6).drawAt(target.center);

		linework.draw(ColorF{ 0.1 });

		if (SimpleGUI::Slider(U"lineCount", lineCount, 0.0, 400.0, Vec2{ 20, 20 }, 150))
		{
			linework.setLineCount(static_cast<size_t>(lineCount));
		}

		if (SimpleGUI::Slider(U"offsetRange", offsetRange, 0.0, 100.0, Vec2{ 20, 60 }, 150))
		{
			linework.setOffsetRange(offsetRange);
		}
	}
}

*/
