#ifndef KCVERIFY_CSV_DOCUMENT_HPP_INCLUDED
#define KCVERIFY_CSV_DOCUMENT_HPP_INCLUDED

// std
#include <cassert>
#include <cstddef>
#include <filesystem>
#include <iterator>
#include <ranges>
#include <utility>

// kcv
#include "csv/impl.hpp"
#include "csv/row.hpp"

namespace kcv {
namespace csv {

class document final {
   public:
    // operator--等を定義することでstd::bidirectional_iteratorを満たすことができるが,
    // なぜかマルチパス保証ができないため, std::input_iteratorまでを満たすようにする.
    class iterator final {
       public:
        using iterator_concept = std::input_iterator_tag;
        using difference_type  = std::ptrdiff_t;
        using value_type       = csv::row;
        using reference        = csv::row&;
        using const_reference  = const csv::row&;
        using pointer          = csv::row*;
        using const_pointer    = const csv::row*;

        friend constexpr bool operator==(const iterator& lhs, const iterator& rhs) noexcept {
            return lhs.itr_ == rhs.itr_;
        }

        friend constexpr bool operator!=(const iterator& lhs, const iterator& rhs) noexcept {
            return lhs.itr_ != rhs.itr_;
        }

        friend auto operator++(iterator& itr) -> iterator& {
            ++itr.itr_;
            itr.row_ = value_type{*itr.itr_};
            return itr;
        }

        friend auto operator++(iterator& itr, int) -> iterator {
            auto self = itr;
            ++itr.itr_;
            itr.row_ = value_type{*itr.itr_};
            return itr;
        }

        // std::input_iteratorを満たすためには, 引数をconstで修飾する必要がある.
        // しかし, const vincent_csv::reader::iteratorに対するoperator*が定義されていないため,
        // 非公開メンバ変数row_を用意してそのまま返す.
        friend auto operator*(const iterator& itr) -> const_reference {
            return itr.row_;
        }

        // friend auto operator--(iterator& itr) -> iterator& {
        //     --itr.itr_;
        //     itr.row_ = value_type{*itr.itr_};
        //     return itr;
        // }

        // friend auto operator--(iterator& itr, int) -> iterator {
        //     auto self = itr;
        //     --itr.itr_;
        //     itr.row_ = value_type{*itr.itr_};
        //     return itr;
        // }

        iterator() = default;

        iterator(const vincent_csv::reader::iterator& itr)
            : itr_{itr}
            , row_{*this->itr_} {
        }

        iterator(vincent_csv::reader::iterator&& itr)
            : itr_{std::move(itr)}
            , row_{*this->itr_} {
        }

        // constexpr auto operator->() noexcept -> pointer { return std::addressof(this->row_); }
        // constexpr auto operator->() const noexcept -> const_pointer { return std::addressof(this->row_); }

       private:
        vincent_csv::reader::iterator itr_;
        csv::row row_;
    };

    document(const std::filesystem::path& fname)
        : reader_{fname.c_str()} {
        assert(fname.extension() == ".csv");
    }

    auto begin() -> iterator {
        return iterator{this->reader_.begin()};
    }

    auto end() const -> iterator {
        return iterator{this->reader_.end()};
    }

   private:
    vincent_csv::reader reader_;
};

}  // namespace csv
}  // namespace kcv

static_assert(std::ranges::range<kcv::csv::document>);
static_assert(std::input_iterator<kcv::csv::document::iterator>);

#endif  // KCVERIFY_CSV_DOCUMENT_HPP_INCLUDED
