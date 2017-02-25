#include <cstring>

#include <sstream>

#include <unicode/ucnv.h>
#include <unicode/ucsdet.h>

//constexpr size_t bufferLength = 1024;

std::string ConvertLine(const std::string& line)
{
	/*
	char sourceBuffer[bufferLength] = { '\0' };
	UChar utf16Buffer[bufferLength*2] = { '\0' };
	char utf8Buffer[bufferLength*2] = { '\0' };
	std::string out = "";

	std::stringstream ss(line);
	ss.read(sourceBuffer, bufferLength);

	UErrorCode error = U_ZERO_ERROR;
	UCharsetDetector* csd = ucsdet_open(&error);
	ucsdet_setText(csd, sourceBuffer, bufferLength, &error);
	const UCharsetMatch *ucm = ucsdet_detect(csd, &error);
	UConverter *conv = ucnv_open(ucsdet_getName(ucm, &error), &error);

	while(1)
	{
		const char* source = sourceBuffer;
		const char* sourceLimit = source + bufferLength;
		UChar* target = utf16Buffer;
		UChar* targetLimit = utf16Buffer + bufferLength*2;
		UBool flush = ss.eof();

		do {
			ucnv_toUnicode(conv, &target, targetLimit, &source, sourceLimit, 0, flush, &error);
		} while(error == U_BUFFER_OVERFLOW_ERROR);

		int c = (int)(target - utf16Buffer);
		int32_t pDestLength;
		u_strToUTF8(utf8Buffer, bufferLength*2, &pDestLength, utf16Buffer, c, &error);
		out.append(utf8Buffer);

		int remain = (int)(sourceBuffer+bufferLength - source);
		for(int i = 0; i < remain; i++)
			sourceBuffer[i] = source[1 + i];

		if(ss.eof()) break;
		ss.read(sourceBuffer+remain, bufferLength-remain);
		memset(sourceBuffer + ss.gcount(), 0, bufferLength - ss.gcount());
	}

	ucnv_close(conv);
	ucsdet_close(csd);

	return out;
	*/
	return std::string(line);
}
