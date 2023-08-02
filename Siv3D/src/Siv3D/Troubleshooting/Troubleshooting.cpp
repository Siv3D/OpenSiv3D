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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>
# include <Siv3D/System.hpp>
# include "Troubleshooting.hpp"

namespace s3d
{
	namespace detail
	{
		static const Array<std::array<String, 2>> Warnings =
		{
			{
				U"Assets are newly created and discarded in consecutive frames. This may cause performance issues.",
				U"アセットが毎フレーム連続して新規作成・破棄されています。これはパフォーマンスの低下を引き起こします。",
			}
		};

		static const Array<std::array<String, 2>> Errors =
		{

		};

		static const Array<String> Languages =
		{
			U"en-us",
			U"ja-jp",
		};

		[[nodiscard]]
		static size_t GetLanguageIndex()
		{
			return (System::DefaultLanguage().lowercase().contains(U"ja") ? 1 : 0);
		}
	}

	namespace Troubleshooting
	{
		void Show(const Warning id, const StringView hint)
		{
			const int32 number = FromEnum(id);
			const int32 index = (number - FromEnum(Warning::InefficientAssetCreation));
			const size_t languageIndex = detail::GetLanguageIndex();
			const String language = detail::Languages[languageIndex];
			const String message = U"Warning W{} | {}"_fmt(number, (Fmt(detail::Warnings[index][languageIndex])(hint)));

			LOG_ERROR(message);
			FreestandingMessageBox::ShowError(message);
			System::LaunchBrowser(U"https://github.com/Siv3D/Troubleshooting/blob/main/{}/warnings/w{}.md"_fmt(language, number));
		}

		void Show(const Error id, const StringView hint)
		{
			const int32 number = FromEnum(id);
			const int32 index = (number - FromEnum(Error::Test));
			const size_t languageIndex = detail::GetLanguageIndex();
			const String language = detail::Languages[languageIndex];
			const String message = U"Error E{} | {}"_fmt(FromEnum(id), (Fmt(detail::Errors[index][languageIndex])(hint)));

			LOG_ERROR(message);
			FreestandingMessageBox::ShowError(message);
			System::LaunchBrowser(U"https://github.com/Siv3D/Troubleshooting/blob/main/{}/errors/w{}.md"_fmt(language, number));
		}
	}
}
