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

# include <Siv3D/Twitter.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FormatUtility.hpp>
# include <Siv3D/System.hpp>

namespace s3d
{
	namespace detail
	{
		String PercentEncode(StringView str)
		{
			String result;

			for (const auto ch : Unicode::ToUTF8(str))
			{
				if (IsAlnum(ch) || ch == '-' || ch == '_' || ch == '.' || ch == '~')
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
		bool OpenTweetWindow(const String& text)
		{
			return System::LaunchBrowser(U"https://twitter.com/intent/tweet?text=" + detail::PercentEncode(text));
		}

		bool OpenLikeWindow(uint64 id)
		{
			return System::LaunchBrowser(U"https://twitter.com/intent/like?tweet_id=" + ToString(id));
		}

		bool OpenRetweetWindow(uint64 id)
		{
			return System::LaunchBrowser(U"https://twitter.com/intent/retweet?tweet_id=" + ToString(id));
		}

		bool OpenMiniProfileWindow(const String& screenName)
		{
			return System::LaunchBrowser(U"https://twitter.com/intent/user?screen_name=" + screenName);
		}

		bool OpenFollowWindow(const String& screenName)
		{
			return System::LaunchBrowser(U"https://twitter.com/intent/follow?screen_name=" + screenName);
		}
	}
}
