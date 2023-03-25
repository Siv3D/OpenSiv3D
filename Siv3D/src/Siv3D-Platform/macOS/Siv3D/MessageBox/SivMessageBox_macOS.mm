//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/MessageBox.hpp>
# import <Cocoa/Cocoa.h>

namespace s3d
{
	namespace detail
	{
		static MessageBoxResult ShowMessageBox(const StringView title, const StringView text, const MessageBoxStyle style, const int32 type)
		{
			const std::string titleS = title.narrow();
			const std::string textS = text.narrow();
			
			NSAlert* alert = [[NSAlert alloc] init];
			[alert setMessageText:[NSString stringWithCString:titleS.c_str() encoding:NSUTF8StringEncoding]];
			[alert setInformativeText:[NSString stringWithCString:textS.c_str() encoding:NSUTF8StringEncoding]];
			
			const NSAlertStyle styles[] = {
				NSAlertStyleInformational,
				NSAlertStyleInformational,
				NSAlertStyleWarning,
				NSAlertStyleCritical,
				NSAlertStyleInformational,
			};
			[alert setAlertStyle: styles[FromEnum(style)]];
			
			switch (type)
			{
				case 0:
					[alert addButtonWithTitle: @"OK"];
					break;
				case 1:
					[alert addButtonWithTitle: @"OK"];
					[alert addButtonWithTitle: @"Cancel"];
					break;
				case 2:
					[alert addButtonWithTitle: @"Yes"];
					[alert addButtonWithTitle: @"No"];
					break;
			}
			
			const long resultIndex = [alert runModal];
			
			if (type == 0) // [OK]
			{
				return MessageBoxResult::OK;
			}
			else if (type == 1) // [OK][Cancel]
			{
				return (resultIndex == NSAlertFirstButtonReturn ? MessageBoxResult::OK : MessageBoxResult::Cancel);
			}
			else // [Yes][No]
			{
				return (resultIndex == NSAlertFirstButtonReturn ? MessageBoxResult::Yes : MessageBoxResult::No);
			}
		}
	}

	namespace System
	{
		MessageBoxResult MessageBoxOK(const StringView title, const StringView text, const MessageBoxStyle style)
		{
			return detail::ShowMessageBox(title, text, style, 0);
		}

		MessageBoxResult MessageBoxOKCancel(const StringView title, const StringView text, const MessageBoxStyle style)
		{
			return detail::ShowMessageBox(title, text, style, 1);
		}

		MessageBoxResult MessageBoxYesNo(const StringView title, const StringView text, const MessageBoxStyle style)
		{
			return detail::ShowMessageBox(title, text, style, 2);
		}
	}
}
