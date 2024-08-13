#include "../include/City.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <map>
#include <random>
#include <ranges>
#include "../helper.h"

#include <string>
#include "fmt/core.h"
#include "fmt/format.h"
#include "fmt/ostream.h"

City::~City() {
    for (const auto member: this->members) {
        delete member;
    }
    members.clear();
    fmt::println("City got destroyed >:D");
}

void City::populate() {
    const auto population_a = static_cast<int>(this->population_count * this->population_ratio);
    const auto population_b = this->population_count - population_a;

    auto name = std::string("A");
    for (auto index = 0; index < population_a; index++) {
        auto member = new Member(name, this->size);
        this->members.push_back(member);
    }

    name = std::string("B");
    for (auto index = 0; index < population_b; index++) {
        auto member = new Member(name, this->size);
        this->members.push_back(member);
    }

    std::mt19937 engine(std::random_device{}());
    std::ranges::shuffle(members, engine);
}


void City::save_and_draw(const std::string &save_file, const std::string &image_file, const int size, const float r) {
    auto sfile = std::fstream(save_file, std::ios::out);
    for (const auto member: members) {
        fmt::println(sfile, "{} {} {}", member->x, member->y, member->party_name);
    }

    this->draw(image_file, size, r);
}


void City::next_generation() {
    long long int happiness_sum = 0;
    for (int index = 0; index < members.size(); index++) {
        if (index % 20) printProgress(1. * index / members.size());

        const auto member1 = members[index];

        // auto iter = std::ranges::views::filter(
        //     std::ranges::subrange(members.begin() + index + 1, members.end()),
        //     [member1, this](auto member2) -> bool {
        //         return member1->czy_sasiaduja(member2, this->check_radius, this->size);
        //     }
        // );
        //
        // for (const auto member2: iter) {
        //     if (member1->nazwa_klubu == member2->nazwa_klubu) {
        //         member1->happines++;
        //         member2->happines++;
        //         continue;
        //     }
        //
        //     member1->happines--;
        //     member2->happines--;
        // }

        for (auto second = index + 1; second < members.size(); second++) {
            const auto member2 = members[second];
            if (!member1->is_neighbour(member2, this->check_radius, this->size)) continue;

            if (member1->party_name == member2->party_name) {
                member1->happines++;
                member2->happines++;
                continue;
            }

            member1->happines--;
            member2->happines--;
        }

        happiness_sum += member1->happines;
    }

    for (auto member: members) {
        if (member->happines < 0) member->move_out(size, move_radius);
        member->happines = 0;
    }

    printProgress(1.);
    fmt::println("\nAverage happiness: {}", happiness_sum / (1. * population_count));
    std::cout << std::endl;
}

void City::read(const std::string &file_name) {
    auto plik = std::fstream(file_name, std::ios::in);
    plik.open(file_name);
    int population = 0;
    float x, y;
    std::string name;
    members.clear();
    std::map<std::string, int> m;

    while (plik >> x >> y >> name) {
        if (x > this->size || x < 0) {
            fmt::println("Error: Bad memeber coordinates");
            exit(-3);
        }
        if (y > this->size || y < 0) {
            fmt::println("Error: Bad memeber coordinates");
            exit(-3);
        }
        auto member = new Member(name, this->size);
        this->members.push_back(member);
        m[name]++;
        population++;
    }
    population_count = population;
    this->population_ratio = m.begin()->second / (population_count * 1.);
    plik.close();
}

void City::draw(const std::string &file_name, const int size, const float r) const {
    fmt::println("\nDrawing process: ");
    auto file = std::fstream(file_name, std::ios::out);
    file << "P3" << std::endl;
    file << size << " " << size << std::endl;
    file << 255 << std::endl;

    const auto v = std::vector(size, 255);

    auto R = std::vector(size, v);
    auto G = std::vector(size, v);
    auto B = std::vector(size, v);

    const float multiplier = (float) size / this->size;

    for (int index = 0; index < population_count; index++) {
        const double procent = index / (1. * population_count);
        const auto member = members[index];
        const int x = std::round((member->x) * (multiplier));
        const int y = std::round((member->y) * (multiplier));

        printProgress(procent * 0.5);
        int w = 1;
        for (int i = -r; i <= r; i++) {
            const auto idx = y + i;
            if (!((idx) > 0 && (idx) < size)) continue;
            for (int k = 0; k < w; k++) {
                auto idx1 = x - k;
                auto idx2 = x + k;
                if (member->party_name == "A") {
                    if (idx1 >= 0) {
                        R[idx][idx1] = 0;
                        G[idx][idx1] = 255;
                        B[idx][idx1] = 0;
                    }
                    if (idx2 < size) {
                        R[idx][idx2] = 0;
                        G[idx][idx2] = 255;
                        B[idx][idx2] = 0;
                    }
                    continue;
                }
                if (idx1 >= 0) {
                    R[idx][idx1] = 255;
                    G[idx][idx1] = 0;
                    B[idx][idx1] = 0;
                }

                if (idx2 < size) {
                    R[idx][idx2] = 255;
                    G[idx][idx2] = 0;
                    B[idx][idx2] = 0;
                }
            }

            w += i >= 0? -1: 1;
        }
    }

    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++) {
            fmt::println(file,"{} {} {}", R[k][i], G[k][i], B[k][i]);
        }
        printProgress(0.5 + 0.5 * i / size);
    }
    printProgress(1.);
    fmt::println("");
}


auto City::get_member(int index) const -> Member * {
    if (index < members.size())
        return members[index];

    fmt::println("Nie ma takiego kibica!");
    exit(-5);
}
