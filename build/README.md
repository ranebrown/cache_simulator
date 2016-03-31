# Makefile Usage
* `make` - compile main executable
* `make run` - run the main executable with default options
    * if files are not already compiled this command will compile them
* run the main executable with a specific configuration file located in `config/` and a trace file (located anywhere)
    * `make run trace=path_to_a_trace conf=path_to_configuration_file`
* `make check` - compile each unit test file as a seperate executable and run them all
    * if the executables are already compiled it will still run the tests
* `make clean` - delete all .o files and all executables located in `build/`
* `make doc` - generate doxygen documentation in html format
