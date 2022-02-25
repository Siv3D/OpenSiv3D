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

namespace s3d
{
	/// @brief 時間
	/// @remark 時間に関する機能を提供します。
	namespace Time
	{
		/// @brief アプリケーションが起動してからの経過時間を秒で返します。
		/// @return アプリケーションが起動してからの経過時間（秒）
		[[nodiscard]]
		uint64 GetSec() noexcept;

		/// @brief アプリケーションが起動してからの経過時間をミリ秒で返します。
		/// @return アプリケーションが起動してからの経過時間（ミリ秒）
		[[nodiscard]]
		uint64 GetMillisec() noexcept;

		/// @brief アプリケーションが起動してからの経過時間をマイクロ秒で返します。
		/// @return アプリケーションが起動してからの経過時間（マイクロ秒）
		[[nodiscard]]
		uint64 GetMicrosec() noexcept;

		/// @brief アプリケーションが起動してからの経過時間をナノ秒で返します。
		/// @return アプリケーションが起動してからの経過時間（ナノ秒）
		[[nodiscard]]
		uint64 GetNanosec() noexcept;

		/// @brief 協定世界時 (UTC) で 1970 年 1 月 1 日午前 0 時からの経過時間を秒で返します。
		/// @return 1970 年 1 月 1 日午前 0 時からの経過時間（秒）
		[[nodiscard]]
		uint64 GetSecSinceEpoch();

		/// @brief 協定世界時 (UTC) で 1970 年 1 月 1 日午前 0 時からの経過時間をミリ秒で返します。
		/// @return 1970 年 1 月 1 日午前 0 時からの経過時間（ミリ秒）
		[[nodiscard]]
		uint64 GetMillisecSinceEpoch();

		/// @brief 協定世界時 (UTC) で 1970 年 1 月 1 日午前 0 時からの経過時間をマイクロ秒で返します。
		/// @return 1970 年 1 月 1 日午前 0 時からの経過時間（マイクロ秒）
		[[nodiscard]]
		uint64 GetMicrosecSinceEpoch();

		/// @brief 協定世界時 (UTC) との時差を分で返します。
		/// @return 協定世界時 (UTC) との時差（分）
		[[nodiscard]]
		int32 UTCOffsetMinutes();
	}
}
