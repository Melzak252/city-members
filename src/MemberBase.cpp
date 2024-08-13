#include "../include/Member.h"
#include <iostream>
#include<cmath>
#include<random>
using namespace std;

class Miasto;

ostream &operator<<(ostream &out, MemberBase *m) {
    string nazwa = m->party_name;
    out << m->x << " " << m->y << " " << nazwa << endl;
    return out;
}

MemberBase::MemberBase(const string &nazwa_klubu, float size) {
    std::mt19937 engine(std::random_device{}());
    std::uniform_real_distribution<double> dist(0, size);
    x = dist(engine);
    y = dist(engine);
    MemberBase::party_name = nazwa_klubu;
}

MemberBase::MemberBase(float x, float y, const string &name) {
    MemberBase::x = x;
    MemberBase::y = y;
    MemberBase::party_name = name;
}

void MemberBase::move_out(const float &size, const float move_out_radius = 1.) {
    std::mt19937 engine(std::random_device{}());

    std::uniform_real_distribution<> dist(0, 2 * M_PI);

    const float angle = dist(engine);

    const float dx = move_out_radius * cos(angle);
    const float dy = move_out_radius * sin(angle);
    x += dx;
    y += dy;

    if (x > size) x -= size;
    else if (x < 0) x += size;

    if (y > size) y -= size;
    else if (y < 0) y += size;
}
