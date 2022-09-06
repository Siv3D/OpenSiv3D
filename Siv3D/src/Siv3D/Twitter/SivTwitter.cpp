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

# include <Siv3D/Twitter.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/FormatUtility.hpp>
# include <Siv3D/FormatInt.hpp>
# include <Siv3D/Char.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static String PercentEncode(const StringView str)
		{
			String result;

			for (const auto ch : str.toUTF8())
			{
				if (IsAlnum(ch) || (ch == '-') || (ch == '_') || (ch == '.') || (ch == '~'))
				{
					result << static_cast<char32>(ch);
				}
				else
				{
					result << U'%';

					result.append(Pad(ToHex(static_cast<uint8>(ch)), { 2, U'0' }).uppercase());
				}
			}

			return result;
		}
	}

	namespace Twitter
	{
		bool OpenTweetWindow(const StringView text)
		{
			return System::LaunchBrowser(U"https://twitter.com/intent/tweet?text=" + detail::PercentEncode(text));
		}

		bool OpenLikeWindow(const uint64 tweetID)
		{
			return System::LaunchBrowser(U"https://twitter.com/intent/like?tweet_id=" + ToString(tweetID));
		}

		bool OpenRetweetWindow(const uint64 tweetID)
		{
			return System::LaunchBrowser(U"https://twitter.com/intent/retweet?tweet_id=" + ToString(tweetID));
		}

		bool OpenMiniProfileWindow(const StringView screen_name)
		{
			return System::LaunchBrowser(U"https://twitter.com/intent/user?screen_name=" + screen_name);
		}

		bool OpenMiniProfileWindow(const uint64 user_id)
		{
			return System::LaunchBrowser(U"https://twitter.com/intent/user?user_id=" + ToString(user_id));
		}

		bool OpenFollowWindow(const StringView screen_name)
		{
			return System::LaunchBrowser(U"https://twitter.com/intent/follow?screen_name=" + screen_name);
		}

		bool OpenFollowWindow(const uint64 user_id)
		{
			return System::LaunchBrowser(U"https://twitter.com/intent/follow?user_id=" + ToString(user_id));
		}
	}
}
