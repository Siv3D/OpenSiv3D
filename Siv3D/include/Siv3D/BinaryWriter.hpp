//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "IWriter.hpp"
# include "String.hpp"
# include "OpenMode.hpp"

namespace s3d
{
	class BinaryWriter : public IWriter
	{
	private:

		class BinaryWriterDetail;

		std::shared_ptr<BinaryWriterDetail> pImpl;

	public:

		BinaryWriter();

		explicit BinaryWriter(FilePathView path, OpenMode openMode = OpenMode::Trunc);

		bool open(FilePathView path, OpenMode openMode = OpenMode::Trunc);

		void close();

		[[nodiscard]]
		bool isOpen() const noexcept override;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		void flush();

		void clear();

		[[nodiscard]]
		int64 size() const override;

		[[nodiscard]]
		int64 getPos() const override;

		bool setPos(int64 pos) override;

		int64 seekToEnd();

		int64 write(const void* src, int64 size) override;

		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool write(const TriviallyCopyable& src);

		[[nodiscard]]
		const FilePath& path() const noexcept;
	};
}

# include "detail/BinaryWriter.ipp"
