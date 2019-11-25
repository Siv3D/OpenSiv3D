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
# include <memory>
# include <variant>
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "Rectangle.hpp"
# include "Optional.hpp"
# include "String.hpp"
# include "HSV.hpp"
# include "SimpleGUI.hpp"

namespace s3d
{
	namespace SimpleGUIWidget
	{
		struct Headline
		{
			Vec2 pos = Vec2(0, 0);

			String text;

			Optional<double> width;

			bool enabled = true;
		};

		struct Button
		{
			Vec2 pos = Vec2(0, 0);

			String label;

			Optional<double> width;

			bool enabled = true;
		};

		struct Slider
		{
			Vec2 pos = Vec2(0, 0);

			String label;

			double value = 0.0;

			double min = 0.0;

			double max = 1.0;

			double labelWidth = 80.0;

			double sliderWidth = 120.0;

			bool enabled = true;
		};

		struct VerticalSlider
		{
			Vec2 pos = Vec2(0, 0);

			double min = 0.0;

			double max = 1.0;

			double value = 0.0;

			double sliderHeight = 120.0;

			bool enabled = true;
		};

		struct CheckBox
		{
			Vec2 pos = Vec2(0, 0);

			String label;

			Optional<double> width;

			bool checked = false;

			bool enabled = true;
		};

		struct RadioButtons
		{
			Vec2 pos = Vec2(0, 0);

			Array<String> options;

			Optional<double> width;

			size_t index = 0;

			bool enabled = true;
		};

		struct TextBox
		{
			Vec2 pos = Vec2(0, 0);

			TextEditState state;

			double width = 200.0;

			Optional<size_t> maxChars;

			bool enabled = true;
		};

		struct ColorPicker
		{
			Vec2 pos = Vec2(0, 0);

			HSV color = Palette::White;

			bool enabled = true;
		};
	}

	namespace SimpleGUI
	{
		enum class WidgetType
		{
			Headline,
			Button,
			Slider,
			VerticalSlider,
			CheckBox,
			RadioButtons,
			TextBox,
			ColorPicker,
		};

		struct Widget
		{
			String name;

			bool hasChanged = false;

			std::variant<SimpleGUIWidget::Headline,
				SimpleGUIWidget::Button,
				SimpleGUIWidget::Slider,
				SimpleGUIWidget::VerticalSlider,
				SimpleGUIWidget::CheckBox,
				SimpleGUIWidget::RadioButtons,
				SimpleGUIWidget::TextBox,
				SimpleGUIWidget::ColorPicker> widget;
		};
	}

	class SimpleGUIManager
	{
	private:

		class SimpleGUIManagerDetail;

		std::shared_ptr<SimpleGUIManagerDetail> pImpl;

	public:

		SimpleGUIManager();

		explicit SimpleGUIManager(FilePathView path);

		~SimpleGUIManager();

		bool load(FilePathView path, bool verbose = true);

		bool save(FilePathView path) const;

		void draw() const;

		[[nodiscard]] bool hasChanged(StringView name) const;

		[[nodiscard]] RectF region(StringView name) const;

		[[nodiscard]] bool button(StringView name) const;

		[[nodiscard]] double slider(StringView name) const;

		[[nodiscard]] double verticalSlider(StringView name) const;

		[[nodiscard]] bool checkBox(StringView name) const;

		[[nodiscard]] size_t radioButtons(StringView name) const;

		[[nodiscard]] const TextEditState& textBox(StringView name) const;

		[[nodiscard]] HSV colorPicker(StringView name) const;
	};
}
