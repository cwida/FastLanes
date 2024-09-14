# issues
example:
```shell
Traceback (most recent call last):
File "__fast_lanes/fls_bi/compress_via_pq.py", line 193, in <module>
compress_all()
File "__fast_lanes/fls_bi/compress_via_pq.py", line 189, in compress_all
compress_all_int()
File "__fast_lanes/fls_bi/compress_via_pq.py", line 181, in compress_all_int
compress(public_bi_dir_path, "Romance", "_1.sample", lambda cur_type: is_int64(cur_type))
File "__fast_lanes/fls_bi/compress_via_pq.py", line 57, in compress
csv_table = csv.read_csv(sed_csv_file_path, parse_options=csv.ParseOptions(delimiter="|"),
File "pyarrow/_csv.pyx", line 956, in pyarrow._csv.read_csv
File "pyarrow/_csv.pyx", line 965, in pyarrow._csv.read_csv
File "pyarrow/error.pxi", line 143, in pyarrow.lib.pyarrow_internal_check_status
File "pyarrow/error.pxi", line 99, in pyarrow.lib.check_status
pyarrow.lib.ArrowInvalid: CSV parse error: Expected 12 columns, got 18: 26655|1|The beauty of |null|1247106805747514379_2759800862|18.465245144746|https://www.instagram ...
```

problem:
```
26655|1|The beauty of |null|1247106805747514379_2759800862|18.465245144746|https://www.instagram.com/p/BFOnQhJjXwL/|-66.113977375825|"Old San Juan Pueto Rico.|caribbean,puertorico,frangipani,traveltuesday,travelpics,romance,oldsanjuanpr,charm,plumeria,oldworld,travelpicsoninstagram,oldsanjuanpuertorico,oldsanjuan|romance|2759800862

Quoted column is not ended with quote.

|"Old San Juan Pueto Rico. ->|Old San Juan Pueto Rico.
```

in:
- Romance
- Euro2016
- Corporations
- HashTags

solution:
