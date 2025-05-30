#ifndef FLS_UTL_CPU_INFO_HPP
#define FLS_UTL_CPU_INFO_HPP

#include "fls/utl/cpu/feature.hpp" // for CPUFeature
#include <iosfwd>                  // for string
#include <vector>                  // for vector

namespace fast_lanes {
class CpuInfo {
public:
	CpuInfo(); //
public:
	const std::vector<CPUFeature>& GetAvailFeatures() const;                //
	bool                           HasFeature(CPUFeature feature);          //
	bool                           HasFeature(const std::string& feature);  //
	CPUFeature                     GetBestFeature() const;                  //
	void                           Initialize();                            //
	void                           SetFeature(CPUFeature feature);          //
	void                           SetBestFeature(CPUFeature best_feature); //
public:
	std::vector<CPUFeature> avail_features; //
	CPUFeature              best_feature;   //
};
} // namespace fast_lanes
#endif // FLS_UTL_CPU_INFO_HPP
