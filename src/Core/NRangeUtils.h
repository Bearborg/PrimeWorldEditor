#ifndef CORE_NRANGEUTILS_H
#define CORE_NRANGEUTILS_H

#include <ranges>

namespace Utils
{

// TODO: Can be replaced with std::views::enumerate once Clang implements this
template <std::ranges::input_range Range>
auto enumerate(Range&& range)
{
    return std::views::zip(std::views::iota(size_t{0}), std::forward<Range>(range));
}

} // namespace Utils

#endif // CORE_NRANGEUTILS_H
