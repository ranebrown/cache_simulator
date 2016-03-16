# Cache Simulator

## Important Information
* **Hard Deadline:** 5 pm on Friday, April 29
* traces on eces server `/scratch/arp/ecen4594-sp16`

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
    * `build/` makefile, .o files, executable
    * `report/` latex report
    * `report/images` images used in latex report

## Project Outline

### Memory Structure
* L1 instruction cache
* L1 data cache
  * L2 unified cache (inst. & data)
    * Main Memory

### Input Traces
* stored in gzip format
* use zcat command piped to simulator

### Configuration File
* at runtime a config file is read to specify cache parameters
* cache sizes, bus widths and associativity **always** a power of 2

### Main Memory
* modeled by a constant delay and bandwidth
* in-order processor model i.e. only a single out-standing request to memory system at a time

### Cache Organization
* caches are *write-allocate, write-back*
* 8-entry *victim cache*
* each cache must maintain a LRU (least recently used) replacement policy
