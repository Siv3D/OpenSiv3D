//-----------------------------------------------
//
//	This file is part of the HamFramework for Siv3D.
//
//	Copyright (C) 2014-2018 HAMSTRO
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D.hpp>

namespace s3d
{
	namespace OptimalScreen
	{
		enum class Preference
		{
			Min,

			Max,

			AspectMin,

			AspectMax,
		};

		struct Setting
		{
			size_t displayIndex;

			DisplayMode dislayMode;

			double xScale;
		};

		inline Array<Setting> Enum(
			const Optional<Size>& targetResolution = none,
			const Optional<int32>& targetRefreshRate = 60,
			const Optional<size_t>& targetDisplayIndex = 0)
		{
			Array<Setting> results;
			{
				const auto outputs = Graphics::EnumOutputs();

				size_t displayIndex = 0;

				for (const auto& output : outputs)
				{
					Size maxResolution(0, 0);

					// Get max resolution
					for (const auto& mode : output.displayModes)
					{
						if ((maxResolution.x * maxResolution.y) < (mode.size.x * mode.size.y))
						{
							maxResolution = mode.size;
						}
					}

					const double screenAspect = static_cast<double>(maxResolution.x) / maxResolution.y;

					for (const auto& mode : output.displayModes)
					{
						const double aspect = static_cast<double>(mode.size.x) / mode.size.y;

						if (targetResolution)
						{
							if ((mode.size.x >= targetResolution->x && mode.size.y >= targetResolution->y)
								|| mode.size == maxResolution)
							{
								results.push_back({ displayIndex, mode, screenAspect / aspect });
							}
						}
						else
						{
							results.push_back({ displayIndex, mode, screenAspect / aspect });
						}
					}

					++displayIndex;
				}

				if (targetDisplayIndex && results.count_if([index = *targetDisplayIndex](const auto& result){ return result.displayIndex == index; }))
				{
					results.remove_if([index = *targetDisplayIndex](const auto& result){ return result.displayIndex != index; });
				}
			}

			Array<Setting> results2;
			{
				Array<Setting> tmps;
				std::pair<size_t, Size> previous(0, Size(0, 0));

				for (const auto& result : results)
				{
					const auto current = std::make_pair(result.displayIndex, result.dislayMode.size);

					if (previous == current)
					{
						tmps.push_back(result);
					}
					else
					{
						if (tmps.size() > 1)
						{
							if (targetRefreshRate)
							{
								results2.push_back(tmps.sorted_by([target = *targetRefreshRate](const auto& a, const auto& b)
								{
									return std::abs(target - a.dislayMode.refreshRateHz) < std::abs(target - b.dislayMode.refreshRateHz);
								}).front());

								tmps.clear();
							}
							else
							{
								results2.push_back(tmps.sorted_by([](const auto& a, const auto& b)
								{
									return a.dislayMode.refreshRateHz < b.dislayMode.refreshRateHz;
								}).back());

								tmps.clear();
							}
						}
						else if (tmps.size() == 1)
						{
							results2.push_back(tmps.front());

							tmps.clear();
						}

						previous = current;

						tmps.push_back(result);
					}
				}

				if (tmps.size() > 1)
				{
					if (targetRefreshRate)
					{
						results2.push_back(tmps.sorted_by([target = *targetRefreshRate](const auto& a, const auto& b)
						{
							return std::abs(target - a.dislayMode.refreshRateHz) < std::abs(target - b.dislayMode.refreshRateHz);
						}).front());
					}
					else
					{
						results2.push_back(tmps.sorted_by([](const auto& a, const auto& b)
						{
							return a.dislayMode.refreshRateHz < b.dislayMode.refreshRateHz;
						}).back());
					}
				}
				else if (tmps.size() == 1)
				{
					results2.push_back(tmps.front());
				}
			}

			return results2;
		}

		inline std::pair<size_t, DisplayMode> Get(
			Preference preference = Preference::AspectMin,
			const Optional<Size>& targetResolution = none,
			const Optional<int32>& targetRefreshRate = 60,
			const Optional<size_t>& targetDisplayIndex = 0)
		{
			Array<Setting> results = Enum(targetResolution, targetRefreshRate, targetDisplayIndex);

			if (results.size() == 1)
			{
				const auto& reuslt = results.front();

				return{ reuslt.displayIndex, reuslt.dislayMode };
			}

			if (!targetResolution)
			{
				if (preference == Preference::AspectMin)
				{
					preference = Preference::Min;
				}
				else if (preference == Preference::AspectMin)
				{
					preference = Preference::Max;
				}
			}

			if (preference == Preference::Min)
			{
				const auto& reuslt = results.stable_sort_by([](const auto& a, const auto& b)
				{
					return (a.dislayMode.size.x * a.dislayMode.size.y) < (b.dislayMode.size.x * b.dislayMode.size.y);
				}).front();

				return{ reuslt.displayIndex, reuslt.dislayMode };
			}
			else if (preference == Preference::Max)
			{
				const auto& reuslt = results.stable_sort_by([](const auto& a, const auto& b)
				{
					return (a.dislayMode.size.x * a.dislayMode.size.y) > (b.dislayMode.size.x * b.dislayMode.size.y);
				}).front();

				return{ reuslt.displayIndex, reuslt.dislayMode };
			}
			else if (preference == Preference::AspectMin)
			{
				results.stable_sort_by([](const auto& a, const auto& b)
				{
					return (a.dislayMode.size.x * a.dislayMode.size.y) < (b.dislayMode.size.x * b.dislayMode.size.y);
				});

				const auto& reuslt = results.stable_sort_by([](const auto& a, const auto& b)
				{
					double ar = std::abs(1.0 - a.xScale);
					double br = std::abs(1.0 - b.xScale);
					
					if (ar < 0.005)
					{
						ar = 0.0;
					}

					if (br < 0.005)
					{
						br = 0.0;
					}

					return ar < br;
				}).front();

				return{ reuslt.displayIndex, reuslt.dislayMode };
			}
			else // preference == Preference::AspectMax
			{
				results.stable_sort_by([](const auto& a, const auto& b)
				{
					return (a.dislayMode.size.x * a.dislayMode.size.y) > (b.dislayMode.size.x * b.dislayMode.size.y);
				});

				const auto& reuslt = results.stable_sort_by([](const auto& a, const auto& b)
				{
					double ar = std::abs(1.0 - a.xScale);
					double br = std::abs(1.0 - b.xScale);

					if (ar < 0.005)
					{
						ar = 0.0;
					}

					if (br < 0.005)
					{
						br = 0.0;
					}

					return ar < br;
				}).front();

				return{ reuslt.displayIndex, reuslt.dislayMode };
			}
		}
	}
}

/* example

# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	const auto[displayIndex, displayMode] = OptimalScreen::Get(OptimalScreen::Preference::Min, Size(1280, 720));

	Print << displayIndex << U":" << displayMode.size << U"@" << displayMode.refreshRateHz;

	Graphics::SetFullScreen(true, displayMode.size, displayIndex, displayMode.refreshRateHz);

	while (System::Update())
	{
		Circle(Cursor::Pos(), 100).draw(ColorF(1.0, 0.0, 0.0, 0.5));
	}
}

*/
