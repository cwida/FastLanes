#ifndef DATA_TIMESERIES_HPP
#define DATA_TIMESERIES_HPP

#include <array>
#include <string_view>

namespace fastlanes {

using timeseries_dataset_t = std::array<std::pair<std::string_view, std::string_view>, 5>;

// clang-format off
class TimeSeries {
public:
    // static constexpr std::string_view AMPds                             { FASTLANES_DATA_DIR "/TimeSeries/tables/AMPds" };                    
    // static constexpr std::string_view WEATHER_FORCAST                   { FASTLANES_DATA_DIR "/TimeSeries/tables/Weather_Forcast" };           
    // static constexpr std::string_view SMART_GRID                        { FASTLANES_DATA_DIR "/TimeSeries/tables/Smart_Gird" };               
    // static constexpr std::string_view LINEAR_ROEAD                      { FASTLANES_DATA_DIR "/TimeSeries/tables/Linear_Road" };               
    // static constexpr std::string_view COMPUTER_MONITOR                  { FASTLANES_DATA_DIR "/TimeSeries/tables/Computer_Monitor" };               

    static constexpr std::string_view AMPds                             { FLS_CMAKE_SOURCE_DIR "/data/time_series/tables/AMPds" };                    
    static constexpr std::string_view WEATHER_FORCAST                   { FLS_CMAKE_SOURCE_DIR "/data/time_series/tables/Weather_Forcast" };           
    static constexpr std::string_view SMART_GRID                        { FLS_CMAKE_SOURCE_DIR "/data/time_series/tables/Smart_Grid" };               
    static constexpr std::string_view LINEAR_ROEAD                      { FLS_CMAKE_SOURCE_DIR "/data/time_series/tables/Linear_Road" };               
    static constexpr std::string_view COMPUTER_MONITOR                  { FLS_CMAKE_SOURCE_DIR "/data/time_series/tables/Computer_Monitor" };    

    static constexpr timeseries_dataset_t dataset = {{
        { "AMPds",                           AMPds },
        { "Weather_Forcast",                 WEATHER_FORCAST },
        { "Smart_Gird",                      SMART_GRID },
        { "Linear_Road",                     LINEAR_ROEAD },
        { "Computer_Monitor",                COMPUTER_MONITOR }
    }};
};
// clang-format on

} // namespace fastlanes

#endif // DATA_TIMESERIES_HPP
