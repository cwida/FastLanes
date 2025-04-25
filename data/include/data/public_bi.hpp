#ifndef DATA_PUBLIC_BI_HPP
#define DATA_PUBLIC_BI_HPP

#include "fls/std/string.hpp"
#include <array>

namespace fastlanes {
using public_bi_dataset_t = std::array<std::pair<string_view, string_view>, 36>;

// clang-format off
class public_bi {
public:
    // Define all the string_view constants for paths
	static constexpr string_view Arade {FASTLANES_DATA_DIR "/public_bi/tables/Arade/Arade_1"}; //NOLINT
	static constexpr string_view Bimbo {FASTLANES_DATA_DIR "/public_bi/tables/Bimbo/Bimbo_1"}; //NOLINT
	static constexpr string_view CMSprovider {FASTLANES_DATA_DIR "/public_bi/tables/CMSprovider/CMSprovider_1"}; //NOLINT
	static constexpr string_view CityMaxCapita {FASTLANES_DATA_DIR "/public_bi/tables/CityMaxCapita/CityMaxCapita_1"}; //NOLINT
	static constexpr string_view CommonGovernment {FASTLANES_DATA_DIR "/public_bi/tables/CommonGovernment/CommonGovernment_1"}; //NOLINT
	static constexpr string_view Corporations {FASTLANES_DATA_DIR "/public_bi/tables/Corporations/Corporations_1"}; //NOLINT
	static constexpr string_view Eixo {FASTLANES_DATA_DIR "/public_bi/tables/Eixo/Eixo_1"}; //NOLINT
	static constexpr string_view Euro2016 {FASTLANES_DATA_DIR "/public_bi/tables/Euro2016/Euro2016_1"}; //NOLINT
	static constexpr string_view Food {FASTLANES_DATA_DIR "/public_bi/tables/Food/Food_1"}; //NOLINT
	static constexpr string_view Generico {FASTLANES_DATA_DIR "/public_bi/tables/Generico/Generico_1"}; //NOLINT
	static constexpr string_view HashTags {FASTLANES_DATA_DIR "/public_bi/tables/HashTags/HashTags_1"}; //NOLINT
	static constexpr string_view Hatred {FASTLANES_DATA_DIR "/public_bi/tables/Hatred/Hatred_1"}; //NOLINT
	static constexpr string_view IGlocations1 {FASTLANES_DATA_DIR "/public_bi/tables/IGlocations1/IGlocations1_1"}; //NOLINT
	static constexpr string_view MLB {FASTLANES_DATA_DIR "/public_bi/tables/MLB/MLB_1"}; //NOLINT
	static constexpr string_view MedPayment1 {FASTLANES_DATA_DIR "/public_bi/tables/MedPayment1/MedPayment1_1"}; //NOLINT
	static constexpr string_view Medicare1 {FASTLANES_DATA_DIR "/public_bi/tables/Medicare1/Medicare1_1"}; //NOLINT
	static constexpr string_view Motos {FASTLANES_DATA_DIR "/public_bi/tables/Motos/Motos_1"}; //NOLINT
	static constexpr string_view MulheresMil {FASTLANES_DATA_DIR "/public_bi/tables/MulheresMil/MulheresMil_1"}; //NOLINT
	static constexpr string_view NYC {FASTLANES_DATA_DIR "/public_bi/tables/NYC/NYC_1"}; //NOLINT
	static constexpr string_view PanCreactomy1 {FASTLANES_DATA_DIR "/public_bi/tables/PanCreactomy1/PanCreactomy1_1"}; //NOLINT
	static constexpr string_view Physicians {FASTLANES_DATA_DIR "/public_bi/tables/Physicians/Physicians_1"}; //NOLINT
	static constexpr string_view Provider {FASTLANES_DATA_DIR "/public_bi/tables/Provider/Provider_1"}; //NOLINT
	static constexpr string_view RealEstate1 {FASTLANES_DATA_DIR "/public_bi/tables/RealEstate1/RealEstate1_1"}; //NOLINT
	static constexpr string_view Redfin1 {FASTLANES_DATA_DIR "/public_bi/tables/Redfin1/Redfin1_1"}; //NOLINT
	static constexpr string_view Rentabilidad {FASTLANES_DATA_DIR "/public_bi/tables/Rentabilidad/Rentabilidad_1"}; //NOLINT
	static constexpr string_view Romance {FASTLANES_DATA_DIR "/public_bi/tables/Romance/Romance_1"}; //NOLINT
	static constexpr string_view SalariesFrance {FASTLANES_DATA_DIR "/public_bi/tables/SalariesFrance/SalariesFrance_1"}; //NOLINT
	static constexpr string_view TableroSistemaPenal {FASTLANES_DATA_DIR "/public_bi/tables/TableroSistemaPenal/TableroSistemaPenal_1"}; //NOLINT
	static constexpr string_view Taxpayer {FASTLANES_DATA_DIR "/public_bi/tables/Taxpayer/Taxpayer_1"}; //NOLINT
	static constexpr string_view Telco {FASTLANES_DATA_DIR "/public_bi/tables/Telco/Telco_1"}; //NOLINT
	static constexpr string_view TrainsUK1 {FASTLANES_DATA_DIR "/public_bi/tables/TrainsUK1/TrainsUK1_2"}; //NOLINT
	static constexpr string_view TrainsUK2 {FASTLANES_DATA_DIR "/public_bi/tables/TrainsUK2/TrainsUK2_1"}; //NOLINT
	static constexpr string_view USCensus {FASTLANES_DATA_DIR "/public_bi/tables/USCensus/USCensus_1"}; //NOLINT
	static constexpr string_view Uberlandia {FASTLANES_DATA_DIR "/public_bi/tables/Uberlandia/Uberlandia_1"}; //NOLINT
	static constexpr string_view Wins {FASTLANES_DATA_DIR "/public_bi/tables/Wins/Wins_1"}; //NOLINT
	static constexpr string_view YaleLanguages {FASTLANES_DATA_DIR "/public_bi/tables/YaleLanguages/YaleLanguages_1"}; //NOLINT

	static constexpr public_bi_dataset_t dataset = {{
		{"Arade", Arade},
		{"Bimbo", Bimbo},
		{"CMSprovider", CMSprovider},
		{"CityMaxCapita", CityMaxCapita},
		{"CommonGovernment", CommonGovernment},
		{"Corporations", Corporations},
		{"Eixo", Eixo},
		{"Euro2016", Euro2016},
		{"Food", Food},
		{"Generico", Generico},
		{"HashTags", HashTags},
		{"Hatred", Hatred},
		{"IGlocations1", IGlocations1},
		{"MLB", MLB},
		{"MedPayment1", MedPayment1},
		{"Medicare1", Medicare1},
		{"Motos", Motos},
		{"MulheresMil", MulheresMil},
		{"NYC", NYC},
		{"PanCreactomy1", PanCreactomy1},
		{"Physicians", Physicians},
		{"Provider", Provider},
		{"RealEstate1", RealEstate1},
		{"Redfin1", Redfin1},
		{"Rentabilidad", Rentabilidad},
		{"Romance", Romance},
		{"SalariesFrance", SalariesFrance},
		{"TableroSistemaPenal", TableroSistemaPenal},
		{"Taxpayer", Taxpayer},
		{"Telco", Telco},
		{"TrainsUK1", TrainsUK1},
		{"TrainsUK2", TrainsUK2},
		{"USCensus", USCensus},
		{"Uberlandia", Uberlandia},
		{"Wins", Wins},
		{"YaleLanguages", YaleLanguages}
	}};
};
// clang-format on
} // namespace fastlanes

#endif // DATA_PUBLIC_BI_HPP
