#include "data/public_bi.hpp"
#include "fastlanes.hpp"
#include "test/tester.hpp"

namespace fastlanes {

/* TABLE*/
FLS_TABLE_TEST(public_bi, Arade)
FLS_TABLE_TEST(public_bi, Bimbo)
FLS_TABLE_TEST(public_bi, CityMaxCapita)
FLS_TABLE_TEST(public_bi, CMSprovider)
FLS_TABLE_TEST(public_bi, CommonGovernment)
FLS_TABLE_TEST(public_bi, Corporations)
FLS_TABLE_TEST(public_bi, Eixo)
FLS_TABLE_TEST(public_bi, Euro2016)
FLS_TABLE_TEST(public_bi, Food)
FLS_TABLE_TEST(public_bi, Generico)
FLS_TABLE_TEST(public_bi, HashTags)
FLS_TABLE_TEST(public_bi, Hatred)
FLS_TABLE_TEST(public_bi, IGlocations1)
FLS_TABLE_TEST(public_bi, MLB)
FLS_TABLE_TEST(public_bi, MedPayment1)
FLS_TABLE_TEST(public_bi, Medicare1)
FLS_TABLE_TEST(public_bi, Motos)
FLS_TABLE_TEST(public_bi, MulheresMil)
FLS_TABLE_TEST(public_bi, NYC)
FLS_TABLE_TEST(public_bi, PanCreactomy1)
FLS_TABLE_TEST(public_bi, Physicians)
FLS_TABLE_TEST(public_bi, Provider)
FLS_TABLE_TEST(public_bi, RealEstate1)
FLS_TABLE_TEST(public_bi, Redfin1)
FLS_TABLE_TEST(public_bi, Rentabilidad)
FLS_TABLE_TEST(public_bi, Romance)
FLS_TABLE_TEST(public_bi, SalariesFrance)
FLS_TABLE_TEST(public_bi, TableroSistemaPenal)
FLS_TABLE_TEST(public_bi, Taxpayer)
// FLS_TABLE_TEST(public_bi, Telco) // VERY LONG
FLS_TABLE_TEST(public_bi, TrainsUK1)
FLS_TABLE_TEST(public_bi, TrainsUK2)
FLS_TABLE_TEST(public_bi, USCensus)
FLS_TABLE_TEST(public_bi, Uberlandia)
FLS_TABLE_TEST(public_bi, Wins)
FLS_TABLE_TEST(public_bi, YaleLanguages)

// COL
FLS_COLOUMN_TEST(public_bi, Bimbo, 0)

// EQUALITY PLAN

class PlanTester : public ::testing::Test {
public:
	static void Test(const path& dir_path) {
		Connection fls;
		const path fastlanes_data_path {CMAKE_SOURCE_DIR};
		const path full_dir_path = fastlanes_data_path / dir_path;
		fls.read(full_dir_path).spell(); // NOLINT
	}
};

#define FLS_PLAN_EQUALITY_TEST(DATASET_NAME, TABLE_NAME)                                                               \
	TEST_F(PlanTester, DATASET_NAME##_##TABLE_NAME##_PLANTEST) {                                                       \
		Test(DATASET_NAME::TABLE_NAME);                                                                                \
	};

FLS_PLAN_EQUALITY_TEST(public_bi, Arade)
FLS_PLAN_EQUALITY_TEST(public_bi, Bimbo)
FLS_PLAN_EQUALITY_TEST(public_bi, CityMaxCapita)
FLS_PLAN_EQUALITY_TEST(public_bi, CMSprovider)
FLS_PLAN_EQUALITY_TEST(public_bi, CommonGovernment)
FLS_PLAN_EQUALITY_TEST(public_bi, Corporations)
FLS_PLAN_EQUALITY_TEST(public_bi, Eixo)
FLS_PLAN_EQUALITY_TEST(public_bi, Euro2016)
FLS_PLAN_EQUALITY_TEST(public_bi, Food)
FLS_PLAN_EQUALITY_TEST(public_bi, Generico)
FLS_PLAN_EQUALITY_TEST(public_bi, HashTags)
FLS_PLAN_EQUALITY_TEST(public_bi, Hatred)
FLS_PLAN_EQUALITY_TEST(public_bi, IGlocations1)
FLS_PLAN_EQUALITY_TEST(public_bi, MLB)
FLS_PLAN_EQUALITY_TEST(public_bi, MedPayment1)
FLS_PLAN_EQUALITY_TEST(public_bi, Medicare1)
FLS_PLAN_EQUALITY_TEST(public_bi, Motos)
FLS_PLAN_EQUALITY_TEST(public_bi, MulheresMil)
FLS_PLAN_EQUALITY_TEST(public_bi, NYC)
FLS_PLAN_EQUALITY_TEST(public_bi, PanCreactomy1)
FLS_PLAN_EQUALITY_TEST(public_bi, Physicians)
FLS_PLAN_EQUALITY_TEST(public_bi, Provider)
FLS_PLAN_EQUALITY_TEST(public_bi, RealEstate1)
FLS_PLAN_EQUALITY_TEST(public_bi, Redfin1)
FLS_PLAN_EQUALITY_TEST(public_bi, Rentabilidad)
FLS_PLAN_EQUALITY_TEST(public_bi, Romance)
FLS_PLAN_EQUALITY_TEST(public_bi, SalariesFrance)
FLS_PLAN_EQUALITY_TEST(public_bi, TableroSistemaPenal)
FLS_PLAN_EQUALITY_TEST(public_bi, Taxpayer)
FLS_PLAN_EQUALITY_TEST(public_bi, Telco)
FLS_PLAN_EQUALITY_TEST(public_bi, TrainsUK1)
FLS_PLAN_EQUALITY_TEST(public_bi, TrainsUK2)
FLS_PLAN_EQUALITY_TEST(public_bi, USCensus)
FLS_PLAN_EQUALITY_TEST(public_bi, Uberlandia)
FLS_PLAN_EQUALITY_TEST(public_bi, Wins)
FLS_PLAN_EQUALITY_TEST(public_bi, YaleLanguages)

} // namespace fastlanes