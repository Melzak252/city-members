#pragma once

#include<string>

namespace load_method {
    enum LoadPopulation {
        RANDOM,
        FROM_FILE
    };
}

class Config final {
public:
    float size = 25.;
    int population = 10000;
    float ratio = 0.5;
    float check_radius = 1.;
    float move_radius = 1.;
    float draw_radius = 2;
    int drawing_pix_size = 1000;
    load_method::LoadPopulation load_method = load_method::RANDOM;
    std::string file;
};
