#ifndef EURO2016_1_PLAN_HPP
#define EURO2016_1_PLAN_HPP

namespace Euro2016_1_tab {
inline fastlanes::SimplePlan plan {{
    fastlanes::Scheme {fastlanes::SchemeType::NONE},
    fastlanes::Scheme {fastlanes::SchemeType::NONE},
    fastlanes::Scheme {fastlanes::SchemeType::NONE}, // Dict_1toN,
    fastlanes::Scheme {fastlanes::SchemeType::EQUALITY},
    fastlanes::Scheme {fastlanes::SchemeType::EQUALITY},
    fastlanes::Scheme {fastlanes::SchemeType::EQUALITY},
    fastlanes::Scheme {fastlanes::SchemeType::NONE},
    fastlanes::Scheme {fastlanes::SchemeType::NONE}, // Dict_1toN,
    fastlanes::Scheme {fastlanes::SchemeType::NONE},
    fastlanes::Scheme {fastlanes::SchemeType::EQUALITY},
}};
} // namespace Euro2016_1_tab

#endif // EURO2016_1_PLAN_HPP
