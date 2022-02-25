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
# include <memory>
# include "Common.hpp"
# include "Optional.hpp"
# include "Unspecified.hpp"
# include "StringView.hpp"
# include "PointVector.hpp"

namespace s3d
{
	class CascadeClassifier
	{
	public:

		SIV3D_NODISCARD_CXX20
		CascadeClassifier();

		SIV3D_NODISCARD_CXX20
		explicit CascadeClassifier(FilePathView path);

		~CascadeClassifier();

		bool open(FilePathView path);

		void close();

		bool isOpen() const;

		[[nodiscard]]
		explicit operator bool() const;

		[[nodiscard]]
		Array<Rect> detectObjects(const Image& image, int32 minNeighbors = 3, const Size& minSize = Size{ 30, 30 }, const Optional<Size>& maxSize = unspecified) const;

		[[nodiscard]]
		Array<Rect> detectObjects(const Image& image, const Array<Rect>& regions, int32 minNeighbors = 3, const Size& minSize = Size{ 30, 30 }, const Optional<Size>& maxSize = unspecified) const;

	private:

		class CascadeClassifierDetail;

		std::shared_ptr<CascadeClassifierDetail> pImpl;
	};
}
