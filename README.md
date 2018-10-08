# WDSLib
WDSLib is a C++ library that implements many WDS simulation methods. Currently, a number of solution methods have been implemented: namely the forest-core partitioning algorithm (FCPA), the global gradient algorithm (GGA), and the reformulated co-tree flow method (RCTM)
## Getting Started


### Prerequisites
The WDSLib source code bundles two additional packages, including:
* SuiteSparse(Davisetal.2014)(availablefromhttp://faculty.cse.tamu.edu/davis/suitesparse.html) is a suite of sparse matrix algorithms with exceptional performance, from which the approximated minimum degree permutation (AMD) and the sparse Cholesky decomposition routines have been used; and
* EPANET (available from https://www.epa.gov/water-research/ epanet) part of which is used in WDSLib to parse the network pa- rameter from the EPANET input file.
The source codes of these two additional third-party dependencies have been packaged in WDSLib.
### Installing
WDSLib is built by using CMake, a cross-platform, open-source build system generator, to generate makefiles for different operating systems. In this section, an installation guide for four platforms, namely Windows, Cygwin, Linux, and MacOS is presented.
#### Windows
A binary release of CMake and a C++ compiler, such as visual studio or MinGW, are required for installation on Windows (https://cmake.org/ download/).
* Step 1: After installing the CMake application, input the WDSLib source code directory and the build file directory.
* Step 2: After choosing the source file directory and the build file directory, press the configure button.
* Step 3: After pressing the configure button, Cmake will ask the user to choose a project generator (compiler).
* Step 4: Generate build files using the selected project generator by pressing the generate button.
* Step 5: Open the project solution created by the Cmake and compile the solution.
#### CYGWIN, LINUX, AND MACOS
Two packages, g++ and CMake, are required to build the WDSLib on Cygwin, both of which can be installed via the default Cygwin setup program. For Linux and MacOS, CMake source files can be downloaded from the CMake source distribution website (https://cmake.org/download/). After downloading the source files, the following commands are required to install CMake.

```
./bootstrap
make
make install
```

* Step 1: Change the current directory to the WDSLib build directory using one the following commands that is applicable to the current operating system

```
cd WDSLib-master/Cygwin\ Build/
cd WDSLib-master/Linux\ Build/
cd WDSLib-master/Mac\ Build/
```
* Step 2: Configure and generate makefiles using g++ as the compiler.
```
cmake ../WDSLib-master/
```
* Step 3: compile and install WDSLib using the following command

```
make
```
## Running the tests
A suite of unit tests has been provided to check the validity of the results. These tests can be performed by using the following command:
```
make test
```
Five tests have been used for each of the four WDS solution methods, namely tests for each of: the continuity residuals, the energy residuals, the norm at the final iteration, the infinity norm of the difference between the users final flows and the results, and the infinity norm of the difference between the users final heads and the results.
Please note that the results from these tests are highly dependent on the stopping tolerance selected by the user as any digits less significant than the stopping tolerance will be unreliable.

## Uninstalling WDSLib
WDSLib does not rely on a formal uninstaller to uninstall the package. To uninstall the package, users only need to delete the main WDSLib directory.

## How to use WDSLib
The setup for WDSLib as a standalone application is straightforward. The user provides a human-readable configuration text file that specifies input and output filenames; the name of the solver; the desired output variables; and simulation parameters. The detailed description of the configuration file can be found in User's manual. Hydraulic simulation using WDSLib can be performed by using the following command:
```
./Netsolver config.txt
```

## Authors

* **Mengning Qiu** , **Bradley Alexander** , **Sylvan Elhay** , **Angus R. Simpson** - *Initial work* -(https://github.com/a1184182)


## License

This project is licensed under the GNU LESSER GENERAL PUBLIC LICENS - see the [LICENSE.md](LICENSE.md) file for details

