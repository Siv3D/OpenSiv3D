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
# include "Fwd.hpp"
# include "Array.hpp"

namespace s3d
{
	//class Serial
	//{
	//private:

	//	class SerialDetail;

	//	std::shared_ptr<SerialDetail> pImpl;

	//public:

	//	Serial();

	//	explicit Serial(size_t index);

	//	~Serial();

	//	[[nodiscard]] bool isAvailable() const;

	//	[[nodiscard]] explicit operator bool() const;
	//};

	struct SerialPortInfo
	{
		String port;

		String description;

		String hardwareID;
	};

	namespace System
	{
		[[nodiscard]] Array<SerialPortInfo> EnumerateSerialPorts();
	}
}
