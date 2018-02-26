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

#ifdef __cplusplus

extern "C"
{

#endif
	
	void s3d_DraggingEntered(bool isFilePath);
	
	void s3d_DraggingUpdated();

	void s3d_DraggingExited();
	
	void s3d_DataDropped(const char* text);
	
#ifdef __cplusplus

}

#endif
