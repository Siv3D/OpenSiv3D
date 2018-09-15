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
# include <Siv3D/Circle.hpp>
# include <Siv3D/Ellipse.hpp>
# include <Siv3D/Triangle.hpp>
# include <Siv3D/Quad.hpp>
# include <Siv3D/RoundRect.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/Image.hpp>
# include "ScriptBind.hpp"

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

	static void ConstructIc(const Icon& icon, BindType* self)
	{
		new(self) BindType(icon);
	}

	static void Destruct(BindType* self)
	{
		self->~Image();
	}

	static Color* OpIndexUU(uint32 x, uint32 y, BindType* image)
	{
		const size_t index = y * image->width() + x;

		if (index >= image->num_pixels())
		{
			asIScriptContext *ctx = asGetActiveContext();
			if (ctx)
				ctx->SetException("Image::operator[]: Index out of bounds");
			return nullptr;
		}

		return (image->data() + index);
	}

	static const Color* OpIndexUUC(uint32 x, uint32 y, const BindType* image)
	{
		const size_t index = y * image->width() + x;

		if (index >= image->num_pixels())
		{
			asIScriptContext *ctx = asGetActiveContext();
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
			asIScriptContext *ctx = asGetActiveContext();
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
			asIScriptContext *ctx = asGetActiveContext();
			if (ctx)
				ctx->SetException("Image::operator[]: Index out of bounds");
			return nullptr;
		}

		return (image->data() + index);
	}

	static bool ConvToBool(const BindType& image)
	{
		return !image.isEmpty();
	}

	void RegisterImage(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Image";

		int32 r = 0;

		r = engine->RegisterEnumValue("ImageFormat", "Unknown", 0); assert(r >= 0);
		r = engine->RegisterEnumValue("ImageFormat", "DDS", 1); assert(r >= 0);
		r = engine->RegisterEnumValue("ImageFormat", "PNG", 2); assert(r >= 0);
		r = engine->RegisterEnumValue("ImageFormat", "JPEG", 3); assert(r >= 0);
		r = engine->RegisterEnumValue("ImageFormat", "JPEG2000", 4); assert(r >= 0);
		r = engine->RegisterEnumValue("ImageFormat", "BMP", 5); assert(r >= 0);
		r = engine->RegisterEnumValue("ImageFormat", "WebP", 6); assert(r >= 0);
		r = engine->RegisterEnumValue("ImageFormat", "GIF", 7); assert(r >= 0);
		r = engine->RegisterEnumValue("ImageFormat", "TIFF", 8); assert(r >= 0);
		r = engine->RegisterEnumValue("ImageFormat", "TGA", 9); assert(r >= 0);
		r = engine->RegisterEnumValue("ImageFormat", "PPM", 10); assert(r >= 0);
		r = engine->RegisterEnumValue("ImageFormat", "Unspecified", 0); assert(r >= 0);

		r = engine->RegisterEnumValue("FloodFillConnectivity", "Value4", 4); assert(r >= 0);
		r = engine->RegisterEnumValue("FloodFillConnectivity", "Value8", 8); assert(r >= 0);
		
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Image& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint32 size)", asFUNCTION(Image_FactoryI), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint32 size, const Color& in)", asFUNCTION(Image_FactoryIC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in)", asFUNCTION(Image_FactoryP), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in, const Color& in)", asFUNCTION(Image_FactoryPC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint32 w, uint32 h)", asFUNCTION(Image_FactoryII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint32 w, uint32 h, const Color& in)", asFUNCTION(Image_FactoryIIC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in)", asFUNCTION(ConstructF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, const String& in)", asFUNCTION(ConstructFF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in, const String& in)", asFUNCTION(ConstructCF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Emoji& in)", asFUNCTION(ConstructEm), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Icon& in)", asFUNCTION(ConstructIc), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//explicit Image(const Grid<Color>& grid);
		//explicit Image(const Grid<ColorF>& grid);

		r = engine->RegisterObjectMethod(TypeName, "Image& opAssign(const Image& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image& assign(const Image& in)", asMETHODPR(BindType, assign, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "int32 width() const", asMETHOD(BindType, width), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 height() const", asMETHOD(BindType, height), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point size() const", asMETHOD(BindType, size), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 stride() const", asMETHOD(BindType, stride), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 num_pixels() const", asMETHOD(BindType, num_pixels), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 size_bytes() const", asMETHOD(BindType, size_bytes), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHOD(BindType, isEmpty), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void shrink_to_fit()", asMETHOD(BindType, shrink_to_fit), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void clear()", asMETHOD(BindType, clear), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void release()", asMETHOD(BindType, release), asCALL_THISCALL); assert(r >= 0);

		//r = engine->RegisterObjectMethod(TypeName, "void swap(Image& image)", asMETHOD(BindType, swap), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image cloned()", asMETHOD(BindType, cloned), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Color& opIndex(uint32 x, uint32 y)", asFUNCTION(OpIndexUU), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Color& opIndex(uint32 x, uint32 y) const", asFUNCTION(OpIndexUUC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& opIndex(const Point& in)", asFUNCTION(OpIndexP), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Color& opIndex(const Point& in) const", asFUNCTION(OpIndexPC), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void fill(const Color& in)", asMETHOD(BindType, fill), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void resize(uint32 x, uint32 y)", asMETHODPR(BindType, resize, (size_t, size_t), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void resize(const Point& in)", asMETHODPR(BindType, resize, (const Size&), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void resize(uint32 x, uint32 y, const Color& in)", asMETHODPR(BindType, resize, (size_t, size_t, const Color&), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void resize(const Point& in, const Color& in)", asMETHODPR(BindType, resize, (const Size&, const Color&), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void resizeRows(uint32, const Color& in)", asMETHOD(BindType, resizeRows), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Color& getPixel_Repeat(int32 x, int32 y) const", asMETHODPR(BindType, getPixel_Repeat, (int32, int32) const, const Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Color& getPixel_Repeat(const Point& in) const", asMETHODPR(BindType, getPixel_Repeat, (const Point&) const, const Color&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Color& getPixel_Clamp(int32 x, int32 y) const", asMETHODPR(BindType, getPixel_Clamp, (int32, int32) const, const Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Color& getPixel_Clamp(const Point& in) const", asMETHODPR(BindType, getPixel_Clamp, (const Point&) const, const Color&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Color& getPixel_Mirror(int32 x, int32 y) const", asMETHODPR(BindType, getPixel_Mirror, (int32, int32) const, const Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Color& getPixel_Mirror(const Point& in) const", asMETHODPR(BindType, getPixel_Mirror, (const Point&) const, const Color&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "ColorF sample_Repeat(double x, double y) const", asMETHODPR(BindType, sample_Repeat, (double, double) const, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF sample_Repeat(const Vec2& in) const", asMETHODPR(BindType, sample_Repeat, (const Vec2&) const, ColorF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "ColorF sample_Clamp(double x, double y) const", asMETHODPR(BindType, sample_Clamp, (double, double) const, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF sample_Clamp(const Vec2& in) const", asMETHODPR(BindType, sample_Clamp, (const Vec2&) const, ColorF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "ColorF sample_Mirror(double x, double y) const", asMETHODPR(BindType, sample_Mirror, (double, double) const, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF sample_Mirror(const Vec2& in) const", asMETHODPR(BindType, sample_Mirror, (const Vec2&) const, ColorF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Image clipped(const Rect& in) const", asMETHODPR(BindType, clipped, (const Rect&) const, Image), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image clipped(int32 x, int32 y, int32 w, int32 h) const", asMETHODPR(BindType, clipped, (int32, int32, int32, int32) const, Image), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image clipped(const Point& in pos, int32 w, int32 h) const", asMETHODPR(BindType, clipped, (const Point&, int32, int32) const, Image), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image clipped(int32 x, int32 y, const Point& in size) const", asMETHODPR(BindType, clipped, (int32, int32, const Point&) const, Image), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image clipped(const Point& in pos, const Point& in size) const", asMETHODPR(BindType, clipped, (const Point&, const Size&) const, Image), asCALL_THISCALL); assert(r >= 0);

		//Image& forEach(std::function<void(Color&)> function)
		//Image& swapRB()
		//bool applyAlphaFromRChannel(const FilePath& alpha);

		r = engine->RegisterObjectMethod(TypeName, "bool save(const String& in, ImageFormat format = ImageFormat::Unspecified) const", asMETHOD(BindType, save), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool saveWithDialog() const", asMETHOD(BindType, saveWithDialog), asCALL_THISCALL); assert(r >= 0);

		//bool savePNG(const FilePath& path, PNGFilter::Flag filterFlag = PNGFilter::Default) const;
		//bool saveJPEG(const FilePath& path, int32 quality = 90) const;
		//bool savePPM(const FilePath& path, PPMType format = PPMType::AsciiRGB) const;
		//[[nodiscard]] MemoryWriter encode(ImageFormat format = ImageFormat::PNG) const;



		//
		//...

		r = engine->RegisterObjectMethod(TypeName, "Image& floodFill(const Point& in, const Color& in, FloodFillConnectivity connectivity = FloodFillConnectivity::Value4, int32 lowerDifference = 0, int32 upperDifference = 0) const", asMETHOD(BindType, floodFill), asCALL_THISCALL); assert(r >= 0);


		Image& floodFill(const Point& pos, const Color& color, FloodFillConnectivity connectivity = FloodFillConnectivity::Value4, int32 lowerDifference = 0, int32 upperDifference = 0);


		//...



		r = engine->RegisterObjectMethod(TypeName, "Polygon alphaToPolygon(uint32 threshold = 160, bool allowHoles = true) const", asMETHOD(BindType, alphaToPolygon), asCALL_THISCALL); assert(r >= 0);



		r = engine->RegisterObjectMethod(TypeName, "const Point& paint(Image& inout, int, const Color& in) const", asMETHOD(Point, paint), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Point& overwrite(Image& inout, int, const Color& in) const", asMETHOD(Point, overwrite), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("Line", "const Line& paint(Image& inout, const Color& in) const", asMETHODPR(Line, paint, (Image&, const Color&) const, const Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& paint(Image& inout, int32, const Color& in) const", asMETHODPR(Line, paint, (Image&, int32, const Color&) const, const Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& overwrite(Image& inout, const Color& in, bool antialiased = true) const", asMETHODPR(Line, overwrite, (Image&, const Color&, bool) const, const Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& overwrite(Image& inout, int32, const Color& in, bool antialiased = true) const", asMETHODPR(Line, overwrite, (Image&, int32, const Color&, bool) const, const Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& paintArrow(Image& inout, double, const Vec2& in, const Color& in) const", asMETHOD(Line, paintArrow), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& overwriteArrow(Image& inout, double, const Vec2& in, const Color& in) const", asMETHOD(Line, overwriteArrow), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("Rect", "const Rect& paint(Image& inout, const Color& in) const", asMETHODPR(Rect, paint, (Image&, const Color&) const, const Rect&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Rect", "const Rect& overwrite(Image& inout, const Color& in) const", asMETHODPR(Rect, overwrite, (Image&, const Color&) const, const Rect&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Rect", "const Rect& paintFrame(Image& inout, const Color& in) const", asMETHODPR(Rect, paintFrame, (Image&, int32, int32, const Color&) const, const Rect&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Rect", "const Rect& overwriteFrame(Image& inout, const Color& in) const", asMETHODPR(Rect, overwriteFrame, (Image&, int32, int32, const Color&) const, const Rect&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("RectF", "const RectF& paint(Image& inout, const Color& in) const", asMETHODPR(RectF, paint, (Image&, const Color&) const, const RectF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("RectF", "const RectF& overwrite(Image& inout, const Color& in) const", asMETHODPR(RectF, overwrite, (Image&, const Color&) const, const RectF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("RectF", "const RectF& paintFrame(Image& inout, const Color& in) const", asMETHODPR(RectF, paintFrame, (Image&, int32, int32, const Color&) const, const RectF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("RectF", "const RectF& overwriteFrame(Image& inout, const Color& in) const", asMETHODPR(RectF, overwriteFrame, (Image&, int32, int32, const Color&) const, const RectF&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("Circle", "const Circle& paint(Image& inout, const Color& in, bool antialiased = true) const", asMETHODPR(Circle, paint, (Image&, const Color&, bool) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Circle", "const Circle& overwrite(Image& inout, const Color& in, bool antialiased = true) const", asMETHODPR(Circle, overwrite, (Image&, const Color&, bool) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Circle", "const Circle& paintFrame(Image& inout, const Color& in, bool antialiased = true) const", asMETHODPR(Circle, paintFrame, (Image&, int32, int32, const Color&, bool) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Circle", "const Circle& overwriteFrame(Image& inout, const Color& in, bool antialiased = true) const", asMETHODPR(Circle, overwriteFrame, (Image&, int32, int32, const Color&, bool) const, const Circle&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("Ellipse", "const Ellipse& paint(Image& inout, const Color& in) const", asMETHODPR(Ellipse, paint, (Image&, const Color&) const, const Ellipse&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Ellipse", "const Ellipse& overwrite(Image& inout, const Color& in) const", asMETHODPR(Ellipse, overwrite, (Image&, const Color&) const, const Ellipse&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("Triangle", "const Triangle& paint(Image& inout, const Color& in) const", asMETHODPR(Triangle, paint, (Image&, const Color&) const, const Triangle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Triangle", "const Triangle& overwrite(Image& inout, const Color& in, bool antialiased = true) const", asMETHODPR(Triangle, overwrite, (Image&, const Color&, bool) const, const Triangle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Triangle", "const Triangle& paintFrame(Image& inout, int32, const Color& in) const", asMETHODPR(Triangle, paintFrame, (Image&, int32, const Color&) const, const Triangle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Triangle", "const Triangle& overwriteFrame(Image& inout, int32, const Color& in, bool antialiased = true) const", asMETHODPR(Triangle, overwriteFrame, (Image&, int32, const Color&, bool) const, const Triangle&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("Quad", "const Quad& paint(Image& inout, const Color& in) const", asMETHODPR(Quad, paint, (Image&, const Color&) const, const Quad&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Quad", "const Quad& overwrite(Image& inout, const Color& in, bool antialiased = true) const", asMETHODPR(Quad, overwrite, (Image&, const Color&, bool) const, const Quad&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Quad", "const Quad& paintFrame(Image& inout, int32, const Color& in) const", asMETHODPR(Quad, paintFrame, (Image&, int32, const Color&) const, const Quad&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Quad", "const Quad& overwriteFrame(Image& inout, int32, const Color& in, bool antialiased = true) const", asMETHODPR(Quad, overwriteFrame, (Image&, int32, const Color&, bool) const, const Quad&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("RoundRect", "const RoundRect& paint(Image& inout, const Color& in) const", asMETHODPR(RoundRect, paint, (Image&, const Color&) const, const RoundRect&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("RoundRect", "const RoundRect& overwrite(Image& inout, const Color& in, bool antialiased = true) const", asMETHODPR(RoundRect, overwrite, (Image&, const Color&, bool) const, const RoundRect&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("RoundRect", "const RoundRect& paintFrame(Image& inout, int32, int32, const Color& in) const", asMETHODPR(RoundRect, paintFrame, (Image&, int32, int32, const Color&) const, const RoundRect&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("RoundRect", "const RoundRect& overwriteFrame(Image& inout, int32, int32, const Color& in, bool antialiased = true) const", asMETHODPR(RoundRect, overwriteFrame, (Image&, int32, int32, const Color&, bool) const, const RoundRect&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("Polygon", "const Polygon& paint(Image& inout, const Color& in) const", asMETHODPR(Polygon, paint, (Image&, const Color&) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Polygon", "const Polygon& paint(Image& inout, double, double, const Color& in) const", asMETHODPR(Polygon, paint, (Image&, double, double, const Color&) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Polygon", "const Polygon& paint(Image& inout, const Vec2& in, const Color& in) const", asMETHODPR(Polygon, paint, (Image&, const Vec2&, const Color&) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Polygon", "const Polygon& overwrite(Image& inout, const Color& in, bool antialiased = true) const", asMETHODPR(Polygon, overwrite, (Image&, const Color&, bool) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Polygon", "const Polygon& overwrite(Image& inout, double, double, const Color& in, bool antialiased = true) const", asMETHODPR(Polygon, overwrite, (Image&, double, double, const Color&, bool) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Polygon", "const Polygon& overwrite(Image& inout, const Vec2& in, const Color& in, bool antialiased = true) const", asMETHODPR(Polygon, overwrite, (Image&, const Vec2&, const Color&, bool) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod("LineString", "const LineString& paint(Image& inout, const Color& in, bool isClosed = false) const", asMETHODPR(LineString, paint, (Image&, const Color&, bool) const, const LineString&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("LineString", "const LineString& paint(Image& inout, int32, const Color& in, bool isClosed = false) const", asMETHODPR(LineString, paint, (Image&, int32, const Color&, bool) const, const LineString&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("LineString", "const LineString& overwrite(Image& inout, const Color& in, bool isClosed = false, bool antialiased = true) const", asMETHODPR(LineString, overwrite, (Image&, const Color&, bool, bool) const, const LineString&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("LineString", "const LineString& overwrite(Image& inout, int32, const Color& in, bool isClosed = false, bool antialiased = true) const", asMETHODPR(LineString, overwrite, (Image&, int32, const Color&, bool, bool) const, const LineString&), asCALL_THISCALL); assert(r >= 0);

	}
}
