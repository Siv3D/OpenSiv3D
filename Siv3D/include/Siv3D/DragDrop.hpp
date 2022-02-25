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
# include "Array.hpp"
# include "Optional.hpp"
# include "DragItemType.hpp"
# include "DragStatus.hpp"
# include "DroppedFilePath.hpp"
# include "DroppedText.hpp"

namespace s3d
{
	namespace DragDrop
	{
		/// @brief ドラッグ＆ドロップでファイルパスを受け付けるかを設定します。
		/// @param accept ファイルパスを受け付けるか
		/// @remark デフォルトでは true です。
		void AcceptFilePaths(bool accept);

		/// @brief ドラッグ＆ドロップでテキストを受け付けるかを設定します。
		/// @param accept テキストを受け付けるか
		/// @remark デフォルトでは false です。
		void AcceptText(bool accept);

		/// @brief ウィンドウ上でドラッグ中のアイテムの情報を返します。
		/// @return ドラッグ中のアイテムの情報。ドラッグ中でない場合 none
		[[nodiscard]]
		Optional<DragStatus> DragOver();

		/// @brief 新しいファイルパスがドロップされたアイテムリストにあるかを返します。
		/// @return 新しいファイルパスがドロップされている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool HasNewFilePaths();

		/// @brief 新しいテキストがドロップされたアイテムリストにあるかを返します。
		/// @return 新しいテキストがドロップされている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool HasNewText();

		/// @brief ドロップされているオブジェクトの情報を消去します。
		void Clear();

		/// @brief ドロップされたファイルパスの情報一覧を返します。
		/// @remark この関数で返されたアイテムは、現在のアイテムリストから削除されます。
		/// @return ドロップされたファイルパスの情報一覧
		[[nodiscard]]
		Array<DroppedFilePath> GetDroppedFilePaths();

		/// @brief ドロップされたテキストの情報一覧を返します。
		/// @remark この関数で返されたアイテムは、現在のアイテムリストから削除されます。
		/// @return ドロップされたテキストの情報一覧
		[[nodiscard]]
		Array<DroppedText> GetDroppedText();
	}

# if SIV3D_PLATFORM(WINDOWS)

	namespace Platform::Windows::DragDrop
	{
		/// @brief 指定したファイルのドラッグを開始します。
		/// @param path ファイルパス
		void MakeDragDrop(FilePathView path);
	}

# endif
}
