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
# include <variant>
# include <Siv3D/Array.hpp>
# include <Siv3D/SimpleGUIManager.hpp>

namespace s3d
{
	class SimpleGUIManager::SimpleGUIManagerDetail
	{
	private:

		Array<SimpleGUI::Widget> m_widgets;

		bool m_verbose = true;

		void print(StringView messgae) const;

		bool exeists(StringView name);

		bool checkName(const TOMLValue& item, String& name);

		void loadHeadline(const TOMLValue& item);

		void loadButton(const TOMLValue& item);

		void loadSlider(const TOMLValue& item);

		void loadVerticalSlider(const TOMLValue& item);

		void loadCheckBox(const TOMLValue& item);

		void loadRadioButtons(const TOMLValue& item);

		void loadHorizontalRadioButtons(const TOMLValue& item);

		void loadTextBox(const TOMLValue& item);

		void loadColorPicker(const TOMLValue& item);

	public:

		SimpleGUIManagerDetail();

		~SimpleGUIManagerDetail();

		bool load(FilePathView path, bool verbose);

		bool save(FilePathView path) const;

		void draw();

		[[nodiscard]] const Array<SimpleGUI::Widget>& widgets() const;

		[[nodiscard]] bool hasChanged(StringView name) const;

		[[nodiscard]] SimpleGUI::Widget& widget(StringView name);

		[[nodiscard]] const SimpleGUI::Widget& widget(StringView name) const;

		[[nodiscard]] RectF region(StringView name) const;

		[[nodiscard]] bool button(StringView name) const;

		[[nodiscard]] double slider(StringView name) const;

		[[nodiscard]] double verticalSlider(StringView name) const;

		[[nodiscard]] bool checkBox(StringView name) const;

		[[nodiscard]] size_t radioButtons(StringView name) const;

		[[nodiscard]] size_t horizontalRadioButtons(StringView name) const;

		[[nodiscard]] const TextEditState& textBox(StringView name) const;

		[[nodiscard]] HSV colorPicker(StringView name) const;
	};
}
