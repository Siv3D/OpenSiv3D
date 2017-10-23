//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <cassert>
# include <random>
# include <type_traits>

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

		using distribution_type = std::conditional_t<std::is_floating_point<Type>::value,
			std::uniform_real_distribution<Type>, std::uniform_int_distribution<Type>>;

		distribution_type m_distribution;

	public:

		using result_type = Type;

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
		result_type min() const
		{
			return m_distribution.min();
		}

		/// <summary>
		/// 生成する乱数の最大値
		/// </summary>
		result_type max() const
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
		result_type mean() const
		{
			return m_distribution.mean();
		}

		/// <summary>
		/// 標準偏差
		/// </summary>
		result_type sigma() const
		{
			return m_distribution.sigma();
		}
	};
}
