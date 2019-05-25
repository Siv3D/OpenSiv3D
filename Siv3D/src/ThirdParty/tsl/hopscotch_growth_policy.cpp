
/**
 * MIT License
 *
 * Copyright (c) 2018 Tessil
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

# include <ThirdParty/tsl/hopscotch_growth_policy.h>

namespace tsl::hh
{
	namespace detail {

		static constexpr const std::array<std::size_t, 40> PRIMES = { {
			1ul, 5ul, 17ul, 29ul, 37ul, 53ul, 67ul, 79ul, 97ul, 131ul, 193ul, 257ul, 389ul, 521ul, 769ul, 1031ul,
			1543ul, 2053ul, 3079ul, 6151ul, 12289ul, 24593ul, 49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul, 50331653ul, 100663319ul, 201326611ul,
			402653189ul, 805306457ul, 1610612741ul, 3221225473ul, 4294967291ul
		} };

		template<unsigned int IPrime>
		static constexpr std::size_t mod(std::size_t hash) { return hash % PRIMES[IPrime]; }

		// MOD_PRIME[iprime](hash) returns hash % PRIMES[iprime]. This table allows for faster modulo as the
		// compiler can optimize the modulo code better with a constant known at the compilation.
		static constexpr const std::array<std::size_t(*)(std::size_t), 40> MOD_PRIME = { {
			&mod<0>, &mod<1>, &mod<2>, &mod<3>, &mod<4>, &mod<5>, &mod<6>, &mod<7>, &mod<8>, &mod<9>, &mod<10>,
			&mod<11>, &mod<12>, &mod<13>, &mod<14>, &mod<15>, &mod<16>, &mod<17>, &mod<18>, &mod<19>, &mod<20>,
			&mod<21>, &mod<22>, &mod<23>, &mod<24>, &mod<25>, &mod<26>, &mod<27>, &mod<28>, &mod<29>, &mod<30>,
			&mod<31>, &mod<32>, &mod<33>, &mod<34>, &mod<35>, &mod<36>, &mod<37> , &mod<38>, &mod<39>
		} };

	}

	prime_growth_policy::prime_growth_policy(std::size_t& min_bucket_count_in_out) {

		static_assert(std::numeric_limits<decltype(m_iprime)>::max() >= detail::PRIMES.size(),
			"The type of m_iprime is not big enough.");

		auto it_prime = std::lower_bound(detail::PRIMES.begin(),
			detail::PRIMES.end(), min_bucket_count_in_out);
		if (it_prime == detail::PRIMES.end()) {
			throw std::length_error("The hash table exceeds its maxmimum size.");
		}

		m_iprime = static_cast<unsigned int>(std::distance(detail::PRIMES.begin(), it_prime));
		if (min_bucket_count_in_out > 0) {
			min_bucket_count_in_out = *it_prime;
		}
		else {
			min_bucket_count_in_out = 0;
		}
	}

	std::size_t prime_growth_policy::bucket_for_hash(std::size_t hash) const noexcept {
		return detail::MOD_PRIME[m_iprime](hash);
	}

	std::size_t prime_growth_policy::next_bucket_count() const {
		if (m_iprime + 1 >= detail::PRIMES.size()) {
			throw std::length_error("The hash table exceeds its maxmimum size.");
		}

		return detail::PRIMES[m_iprime + 1];
	}

	std::size_t prime_growth_policy::max_bucket_count() const {
		return detail::PRIMES.back();
	}
}
