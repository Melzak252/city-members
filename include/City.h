#pragma once

#include <memory>
#include <vector>

#include "Config.h"
#include "Member.h"

class City {
public:
    City(): population_count(10000), check_radius(1), move_radius(1), size(10), population_ratio(0.5) {
    }

    explicit City(const Config &config)
        : population_count(config.population),
          check_radius(config.check_radius),
          move_radius(config.move_radius),
          size(config.size),
          population_ratio(config.ratio) {
    }

    virtual ~City();

    void populate();

    void save_and_draw(const std::string &, const std::string &, const int size, const float r);

    void next_generation();

    void read(const std::string &);

    void draw(const std::string &, int, float) const;

    Member *get_member(int) const;

    int population_count;
    float population_ratio;

    const float check_radius;
    const float move_radius;
    const float size;

    std::vector<Member *> members;
};
