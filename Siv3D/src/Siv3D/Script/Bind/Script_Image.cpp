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
# include "Script_Image.hpp"
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = RefWrapper<Image>;

	BindType* DefaultConstruct()
	{
		return new BindType();
	}

	BindType* CopyConstruct(const BindType& image)
	{
		return new BindType(image);
	}

	BindType* Image_FactoryI(size_t size)
	{
		return new BindType(size);
	}

	BindType* Image_FactoryIC(size_t size, const Color& color)
	{
		return new BindType(size, color);
	}

	BindType* Image_FactoryP(const Point& size)
	{
		return new BindType(size);
	}

	BindType* Image_FactoryPC(const Point& size, const Color& color)
	{
		return new BindType(size, color);
	}

	BindType* Image_FactoryII(size_t w, size_t h)
	{
		return new BindType(w, h);
	}

	BindType* Image_FactoryIIC(size_t w, size_t h, const Color& color)
	{
		return new BindType(w, h, color);
	}

	BindType* ConstructF(const FilePath& path)
	{
		return new BindType(path);
	}

	BindType* ConstructFF(const FilePath& rgb, const FilePath& alpha)
	{
		return new BindType(rgb, alpha);
	}

	BindType* ConstructCF(const ColorF& rgb, const FilePath& alpha)
	{
		return new BindType(rgb, alpha);
	}

	BindType* ConstructEm(const Emoji& emoji)
	{
		return new BindType(emoji);
	}

	BindType* ConstructIc(const Icon& icon)
	{
		return new BindType(icon);
	}

	static bool ConvToBool(const BindType& imageRef)
	{
		return !imageRef.isEmpty();
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

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f()", asFUNCTION(DefaultConstruct), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(const Image& in)", asFUNCTION(CopyConstruct), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(uint32 size)", asFUNCTION(Image_FactoryI), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(uint32 size, const Color& in)", asFUNCTION(Image_FactoryIC), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(const Point& in)", asFUNCTION(Image_FactoryP), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(const Point& in, const Color& in)", asFUNCTION(Image_FactoryPC), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(uint32 w, uint32 h)", asFUNCTION(Image_FactoryII), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(uint32 w, uint32 h, const Color& in)", asFUNCTION(Image_FactoryIIC), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(const String& in)", asFUNCTION(ConstructF), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(const String& in, const String& in)", asFUNCTION(ConstructFF), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(const Color& in, const String& in)", asFUNCTION(ConstructCF), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(const Emoji& in)", asFUNCTION(ConstructEm), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(const Icon& in)", asFUNCTION(ConstructIc), asCALL_CDECL); assert(r >= 0);

		//explicit Image(const Grid<Color>& grid);

		//explicit Image(const Grid<ColorF>& grid);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_ADDREF, "void f()", asMETHOD(BindType, AddRef), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_RELEASE, "void f()", asMETHOD(BindType, Release), asCALL_THISCALL); assert(r >= 0);
			
		r = engine->RegisterObjectMethod(TypeName, "Image& opAssign(const Image& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Image& assign(const Image& in)", asMETHOD(BindType, assign), asCALL_THISCALL); assert(r >= 0);

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
		//[[nodiscard]] Image cloned() const
		//r = engine->RegisterObjectMethod(TypeName, "Image release()", asMETHOD(BindType, cloned), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Color& opIndex(uint32 x, uint32 y)", asMETHODPR(BindType, opIndex, (size_t, size_t), Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Color& opIndex(uint32 x, uint32 y) const", asMETHODPR(BindType, opIndex, (size_t, size_t) const, const Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& opIndex(const Point& in)", asMETHODPR(BindType, opIndex, (const Point&), Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Color& opIndex(const Point& in) const", asMETHODPR(BindType, opIndex, (const Point&) const, const Color&), asCALL_THISCALL); assert(r >= 0);


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

		//[[nodiscard]] Image clipped(const Rect& rect) const;
		//[[nodiscard]] Image clipped(int32 x, int32 y, int32 w, int32 h) const
		//[[nodiscard]] Image clipped(const Point& pos, int32 w, int32 h) const
		//[[nodiscard]] Image clipped(int32 x, int32 y, const Size& size) const
		//[[nodiscard]] Image clipped(const Point& pos, const Size& size) const
		//Image& forEach(std::function<void(Color&)> function)
		//Image& swapRB()
		//bool applyAlphaFromRChannel(const FilePath& alpha);

		r = engine->RegisterObjectMethod(TypeName, "bool save(const String& in, ImageFormat format = ImageFormat::Unspecified) const", asMETHOD(BindType, save), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool saveWithDialog() const", asMETHOD(BindType, saveWithDialog), asCALL_THISCALL); assert(r >= 0);

		//bool savePNG(const FilePath& path, PNGFilter::Flag filterFlag = PNGFilter::Default) const;
		//bool saveJPEG(const FilePath& path, int32 quality = 90) const;
		//bool savePPM(const FilePath& path, PPMType format = PPMType::AsciiRGB) const;
		//[[nodiscard]] MemoryWriter encode(ImageFormat format = ImageFormat::PNG) const;




		r = engine->RegisterObjectMethod(TypeName, "Polygon alphaToPolygon(uint32 threshold = 160, bool allowHoles = true) const", asMETHOD(BindType, alphaToPolygon), asCALL_THISCALL); assert(r >= 0);


		r = engine->RegisterObjectMethod("Line", "const Line& paint(Image& inout, const Color& in) const", asMETHODPR(Line, paint, (Image&, const Color&) const, const Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& paint(Image& inout, int32, const Color& in) const", asMETHODPR(Line, paint, (Image&, int32, const Color&) const, const Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& overwrite(Image& inout, const Color& in, bool antialiased = true) const", asMETHODPR(Line, overwrite, (Image&, const Color&, bool) const, const Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& overwrite(Image& inout, int32, const Color& in, bool antialiased = true) const", asMETHODPR(Line, overwrite, (Image&, int32, const Color&, bool) const, const Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& paintArrow(Image& inout, double, const Vec2& in, const Color& in) const", asMETHOD(Line, paintArrow), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Line", "const Line& overwriteArrow(Image& inout, double, const Vec2& in, const Color& in) const", asMETHOD(Line, overwriteArrow), asCALL_THISCALL); assert(r >= 0);


	}
}
