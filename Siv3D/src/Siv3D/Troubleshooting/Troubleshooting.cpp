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
				U"Variables of type {} must be initialized after the engine has started. If declared as a global variable or a static member variable, initialization occurs before the engine starts, causing an error.",
				U"{} 型の変数はエンジンの起動完了後に初期化される必要があります。グローバル変数や静的メンバ変数として宣言すると、エンジン起動前に初期化が実行され、エラーを発生させます。",
			}
		};

		constexpr std::array<StringView, 2> AdditionalMessages =
		{
			U"Press [OK] to open the troubleshooting page in your web browser.",
			U"[OK] を押して Web ブラウザでトラブルシューティングのページを開きます。",
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

		void Show(const bool isError, const int32 number, const int32 messageArrayIndex, const StringView hint)
		{
			const size_t languageIndex = GetLanguageIndex();
			const StringView language = Languages[languageIndex];
			
			const String messageBody = (Fmt((isError ? detail::Errors : detail::Warnings)[messageArrayIndex][languageIndex])(hint));
			const StringView messageFooter = detail::AdditionalMessages[languageIndex];	

			// トラブルシューティングの Web ページの URL
			const String url = U"https://github.com/Siv3D/Troubleshooting/blob/main/{}/{}{}.md"_fmt(language, (isError ? U"errors/e" : U"warnings/w"), number);

			String logMessage;
			String displayMessage;

			if (isError) // エラーの場合
			{
				logMessage = U"Error (E{}) | {}\nFor more information, see: {}"_fmt(number, messageBody, url);
				displayMessage = U"Error | E{}\n\n{}\n\n{}"_fmt(number, messageBody, messageFooter);
				LOG_ERROR(logMessage);
			}
			else // 警告の場合
			{
				logMessage = U"Warning (W{}) | {}\nFor more information, see: {}"_fmt(number, messageBody, url);
				displayMessage = U"Warning | W{}\n\n{}\n\n{}"_fmt(number, messageBody, messageFooter);
				LOG_WARNING(logMessage);
			}
	
			// メッセージボックスを表示する
			FreestandingMessageBox::ShowError(displayMessage);

			// Web ブラウザで開く
			System::LaunchBrowser(url);
		}
	}

	namespace Troubleshooting
	{
		void Show(const Warning id, const StringView hint)
		{
			detail::Show(false, FromEnum(id), (FromEnum(id) - FromEnum(Warning::InefficientAssetCreation)), hint);
		}

		void Show(const Error id, const StringView hint)
		{
			detail::Show(true, FromEnum(id), (FromEnum(id) - FromEnum(Error::AssetInitializationBeforeEngineStartup)), hint);
		}
	}
}
