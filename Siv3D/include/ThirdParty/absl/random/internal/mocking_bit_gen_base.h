//
// Copyright 2018 The Abseil Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef ABSL_RANDOM_INTERNAL_MOCKING_BIT_GEN_BASE_H_
#define ABSL_RANDOM_INTERNAL_MOCKING_BIT_GEN_BASE_H_

#include <atomic>
#include <deque>
#include <string>
#include <typeinfo>

#include "absl/random/random.h"
#include "absl/strings/str_cat.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace random_internal {

// MockingBitGenExpectationFormatter is invoked to format unsatisfied mocks
// and remaining results into a description string.
template <typename DistrT, typename FormatT>
struct MockingBitGenExpectationFormatter {
  std::string operator()(absl::string_view args) {
    return absl::StrCat(FormatT::FunctionName(), "(", args, ")");
  }
};

// MockingBitGenCallFormatter is invoked to format each distribution call
// into a description string for the mock log.
template <typename DistrT, typename FormatT>
struct MockingBitGenCallFormatter {
  std::string operator()(const DistrT& dist,
                         const typename DistrT::result_type& result) {
    return absl::StrCat(
        FormatT::FunctionName(), "(", FormatT::FormatArgs(dist), ") => {",
        FormatT::FormatResults(absl::MakeSpan(&result, 1)), "}");
  }
};

class MockingBitGenBase {
  template <typename>
  friend struct DistributionCaller;
  using generator_type = absl::BitGen;

 public:
  // URBG interface
  using result_type = generator_type::result_type;
  static constexpr result_type(min)() { return (generator_type::min)(); }
  static constexpr result_type(max)() { return (generator_type::max)(); }
  result_type operator()() { return gen_(); }

  MockingBitGenBase() : gen_(), observed_call_log_() {}
  virtual ~MockingBitGenBase() = default;

 protected:
  const std::deque<std::string>& observed_call_log() {
    return observed_call_log_;
  }

  // CallImpl is the type-erased virtual dispatch.
  // The type of dist is always distribution<T>,
  // The type of result is always distribution<T>::result_type.
  virtual bool CallImpl(const std::type_info& distr_type, void* dist_args,
                        void* result) = 0;

  template <typename DistrT, typename ArgTupleT>
  static const std::type_info& GetTypeId() {
    return typeid(std::pair<absl::decay_t<DistrT>, absl::decay_t<ArgTupleT>>);
  }

  // Call the generating distribution function.
  // Invoked by DistributionCaller<>::Call<DistT, FormatT>.
  // DistT is the distribution type.
  // FormatT is the distribution formatter traits type.
  template <typename DistrT, typename FormatT, typename... Args>
  typename DistrT::result_type Call(Args&&... args) {
    using distr_result_type = typename DistrT::result_type;
    using ArgTupleT = std::tuple<absl::decay_t<Args>...>;

    ArgTupleT arg_tuple(std::forward<Args>(args)...);
    auto dist = absl::make_from_tuple<DistrT>(arg_tuple);

    distr_result_type result{};
    bool found_match =
        CallImpl(GetTypeId<DistrT, ArgTupleT>(), &arg_tuple, &result);

    if (!found_match) {
      result = dist(gen_);
    }

    // TODO(asoffer): Forwarding the args through means we no longer need to
    // extract them from the from the distribution in formatter traits. We can
    // just StrJoin them.
    observed_call_log_.push_back(
        MockingBitGenCallFormatter<DistrT, FormatT>{}(dist, result));
    return result;
  }

 private:
  generator_type gen_;
  std::deque<std::string> observed_call_log_;
};  // namespace random_internal

}  // namespace random_internal
ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_RANDOM_INTERNAL_MOCKING_BIT_GEN_BASE_H_
