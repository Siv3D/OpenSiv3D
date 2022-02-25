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

namespace s3d
{
	template <class TargetShape, class URNG>
	inline SaturatedLinework<TargetShape, URNG>::SaturatedLinework()
		: SaturatedLinework{ Ellipse{ Scene::CenterF(), 200, 100 }, Scene::Rect() } {}

	template <class TargetShape, class URNG>
	inline SaturatedLinework<TargetShape, URNG>::SaturatedLinework(const TargetShape& targetShape)
		: SaturatedLinework{ targetShape, Scene::Rect() } {}

	template <class TargetShape, class URNG>
	inline SaturatedLinework<TargetShape, URNG>::SaturatedLinework(const TargetShape& targetShape, const Rect& outerShape)
		: m_targetShape{ targetShape }
		, m_outerRect{ outerShape }
	{
		setSeed(RandomUint64());
	}

	template <class TargetShape, class URNG>
	inline SaturatedLinework<TargetShape, URNG>& SaturatedLinework<TargetShape, URNG>::setTargetShape(const TargetShape& targetShape)
	{
		if (targetShape != m_targetShape)
		{
			m_targetShape = targetShape;
			m_isDirty = true;
		}

		return *this;
	}

	template <class TargetShape, class URNG>
	inline const TargetShape& SaturatedLinework<TargetShape, URNG>::getTargetShape() const noexcept
	{
		return m_targetShape;
	}

	template <class TargetShape, class URNG>
	inline SaturatedLinework<TargetShape, URNG>& SaturatedLinework<TargetShape, URNG>::setOuterRect(const Rect& outerRect)
	{
		if (outerRect != m_outerRect)
		{
			m_outerRect = outerRect;
			m_isDirty = true;
		}

		return *this;
	}

	template <class TargetShape, class URNG>
	inline const Rect& SaturatedLinework<TargetShape, URNG>::getOuterRect() const noexcept
	{
		return m_outerRect;
	}

	template <class TargetShape, class URNG>
	inline SaturatedLinework<TargetShape, URNG>& SaturatedLinework<TargetShape, URNG>::setLineCount(size_t lineCount)
	{
		if (lineCount != m_lineCount)
		{
			m_lineCount = lineCount;
			m_isDirty = true;
		}

		return *this;
	}

	template <class TargetShape, class URNG>
	inline size_t SaturatedLinework<TargetShape, URNG>::getLineCount() const noexcept
	{
		return m_lineCount;
	}

	template <class TargetShape, class URNG>
	inline SaturatedLinework<TargetShape, URNG>& SaturatedLinework<TargetShape, URNG>::setMinThickness(double minThickness)
	{
		if (minThickness < 0.0)
		{
			throw Error{ U"SaturatedLinework::setMinThickness(): minThickness < 0.0" };
		}

		if (m_maxThickness < minThickness)
		{
			throw Error{ U"SaturatedLinework::setMinThickness(): m_maxThickness < minThickness" };
		}

		if (minThickness != m_minThickness)
		{
			m_minThickness = minThickness;
			m_isDirty = true;
		}

		return *this;
	}

	template <class TargetShape, class URNG>
	inline double SaturatedLinework<TargetShape, URNG>::getMinThickness() const noexcept
	{
		return m_minThickness;
	}

	template <class TargetShape, class URNG>
	inline SaturatedLinework<TargetShape, URNG>& SaturatedLinework<TargetShape, URNG>::setMaxThickness(const double maxThickness)
	{
		if (maxThickness < m_minThickness)
		{
			throw Error{ U"SaturatedLinework::setMaxThickness(): maxThickness < m_minThickness" };
		}

		if (m_maxThickness != maxThickness)
		{
			m_maxThickness = maxThickness;
			m_isDirty = true;
		}

		return *this;
	}

	template <class TargetShape, class URNG>
	inline double SaturatedLinework<TargetShape, URNG>::getMaxThickness() const noexcept
	{
		return m_maxThickness;
	}

	template <class TargetShape, class URNG>
	inline SaturatedLinework<TargetShape, URNG>& SaturatedLinework<TargetShape, URNG>::setThickness(const double minThickness, const double maxThickness)
	{
		if (minThickness < 0.0)
		{
			throw Error{ U"SaturatedLinework::setThickness(): minThickness < 0.0" };
		}

		if (maxThickness < minThickness)
		{
			throw Error{ U"SaturatedLinework::setThickness(): maxThickness < minThickness" };
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

	template <class TargetShape, class URNG>
	inline SaturatedLinework<TargetShape, URNG>& SaturatedLinework<TargetShape, URNG>::setOffsetRange(const double offsetRange)
	{
		if (offsetRange < 0.0)
		{
			throw Error{ U"SaturatedLinework::setOffsetRange(): offsetRange < 0.0" };
		}

		if (offsetRange != m_offsetRange)
		{
			m_offsetRange = offsetRange;
			m_isDirty = true;
		}
		return *this;
	}

	template <class TargetShape, class URNG>
	inline double SaturatedLinework<TargetShape, URNG>::getOffsetRange() const noexcept
	{
		return m_offsetRange;
	}

	template <class TargetShape, class URNG>
	inline SaturatedLinework<TargetShape, URNG>& SaturatedLinework<TargetShape, URNG>::setSeed(const uint64 seed)
	{
		m_seed = seed;
		m_rng.seed(seed);
		m_isDirty = true;
		return *this;
	}

	template <class TargetShape, class URNG>
	inline uint64 SaturatedLinework<TargetShape, URNG>::getSeed() const noexcept
	{
		return m_seed;
	}

	template <class TargetShape, class URNG>
	inline void SaturatedLinework<TargetShape, URNG>::generate() const
	{
		const int32 offset = static_cast<int32>(m_maxThickness / 2);
		const Rect outerRect = m_outerRect.stretched(offset);

		// 内部の図形が外部の図形に包まれてない場合はエラー
		// [Siv3D ToDo] より厳密に
		if (not IsValid(m_targetShape, outerRect))
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

		UniformDistribution<double> angleDist{ 0.0, Math::TwoPi };
		UniformDistribution<double> posDist{ 0.0, m_offsetRange };
		UniformDistribution<double> thickDist{ m_minThickness, m_maxThickness };

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
			if (not targetIntersects
				|| targetIntersects->isEmpty())
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
			if (not outerIntersects
				|| outerIntersects->isEmpty())
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
			const auto [s, c] = FastMath::SinCos(rotated);
			const Vec2 v{ c, s };
			const Vec2 outerOffset = v * r;

			// 左右にずらした座標を作る
			// 180度にずらすので、-+で対処可能
			const Vec2 outerLeft = outer + outerOffset;
			const Vec2 outerRight = outer - outerOffset;

			// Triangleの座標として登録
			m_triangles.emplace_back(inner, outerLeft, outerRight);
		}
	}

	template <class TargetShape, class URNG>
	inline void SaturatedLinework<TargetShape, URNG>::draw(const ColorF& color) const
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

	template <class TargetShape, class URNG>
	template <class _TargetShape>
	inline bool SaturatedLinework<TargetShape, URNG>::IsValid(const _TargetShape& targetShape, const Rect& outerShape)
	{
		// [Siv3D ToDo] より厳密に
		return outerShape.contains(Geometry2D::Center(targetShape));
	}
}
