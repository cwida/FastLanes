#ifndef ALP_MAPPER_HPP
#define ALP_MAPPER_HPP

#include <chrono>
#include <fcntl.h>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace mapper {

inline double* mmap_file(size_t& n_values, const std::string& filename) {
	double*     file_pointer;
	size_t      file_size;
	struct stat file_stats;

	int fd = ::open(filename.c_str(), O_RDONLY);
	fstat(fd, &file_stats);
	file_size    = file_stats.st_size;
	file_pointer = (double*)mmap(0, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
	n_values     = file_size / sizeof(double);
	return file_pointer;
}

} // namespace mapper

#endif