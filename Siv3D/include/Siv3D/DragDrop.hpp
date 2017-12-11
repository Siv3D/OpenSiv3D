//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "PointVector.hpp"

namespace s3d
{
	enum class DragItemType
	{
		/// <summary>
		/// ファイルパス
		/// </summary>
		FilePaths,

		/// <summary>
		/// テキスト
		/// </summary>
		Text
	};

	struct DragStatus
	{
		/// <summary>
		/// ドラッグしているアイテムの種類
		/// </summary>
		DragItemType itemType;

		/// <summary>
		/// ドラッグしているカーソルの位置（クライアント座標）
		/// </summary>
		Point pos;
	};

	struct DroppedFilePath
	{
		/// <summary>
		/// ファイルパス
		/// </summary>
		FilePath path;

		/// <summary>
		/// ドロップされた位置（クライアント座標）
		/// </summary>
		Point pos;

		/// <summary>
		/// ドロップされた時刻（ミリ秒）
		/// </summary>
		/// <remarks>
		/// Time::GetMillisec() で取得する時刻と比較できます。
		/// </remarks>
		uint64 timeMillisec;
	};

	struct DroppedText
	{
		/// <summary>
		/// テキスト
		/// </summary>
		String text;

		/// <summary>
		/// ドロップされたクライアント位置（クライアント座標）
		/// </summary>
		Point pos;

		/// <summary>
		/// ドロップされた時刻（ミリ秒）
		/// </summary>
		/// <remarks>
		/// Time::GetMillisec() で取得する時刻と比較できます。
		/// </remarks>
		uint64 timeMillisec;
	};

	namespace DragDrop
	{
		void AcceptFilePaths(bool accept);

		void AcceptText(bool accept);

		Optional<DragStatus> DragOver();

		bool HasNewFilePaths();

		bool HasNewText();

		void Clear();

		Array<DroppedFilePath> GetDroppedFilePaths();

		Array<DroppedText> GetDroppedText();
	}
}
