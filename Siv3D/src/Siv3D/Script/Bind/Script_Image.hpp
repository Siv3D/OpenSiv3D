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

# include <Siv3D/Script.hpp>
# include <Siv3D/Image.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	template <>
	struct RefWrapper<Image> : Image
	{
	private:

		int32 m_refCount = 1;

	public:

		using Image::Image;

		RefWrapper() = default;

		RefWrapper(Image&& image)
			: Image(std::move(image))
		{

		}

		void AddRef()
		{
			++m_refCount;
		}

		void Release()
		{
			if (--m_refCount == 0)
			{
				delete this;
			}
		}

		RefWrapper<Image>& assign(const RefWrapper<Image>& image)
		{
			Image::assign(image);

			return *this;
		}

		Color& opIndex(size_t x, size_t y)
		{
			return *(data() + (y * width() + x));
		}

		const Color& opIndex(size_t x, size_t y) const
		{
			return *(data() + (y * width() + x));
		}

		Color& opIndex(const Point& pos)
		{
			return *(data() + (pos.y * width() + pos.x));
		}

		const Color& opIndex(const Point& pos) const
		{
			return *(data() + (pos.y * width() + pos.x));
		}
	};
}
