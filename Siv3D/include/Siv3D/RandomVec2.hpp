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
# include "PointVector.hpp"
# include "2DShapes.hpp"
# include "DiscreteDistribution.hpp"

namespace s3d
{
	/// @brief 長さが 1 のランダムな 2 次元ベクトルを返します。
	/// @return 長さが 1 のランダムな 2 次元ベクトル
	[[nodiscard]]
	inline Vec2 RandomVec2();

	/// @brief 長さが 1 のランダムな 2 次元ベクトルを返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param urbg 乱数エンジン
	/// @return 長さが 1 のランダムな 2 次元ベクトル
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(URBG&& urbg);

	/// @brief 指定した長さを持つランダムな 2 次元ベクトルを返します。
	/// @param length ベクトルの長さ
	/// @return 指定した長さを持つランダムな 2 次元ベクトル
	[[nodiscard]]
	inline Vec2 RandomVec2(double length);

	/// @brief 指定した長さを持つランダムな 2 次元ベクトルを返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param length ベクトルの長さ
	/// @param urbg 乱数エンジン
	/// @return 指定した長さを持つランダムな 2 次元ベクトル
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(double length, URBG&& urbg);

	/// @brief 固定の X 成分と、ランダムな Y 成分を持つ 2 次元ベクトルを返します。
	/// @param x 固定の X 成分
	/// @param yMinMax Y 成分の最小値と最大値
	/// @return 固定の X 成分と、ランダムな Y 成分を持つ 2 次元ベクトル
	[[nodiscard]]
	inline Vec2 RandomVec2(double x, const std::pair<double, double>& yMinMax);

	/// @brief 固定の X 成分と、ランダムな Y 成分を持つ 2 次元ベクトルを返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param x 固定の X 成分
	/// @param yMinMax Y 成分の最小値と最大値
	/// @param urbg 乱数エンジン
	/// @return 固定の X 成分と、ランダムな Y 成分を持つ 2 次元ベクトル
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(double x, const std::pair<double, double>& yMinMax, URBG&& urbg);

	/// @brief ランダムな X 成分と、固定の Y 成分を持つ 2 次元ベクトルを返します。
	/// @param xMinMax X 成分の最小値と最大値
	/// @param y 固定の Y 成分
	/// @return ランダムな X 成分と、固定の Y 成分を持つ 2 次元ベクトル
	[[nodiscard]]
	inline Vec2 RandomVec2(const std::pair<double, double>& xMinMax, double y);

	/// @brief ランダムな X 成分と、固定の Y 成分を持つ 2 次元ベクトルを返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param xMinMax X 成分の最小値と最大値
	/// @param y 固定の Y 成分
	/// @param urbg 乱数エンジン
	/// @return ランダムな X 成分と、固定の Y 成分を持つ 2 次元ベクトル
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(const std::pair<double, double>& xMinMax, double y, URBG&& urbg);

	/// @brief ランダムな X 成分、Y 成分を持つ 2 次元ベクトルを返します。
	/// @param xMinMax X 成分の最小値と最大値
	/// @param yMinMax Y 成分の最小値と最大値
	/// @return ランダムな X 成分、Y 成分を持つ 2 次元ベクトル
	[[nodiscard]]
	inline Vec2 RandomVec2(const std::pair<double, double>& xMinMax, const std::pair<double, double>& yMinMax);

	/// @brief ランダムな X 成分、Y 成分を持つ 2 次元ベクトルを返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param xMinMax X 成分の最小値と最大値
	/// @param yMinMax Y 成分の最小値と最大値
	/// @param urbg 乱数エンジン
	/// @return ランダムな X 成分、Y 成分を持つ 2 次元ベクトル
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(const std::pair<double, double>& xMinMax, const std::pair<double, double>& yMinMax, URBG&& urbg);

	/// @brief 0 以上、指定した最大値以下のランダムな X 成分、Y 成分を持つ 2 次元ベクトルを返します。
	/// @param xMax X 成分の最大値
	/// @param yMax Y 成分の最大値
	/// @return 0 以上、指定した最大値以下のランダムな X 成分、Y 成分を持つ 2 次元ベクトル
	[[nodiscard]]
	inline Vec2 RandomVec2(double xMax, double yMax);

	/// @brief 0 以上、指定した最大値以下のランダムな X 成分、Y 成分を持つ 2 次元ベクトルを返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param xMax X 成分の最大値
	/// @param yMax Y 成分の最大値
	/// @param urbg 乱数エンジン
	/// @return 0 以上、指定した最大値以下のランダムな X 成分、Y 成分を持つ 2 次元ベクトル
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(double xMax, double yMax, URBG&& urbg);

	/// @brief 指定した線分上のランダムな位置ベクトルを返します。
	/// @param line 線分
	/// @return 指定した線分上のランダムな位置ベクトル
	[[nodiscard]]
	inline Vec2 RandomVec2(const Line& line);

	/// @brief 指定した線分上のランダムな位置ベクトルを返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param line 線分
	/// @param urbg 乱数エンジン
	/// @return 指定した線分上のランダムな位置ベクトル
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(const Line& line, URBG&& urbg);

	/// @brief 指定した円の内部のランダムな位置ベクトルを返します。
	/// @param circle 円
	/// @return 指定した円の内部のランダムな位置ベクトル
	[[nodiscard]]
	inline Vec2 RandomVec2(const Circle& circle);

	/// @brief 指定した円の内部のランダムな位置ベクトルを返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param circle 円
	/// @param urbg 乱数エンジン
	/// @return 指定した円の内部のランダムな位置ベクトル
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(const Circle& circle, URBG&& urbg);

	/// @brief 指定した長方形の内部のランダムな位置ベクトルを返します。
	/// @param rect 長方形
	/// @return 指定した長方形の内部のランダムな位置ベクトル
	[[nodiscard]]
	inline Vec2 RandomVec2(const RectF& rect);

	/// @brief 指定した長方形の内部のランダムな位置ベクトルを返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param rect 長方形
	/// @param urbg 乱数エンジン
	/// @return 指定した長方形の内部のランダムな位置ベクトル
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(const RectF& rect, URBG&& urbg);

	/// @brief 指定した三角形の内部のランダムな位置ベクトルを返します。
	/// @param triangle 三角形
	/// @return 指定した三角形の内部のランダムな位置ベクトル
	[[nodiscard]]
	inline Vec2 RandomVec2(const Triangle& triangle);

	/// @brief 指定した三角形の内部のランダムな位置ベクトルを返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param triangle 三角形
	/// @param urbg 乱数エンジン
	/// @return 指定した三角形の内部のランダムな位置ベクトル
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(const Triangle& triangle, URBG&& urbg);

	/// @brief 指定した四角形の内部のランダムな位置ベクトルを返します。
	/// @param quad 四角形
	/// @return 指定した四角形の内部のランダムな位置ベクトル
	[[nodiscard]]
	inline Vec2 RandomVec2(const Quad& quad);

	/// @brief 指定した四角形の内部のランダムな位置ベクトルを返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param quad 四角形
	/// @param urbg 乱数エンジン
	/// @return 指定した四角形の内部のランダムな位置ベクトル
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(const Quad& quad, URBG&& urbg);
}

# include "detail/RandomVec2.ipp"
