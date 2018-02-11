//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
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
		bool OpenTweetWindow(const String& text);

		bool OpenLikeWindow(uint64 id);

		bool OpenRetweetWindow(uint64 id);

		bool OpenMiniProfileWindow(const String& screenName);

		bool OpenFollowWindow(const String& screenName);
	}
}
