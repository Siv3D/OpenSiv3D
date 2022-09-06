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

		inline constexpr int32 CalculateFontSize(const double cardWidth) noexcept
		{
			return Max(static_cast<int32>(cardWidth * (2.0 / 3.0)), 1);
		}
	}
}
