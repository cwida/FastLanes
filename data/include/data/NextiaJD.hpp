// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// data/include/data/NextiaJD.hpp
// ────────────────────────────────────────────────────────
#ifndef DATA_NEXTIAJD_HPP
#define DATA_NEXTIAJD_HPP

#include <array>
#include <string_view>

namespace fastlanes {

using nextiajd_dataset_t = std::array<std::pair<std::string_view, std::string_view>, 53>;

// clang-format off
class NextiaJD {
public:
    static constexpr std::string_view COTAHIST_A2009_to_A2019                           { FASTLANES_DATA_DIR "/NextiaJD/tables/COTAHIST_A2009_to_A2019" };                           // NOLINT
    static constexpr std::string_view Chicago_Crimes_2001_to_2004                        { FASTLANES_DATA_DIR "/NextiaJD/tables/Chicago_Crimes_2001_to_2004" };                        // NOLINT
    static constexpr std::string_view Chicago_Crimes_2005_to_2007                        { FASTLANES_DATA_DIR "/NextiaJD/tables/Chicago_Crimes_2005_to_2007" };                        // NOLINT
    static constexpr std::string_view Chicago_Crimes_2008_to_2011                        { FASTLANES_DATA_DIR "/NextiaJD/tables/Chicago_Crimes_2008_to_2011" };                        // NOLINT
    static constexpr std::string_view Chicago_Crimes_2012_to_2017                        { FASTLANES_DATA_DIR "/NextiaJD/tables/Chicago_Crimes_2012_to_2017" };                        // NOLINT
    static constexpr std::string_view Consumer_Complaints                                 { FASTLANES_DATA_DIR "/NextiaJD/tables/Consumer_Complaints" };                                 // NOLINT
    static constexpr std::string_view Final_comments                                      { FASTLANES_DATA_DIR "/NextiaJD/tables/Final_comments" };                                      // NOLINT
    static constexpr std::string_view Homo_sapiens_GRCh38_92                              { FASTLANES_DATA_DIR "/NextiaJD/tables/Homo_sapiens.GRCh38.92" };                              // NOLINT
    static constexpr std::string_view Iowa_Liquor_Sales                                   { FASTLANES_DATA_DIR "/NextiaJD/tables/Iowa_Liquor_Sales" };                                   // NOLINT
    static constexpr std::string_view Parking_Violations_Issued_Fiscal_Year_2015          { FASTLANES_DATA_DIR "/NextiaJD/tables/Parking_Violations_Issued_Fiscal_Year_2015" };          // NOLINT
    static constexpr std::string_view Parking_Violations_Issued_Fiscal_Year_2016          { FASTLANES_DATA_DIR "/NextiaJD/tables/Parking_Violations_Issued_Fiscal_Year_2016" };          // NOLINT
    static constexpr std::string_view Parking_Violations_Issued_Fiscal_Year_2017          { FASTLANES_DATA_DIR "/NextiaJD/tables/Parking_Violations_Issued_Fiscal_Year_2017" };          // NOLINT
    static constexpr std::string_view Parking_Violations_Issued__Fiscal_Year_2014__August_2013___June_2014_
                                                                                         { FASTLANES_DATA_DIR "/NextiaJD/tables/Parking_Violations_Issued__Fiscal_Year_2014__August_2013___June_2014_" }; // NOLINT
    static constexpr std::string_view Reddit_Comments_7M_2019                              { FASTLANES_DATA_DIR "/NextiaJD/tables/Reddit_Comments_7M_2019" };                              // NOLINT
    static constexpr std::string_view all_anonymized_2015_11_2017_03                       { FASTLANES_DATA_DIR "/NextiaJD/tables/all_anonymized_2015_11_2017_03" };                       // NOLINT
    static constexpr std::string_view artists                                             { FASTLANES_DATA_DIR "/NextiaJD/tables/artists" };                                             // NOLINT
    static constexpr std::string_view az                                                  { FASTLANES_DATA_DIR "/NextiaJD/tables/az" };                                                  // NOLINT
    static constexpr std::string_view bgg_13m_reviews                                     { FASTLANES_DATA_DIR "/NextiaJD/tables/bgg-13m-reviews" };                                     // NOLINT
    // static constexpr std::string_view bitcoin_reddit_all                                  { FASTLANES_DATA_DIR "/NextiaJD/tables/bitcoin_reddit_all" };                                  // NOLINT
    static constexpr std::string_view business_licences                                   { FASTLANES_DATA_DIR "/NextiaJD/tables/business-licences" };                                   // NOLINT
    static constexpr std::string_view checkouts_by_title                                  { FASTLANES_DATA_DIR "/NextiaJD/tables/checkouts-by-title" };                                  // NOLINT
    static constexpr std::string_view chicagoBicycleData                                  { FASTLANES_DATA_DIR "/NextiaJD/tables/chicagoBicycleData" };                                  // NOLINT
    static constexpr std::string_view comments                                            { FASTLANES_DATA_DIR "/NextiaJD/tables/comments" };                                            // NOLINT
    // static constexpr std::string_view comments_negative                                   { FASTLANES_DATA_DIR "/NextiaJD/tables/comments_negative" };                                   // NOLINT
    // static constexpr std::string_view comments_positive                                   { FASTLANES_DATA_DIR "/NextiaJD/tables/comments_positive" };                                   // NOLINT
    static constexpr std::string_view covid_19_tw                                         { FASTLANES_DATA_DIR "/NextiaJD/tables/covid-19_tw" };                                         // NOLINT
    static constexpr std::string_view econbiz                                             { FASTLANES_DATA_DIR "/NextiaJD/tables/econbiz" };                                             // NOLINT
    static constexpr std::string_view eo2                                                { FASTLANES_DATA_DIR "/NextiaJD/tables/eo2" };                                                // NOLINT
    static constexpr std::string_view eo3                                                { FASTLANES_DATA_DIR "/NextiaJD/tables/eo3" };                                                // NOLINT
    static constexpr std::string_view examiner_date_text                                  { FASTLANES_DATA_DIR "/NextiaJD/tables/examiner-date-text" };                                  // NOLINT
    static constexpr std::string_view examiner_date_tokens                                { FASTLANES_DATA_DIR "/NextiaJD/tables/examiner-date-tokens" };                                // NOLINT
    static constexpr std::string_view fhv_tripdata_2019_01                                 { FASTLANES_DATA_DIR "/NextiaJD/tables/fhv_tripdata_2019-01" };                                 // NOLINT
    static constexpr std::string_view freecodecamp_casual_chatroom                        { FASTLANES_DATA_DIR "/NextiaJD/tables/freecodecamp_casual_chatroom" };                        // NOLINT
    static constexpr std::string_view freecodecamp_casual_chatroom_anon                   { FASTLANES_DATA_DIR "/NextiaJD/tables/freecodecamp_casual_chatroom_anon" };                   // NOLINT
    static constexpr std::string_view glassdoor_photos                                    { FASTLANES_DATA_DIR "/NextiaJD/tables/glassdoor_photos" };                                    // NOLINT
    static constexpr std::string_view hail_2015                                           { FASTLANES_DATA_DIR "/NextiaJD/tables/hail-2015" };                                           // NOLINT
    static constexpr std::string_view high_speed_spanish_trains                           { FASTLANES_DATA_DIR "/NextiaJD/tables/high_speed_spanish_trains" };                           // NOLINT
    static constexpr std::string_view jigsaw_unintended_bias_train_it_clean               { FASTLANES_DATA_DIR "/NextiaJD/tables/jigsaw-unintended-bias-train_it_clean" };               // NOLINT
    static constexpr std::string_view library_collection_inventory                        { FASTLANES_DATA_DIR "/NextiaJD/tables/library-collection-inventory" };                        // NOLINT
    static constexpr std::string_view loan                                                { FASTLANES_DATA_DIR "/NextiaJD/tables/loan" };                                                // NOLINT
    static constexpr std::string_view news_week_17aug24                                   { FASTLANES_DATA_DIR "/NextiaJD/tables/news-week-17aug24" };                                   // NOLINT
    static constexpr std::string_view news_week_18aug24                                   { FASTLANES_DATA_DIR "/NextiaJD/tables/news-week-18aug24" };                                   // NOLINT
    static constexpr std::string_view otp                                                 { FASTLANES_DATA_DIR "/NextiaJD/tables/otp" };                                                 // NOLINT
    static constexpr std::string_view plays                                               { FASTLANES_DATA_DIR "/NextiaJD/tables/plays" };                                               // NOLINT
    static constexpr std::string_view previous_application                                { FASTLANES_DATA_DIR "/NextiaJD/tables/previous_application" };                                // NOLINT
    static constexpr std::string_view property_tax_report                                 { FASTLANES_DATA_DIR "/NextiaJD/tables/property-tax-report" };                                 // NOLINT
    static constexpr std::string_view question_tags                                       { FASTLANES_DATA_DIR "/NextiaJD/tables/question_tags" };                                       // NOLINT
    static constexpr std::string_view reviews_detailed                                    { FASTLANES_DATA_DIR "/NextiaJD/tables/reviews_detailed" };                                    // NOLINT
    static constexpr std::string_view reviews_summary                                     { FASTLANES_DATA_DIR "/NextiaJD/tables/reviews_summary" };                                     // NOLINT
    static constexpr std::string_view saudi_hourly_weather_data                           { FASTLANES_DATA_DIR "/NextiaJD/tables/saudi-hourly-weather-data" };                           // NOLINT
    static constexpr std::string_view train_balanced_sarcasm                              { FASTLANES_DATA_DIR "/NextiaJD/tables/train-balanced-sarcasm" };                              // NOLINT
    static constexpr std::string_view trainView                                           { FASTLANES_DATA_DIR "/NextiaJD/tables/trainView" };                                           // NOLINT
    static constexpr std::string_view us_perm_visas                                       { FASTLANES_DATA_DIR "/NextiaJD/tables/us_perm_visas" };                                       // NOLINT
    static constexpr std::string_view utterances                                          { FASTLANES_DATA_DIR "/NextiaJD/tables/utterances" };                                          // NOLINT
    static constexpr std::string_view wowah_data                                          { FASTLANES_DATA_DIR "/NextiaJD/tables/wowah_data" };                                          // NOLINT
    static constexpr std::string_view yellow_tripdata_2019_01                              { FASTLANES_DATA_DIR "/NextiaJD/tables/yellow_tripdata_2019-01" };                              // NOLINT

    static constexpr nextiajd_dataset_t dataset = {{
        { "COTAHIST_A2009_to_A2019",                           COTAHIST_A2009_to_A2019 },
        { "Chicago_Crimes_2001_to_2004",                        Chicago_Crimes_2001_to_2004 },
        { "Chicago_Crimes_2005_to_2007",                        Chicago_Crimes_2005_to_2007 },
        { "Chicago_Crimes_2008_to_2011",                        Chicago_Crimes_2008_to_2011 },
        { "Chicago_Crimes_2012_to_2017",                        Chicago_Crimes_2012_to_2017 },
        { "Consumer_Complaints",                                 Consumer_Complaints },
        { "Final_comments",                                      Final_comments },
        { "Homo_sapiens_GRCh38_92",                              Homo_sapiens_GRCh38_92 },
        { "Iowa_Liquor_Sales",                                   Iowa_Liquor_Sales },
        { "Parking_Violations_Issued_Fiscal_Year_2015",          Parking_Violations_Issued_Fiscal_Year_2015 },
        { "Parking_Violations_Issued_Fiscal_Year_2016",          Parking_Violations_Issued_Fiscal_Year_2016 },
        { "Parking_Violations_Issued_Fiscal_Year_2017",          Parking_Violations_Issued_Fiscal_Year_2017 },
        { "Parking_Violations_Issued__Fiscal_Year_2014__August_2013___June_2014_", Parking_Violations_Issued__Fiscal_Year_2014__August_2013___June_2014_ },
        { "Reddit_Comments_7M_2019",                              Reddit_Comments_7M_2019 },
        { "all_anonymized_2015_11_2017_03",                       all_anonymized_2015_11_2017_03 },
        { "artists",                                             artists },
        { "az",                                                  az },
        { "bgg_13m_reviews",                                     bgg_13m_reviews },
        // { "bitcoin_reddit_all",                                  bitcoin_reddit_all },
        { "business_licences",                                   business_licences },
        { "checkouts_by_title",                                  checkouts_by_title },
        { "chicagoBicycleData",                                  chicagoBicycleData },
        { "comments",                                            comments },
        // { "comments_negative",                                   comments_negative },
        // { "comments_positive",                                   comments_positive },
        { "covid_19_tw",                                         covid_19_tw },
        { "econbiz",                                             econbiz },
        { "eo2",                                                eo2 },
        { "eo3",                                                eo3 },
        { "examiner_date_text",                                  examiner_date_text },
        { "examiner_date_tokens",                                examiner_date_tokens },
        { "fhv_tripdata_2019_01",                                 fhv_tripdata_2019_01 },
        { "freecodecamp_casual_chatroom",                        freecodecamp_casual_chatroom },
        { "freecodecamp_casual_chatroom_anon",                   freecodecamp_casual_chatroom_anon },
        { "glassdoor_photos",                                    glassdoor_photos },
        { "hail_2015",                                           hail_2015 },
        { "high_speed_spanish_trains",                           high_speed_spanish_trains },
        { "jigsaw_unintended_bias_train_it_clean",               jigsaw_unintended_bias_train_it_clean },
        { "library_collection_inventory",                        library_collection_inventory },
        { "loan",                                                loan },
        { "news_week_17aug24",                                   news_week_17aug24 },
        { "news_week_18aug24",                                   news_week_18aug24 },
        { "otp",                                                 otp },
        { "plays",                                               plays },
        { "previous_application",                                previous_application },
        { "property_tax_report",                                 property_tax_report },
        { "question_tags",                                       question_tags },
        { "reviews_detailed",                                    reviews_detailed },
        { "reviews_summary",                                     reviews_summary },
        { "saudi_hourly_weather_data",                           saudi_hourly_weather_data },
        { "train_balanced_sarcasm",                              train_balanced_sarcasm },
        { "trainView",                                           trainView },
        { "us_perm_visas",                                       us_perm_visas },
        { "utterances",                                          utterances },
        { "wowah_data",                                          wowah_data },
        { "yellow_tripdata_2019_01",                              yellow_tripdata_2019_01 }
    }};
};
// clang-format on

} // namespace fastlanes

#endif // DATA_NEXTIAJD_HPP
