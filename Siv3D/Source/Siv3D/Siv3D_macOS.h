//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

#ifdef __cplusplus

extern "C"
{

#endif
	
	void s3d_DraggingEntered(bool isFilePath, int xPos, int yPos);
	
	void s3d_DraggingUpdated(int x, int y);

	void s3d_DraggingExited();
	
	void s3d_TextDropped(const char* text, int x, int y);

	void s3d_FilePathsDropped(int count, const char** paths, int x, int y);
	
#ifdef __cplusplus

}

#endif
