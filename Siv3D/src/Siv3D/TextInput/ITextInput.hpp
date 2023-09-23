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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/TextInput.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DTextInput
	{
	public:

		static ISiv3DTextInput* Create();

		virtual ~ISiv3DTextInput() = default;

		virtual void init() = 0;

		virtual void update() = 0;

		virtual void pushChar(uint32 ch) = 0;

		virtual const String& getChars() const = 0;

		virtual const String& getEditingText() const = 0;

		virtual void enableIME(bool enabled) = 0;

		virtual const Array<String>& getCandidates() const = 0;

		virtual const TextInput::CandidateState& getCandidateState() const { static const TextInput::CandidateState _empty; return _empty; }

		virtual std::pair<int32, int32> getCursorIndex() const = 0;

		virtual const Array<UnderlineStyle>& getEditingTextStyle() const { static const Array<UnderlineStyle> _empty; return _empty; }
	};
}
