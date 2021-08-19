//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/SimpleGUI.hpp>
# include "../angelscript/scriptarray.h"

namespace s3d
{
	using namespace AngelScript;

	namespace detail
	{
		static Array<String> ToArrayString(const CScriptArray* arr)
		{
			Array<String> options(arr->GetSize());

			for (uint32 i = 0; i < options.size(); ++i)
			{
				options[i] = *static_cast<const String*>(arr->At(i));
			}

			return options;
		}
	}

	static RectF HeadlineRegion1(const String& text, const Vec2& pos, double width)
	{
		return SimpleGUI::HeadlineRegion(text, pos, width);
	}

	static RectF HeadlineRegion2(const String& text, const Vec2& pos, const uint8&)
	{
		return SimpleGUI::HeadlineRegion(text, pos, none);
	}

	void Headline1(const String& text, const Vec2& pos, double width, bool enabled)
	{
		SimpleGUI::Headline(text, pos, width, enabled);
	}

	void Headline2(const String& text, const Vec2& pos, const uint8&, bool enabled)
	{
		SimpleGUI::Headline(text, pos, none, enabled);
	}

	bool Button1(const String& text, const Vec2& pos, double width, bool enabled)
	{
		return SimpleGUI::Button(text, pos, width, enabled);
	}

	bool Button2(const String& text, const Vec2& pos, const uint8&, bool enabled)
	{
		return SimpleGUI::Button(text, pos, none, enabled);
	}

	bool Slider1(double& value, const Vec2& pos, double sliderWidth, bool enabled)
	{
		return SimpleGUI::Slider(value, pos, sliderWidth, enabled);
	}

	bool Slider2(double& value, double min, double max, const Vec2& pos, double sliderWidth, bool enabled)
	{
		return SimpleGUI::Slider(value, min, max, pos, sliderWidth, enabled);
	}

	bool Slider3(const String& label, double& value, const Vec2& pos, double sliderWidth, bool enabled)
	{
		return SimpleGUI::Slider(label, value, pos, sliderWidth, enabled);
	}

	bool Slider4(const String& label, double& value, double min, double max, const Vec2& pos, double sliderWidth, bool enabled)
	{
		return SimpleGUI::Slider(label, value, min, max, pos, sliderWidth, enabled);
	}


	bool VerticalSlider1(double& value, const Vec2& pos, double sliderWidth, bool enabled)
	{
		return SimpleGUI::VerticalSlider(value, pos, sliderWidth, enabled);
	}

	bool VerticalSlider2(double& value, double min, double max, const Vec2& pos, double sliderWidth, bool enabled)
	{
		return SimpleGUI::VerticalSlider(value, min, max, pos, sliderWidth, enabled);
	}


	bool RadioButtons1(size_t& index, const CScriptArray* arr, const Vec2& pos, double width, bool enabled)
	{
		return SimpleGUI::RadioButtons(index, detail::ToArrayString(arr), pos, width, enabled);
	}

	bool RadioButtons2(size_t& index, const CScriptArray* arr, const Vec2& pos, const uint8&, bool enabled)
	{
		return SimpleGUI::RadioButtons(index, detail::ToArrayString(arr), pos, none, enabled);
	}

	bool HorizontalRadioButtons1(size_t& index, const CScriptArray* arr, const Vec2& pos, double width, bool enabled)
	{
		return SimpleGUI::HorizontalRadioButtons(index, detail::ToArrayString(arr), pos, width, enabled);
	}

	bool HorizontalRadioButtons2(size_t& index, const CScriptArray* arr, const Vec2& pos, const uint8&, bool enabled)
	{
		return SimpleGUI::HorizontalRadioButtons(index, detail::ToArrayString(arr), pos, none, enabled);
	}

	bool CheckBox1(bool& checked, const String& text, const Vec2& pos, double width, bool enabled)
	{
		return SimpleGUI::CheckBox(checked, text, pos, width, enabled);
	}

	bool CheckBox2(bool& checked, const String& text, const Vec2& pos, const uint8&, bool enabled)
	{
		return SimpleGUI::CheckBox(checked, text, pos, none, enabled);
	}

	bool ColorPicker(HSV& hsv, const Vec2& pos, bool enabled)
	{
		return SimpleGUI::ColorPicker(hsv, pos, enabled);
	}

	void RegisterSimpleGUI(asIScriptEngine* engine)
	{
		int32 r = 0;

		r = engine->SetDefaultNamespace("SimpleGUI"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("RectF HeadlineRegion(const String& in, const Vec2& in, double width)", asFUNCTION(HeadlineRegion1), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("RectF HeadlineRegion(const String& in, const Vec2& in, None_t = unspecified)", asFUNCTION(HeadlineRegion2), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void Headline(const String& in, const Vec2& in, double width, bool enabled = true)", asFUNCTION(Headline1), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void Headline(const String& in, const Vec2& in, None_t = unspecified, bool enabled = true)", asFUNCTION(Headline2), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool Button(const String& in, const Vec2& in, double width, bool enabled = true)", asFUNCTION(Button1), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool Button(const String& in, const Vec2& in, None_t = unspecified, bool enabled = true)", asFUNCTION(Button2), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool Slider(double& inout value, const Vec2& in pos, double sliderWidth = 120.0, bool enabled = true)", asFUNCTION(Slider1), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool Slider(double& inout value, double min, double max, const Vec2& in pos, double sliderWidth = 120.0, bool enabled = true)", asFUNCTION(Slider2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool Slider(const String& in, double& inout value, const Vec2& in pos, double sliderWidth = 120.0, bool enabled = true)", asFUNCTION(Slider3), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool Slider(const String& in, double& inout value, double min, double max, const Vec2& in pos, double sliderWidth = 120.0, bool enabled = true)", asFUNCTION(Slider4), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool VerticalSlider(double& inout value, const Vec2& in pos, double sliderHeight = 120.0, bool enabled = true)", asFUNCTION(VerticalSlider1), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool VerticalSlider(double& inout value, double min, double max, const Vec2& in pos, double sliderHeight = 120.0, bool enabled = true)", asFUNCTION(VerticalSlider2), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool CheckBox(bool& inout, const String& in, const Vec2& in, double width, bool enabled = true)", asFUNCTION(CheckBox1), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool CheckBox(bool& inout, const String& in, const Vec2& in, None_t = unspecified, bool enabled = true)", asFUNCTION(CheckBox2), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool RadioButtons(size_t& inout, const Array<String>& in, const Vec2& in, double width, bool enabled = true)", asFUNCTION(RadioButtons1), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool RadioButtons(size_t& inout, const Array<String>& in, const Vec2& in, None_t = unspecified, bool enabled = true)", asFUNCTION(RadioButtons2), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool HorizontalRadioButtons(size_t& inout, const Array<String>& in, const Vec2& in, double width, bool enabled = true)", asFUNCTION(HorizontalRadioButtons1), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool HorizontalRadioButtons(size_t& inout, const Array<String>& in, const Vec2& in, None_t = unspecified, bool enabled = true)", asFUNCTION(HorizontalRadioButtons2), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool ColorPicker(HSV& inout, const Vec2& in, bool enabled = true)", asFUNCTION(ColorPicker), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
