//-----------------------------------------------
//
//	This file is part of the HamFramework for Siv3D.
//
//	Copyright (C) 2014-2017 HAMSTRO
//	Copyright (c) 2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D.hpp>

namespace s3d
{
	namespace PlayingCard
	{
		/// <summary>
		/// カードのスート（絵柄のマーク）
		/// </summary>
		enum Suit : uint16
		{
			/// <summary>
			/// ♠ スペード
			/// </summary>
			Spade,

			/// <summary>
			/// ♥ ハート
			/// </summary>
			Heart,

			/// <summary>
			/// ♣ クローバー
			/// </summary>
			Club,

			/// <summary>
			/// ♣ クローバー
			/// </summary>
			Clover = Club,

			/// <summary>
			/// ♦ ダイヤモンド
			/// </summary>
			Diamond,

			/// <summary>
			/// ジョーカー
			/// </summary>
			Joker,
		};

		/// <summary>
		/// カードの番号、スート、裏表などのデータ
		/// </summary>
		struct Card
		{
			/// <summary>
			/// 表向き
			/// </summary>
			static constexpr bool Front = true;

			/// <summary>
			/// 裏向き
			/// </summary>
			static constexpr bool Back = false;

			/// <summary>
			/// スートの文字を返します。
			/// </summary>
			/// <param name="suit">
			/// スート
			/// </param>
			/// <returns>
			/// スートの文字
			/// </returns>
			static constexpr wchar GetSuit(const Suit suit)
			{
				return L"♠♥♣♦"[static_cast<size_t>(suit)];
			}

			/// <summary>
			/// 番号の文字列表現を返します。
			/// </summary>
			/// <param name="rank">
			/// 番号
			/// </param>
			/// <returns>
			/// 番号の文字列表現
			/// </returns>
			static String GetRank(const int32 rank)
			{
				assert(InRange(rank, 1, 13));

				static const String ranks[13] = { L"A", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"10", L"J", L"Q", L"K" };

				return ranks[rank - 1];
			}

			/// <summary>
			/// 番号
			/// </summary>
			int32 rank;

			/// <summary>
			/// スート
			/// </summary>
			Suit suit;

			/// <summary>
			/// 表向きであるか
			/// </summary>
			bool isFaceSide;

			/// <summary>
			/// デフォルトコンストラクタ
			/// </summary>
			Card() = default;

			/// <summary>
			/// カードを作成します。
			/// </summary>
			/// <param name="_suit">
			/// スート
			/// </param>
			/// <param name="_rank">
			/// 番号
			/// </param>
			/// <param name="_isFaceSide">
			/// 表向きであるか
			/// </param>
			constexpr Card(Suit _suit, int32 _rank, bool _isFaceSide = true) noexcept
				: suit(_suit)
				, rank(suit == Suit::Joker ? 0 : _rank)
				, isFaceSide(_isFaceSide) {}

			/// <summary>
			/// カードを裏表を反転します。
			/// </summary>
			/// <returns>
			/// *this
			/// </returns>
			constexpr Card& flip() noexcept
			{
				isFaceSide = !isFaceSide;
				return *this;
			}

			/// <summary>
			/// カードが赤色のスート（ハートまたはダイヤモンド）かどうかを返します。
			/// </summary>
			/// <returns>
			/// カードが赤色のスートの場合 true, それ以外の場合は false
			/// </returns>
			constexpr bool isRed() const noexcept
			{
				return suit == Heart || suit == Diamond;
			}

			/// <summary>
			/// カードが黒色のスート（スペードまたはクローバー）かどうかを返します。
			/// </summary>
			/// <returns>
			/// カードが黒色のスートの場合 true, それ以外の場合は false
			/// </returns>
			constexpr bool isBlack() const noexcept
			{
				return suit == Spade || suit == Club;
			}

			/// <summary>
			/// カードのスートがスペードかどうかを返します。
			/// </summary>
			/// <returns>
			/// カードのスートがスペードの場合 true, それ以外の場合は false
			/// </returns>
			constexpr bool isSpade() const noexcept
			{
				return suit == Spade;
			}

			/// <summary>
			/// カードのスートがハートかどうかを返します。
			/// </summary>
			/// <returns>
			/// カードのスートがハートの場合 true, それ以外の場合は false
			/// </returns>
			constexpr bool isHeart() const noexcept
			{
				return suit == Heart;
			}

			/// <summary>
			/// カードのスートがクローバーかどうかを返します。
			/// </summary>
			/// <returns>
			/// カードのスートがクローバーの場合 true, それ以外の場合は false
			/// </returns>
			constexpr bool isClub() const noexcept
			{
				return suit == Club;
			}

			/// <summary>
			/// カードのスートがダイヤモンドかどうかを返します。
			/// </summary>
			/// <returns>
			/// カードのスートがダイヤモンドの場合 true, それ以外の場合は false
			/// </returns>
			constexpr bool isDiamond() const noexcept
			{
				return suit == Diamond;
			}

			/// <summary>
			/// カードがジョーカーかどうかを返します。
			/// </summary>
			/// <returns>
			/// カードがジョーカーの場合 true, それ以外の場合は false
			/// </returns>
			constexpr bool isJoker() const noexcept
			{
				return suit == Joker;
			}

			/// <summary>
			/// カードがエース (A) かどうかを返します。
			/// </summary>
			/// <returns>
			/// カードがエース (A) の場合 true, それ以外の場合は false
			/// </returns>
			constexpr bool isAce() const noexcept
			{
				return rank == 1;
			}

			/// <summary>
			/// カードがジャック (J) かどうかを返します。
			/// </summary>
			/// <returns>
			/// カードがジャック (J) の場合 true, それ以外の場合は false
			/// </returns>
			constexpr bool isJack() const noexcept
			{
				return rank == 11;
			}

			/// <summary>
			/// カードがクイーン (Q) かどうかを返します。
			/// </summary>
			/// <returns>
			/// カードがクイーン (Q) の場合 true, それ以外の場合は false
			/// </returns>
			constexpr bool isQueen() const noexcept
			{
				return rank == 12;
			}

			/// <summary>
			/// カードがキング (K) かどうかを返します。
			/// </summary>
			/// <returns>
			/// カードがキング (K) の場合 true, それ以外の場合は false
			/// </returns>
			constexpr bool isKing() const noexcept
			{
				return rank == 13;
			}

			/// <summary>
			/// カードの数字が有効な範囲 (1-13) かどうかを返します。
			/// </summary>
			/// <returns>
			/// カードの数字が有効な範囲の場合 true, それ以外の場合は false
			/// </returns>
			constexpr bool isValid() const noexcept
			{
				return InRange(rank, 1, 13) || isJoker();
			}
		};

		/// <summary>
		/// カードの描画用の情報
		/// </summary>
		struct CardInfo
		{
		private:

			static constexpr double corner = 0.045;

			Card m_card;

			Font m_font;

			Vec2 m_cardSize;

			ColorF m_backSideColor;

			double m_frameThickness;

		public:

			/// <summary>
			/// デフォルトコンストラクタ
			/// </summary>
			CardInfo() = default;

			/// <summary>
			/// カードの情報を作成します。
			/// </summary>
			/// <param name="card">
			/// カード
			/// </param>
			/// <param name="font">
			/// 描画に使用するフォント
			/// </param>
			/// <param name="size">
			/// カードの大きさ
			/// </param>
			/// <param name="frameThickness">
			/// 枠の太さ
			/// </param>
			/// <param name="backSideColor">
			/// 裏面の色
			/// </param>
			CardInfo(const Card& card, const Font& font, const Vec2& size, double frameThickness, const ColorF& backSideColor)
				: m_card(card)
				, m_font(font)
				, m_cardSize(size)
				, m_backSideColor(backSideColor)
				, m_frameThickness(frameThickness)
			{
				assert(card.isValid());
			}

			/// <summary>
			/// カードの裏面を描画します。
			/// </summary>
			/// <param name="pos">
			/// カードの左上の座標
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void drawBack(const Vec2& pos) const
			{
				RoundRect(pos, m_cardSize, m_cardSize.x * corner)
					.draw()
					.drawFrame(0.0, m_frameThickness, Palette::Black)
					.rect.stretched(m_cardSize.x * -0.1).draw(m_backSideColor);
			}

			/// <summary>
			/// カードの裏面を描画します。
			/// </summary>
			/// <param name="pos">
			/// カードの左上の座標
			/// </param>
			/// <param name="angle">
			/// カードの時計回りの回転
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void drawBack(const Vec2& pos, double angle) const
			{
				const Transformer2D transformer(Mat3x2::Rotate(angle, pos + m_cardSize / 2));

				drawBack(pos);
			}

			/// <summary>
			/// 中心座標を指定してカードの裏面を描画します。
			/// </summary>
			/// <param name="center">
			/// カードの中心の座標
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void drawBackAt(const Vec2& center) const
			{
				drawBack(center - m_cardSize * 0.5);
			}

			/// <summary>
			/// 中心座標を指定してカードの裏面を描画します。
			/// </summary>
			/// <param name="center">
			/// カードの中心の座標
			/// </param>
			/// <param name="angle">
			/// カードの時計回りの回転
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void drawBackAt(const Vec2& center, double angle) const
			{
				const Transformer2D transformer(Mat3x2::Rotate(angle, center));

				drawBackAt(center);
			}

			/// <summary>
			/// カードを描画します。
			/// </summary>
			/// <param name="pos">
			/// カードの左上の座標
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void draw(const Vec2& pos) const
			{
				if (!m_card.isFaceSide)
				{
					return drawBack(pos);
				}

				struct DrawInfo
				{
					bool flip;

					Vec2 offset;
				};

				static const Array<DrawInfo> drawInfos[9] =
				{
					{	// 2
						DrawInfo{ false, Vec2(0.0,-1.0 / 3.0) },
						DrawInfo{ true, Vec2(0.0,1.0 / 3.0) }
					},

					{	// 3
						DrawInfo{ false, Vec2(0.0,0.0) },
						DrawInfo{ false, Vec2(0.0,-1.0 / 3.0) },
						DrawInfo{ true, Vec2(0.0,1.0 / 3.0) }
					},

					{	// 4
						DrawInfo{ false, Vec2(0.2,-1.0 / 3.0) },
						DrawInfo{ true, Vec2(-0.2,1.0 / 3.0) },
						DrawInfo{ true, Vec2(0.2,1.0 / 3.0) },
						DrawInfo{ false, Vec2(-0.2,-1.0 / 3.0) }
					},

					{	// 5
						DrawInfo{ false, Vec2(0.2,-1.0 / 3.0) },
						DrawInfo{ true, Vec2(-0.2,1.0 / 3.0) },
						DrawInfo{ true, Vec2(0.2,1.0 / 3.0) },
						DrawInfo{ false, Vec2(-0.2,-1.0 / 3.0) },
						DrawInfo{ false, Vec2(0.0,0.0) }
					},

					{	// 5
						DrawInfo{ false, Vec2(-0.2, -1.0 / 3.0) },
						DrawInfo{ false, Vec2(0.2, -1.0 / 3.0) },
						DrawInfo{ false, Vec2(-0.2, 0.0) },
						DrawInfo{ false, Vec2(0.2, 0.0) },
						DrawInfo{ true, Vec2(-0.2, 1.0 / 3.0) },
						DrawInfo{ true, Vec2(0.2, 1.0 / 3.0) },
					},

					{	// 6
						DrawInfo{ false, Vec2(-0.2, -1.0 / 3.0) },
						DrawInfo{ false, Vec2(0.2, -1.0 / 3.0) },
						DrawInfo{ false, Vec2(-0.2, 0.0) },
						DrawInfo{ false, Vec2(0.2, 0.0) },
						DrawInfo{ true, Vec2(-0.2, 1.0 / 3.0) },
						DrawInfo{ true, Vec2(0.2, 1.0 / 3.0) },
						DrawInfo{ false, Vec2(0.0, -1.0 / 6.0) },
					},

					{	// 7
						DrawInfo{ false, Vec2(-0.2, -1.0 / 3.0) },
						DrawInfo{ false, Vec2(0.2, -1.0 / 3.0) },
						DrawInfo{ false, Vec2(-0.2, 0.0) },
						DrawInfo{ false, Vec2(0.2, 0.0) },
						DrawInfo{ true, Vec2(-0.2, 1.0 / 3.0) },
						DrawInfo{ true, Vec2(0.2, 1.0 / 3.0) },
						DrawInfo{ false, Vec2(0.0, -1.0 / 6.0) },
						DrawInfo{ true, Vec2(0.0, 1.0 / 6.0) },
					},

					{	// 8
						DrawInfo{ false, Vec2(-0.2, -1.0 / 3.0) },
						DrawInfo{ false, Vec2(0.2, -1.0 / 3.0) },
						DrawInfo{ true, Vec2(-0.2, 1.0 / 3.0) },
						DrawInfo{ true, Vec2(0.2, 1.0 / 3.0) },
						DrawInfo{ false, Vec2(-0.2, -1.0 / 9.0) },
						DrawInfo{ false, Vec2(0.2, -1.0 / 9.0) },
						DrawInfo{ true, Vec2(-0.2, 1.0 / 9.0) },
						DrawInfo{ true, Vec2(0.2, 1.0 / 9.0) },
						DrawInfo{ false, Vec2(0.0, 0.0) },
					},

					{	// 9
						DrawInfo{ false, Vec2(-0.2, -1.0 / 3.0) },
						DrawInfo{ false, Vec2(0.2, -1.0 / 3.0) },
						DrawInfo{ true, Vec2(-0.2, 1.0 / 3.0) },
						DrawInfo{ true, Vec2(0.2, 1.0 / 3.0) },
						DrawInfo{ false, Vec2(-0.2, -1.0 / 9.0) },
						DrawInfo{ false, Vec2(0.2, -1.0 / 9.0) },
						DrawInfo{ true, Vec2(-0.2, 1.0 / 9.0) },
						DrawInfo{ true, Vec2(0.2, 1.0 / 9.0) },
						DrawInfo{ false, Vec2(0.0, -1.0 / 4.5) },
						DrawInfo{ true, Vec2(0.0, 1.0 / 4.5) }
					},
				};

				const Vec2 center = pos + m_cardSize * 0.5;
				const Vec2 centering = m_cardSize * 0.1;
				const double drawSize = 0.34;
				const ColorF color = m_card.isRed() ? Palette::Red : Palette::Black;

				RoundRect(pos, m_cardSize, m_cardSize.x * corner)
					.draw()
					.drawFrame(0, m_frameThickness, Palette::Black);

				if (m_card.isJoker())
				{
					const Array<Glyph> glyphs = m_font.getGlyphs(L"JOKER");
					const double height = glyphs[0].texture.size.y * drawSize * 1.08;
					const Vec2 drawpos(centering / 10 + Vec2(glyphs[0].texture.resize(Vec2(glyphs[0].texture.size) * drawSize).size.x, height * 0.5));

					for (const auto a : step(glyphs.size()))
					{
						const TextureRegion t = glyphs[a].texture.resize(Vec2(glyphs[0].texture.size) * drawSize);
						t.drawAt(pos + drawpos + Vec2(0, a * height * 1.2), color);
						t.flip().mirror().drawAt(pos - drawpos - Vec2(0, a * height * 1.2) + m_cardSize, color);
					}

					m_font.getGlyph(U'♋').texture.drawAt(center, color);

					return;
				}

				const Glyph suitGlyph = m_font.getGlyph(Card::GetSuit(m_card.suit));
				const Glyph rankGlyph = m_font.getGlyph(Card::GetRank(m_card.rank)[0]);
				const Vec2 suitpos(0.0, m_cardSize.y * 0.13888);
				const double suitSize = drawSize * 1.4;

				suitGlyph.texture.scale(drawSize).drawAt(pos.movedBy(centering + suitpos), color);
				suitGlyph.texture.flip().mirror().scale(drawSize).drawAt(pos + m_cardSize - centering - suitpos, color);

				if (m_card.rank == 10)
				{
					const auto zerotexture = m_font.getGlyph(U'0');
					const Vec2 rankSize = Vec2(rankGlyph.texture.size.x * 2.2 / 3.0, rankGlyph.texture.size.y)* drawSize;

					rankGlyph.texture.resize(rankSize)
						.drawAt(pos + centering - Vec2(rankSize.x * 1.2, 0), color);
					rankGlyph.texture.flip().mirror().resize(rankSize.x / 2, rankSize.y)
						.drawAt(pos + m_cardSize - centering + Vec2(rankSize.x * 1.2, 0), color);

					zerotexture.texture.scale(drawSize*0.8, drawSize)
						.drawAt(pos + centering + Vec2(rankGlyph.texture.size.x * drawSize - rankSize.x / 1.55, 0), color);
					zerotexture.texture.flip().mirror().scale(drawSize*0.8, drawSize)
						.drawAt(pos - centering + Vec2(-rankGlyph.texture.size.x * drawSize + rankSize.x / 1.55, 0) + m_cardSize, color);
				}
				else
				{
					rankGlyph.texture.scale(drawSize).drawAt(pos + centering, color);
					rankGlyph.texture.flip().mirror().scale(drawSize).drawAt(pos + m_cardSize - centering, color);
				}

				const TextureRegion smallSuit = suitGlyph.texture.scale(suitSize);

				if (InRange(m_card.rank, 2, 10))
				{
					for (const auto a : drawInfos[m_card.rank - 2])
					{
						smallSuit.flip(a.flip).drawAt(center.movedBy(m_cardSize.x * a.offset.x, m_cardSize.y * a.offset.y), color);
					}
				}
				else
				{
					const char32_t c[4] = { static_cast<char32_t>(Card::GetSuit(m_card.suit)), U'💂', U'👸', U'👴' };

					m_font.getGlyph(c[(m_card.rank - 1) % 9]).texture.drawAt(center.movedBy(m_card.rank == 13 ? Vec2(0, m_cardSize.y / 12 - m_cardSize.y / 21) : Vec2::Zero()), color);

					if (m_card.isKing())
					{
						m_font.getGlyph(U'👑').texture.scale(0.6).drawAt(center.movedBy(0, -m_cardSize.y / 7 - m_cardSize.y / 21), color);
					}
				}
			}

			/// <summary>
			/// カードを描画します。
			/// </summary>
			/// <param name="pos">
			/// カードの左上の座標
			/// </param>
			/// <param name="angle">
			/// カードの時計回りの回転
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void draw(const Vec2& pos, double angle) const
			{
				const Transformer2D trans(Mat3x2::Rotate(angle, pos + m_cardSize / 2));

				draw(pos);
			}

			/// <summary>
			/// 中心座標を指定してカードを描画します。
			/// </summary>
			/// <param name="center">
			/// カードの中心の座標
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void drawAt(const Vec2& center) const
			{
				draw(center - m_cardSize * 0.5);
			}

			/// <summary>
			/// 中心座標を指定してカードを描画します。
			/// </summary>
			/// <param name="center">
			/// カードの中心の座標
			/// </param>
			/// <param name="angle">
			/// カードの時計回りの回転
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void drawAt(const Vec2& center, double angle) const
			{
				const Transformer2D trans(Mat3x2::Rotate(angle, center));

				draw(center - m_cardSize * 0.5);
			}

			/// <summary>
			/// シンプルなデザインの描画を行います。
			/// </summary>
			/// <param name="pos">
			/// カードの左上の座標
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void drawSimple(const Vec2& pos) const
			{
				if (m_card.isFaceSide)
				{
					const RectF rect(pos, m_cardSize);

					RoundRect(rect, rect.w*corner).draw().drawFrame(m_frameThickness, Palette::Black);

					if (!m_card.isJoker())
					{
						const ColorF color = m_card.isRed() ? Palette::Red : Palette::Black;
						const wchar suit = Card::GetSuit(m_card.suit);
						const String rank = Card::GetRank(m_card.rank);

						m_font(suit).drawAt(pos.movedBy(m_cardSize.x * 0.5, m_cardSize.y * 0.3333), color);
						m_font(rank).drawAt(pos.movedBy(m_cardSize.x * 0.5, m_cardSize.y * 2.0 * 0.3333), color);
					}
					else
					{
						m_font.getGlyph(U'♋').texture.resize(m_cardSize.xx() * 0.90909).drawAt(rect.center(), Palette::Black);
					}
				}
				else
				{
					drawBack(pos);
				}
			}

			/// <summary>
			/// シンプルなデザインの描画を行います。
			/// </summary>
			/// <param name="pos">
			/// カードの左上の座標
			/// </param>
			/// <param name="angle">
			/// カードの時計回りの回転
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void drawSimple(const Vec2& pos, double angle) const
			{
				const Transformer2D trans(Mat3x2::Rotate(angle, pos + m_cardSize / 2));

				drawSimple(pos);
			}

			/// <summary>
			/// 中心座標を指定してシンプルなデザインの描画を行います。
			/// </summary>
			/// <param name="center">
			/// カードの中心の座標
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void drawSimpleAt(const Vec2& center) const
			{
				drawSimple(center - m_cardSize * 0.5);
			}

			/// <summary>
			/// 中心座標を指定してシンプルなデザインの描画を行います。
			/// </summary>
			/// <param name="center">
			/// カードの中心の座標
			/// </param>
			/// <param name="angle">
			/// カードの時計回りの回転
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void drawSimpleAt(const Vec2& center, double angle) const
			{
				const Transformer2D trans(Mat3x2::Rotate(angle, center));

				drawSimple(center - m_cardSize * 0.5);
			}
		};

		/// <summary>
		/// カードに用いるフォントの大きさを計算します。
		/// </summary>
		/// <param name="cardWidth">
		/// カードの幅
		/// </param>
		/// <returns>
		/// カードに用いるフォントの大きさ
		/// </returns>
		constexpr inline int32 CalculateFontSize(double cardWidth) noexcept
		{
			return std::max(static_cast<int32>(cardWidth * 0.666667), 1);
		}

		/// <summary>
		/// カードを作成するクラス
		/// </summary>
		class Pack
		{
		private:

			Font m_font;

			Vec2 m_cardSize = { 0, 0 };

			ColorF m_backSideColor = Palette::Blue;

			double m_framethickness = 0.0;

		public:

			/// <summary>
			/// デフォルトコンストラクタ
			/// </summary>
			Pack() = default;

			/// <summary>
			/// カードを扱うための構造体を作成します。
			/// </summary>
			/// <param name="font">
			/// フォントデータ
			/// </param>
			/// <param name="cardWidth">
			/// カードの幅
			/// </param>
			/// <param name="backSideColor">
			/// カード背面の色
			/// </param>
			/// <param name="frameThickness">
			/// カードの枠の太さ
			/// </param>
			/// <remarks>
			/// フォントの大きさは BestFontSize() を使って計算します。
			/// </remarks>
			explicit Pack(const Font& font, double cardWidth = 50, const ColorF& backSideColor = Palette::Blue, double frameThickness = 1.0)
				: m_font(font)
				, m_cardSize(cardWidth, cardWidth * 1.618)
				, m_backSideColor(backSideColor)
				, m_framethickness(frameThickness) {}

			/// <summary>
			/// カードを扱うための構造体を作成します。
			/// </summary>
			/// <param name="cardWidth">
			/// カードの幅
			/// </param>
			/// <param name="backSideColor">
			/// カード背面の色
			/// </param>
			/// <param name="frameThickness">
			/// カードの枠の太さ
			/// </param>
			explicit Pack(double cardWidth, const ColorF& backSideColor = Palette::Blue, double frameThickness = 1.0)
				: m_font(CalculateFontSize(cardWidth))
				, m_cardSize(cardWidth, cardWidth * 1.618)
				, m_backSideColor(backSideColor)
				, m_framethickness(frameThickness) {}

			/// <summary>
			/// カードの描画用の情報を作成します。
			/// </summary>
			/// <param name="suit">
			/// カードのスート
			/// </param>
			/// <param name="rank">
			/// カードの数字
			/// </param>
			/// <param name="isFaceSide">
			/// カードが表面かどうか
			/// </param>
			/// <returns>
			/// カードの描画用の情報
			/// </returns>
			CardInfo operator ()(Suit suit, int32 rank = 1, bool isFaceSide = Card::Front) const
			{
				return operator()(Card(suit, rank, isFaceSide));
			}

			/// <summary>
			/// カードの描画用の情報を作成します。
			/// </summary>
			/// <param name="card">
			/// カード
			/// </param>
			/// <returns>
			/// カードの描画用の情報
			/// </returns>
			CardInfo operator ()(const Card& card) const
			{
				return CardInfo(card, m_font, m_cardSize, m_framethickness, m_backSideColor);
			}

			/// <summary>
			/// カードの大きさを返します。
			/// </summary>
			/// <returns>
			/// カードの大きさ
			/// </returns>
			Vec2 size() const noexcept
			{
				return m_cardSize;
			}

			/// <summary>
			/// カードの幅を返します。
			/// </summary>
			/// <returns>
			/// カードの幅
			/// </returns>
			double width() const noexcept
			{
				return m_cardSize.x;
			}

			/// <summary>
			/// カードの高さを返します。
			/// </summary>
			/// <returns>
			/// カードの高さ
			/// </returns>
			double height() const noexcept
			{
				return m_cardSize.y;
			}

			/// <summary>
			/// カードの領域を返します。
			/// </summary>
			/// <param name="pos">
			/// カードの左上の座標
			/// </param>
			/// <returns>
			/// カードの領域
			/// </returns>
			RectF region(const Vec2& pos) const
			{
				return RectF(pos, m_cardSize);
			}

			/// <summary>
			/// カードの領域を返します。
			/// </summary>
			/// <param name="pos">
			/// カードの左上の座標
			/// </param>
			/// <param name="angle">
			/// カードの時計回りの回転
			/// </param>
			/// <returns>
			/// カードの領域
			/// </returns>
			Quad region(const Vec2& pos, double angle) const
			{
				return RectF(pos, m_cardSize).rotated(angle);
			}

			/// <summary>
			/// カードの領域を返します。
			/// </summary>
			/// <param name="pos">
			/// カードの中心の座標
			/// </param>
			/// <returns>
			/// カードの領域
			/// </returns>
			RectF regionAt(const Vec2& center) const
			{
				return RectF(Arg::center = center, m_cardSize);
			}

			/// <summary>
			/// カードの領域を返します。
			/// </summary>
			/// <param name="pos">
			/// カードの中心の座標
			/// </param>
			/// <param name="angle">
			/// カードの時計回りの回転
			/// </param>
			/// <returns>
			/// カードの領域
			/// </returns>
			Quad regionAt(const Vec2& center, double angle) const
			{
				return RectF(Arg::center = center, m_cardSize).rotated(angle);
			}
		};

		/// <summary>
		/// カードの山札を作ります。
		/// </summary>
		/// <param name="num_joker">
		/// ジョーカーの枚数
		/// </param>
		/// <param name="isFaceSide">
		/// 各カードの裏表の初期状態
		/// </param>
		/// <remarks>
		/// ジョーカーは配列の最後に加えられます。
		/// シャッフルしたい場合は、取得後に shuffle() します。
		/// </remarks>
		/// <returns>
		/// カードの山札
		/// </returns>
		Array<Card> CreateDeck(size_t num_jokers = 0, bool isFaceSide = Card::Front)
		{
			Array<Card> cards;

			cards.reserve(13 * 4 + num_jokers);

			for (auto suit : step(4))
			{
				for (auto i : step(13))
				{
					cards.emplace_back(static_cast<Suit>(suit), i + 1, isFaceSide);
				}
			}

			cards.insert(cards.end(), num_jokers, Card(Suit::Joker, 0, isFaceSide));

			return cards;
		}
	}
}

/* example

# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Window::Resize(1280, 720);

	Graphics::SetBackground(Palette::Darkgreen);

	const PlayingCard::Pack cardsPack(70, Palette::Red);

	Array<PlayingCard::Card> cards = PlayingCard::CreateDeck(13);

	while (System::Update())
	{
		size_t index = 0;

		for (auto y : step(5))
		{
			for (auto x : step(13))
			{
				const Vec2 pos(50 + 85 * x, 25 + 125 * y);

				if (cardsPack.region(pos).leftClicked())
				{
					cards[index].flip();
				}

				cardsPack(cards[index]).draw(pos);
				
				++index;
			}
		}
	}
}
*/
