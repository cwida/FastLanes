
#Measure scaling with 1,2,4,6,8,10,12,14,16,32 threads on scale factor 100
for i in `seq 1 20`; do for sf in 100; do echo sf: $sf; for threads in 1 2 4 6 8 10 12 14 16 32; do echo "Threads: " $threads;   ./run_tpch 1 ../../data/tpch/sf$sf/ $threads; done; done; done | tee -a  scalingCRC32Sf10064bit
