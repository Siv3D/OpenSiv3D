//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Array.hpp"
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// Webcam device information
	/// </summary>
	struct WebcamInfo
	{
		/// <summary>
		/// Webcam index
		/// </summary>
		uint32 index = 0;

		/// <summary>
		/// Name of the device
		/// </summary>
		String name;

		/// <summary>
		/// Unique name
		/// </summary>
		String uniqueName;
	};

	class Webcam
	{
	private:

	public:

	};

	namespace System
	{
		Array<WebcamInfo> EnumerateWebcams();
	}
}
