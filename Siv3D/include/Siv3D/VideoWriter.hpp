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
# include <memory>
# include "Fwd.hpp"

namespace s3d
{
	class VideoWriter
	{
	private:

		class CVideoWriter;

		std::shared_ptr<CVideoWriter> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		VideoWriter();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~VideoWriter();

		explicit VideoWriter(const FilePath& path);

		bool open(const FilePath& path);

		void close();

		[[nodiscard]] bool isOpened() const;
	};
}
