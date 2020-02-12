//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
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

		class VideoWriterDetail;

		std::shared_ptr<VideoWriterDetail> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		VideoWriter();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~VideoWriter();

		explicit VideoWriter(const FilePath& path, const Size& size, double fps = 60.0);

		bool open(const FilePath& path, const Size& size, double fps = 60.0);

		void close();

		[[nodiscard]] bool isOpen() const;

		[[nodiscard]] explicit operator bool() const;

		bool writeFrame(const Image& image);

		[[nodiscard]] Size size() const;
	};
}
