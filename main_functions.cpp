#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

#include "fmt/core.h"
#include "include/Config.h"
#include "include/City.h"

void random_params(Config &c) {
    float ratio;
    int population_count;
    fmt::print("Insert population count: ");
    std::cin >> population_count;
    if (population_count < 0) {
        fmt::println("Population cannot be negative!");
        exit(-2);
    }

    fmt::print("Insert ratio between population a and b: ");
    std::cin >> ratio;

    if (ratio >= 1. || ratio <= 0.) {
        fmt::println("Error: Ratio has to be in range (0, 1)");
        exit(-2);
    }

    c.population = population_count;
    c.ratio = ratio;
}

void menu(Config &config) {
    char decyzja;
    fmt::println("Populate method: ");
    fmt::println("1 - Random,");
    fmt::println("2 - From file,");
    fmt::println("3 - Exit.");
    std::cin >> decyzja;
    switch (decyzja) {
        case '1':
            random_params(config);
            break;
        case '2': {
            std::string file_name;
            fmt::print("Insert file name: ");
            std::cin >> file_name;

            if (const auto file = std::fstream(file_name, std::ios::in); !file) {
                fmt::println("Error: There is problem with given file: {}", file_name);
                exit(-1);
            }

            config.load_method = load_method::FROM_FILE;
            config.file = file_name;

            break;
        }
        case '3':
            exit(-1);
            break;
        default:
            exit(-2);
            break;
    }
}

void start() {
    auto config = Config();
    menu(config);
    City c(config);
    if (config.load_method == load_method::FROM_FILE) c.read(config.file);
    else c.populate();

    int years;
    fmt::print("Insert number of years: ");
    std::cin >> years;

    if (years <= 0) {
        fmt::println("Number of years should be positive!");
        exit(-3);
    }

    for (int year = 0; year < years; year++) {
        std::string file_name = "Year_" + std::to_string(year) + ".ppm";
        c.save_and_draw("population.txt", file_name, config.drawing_pix_size, config.draw_radius);
        fmt::println("Year: {}", year + 1);
        c.next_generation();
    }
    const std::string file_name = "Year_" + std::to_string(years) + ".ppm";
    c.save_and_draw("population.txt", file_name, config.drawing_pix_size, config.draw_radius);
}
