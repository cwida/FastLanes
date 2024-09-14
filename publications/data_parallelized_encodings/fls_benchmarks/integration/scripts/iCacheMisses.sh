for query in `seq 0 11`; do
    echo "Query: " $query
    q=$query ./run_tpch 1000 ../../data/tpch/sf100/ 20 &
    sleep 1
    timeout -s SIGINT 10 perf stat -d -d -p `pidof run_tpch`
    pkill run_tpch
    wait
done 2>&1 | tee iCacheMisses
