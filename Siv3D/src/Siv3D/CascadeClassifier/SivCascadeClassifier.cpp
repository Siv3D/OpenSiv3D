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

# include <Siv3D/CascadeClassifier.hpp>
# include <Siv3D/CascadeClassifier/CascadeClassifierDetail.hpp>

namespace s3d
{
	CascadeClassifier::CascadeClassifier()
		: pImpl{ std::make_shared<CascadeClassifierDetail>() } {}

	CascadeClassifier::CascadeClassifier(const FilePathView path)
		: CascadeClassifier{}
	{
		if (not pImpl->open(path))
		{
			return;
		}
	}

	CascadeClassifier::~CascadeClassifier()
	{
		// do nothing
	}

	bool CascadeClassifier::open(const FilePathView path)
	{
		return pImpl->open(path);
	}

	void CascadeClassifier::close()
	{
		pImpl->close();
	}

	bool CascadeClassifier::isOpen() const
	{
		return pImpl->isOpen();
	}

	CascadeClassifier::operator bool() const
	{
		return isOpen();
	}

	Array<Rect> CascadeClassifier::detectObjects(const Image& image, int32 minNeighbors, const Size& minSize, const Optional<Size>& maxSize) const
	{
		return detectObjects(image, { Rect{ image.size() } }, minNeighbors, minSize, maxSize);
	}

	Array<Rect> CascadeClassifier::detectObjects(const Image& image, const Array<Rect>& regions, int32 minNeighbors, const Size& minSize, const Optional<Size>& maxSize) const
	{
		return pImpl->detectObjects(image, regions, minNeighbors, minSize, maxSize.value_or_construct(0, 0));
	}
}
