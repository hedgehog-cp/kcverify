#ifndef KCV_STD_EXT_UTILITY_HPP_INCLUDED
#define KCV_STD_EXT_UTILITY_HPP_INCLUDED

namespace kcv {

template <typename... Ts>
struct overloaded : public Ts... {
    using Ts::operator()...;
};

template <typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

}  // namespace kcv

#endif  // KCV_STD_EXT_UTILITY_HPP_INCLUDED
