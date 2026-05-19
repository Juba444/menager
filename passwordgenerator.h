#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <QString>

class PasswordGenerator
{
public:
    static QString generate(int length = 16);
};

#endif
