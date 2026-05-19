#ifndef PASSWORDSTORAGE_H
#define PASSWORDSTORAGE_H

#include "passwordentry.h"
#include <QVector>

class PasswordStorage
{
public:
    PasswordStorage();

    void load();
    void save();

    void addEntry(const PasswordEntry &entry);
    void updateEntry(int id, const PasswordEntry &entry);
    void deleteEntry(int id);

    QVector<PasswordEntry> getEntries() const;

private:
    QVector<PasswordEntry> entries;
    QString fileName;
};

#endif
