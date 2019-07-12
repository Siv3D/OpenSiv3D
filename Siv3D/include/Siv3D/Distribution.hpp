//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <cassert>
# include <random>
# include <type_traits>
# include <array>
# include "Array.hpp"

namespace s3d
{
	/// <summary>
	/// 一様分布
	/// </summary>
	/// <remarks>
	/// 乱数の型と範囲を定義します。
	/// </remarks>
	template <class Type>
	class UniformDistribution
	{
	private:

		using distribution_type = std::conditional_t<std::is_floating_point_v<Type>,
			std::uniform_real_distribution<Type>, std::uniform_int_distribution<Type>>;

		distribution_type m_distribution;

	public:

		using result_type = Type;

		UniformDistribution() = default;

		/// <summary>
		/// 一様分布を設定します。
		/// </summary>
		/// <param name="min">
		/// 生成する乱数の最小値
		/// </param>
		/// <param name="max">
		/// 生成する乱数の最大値
		/// </param>
		UniformDistribution(result_type min, result_type max)
		{
			assert(min <= max);

			m_distribution.param(typename distribution_type::param_type{ min, max });
		}

		/// <summary>
		/// 一様分布の乱数を生成します。
		/// </summary>
		/// <param name="engine">
		/// 乱数生成エンジン
		/// </param>
		/// <returns>
		/// 乱数
		/// </returns>
		template <class Engine>
		result_type operator()(Engine& engine)
		{
			return m_distribution(engine);
		}

		/// <summary>
		/// 一様分布を設定します。
		/// </summary>
		/// <param name="min">
		/// 生成する乱数の最小値
		/// </param>
		/// <param name="max">
		/// 生成する乱数の最大値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void set(const result_type min, const result_type max)
		{
			assert(min <= max);

			m_distribution.param({ min, max });
		}

		/// <summary>
		/// 生成する乱数の最小値
		/// </summary>
		[[nodiscard]] result_type min() const
		{
			return m_distribution.min();
		}

		/// <summary>
		/// 生成する乱数の最大値
		/// </summary>
		[[nodiscard]] result_type max() const
		{
			return m_distribution.max();
		}
	};

	/// <summary>
	/// 正規分布
	/// </summary>
	/// <remarks>
	/// 正規分布を定義します。
	/// </remarks>
	template <class Type = double>
	class NormalDistribution
	{
	private:

		using distribution_type = std::normal_distribution<Type>;

		distribution_type m_distribution;

	public:

		using result_type = Type;

		NormalDistribution() = default;

		/// <summary>
		/// 正規分布を設定します。
		/// </summary>
		/// <param name="mean">
		/// 平均
		/// </param>
		/// <param name="sigma">
		/// 標準偏差
		/// </param>
		NormalDistribution(result_type mean, result_type sigma)
			: m_distribution(mean, sigma) {}

		/// <summary>
		/// 正規分布の乱数を生成します。
		/// </summary>
		/// <param name="engine">
		/// 乱数生成エンジン
		/// </param>
		/// <returns>
		/// 乱数
		/// </returns>
		template <class Engine>
		result_type operator()(Engine& engine)
		{
			return m_distribution(engine);
		}

		/// <summary>
		/// 正規分布を設定します。
		/// </summary>
		/// <param name="mean">
		/// 平均
		/// </param>
		/// <param name="sigma">
		/// 標準偏差
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void set(const result_type mean, const result_type sigma)
		{
			m_distribution.param(typename distribution_type::param_type{ mean, sigma });
		}

		/// <summary>
		/// 平均
		/// </summary>
		[[nodiscard]] result_type mean() const
		{
			return m_distribution.mean();
		}

		/// <summary>
		/// 標準偏差
		/// </summary>
		[[nodiscard]] result_type sigma() const
		{
			return m_distribution.sigma();
		}
	};

	class DiscreteDistribution
	{
	private:

		using distribution_type = std::discrete_distribution<size_t>;

		distribution_type m_distribution;

	public:

		using result_type = size_t;

		DiscreteDistribution() = default;

		explicit DiscreteDistribution(std::initializer_list<double> ilist);

		explicit DiscreteDistribution(const Array<double>& weights);

		template <size_t Size>
		explicit DiscreteDistribution(const std::array<double, Size>& weights)
			: m_distribution(weights.begin(), weights.end()) {}

		template <class Iterator>
		explicit DiscreteDistribution(Iterator begin, Iterator end)
			: m_distribution(begin, end) {}

		DiscreteDistribution& operator =(std::initializer_list<double> ilist);

		template <size_t Size>
		DiscreteDistribution& operator =(const std::array<double, Size>& weights)
		{
			m_distribution = distribution_type(weights.begin(), weights.end());
			return *this;
		}

		DiscreteDistribution& operator =(const Array<double>& weights);

		[[nodiscard]] Array<double> probabilities() const;

		template <class Engine>
		result_type operator()(Engine& engine)
		{
			return m_distribution(engine);
		}

		[[nodiscard]] size_t min() const;

		[[nodiscard]] size_t max() const;

		[[nodiscard]] size_t size() const;
	};
}
