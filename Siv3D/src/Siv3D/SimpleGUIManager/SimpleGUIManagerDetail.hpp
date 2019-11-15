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

			bool hasChanged;

			std::variant<SimpleGUIWidget::Headline> widget;
		};

		Array<Widget> m_widgets;

		bool m_verbose = true;

		void print(StringView messgae) const;

		bool exeists(StringView name);

		void loadHeadline(const TOMLValue& item);

	public:

		SimpleGUIManagerDetail();

		~SimpleGUIManagerDetail();

		bool load(FilePathView path, bool verbose);

		bool save(FilePathView path) const;

		void draw();

		[[nodiscard]] bool hasChanged(StringView name) const;

		[[nodiscard]] RectF region(StringView name) const;
	};
}
