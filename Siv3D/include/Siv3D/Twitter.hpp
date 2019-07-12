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
# include "Fwd.hpp"

namespace s3d
{
	/// <summary>
	/// Twitter
	/// </summary>
	/// <remarks>
	/// Twitter に関する機能を提供します。
	/// </remarks>
	namespace Twitter
	{
		/// <summary>
		/// Twitter への投稿ページをユーザの既定のブラウザで開きます。
		/// </summary>
		/// <param name="text">
		/// 投稿するテキスト
		/// </param>
		/// <returns>
		/// ブラウザを起動できたら true, それ以外の場合は false
		/// </returns>
		bool OpenTweetWindow(StringView text);

		bool OpenLikeWindow(uint64 tweetID);

		bool OpenRetweetWindow(uint64 tweetID);

		bool OpenMiniProfileWindow(StringView screen_name);

		bool OpenMiniProfileWindow(uint64 user_id);

		bool OpenFollowWindow(StringView screen_name);

		bool OpenFollowWindow(uint64 user_id);
	}
}
