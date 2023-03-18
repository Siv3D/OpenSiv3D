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

# include <Siv3D/Image.hpp>
# include "AnimatedGIFReaderDetail.hpp"
# include <gif_load/gif_load.h>

namespace s3d
{
	struct GifData
	{
		void* data = nullptr;
		void* pict = nullptr;
		void* prev = nullptr;
		unsigned long last = 0;
		Array<Image> images;
		Array<int32> delays; // ms
		Image lastImage;

		~GifData()
		{
			std::free(data); data = nullptr;
			std::free(pict); pict = nullptr;
			std::free(prev); prev = nullptr;
		}
	};

	inline constexpr uint32 RGBA(const GIF_WHDR* whdr, size_t i)
	{
		return (whdr->bptr[i] == whdr->tran) ? 0 :
			(uint32(whdr->cpal[whdr->bptr[i]].R << 24)
				| uint32(whdr->cpal[whdr->bptr[i]].G << 16)
				| uint32(whdr->cpal[whdr->bptr[i]].B << 8)
				| 0xFFu);
	}

	static void ReadAllCallback(void* data, GIF_WHDR* whdr)
	{
		GifData* gif = static_cast<GifData*>(data);
		uint32_t* pict, * prev, x, y, yoff, iter, ifin, dsrc, ddst;

		if (!whdr->ifrm)
		{
			/** TGA doesn`t support heights over 0xFFFF, so we have to trim: **/
			whdr->nfrm = ((whdr->nfrm < 0) ? -whdr->nfrm : whdr->nfrm) * whdr->ydim;
			whdr->nfrm = (whdr->nfrm < 0xFFFF) ? whdr->nfrm : 0xFFFF;
			/** this is the very first frame, so we must write the header **/
			ddst = (uint32_t)(whdr->xdim * whdr->ydim);
			gif->pict = calloc(sizeof(uint32_t), ddst);
			gif->prev = calloc(sizeof(uint32_t), ddst);
		}
		/** [TODO:] the frame is assumed to be inside global bounds,
					however it might exceed them in some GIFs; fix me. **/
		pict = (uint32_t*)gif->pict;
		ddst = (uint32_t)(whdr->xdim * whdr->fryo + whdr->frxo);
		ifin = (!(iter = (whdr->intr) ? 0 : 4)) ? 4 : 5; /** interlacing support **/

		for (dsrc = (uint32_t)-1; iter < ifin; iter++)
		{
			for (yoff = 16U >> ((iter > 1) ? iter : 1), y = (8 >> iter) & 7; y < (uint32_t)whdr->fryd; y += yoff)
			{
				for (x = 0; x < (uint32_t)whdr->frxd; x++)
				{
					if (whdr->tran != (long)whdr->bptr[++dsrc])
					{
						pict[(uint32_t)whdr->xdim * y + x + ddst] = RGBA(whdr, dsrc);
					}
				}
			}
		}

		const Size rawImageSize(whdr->frxd, whdr->fryd);
		const Point offset(whdr->frxo, whdr->fryo);
		Image image;

		if (!gif->lastImage) // first frame
		{
			image.resize(rawImageSize);
			for (int32 yy = 0; yy < rawImageSize.y; ++yy)
			{
				for (int32 xx = 0; xx < rawImageSize.x; ++xx)
				{
					image[yy][xx] = Color::FromRGBA(pict[whdr->xdim * yy + xx + ddst]);
				}
			}
		}
		else
		{
			image = gif->lastImage;
			for (int32 yy = 0; yy < rawImageSize.y; ++yy)
			{
				for (int32 xx = 0; xx < rawImageSize.x; ++xx)
				{
					image[yy + offset.y][xx + offset.x] = Color::FromRGBA(pict[whdr->xdim * yy + xx + ddst]);
				}
			}
		}

		gif->images << image;
		gif->delays << (whdr->time * 10);
		gif->lastImage = image;

		if ((whdr->mode == GIF_PREV) && !gif->last)
		{
			whdr->frxd = whdr->xdim;
			whdr->fryd = whdr->ydim;
			whdr->mode = GIF_BKGD;
			ddst = 0;
		}
		else
		{
			gif->last = (whdr->mode == GIF_PREV) ? gif->last : (unsigned long)(whdr->ifrm + 1);
			pict = (uint32_t*)((whdr->mode == GIF_PREV) ? gif->pict : gif->prev);
			prev = (uint32_t*)((whdr->mode == GIF_PREV) ? gif->prev : gif->pict);
			for (x = (uint32_t)(whdr->xdim * whdr->ydim); --x; pict[x - 1] = prev[x - 1])
			{
				;
			}
		}

		// cutting a hole for the next frame
		if (whdr->mode == GIF_BKGD)
		{
			for (whdr->bptr[0] = (uint8_t)((whdr->tran >= 0) ? whdr->tran : whdr->bkgd), y = 0, pict = (uint32_t*)gif->pict;
				y < (uint32_t)whdr->fryd; y++)
			{
				for (x = 0; x < (uint32_t)whdr->frxd; x++)
				{
					pict[(uint32_t)whdr->xdim * y + x + ddst] = 0;
					gif->lastImage[Point(x, y) + offset] = Color(0, 0);
				}
			}
		}
	}
}

namespace s3d
{
	AnimatedGIFReader::AnimatedGIFReaderDetail::AnimatedGIFReaderDetail() {}

	AnimatedGIFReader::AnimatedGIFReaderDetail::~AnimatedGIFReaderDetail()
	{
		// do nothing
	}

	bool AnimatedGIFReader::AnimatedGIFReaderDetail::open(const FilePathView path)
	{
		m_blob.createFromFile(path);

		return isOpen();
	}

	bool AnimatedGIFReader::AnimatedGIFReaderDetail::open(IReader&& reader)
	{
		const size_t size_bytes = reader.size();

		m_blob.resize(size_bytes);
		reader.read(m_blob.data(), m_blob.size());

		return isOpen();
	}

	void AnimatedGIFReader::AnimatedGIFReaderDetail::close()
	{
		m_blob.release();
	}

	bool AnimatedGIFReader::AnimatedGIFReaderDetail::isOpen() const noexcept
	{
		return (not m_blob.isEmpty());
	}

	bool AnimatedGIFReader::AnimatedGIFReaderDetail::read(Array<Image>& images, Array<int32>& delaysMillisec) const
	{
		images.clear();
		delaysMillisec.clear();

		if (not isOpen())
		{
			return false;
		}

		GifData gif;
		const long ret = GIF_Load(static_cast<const void*>(m_blob.data()), static_cast<long>(m_blob.size()),
			ReadAllCallback, nullptr, &gif, 0L);

		if (ret < 0 || !gif.images)
		{
			return false;
		}

		images = std::move(gif.images);
		delaysMillisec = std::move(gif.delays);

		return true;
	}
}
