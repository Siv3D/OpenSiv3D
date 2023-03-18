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
# include <Siv3D/SimpleGUI.hpp>
# include "ScriptArray.hpp"

namespace s3d
{
	using namespace AngelScript;

	static RectF HeadlineRegion1(const String& text, const Vec2& pos, double width)
	{
		return SimpleGUI::HeadlineRegion(text, pos, width);
	}

	static RectF HeadlineRegion2(const String& text, const Vec2& pos, const uint8&)
	{
		return SimpleGUI::HeadlineRegion(text, pos, none);
	}

	static void Headline1(const String& text, const Vec2& pos, double width, bool enabled)
	{
		SimpleGUI::Headline(text, pos, width, enabled);
	}

	static void Headline2(const String& text, const Vec2& pos, const uint8&, bool enabled)
	{
		SimpleGUI::Headline(text, pos, none, enabled);
	}

	static bool Button1(const String& text, const Vec2& pos, double width, bool enabled)
	{
		return SimpleGUI::Button(text, pos, width, enabled);
	}

	static bool Button2(const String& text, const Vec2& pos, const uint8&, bool enabled)
	{
		return SimpleGUI::Button(text, pos, none, enabled);
	}

	static bool Slider1(double& value, const Vec2& pos, double sliderWidth, bool enabled)
	{
		return SimpleGUI::Slider(value, pos, sliderWidth, enabled);
	}

	static bool Slider2(double& value, double min, double max, const Vec2& pos, double sliderWidth, bool enabled)
	{
		return SimpleGUI::Slider(value, min, max, pos, sliderWidth, enabled);
	}

	static bool Slider3(const String& label, double& value, const Vec2& pos, double labelWidth, double sliderWidth, bool enabled)
	{
		return SimpleGUI::Slider(label, value, pos, labelWidth, sliderWidth, enabled);
	}

	static bool Slider4(const String& label, double& value, double min, double max, const Vec2& pos, double labelWidth, double sliderWidth, bool enabled)
	{
		return SimpleGUI::Slider(label, value, min, max, pos, labelWidth, sliderWidth, enabled);
	}


	static bool VerticalSlider1(double& value, const Vec2& pos, double sliderWidth, bool enabled)
	{
		return SimpleGUI::VerticalSlider(value, pos, sliderWidth, enabled);
	}

	static bool VerticalSlider2(double& value, double min, double max, const Vec2& pos, double sliderWidth, bool enabled)
	{
		return SimpleGUI::VerticalSlider(value, min, max, pos, sliderWidth, enabled);
	}


	static bool RadioButtons1(size_t& index, const CScriptArray* arr, const Vec2& pos, double width, bool enabled)
	{
		return SimpleGUI::RadioButtons(index, detail::FromScriptArray<String>(arr), pos, width, enabled);
	}

	static bool RadioButtons2(size_t& index, const CScriptArray* arr, const Vec2& pos, const uint8&, bool enabled)
	{
		return SimpleGUI::RadioButtons(index, detail::FromScriptArray<String>(arr), pos, none, enabled);
	}

	static bool HorizontalRadioButtons1(size_t& index, const CScriptArray* arr, const Vec2& pos, double width, bool enabled)
	{
		return SimpleGUI::HorizontalRadioButtons(index, detail::FromScriptArray<String>(arr), pos, width, enabled);
	}

	static bool HorizontalRadioButtons2(size_t& index, const CScriptArray* arr, const Vec2& pos, const uint8&, bool enabled)
	{
		return SimpleGUI::HorizontalRadioButtons(index, detail::FromScriptArray<String>(arr), pos, none, enabled);
	}

	static bool CheckBox1(bool& checked, const String& text, const Vec2& pos, double width, bool enabled)
	{
		return SimpleGUI::CheckBox(checked, text, pos, width, enabled);
	}

	static bool CheckBox2(bool& checked, const String& text, const Vec2& pos, const uint8&, bool enabled)
	{
		return SimpleGUI::CheckBox(checked, text, pos, none, enabled);
	}

	static bool TextBox1(TextEditState& text, const Vec2& pos, double width, size_t maxChars, bool enabled)
	{
		return SimpleGUI::TextBox(text, pos, width, maxChars, enabled);
	}

	static bool TextBox2(TextEditState& text, const Vec2& pos, double width, const uint8&, bool enabled)
	{
		return SimpleGUI::TextBox(text, pos, width, unspecified, enabled);
	}

	//static bool TextBoxAt(TextEditState& text, const Vec2& center, double width, size_t maxChars, bool enabled) // FIXME ->ScriptSimpleGUI.cpp
	//{
	//	Optional<size_t> d = (maxChars > 0) ? (Optional<size_t>)maxChars : unspecified;
	//	return SimpleGUI::TextBoxAt(text, center, width, d, enabled);
	//}

	static bool ColorPicker(HSV& hsv, const Vec2& pos, bool enabled)
	{
		return SimpleGUI::ColorPicker(hsv, pos, enabled);
	}

	void RegisterSimpleGUI(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

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
			r = engine->RegisterGlobalFunction("bool Slider(const String& in, double& inout value, const Vec2& in pos, double labelWidth = 80.0, double sliderWidth = 120.0, bool enabled = true)", asFUNCTION(Slider3), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool Slider(const String& in, double& inout value, double min, double max, const Vec2& in pos, double labelWidth = 80.0, double sliderWidth = 120.0, bool enabled = true)", asFUNCTION(Slider4), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool VerticalSlider(double& inout value, const Vec2& in pos, double sliderHeight = 120.0, bool enabled = true)", asFUNCTION(VerticalSlider1), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool VerticalSlider(double& inout value, double min, double max, const Vec2& in pos, double sliderHeight = 120.0, bool enabled = true)", asFUNCTION(VerticalSlider2), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool CheckBox(bool& inout, const String& in, const Vec2& in, double width, bool enabled = true)", asFUNCTION(CheckBox1), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool CheckBox(bool& inout, const String& in, const Vec2& in, None_t = unspecified, bool enabled = true)", asFUNCTION(CheckBox2), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool RadioButtons(size_t& inout, const Array<String>& in, const Vec2& in, double width, bool enabled = true)", asFUNCTION(RadioButtons1), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool RadioButtons(size_t& inout, const Array<String>& in, const Vec2& in, None_t = unspecified, bool enabled = true)", asFUNCTION(RadioButtons2), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool HorizontalRadioButtons(size_t& inout, const Array<String>& in, const Vec2& in, double width, bool enabled = true)", asFUNCTION(HorizontalRadioButtons1), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool HorizontalRadioButtons(size_t& inout, const Array<String>& in, const Vec2& in, None_t = unspecified, bool enabled = true)", asFUNCTION(HorizontalRadioButtons2), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool TextBox(TextEditState& inout, const Vec2&in, double width, size_t, bool enabled = true)", asFUNCTION(TextBox1), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool TextBox(TextEditState& inout, const Vec2&in, double width = 200.0, None_t = unspecified, bool enabled = true)", asFUNCTION(TextBox2), asCALL_CDECL); assert(r >= 0);

			//r = engine->RegisterGlobalFunction("bool TextBoxAt(TextEditState& inout, const Vec2&in, double = 200.0, size_t = 0, bool enabled = true)", asFUNCTION(TextBoxAt), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool ColorPicker(HSV& inout, const Vec2& in, bool enabled = true)", asFUNCTION(ColorPicker), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
