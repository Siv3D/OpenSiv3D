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
# include "../Math.hpp"

namespace s3d
{
	namespace detail
	{
		template <class Iterator>
		inline constexpr bool IsRandomAccessIterator
			= std::is_convertible_v<
			typename std::iterator_traits<Iterator>::iterator_category,
			std::random_access_iterator_tag>;
	}

	namespace Statistics
	{
		// 最小値
		// - 範囲が空の場合は none
		template <class ForwardIt>
		inline constexpr auto Min(ForwardIt first, ForwardIt last)
			-> Optional<typename std::iterator_traits<ForwardIt>::value_type>
		{
			if (first == last) // range is empty
			{
				return none;
			}

			return *std::min_element(first, last);
		}

		// 最大値
		// - 範囲が空の場合は none
		template <class ForwardIt>
		inline constexpr auto Max(ForwardIt first, ForwardIt last)
			-> Optional<typename std::iterator_traits<ForwardIt>::value_type>
		{
			if (first == last) // range is empty
			{
				return none;
			}

			return *std::max_element(first, last);
		}

		// 平均値
		// - 範囲が空の場合は 0
		template <class Type, class ForwardIt>
		inline constexpr Type Mean(ForwardIt first, ForwardIt last)
		{
			if (first == last) // range is empty
			{
				return Type{};
			}

			if constexpr (detail::IsRandomAccessIterator<ForwardIt>)
			{
				const auto count = (last - first);
				return std::accumulate(first, last, Type{}) / count;
			}
			else
			{
				Type sum{};
				size_t count = 0;

				while (first != last)
				{
					sum += *(first++);
					++count;
				}

				return sum / count;
			}
		}

		// 中央値
		// - 範囲が空の場合は none
		template <class ForwardIt>
		inline constexpr Optional<double> Median(ForwardIt first, ForwardIt last)
		{
			if (first == last) // range is empty
			{
				return none;
			}

			using ValueType = typename std::iterator_traits<ForwardIt>::value_type;
			Array<ValueType> data(first, last);

			const size_t n = data.size();
			const size_t medianIndex = n / 2;

			std::nth_element(data.begin(), data.begin() + medianIndex, data.end());

			if (IsOdd(n))
			{
				return static_cast<double>(data[medianIndex]);
			}
			else
			{
				const auto medianLow
					= static_cast<double>(*std::max_element(data.begin(), data.begin() + medianIndex));
				const auto medianHigh
					= static_cast<double>(data[medianIndex]);

			# ifdef __cpp_lib_interpolate
				return std::midpoint(medianLow, medianHigh);
			# else
				return (medianLow + medianHigh) / 2.0;
			# endif
			}
		}

		// 中央値 (low median)
		// - データ数が偶数の場合、中央の 2 値の小さい方
		template <class ForwardIt>
		inline constexpr auto LowMedian(ForwardIt first, ForwardIt last)
			-> Optional<typename std::iterator_traits<ForwardIt>::value_type>
		{
			if (first == last) // range is empty
			{
				return none;
			}

			using ValueType = typename std::iterator_traits<ForwardIt>::value_type;
			Array<ValueType> data(first, last);

			const size_t n = data.size();
			const size_t medianIndex = (n - 1) / 2;

			std::nth_element(data.begin(), data.begin() + medianIndex, data.end());

			return data[medianIndex];
		}

		// 中央値 (high median)
		// - データ数が偶数の場合、中央の 2 値の大きい方
		template <class ForwardIt>
		inline constexpr auto HighMedian(ForwardIt first, ForwardIt last)
			-> Optional<typename std::iterator_traits<ForwardIt>::value_type>
		{
			if (first == last) // range is empty
			{
				return none;
			}

			using ValueType = typename std::iterator_traits<ForwardIt>::value_type;
			Array<ValueType> data(first, last);

			const size_t n = data.size();
			const size_t medianIndex = n / 2;

			std::nth_element(data.begin(), data.begin() + medianIndex, data.end());

			return data[medianIndex];
		}

		// 最頻値
		// - 複数ある場合は最初に最頻値に達したもの
		template <class ForwardIt>
		inline auto Mode(ForwardIt first, ForwardIt last)
			-> Optional<typename std::iterator_traits<ForwardIt>::value_type>
		{
			size_t unused;
			return Mode(first, last, unused);
		}

		// 最頻値
		// - count: 最頻値の出現数の結果を格納
		// - 複数ある場合は最初に最頻値に達したもの
		template <class ForwardIt>
		inline auto Mode(ForwardIt first, ForwardIt last, size_t& count)
			-> Optional<typename std::iterator_traits<ForwardIt>::value_type>
		{
			if (first == last) // range is empty
			{
				count = 0;
				return none;
			}

			using ValueType = typename std::iterator_traits<ForwardIt>::value_type;
			HashTable<ValueType, size_t> ht;

			size_t maxCount = 1;
			ForwardIt modeValueIt = first;

			while (first != last)
			{
				if (auto it = ht.find(*first);
					it != ht.end())
				{
					const size_t keyCount = ++(it.value());

					if (keyCount > maxCount)
					{
						modeValueIt = first;
						maxCount = keyCount;
					}
				}
				else
				{
					ht.emplace(*first, 1);
				}

				++first;
			}

			count = maxCount;
			return *modeValueIt;
		}

		// 最頻値（複数）
		// - 複数ある場合は入力された順
		template <class ForwardIt>
		inline auto MultiMode(ForwardIt first, ForwardIt last)
			-> Array<typename std::iterator_traits<ForwardIt>::value_type>
		{
			size_t unused;
			return MultiMode(first, last, unused);
		}

		// 最頻値（複数）
		// - count: 最頻値の出現数の結果を格納
		// - 複数ある場合は入力された順
		template <class ForwardIt>
		inline auto MultiMode(ForwardIt first, ForwardIt last, size_t& count)
			-> Array<typename std::iterator_traits<ForwardIt>::value_type>
		{
			if (first == last) // range is empty
			{
				count = 0;
				return{};
			}

			using ValueType = typename std::iterator_traits<ForwardIt>::value_type;
			using Count = size_t;
			using Index = size_t;
			HashTable<ValueType, std::pair<Count, Index>> ht;
			Count maxCount = 1;
			Index index = 0;

			while (first != last)
			{
				if (auto it = ht.find(*first);
					it != ht.end())
				{
					const Count keyCount = ++(it.value().first);
					maxCount = s3d::Max(maxCount, keyCount);
				}
				else
				{
					ht.emplace(*first, std::pair<Count, Index>(1, index));
				}

				++first;
				++index;
			}

			Array<std::pair<ValueType, Index>> results;

			for (auto [key, value] : ht)
			{
				if (value.first == maxCount)
				{
					results.emplace_back(key, value.second);
				}
			}

			results.sort_by([](const std::pair<ValueType, Index>& a,
				const std::pair<ValueType, Index>& b)
				{
					return a.second < b.second;
				});

			count = maxCount;

			return results.map([](const std::pair<ValueType, Index>& p)
				{
					return p.first;
				});
		}

		// 母分散 | population variance
		// - 範囲が空の場合は none
		template <class ForwardIt>
		inline constexpr Optional<double> PopulationVariance(ForwardIt first, ForwardIt last)
		{
			return PopulationVariance(first, last, Mean(first, last));
		}

		// 母分散 | population variance
		// - mu: μ
		// - 範囲が空の場合は none
		template <class ForwardIt>
		constexpr Optional<double> PopulationVariance(ForwardIt first, ForwardIt last, double mu)
		{
			if (first == last) // range is empty
			{
				return none;
			}

			KahanSummation<double> s;
			size_t count = 0;

			for (; first != last; ++first)
			{
				const double value = static_cast<double>(*first);
				s += Math::Square(value - mu);
				++count;
			}

			return s.value() / count;
		}

		// 不偏分散 | unbiased sample variance
		// - 範囲の要素数が 2 未満の場合は none
		template <class ForwardIt>
		inline constexpr Optional<double> Variance(ForwardIt first, ForwardIt last)
		{
			return Variance(first, last, Mean(first, last));
		}

		// 不偏分散 | unbiased sample variance
		// - xbar: データの平均値
		// - 範囲の要素数が 2 未満の場合は none
		template <class ForwardIt>
		inline constexpr Optional<double> Variance(ForwardIt first, ForwardIt last, double xbar)
		{
			if (first == last) // range is empty
			{
				return none;
			}

			KahanSummation<double> s;
			size_t count = 0;

			for (; first != last; ++first)
			{
				const double value = static_cast<double>(*first);
				s += Math::Square(value - xbar);
				++count;
			}

			if (count < 2)
			{
				return none;
			}

			return s.value() / (count - 1);
		}
		
		// 母標準偏差 | population standard deviation
		// - 範囲が空の場合は none
		template <class ForwardIt>
		inline constexpr Optional<double> PopulationStandardDeviation(ForwardIt first, ForwardIt last)
		{
			return PopulationStandardDeviation(first, last, Mean(first, last));
		}
		
		// 母標準偏差 | population standard deviation
		// - mu: μ
		// - 範囲が空の場合は none
		template <class ForwardIt>
		inline constexpr Optional<double> PopulationStandardDeviation(ForwardIt first, ForwardIt last, double mu)
		{
			if (auto variance = PopulationVariance(first, last, mu))
			{
				return std::sqrt(*variance);
			}
			else
			{
				return none;
			}
		}

		// 不偏標準偏差 | unbiased standard deviation
		// - 範囲の要素数が 2 未満の場合は none
		template <class ForwardIt>
		inline constexpr Optional<double> StandardDeviation(ForwardIt first, ForwardIt last)
		{
			return StandardDeviation(first, last, Mean(first, last));
		}

		// 不偏標準偏差 | unbiased standard deviation
		// - xbar: データの平均値
		// - 範囲の要素数が 2 未満の場合は none
		template <class ForwardIt>
		inline constexpr Optional<double> StandardDeviation(ForwardIt first, ForwardIt last, double xbar)
		{
			if (auto variance = Variance(first, last, xbar))
			{
				return std::sqrt(*variance);
			}
			else
			{
				return none;
			}
		}

		// 尖度 | Kurtosis
		// - 範囲が空の場合は none
		template <class ForwardIt>
		inline constexpr Optional<double> Kurtosis(ForwardIt first, ForwardIt last)
		{
			if (first == last) // range is empty
			{
				return none;
			}

			const double mean = Mean(first, last);
			const auto v = Math::Square(PopulationVariance(first, last, mean).value());

			KahanSummation<double> sum;
			size_t count = 0;

			while (first != last)
			{
				const double value = static_cast<double>(*first);
				sum += Math::Square(Math::Square(value - mean));

				++first;
				++count;
			}

			return ((sum.value() / v) / count) - 3;
		}

		// 歪度 | Skewness
		// - 範囲が空の場合は none
		template <class ForwardIt>
		inline constexpr Optional<double> Skewness(ForwardIt first, ForwardIt last)
		{
			if (first == last) // range is empty
			{
				return none;
			}

			const double mean = Mean(first, last);
			double sd = PopulationStandardDeviation(first, last, mean).value();
			sd = (sd * sd * sd);

			KahanSummation<double> sum;
			size_t count = 0;

			while (first != last)
			{
				const double value = static_cast<double>(*first);
				const double t = (value - mean);
				sum += (t * t * t);

				++first;
				++count;
			}

			return (sum.value() / sd) / count;
		}
	}
}
