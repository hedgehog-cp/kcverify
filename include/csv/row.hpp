#ifndef KCVERIFY_CSV_ROW_HPP_INCLUDED
#define KCVERIFY_CSV_ROW_HPP_INCLUDED

// std
#include <cstddef>
#include <string>
#include <utility>

// kcv
#include "csv/field.hpp"

namespace kcv {
namespace csv {

class row final {
   public:
    row() = default;

    row(const vincent_csv::row &row)
        : row_{row} {
    }

    row(vincent_csv::row &&row) noexcept
        : row_{std::move(row)} {
    }

    auto operator[](std::size_t index) const -> field {
        return field{this->row_[index]};
    }

    auto operator[](const std::string &key) const -> field {
        return field{this->row_[key]};
    }

   private:
    vincent_csv::row row_;
};

}  // namespace csv
}  // namespace kcv

#endif  // KCVERIFY_CSV_ROW_HPP_INCLUDED
