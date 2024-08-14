# city-members

## Project Overview
This project simulates a city with two distinct groups of residents, referred to as members of Party A and Party B. 
The city, initially uninhabited, is populated by members who prefer to live near others from their own party. 
Over time, the residents may relocate to improve their satisfaction, leading to an evolving distribution of the population.

## Features
- **City Creation**: A city of size 𝑚×𝑚 is generated, and residents are placed at random positions.
- **Two Groups**: Residents are divided into two groups, Party A and Party B, each with preferences for their neighbors.
- **Yearly Evolution**: Each year, residents evaluate their satisfaction based on their neighbors and may decide to relocate.
- **Output Files**: The program generates visual representations of the city in PPM format for each year and outputs a population.txt file with the final state of the simulation.

Requirements
C++23: The program is written in C++23, requiring a compatible compiler.
CMake 3.26+: CMake is used for building the project.
fmt Library: The project uses the fmt library for formatting output, fetched automatically via CMake.
Building the Project

To build the project, follow these steps:
1. Clone the repository:
    ```bash
    git clone https://github.com/melzak252/city-members.git
    cd city-members
    ```
2. Create a build directory:

    ```bash
    mkdir build
    cd build
    ```

3. Run CMake:
    ```bash
    cmake ..
    ```

4. Build the project:
    ```bash
    cmake --build .
    ```
This will fetch the necessary dependencies and compile the project.

## Running the Program
After building, you can run the program with the following command:

```bash
./city-members
```
Follow the prompts to input the desired parameters.

### Interactive Mode:
The program will prompt you for the number of residents (N), the number of simulation years (x), ratio of population A to total population.
It will then simulate the city’s evolution, showing the average satisfaction of the residents and their distribution over the years.

### File Input Mode:
You can also load the city's initial state from a file, which should contain the x and y coordinates of the residents and their party affiliation (either "A" for Party A or "B" for Party B).
The program will prompt you for the file name and the number of simulation years (x).

### Output Files:
- **PPM Files**: After each year of simulation, a PPM file representing the city's state is generated. These files can be viewed with any image viewer that supports the PPM format.
- `population.txt`: At the end of the simulation, a population.txt file is created, containing the final positions and affiliations of all residents in the format:
   ```
   x y party_name
   ```


## License
This project is open-source and available under the MIT License. Feel free to modify and distribute it as needed.

## Python Version
A Python implementation of this solution is also available in a separate branch of this repository. To switch to the Python version, use the following commands:

```bash
git checkout python-version
```