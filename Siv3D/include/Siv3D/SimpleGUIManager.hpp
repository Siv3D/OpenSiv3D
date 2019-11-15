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
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "Rectangle.hpp"
# include "Optional.hpp"
# include "String.hpp"

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
