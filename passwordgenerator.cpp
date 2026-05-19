#include "passwordgenerator.h"
#include <QRandomGenerator>

QString PasswordGenerator::generate(int length)
{
    QString chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%^&*";

    QString password;

    for(int i = 0; i < length; i++) {
        int index = QRandomGenerator::global()->bounded(chars.length());
        password.append(chars[index]);
    }

    return password;
}
