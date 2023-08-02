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
		constexpr std::array<std::array<StringView, 2>, 1> Warnings =
		{
			{
				U"Assets are newly created and discarded in consecutive frames. This may cause performance issues.",
				U"アセットが毎フレーム連続して新規作成・破棄されています。これはパフォーマンスの低下を引き起こします。",
			}
		};

		constexpr std::array<std::array<StringView, 2>, 1> Errors =
		{
			{
				U"Variables of type `{}` must be initialized after the engine has started. Initialization as a global variable is not processed correctly because it occurs before the engine starts.",
				U"{} 型の変数はエンジンの起動完了後に初期化される必要があります。グローバル変数として宣言すると、エンジン起動前に初期化が実行され、正常に処理できません。",
			}
		};

		constexpr std::array<StringView, 2> AdditionalMessages =
		{
			U"Pressing [OK] will open the troubleshooting page.",
			U"[OK] を押すとトラブルシューティングのページを開きます。",
		};

		constexpr std::array<StringView, 2> Languages =
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
			const StringView language = detail::Languages[languageIndex];
			const String message = U"Warning | W{}\n\n{}\n\n{}"_fmt(number, (Fmt(detail::Warnings[index][languageIndex])(hint)), detail::AdditionalMessages[languageIndex]);

			LOG_ERROR(message);
			FreestandingMessageBox::ShowError(message);
			System::LaunchBrowser(U"https://github.com/Siv3D/Troubleshooting/blob/main/{}/warnings/w{}.md"_fmt(language, number));
		}

		void Show(const Error id, const StringView hint)
		{
			const int32 number = FromEnum(id);
			const int32 index = (number - FromEnum(Error::AssetInitializationBeforeEngineStartup));
			const size_t languageIndex = detail::GetLanguageIndex();
			const StringView language = detail::Languages[languageIndex];
			const String message = U"Error | E{}\n\n{}\n\n{}"_fmt(number, (Fmt(detail::Errors[index][languageIndex])(hint)), detail::AdditionalMessages[languageIndex]);

			LOG_ERROR(message);
			FreestandingMessageBox::ShowError(message);
			System::LaunchBrowser(U"https://github.com/Siv3D/Troubleshooting/blob/main/{}/errors/e{}.md"_fmt(language, number));
		}
	}
}
