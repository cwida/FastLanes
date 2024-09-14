#include "data/NextiaJD.hpp"
#include "fastlanes.hpp"
#include "test/tester.hpp"

namespace fastlanes {

// To run FLS compression, uncomment all lines in src/cor/exp_pool.cpp
// To run UNCOMPRESSED, comment everything apart from UNCOMPRESSED (sometimes with BYTE_ARR)
FLS_TABLE_TEST(NextiaJD, Chicago_Crimes_2001_to_2004)
FLS_TABLE_TEST(NextiaJD, Chicago_Crimes_2005_to_2007)
FLS_TABLE_TEST(NextiaJD, Chicago_Crimes_2012_to_2017)
FLS_TABLE_TEST(NextiaJD, Consumer_Complaints)
FLS_TABLE_TEST(NextiaJD, Homo_sapiens_GRCh38_92)
FLS_TABLE_TEST(NextiaJD, all_anonymized_2015_11_2017_03)
FLS_TABLE_TEST(NextiaJD, artists)
FLS_TABLE_TEST(NextiaJD, az)
FLS_TABLE_TEST(NextiaJD, business_licences)
FLS_TABLE_TEST(NextiaJD, comments)
FLS_TABLE_TEST(NextiaJD, econbiz)
FLS_TABLE_TEST(NextiaJD, eo2)
FLS_TABLE_TEST(NextiaJD, eo3)
FLS_TABLE_TEST(NextiaJD, examiner_date_text)
FLS_TABLE_TEST(NextiaJD, examiner_date_tokens)
FLS_TABLE_TEST(NextiaJD, glassdoor_photos)
FLS_TABLE_TEST(NextiaJD, news_week_17aug24)
FLS_TABLE_TEST(NextiaJD, otp)
FLS_TABLE_TEST(NextiaJD, plays)
FLS_TABLE_TEST(NextiaJD, previous_application)
FLS_TABLE_TEST(NextiaJD, property_tax_report)
FLS_TABLE_TEST(NextiaJD, reviews_detailed)
FLS_TABLE_TEST(NextiaJD, reviews_summary)
FLS_TABLE_TEST(NextiaJD, saudi_hourly_weather_data)
FLS_TABLE_TEST(NextiaJD, train_balanced_sarcasm)
FLS_TABLE_TEST(NextiaJD, trainView)
FLS_TABLE_TEST(NextiaJD, us_perm_visas)
FLS_TABLE_TEST(NextiaJD, wowah_data)
FLS_TABLE_TEST(NextiaJD, yellow_tripdata_2019_01)

} // namespace fastlanes