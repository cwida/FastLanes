# Measure single threaded scale factor 1
for i in `seq 1 10`; do for sf in 1; do echo sf: $sf; for threads in 1; do echo "Threads: " $threads;   ./run_tpch 1 ../../data/tpch/sf$sf/ $threads; done; done; done | tee  scalingCRC32_64bit

#Measure scaling with 1,10,20 threads on scale factor 100
for i in `seq 1 10`; do for sf in 100; do echo sf: $sf; for threads in 1 10 20; do echo "Threads: " $threads;   ./run_tpch 1 ../../data/tpch/sf$sf/ $threads; done; done; done | tee -a  scalingCRC32Sf100_64bit

#Measure scaling with 1 thread scale factors 1 3 10 30 100
for i in `seq 1 10`; do for sf in 100 30 10 3 1; do echo sf: $sf; for threads in 1; do echo "Threads: " $threads;   ./run_tpch 1 ../../data/tpch/sf$sf/ $threads; done; done; done | tee -a  scalingCRC32MemStall_64bit

#Measure scaling with 2,4,6,8 threads on scale factor 100
for i in `seq 1 10`; do for sf in 100; do echo sf: $sf; for threads in 2 4 6 8; do echo "Threads: " $threads;   ./run_tpch 1 ../../data/tpch/sf$sf/ $threads; done; done; done | tee -a  scalingCRC32Sf100_64bit
