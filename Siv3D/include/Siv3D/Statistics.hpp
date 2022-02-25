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
//	Authors (OpenSiv3D challenge #01 paricipants)
//	- 白坂
//	- マキア
//	- fal_rnd
//-----------------------------------------------

# pragma once
# include <iterator>
# include "Common.hpp"
# include "Array.hpp"
# include "Optional.hpp"

namespace s3d
{
	namespace Statistics
	{
		// 最小値
		// - 範囲が空の場合は none
		template <class ForwardIt>
		constexpr auto Min(ForwardIt first, ForwardIt last)
			->Optional<typename std::iterator_traits<ForwardIt>::value_type>;

		// 最大値
		// - 範囲が空の場合は none
		template <class ForwardIt>
		constexpr auto Max(ForwardIt first, ForwardIt last)
			->Optional<typename std::iterator_traits<ForwardIt>::value_type>;

		// 平均値
		// - 範囲が空の場合は 0
		template <class Type = double, class ForwardIt>
		constexpr Type Mean(ForwardIt first, ForwardIt last);

		// 中央値
		// - 範囲が空の場合は none
		template <class ForwardIt>
		constexpr Optional<double> Median(ForwardIt first, ForwardIt last);

		// 中央値 (low median)
		// - データ数が偶数の場合、中央の 2 値の小さい方
		template <class ForwardIt>
		[[nodiscard]]
		constexpr auto LowMedian(ForwardIt first, ForwardIt last)
			->Optional<typename std::iterator_traits<ForwardIt>::value_type>;

		// 中央値 (high median)
		// - データ数が偶数の場合、中央の 2 値の大きい方
		template <class ForwardIt>
		[[nodiscard]]
		constexpr auto HighMedian(ForwardIt first, ForwardIt last)
			->Optional<typename std::iterator_traits<ForwardIt>::value_type>;

		// 最頻値
		// - 複数ある場合は最初に最頻値に達したもの
		template <class ForwardIt>
		auto Mode(ForwardIt first, ForwardIt last)
			->Optional<typename std::iterator_traits<ForwardIt>::value_type>;

		// 最頻値
		// - count: 最頻値の出現数の結果を格納
		// - 複数ある場合は最初に最頻値に達したもの
		template <class ForwardIt>
		auto Mode(ForwardIt first, ForwardIt last, size_t& count)
			->Optional<typename std::iterator_traits<ForwardIt>::value_type>;

		// 最頻値（複数）
		// - 複数ある場合は入力された順
		template <class ForwardIt>
		auto MultiMode(ForwardIt first, ForwardIt last)
			->Array<typename std::iterator_traits<ForwardIt>::value_type>;

		// 最頻値（複数）
		// - count: 最頻値の出現数の結果を格納
		// - 複数ある場合は入力された順
		template <class ForwardIt>
		auto MultiMode(ForwardIt first, ForwardIt last, size_t& count)
			->Array<typename std::iterator_traits<ForwardIt>::value_type>;

		// 母分散 | population variance
		// - 範囲が空の場合は none
		template <class ForwardIt>
		constexpr Optional<double> PopulationVariance(ForwardIt first, ForwardIt last);

		// 母分散 | population variance
		// - mu: μ
		// - 範囲が空の場合は none
		template <class ForwardIt>
		constexpr Optional<double> PopulationVariance(ForwardIt first, ForwardIt last, double mu);

		// 不偏分散 | unbiased sample variance
		// - 範囲の要素数が 2 未満の場合は none
		template <class ForwardIt>
		constexpr Optional<double> Variance(ForwardIt first, ForwardIt last);

		// 不偏分散 | unbiased sample variance
		// - xbar: データの平均値
		// - 範囲の要素数が 2 未満の場合は none
		template <class ForwardIt>
		constexpr Optional<double> Variance(ForwardIt first, ForwardIt last, double xbar);

		// 母標準偏差 | population standard deviation
		// - 範囲が空の場合は none
		template <class ForwardIt>
		constexpr Optional<double> PopulationStandardDeviation(ForwardIt first, ForwardIt last);

		// 母標準偏差 | population standard deviation
		// - mu: μ
		// - 範囲が空の場合は none
		template <class ForwardIt>
		constexpr Optional<double> PopulationStandardDeviation(ForwardIt first, ForwardIt last, double mu);

		// 不偏標準偏差 | unbiased standard deviation
		// - 範囲の要素数が 2 未満の場合は none
		template <class ForwardIt>
		constexpr Optional<double> StandardDeviation(ForwardIt first, ForwardIt last);

		// 不偏標準偏差 | unbiased standard deviation
		// - xbar: データの平均値
		// - 範囲の要素数が 2 未満の場合は none
		template <class ForwardIt>
		constexpr Optional<double> StandardDeviation(ForwardIt first, ForwardIt last, double xbar);

		// 尖度 | Kurtosis
		// - 範囲が空の場合は none
		template <class ForwardIt>
		constexpr Optional<double> Kurtosis(ForwardIt first, ForwardIt last);

		// 歪度 | Skewness
		// - 範囲が空の場合は none
		template <class ForwardIt>
		constexpr Optional<double> Skewness(ForwardIt first, ForwardIt last);
	}
}

# include "detail/Statistics.ipp"
