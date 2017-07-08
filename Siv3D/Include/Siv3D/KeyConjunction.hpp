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
# include "Key.hpp"

namespace s3d
{
	/// <summary>
	/// キーの組み合わせ（プラス）
	/// </summary>
	/// <remarks>
	/// 1 つ目のキーが押されている状態のとき 2 つ目のキー入力を調べます。
	/// </remarks>
	class KeyConjunction
	{
	private:

		Key m_key1, m_key2;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		KeyConjunction() = default;

		/// <summary>
		/// キーの組み合わせを設定します。
		/// </summary>
		/// <param name="key1">
		/// 1 つ目のキー
		/// </param>
		/// <param name="key2">
		/// 2 つ目のキー
		/// </param>
		constexpr KeyConjunction(const Key& key1, const Key& key2)
			: m_key1(key1)
			, m_key2(key2) {}

		bool down() const
		{
			return m_key1.pressed() && m_key2.down();
		}

		bool pressed() const
		{
			const auto t1 = m_key1.pressedDuration();
			const auto t2 = m_key2.pressedDuration();

			if (t1 < t2)
			{
				return false;
			}

			return m_key1.pressed() && m_key2.pressed();
		}

		bool up() const
		{
			return m_key1.pressed() && m_key2.up();
		}

		MillisecondsF pressedDuration() const
		{
			const auto t1 = m_key1.pressedDuration();
			const auto t2 = m_key2.pressedDuration();
			const bool pr = m_key1.pressed() && m_key2.pressed();

			if (!pr || t1 < t2)
			{
				return MillisecondsF(0);
			}

			return t2;
		}

		const Key& key1() const noexcept
		{
			return m_key1;
		}

		const Key& key2() const noexcept
		{
			return m_key2;
		}

		constexpr uint64 asUint64() const noexcept
		{
			return (uint64(m_key1.asUint32()) << 32) | uint64(m_key2.asUint32());
		}

		String name() const
		{
			return m_key1.name() + S3DCHAR('+') + m_key2.name();
		}
	};

	/// <summary>
	/// キーの組み合わせ（プラス）を設定します。
	/// </summary>
	/// <param name="key1">
	/// 1 つ目のキー
	/// </param>
	/// <param name="key2">
	/// 2 つ目のキー
	/// </param>
	/// <returns>
	/// キーの組み合わせ（プラス）
	/// </returns>
	inline constexpr KeyConjunction operator +(const Key& key1, const Key& key2) noexcept
	{
		return{ key1, key2 };
	}

	/// <summary>
	/// 2 つのキーが同じキーを示しているかを返します。
	/// </summary>
	/// <param name="key1">
	/// 比較するキー
	/// </param>
	/// <param name="key2">
	/// 比較するキー
	/// </param>
	/// <returns>
	/// 2 つのキーが同じキーを示している場合 true, それ以外の場合は false
	/// </returns>
	inline constexpr bool operator ==(const KeyConjunction& conjunction1, const KeyConjunction& conjunction2) noexcept
	{
		return conjunction1.asUint64() == conjunction2.asUint64();
	}

	/// <summary>
	/// 2 つのキーが異なるキーを示しているかを返します。
	/// </summary>
	/// <param name="key1">
	/// 比較するキー
	/// </param>
	/// <param name="key2">
	/// 比較するキー
	/// </param>
	/// <returns>
	/// 2 つのキーが異なるキーを示している場合 true, それ以外の場合は false
	/// </returns>
	inline constexpr bool operator !=(const KeyConjunction& conjunction1, const KeyConjunction& conjunction2) noexcept
	{
		return conjunction1.asUint64() != conjunction2.asUint64();
	}

	inline constexpr bool operator <(const KeyConjunction& conjunction1, const KeyConjunction& conjunction2) noexcept
	{
		return conjunction1.asUint64() < conjunction2.asUint64();
	}

	inline constexpr bool operator <=(const KeyConjunction& conjunction1, const KeyConjunction& conjunction2) noexcept
	{
		return conjunction1.asUint64() <= conjunction2.asUint64();
	}

	inline constexpr bool operator >(const KeyConjunction& conjunction1, const KeyConjunction& conjunction2) noexcept
	{
		return conjunction1.asUint64() > conjunction2.asUint64();
	}

	inline constexpr bool operator >=(const KeyConjunction& conjunction1, const KeyConjunction& conjunction2) noexcept
	{
		return conjunction1.asUint64() >= conjunction2.asUint64();
	}
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting KeyConjunction
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[ ] istream
//	[ ] wistream
//	[p] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	inline void Formatter(FormatData& formatData, const KeyConjunction& conjunction)
	{
		formatData.string.append(conjunction.name());
	}

	template <class CharType>
	inline std::basic_ostream<CharType> & operator <<(std::basic_ostream<CharType> os, const KeyConjunction& conjunction)
	{
		return os << conjunction.name();
	}
}
//
//////////////////////////////////////////////////////////////////////////////
