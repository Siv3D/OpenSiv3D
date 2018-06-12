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

# include <Siv3D/NLP_Japanese.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/Parse.hpp>
# include <Siv3D/Windows.hpp>


namespace s3d
{
	namespace detail
	{
		constexpr std::array<char32, 128> AsciiTable =
		{{
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
			16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 39, 31,
			U'　', U'！', U'＂', U'＃', U'＄', U'％', U'＆', U'＇', U'（', U'）', U'＊', U'＋', U'，', U'－', U'．', U'／',
			U'０', U'１', U'２', U'３', U'４', U'５', U'６', U'７', U'８', U'９', U'：', U'；', U'＜', U'＝', U'＞', U'？',
			U'＠', U'Ａ', U'Ｂ', U'Ｃ', U'Ｄ', U'Ｅ', U'Ｆ', U'Ｇ', U'Ｈ', U'Ｉ', U'Ｊ', U'Ｋ', U'Ｌ', U'Ｍ', U'Ｎ', U'Ｏ',
			U'Ｐ', U'Ｑ', U'Ｒ', U'Ｓ', U'Ｔ', U'Ｕ', U'Ｖ', U'Ｗ', U'Ｘ', U'Ｙ', U'Ｚ', U'［', U'＼', U'］', U'＾', U'＿',
			U'｀', U'ａ', U'ｂ', U'ｃ', U'ｄ', U'ｅ', U'ｆ', U'ｇ', U'ｈ', U'ｉ', U'ｊ', U'ｋ', U'ｌ', U'ｍ', U'ｎ', U'ｏ',
			U'ｐ', U'ｑ', U'ｒ', U'ｓ', U'ｔ', U'ｕ', U'ｖ', U'ｗ', U'ｘ', U'ｙ', U'ｚ', U'｛', U'｜', U'｝', U'～', 127,
		}};

		String Convert(const String& text)
		{
			String result(text);

			for (auto& ch : result)
			{
				if (ch < 128)
				{
					ch = AsciiTable[ch];
				}
			}

			return result;
		}

		FilePath ToTextFile(const String& input)
		{
			const FilePath tmpPath = FileSystem::UniqueFilePath();

			const std::string utf8 = input.toUTF8();

			BinaryWriter(tmpPath).write(utf8.data(), utf8.size());

			return tmpPath;
		}

		bool AnalyzeJapaneseMorphology(const FilePath& input, const FilePath& output, const FilePath& exePath, const FilePath& modelPath)
		{
			if (!FileSystem::Exists(input)
				|| !FileSystem::Exists(exePath)
				|| !FileSystem::Exists(modelPath))
			{
				return false;
			}

		# if defined(SIV3D_TARGET_WINDOWS)

			std::wstring command = UR"-({} --model="{}" --output="{}" "{}")-"_fmt(exePath, modelPath, output, input).toWstr();

			STARTUPINFO si	= {};
			si.cb			= sizeof(si);
			si.dwFlags		= STARTF_USESHOWWINDOW;
			si.wShowWindow	= SW_HIDE;
			PROCESS_INFORMATION pi = {};

			const bool ret = (::CreateProcessW(nullptr, command.data(), nullptr, nullptr, false,
				CREATE_DEFAULT_ERROR_MODE | NORMAL_PRIORITY_CLASS, nullptr, nullptr, &si, &pi) != 0);

			::CloseHandle(pi.hThread);
			::WaitForSingleObject(pi.hProcess, INFINITE);
			::CloseHandle(pi.hProcess);

			return ret;

		# else
			
			const std::string command = UR"-({} --model="{}" --output="{}" "{}")-"_fmt(exePath, modelPath, output, input).toUTF8();

			return (std::system(command.c_str()) == 0);

		# endif
		}

		Array<String> SplitMorphemeElements(const String& text)
		{
			enum class MState
			{
				Element,
				Quoted,
				QuotedEscaped,
				Escaped
			} state = MState::Element;

			Array<String> result;
			
			String word;

			for (const auto& ch : text)
			{
				if (state == MState::Element)
				{
					if (ch == U' ')
					{
						result << word;

						word.clear();
					}
					else if (ch == U'\\')
					{
						state = MState::Escaped;
					}
					else if (ch == U'\"')
					{
						state = MState::Quoted;
					}
					else
					{
						word << ch;
					}
				}
				else if (state == MState::Quoted)
				{
					if (ch == U'\\')
					{
						state = MState::QuotedEscaped;
					}
					else if (ch == U'\"')
					{
						state = MState::Element;
					}
					else
					{
						word << ch;
					}
				}
				else if (state == MState::QuotedEscaped)
				{
					if (ch == U't')
					{
						word << U'\t';
					}
					else if (ch == U' ')
					{
						word << U' ';
					}

					state = MState::Quoted;
				}
				else if (state == MState::Escaped)
				{
					if (ch == U't')
					{
						word << U'\t';
					}
					else if (ch == U' ')
					{
						word << U' ';
					}

					state = MState::Element;
				}
			}

			result << word;

			return result;
		}
	}

	namespace NLP
	{
		namespace Japanese
		{
			Array<Morpheme> AnalyzeMorphology(const String& text, const FilePath& exePath, const FilePath& modelPath)
			{
				const String normalized = detail::Convert(text);

				const FilePath tmpPath = detail::ToTextFile(normalized);

				const FilePath outTmpPath = FileSystem::UniqueFilePath();

				const bool result = detail::AnalyzeJapaneseMorphology(tmpPath, outTmpPath, exePath, modelPath);

				FileSystem::Remove(tmpPath);

				if (!result)
				{
					return Array<Morpheme>();
				}

				TextReader reader(outTmpPath, TextEncoding::UTF8_NO_BOM);

				Array<Morpheme> morphemes;

				String line;

				while (reader.readLine(line))
				{
					Array<String> elements = detail::SplitMorphemeElements(line);

					if (elements.size() != 12
						&& elements.size() != 13
						&& elements.size() != 1)
					{
						//Logger << line;
						//Logger << elements;
						continue;
					}

					//Logger << elements;

					if (elements.size() <= 1)
					{
						morphemes.emplace_back();
					}
					else if (elements.front() != U"@")
					{
						morphemes.emplace_back();
						auto& morpheme = morphemes.back();
						morpheme.surface			= std::move(elements[0]);
						morpheme.reading			= std::move(elements[1]);
						morpheme.surfaceBase		= std::move(elements[2]);
						morpheme.wordClass			= std::move(elements[3]);
						morpheme.wordClassID		= static_cast<WordClass>(ParseOpt<int32>(elements[4]).value_or(0));
						morpheme.wordSubClass		= std::move(elements[5]);
						morpheme.wordSubClassID		= ParseOpt<int32>(elements[6]).value_or(0);
						morpheme.conjugatedType		= std::move(elements[7]);
						morpheme.conjugatedTypeID	= ParseOpt<int32>(elements[8]).value_or(0);
						morpheme.conjugatedForm		= std::move(elements[9]);
						morpheme.conjugatedFormID	= ParseOpt<int32>(elements[10]).value_or(0);
						morpheme.features			= std::move(elements[11]);
					}
					else
					{
						std::unique_ptr<Morpheme> pMorpheme = std::make_unique<Morpheme>();
						auto& morpheme = *pMorpheme;
						morpheme.surface			= std::move(elements[1]);
						morpheme.reading			= std::move(elements[2]);
						morpheme.surfaceBase		= std::move(elements[3]);
						morpheme.wordClass			= std::move(elements[4]);
						morpheme.wordClassID		= static_cast<WordClass>(ParseOpt<int32>(elements[5]).value_or(0));
						morpheme.wordSubClass		= std::move(elements[6]);
						morpheme.wordSubClassID		= ParseOpt<int32>(elements[7]).value_or(0);
						morpheme.conjugatedType		= std::move(elements[8]);
						morpheme.conjugatedTypeID	= ParseOpt<int32>(elements[9]).value_or(0);
						morpheme.conjugatedForm		= std::move(elements[10]);
						morpheme.conjugatedFormID	= ParseOpt<int32>(elements[11]).value_or(0);
						morpheme.features			= std::move(elements[12]);
						
						morphemes.back().options.push_back(std::move(pMorpheme));
					}
				}

				reader.close();

				FileSystem::Remove(outTmpPath);

				return morphemes;
			}
		}
	}
}


/*
U"",
U"特殊",
U"動詞",
U"形容詞",
U"判定詞",
U"助動詞",
U"名詞",
U"指示詞",
U"副詞",
U"助詞",
U"接続詞",
U"連体詞",
U"感動詞",
U"接頭辞",
U"接尾辞",
U"未定義語",
*/
