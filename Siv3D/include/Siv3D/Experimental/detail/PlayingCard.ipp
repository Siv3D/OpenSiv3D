//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------
// s3d::PlayingCard is originally created by Yuta Ishii (OpenSiv3D Project)
//-----------------------------------------------

# pragma once

namespace s3d
{
	namespace PlayingCard
	{
		inline constexpr Card::Card(const Suit _suit, const int32 _rank, const bool _isFaceSide) noexcept
			: rank{ _suit == Suit::Joker ? 0 : _rank }
			, suit{ _suit }
			, isFaceSide{ _isFaceSide } {}

		inline constexpr Card& Card::flip() noexcept
		{
			isFaceSide = (not isFaceSide);
			return *this;
		}

		inline constexpr bool Card::isRed() const noexcept
		{
			return ((suit == Heart) || (suit == Diamond));
		}

		inline constexpr bool Card::isBlack() const noexcept
		{
			return ((suit == Spade) || (suit == Club));
		}

		inline constexpr bool Card::isSpade() const noexcept
		{
			return (suit == Spade);
		}

		inline constexpr bool Card::isHeart() const noexcept
		{
			return (suit == Heart);
		}

		inline constexpr bool Card::isClub() const noexcept
		{
			return (suit == Club);
		}

		inline constexpr bool Card::isDiamond() const noexcept
		{
			return (suit == Diamond);
		}

		inline constexpr bool Card::isJoker() const noexcept
		{
			return (suit == Joker);
		}

		inline constexpr bool Card::isAce() const noexcept
		{
			return (rank == 1);
		}

		inline constexpr bool Card::isJack() const noexcept
		{
			return (rank == 11);
		}

		inline constexpr bool Card::isQueen() const noexcept
		{
			return (rank == 12);
		}

		inline constexpr bool Card::isKing() const noexcept
		{
			return (rank == 13);
		}

		inline constexpr bool Card::isValid() const noexcept
		{
			return (InRange(rank, 1, 13) || isJoker());
		}

		inline constexpr char32 Card::GetSuit(const Suit suit) noexcept
		{
			return U"♠♥♣♦"[static_cast<size_t>(suit)];
		}

		inline constexpr StringView Card::GetRank(const int32 rank) noexcept
		{
			assert(InRange(rank, 1, 13));
			constexpr StringView ranks[13] = { U"A", U"2", U"3", U"4", U"5", U"6", U"7", U"8", U"9", U"10", U"J", U"Q", U"K" };
			return ranks[rank - 1];
		}

		inline CardInfo::CardInfo(const Card& card, const Font& font, const Font& fontLarge, const Font& fontEmoji, const Vec2& size, const double frameThickness, const ColorF& backSideColor)
			: m_card{ card }
			, m_font{ font }
			, m_fontLarge{ fontLarge }
			, m_fontEmoji{ fontEmoji }
			, m_cardSize{ size }
			, m_backSideColor{ backSideColor }
			, m_frameThickness{ frameThickness }
		{
			assert(card.isValid());
		}

		inline void CardInfo::drawBack(const Vec2& pos) const
		{
			RoundRect{ pos, m_cardSize, (m_cardSize.x * corner) }
				.draw()
				.drawFrame(0.0, m_frameThickness, Palette::Black)
				.rect.stretched(m_cardSize.x * -0.1).draw(m_backSideColor);
		}

		inline void CardInfo::drawBack(const double x, const double y) const
		{
			drawBack(Vec2{ x, y });
		}

		inline void CardInfo::drawBack(const Vec2& pos, const double angle) const
		{
			const Transformer2D transformer{ Mat3x2::Rotate(angle, (pos + m_cardSize / 2)) };

			drawBack(pos);
		}

		inline void CardInfo::drawBack(const double x, const double y, const double angle) const
		{
			drawBack(Vec2{ x, y }, angle);
		}

		inline void CardInfo::drawBackAt(const Vec2& center) const
		{
			drawBack(center - m_cardSize * 0.5);
		}

		inline void CardInfo::drawBackAt(const double x, const double y) const
		{
			drawBackAt(Vec2{ x, y });
		}

		inline void CardInfo::drawBackAt(const Vec2& center, const double angle) const
		{
			const Transformer2D transformer{ Mat3x2::Rotate(angle, center) };

			drawBackAt(center);
		}

		inline void CardInfo::drawBackAt(const double x, const double y, const double angle) const
		{
			drawBackAt(Vec2{ x, y }, angle);
		}

		inline void CardInfo::draw(const Vec2& pos) const
		{
			if (not m_card.isFaceSide)
			{
				return drawBack(pos);
			}

			static const std::array<Array<DrawInfo>, 9> drawInfos =
			{ {
				{	// 2
					DrawInfo{ false, Vec2{ 0.0,-1.0 / 3.0 } },
					DrawInfo{ true, Vec2{ 0.0,1.0 / 3.0 } }
				},

				{	// 3
					DrawInfo{ false, Vec2{ 0.0,0.0 } },
					DrawInfo{ false, Vec2{ 0.0,-1.0 / 3.0 } },
					DrawInfo{ true, Vec2{ 0.0,1.0 / 3.0 } }
				},

				{	// 4
					DrawInfo{ false, Vec2{ 0.2,-1.0 / 3.0 } },
					DrawInfo{ true, Vec2{ -0.2,1.0 / 3.0 } },
					DrawInfo{ true, Vec2{ 0.2,1.0 / 3.0 } },
					DrawInfo{ false, Vec2{ -0.2,-1.0 / 3.0 } }
				},

				{	// 5
					DrawInfo{ false, Vec2{ 0.2,-1.0 / 3.0 } },
					DrawInfo{ true, Vec2{ -0.2,1.0 / 3.0 } },
					DrawInfo{ true, Vec2{ 0.2,1.0 / 3.0 } },
					DrawInfo{ false, Vec2{ -0.2,-1.0 / 3.0 } },
					DrawInfo{ false, Vec2{ 0.0,0.0 } }
				},

				{	// 5
					DrawInfo{ false, Vec2{ -0.2, -1.0 / 3.0 } },
					DrawInfo{ false, Vec2{ 0.2, -1.0 / 3.0 } },
					DrawInfo{ false, Vec2{ -0.2, 0.0 } },
					DrawInfo{ false, Vec2{ 0.2, 0.0 } },
					DrawInfo{ true, Vec2{ -0.2, 1.0 / 3.0 } },
					DrawInfo{ true, Vec2{ 0.2, 1.0 / 3.0 } },
				},

				{	// 6
					DrawInfo{ false, Vec2{ -0.2, -1.0 / 3.0 } },
					DrawInfo{ false, Vec2{ 0.2, -1.0 / 3.0 } },
					DrawInfo{ false, Vec2{ -0.2, 0.0 } },
					DrawInfo{ false, Vec2{ 0.2, 0.0 } },
					DrawInfo{ true, Vec2{ -0.2, 1.0 / 3.0 } },
					DrawInfo{ true, Vec2{ 0.2, 1.0 / 3.0 } },
					DrawInfo{ false, Vec2{ 0.0, -1.0 / 6.0 } },
				},

				{	// 7
					DrawInfo{ false, Vec2{ -0.2, -1.0 / 3.0 } },
					DrawInfo{ false, Vec2{ 0.2, -1.0 / 3.0 } },
					DrawInfo{ false, Vec2{ -0.2, 0.0 } },
					DrawInfo{ false, Vec2{ 0.2, 0.0 } },
					DrawInfo{ true, Vec2{ -0.2, 1.0 / 3.0 } },
					DrawInfo{ true, Vec2{ 0.2, 1.0 / 3.0 } },
					DrawInfo{ false, Vec2{ 0.0, -1.0 / 6.0 } },
					DrawInfo{ true, Vec2{ 0.0, 1.0 / 6.0 } },
				},

				{	// 8
					DrawInfo{ false, Vec2{ -0.2, -1.0 / 3.0 } },
					DrawInfo{ false, Vec2{ 0.2, -1.0 / 3.0 } },
					DrawInfo{ true, Vec2{ -0.2, 1.0 / 3.0 } },
					DrawInfo{ true, Vec2{ 0.2, 1.0 / 3.0 } },
					DrawInfo{ false, Vec2{ -0.2, -1.0 / 9.0 } },
					DrawInfo{ false, Vec2{ 0.2, -1.0 / 9.0 } },
					DrawInfo{ true, Vec2{ -0.2, 1.0 / 9.0 } },
					DrawInfo{ true, Vec2{ 0.2, 1.0 / 9.0 } },
					DrawInfo{ false, Vec2{ 0.0, 0.0 } },
				},

				{	// 9
					DrawInfo{ false, Vec2{ -0.2, -1.0 / 3.0 } },
					DrawInfo{ false, Vec2{ 0.2, -1.0 / 3.0 } },
					DrawInfo{ true, Vec2{ -0.2, 1.0 / 3.0 } },
					DrawInfo{ true, Vec2{ 0.2, 1.0 / 3.0 } },
					DrawInfo{ false, Vec2{ -0.2, -1.0 / 9.0 } },
					DrawInfo{ false, Vec2{ 0.2, -1.0 / 9.0 } },
					DrawInfo{ true, Vec2{ -0.2, 1.0 / 9.0 } },
					DrawInfo{ true, Vec2{ 0.2, 1.0 / 9.0 } },
					DrawInfo{ false, Vec2{ 0.0, -1.0 / 4.5 } },
					DrawInfo{ true, Vec2{ 0.0, 1.0 / 4.5 } }
				},
			} };

			const Vec2 center = (pos + m_cardSize * 0.5);
			const Vec2 centering = (m_cardSize * 0.1);
			const double drawSize = (0.34 / 0.467);
			const ColorF color = (m_card.isRed() ? Palette::Red : Palette::Black);

			RoundRect{ pos, m_cardSize, (m_cardSize.x * corner) }
				.draw()
				.drawFrame(0, m_frameThickness, Palette::Black);

			if (m_card.isJoker())
			{
				const Array<Glyph> glyphs = m_font.getGlyphs(U"JOKER");
				const auto& glyphTexture = glyphs[0].texture;
				const double height = glyphTexture.size.y * drawSize * 1.08;
				const Vec2 drawPos{ centering / 10 + Vec2{ glyphTexture.resized(Vec2{ glyphTexture.size } *drawSize).size.x, height * 0.5 } };

				for (size_t a = 0; a < glyphs.size(); ++a)
				{
					const TextureRegion t = glyphs[a].texture.resized(Vec2{ glyphTexture.size } * drawSize);
					t.drawAt(pos + drawPos + Vec2{ 0, a * height * 1.2 }, color);
					t.flipped().mirrored().drawAt(pos - drawPos - Vec2{ 0, a * height * 1.2 } + m_cardSize, color);
				}

				m_fontEmoji.getGlyph(U'♋').texture.scaled(0.9).drawAt(center, color);

				return;
			}

			const Glyph suitGlyph = m_font.getGlyph(Card::GetSuit(m_card.suit));
			const Glyph rankGlyph = m_font.getGlyph(Card::GetRank(m_card.rank)[0]);
			const Vec2 suitpos{ 0.0, m_cardSize.y * 0.13888 };

			suitGlyph.texture.scaled(drawSize).drawAt(pos.movedBy(centering + suitpos), color);
			suitGlyph.texture.scaled(drawSize).flipped().mirrored().drawAt(pos + m_cardSize - centering - suitpos, color);

			if (m_card.rank == 10)
			{
				const auto zerotexture = m_font.getGlyph(U'0');
				const Vec2 rankSize = Vec2{ rankGlyph.texture.size.x * 2.2 / 3.0, rankGlyph.texture.size.y } *drawSize;

				rankGlyph.texture.resized(rankSize)
					.drawAt(pos + centering - Vec2{ rankSize.x * 1.1, 0 }, color);
				rankGlyph.texture.resized(rankSize)
					.flipped().mirrored()
					.drawAt(pos + m_cardSize - centering + Vec2{ rankSize.x * 1.1, 0 }, color);

				zerotexture.texture.scaled(drawSize * 0.8, drawSize)
					.drawAt(pos + centering + Vec2{ rankGlyph.texture.size.x * drawSize - rankSize.x / 1.55, 0 }, color);
				zerotexture.texture.scaled(drawSize * 0.8, drawSize)
					.flipped().mirrored()
					.drawAt(pos - centering + Vec2{ -rankGlyph.texture.size.x * drawSize + rankSize.x / 1.55, 0 } + m_cardSize, color);
			}
			else
			{
				rankGlyph.texture.scaled(drawSize).drawAt(pos + centering, color);
				rankGlyph.texture.scaled(drawSize).flipped().mirrored().drawAt(pos + m_cardSize - centering, color);
			}

			if (InRange(m_card.rank, 2, 10))
			{
				for (const auto& drawInfo : drawInfos[m_card.rank - 2])
				{
					suitGlyph.texture.flipped(drawInfo.flip).drawAt(center.movedBy(m_cardSize * drawInfo.offset), color);
				}
			}
			else
			{
				const char32 c[4] = { static_cast<char32>(Card::GetSuit(m_card.suit)), U'\x1f482', U'\x1f478', U'\x1f474' };

				m_fontEmoji.getGlyph(c[(m_card.rank - 1) % 9 % 4]).texture.drawAt(center.movedBy(m_card.rank == 13 ? Vec2{ 0, m_cardSize.y / 12 - m_cardSize.y / 21 } : Vec2::Zero()), color);

				if (m_card.isKing())
				{
					m_fontEmoji.getGlyph(U'\x1f451').texture.scaled(0.6).drawAt(center.movedBy(0, -m_cardSize.y / 7 - m_cardSize.y / 21), color);
				}
			}
		}

		inline void CardInfo::draw(const double x, const double y) const
		{
			draw(Vec2{ x, y });
		}

		inline void CardInfo::draw(const Vec2& pos, const double angle) const
		{
			const Transformer2D transformer{ Mat3x2::Rotate(angle, pos + m_cardSize / 2) };

			draw(pos);
		}

		inline void CardInfo::draw(const double x, const double y, const double angle) const
		{
			draw(Vec2{ x, y }, angle);
		}

		inline void CardInfo::drawAt(const Vec2& center) const
		{
			draw(center - m_cardSize * 0.5);
		}

		inline void CardInfo::drawAt(const double x, const double y) const
		{
			drawAt(Vec2{ x, y });
		}

		inline void CardInfo::drawAt(const Vec2& center, const double angle) const
		{
			const Transformer2D transformer{ Mat3x2::Rotate(angle, center) };

			draw(center - m_cardSize * 0.5);
		}

		inline void CardInfo::drawAt(const double x, const double y, const double angle) const
		{
			drawAt(Vec2{ x, y }, angle);
		}

		inline void CardInfo::drawSimple(const Vec2& pos) const
		{
			if (m_card.isFaceSide)
			{
				const RectF rect{ pos, m_cardSize };
				RoundRect{ rect, rect.w * corner }
					.draw()
					.drawFrame(m_frameThickness, Palette::Black);

				if (not m_card.isJoker())
				{
					const ColorF color = (m_card.isRed() ? Palette::Red : Palette::Black);
					const char32 suit = Card::GetSuit(m_card.suit);
					const StringView rank = Card::GetRank(m_card.rank);

					m_fontLarge(suit).drawAt(pos.movedBy(m_cardSize.x * 0.5, m_cardSize.y * 0.3), color);
					m_fontLarge(rank).drawAt(pos.movedBy(m_cardSize.x * 0.5, m_cardSize.y * 0.67), color);
				}
				else
				{
					m_fontEmoji.getGlyph(U'♋').texture.scaled(0.9).drawAt(rect.center(), Palette::Black);
				}
			}
			else
			{
				drawBack(pos);
			}
		}

		inline void CardInfo::drawSimple(const double x, const double y) const
		{
			drawSimple(Vec2{ x, y });
		}

		inline void CardInfo::drawSimple(const Vec2& pos, const double angle) const
		{
			const Transformer2D transformer{ Mat3x2::Rotate(angle, pos + m_cardSize / 2) };

			drawSimple(pos);
		}

		inline void CardInfo::drawSimple(const double x, const double y, const double angle) const
		{
			drawSimple(Vec2{ x, y }, angle);
		}

		inline void CardInfo::drawSimpleAt(const Vec2& center) const
		{
			drawSimple(center - m_cardSize * 0.5);
		}

		inline void CardInfo::drawSimpleAt(const double x, const double y) const
		{
			drawSimpleAt(Vec2{ x, y });
		}

		inline void CardInfo::drawSimpleAt(const Vec2& center, const double angle) const
		{
			const Transformer2D transformer{ Mat3x2::Rotate(angle, center) };

			drawSimple(center - m_cardSize * 0.5);
		}

		inline void CardInfo::drawSimpleAt(const double x, const double y, const double angle) const
		{
			drawSimpleAt(Vec2{ x, y }, angle);
		}

		inline constexpr int32 CalculateFontSize(const double cardWidth) noexcept
		{
			return Max(static_cast<int32>(cardWidth * (2.0 / 3.0)), 1);
		}

		inline Pack::Pack(const Font& font, const Font& fontLarge, const Font& fontEmoji, const double cardWidth, const ColorF& backSideColor, const double frameThickness)
			: m_font{ font }
			, m_fontLarge{ fontLarge }
			, m_fontEmoji{ fontEmoji }
			, m_cardSize{ cardWidth, cardWidth * Math::Phi }
			, m_backSideColor{ backSideColor }
			, m_framethickness{ frameThickness } {}

		inline Pack::Pack(const double cardWidth, const ColorF& backSideColor, const double frameThickness)
			: m_font{ CalculateFontSize(cardWidth * 0.475) }
			, m_fontLarge{ CalculateFontSize(cardWidth) }
			, m_fontEmoji{ CalculateFontSize(cardWidth), Typeface::MonochromeEmoji }
			, m_cardSize{ cardWidth, cardWidth * Math::Phi }
			, m_backSideColor{ backSideColor }
			, m_framethickness{ frameThickness } {}

		inline CardInfo Pack::operator ()(const Suit suit, const int32 rank, const bool isFaceSide) const
		{
			return operator()(Card{ suit, rank, isFaceSide });
		}

		inline CardInfo Pack::operator ()(const Card& card) const
		{
			return CardInfo{ card, m_font, m_fontLarge, m_fontEmoji, m_cardSize, m_framethickness, m_backSideColor };
		}

		inline Vec2 Pack::size() const noexcept
		{
			return m_cardSize;
		}

		inline double Pack::width() const noexcept
		{
			return m_cardSize.x;
		}

		inline double Pack::height() const noexcept
		{
			return m_cardSize.y;
		}

		inline RectF Pack::region(const Vec2& pos) const
		{
			return{ pos, m_cardSize };
		}

		inline Quad Pack::region(const Vec2& pos, const double angle) const
		{
			return RectF{ pos, m_cardSize }.rotated(angle);
		}

		inline RectF Pack::regionAt(const Vec2& center) const
		{
			return{ Arg::center = center, m_cardSize };
		}

		inline Quad Pack::regionAt(const Vec2& center, const double angle) const
		{
			return RectF{ Arg::center = center, m_cardSize }.rotated(angle);
		}

		inline Array<Card> CreateDeck(const size_t num_jokers, const bool isFaceSide)
		{
			Array<Card> cards(Arg::reserve = (13 * 4 + num_jokers));
			{
				for (uint16 suit = 0; suit < 4; ++suit)
				{
					for (int32 i = 1; i <= 13; ++i)
					{
						cards.emplace_back(static_cast<Suit>(suit), i, isFaceSide);
					}
				}

				cards.insert(cards.end(), num_jokers, Card{ Suit::Joker, 0, isFaceSide });
			}

			return cards;
		}
	}
}
