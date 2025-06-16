#include "data/NextiaJD.hpp"
#include "fastlanes.hpp"
#include "fls_tester.hpp"

namespace fastlanes {

#define NEXTIAJD_TEST(DATASET_VAR)                                                                                     \
	TEST_F(FastLanesReaderTester, NextiaJD_##DATASET_VAR) {                                                            \
		const std::vector<n_t> constant_cols {};                                                                       \
		const std::vector<n_t> equal_cols {};                                                                          \
		const std::vector<n_t> one_to_one_mapped_col_indexes {};                                                       \
		AllTest(NextiaJD::DATASET_VAR, constant_cols, equal_cols, one_to_one_mapped_col_indexes);                      \
	}

NEXTIAJD_TEST(COTAHIST_A2009_to_A2019)
NEXTIAJD_TEST(Chicago_Crimes_2001_to_2004)
NEXTIAJD_TEST(Chicago_Crimes_2005_to_2007)
NEXTIAJD_TEST(Chicago_Crimes_2008_to_2011)
NEXTIAJD_TEST(Chicago_Crimes_2012_to_2017)
NEXTIAJD_TEST(Consumer_Complaints)
NEXTIAJD_TEST(Final_comments)
NEXTIAJD_TEST(Homo_sapiens_GRCh38_92)
NEXTIAJD_TEST(Iowa_Liquor_Sales)
NEXTIAJD_TEST(Parking_Violations_Issued_Fiscal_Year_2015)
NEXTIAJD_TEST(Parking_Violations_Issued_Fiscal_Year_2016)
NEXTIAJD_TEST(Parking_Violations_Issued_Fiscal_Year_2017)
NEXTIAJD_TEST(Parking_Violations_Issued__Fiscal_Year_2014__August_2013___June_2014_)
NEXTIAJD_TEST(Reddit_Comments_7M_2019)
NEXTIAJD_TEST(all_anonymized_2015_11_2017_03)
NEXTIAJD_TEST(artists)
NEXTIAJD_TEST(az)
NEXTIAJD_TEST(bgg_13m_reviews)
// NEXTIAJD_TEST(bitcoin_reddit_all)
NEXTIAJD_TEST(business_licences)
NEXTIAJD_TEST(checkouts_by_title)
NEXTIAJD_TEST(chicagoBicycleData)
NEXTIAJD_TEST(comments)
// NEXTIAJD_TEST(comments_negative)
// NEXTIAJD_TEST(comments_positive)
NEXTIAJD_TEST(covid_19_tw)
NEXTIAJD_TEST(econbiz)
NEXTIAJD_TEST(eo2)
NEXTIAJD_TEST(eo3)
NEXTIAJD_TEST(examiner_date_text)
NEXTIAJD_TEST(examiner_date_tokens)
NEXTIAJD_TEST(fhv_tripdata_2019_01)
NEXTIAJD_TEST(freecodecamp_casual_chatroom)
NEXTIAJD_TEST(freecodecamp_casual_chatroom_anon)
NEXTIAJD_TEST(glassdoor_photos)
NEXTIAJD_TEST(hail_2015)
NEXTIAJD_TEST(high_speed_spanish_trains)
NEXTIAJD_TEST(jigsaw_unintended_bias_train_it_clean)
NEXTIAJD_TEST(library_collection_inventory)
NEXTIAJD_TEST(loan)
NEXTIAJD_TEST(news_week_17aug24)
NEXTIAJD_TEST(news_week_18aug24)
NEXTIAJD_TEST(otp)
NEXTIAJD_TEST(plays)
NEXTIAJD_TEST(previous_application)
NEXTIAJD_TEST(property_tax_report)
NEXTIAJD_TEST(question_tags)
NEXTIAJD_TEST(reviews_detailed)
NEXTIAJD_TEST(reviews_summary)
NEXTIAJD_TEST(saudi_hourly_weather_data)
NEXTIAJD_TEST(train_balanced_sarcasm)
NEXTIAJD_TEST(trainView)
NEXTIAJD_TEST(us_perm_visas)
NEXTIAJD_TEST(utterances)
NEXTIAJD_TEST(wowah_data)
NEXTIAJD_TEST(yellow_tripdata_2019_01)

#undef NEXTIAJD_TEST

} // namespace fastlanes
