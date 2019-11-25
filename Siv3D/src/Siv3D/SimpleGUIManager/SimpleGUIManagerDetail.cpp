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

# include <Siv3D/Print.hpp>
# include <Siv3D/TOMLReader.hpp>
# include <Siv3D/TextWriter.hpp>
# include <Siv3D/SimpleGUI.hpp>
# include "SimpleGUIManagerDetail.hpp"

namespace s3d
{
	using namespace SimpleGUI;

	namespace detail
	{
		static void WriteHeadline(TextWriter& writer, const String& name, const SimpleGUIWidget::Headline& item)
		{
			writer.writeln(U"[[Headline]]");
			writer.writeln(U"name = \"{}\""_fmt(name));
			writer.writeln(U"text = \"{}\""_fmt(item.text));
			writer.writeln(U"pos = {{ x = {}, y = {} }}"_fmt(item.pos.x, item.pos.y));
			if (item.width)
			{
				writer.writeln(U"width = {}"_fmt(item.width.value()));
			}
			writer.writeln(U"enabled = {}"_fmt(item.enabled));
			writer.writeln();
		}

		static void WriteButton(TextWriter& writer, const String& name, const SimpleGUIWidget::Button& item)
		{
			writer.writeln(U"[[Button]]");
			writer.writeln(U"name = \"{}\""_fmt(name));
			writer.writeln(U"label = \"{}\""_fmt(item.label));
			writer.writeln(U"pos = {{ x = {}, y = {} }}"_fmt(item.pos.x, item.pos.y));
			if (item.width)
			{
				writer.writeln(U"width = {}"_fmt(item.width.value()));
			}
			writer.writeln(U"enabled = {}"_fmt(item.enabled));
			writer.writeln();
		}

		static void WriteSlider(TextWriter& writer, const String& name, const SimpleGUIWidget::Slider& item)
		{
			writer.writeln(U"[[Slider]]");
			writer.writeln(U"name = \"{}\""_fmt(name));
			writer.writeln(U"pos = {{ x = {}, y = {} }}"_fmt(item.pos.x, item.pos.y));
			writer.writeln(U"label = \"{}\""_fmt(item.label));
			writer.writeln(U"default = {}"_fmt(item.value));
			writer.writeln(U"min = {}"_fmt(item.min));
			writer.writeln(U"max = {}"_fmt(item.max));
			writer.writeln(U"labelWidth = {}"_fmt(item.labelWidth));
			writer.writeln(U"sliderWidth = {}"_fmt(item.sliderWidth));
			writer.writeln();
		}

		static void WriteVerticalSlider(TextWriter& writer, const String& name, const SimpleGUIWidget::VerticalSlider& item)
		{
			writer.writeln(U"[[VerticalSlider]]");
			writer.writeln(U"name = \"{}\""_fmt(name));
			writer.writeln(U"pos = {{ x = {}, y = {} }}"_fmt(item.pos.x, item.pos.y));
			writer.writeln(U"default = {}"_fmt(item.value));
			writer.writeln(U"min = {}"_fmt(item.min));
			writer.writeln(U"max = {}"_fmt(item.max));
			writer.writeln(U"sliderHeight = {}"_fmt(item.sliderHeight));
			writer.writeln();
		}

		static void WriteCheckBox(TextWriter& writer, const String& name, const SimpleGUIWidget::CheckBox& item)
		{
			writer.writeln(U"[[CheckBox]]");
			writer.writeln(U"name = \"{}\""_fmt(name));
			writer.writeln(U"label = \"{}\""_fmt(item.label));
			writer.writeln(U"pos = {{ x = {}, y = {} }}"_fmt(item.pos.x, item.pos.y));
			writer.writeln(U"default = {}"_fmt(item.checked));
			if (item.width)
			{
				writer.writeln(U"width = {}"_fmt(item.width.value()));
			}
			writer.writeln(U"enabled = {}"_fmt(item.enabled));
			writer.writeln();
		}

		static void WriteRadioButtons(TextWriter& writer, const String& name, const SimpleGUIWidget::RadioButtons& item)
		{
			writer.writeln(U"[[RadioButtons]]");
			writer.writeln(U"name = \"{}\""_fmt(name));
			writer.writeln(U"pos = {{ x = {}, y = {} }}"_fmt(item.pos.x, item.pos.y));
			writer.writeln(U"options = {}"_fmt(item.options.map([](const String& s) { return U'\"' + s + U'\"'; }).join(U", ", U"[ ", U" ]")));	
			writer.writeln(U"default = {}"_fmt(item.index));
			if (item.width)
			{
				writer.writeln(U"width = {}"_fmt(item.width.value()));
			}
			writer.writeln(U"enabled = {}"_fmt(item.enabled));
			writer.writeln();
		}

		static void WriteTextBox(TextWriter& writer, const String& name, const SimpleGUIWidget::TextBox& item)
		{
			writer.writeln(U"[[TextBox]]");
			writer.writeln(U"name = \"{}\""_fmt(name));
			writer.writeln(U"pos = {{ x = {}, y = {} }}"_fmt(item.pos.x, item.pos.y));
			writer.writeln(U"default = \"{}\""_fmt(item.state.text));
			writer.writeln(U"width = {}"_fmt(item.width));
			if (item.maxChars)
			{
				writer.writeln(U"maxChars = {}"_fmt(item.maxChars.value()));
			}
			writer.writeln(U"enabled = {}"_fmt(item.enabled));
			writer.writeln();
		}

		static void WriteColorPicker(TextWriter& writer, const String& name, const SimpleGUIWidget::ColorPicker& item)
		{
			writer.writeln(U"[[ColorPicker]]");
			writer.writeln(U"name = \"{}\""_fmt(name));
			writer.writeln(U"pos = {{ x = {}, y = {} }}"_fmt(item.pos.x, item.pos.y));
			writer.writeln(U"default = {{ h = {}, s = {}, v = {} }}"_fmt(item.color.h, item.color.s, item.color.v));
			writer.writeln(U"enabled = {}"_fmt(item.enabled));
			writer.writeln();
		}
	}

	SimpleGUIManager::SimpleGUIManagerDetail::SimpleGUIManagerDetail()
	{

	}

	SimpleGUIManager::SimpleGUIManagerDetail::~SimpleGUIManagerDetail()
	{

	}

	bool SimpleGUIManager::SimpleGUIManagerDetail::load(const FilePathView path, const bool verbose)
	{
		m_verbose = verbose;

		const TOMLReader toml(path);
		{
			if (!toml)
			{
				return false;
			}
		}

		m_widgets.clear();

		for (const auto& table : toml.tableView())
		{
			const auto& widget = table.value;
			const String& widgetName = table.name;

			if (!widget.isTableArray())
			{
				print(U"Invalid table {}"_fmt(widgetName));
				continue;
			}

			if (widgetName == U"Headline")
			{
				for (const auto& item : widget.tableArrayView())
				{
					loadHeadline(item);
				}
			}
			else if (widgetName == U"Button")
			{
				for (const auto& item : widget.tableArrayView())
				{
					loadButton(item);
				}
			}
			else if (widgetName == U"Slider")
			{
				for (const auto& item : widget.tableArrayView())
				{
					loadSlider(item);
				}
			}
			else if (widgetName == U"VerticalSlider")
			{
				for (const auto& item : widget.tableArrayView())
				{
					loadVerticalSlider(item);
				}
			}
			else if (widgetName == U"CheckBox")
			{
				for (const auto& item : widget.tableArrayView())
				{
					loadCheckBox(item);
				}
			}
			else if (widgetName == U"RadioButtons")
			{
				for (const auto& item : widget.tableArrayView())
				{
					loadRadioButtons(item);
				}
			}
			else if (widgetName == U"TextBox")
			{
				for (const auto& item : widget.tableArrayView())
				{
					loadTextBox(item);
				}
			}
			else if (widgetName == U"ColorPicker")
			{
				for (const auto& item : widget.tableArrayView())
				{
					loadColorPicker(item);
				}
			}
			else
			{
				print(U"Invalid widget type: `{}`"_fmt(widgetName));
			}
		}

		return true;
	}

	bool SimpleGUIManager::SimpleGUIManagerDetail::save(const FilePathView path) const
	{
		TextWriter writer(path);

		if (!writer)
		{
			return false;
		}

		for (const auto& widget : m_widgets)
		{
			switch (static_cast<WidgetType>(widget.widget.index()))
			{
			case WidgetType::Headline:
				{
					const auto& w = std::get<SimpleGUIWidget::Headline>(widget.widget);
					detail::WriteHeadline(writer, widget.name, w);
					break;
				}
			case WidgetType::Button:
				{
					const auto& w = std::get<SimpleGUIWidget::Button>(widget.widget);
					detail::WriteButton(writer, widget.name, w);
					break;
				}
			case WidgetType::Slider:
				{
					const auto& w = std::get<SimpleGUIWidget::Slider>(widget.widget);
					detail::WriteSlider(writer, widget.name, w);
					break;
				}
			case WidgetType::VerticalSlider:
				{
					const auto& w = std::get<SimpleGUIWidget::VerticalSlider>(widget.widget);
					detail::WriteVerticalSlider(writer, widget.name, w);
					break;
				}
			case WidgetType::CheckBox:
				{
					const auto& w = std::get<SimpleGUIWidget::CheckBox>(widget.widget);
					detail::WriteCheckBox(writer, widget.name, w);
					break;
				}
			case WidgetType::RadioButtons:
				{
					const auto& w = std::get<SimpleGUIWidget::RadioButtons>(widget.widget);
					detail::WriteRadioButtons(writer, widget.name, w);
					break;
				}
			case WidgetType::TextBox:
				{
					const auto& w = std::get<SimpleGUIWidget::TextBox>(widget.widget);
					detail::WriteTextBox(writer, widget.name, w);
					break;
				}
			case WidgetType::ColorPicker:
				{
					const auto& w = std::get<SimpleGUIWidget::ColorPicker>(widget.widget);
					detail::WriteColorPicker(writer, widget.name, w);
					break;
				}
			}
		}

		return true;
	}

	void SimpleGUIManager::SimpleGUIManagerDetail::draw()
	{
		for (auto& widget : m_widgets)
		{
			switch (static_cast<WidgetType>(widget.widget.index()))
			{
			case WidgetType::Headline:
				{
					auto& w = std::get<SimpleGUIWidget::Headline>(widget.widget);
					SimpleGUI::Headline(w.text, w.pos, w.width, w.enabled);
					break;
				}
			case WidgetType::Button:
				{
					auto& w = std::get<SimpleGUIWidget::Button>(widget.widget);
					widget.hasChanged = SimpleGUI::Button(w.label, w.pos, w.width, w.enabled);
					break;
				}
			case WidgetType::Slider:
				{
					auto& w = std::get<SimpleGUIWidget::Slider>(widget.widget);
					widget.hasChanged = SimpleGUI::Slider(Fmt(w.label)(w.value), w.value, w.min, w.max, w.pos, w.labelWidth, w.sliderWidth, w.enabled);
					break;
				}
			case WidgetType::VerticalSlider:
				{
					auto& w = std::get<SimpleGUIWidget::VerticalSlider>(widget.widget);
					widget.hasChanged = SimpleGUI::VerticalSlider(w.value, w.min, w.max, w.pos, w.sliderHeight, w.enabled);
					break;
				}
			case WidgetType::CheckBox:
				{
					auto& w = std::get<SimpleGUIWidget::CheckBox>(widget.widget);
					widget.hasChanged = SimpleGUI::CheckBox(w.checked, w.label, w.pos, w.width, w.enabled);
					break;
				}
			case WidgetType::RadioButtons:
				{
					auto& w = std::get<SimpleGUIWidget::RadioButtons>(widget.widget);
					widget.hasChanged = SimpleGUI::RadioButtons(w.index, w.options, w.pos, w.width, w.enabled);
					break;
				}
			case WidgetType::TextBox:
				{
					auto& w = std::get<SimpleGUIWidget::TextBox>(widget.widget);
					widget.hasChanged = SimpleGUI::TextBox(w.state, w.pos, w.width, w.maxChars, w.enabled);
					break;
				}
			case WidgetType::ColorPicker:
				{
					auto& w = std::get<SimpleGUIWidget::ColorPicker>(widget.widget);
					widget.hasChanged = SimpleGUI::ColorPicker(w.color, w.pos, w.enabled);
					break;
				}
			}
		}
	}

	const Array<SimpleGUI::Widget>& SimpleGUIManager::SimpleGUIManagerDetail::widgets() const
	{
		return m_widgets;
	}

	bool SimpleGUIManager::SimpleGUIManagerDetail::hasChanged(const StringView name) const
	{
		for (const auto& widget : m_widgets)
		{
			if (widget.name == name)
			{
				return widget.hasChanged;
			}
		}

		return false;
	}

	SimpleGUI::Widget& SimpleGUIManager::SimpleGUIManagerDetail::widget(const StringView name)
	{
		for (auto& widget : m_widgets)
		{
			if (widget.name == name)
			{
				return widget;
			}
		}

		throw Error(U"SimpleGUIManager::widget(): widget `{}` does not exist"_fmt(name));
	}

	const SimpleGUI::Widget& SimpleGUIManager::SimpleGUIManagerDetail::widget(const StringView name) const
	{
		for (const auto& widget : m_widgets)
		{
			if (widget.name == name)
			{
				return widget;
			}
		}

		throw Error(U"SimpleGUIManager::widget(): widget `{}` does not exist"_fmt(name));
	}

	RectF SimpleGUIManager::SimpleGUIManagerDetail::region(const StringView name) const
	{
		for (const auto& widget : m_widgets)
		{
			if (widget.name != name)
			{
				continue;
			}

			switch (static_cast<WidgetType>(widget.widget.index()))
			{
			case WidgetType::Headline:
				{
					auto& w = std::get<SimpleGUIWidget::Headline>(widget.widget);
					return SimpleGUI::HeadlineRegion(w.text, w.pos, w.width);
				}
			case WidgetType::Button:
				{
					auto& w = std::get<SimpleGUIWidget::Button>(widget.widget);
					return SimpleGUI::ButtonRegion(w.label, w.pos, w.width);
				}
			case WidgetType::Slider:
				{
					auto& w = std::get<SimpleGUIWidget::Slider>(widget.widget);
					return SimpleGUI::SliderRegion(w.pos, w.labelWidth, w.sliderWidth);
				}
			case WidgetType::VerticalSlider:
				{
					auto& w = std::get<SimpleGUIWidget::VerticalSlider>(widget.widget);
					return SimpleGUI::VerticalSliderRegion(w.pos, w.sliderHeight);
				}
			case WidgetType::CheckBox:
				{
					auto& w = std::get<SimpleGUIWidget::CheckBox>(widget.widget);
					return SimpleGUI::CheckBoxRegion(w.label, w.pos, w.width);
				}
			case WidgetType::RadioButtons:
				{
					auto& w = std::get<SimpleGUIWidget::RadioButtons>(widget.widget);
					return SimpleGUI::RadioButtonsRegion(w.options, w.pos, w.width);
				}
			case WidgetType::TextBox:
				{
					auto& w = std::get<SimpleGUIWidget::TextBox>(widget.widget);
					return SimpleGUI::TextBoxRegion(w.pos, w.width);
				}
			case WidgetType::ColorPicker:
				{
					auto& w = std::get<SimpleGUIWidget::ColorPicker>(widget.widget);
					return SimpleGUI::ColorPickerRegion(w.pos);
				}
			}
		}

		return RectF(0);
	}

	bool SimpleGUIManager::SimpleGUIManagerDetail::button(const StringView name) const
	{
		for (const auto& widget : m_widgets)
		{
			if (widget.name != name)
			{
				continue;
			}

			if (static_cast<WidgetType>(widget.widget.index()) != WidgetType::Button)
			{
				throw Error(U"SimpleGUIManager: `{}` is not WidgetType::Button"_fmt(name));
			}

			return widget.hasChanged;
		}

		throw Error(U"SimpleGUIManager: Button `{}` does not exist"_fmt(name));
	}

	double SimpleGUIManager::SimpleGUIManagerDetail::slider(const StringView name) const
	{
		for (const auto& widget : m_widgets)
		{
			if (widget.name != name)
			{
				continue;
			}

			if (static_cast<WidgetType>(widget.widget.index()) != WidgetType::Slider)
			{
				throw Error(U"SimpleGUIManager: `{}` is not WidgetType::Slider"_fmt(name));
			}

			return std::get<SimpleGUIWidget::Slider>(widget.widget).value;
		}

		throw Error(U"SimpleGUIManager: Slider `{}` does not exist"_fmt(name));
	}

	double SimpleGUIManager::SimpleGUIManagerDetail::verticalSlider(const StringView name) const
	{
		for (const auto& widget : m_widgets)
		{
			if (widget.name != name)
			{
				continue;
			}

			if (static_cast<WidgetType>(widget.widget.index()) != WidgetType::VerticalSlider)
			{
				throw Error(U"SimpleGUIManager: `{}` is not WidgetType::VerticalSlider"_fmt(name));
			}

			return std::get<SimpleGUIWidget::VerticalSlider>(widget.widget).value;
		}

		throw Error(U"SimpleGUIManager: VerticalSlider `{}` does not exist"_fmt(name));
	}

	bool SimpleGUIManager::SimpleGUIManagerDetail::checkBox(const StringView name) const
	{
		for (const auto& widget : m_widgets)
		{
			if (widget.name != name)
			{
				continue;
			}

			if (static_cast<WidgetType>(widget.widget.index()) != WidgetType::CheckBox)
			{
				throw Error(U"SimpleGUIManager: `{}` is not WidgetType::CheckBox"_fmt(name));
			}

			return std::get<SimpleGUIWidget::CheckBox>(widget.widget).checked;
		}

		throw Error(U"SimpleGUIManager: CheckBox `{}` does not exist"_fmt(name));
	}

	size_t SimpleGUIManager::SimpleGUIManagerDetail::radioButtons(const StringView name) const
	{
		for (const auto& widget : m_widgets)
		{
			if (widget.name != name)
			{
				continue;
			}

			if (static_cast<WidgetType>(widget.widget.index()) != WidgetType::RadioButtons)
			{
				throw Error(U"SimpleGUIManager: `{}` is not WidgetType::RadioButtons"_fmt(name));
			}

			return std::get<SimpleGUIWidget::RadioButtons>(widget.widget).index;
		}

		throw Error(U"SimpleGUIManager: RadioButtons `{}` does not exist"_fmt(name));
	}

	const TextEditState& SimpleGUIManager::SimpleGUIManagerDetail::textBox(const StringView name) const
	{
		for (const auto& widget : m_widgets)
		{
			if (widget.name != name)
			{
				continue;
			}

			if (static_cast<WidgetType>(widget.widget.index()) != WidgetType::TextBox)
			{
				throw Error(U"SimpleGUIManager: `{}` is not WidgetType::TextBox"_fmt(name));
			}

			return std::get<SimpleGUIWidget::TextBox>(widget.widget).state;
		}

		throw Error(U"SimpleGUIManager: TextBox `{}` does not exist"_fmt(name));
	}

	HSV SimpleGUIManager::SimpleGUIManagerDetail::colorPicker(const StringView name) const
	{
		for (const auto& widget : m_widgets)
		{
			if (widget.name != name)
			{
				continue;
			}

			if (static_cast<WidgetType>(widget.widget.index()) != WidgetType::ColorPicker)
			{
				throw Error(U"SimpleGUIManager: `{}` is not WidgetType::ColorPicker"_fmt(name));
			}

			return std::get<SimpleGUIWidget::ColorPicker>(widget.widget).color;
		}

		throw Error(U"SimpleGUIManager: ColorPicker `{}` does not exist"_fmt(name));
	}

	void SimpleGUIManager::SimpleGUIManagerDetail::print(const StringView messgae) const
	{
		if (!m_verbose)
		{
			return;
		}

		Print << messgae;
	}

	bool SimpleGUIManager::SimpleGUIManagerDetail::exeists(const StringView name)
	{
		for (const auto& widget : m_widgets)
		{
			if (widget.name == name)
			{
				return true;
			}
		}

		return false;
	}

	bool SimpleGUIManager::SimpleGUIManagerDetail::checkName(const TOMLValue& item, String& _name)
	{
		String name = item[U"name"].getString();

		if (!name)
		{
			print(U"Item has no name");
			return false;
		}

		if (exeists(name))
		{
			print(U"Item name: `{}` is already used"_fmt(name));
			return false;
		}

		_name = std::move(name);
		return true;
	}

	void SimpleGUIManager::SimpleGUIManagerDetail::loadHeadline(const TOMLValue& item)
	{
		Widget w;
		if (!checkName(item, w.name))
		{
			return;
		}

		SimpleGUIWidget::Headline h;
		h.pos.x		= item[U"pos.x"].getOr<double>(0.0);
		h.pos.y		= item[U"pos.y"].getOr<double>(0.0);
		h.text		= item[U"text"].getString();
		h.width		= item[U"width"].getOpt<double>();
		h.enabled	= item[U"enabled"].getOr<bool>(true);
		
		w.widget = h;
		m_widgets << w;
	}

	void SimpleGUIManager::SimpleGUIManagerDetail::loadButton(const TOMLValue& item)
	{
		Widget w;
		if (!checkName(item, w.name))
		{
			return;
		}

		SimpleGUIWidget::Button b;
		b.pos.x		= item[U"pos.x"].getOr<double>(0.0);
		b.pos.y		= item[U"pos.y"].getOr<double>(0.0);
		b.label		= item[U"label"].getString();
		b.width		= item[U"width"].getOpt<double>();
		b.enabled	= item[U"enabled"].getOr<bool>(true);

		w.widget = b;
		m_widgets << w;
	}

	void SimpleGUIManager::SimpleGUIManagerDetail::loadSlider(const TOMLValue& item)
	{
		Widget w;
		if (!checkName(item, w.name))
		{
			return;
		}

		SimpleGUIWidget::Slider s;
		s.pos.x		= item[U"pos.x"].getOr<double>(0.0);
		s.pos.y		= item[U"pos.y"].getOr<double>(0.0);
		s.label		= item[U"label"].getString();
		s.value		= item[U"default"].getOr<double>(0.0);
		s.min		= item[U"min"].getOr<double>(0.0);
		s.max		= item[U"max"].getOr<double>(1.0);
		s.labelWidth	= item[U"labelWidth"].getOr<double>(80.0);
		s.sliderWidth	= item[U"sliderWidth"].getOr<double>(120.0);
		s.enabled	= item[U"enabled"].getOr<bool>(true);

		w.widget = s;
		m_widgets << w;
	}

	void SimpleGUIManager::SimpleGUIManagerDetail::loadVerticalSlider(const TOMLValue& item)
	{
		Widget w;
		if (!checkName(item, w.name))
		{
			return;
		}

		SimpleGUIWidget::VerticalSlider s;
		s.pos.x		= item[U"pos.x"].getOr<double>(0.0);
		s.pos.y		= item[U"pos.y"].getOr<double>(0.0);
		s.value		= item[U"default"].getOr<double>(0.0);
		s.min		= item[U"min"].getOr<double>(0.0);
		s.max		= item[U"max"].getOr<double>(1.0);
		s.sliderHeight = item[U"sliderHeight"].getOr<double>(120.0);
		s.enabled	= item[U"enabled"].getOr<bool>(true);

		w.widget = s;
		m_widgets << w;
	}

	void SimpleGUIManager::SimpleGUIManagerDetail::loadCheckBox(const TOMLValue& item)
	{
		Widget w;
		if (!checkName(item, w.name))
		{
			return;
		}

		SimpleGUIWidget::CheckBox c;
		c.pos.x		= item[U"pos.x"].getOr<double>(0.0);
		c.pos.y		= item[U"pos.y"].getOr<double>(0.0);
		c.label		= item[U"label"].getString();
		c.width		= item[U"width"].getOpt<double>();
		c.checked	= item[U"default"].getOr<bool>(false);
		c.enabled	= item[U"enabled"].getOr<bool>(true);

		w.widget = c;
		m_widgets << w;
	}

	void SimpleGUIManager::SimpleGUIManagerDetail::loadRadioButtons(const TOMLValue& item)
	{
		Widget w;
		if (!checkName(item, w.name))
		{
			return;
		}

		SimpleGUIWidget::RadioButtons r;
		r.pos.x		= item[U"pos.x"].getOr<double>(0.0);
		r.pos.y		= item[U"pos.y"].getOr<double>(0.0);
		if (item[U"options"].isArray())
		{
			for (const auto& option : item[U"options"].arrayView())
			{
				r.options << option.getString();
			}
		}
		r.index		= item[U"default"].getOr<size_t>(0);
		r.width		= item[U"width"].getOpt<double>();
		r.enabled	= item[U"enabled"].getOr<bool>(true);

		w.widget = r;
		m_widgets << w;
	}

	void SimpleGUIManager::SimpleGUIManagerDetail::loadTextBox(const TOMLValue& item)
	{
		Widget w;
		if (!checkName(item, w.name))
		{
			return;
		}

		SimpleGUIWidget::TextBox t;
		t.pos.x		= item[U"pos.x"].getOr<double>(0.0);
		t.pos.y		= item[U"pos.y"].getOr<double>(0.0);
		t.state.text		= item[U"default"].getOr<String>(U"");
		t.state.cursorPos	= t.state.text.size();
		t.width		= item[U"width"].getOr<double>(200.0);
		t.maxChars	= item[U"maxChars"].getOpt<size_t>();
		t.enabled	= item[U"enabled"].getOr<bool>(true);

		w.widget = t;
		m_widgets << w;
	}

	void SimpleGUIManager::SimpleGUIManagerDetail::loadColorPicker(const TOMLValue& item)
	{
		Widget w;
		if (!checkName(item, w.name))
		{
			return;
		}

		SimpleGUIWidget::ColorPicker c;
		c.pos.x		= item[U"pos.x"].getOr<double>(0.0);
		c.pos.y		= item[U"pos.y"].getOr<double>(0.0);
		c.color.h	= item[U"default.h"].getOr<double>(0.0);
		c.color.s	= item[U"default.s"].getOr<double>(0.0);
		c.color.v	= item[U"default.v"].getOr<double>(1.0);
		c.color.a	= 1.0;
		c.enabled	= item[U"enabled"].getOr<bool>(true);

		w.widget = c;
		m_widgets << w;
	}
}
