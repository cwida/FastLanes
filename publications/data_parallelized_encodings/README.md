# FastLanes
---
We think it is time for a new data format; going beyond Parquet (and ORC). The existing data formats have been very successful and form the basis
of data lakes and lakehouse architectures. Yet, they are 15 years old and very hard to evolve, for various reasons. There are two main reasons to 
evolve them and these form the motivation behind FastLanes:
1. it is possible to provide significantly better compression and better access speeds on current workloads.
2. new workloads have emerged, particularly, data engineering pipelines for machine learning (ML).

In Data Lakes, there is a much reduced role for database design, as there are no database administrators and applications often emerge after data gets
collected. This yields many situations where data ends up being stored in sub-optimal formats. Simple examples are using string datatypes for 
data that is numeric or timestamp (and the majority of data is string), a complex example is redundancy in data, e.g., due to denormalization. 
We think that compression ratio is one area where file formats can be improved. Further, improved access speed can be obtained by letting data
consumers operate on (partly) compressed data. This means that the API of the data format needs to be more flexible.

ML workloads often have very wide tables with many features. These can sometimes be dense high-dimensional floating-point vectors, and other times
be very sparse, such that storing features in maps becomes attractive. Wide and sparse columns using maps and lists get to be more common.
We also think the established (Data Lake) and new (ML) workloads can leverage modern hardware better. On the CPU side, it is critical to use SIMD instructions
effectively. ML pipelines very often run on GPUs, which have less memory and much less cache memory than CPUs, and GPU cores are not efficient on
complex and branchy codecs like general-purpose decompressors (LZ4, zstd). Note that GPUs and SIMD have a lot in common: both excel when there is
(i) a lot of data-parallelism and (ii) absence of branch control-flow.

Some key ideas in FastLanes:
1. a layout design that is highly data-parallel. FastLanes on Intel CPUs can bit-unpack at 60 values per CPU cycle (per core).
2. separation between the logical table format the application expects, and a physical data format in which row-groups get stored.
3. cascading compression "expressions" that achieve very high compression ratios without having to use general-purpose codecs.
4. specific compression schemes for nested data (lists, structs, maps).
5. efficient data-parallel predicate pushdown.
6. read support for compressed vectors (batches), such as FOR-vectors, RLE-vectors, FSST-vectors and DICT-vectors.

FastLanes is still in its early days, but we think we have an excellent foundation. It is open-source and would like to create a vibrant community around it.


## Join Us on Discord
[Join our Discord server!](https://discord.gg/u8wtVRh9)

[![Discord](https://img.shields.io/discord/YOUR_SERVER_ID.svg?label=Join%20Us%20on%20Discord&logo=discord)](https://discord.gg/u8wtVRh9)



## Publications :

1. [The FastLanes Compression Layout:Decoding >100 Billion Integers per Second with Scalar Code](https://www.vldb.org/pvldb/vol16/p2132-afroozeh.pdf)
    - [source code]()
2. [Expression Encoding]()
    - [source code]()
3. [FastLanes on GPU]()
    - [source code](publications/fastlanes_on_gpu)
    

