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
# include <Siv3D/SimpleGUI.hpp>
# include "SimpleGUIManagerDetail.hpp"

namespace s3d
{
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
		}

		return true;
	}

	bool SimpleGUIManager::SimpleGUIManagerDetail::save(const FilePathView path) const
	{
		return(false);
	}

	void SimpleGUIManager::SimpleGUIManagerDetail::draw()
	{
		for (const auto& widget : m_widgets)
		{
			switch (WidgetType{ widget.widget.index() })
			{
			case WidgetType::Headline:
			{
				auto& w = std::get<SimpleGUIWidget::Headline>(widget.widget);
				SimpleGUI::Headline(w.text, w.pos, w.width, w.enabled);
				break;
			}
			}
		}
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

	RectF SimpleGUIManager::SimpleGUIManagerDetail::region(const StringView name) const
	{
		for (const auto& widget : m_widgets)
		{
			if (widget.name != name)
			{
				continue;
			}

			switch (WidgetType{ widget.widget.index() })
			{
			case WidgetType::Headline:
			{
				auto& w = std::get<SimpleGUIWidget::Headline>(widget.widget);
				return SimpleGUI::HeadlineRegion(w.text, w.pos, w.width);
			}
			}
		}

		return RectF(0);
	}

	void SimpleGUIManager::SimpleGUIManagerDetail::print(const StringView messgae) const
	{
		if (m_verbose)
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

	void SimpleGUIManager::SimpleGUIManagerDetail::loadHeadline(const TOMLValue& item)
	{
		Widget w;
		{
			w.name = item[U"name"].getString();
			if (!w.name)
			{
				return print(U"Item has no name");
			}
			if (exeists(w.name))
			{
				return print(U"Item name: `{}` is already used"_fmt());
			}
		}

		SimpleGUIWidget::Headline h;
		h.text = item[U"text"].getString();
		h.pos.x = item[U"pos.x"].getOr<double>(0.0);
		h.pos.y = item[U"pos.y"].getOr<double>(0.0);
		h.width = item[U"width"].getOpt<double>();
		h.enabled = item[U"enabled"].getOr<bool>(true);
		w.widget = h;
		m_widgets << w;
	}
}
