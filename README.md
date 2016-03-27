# Cache Simulator

## Important Information
* **Hard Deadline:** 5 pm on Friday, April 29
* traces on eces server `/scratch/arp/ecen4593-sp16`
* **data types:** - very important - signed, unsigned, long int, long long int, etc.
    * any timing statistic - unsigned long long
    * use correct printf format specifier e.g. %llu or %Lu

## Setup
1. tab size 4
2. spaces rather than hard tabs - avoids alignment issues
3. report written in latex
3. each function has its own file and header
3. functions documented in doxygen style

    ```C
     /**
      * @brief function description
      * @param[in] x input variable description
      * @param[in,out] y input and output variable description
      * @param[out] z output variable description
      * @return return value description
      */
     ```
3. directory structure
    * `src/` source files
    * `inc/` header files
    * `build/` makefile, .o files, executable, config file
    * `test/` unit test files - uses check framework
    * `sim_results/` all txt files of simulation results - folder is ignored for now
    * `config/` contains configuration files used to specify cache memory parameters at runtime
    * `trace_short/` gzipped short traces tr1 through tr6
    * `report/` latex report
    * `report/images` images used in latex report (and any other images e.g. for wiki)
1. makefile commands
    * `make` - compile main executable
    * `make run` - run the main executable with default options
    * run the main executable with a specific configuration file located in `config/` and a trace file (located anywhere)
        * `make run trace=path_to_a_trace conf=configuration_filename`
    * `make check` - compile each unit test file as a seperate executable and run them all

## Project Outline

### Memory Structure
* L1 instruction cache
* L1 data cache
  * L2 unified cache (inst. & data)
    * Main Memory

### Input Traces
* stored in gzip format
* use zcat command piped to simulator
    * `zcat trace_name.gz | ./executable config_file`
    * on OSX may be necessary to use `zcat < trace_name.gz`

### Configuration File
* at runtime a config file is read to specify cache and memory parameters
* config file should be a command line argument
* if no config file is given then default paramaters should be used
* cache sizes, bus widths and associativity **always** a power of 2

### Main Memory
* modeled by a constant delay and bandwidth
* in-order processor model i.e. only a single out-standing request to memory system at a time

### Cache Organization
* caches are *write-allocate, write-back*
* 8-entry *victim cache*
* each cache must maintain a LRU (least recently used) replacement policy
    * the least recently used item is discarded first
* cache lines are marked as "dirty" if the program has written to that cache entry
* on a miss the cache's victim cache is checked before going to the next level or main memory
    * the victim cache is an 8 deep LRU stack
    * if the line is available in the victim cache it is moved to the top of the victim cache stack
    * the line being removed from the cache is then swapped with the entry at the top of the victim cache
* if the miss is not available in the victim cache
    * the entry at the bottom of the victim cache is checked to see if it is "dirty"
    * if the entry is "dirty" then it is *written back* to the next level of the hierarchy
        * the line is written as "dirty" in the level the line is moved to
    * that line is then moved to the top of the victim cache and overwritten with the line being removed from the cache
        * this is the *write-allocate* portion where room is made in the cache for the new line
    * the new line is then brought into the cache
* a write request only causes the line to be "dirty" on the level that sees the write
* after a cache miss
    * the miss penalty is added to the execution time
    * it is necessary to account for the time of adding a new block into the cache
        * this is done by adding the hit time of the cache level to the total execution time

### Program Trace Information
* the input traces are a sequence of records that contain reference information
* format
    * Reference type: instruction, data read, data write
    * Address: memory address in hex - up to 64 bits
    * Number of bytes: the number of bytes referenced by the request
* inst. and data references can fall on any byte boundry -> variable size
* an instruction or data reference may generate multiple references to the first-level caches
    * there is a 4-byte bus between the processor and the L1 caches
    * all references to the L1 caches look like they are aligned on 4-byte boundaries
    * the L1 cache returns ad 4-byte value
* available traces
    * testing traces: tr1-tr6
    * testing traces: parts of the production traces
    * production traces: 6 straces

### Program Output
* output statistics - see example
* might want to do post-processing of data for plotting
* debugging info that could be printed: valid, dirty, and tag information

### Evaluation
* Execution time
    * inst. takes 1 cycle
    * inst. fetch 1 cycle
    * data fetch 1 cycle (for each reference)
    * **note:** memory references are not aligned - multiple cache accesses possible
    * total execution time = 1 cycle per inst. + simulated time to access memory hierarchy + 1 * num data refs
* Cost
    * L1 cache
        * $100 per 4KB
        * $100 for each doubling of a associativity beyond direct=mapped
        * cost for doubling the associativity is per 4KB (combined costs are multiplied)
    * L2 cache
        * $50 per 16KB
        * $50 per doubling of associativity
    * Main Memory
        * $200 to decrease latency by factor of 2
        * $100 to increase bandwidth by factor of 2
        * base setup - latency 50 costs $50 + 8-byte bandwidth 25 = $75
    * program should compute cost based on the memory configuration specified

### Memory System Configurations
* Default
    * 8KB direct-mapped Icache, 8KB direct-mapped Dcache, with a unified 32KB direct- mapped Level-2 cache
* L1-2way
    * 8KB two-way set associative Icache, 8KB two-way set associative Dcache, with a uni- fied 32KB direct-mapped Level-2 cache
* All-2way
    * 8KB two-way set associative Icache, 8KB two-way set associative Dcache, with a uni- fied 32KB two-way set associative Level-2 cache
* All-4way
    * 8KB four-way set associative Icache, 8KB four-way set associative Dcache, with a unified 32KB four-way set associative Level-2 cache
* L1-8way
    * 8KB eight-way set associative Icache, 8KB eight-way set associative Dcache, with a unified 32KB direct-mapped Level-2 cache
* L1-small
    * 4KB direct-mapped Icache, 4KB direct-mapped Dcache, with a unified 32KB direct- mapped Level-2 cache
* L1-small-4way
    * 4KB 4-way set associative Icache, 4KB 4-way set associative Dcache, with a unified 32KB direct-mapped Level-2 cache
* All-small
    * 4KB direct-mapped Icache, 4KB direct-mapped Dcache, with a unified 16KB direct- mapped Level-2 cache
* All-FA
    * Fully Associative 8KB Icache, 8KB Dcache, and 32KB Level-2 cache

## Deliverables
1. printouts of simulator code
1. outputs of simulations
    1. 6 production traces * 9 memory configurations = 54 total
1. plots of all simulation results
1. commentary on simulation results - "several pages"
1. Additional simulation - sjeng trace only
    1. use default config
    1. run simulations increasing main memory bandwidth by powrs of 2
    1. run for 8, 16, 32, 64
    1. create plots of performance vs. cost
    1. discuss best main memory system model
    1. discuss effects of bandwidth on overall system performance
1. submit hard copy of report
1. submit cd or usb of code and simulation results
