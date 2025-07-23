#ifndef KCVERIFY_EXTENSIONS_UTILITY_HPP_INCLUDED
#define KCVERIFY_EXTENSIONS_UTILITY_HPP_INCLUDED

namespace kcv {

template <typename... Ts>
struct overload : public Ts... {
    using Ts::operator()...;
};

template <typename... Ts>
overload(Ts...) -> overload<Ts...>;

}  // namespace kcv

#endif  // KCVERIFY_EXTENSIONS_UTILITY_HPP_INCLUDED
