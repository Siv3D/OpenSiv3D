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

# include <Siv3D/Script.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/Icon.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/DrawableText.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = Image;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const BindType& image, BindType* self)
	{
		new(self) BindType(image);
	}

	static void Image_FactoryI(size_t size, BindType* self)
	{
		new(self) BindType(size);
	}

	static void Image_FactoryIC(size_t size, const Color& color, BindType* self)
	{
		new(self) BindType(size, color);
	}

	static void Image_FactoryP(const Point& size, BindType* self)
	{
		new(self) BindType(size);
	}

	static void Image_FactoryPC(const Point& size, const Color& color, BindType* self)
	{
		new(self) BindType(size, color);
	}

	static void Image_FactoryII(size_t w, size_t h, BindType* self)
	{
		new(self) BindType(w, h);
	}

	static void Image_FactoryIIC(size_t w, size_t h, const Color& color, BindType* self)
	{
		new(self) BindType(w, h, color);
	}

	static void ConstructF(const FilePath& path, BindType* self)
	{
		new(self) BindType(path);
	}

	static void ConstructFF(const FilePath& rgb, const FilePath& alpha, BindType* self)
	{
		new(self) BindType(rgb, alpha);
	}

	static void ConstructCF(const ColorF& rgb, const FilePath& alpha, BindType* self)
	{
		new(self) BindType(rgb, alpha);
	}

	static void ConstructEm(const Emoji& emoji, BindType* self)
	{
		new(self) BindType(emoji);
	}

	static void ConstructIcI(const Icon& icon, int32 size, BindType* self)
	{
		new(self) BindType(icon, size);
	}

	static void Destruct(BindType* self)
	{
		self->~Image();
	}

	static Color* OpIndexUU(size_t x, size_t y, BindType* image)
	{
		const size_t index = y * image->width() + x;

		if (index >= image->num_pixels())
		{
			asIScriptContext* ctx = asGetActiveContext();
			if (ctx)
				ctx->SetException("Image::operator[]: Index out of bounds");
			return nullptr;
		}

		return (image->data() + index);
	}

	static const Color* OpIndexUUC(size_t x, size_t y, const BindType* image)
	{
		const size_t index = y * image->width() + x;

		if (index >= image->num_pixels())
		{
			asIScriptContext* ctx = asGetActiveContext();
			if (ctx)
				ctx->SetException("Image::operator[]: Index out of bounds");
			return nullptr;
		}

		return (image->data() + index);
	}

	static Color* OpIndexP(const Point& pos, BindType* image)
	{
		const size_t index = pos.y * image->width() + pos.x;

		if (index >= image->num_pixels())
		{
			asIScriptContext* ctx = asGetActiveContext();
			if (ctx)
				ctx->SetException("Image::operator[]: Index out of bounds");
			return nullptr;
		}

		return (image->data() + index);
	}

	static const Color* OpIndexPC(const Point& pos, const BindType* image)
	{
		const size_t index = pos.y * image->width() + pos.x;

		if (index >= image->num_pixels())
		{
			asIScriptContext* ctx = asGetActiveContext();
			if (ctx)
				ctx->SetException("Image::operator[]: Index out of bounds");
			return nullptr;
		}

		return (image->data() + index);
	}

	static bool ConvToBool(const BindType& image)
	{
		return static_cast<bool>(image);
	}

	static bool Save(const String& path, int32 format, const BindType& image)
	{
		return image.save(path, ToEnum<ImageFormat>(static_cast<uint8>(format)));
	}

	void RegisterImage(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Image";

		[[maybe_unused]] int32 r = 0;

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Image& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(size_t size) explicit", asFUNCTION(Image_FactoryI), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(size_t size, const Color& in)", asFUNCTION(Image_FactoryIC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in) explicit", asFUNCTION(Image_FactoryP), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in, const Color& in)", asFUNCTION(Image_FactoryPC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(size_t w, size_t h)", asFUNCTION(Image_FactoryII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(size_t w, size_t h, const Color& in)", asFUNCTION(Image_FactoryIIC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in) explicit", asFUNCTION(ConstructF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, const String& in)", asFUNCTION(ConstructFF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in, const String& in)", asFUNCTION(ConstructCF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Emoji& in) explicit", asFUNCTION(ConstructEm), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Icon& in, int32)", asFUNCTION(ConstructIcI), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& opAssign(const Image& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "int32 width() const", asMETHODPR(BindType, width, () const, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 height() const", asMETHODPR(BindType, height, () const, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point size() const", asMETHODPR(BindType, size, () const, Size), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 stride() const", asMETHODPR(BindType, stride, () const, uint32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 num_pixels() const", asMETHODPR(BindType, num_pixels, () const, uint32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "size_t size_bytes() const", asMETHODPR(BindType, size_bytes, () const, size_t), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHODPR(BindType, isEmpty, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void shrink_to_fit()", asMETHOD(BindType, shrink_to_fit), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void clear()", asMETHOD(BindType, clear), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void release()", asMETHOD(BindType, release), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void swap(Image& inout)", asMETHODPR(BindType, swap, (Image&), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image cloned() const", asMETHODPR(BindType, cloned, () const, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Color& opIndex(uint32 x, uint32 y)", asFUNCTION(OpIndexUU), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Color& opIndex(uint32 x, uint32 y) const", asFUNCTION(OpIndexUUC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& opIndex(const Point& in)", asFUNCTION(OpIndexP), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Color& opIndex(const Point& in) const", asFUNCTION(OpIndexPC), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void fill(Color)", asMETHODPR(BindType, fill, (Color), void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void resize(size_t x, size_t y)", asMETHODPR(BindType, resize, (size_t, size_t), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void resize(Point)", asMETHODPR(BindType, resize, (Size), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void resize(size_t x, size_t y, const Color& in)", asMETHODPR(BindType, resize, (size_t, size_t, Color), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void resize(Point, Color)", asMETHODPR(BindType, resize, (Size, Color), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void resizeRows(size_t, Color)", asMETHODPR(BindType, resizeRows, (size_t, Color), void), asCALL_THISCALL); assert(r >= 0);

		//getPixel()
		//samplePixel()

		r = engine->RegisterObjectMethod(TypeName, "Image clipped(const Rect& in) const", asMETHODPR(BindType, clipped, (const Rect&) const&, Image), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image clipped(int32 x, int32 y, int32 w, int32 h) const", asMETHODPR(BindType, clipped, (int32, int32, int32, int32) const&, Image), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image clipped(const Point& in pos, int32 w, int32 h) const", asMETHODPR(BindType, clipped, (const Point&, int32, int32) const&, Image), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image clipped(int32 x, int32 y, const Point& in size) const", asMETHODPR(BindType, clipped, (int32, int32, const Point&) const&, Image), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image clipped(const Point& in pos, const Point& in size) const", asMETHODPR(BindType, clipped, (const Point&, const Size&) const&, Image), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image squareClipped() const", asMETHODPR(BindType, squareClipped, () const&, Image), asCALL_THISCALL); assert(r >= 0);

		//forEach()

		r = engine->RegisterObjectMethod(TypeName, "Image& RGBAtoBGRA()", asMETHODPR(BindType, RGBAtoBGRA, (), Image&), asCALL_THISCALL); assert(r >= 0);
		
		//bool applyAlphaFromRChannel(FilePathView alpha);

		r = engine->RegisterObjectMethod(TypeName, "bool save(const String& in, ImageFormat format = ImageFormat::Unspecified) const", asFUNCTION(Save), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool saveWithDialog() const", asMETHODPR(BindType, saveWithDialog, () const, bool), asCALL_THISCALL); assert(r >= 0);


		// ...

		r = engine->RegisterObjectMethod(TypeName, "Image& negate()", asMETHODPR(BindType, negate, (), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image negated() const", asMETHODPR(BindType, negated, () const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& grayscale()", asMETHODPR(BindType, grayscale, (), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image grayscaled() const", asMETHODPR(BindType, grayscaled, () const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& sepia()", asMETHODPR(BindType, sepia, (), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image sepiaed() const", asMETHODPR(BindType, sepiaed, () const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& posterize(int32)", asMETHODPR(BindType, posterize, (int32), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image posterized(int32) const", asMETHODPR(BindType, posterized, (int32) const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& brighten(int32)", asMETHODPR(BindType, brighten, (int32), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image brightened(int32) const", asMETHODPR(BindType, brightened, (int32) const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& mirror()", asMETHODPR(BindType, mirror, (), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image mirrored() const", asMETHODPR(BindType, mirrored, () const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& flip()", asMETHODPR(BindType, flip, (), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image flipped() const", asMETHODPR(BindType, flipped, () const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& rotate90()", asMETHODPR(BindType, rotate90, (), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image rotated90() const", asMETHODPR(BindType, rotated90, () const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& rotate180()", asMETHODPR(BindType, rotate180, (), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image rotated180() const", asMETHODPR(BindType, rotated180, () const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& rotate270()", asMETHODPR(BindType, rotate270, (), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image rotated270() const", asMETHODPR(BindType, rotated270, () const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& gammaCorrect(double)", asMETHODPR(BindType, gammaCorrect, (double), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image gammaCorrected(double) const", asMETHODPR(BindType, gammaCorrected, (double) const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& threshold(uint8, bool invertColor = InvertColor::No)", asMETHODPR(BindType, threshold, (uint8, InvertColor), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image thresholded(uint8, bool invertColor = InvertColor::No) const", asMETHODPR(BindType, thresholded, (uint8, InvertColor) const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& threshold_Otsu(bool invertColor = InvertColor::No)", asMETHODPR(BindType, threshold_Otsu, (InvertColor), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image thresholded_Otsu(bool invertColor = InvertColor::No) const", asMETHODPR(BindType, thresholded_Otsu, (InvertColor) const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& adaptiveThreshold(AdaptiveThresholdMethod method, int32 blockSize, double c, bool invertColor = InvertColor::No)", asMETHODPR(BindType, adaptiveThreshold, (AdaptiveThresholdMethod, int32, double, InvertColor), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image adaptiveThresholded(AdaptiveThresholdMethod method, int32 blockSize, double c, bool invertColor = InvertColor::No) const", asMETHODPR(BindType, mirrored, () const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& mosaic(int32)", asMETHODPR(BindType, mosaic, (int32), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image& mosaic(int32, int32)", asMETHODPR(BindType, mosaic, (int32, int32), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image mosaiced(int32) const", asMETHODPR(BindType, mosaiced, (int32) const&, Image), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image mosaiced(int32, int32) const", asMETHODPR(BindType, mosaiced, (int32, int32) const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& spread(int32)", asMETHODPR(BindType, spread, (int32), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image& spread(int32, int32)", asMETHODPR(BindType, spread, (int32, int32), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image spreaded(int32) const", asMETHODPR(BindType, spreaded, (int32) const, Image), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image spreaded(int32, int32) const", asMETHODPR(BindType, spreaded, (int32, int32) const, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& blur(int32, BorderType borderType = BorderType::Reflect_101)", asMETHODPR(BindType, blur, (int32, BorderType), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image& blur(int32, int32, BorderType borderType = BorderType::Reflect_101)", asMETHODPR(BindType, blur, (int32, int32, BorderType), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image blurred(int32, BorderType borderType = BorderType::Reflect_101) const", asMETHODPR(BindType, blurred, (int32, BorderType) const&, Image), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image blurred(int32, int32, BorderType borderType = BorderType::Reflect_101) const", asMETHODPR(BindType, blurred, (int32, int32, BorderType) const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& medianBlur(int32)", asMETHODPR(BindType, medianBlur, (int32), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image medianBlurred(int32) const", asMETHODPR(BindType, medianBlurred, (int32) const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& gaussianBlur(int32, BorderType borderType = BorderType::Reflect_101)", asMETHODPR(BindType, gaussianBlur, (int32, BorderType), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image& gaussianBlur(int32, int32, BorderType borderType = BorderType::Reflect_101)", asMETHODPR(BindType, gaussianBlur, (int32, int32, BorderType), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image gaussianBlurred(int32, BorderType borderType = BorderType::Reflect_101) const", asMETHODPR(BindType, gaussianBlurred, (int32, BorderType) const&, Image), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image gaussianBlurred(int32, int32, BorderType borderType = BorderType::Reflect_101) const", asMETHODPR(BindType, gaussianBlurred, (int32, int32, BorderType) const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& bilateralFilter(int32 d, double sigmaColor, double sigmaSpace, BorderType borderType = BorderType::Reflect_101)", asMETHODPR(BindType, bilateralFilter, (int32, double, double, BorderType), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image bilateralFiltered(int32 d, double sigmaColor, double sigmaSpace, BorderType borderType = BorderType::Reflect_101) const", asMETHODPR(BindType, bilateralFiltered, (int32, double, double, BorderType) const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& dilate(int32 iterations = 1)", asMETHODPR(BindType, dilate, (int32), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image dilated(int32 iterations = 1) const", asMETHODPR(BindType, dilated, (int32) const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& erode(int32 iterations = 1)", asMETHODPR(BindType, erode, (int32), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image eroded(int32 iterations = 1) const", asMETHODPR(BindType, eroded, (int32) const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& floodFill(const Point& in, const Color& in, FloodFillConnectivity connectivity = FloodFillConnectivity::Value4, int32 lowerDifference = 0, int32 upperDifference = 0)", asMETHODPR(BindType, floodFill, (const Point&, const Color&, FloodFillConnectivity, int32, int32), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image floodFilled(const Point& in, const Color& in, FloodFillConnectivity connectivity = FloodFillConnectivity::Value4, int32 lowerDifference = 0, int32 upperDifference = 0) const", asMETHODPR(BindType, floodFilled, (const Point&, const Color&, FloodFillConnectivity, int32, int32) const&, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& scale(int32 width, int32 height, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto)", asMETHODPR(BindType, scale, (int32, int32, InterpolationAlgorithm), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image scaled(int32 width, int32 height, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto) const", asMETHODPR(BindType, scaled, (int32, int32, InterpolationAlgorithm) const, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& scale(const Point& in, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto)", asMETHODPR(BindType, scale, (const Point&, InterpolationAlgorithm), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image scaled(const Point& in, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto) const", asMETHODPR(BindType, scaled, (const Point&, InterpolationAlgorithm) const, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& scale(double scaling, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto)", asMETHODPR(BindType, scale, (double, InterpolationAlgorithm), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image scaled(double scaling, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto) const", asMETHODPR(BindType, scaled, (double, InterpolationAlgorithm) const, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& fit(int32 width, int32 height, bool allowScaleUp = AllowScaleUp::Yes, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto)", asMETHODPR(BindType, fit, (int32, int32, AllowScaleUp, InterpolationAlgorithm), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image fitted(int32 width, int32 height, bool allowScaleUp = AllowScaleUp::Yes, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto) const", asMETHODPR(BindType, fitted, (int32, int32, AllowScaleUp, InterpolationAlgorithm) const, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& fit(const Point& in, bool allowScaleUp = AllowScaleUp::Yes, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto)", asMETHODPR(BindType, fit, (const Point&, AllowScaleUp, InterpolationAlgorithm), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image fitted(const Point& in, bool allowScaleUp = AllowScaleUp::Yes, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto) const", asMETHODPR(BindType, fitted, (const Point&, AllowScaleUp, InterpolationAlgorithm) const, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& border(int32, const Color& in = Palette::White)", asMETHODPR(BindType, border, (int32, const Color&), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image bordered(int32, const Color& in = Palette::White) const", asMETHODPR(BindType, bordered, (int32, const Color&) const, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image& border(int32 top, int32 right, int32 bottom, int32 left, const Color& in = Palette::White)", asMETHODPR(BindType, border, (int32, int32, int32, int32, const Color&), Image&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image bordered(int32 top, int32 right, int32 bottom, int32 left, const Color& in = Palette::White) const", asMETHODPR(BindType, bordered, (int32, int32, int32, int32, const Color&) const, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image warpAffine(const Mat3x2& in, const Color& in = Color(0, 0)) const", asMETHODPR(BindType, warpAffine, (const Mat3x2&, const Color&) const, Image), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image rotated(double, const Color& in = Color(0, 0)) const", asMETHODPR(BindType, rotated, (double, const Color&) const, Image), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image warpPerspective(const Quad& in, const Color& in = Color(0, 0)) const", asMETHODPR(BindType, warpPerspective, (const Quad&, const Color&) const, Image), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void paint(Image& inout, int32, int32, const Color& in = Palette::White) const", asMETHODPR(BindType, paint, (Image&, int32, int32, const Color&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void paint(Image& inout, const Point& in, const Color& in = Palette::White) const", asMETHODPR(BindType, paint, (Image&, const Point&, const Color&) const, void), asCALL_THISCALL); assert(r >= 0);
		
		r = engine->RegisterObjectMethod(TypeName, "void stamp(Image& inout, int32, int32, const Color& in = Palette::White) const", asMETHODPR(BindType, stamp, (Image&, int32, int32, const Color&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void stamp(Image& inout, const Point& in, const Color& in = Palette::White) const", asMETHODPR(BindType, stamp, (Image&, const Point&, const Color&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void overwrite(Image& inout, int32, int32) const", asMETHODPR(BindType, overwrite, (Image&, int32, int32) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void overwrite(Image& inout, Point) const", asMETHODPR(BindType, overwrite, (Image&, Point) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void paintAt(Image& inout, int32, int32, const Color& in = Palette::White) const", asMETHODPR(BindType, paintAt, (Image&, int32, int32, const Color&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void paintAt(Image& inout, const Point& in, const Color& in = Palette::White) const", asMETHODPR(BindType, paintAt, (Image&, const Point&, const Color&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void stampAt(Image& inout, int32, int32, const Color& in = Palette::White) const", asMETHODPR(BindType, stampAt, (Image&, int32, int32, const Color&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void stampAt(Image& inout, const Point& in, const Color& in = Palette::White) const", asMETHODPR(BindType, stampAt, (Image&, const Point&, const Color&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void overwriteAt(Image& inout, int32, int32) const", asMETHODPR(BindType, overwriteAt, (Image&, int32, int32) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void overwriteAt(Image& inout, Point) const", asMETHODPR(BindType, overwriteAt, (Image&, Point) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon alphaToPolygon(uint32 threshold = 160, bool allowHoles = AllowHoles::Yes) const", asMETHODPR(BindType, alphaToPolygon, (uint32, AllowHoles) const, Polygon), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon alphaToPolygonCentered(uint32 threshold = 160, bool allowHoles = AllowHoles::Yes) const", asMETHODPR(BindType, alphaToPolygonCentered, (uint32, AllowHoles) const, Polygon), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon grayscaleToPolygon(uint32 threshold = 160, bool allowHoles = AllowHoles::Yes) const", asMETHODPR(BindType, grayscaleToPolygon, (uint32, AllowHoles) const, Polygon), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon grayscaleToPolygonCentered(uint32 threshold = 160, bool allowHoles = AllowHoles::Yes) const", asMETHODPR(BindType, grayscaleToPolygonCentered, (uint32, AllowHoles) const, Polygon), asCALL_THISCALL); assert(r >= 0);


		{
			constexpr char EnumName[] = "AdaptiveThresholdMethod";
			r = engine->RegisterEnumValue(EnumName, "Mean", static_cast<int32>(AdaptiveThresholdMethod::Mean)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Gaussian", static_cast<int32>(AdaptiveThresholdMethod::Gaussian)); assert(r >= 0);
		}

		{
			constexpr char EnumName[] = "BorderType";
			r = engine->RegisterEnumValue(EnumName, "Replicate", static_cast<int32>(BorderType::Replicate)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Reflect", static_cast<int32>(BorderType::Reflect)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Reflect_101", static_cast<int32>(BorderType::Reflect_101)); assert(r >= 0);
		}

		{
			constexpr char EnumName[] = "FloodFillConnectivity";
			r = engine->RegisterEnumValue(EnumName, "Value4", static_cast<int32>(FloodFillConnectivity::Value4)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Value8", static_cast<int32>(FloodFillConnectivity::Value8)); assert(r >= 0);
		}

		{
			constexpr char EnumName[] = "InterpolationAlgorithm";
			r = engine->RegisterEnumValue(EnumName, "Nearest", static_cast<int32>(InterpolationAlgorithm::Nearest)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Linear", static_cast<int32>(InterpolationAlgorithm::Linear)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Cubic", static_cast<int32>(InterpolationAlgorithm::Cubic)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Area", static_cast<int32>(InterpolationAlgorithm::Area)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Lanczos", static_cast<int32>(InterpolationAlgorithm::Lanczos)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Auto", static_cast<int32>(InterpolationAlgorithm::Auto)); assert(r >= 0);
		}




		r = engine->RegisterObjectMethod("Point", "const Point& paint(Image& inout, const Color& in) const", asMETHODPR(Point, paint, (Image&, const Color&) const, const Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Point", "const Point& overwrite(Image& inout, const Color& in) const", asMETHODPR(Point, overwrite, (Image&, const Color&) const, const Point&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("Line", "const Line& paint(Image& inout, const Color& in) const", asMETHODPR(Line, paint, (Image&, const Color&) const, const Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& paint(Image& inout, int32, const Color& in) const", asMETHODPR(Line, paint, (Image&, int32, const Color&) const, const Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& overwrite(Image& inout, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(Line, overwrite, (Image&, const Color&, Antialiased) const, const Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& overwrite(Image& inout, int32, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(Line, overwrite, (Image&, int32, const Color&, Antialiased) const, const Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& paintArrow(Image& inout, double, const Vec2& in, const Color& in) const", asMETHODPR(Line, paintArrow, (Image&, double, const Vec2&, const Color&) const, const Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& overwriteArrow(Image& inout, double, const Vec2& in, const Color& in) const", asMETHODPR(Line, overwriteArrow, (Image&, double, const Vec2&, const Color&) const, const Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& paintDoubleHeadedArrow(Image& inout, double, const Vec2& in, const Color& in) const", asMETHODPR(Line, paintDoubleHeadedArrow, (Image&, double, const Vec2&, const Color&) const, const Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& overwriteDoubleHeadedArrow(Image& inout, double, const Vec2& in, const Color& in) const", asMETHODPR(Line, overwriteDoubleHeadedArrow, (Image&, double, const Vec2&, const Color&) const, const Line&), asCALL_THISCALL); assert(r >= 0);


		r = engine->RegisterObjectMethod("Rect", "const Rect& paint(Image& inout, const Color& in) const", asMETHODPR(Rect, paint, (Image&, const Color&) const, const Rect&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Rect", "const Rect& overwrite(Image& inout, const Color& in) const", asMETHODPR(Rect, overwrite, (Image&, const Color&) const, const Rect&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Rect", "const Rect& paintFrame(Image& inout, const Color& in) const", asMETHODPR(Rect, paintFrame, (Image&, int32, int32, const Color&) const, const Rect&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Rect", "const Rect& overwriteFrame(Image& inout, const Color& in) const", asMETHODPR(Rect, overwriteFrame, (Image&, int32, int32, const Color&) const, const Rect&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("RectF", "const RectF& paint(Image& inout, const Color& in) const", asMETHODPR(RectF, paint, (Image&, const Color&) const, const RectF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("RectF", "const RectF& overwrite(Image& inout, const Color& in) const", asMETHODPR(RectF, overwrite, (Image&, const Color&) const, const RectF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("RectF", "const RectF& paintFrame(Image& inout, const Color& in) const", asMETHODPR(RectF, paintFrame, (Image&, int32, int32, const Color&) const, const RectF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("RectF", "const RectF& overwriteFrame(Image& inout, const Color& in) const", asMETHODPR(RectF, overwriteFrame, (Image&, int32, int32, const Color&) const, const RectF&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("Circle", "const Circle& paint(Image& inout, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(Circle, paint, (Image&, const Color&, Antialiased) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Circle", "const Circle& overwrite(Image& inout, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(Circle, overwrite, (Image&, const Color&, Antialiased) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Circle", "const Circle& paintFrame(Image& inout, double, double, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(Circle, paintFrame, (Image&, double, double, const Color&, Antialiased) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Circle", "const Circle& overwriteFrame(Image& inout, double, double, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(Circle, overwriteFrame, (Image&, double, double, const Color&, Antialiased) const, const Circle&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("Ellipse", "const Ellipse& paint(Image& inout, const Color& in) const", asMETHODPR(Ellipse, paint, (Image&, const Color&) const, const Ellipse&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Ellipse", "const Ellipse& overwrite(Image& inout, const Color& in) const", asMETHODPR(Ellipse, overwrite, (Image&, const Color&) const, const Ellipse&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("Triangle", "const Triangle& paint(Image& inout, const Color& in) const", asMETHODPR(Triangle, paint, (Image&, const Color&) const, const Triangle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Triangle", "const Triangle& overwrite(Image& inout, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(Triangle, overwrite, (Image&, const Color&, Antialiased) const, const Triangle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Triangle", "const Triangle& paintFrame(Image& inout, int32, const Color& in) const", asMETHODPR(Triangle, paintFrame, (Image&, int32, const Color&) const, const Triangle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Triangle", "const Triangle& overwriteFrame(Image& inout, int32, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(Triangle, overwriteFrame, (Image&, int32, const Color&, Antialiased) const, const Triangle&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("Quad", "const Quad& paint(Image& inout, const Color& in) const", asMETHODPR(Quad, paint, (Image&, const Color&) const, const Quad&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Quad", "const Quad& overwrite(Image& inout, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(Quad, overwrite, (Image&, const Color&, Antialiased) const, const Quad&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Quad", "const Quad& paintFrame(Image& inout, int32, const Color& in) const", asMETHODPR(Quad, paintFrame, (Image&, int32, const Color&) const, const Quad&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Quad", "const Quad& overwriteFrame(Image& inout, int32, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(Quad, overwriteFrame, (Image&, int32, const Color&, Antialiased) const, const Quad&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("RoundRect", "const RoundRect& paint(Image& inout, const Color& in) const", asMETHODPR(RoundRect, paint, (Image&, const Color&) const, const RoundRect&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("RoundRect", "const RoundRect& overwrite(Image& inout, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(RoundRect, overwrite, (Image&, const Color&, Antialiased) const, const RoundRect&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("RoundRect", "const RoundRect& paintFrame(Image& inout, int32, int32, const Color& in) const", asMETHODPR(RoundRect, paintFrame, (Image&, int32, int32, const Color&) const, const RoundRect&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("RoundRect", "const RoundRect& overwriteFrame(Image& inout, int32, int32, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(RoundRect, overwriteFrame, (Image&, int32, int32, const Color&, Antialiased) const, const RoundRect&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("Polygon", "const Polygon& paint(Image& inout, const Color& in) const", asMETHODPR(Polygon, paint, (Image&, const Color&) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Polygon", "const Polygon& paint(Image& inout, double, double, const Color& in) const", asMETHODPR(Polygon, paint, (Image&, double, double, const Color&) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Polygon", "const Polygon& paint(Image& inout, const Vec2& in, const Color& in) const", asMETHODPR(Polygon, paint, (Image&, const Vec2&, const Color&) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Polygon", "const Polygon& overwrite(Image& inout, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(Polygon, overwrite, (Image&, const Color&, Antialiased) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Polygon", "const Polygon& overwrite(Image& inout, double, double, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(Polygon, overwrite, (Image&, double, double, const Color&, Antialiased) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Polygon", "const Polygon& overwrite(Image& inout, const Vec2& in, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(Polygon, overwrite, (Image&, const Vec2&, const Color&, Antialiased) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("LineString", "const LineString& paint(Image& inout, const Color& in) const", asMETHODPR(LineString, paint, (Image&, const Color&) const, const LineString&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("LineString", "const LineString& paint(Image& inout, int32, const Color& in) const", asMETHODPR(LineString, paint, (Image&, int32, const Color&) const, const LineString&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("LineString", "const LineString& paintClosed(Image& inout, const Color& in) const", asMETHODPR(LineString, paintClosed, (Image&, const Color&) const, const LineString&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("LineString", "const LineString& paintClosed(Image& inout, int32, const Color& in) const", asMETHODPR(LineString, paintClosed, (Image&, int32, const Color&) const, const LineString&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("LineString", "const LineString& overwrite(Image& inout, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(LineString, overwrite, (Image&, const Color&, Antialiased) const, const LineString&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("LineString", "const LineString& overwrite(Image& inout, int32, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(LineString, overwrite, (Image&, int32, const Color&, Antialiased) const, const LineString&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("LineString", "const LineString& overwriteClosed(Image& inout, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(LineString, overwriteClosed, (Image&, const Color&, Antialiased) const, const LineString&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("LineString", "const LineString& overwriteClosed(Image& inout, int32, const Color& in, bool antialiased = Antialiased::Yes) const", asMETHODPR(LineString, overwriteClosed, (Image&, int32, const Color&, Antialiased) const, const LineString&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("DrawableText", "void paint(Image& inout, double, double, const Color& in = Palette::White) const", asMETHODPR(DrawableText, paint, (Image&, double, double, const Color&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("DrawableText", "void paint(Image& inout, const Vec2& in pos, const Color& in = Palette::White) const", asMETHODPR(DrawableText, paint, (Image&, const Vec2&, const Color&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("DrawableText", "void paintAt(Image& inout, double, double, const Color& in = Palette::White) const", asMETHODPR(DrawableText, paintAt, (Image&, double, double, const Color&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("DrawableText", "void paintAt(Image& inout, const Vec2& in pos, const Color& in = Palette::White) const", asMETHODPR(DrawableText, paintAt, (Image&, const Vec2&, const Color&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("DrawableText", "void stamp(Image& inout, double, double, const Color& in = Palette::White) const", asMETHODPR(DrawableText, stamp, (Image&, double, double, const Color&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("DrawableText", "void stamp(Image& inout, const Vec2& in pos, const Color& in = Palette::White) const", asMETHODPR(DrawableText, stamp, (Image&, const Vec2&, const Color&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("DrawableText", "void stampAt(Image& inout, double, double, const Color& in = Palette::White) const", asMETHODPR(DrawableText, stampAt, (Image&, double, double, const Color&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("DrawableText", "void stampAt(Image& inout, const Vec2& in pos, const Color& in = Palette::White) const", asMETHODPR(DrawableText, stampAt, (Image&, const Vec2&, const Color&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("DrawableText", "void overwrite(Image& inout, double, double) const", asMETHODPR(DrawableText, overwrite, (Image&, double, double) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("DrawableText", "void overwrite(Image& inout, const Vec2& in pos) const", asMETHODPR(DrawableText, overwrite, (Image&, const Vec2&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("DrawableText", "void overwriteAt(Image& inout, double, double) const", asMETHODPR(DrawableText, overwriteAt, (Image&, double, double) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("DrawableText", "void overwriteAt(Image& inout, const Vec2& in pos) const", asMETHODPR(DrawableText, overwriteAt, (Image&, const Vec2&) const, void), asCALL_THISCALL); assert(r >= 0);
	}
}
