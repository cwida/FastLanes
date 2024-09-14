/*
-- DATE : 28/01/2024
-- FILE_PATH : test/include/plans/public_bi/arade_1_plan.hpp
-- PROJECT_NAME : fastlanes_fileformat
*/

#ifndef ARADE_1_PLAN_HPP
#define ARADE_1_PLAN_HPP

namespace Arade_1_tab {
inline fastlanes::SimplePlan plan {{
    fastlanes::Scheme {fastlanes::SchemeType::DICT_1T1},
    fastlanes::Scheme {fastlanes::SchemeType::DICT_1T1},
    fastlanes::Scheme {fastlanes::SchemeType::NONE},
    fastlanes::Scheme {fastlanes::SchemeType::NONE},
    fastlanes::Scheme {fastlanes::SchemeType::NONE},
    fastlanes::Scheme {fastlanes::SchemeType::NONE},
    fastlanes::Scheme {fastlanes::SchemeType::NONE},
    fastlanes::Scheme {fastlanes::SchemeType::NONE},
    fastlanes::Scheme {fastlanes::SchemeType::NONE},
    fastlanes::Scheme {fastlanes::SchemeType::NONE}, //
}};
}

#endif // ARADE_1_PLAN_HPP
