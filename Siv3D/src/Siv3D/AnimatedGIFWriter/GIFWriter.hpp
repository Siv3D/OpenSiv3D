﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <string>
# include <Siv3D/IWriter.hpp>

//
// gif.h
// by Charlie Tangora
// Public domain.
//
// This file offers a simple, very limited way to create animated GIFs directly in code.
// There's not much effort to optimize colors to improve compression, so resulting files
// are often quite large. But it's still handy to be able to spit out GIFs on command.
//
// Only RGBA8 is currently supported as an input format; the alpha is ignored.
//
// USAGE:
// Create a GifWriter struct. Pass it to GifBegin() to initialize and write the header.
// Pass subsequent frames to GifWriteFrame().
// Finally, call GifEnd() to close the file handle and free memory.
//

#ifndef gif_h
#define gif_h

//#pragma warning(disable:4018)
//#pragma warning(disable:4244)

#include <stdio.h>   // for FILE*
#include <string.h>  // for memcpy and bzero
#include <stdint.h>  // for integer typedefs

// Define these macros to hook into a custom memory allocator.
// TEMP_MALLOC and TEMP_FREE will only be called in stack fashion - frees in the reverse order of mallocs
// and any temp memory allocated by a function will be freed before it exits.
// MALLOC and FREE are used only by GifBegin and GifEnd respectively (to allocate a buffer the size of the image, which
// is used to find changed pixels for delta-encoding.)

#ifndef GIF_TEMP_MALLOC
#include <stdlib.h>
#define GIF_TEMP_MALLOC malloc
#endif

#ifndef GIF_TEMP_FREE
#include <stdlib.h>
#define GIF_TEMP_FREE free
#endif

#ifndef GIF_MALLOC
#include <stdlib.h>
#define GIF_MALLOC malloc
#endif

#ifndef GIF_FREE
#include <stdlib.h>
#define GIF_FREE free
#endif

const int kGifTransIndex = 0;

enum class GifEncodingMode
{
	SingleRGB,
	SingleRGBA,
	AnimatedRGB,
	AnimatedRGBA
};

inline void FPutc(unsigned char c, s3d::IWriter* w)
{
	w->write(&c, sizeof(c));
}

struct GifPalette
{
	int bitDepth;

	uint8_t r[256];
	uint8_t g[256];
	uint8_t b[256];

	// k-d tree over RGB space, organized in heap fashion
	// i.e. left child of node i is node i*2, right child is node i*2+1
	// nodes 256-511 are implicitly the leaves, containing a color
	uint8_t treeSplitElt[255];
	uint8_t treeSplit[255];
};

// max, min, and abs functions
inline int GifIMax(int l, int r) { return l > r ? l : r; }
inline int GifIMin(int l, int r) { return l < r ? l : r; }
inline int GifIAbs(int i) { return i < 0 ? -i : i; }

// walks the k-d tree to pick the palette entry for a desired color.
// Takes as in/out parameters the current best color and its error -
// only changes them if it finds a better color in its subtree.
// this is the major hotspot in the code at the moment.
inline void GifGetClosestPaletteColor(GifPalette* pPal, int r, int g, int b, int& bestInd, int& bestDiff, int treeRoot = 1)
{
	// base case, reached the bottom of the tree
	if (treeRoot > (1 << pPal->bitDepth) - 1)
	{
		int ind = treeRoot - (1 << pPal->bitDepth);
		if (ind == kGifTransIndex) return;

		// check whether this color is better than the current winner
		int r_err = r - ((int32_t)pPal->r[ind]);
		int g_err = g - ((int32_t)pPal->g[ind]);
		int b_err = b - ((int32_t)pPal->b[ind]);
		int diff = GifIAbs(r_err) + GifIAbs(g_err) + GifIAbs(b_err);

		if (diff < bestDiff)
		{
			bestInd = ind;
			bestDiff = diff;
		}

		return;
	}

	// take the appropriate color (r, g, or b) for this node of the k-d tree
	int comps[3]; comps[0] = r; comps[1] = g; comps[2] = b;
	int splitComp = comps[pPal->treeSplitElt[treeRoot]];

	int splitPos = pPal->treeSplit[treeRoot];
	if (splitPos > splitComp)
	{
		// check the left subtree
		GifGetClosestPaletteColor(pPal, r, g, b, bestInd, bestDiff, treeRoot * 2);
		if (bestDiff > splitPos - splitComp)
		{
			// cannot prove there's not a better value in the right subtree, check that too
			GifGetClosestPaletteColor(pPal, r, g, b, bestInd, bestDiff, treeRoot * 2 + 1);
		}
	}
	else
	{
		GifGetClosestPaletteColor(pPal, r, g, b, bestInd, bestDiff, treeRoot * 2 + 1);
		if (bestDiff > splitComp - splitPos)
		{
			GifGetClosestPaletteColor(pPal, r, g, b, bestInd, bestDiff, treeRoot * 2);
		}
	}
}

inline void GifSwapPixels(uint8_t * image, int pixA, int pixB)
{
	uint8_t rA = image[pixA * 4];
	uint8_t gA = image[pixA * 4 + 1];
	uint8_t bA = image[pixA * 4 + 2];
	uint8_t aA = image[pixA * 4 + 3];

	uint8_t rB = image[pixB * 4];
	uint8_t gB = image[pixB * 4 + 1];
	uint8_t bB = image[pixB * 4 + 2];
	uint8_t aB = image[pixB * 4 + 3];

	image[pixA * 4] = rB;
	image[pixA * 4 + 1] = gB;
	image[pixA * 4 + 2] = bB;
	image[pixA * 4 + 3] = aB;

	image[pixB * 4] = rA;
	image[pixB * 4 + 1] = gA;
	image[pixB * 4 + 2] = bA;
	image[pixB * 4 + 3] = aA;
}

// just the partition operation from quicksort
inline int GifPartition(uint8_t * image, const int left, const int right, const int elt, int pivotIndex)
{
	const int pivotValue = image[(pivotIndex) * 4 + elt];
	GifSwapPixels(image, pivotIndex, right - 1);
	int storeIndex = left;
	bool split = 0;
	for (int ii = left; ii < right - 1; ++ii)
	{
		int arrayVal = image[ii * 4 + elt];
		if (arrayVal < pivotValue)
		{
			GifSwapPixels(image, ii, storeIndex);
			++storeIndex;
		}
		else if (arrayVal == pivotValue)
		{
			if (split)
			{
				GifSwapPixels(image, ii, storeIndex);
				++storeIndex;
			}
			split = !split;
		}
	}
	GifSwapPixels(image, storeIndex, right - 1);
	return storeIndex;
}

// Perform an incomplete sort, finding all elements above and below the desired median
inline void GifPartitionByMedian(uint8_t * image, int left, int right, int com, int neededCenter)
{
	if (left < right - 1)
	{
		int pivotIndex = left + (right - left) / 2;

		pivotIndex = GifPartition(image, left, right, com, pivotIndex);

		// Only "sort" the section of the array that contains the median
		if (pivotIndex > neededCenter)
			GifPartitionByMedian(image, left, pivotIndex, com, neededCenter);

		if (pivotIndex < neededCenter)
			GifPartitionByMedian(image, pivotIndex + 1, right, com, neededCenter);
	}
}

// Builds a palette by creating a balanced k-d tree of all pixels in the image
inline void GifSplitPalette(uint8_t * image, int numPixels, int firstElt, int lastElt, int splitElt, int splitDist, int treeNode, bool buildForDither, GifPalette * pal)
{
	if (lastElt <= firstElt || numPixels == 0)
		return;

	// base case, bottom of the tree
	if (lastElt == firstElt + 1)
	{
		if (buildForDither)
		{
			// Dithering needs at least one color as dark as anything
			// in the image and at least one brightest color -
			// otherwise it builds up error and produces strange artifacts
			if (firstElt == 1)
			{
				// special case: the darkest color in the image
				uint32_t r = 255, g = 255, b = 255;
				for (int ii = 0; ii < numPixels; ++ii)
				{
					r = (uint32_t)GifIMin((int32_t)r, image[ii * 4 + 0]);
					g = (uint32_t)GifIMin((int32_t)g, image[ii * 4 + 1]);
					b = (uint32_t)GifIMin((int32_t)b, image[ii * 4 + 2]);
				}

				pal->r[firstElt] = (uint8_t)r;
				pal->g[firstElt] = (uint8_t)g;
				pal->b[firstElt] = (uint8_t)b;

				return;
			}

			if (firstElt == (1 << pal->bitDepth) - 1)
			{
				// special case: the lightest color in the image
				uint32_t r = 0, g = 0, b = 0;
				for (int ii = 0; ii < numPixels; ++ii)
				{
					r = (uint32_t)GifIMax((int32_t)r, image[ii * 4 + 0]);
					g = (uint32_t)GifIMax((int32_t)g, image[ii * 4 + 1]);
					b = (uint32_t)GifIMax((int32_t)b, image[ii * 4 + 2]);
				}

				pal->r[firstElt] = (uint8_t)r;
				pal->g[firstElt] = (uint8_t)g;
				pal->b[firstElt] = (uint8_t)b;

				return;
			}
		}

		// otherwise, take the average of all colors in this subcube
		uint64_t r = 0, g = 0, b = 0;
		for (int ii = 0; ii < numPixels; ++ii)
		{
			r += image[ii * 4 + 0];
			g += image[ii * 4 + 1];
			b += image[ii * 4 + 2];
		}

		r += (uint64_t)numPixels / 2;  // round to nearest
		g += (uint64_t)numPixels / 2;
		b += (uint64_t)numPixels / 2;

		r /= (uint64_t)numPixels;
		g /= (uint64_t)numPixels;
		b /= (uint64_t)numPixels;

		pal->r[firstElt] = (uint8_t)r;
		pal->g[firstElt] = (uint8_t)g;
		pal->b[firstElt] = (uint8_t)b;

		return;
	}

	// Find the axis with the largest range
	int minR = 255, maxR = 0;
	int minG = 255, maxG = 0;
	int minB = 255, maxB = 0;
	for (int ii = 0; ii < numPixels; ++ii)
	{
		int r = image[ii * 4 + 0];
		int g = image[ii * 4 + 1];
		int b = image[ii * 4 + 2];

		if (r > maxR) maxR = r;
		if (r < minR) minR = r;

		if (g > maxG) maxG = g;
		if (g < minG) minG = g;

		if (b > maxB) maxB = b;
		if (b < minB) minB = b;
	}

	int rRange = maxR - minR;
	int gRange = maxG - minG;
	int bRange = maxB - minB;

	// and split along that axis. (incidentally, this means this isn't a "proper" k-d tree but I don't know what else to call it)
	int splitCom = 1;
	if (bRange > gRange) splitCom = 2;
	if (rRange > bRange&& rRange > gRange) splitCom = 0;

	int subPixelsA = numPixels * (splitElt - firstElt) / (lastElt - firstElt);
	int subPixelsB = numPixels - subPixelsA;

	GifPartitionByMedian(image, 0, numPixels, splitCom, subPixelsA);

	pal->treeSplitElt[treeNode] = (uint8_t)splitCom;
	pal->treeSplit[treeNode] = image[subPixelsA * 4 + splitCom];

	GifSplitPalette(image, subPixelsA, firstElt, splitElt, splitElt - splitDist, splitDist / 2, treeNode * 2, buildForDither, pal);
	GifSplitPalette(image + subPixelsA * 4, subPixelsB, splitElt, lastElt, splitElt + splitDist, splitDist / 2, treeNode * 2 + 1, buildForDither, pal);
}

// Finds all pixels that have changed from the previous image and
// moves them to the fromt of th buffer.
// This allows us to build a palette optimized for the colors of the
// changed pixels only.
inline int GifPickChangedPixels(const uint8_t * lastFrame, uint8_t * frame, int numPixels)
{
	int numChanged = 0;
	uint8_t* writeIter = frame;

	for (int ii = 0; ii < numPixels; ++ii)
	{
		if (lastFrame[0] != frame[0] ||
			lastFrame[1] != frame[1] ||
			lastFrame[2] != frame[2])
		{
			writeIter[0] = frame[0];
			writeIter[1] = frame[1];
			writeIter[2] = frame[2];
			++numChanged;
			writeIter += 4;
		}
		lastFrame += 4;
		frame += 4;
	}

	return numChanged;
}

// Creates a palette by placing all the image pixels in a k-d tree and then averaging the blocks at the bottom.
// This is known as the "modified median split" technique
inline void GifMakePalette(const uint8_t * lastFrame, const uint8_t * nextFrame, uint32_t width, uint32_t height, int bitDepth, bool buildForDither, GifPalette * pPal, GifEncodingMode mode)
{
	pPal->bitDepth = bitDepth;

	// SplitPalette is destructive (it sorts the pixels by color) so
	// we must create a copy of the image for it to destroy
	size_t imageSize = (size_t)(width * height * 4 * sizeof(uint8_t));
	uint8_t* destroyableImage = (uint8_t*)GIF_TEMP_MALLOC(imageSize);
	memcpy(destroyableImage, nextFrame, imageSize);

	int numPixels = (int)(width * height);
	if (lastFrame&& mode != GifEncodingMode::AnimatedRGBA)
		numPixels = GifPickChangedPixels(lastFrame, destroyableImage, numPixels);

	const int lastElt = 1 << bitDepth;
	const int splitElt = lastElt / 2;
	const int splitDist = splitElt / 2;

	GifSplitPalette(destroyableImage, numPixels, 1, lastElt, splitElt, splitDist, 1, buildForDither, pPal);

	GIF_TEMP_FREE(destroyableImage);

	// add the bottom node for the transparency index
	pPal->treeSplit[unsigned(1 << (bitDepth - 1))] = 0;
	pPal->treeSplitElt[unsigned(1 << (bitDepth - 1))] = 0;

	pPal->r[0] = pPal->g[0] = pPal->b[0] = 0;
}

// Implements Floyd-Steinberg dithering, writes palette value to alpha
inline void GifDitherImage(const uint8_t * lastFrame, const uint8_t * nextFrame, uint8_t * outFrame, uint32_t width, uint32_t height, GifPalette * pPal, GifEncodingMode mode)
{
	bool alphaCompression = mode != GifEncodingMode::AnimatedRGBA;

	int numPixels = (int)(width * height);

	// quantPixels initially holds color*256 for all pixels
	// The extra 8 bits of precision allow for sub-single-color error values
	// to be propagated
	int32_t* quantPixels = (int32_t*)GIF_TEMP_MALLOC(sizeof(int32_t) * (size_t)numPixels * 4);

	for (int ii = 0; ii < numPixels * 4; ++ii)
	{
		uint8_t pix = nextFrame[ii];
		int32_t pix16 = int32_t(pix) * 256;
		quantPixels[ii] = pix16;
	}

	for (uint32_t yy = 0; yy < height; ++yy)
	{
		for (uint32_t xx = 0; xx < width; ++xx)
		{
			int32_t* nextPix = quantPixels + 4 * (yy * width + xx);
			const uint8_t * lastPix = lastFrame ? lastFrame + 4 * (yy * width + xx) : NULL;

			// Compute the colors we want (rounding to nearest)
			int32_t rr = (nextPix[0] + 127) / 256;
			int32_t gg = (nextPix[1] + 127) / 256;
			int32_t bb = (nextPix[2] + 127) / 256;

			// if it happens that we want the color from last frame, then just write out
			// a transparent pixel
			if (alphaCompression && lastFrame &&
				lastPix[0] == rr &&
				lastPix[1] == gg &&
				lastPix[2] == bb)
			{
				nextPix[0] = rr;
				nextPix[1] = gg;
				nextPix[2] = bb;
				nextPix[3] = kGifTransIndex;
				continue;
			}
			else if (nextFrame[4 * (yy * width + xx) + 3] != 255)
			{
				nextPix[0] = 0;
				nextPix[1] = 0;
				nextPix[2] = 0;
				nextPix[3] = kGifTransIndex;
				continue;
			}

			int32_t bestDiff = 1000000;
			int32_t bestInd = kGifTransIndex;

			// Search the palete
			GifGetClosestPaletteColor(pPal, rr, gg, bb, bestInd, bestDiff);

			// Write the result to the temp buffer
			int32_t r_err = nextPix[0] - int32_t(pPal->r[bestInd]) * 256;
			int32_t g_err = nextPix[1] - int32_t(pPal->g[bestInd]) * 256;
			int32_t b_err = nextPix[2] - int32_t(pPal->b[bestInd]) * 256;

			nextPix[0] = pPal->r[bestInd];
			nextPix[1] = pPal->g[bestInd];
			nextPix[2] = pPal->b[bestInd];
			nextPix[3] = bestInd;

			// Propagate the error to the four adjacent locations
			// that we haven't touched yet
			int quantloc_7 = (int)(yy * width + xx + 1);
			int quantloc_3 = (int)(yy * width + width + xx - 1);
			int quantloc_5 = (int)(yy * width + width + xx);
			int quantloc_1 = (int)(yy * width + width + xx + 1);

			if (quantloc_7 < numPixels)
			{
				int32_t* pix7 = quantPixels + 4 * quantloc_7;
				pix7[0] += GifIMax(-pix7[0], r_err * 7 / 16);
				pix7[1] += GifIMax(-pix7[1], g_err * 7 / 16);
				pix7[2] += GifIMax(-pix7[2], b_err * 7 / 16);
			}

			if (quantloc_3 < numPixels)
			{
				int32_t* pix3 = quantPixels + 4 * quantloc_3;
				pix3[0] += GifIMax(-pix3[0], r_err * 3 / 16);
				pix3[1] += GifIMax(-pix3[1], g_err * 3 / 16);
				pix3[2] += GifIMax(-pix3[2], b_err * 3 / 16);
			}

			if (quantloc_5 < numPixels)
			{
				int32_t* pix5 = quantPixels + 4 * quantloc_5;
				pix5[0] += GifIMax(-pix5[0], r_err * 5 / 16);
				pix5[1] += GifIMax(-pix5[1], g_err * 5 / 16);
				pix5[2] += GifIMax(-pix5[2], b_err * 5 / 16);
			}

			if (quantloc_1 < numPixels)
			{
				int32_t* pix1 = quantPixels + 4 * quantloc_1;
				pix1[0] += GifIMax(-pix1[0], r_err / 16);
				pix1[1] += GifIMax(-pix1[1], g_err / 16);
				pix1[2] += GifIMax(-pix1[2], b_err / 16);
			}
		}
	}

	// Copy the palettized result to the output buffer
	for (int ii = 0; ii < numPixels * 4; ++ii)
	{
		outFrame[ii] = (uint8_t)quantPixels[ii];
	}

	GIF_TEMP_FREE(quantPixels);
}

// Picks palette colors for the image using simple thresholding, no dithering
inline void GifThresholdImage(const uint8_t * lastFrame, const uint8_t * nextFrame, uint8_t * outFrame, uint32_t width, uint32_t height, GifPalette * pPal, GifEncodingMode mode)
{
	bool alphaCompression = mode != GifEncodingMode::AnimatedRGBA;

	uint32_t numPixels = width * height;
	for (uint32_t ii = 0; ii < numPixels; ++ii)
	{
		// if a previous color is available, and it matches the current color,
		// set the pixel to transparent
		if (alphaCompression && lastFrame &&
			lastFrame[0] == nextFrame[0] &&
			lastFrame[1] == nextFrame[1] &&
			lastFrame[2] == nextFrame[2])
		{
			outFrame[0] = lastFrame[0];
			outFrame[1] = lastFrame[1];
			outFrame[2] = lastFrame[2];
			outFrame[3] = kGifTransIndex;
		}
		else
		{
			//LOG_DEBUG(nextFrame[3]);

			if (nextFrame[3] == 255)
			{
				// palettize the pixel
				int32_t bestDiff = 1000000;
				int32_t bestInd = 1;
				GifGetClosestPaletteColor(pPal, nextFrame[0], nextFrame[1], nextFrame[2], bestInd, bestDiff);

				// Write the resulting color to the output buffer
				outFrame[0] = pPal->r[bestInd];
				outFrame[1] = pPal->g[bestInd];
				outFrame[2] = pPal->b[bestInd];
				outFrame[3] = (uint8_t)bestInd;
			}
			else
			{
				// Write the resulting color to the output buffer
				outFrame[0] = 0;
				outFrame[1] = 0;
				outFrame[2] = 0;
				outFrame[3] = kGifTransIndex;
			}
		}

		if (lastFrame) lastFrame += 4;
		outFrame += 4;
		nextFrame += 4;
	}
}

// Simple structure to write out the LZW-compressed portion of the image
// one bit at a time
struct GifBitStatus
{
	uint8_t bitIndex;  // how many bits in the partial byte written so far
	uint8_t byte;      // current partial byte

	uint32_t chunkIndex;
	uint8_t chunk[256];   // bytes are written in here until we have 256 of them, then written to the file
};

// insert a single bit
inline void GifWriteBit(GifBitStatus & stat, uint32_t bit)
{
	bit = bit & 1;
	bit = bit << stat.bitIndex;
	stat.byte |= bit;

	++stat.bitIndex;
	if (stat.bitIndex > 7)
	{
		// move the newly-finished byte to the chunk buffer 
		stat.chunk[stat.chunkIndex++] = stat.byte;
		// and start a new byte
		stat.bitIndex = 0;
		stat.byte = 0;
	}
}

// write all bytes so far to the file
inline void GifWriteChunk(s3d::IWriter * f, GifBitStatus & stat)
{
	FPutc((uint8_t)stat.chunkIndex, f);
	// fwrite(stat.chunk, 1, stat.chunkIndex, f);
	f->write(stat.chunk, stat.chunkIndex);


	stat.bitIndex = 0;
	stat.byte = 0;
	stat.chunkIndex = 0;
}

inline void GifWriteCode(s3d::IWriter * f, GifBitStatus & stat, uint32_t code, uint32_t length)
{
	for (uint32_t ii = 0; ii < length; ++ii)
	{
		GifWriteBit(stat, code);
		code = code >> 1;

		if (stat.chunkIndex == 255)
		{
			GifWriteChunk(f, stat);
		}
	}
}

// The LZW dictionary is a 256-ary tree constructed as the file is encoded,
// this is one node
struct GifLzwNode
{
	uint16_t m_next[256];
};

// write a 256-color (8-bit) image palette to the file
inline void GifWritePalette(const GifPalette * pPal, s3d::IWriter * f)
{
	FPutc(0, f);  // first color: transparency
	FPutc(0, f);
	FPutc(0, f);

	for (int ii = 1; ii < (1 << pPal->bitDepth); ++ii)
	{
		uint8_t r = pPal->r[ii];
		uint8_t g = pPal->g[ii];
		uint8_t b = pPal->b[ii];

		FPutc(r, f);
		FPutc(g, f);
		FPutc(b, f);
	}
}

// write the image header, LZW-compress and write out the image
inline void GifWriteLzwImage(s3d::IWriter * f, uint8_t * image, uint32_t left, uint32_t top, uint32_t width, uint32_t height, uint32_t delay, GifPalette * pPal, GifEncodingMode mode)
{
	// graphics control extension
	FPutc(0x21, f);
	FPutc(0xf9, f);
	FPutc(0x04, f);
	FPutc(mode == GifEncodingMode::AnimatedRGBA ? 0x09 : 0x05, f); // leave prev frame in place, this frame has transparency
	FPutc(delay & 0xff, f);
	FPutc((delay >> 8) & 0xff, f);
	FPutc(kGifTransIndex, f); // transparent color index
	FPutc(0, f);

	FPutc(0x2c, f); // image descriptor block

	FPutc(left & 0xff, f);           // corner of image in canvas space
	FPutc((left >> 8) & 0xff, f);
	FPutc(top & 0xff, f);
	FPutc((top >> 8) & 0xff, f);

	FPutc(width & 0xff, f);          // width and height of image
	FPutc((width >> 8) & 0xff, f);
	FPutc(height & 0xff, f);
	FPutc((height >> 8) & 0xff, f);

	//FPutc(0, f); // no local color table, no transparency
	//FPutc(0x80, f); // no local color table, but transparency

	FPutc((uint8_t)(0x80 + pPal->bitDepth - 1), f); // local color table present, 2 ^ bitDepth entries
	GifWritePalette(pPal, f);

	const int minCodeSize = pPal->bitDepth;
	const uint32_t clearCode = 1 << pPal->bitDepth;

	FPutc((uint8_t)minCodeSize, f); // min code size 8 bits

	GifLzwNode* codetree = (GifLzwNode*)GIF_TEMP_MALLOC(sizeof(GifLzwNode) * 4096);

	if (!codetree)
	{
		return;
	}

	std::memset(codetree, 0, sizeof(GifLzwNode) * 4096);

	int32_t curCode = -1;
	uint32_t codeSize = (uint32_t)minCodeSize + 1;
	uint32_t maxCode = clearCode + 1;

	GifBitStatus stat;
	stat.byte = 0;
	stat.bitIndex = 0;
	stat.chunkIndex = 0;

	GifWriteCode(f, stat, clearCode, codeSize);  // start with a fresh LZW dictionary

	for (uint32_t yy = 0; yy < height; ++yy)
	{
		for (uint32_t xx = 0; xx < width; ++xx)
		{
			uint8_t nextValue = image[(yy * width + xx) * 4 + 3];

			// "loser mode" - no compression, every single code is followed immediately by a clear
			//WriteCode( f, stat, nextValue, codeSize );
			//WriteCode( f, stat, 256, codeSize );

			if (curCode < 0)
			{
				// first value in a new run
				curCode = nextValue;
			}
			else if (codetree[curCode].m_next[nextValue])
			{
				// current run already in the dictionary
				curCode = codetree[curCode].m_next[nextValue];
			}
			else
			{
				// finish the current run, write a code
				GifWriteCode(f, stat, (uint32_t)curCode, codeSize);

				// insert the new run into the dictionary
				codetree[curCode].m_next[nextValue] = (uint16_t)++maxCode;

				if (maxCode >= (1ul << codeSize))
				{
					// dictionary entry count has broken a size barrier,
					// we need more bits for codes
					codeSize++;
				}
				if (maxCode == 4095)
				{
					// the dictionary is full, clear it out and begin anew
					GifWriteCode(f, stat, clearCode, codeSize); // clear tree

					::memset(codetree, 0, sizeof(GifLzwNode) * 4096);
					//bzero(codetree, sizeof(GifLzwNode)*4096);

					codeSize = (uint32_t)(minCodeSize + 1);
					maxCode = clearCode + 1;
				}

				curCode = nextValue;
			}
		}
	}

	// compression footer
	GifWriteCode(f, stat, (uint32_t)curCode, codeSize);
	GifWriteCode(f, stat, clearCode, codeSize);
	GifWriteCode(f, stat, clearCode + 1, (uint32_t)minCodeSize + 1);

	// write out the last partial chunk
	while (stat.bitIndex) GifWriteBit(stat, 0);
	if (stat.chunkIndex) GifWriteChunk(f, stat);

	FPutc(0, f); // image block terminator

	GIF_TEMP_FREE(codetree);
}

struct GifWriter
{
	s3d::IWriter* w = nullptr;
	//FILE* f;
	uint8_t* oldImage = nullptr;
	bool firstFrame = false;
};

// Creates a gif file.
// The input GIFWriter is assumed to be uninitialized.
// The delay value is the time between frames in hundredths of a second - note that not all viewers pay much attention to this value.
inline bool GifBegin(GifWriter * writer, uint32_t width, uint32_t height, uint32_t delay, [[maybe_unused]] int32_t bitDepth = 8, [[maybe_unused]] bool dither = false)
{
	//fopen_s(&writer->f, filename, "wb");

	//writer->f = fopen(filename, "wb");
   // if(!writer->w) return false;

	writer->firstFrame = true;

	// allocate 
	writer->oldImage = (uint8_t*)GIF_MALLOC(width * height * 4);

	writer->w->write("GIF89a", 6);
	// fputs("GIF89a", writer->w);

	 // screen descriptor
	FPutc(width & 0xff, writer->w);
	FPutc((width >> 8) & 0xff, writer->w);
	FPutc(height & 0xff, writer->w);
	FPutc((height >> 8) & 0xff, writer->w);

	FPutc(0xf0, writer->w);  // there is an unsorted global color table of 2 entries
	FPutc(0, writer->w);     // background color
	FPutc(0, writer->w);     // pixels are square (we need to specify this because it's 1989)

	// now the "global" palette (really just a dummy palette)
	// color 0: black
	FPutc(0, writer->w);
	FPutc(0, writer->w);
	FPutc(0, writer->w);
	// color 1: also black
	FPutc(0, writer->w);
	FPutc(0, writer->w);
	FPutc(0, writer->w);

	if (delay != 0)
	{
		// animation header
		FPutc(0x21, writer->w); // extension
		FPutc(0xff, writer->w); // application specific
		FPutc(11, writer->w); // length 11

		writer->w->write("NETSCAPE2.0", 11);
		//fputs("NETSCAPE2.0", writer->w); // yes, really
		FPutc(3, writer->w); // 3 bytes of NETSCAPE2.0 data

		FPutc(1, writer->w); // JUST BECAUSE
		FPutc(0, writer->w); // loop infinitely (byte 0)
		FPutc(0, writer->w); // loop infinitely (byte 1)

		FPutc(0, writer->w); // block terminator
	}

	return true;
}

// Writes out a new frame to a GIF in progress.
// The GIFWriter should have been created by GIFBegin.
// AFAIK, it is legal to use different bit depths for different frames of an image -
// this may be handy to save bits in animations that don't change much.
inline bool GifWriteFrame(GifWriter * writer, const uint8_t * image, uint32_t width, uint32_t height, uint32_t delay, GifEncodingMode mode, int bitDepth = 8, bool dither = false)
{
	if (!writer->w) return false;

	const uint8_t * oldImage = writer->firstFrame ? NULL : writer->oldImage;
	writer->firstFrame = false;

	GifPalette pal;
	GifMakePalette((dither ? NULL : oldImage), image, width, height, bitDepth, dither, &pal, mode);

	if (dither)
		GifDitherImage(oldImage, image, writer->oldImage, width, height, &pal, mode);
	else
		GifThresholdImage(oldImage, image, writer->oldImage, width, height, &pal, mode);

	GifWriteLzwImage(writer->w, writer->oldImage, 0, 0, width, height, delay, &pal, mode);

	return true;
}

// Writes the EOF code, closes the file handle, and frees temp memory used by a GIF.
// Many if not most viewers will still display a GIF properly if the EOF code is missing,
// but it's still a good idea to write it out.
inline bool GifEnd(GifWriter * writer)
{
	if (!writer->w) return false;

	FPutc(0x3b, writer->w); // end of file
	//fclose(writer->w);
	GIF_FREE(writer->oldImage);

	//writer->f = NULL;
	writer->oldImage = NULL;

	return true;
}

#endif
