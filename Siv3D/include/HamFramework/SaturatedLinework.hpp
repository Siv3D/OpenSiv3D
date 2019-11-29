//-----------------------------------------------
//
//	This file is part of the Siv3D HamFramework.
//
//	Copyright (C) 2014-2019 HAMSTRO
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------
// s3d::SaturatedLinework is originally created by Yuta Ishii (OpenSiv3D Project)
//-----------------------------------------------

# pragma once
# include <Siv3D.hpp>

namespace s3d
{
	template <class TargetShape = Ellipse, class URNG = DefaultRNGType>
	class SaturatedLinework
	{
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
		[[nodiscard]] static bool IsValid(const _TargetShape& targetShape, const Rect& outerShape)
		{
			// [Siv3D ToDo] より厳密に
			return outerShape.contains(Geometry2D::Center(targetShape));
		}

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		SaturatedLinework()
			: m_targetShape(Ellipse(Scene::CenterF(), 200, 100))
			, m_outerRect(Scene::Rect())
		{
			setSeed(RandomUint64());
		}

		/// <summary>
		/// 集中線を作成します。
		/// </summary>
		/// <param name="targetShape">
		/// 集中線の輪郭
		/// </param>
		explicit SaturatedLinework(const TargetShape& targetShape)
			: m_targetShape(targetShape)
			, m_outerRect(Scene::Rect())
		{
			setSeed(RandomUint64());
		}

		/// <summary>
		/// 集中線を作成します。
		/// </summary>
		/// <param name="targetShape">
		/// 集中線の輪郭
		/// </param>
		/// <param name="outerShape">
		/// 集中線の描画範囲
		/// </param>
		SaturatedLinework(const TargetShape& targetShape, const Rect& outerShape)
			: m_targetShape(targetShape)
			, m_outerRect(outerShape)
		{
			setSeed(RandomUint64());
		}

		/// <summary>
		/// 集中線の輪郭を設定します。
		/// </summary>
		/// <param name="targetShape">
		/// 集中線の輪郭
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		SaturatedLinework& setTargetShape(const TargetShape& targetShape)
		{
			if (targetShape != m_targetShape)
			{
				m_targetShape = targetShape;
				m_isDirty = true;
			}

			return *this;
		}

		/// <summary>
		/// 集中線の輪郭を返します。
		/// </summary>
		/// <returns>
		/// 集中線の輪郭
		/// </returns>
		[[nodiscard]] const TargetShape& getTargetShape() const noexcept
		{
			return m_targetShape;
		}

		/// <summary>
		/// 集中線の描画範囲を設定します。
		/// </summary>
		/// <param name="outerRect">
		/// 集中線の描画範囲
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		SaturatedLinework& setOuterRect(const Rect& outerRect)
		{
			if (outerRect != m_outerRect)
			{
				m_outerRect = outerRect;
				m_isDirty = true;
			}

			return *this;
		}

		/// <summary>
		/// 集中線の描画範囲を返します
		/// </summary>
		/// <returns>
		/// 集中線の描画範囲
		/// </returns>
		[[nodiscard]] const Rect& getOuterRect() const noexcept
		{
			return m_outerRect;
		}

		/// <summary>
		/// 線の本数を設定します。
		/// </summary>
		/// <param name="outerRect">
		/// 線の本数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		SaturatedLinework& setLineCount(size_t lineCount)
		{
			if (lineCount != m_lineCount)
			{
				m_lineCount = lineCount;
				m_isDirty = true;
			}

			return *this;
		}

		/// <summary>
		/// 線の本数を返します。
		/// </summary>
		/// <returns>
		/// 線の本数
		/// </returns>
		[[nodiscard]] size_t getLineCount() const noexcept
		{
			return m_lineCount;
		}

		/// <summary>
		/// 線が最も太くなる場所の下限値を設定します。
		/// </summary>
		/// <param name="maxThickness">
		/// 最も太くなる場所の下限値
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		SaturatedLinework& setMinThickness(double minThickness)
		{
			if (minThickness < 0.0)
			{
				throw Error(U"SaturatedLinework::setMinThickness(): minThickness < 0.0");
			}

			if (m_maxThickness < minThickness)
			{
				throw Error(U"SaturatedLinework::setMinThickness(): m_maxThickness < minThickness");
			}

			if (minThickness != m_minThickness)
			{
				m_minThickness = minThickness;
				m_isDirty = true;
			}

			return *this;
		}

		/// <summary>
		/// 線の太さの下限値を返します。
		/// </summary>
		/// <returns>
		/// 線の太さの下限値
		/// </returns>
		[[nodiscard]] double getMinThickness() const noexcept
		{
			return m_minThickness;
		}

		/// <summary>
		/// 線が最も太くなる場所の上限値を設定します。
		/// </summary>
		/// <param name="maxThickness">
		/// 最も太くなる場所の上限値
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		SaturatedLinework& setMaxThickness(double maxThickness)
		{
			if (maxThickness < m_minThickness)
			{
				throw Error(U"SaturatedLinework::setMaxThickness(): maxThickness < m_minThickness");
			}

			if (m_maxThickness != maxThickness)
			{
				m_maxThickness = maxThickness;
				m_isDirty = true;
			}

			return *this;
		}

		/// <summary>
		/// 線の太さの上限値を返します。
		/// </summary>
		/// <returns>
		/// 線の太さの上限値
		/// </returns>
		[[nodiscard]] double getMaxThickness() const noexcept
		{
			return m_maxThickness;
		}

		/// <summary>
		/// 線の太さを設定します。
		/// </summary>
		/// <param name="minThickness">
		/// 最も太くなる場所の下限値
		/// </param>
		/// <param name="maxThickness">
		/// 最も太くなる場所の上限値
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		SaturatedLinework& setThickness(double minThickness, double maxThickness)
		{
			if (minThickness < 0.0)
			{
				throw Error(U"SaturatedLinework::setThickness(): minThickness < 0.0");
			}

			if (maxThickness < m_minThickness)
			{
				throw Error(U"SaturatedLinework::setThickness(): maxThickness < m_minThickness");
			}

			if (minThickness != m_minThickness)
			{
				m_minThickness = minThickness;
				m_isDirty = true;
			}

			if (maxThickness != m_maxThickness)
			{
				m_maxThickness = maxThickness;
				m_isDirty = true;
			}

			return *this;
		}

		/// <summary>
		/// 輪郭のばらけ具合を設定します
		/// </summary>
		/// <param name="offsetRange">
		/// ばらける範囲
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		SaturatedLinework& setOffsetRange(double offsetRange)
		{
			if (offsetRange != m_offsetRange)
			{
				m_offsetRange = offsetRange;
				m_isDirty = true;
			}
			return *this;
		}

		/// <summary>
		/// 輪郭のばらけ具合を返します。
		/// </summary>
		/// <returns>
		/// 輪郭のばらけ具合
		/// </returns>
		[[nodiscard]] double getOffsetRange() const noexcept
		{
			return m_offsetRange;
		}

		/// <summary>
		/// シード値を設定します。
		/// </summary>
		/// <param name="seed">
		/// シード値
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		SaturatedLinework& setSeed(uint64 seed)
		{
			m_seed = seed;
			m_rng.seed(seed);
			m_isDirty = true;
			return *this;
		}

		/// <summary>
		/// シード値を返します。
		/// </summary>
		/// <returns>
		/// シード値
		/// </returns>
		[[nodiscard]] uint64 getSeed() const noexcept
		{
			return m_seed;
		}

		/// <summary>
		/// 集中線を生成します。
		/// </summary>
		void generate() const
		{
			const int32 offset = static_cast<int32>(m_maxThickness / 2);
			const Rect outerRect = m_outerRect.stretched(offset);

			// 内部の図形が外部の図形に包まれてない場合はエラー
			// [Siv3D ToDo] より厳密に
			if (!IsValid(m_targetShape, outerRect))
			{
				return;
			}

			// 最初に配列をリセットする
			m_triangles.clear();
			m_triangles.reserve(m_lineCount);

			// 集中線の位置は実際に中心から線を引いてみて、交差した座標を取得する仕組み
			// 交差座標の取得に使う
			OffsetCircular3 cir;
			cir.setCenter(Geometry2D::Center(m_targetShape));

			// 半径を長く取る
			// 画面より大きければよほどのことがない限り平気なはず
			// 図形により大きさの取得法が違うし、十分大きければ特に支障はないので決め打ちします。
			cir.r = 1000000;

			UniformDistribution<double> angleDist(0.0, 2_pi);
			UniformDistribution<double> posDist(0.0, m_offsetRange);
			UniformDistribution<double> thickDist(m_minThickness, m_maxThickness);

			for (size_t i = 0; i < m_lineCount; ++i)
			{
				// 生成角度を設定
				const double angle = angleDist(m_rng);
				cir.theta = angle;

				// 角度に沿った線を作る
				const Line line(cir.center, cir);

				// 内側の座標を計算する
				// まずは位置にランダム性を持たせる
				const auto is = m_targetShape.stretched(posDist(m_rng));

				// 線との交点を取る
				const auto targetIntersects = is.intersectsAt(line);

				// 内側の図形の中心から線を引き始めているが、図形があまりにも大きいと交差しないので注意
				if (!targetIntersects || targetIntersects->isEmpty())
				{
					continue;
				}

				// 内側は太さは必要ないので中心線の座標をそのまま使用
				const Vec2 inner = targetIntersects->front();

				// 外側の中心(基準)となる座標を計算する そのまま使うわけではない
				const auto outerIntersects = outerRect.intersectsAt(line);

				// 外側の基準座標を取得できなかったら、その線はスキップして処理は続行
				// 並行になっていた場合は…最も遠い点を取得して線を引きたい
				// そもそもtargetShape=Ellipseで使っていたら平行にならない。
				// よほど変な形にしたとしても平行になる確率はn/乱数のとりうる全範囲、という超低確率
				// (平行が多発するような図形はとても歪な形で、頑張って線を引いたところでまともな形にならない)
				// 実装コスパが悪いので諦める方が無難と思われる。
				if (!outerIntersects || outerIntersects->isEmpty())
				{
					continue;
				}

				const Vec2 outer = outerIntersects->front();

				// 直線から垂直に、outerの座標から太さの半分ずらした点を2つ生成する処理
				// 90度回す
				const double rotated = angle + 90_deg;

				// ずらす量
				// 左右に広げるので、ここでの量は半分
				const double r = thickDist(m_rng) / 2;

				// 単位ベクトル
				const Vec2 v(cos(rotated), sin(rotated));
				const Vec2 outerOffset = v * r;

				// 左右にずらした座標を作る
				// 180度にずらすので、-+で対処可能
				const Vec2 outerLeft = outer + outerOffset;
				const Vec2 outerRight = outer - outerOffset;

				// Triangleの座標として登録
				m_triangles.emplace_back(inner, outerLeft, outerRight);
			}
		}

		/// <summary>
		/// 集中線を描画します。
		/// </summary>
		/// <param name="color">
		/// 集中線の色
		/// </param>
		void draw(const ColorF& color = Palette::Black) const
		{
			if (m_isDirty)
			{
				generate();
				m_isDirty = false;
			}

			for (const Triangle& triangle : m_triangles)
			{
				triangle.draw(color);
			}
		}
	};
}

/* example

# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Scene::SetBackground(ColorF(0.98, 0.96, 0.94));
	const Texture texture(Emoji(U"🦀"));

	Ellipse target(400, 300, 180, 120);
	Rect outer = Scene::Rect();
	double minThickness = 3.0, maxThickness = 10.0;
	double lineCount = 150;
	double offsetRange = 60.0;

	SaturatedLinework<Ellipse> linework(target, outer);
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

		linework.draw(ColorF(0.1));

		if (SimpleGUI::Slider(U"lineCount", lineCount, 0.0, 400.0, Vec2(20, 20), 150))
		{
			linework.setLineCount(static_cast<size_t>(lineCount));
		}

		if (SimpleGUI::Slider(U"offsetRange", offsetRange, 0.0, 100.0, Vec2(20, 60), 150))
		{
			linework.setOffsetRange(offsetRange);
		}
	}
}

*/
