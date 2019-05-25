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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Rectangle.hpp>

namespace s3d
{
	class ISiv3DObjectDetection
	{
	public:

		static ISiv3DObjectDetection* Create();

		virtual ~ISiv3DObjectDetection() = default;

		virtual void init() = 0;

		virtual Array<Rect> detect(const Image& image, HaarCascade cascade, int32 minNeighbors, const Size& minSize, const Size& maxSize) = 0;

		virtual Array<Rect> detect(const Image& image, HaarCascade cascade, const Array<Rect>& regions, int32 minNeighbors, const Size& minSize, const Size& maxSize) = 0;
	};
}
