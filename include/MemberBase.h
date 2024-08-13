#pragma once
#include<iostream>


class Miasto;


class MemberBase {
public:
    MemberBase(const std::string &, float);

    MemberBase(float, float, const std::string &);

    void move_out(const float &size, float move_out_radius);

    virtual ~MemberBase() = default;

    friend std::ostream &operator<<(std::ostream &, MemberBase &);

    float x, y;
    std::string party_name;


    int happines = 0;
protected:

    virtual bool is_in_radius(float, float, float, float, float) = 0;

    virtual bool is_neighbour(MemberBase *, float, float) = 0;
};

