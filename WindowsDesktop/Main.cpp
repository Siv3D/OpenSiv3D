
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

struct AnimationTexture
{
	Array<Texture> textures;
	
	Array<int32> delays;
	
	int32 duration = 0;

	explicit operator bool() const noexcept
	{
		return !textures.isEmpty();
	}

	Size size() const noexcept
	{
		if (!textures)
		{
			return Size(0, 0);
		}

		return textures.front().size();
	}

	size_t frames() const noexcept
	{
		return textures.size();
	}

	size_t getFrameIndex(int32 timeMillisec) const noexcept
	{
		return AnimatedGIFReader::MillisecToIndex(timeMillisec, delays, duration);
	}

	const Texture& getTexture(int32 timeMillisec) const noexcept
	{
		return textures[getFrameIndex(timeMillisec)];
	}
};

void Main()
{
	AnimationTexture animation;
	{
		const AnimatedGIFReader gif(U"example/test.gif");

		if (!gif)
		{
			throw Error(U"Failed to open a gif file");
		}

		Array<Image> images;
			
		if (gif.read(images, animation.delays, animation.duration))
		{
			animation.textures = images.map([](const Image& i) { return Texture(i); });
		}
		else
		{
			throw Error(U"Failed to load a gif animation");
		}
	}

	Print << U"{}, {} frames ({} ms)"_fmt(animation.size(), animation.frames(), animation.duration);

	const Point pos(10, 90);
	bool showTiles = false;

	while (System::Update())
	{
		const int32 timeMillisec = static_cast<int32>(Scene::Time() * 1000);
		const auto& texture = animation.getTexture(timeMillisec);

		SimpleGUI::CheckBox(showTiles, U"Show tiles", Vec2(10, 40));

		if (showTiles)
		{
			Rect(pos, texture.size()).draw();
			{
				ScopedViewport2D vp(pos, texture.size());
				for (auto p : step(texture.size() / 10 + Size(1, 1)))
				{
					if (IsEven(p.x + p.y))
					{
						Rect(p * 10, 10).draw(ColorF(0.8));
					}
				}
			}
		}

		texture.draw(pos);
	}
}
