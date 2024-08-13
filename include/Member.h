#pragma once

#include "MemberBase.h"

class Member : public MemberBase {
public:
    Member(const std::string&, float);

    Member(float, float, const std::string &);

    virtual ~Member();

    friend std::ostream &operator<<(std::ostream &, const Member *);

    bool is_in_radius(float, float, float, float, float) override;

    bool is_neighbour(MemberBase *, float, float) override;



};

