#include "../include/Member.h"
#include <cmath>
#include <iostream>
#include<cmath>


std::ostream &operator<<(std::ostream &out, const Member *m) {
    std::string nazwa = m->party_name;
    out << m->x << " " << m->y << " " << nazwa << std::endl;
    return out;
}

Member::Member(const std::string &name, const float size): MemberBase(name, size) {
}

Member::Member(const float x, const float y, const std::string &name): MemberBase(x, y, name) {
}

Member::~Member() {
    //cout<<"Member o indeksie: "<<Member::index<<" zniknal w nie zbadanych okolicznosciach!!!"<<endl;
}

bool Member::is_neighbour(MemberBase *second, const float radius, const float size) {
    if (this->is_in_radius(Member::x, Member::y, second->x, second->y, radius))
        return true;
    if (this->is_in_radius(Member::x - size, Member::y - size, second->x, second->y, radius))
        return true;
    if (this->is_in_radius(Member::x - size, Member::y + size, second->x, second->y, radius))
        return true;
    if (this->is_in_radius(Member::x + size, Member::y + size, second->x, second->y, radius))
        return true;
    if (this->is_in_radius(Member::x + size, Member::y - size, second->x, second->y, radius))
        return true;

    return false;
}

auto Member::is_in_radius(const float x_1, const float y_1, const float x_2, const float y_2,
                             const float promien) -> bool {
    return std::sqrt((x_1 - x_2) * (x_1 - x_2) + (y_1 - y_2) * (y_1 - y_2)) < promien;
}
