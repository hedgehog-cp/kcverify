#include "kcv/domain/verification/damage_formula/attack_power_formula.hpp"

// -----------------------------------------------------------------------------
// 攻撃力式のうちソフトキャップ補正の実装をここに分離する.
// -----------------------------------------------------------------------------

// kcv
#include "kcv/core/constants/ship_attributes.hpp"
#include "kcv/core/context_data.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"

// 長いのでエイリアス.
namespace mod = kcv::modifiers;

auto mod::softcap(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::softcap {
    // if (ctx.既存補正をoff) { return ctx.置換; }

    switch (data.phase) {
        case kcv::phase::sp_midnight:
            return kcv::functions::softcap{.cap = 360};

        case kcv::phase::opening_taisen:
            return kcv::functions::softcap{.cap = 170};

        case kcv::phase::opening_atack:
            return kcv::functions::softcap{.cap = 180};

        case kcv::phase::hougeki:
            return kcv::is_submarine(kcv::get_attacker(data).mst())  //
                     ? kcv::functions::softcap{.cap = 170}
                     : kcv::functions::softcap{.cap = 220};

        case kcv::phase::raigeki:
            return kcv::functions::softcap{.cap = 180};

        case kcv::phase::friendly:
        case kcv::phase::midnight:
            return kcv::functions::softcap{.cap = 360};
    }

    return kcv::functions::softcap::identity();
}