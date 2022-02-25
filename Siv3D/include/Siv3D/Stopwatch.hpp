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
# if  __has_include(<compare>)
#	include <compare>
# endif
# include "Common.hpp"
# include "ISteadyClock.hpp"
# include "Duration.hpp"
# include "FormatData.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	/// @brief ストップウォッチ
	class Stopwatch
	{
	public:

		/// @brief ストップウォッチを作成します。
		/// @param startImmediately 即座に計測を開始する場合は `StartImmediately::Yes`
		/// @param pSteadyClock 基準時刻取得用のカスタム関数。nullptr の場合はシステム時刻
		SIV3D_NODISCARD_CXX20
		explicit Stopwatch(StartImmediately startImmediately = StartImmediately::No, ISteadyClock* pSteadyClock = nullptr);

		/// @brief 指定した時間だけ経過し一時停止している状態のストップウォッチを作成します。
		/// @param startTime 経過時間
		/// @param startImmediately 即座に計測を開始する場合は `StartImmediately::Yes`
		/// @param pSteadyClock 基準時刻取得用のカスタム関数。nullptr の場合はシステム時刻
		SIV3D_NODISCARD_CXX20
		explicit Stopwatch(const Duration& startTime, StartImmediately startImmediately = StartImmediately::No, ISteadyClock* pSteadyClock = nullptr);

		/// @brief ストップウォッチが動作中であるかを示します（開始後の一時停止も動作中に含みます）。
		/// @return ストップウォッチが開始されている、または開始後一時停止中である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isStarted() const noexcept;

		/// @brief ストップウォッチが一時停止中であるかを示します。
		/// @return ストップウォッチが開始後一時停止中である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isPaused() const noexcept;

		/// @brief ストップウォッチが時間を計測中であるかを示します。
		/// @return ストップウォッチが開始されていて、なおかつ一時停止中でない場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isRunning() const noexcept;

		/// @brief ストップウォッチを開始・再開します。
		void start();

		/// @brief 開始しているストップウォッチを一時停止します。
		void pause();

		/// @brief ストップウォッチが一時停止中である場合、再開します。
		void resume();

		/// @brief ストップウォッチを停止し、経過時間を 0 にリセットします。
		void reset() noexcept;

		/// @brief 経過時間を 0 にリセットして、ストップウォッチを再び開始します。
		void restart();

		/// @brief ストップウォッチの経過時間を変更します。
		/// @param time 新しく設定する経過時間
		/// @remark 指定した時間だけ経過している状態にします。計測中であるかの状態は引き継がれます。
		void set(const Duration& time);

		/// @brief 経過時間を [日] で返します。
		/// @return 経過時間 [日]
		[[nodiscard]]
		int32 d() const;

		/// @brief 経過時間を [日] で返します。
		/// @return 経過時間 [日]
		[[nodiscard]]
		int64 d64() const;

		/// @brief 経過時間を [日] で返します。
		/// @return 経過時間 [日]
		[[nodiscard]]
		double dF() const;

		/// @brief 経過時間を [時] で返します。
		/// @return 経過時間 [時]
		[[nodiscard]]
		int32 h() const;

		/// @brief 経過時間を [時] で返します。
		/// @return 経過時間 [時]
		[[nodiscard]]
		int64 h64() const;

		/// @brief 経過時間を [時] で返します。
		/// @return 経過時間 [時]
		[[nodiscard]]
		double hF() const;

		/// @brief 経過時間を [分] で返します。
		/// @return 経過時間 [分]
		[[nodiscard]]
		int32 min() const;

		/// @brief 経過時間を [分] で返します。
		/// @return 経過時間 [分]
		[[nodiscard]]
		int64 min64() const;

		/// @brief 経過時間を [分] で返します。
		/// @return 経過時間 [分]
		[[nodiscard]]
		double minF() const;

		/// @brief 経過時間を [秒] で返します。
		/// @return 経過時間 [秒]
		[[nodiscard]]
		int32 s() const;

		/// @brief 経過時間を [秒] で返します。
		/// @return 経過時間 [秒]
		[[nodiscard]]
		int64 s64() const;

		/// @brief 経過時間を [秒] で返します。
		/// @return 経過時間 [秒]
		[[nodiscard]]
		double sF() const;

		/// @brief 経過時間を [ミリ秒] で返します。
		/// @return 経過時間 [ミリ秒]
		[[nodiscard]]
		int32 ms() const;

		/// @brief 経過時間を [ミリ秒] で返します。
		/// @return 経過時間 [ミリ秒]
		[[nodiscard]]
		int64 ms64() const;

		/// @brief 経過時間を [ミリ秒] で返します。
		/// @return 経過時間 [ミリ秒]
		[[nodiscard]]
		double msF() const;

		/// @brief 経過時間を [マイクロ秒] で返します。
		/// @return 経過時間 [マイクロ秒]
		[[nodiscard]]
		int64 us() const;

		/// @brief 経過時間を [マイクロ秒] で返します。
		/// @return 経過時間 [マイクロ秒]
		[[nodiscard]]
		int64 us64() const;

		/// @brief 経過時間を [マイクロ秒] で返します。
		/// @return 経過時間 [マイクロ秒]
		[[nodiscard]]
		double usF() const;

		/// @brief 経過時間を返します。
		/// @return 経過時間
		[[nodiscard]]
		Duration elapsed() const;

		/// @brief 経過時間を文字列に変換します。
		/// DD		日 (00-)
		/// D		日 (0-)
		/// dd		日 (00-)
		/// d		日 (0-)
		/// HH		時 (00-)
		/// H		時 (0-)
		/// hh		時 (00-24)
		/// h		時 (0-24)
		/// MM		分 (00-)
		/// M		分 (0-)
		/// mm		分 (00-59)
		/// m		分 (0-59)
		/// SS		秒 (00-)
		/// S		秒 (0-)
		/// ss		秒 (00-59)
		/// s		秒 (0-59)
		/// X		ミリ秒 (0-)
		/// x		小数点以下 1 桁秒 (0-9)
		/// xx		小数点以下 2 桁秒 (00-99)
		/// xxx		小数点以下 3 桁秒 (000-999)
		/// @param format フォーマット指定
		/// @return フォーマットされた時間
		[[nodiscard]]
		String format(StringView format = U"H:mm:ss.xx"_sv) const;

	# if __cpp_impl_three_way_comparison

		/// @brief 経過時間を比較します。
		/// @param s ストップウォッチ
		/// @param timeUs 比較する時間
		/// @return 比較の結果
		[[nodiscard]]
		friend auto operator <=>(const Stopwatch& s, const MicrosecondsF& timeUs)
		{
			return (s.usF() <=> timeUs.count());
		}

	# else

		/// @brief 経過時間を比較します。
		/// @param s ストップウォッチ
		/// @param time 比較する時間
		/// @return 比較の結果
		[[nodiscard]]
		friend bool operator <(const Stopwatch& s, const MicrosecondsF& time)
		{
			return (s.elapsed() < time);
		}

		/// @brief 経過時間を比較します。
		/// @param s ストップウォッチ
		/// @param time 比較する時間
		/// @return 比較の結果
		[[nodiscard]]
		friend bool operator <=(const Stopwatch& s, const MicrosecondsF& time)
		{
			return (s.elapsed() <= time);
		}

		/// @brief 経過時間を比較します。
		/// @param s ストップウォッチ
		/// @param time 比較する時間
		/// @return 比較の結果
		[[nodiscard]]
		friend bool operator >(const Stopwatch& s, const MicrosecondsF& time)
		{
			return (s.elapsed() > time);
		}

		/// @brief 経過時間を比較します。
		/// @param s ストップウォッチ
		/// @param time 比較する時間
		/// @return 比較の結果
		[[nodiscard]]
		friend bool operator >=(const Stopwatch& s, const MicrosecondsF& time)
		{
			return (s.elapsed() >= time);
		}

		/// @brief 経過時間を比較します。
		/// @param time 比較する時間
		/// @param s ストップウォッチ
		/// @return 比較の結果
		[[nodiscard]]
		friend bool operator <(const MicrosecondsF& time, const Stopwatch& s)
		{
			return (time < s.elapsed());
		}

		/// @brief 経過時間を比較します。
		/// @param time 比較する時間
		/// @param s ストップウォッチ
		/// @return 比較の結果
		[[nodiscard]]
		friend bool operator <=(const MicrosecondsF& time, const Stopwatch& s)
		{
			return (time <= s.elapsed());
		}

		/// @brief 経過時間を比較します。
		/// @param time 比較する時間
		/// @param s ストップウォッチ
		/// @return 比較の結果
		[[nodiscard]]
		friend bool operator >(const MicrosecondsF& time, const Stopwatch& s)
		{
			return (time > s.elapsed());
		}

		/// @brief 経過時間を比較します。
		/// @param time 比較する時間
		/// @param s ストップウォッチ
		/// @return 比較の結果
		[[nodiscard]]
		friend bool operator >=(const MicrosecondsF& time, const Stopwatch& s)
		{
			return (time >= s.elapsed());
		}

	# endif

		/// @brief 
		/// @tparam CharType 
		/// @param output 
		/// @param value 
		/// @return 
		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Stopwatch& value)
		{
			return output << value.format();
		}

		/// @brief 
		/// @param formatData 
		/// @param value 
		friend void Formatter(FormatData& formatData, const Stopwatch& value)
		{
			formatData.string.append(value.format());
		}

	private:

		int64 m_startTimeMicrosec = 0;

		int64 m_accumulationMicrosec = 0;

		ISteadyClock* m_pSteadyClock = nullptr;

		bool m_isStarted = false;

		bool m_pausing = true;
	};
}

# include "detail/Stopwatch.ipp"
