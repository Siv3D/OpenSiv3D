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
# include "StringView.hpp"

namespace s3d
{
	/// @brief Twitter に関する機能
	namespace Twitter
	{
		/// @brief Twitter への投稿ページをユーザの既定のブラウザで開きます。
		/// @param text 投稿するテキスト
		/// @return ブラウザを起動できたら true, それ以外の場合は false
		bool OpenTweetWindow(StringView text);

		bool OpenLikeWindow(uint64 tweetID);

		bool OpenRetweetWindow(uint64 tweetID);

		bool OpenMiniProfileWindow(StringView screen_name);

		bool OpenMiniProfileWindow(uint64 user_id);

		bool OpenFollowWindow(StringView screen_name);

		bool OpenFollowWindow(uint64 user_id);
	}
}
