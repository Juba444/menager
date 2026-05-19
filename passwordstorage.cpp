#include "passwordstorage.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

PasswordStorage::PasswordStorage()
{
    fileName = "passwords.json";
    load();
}

void PasswordStorage::load()
{
    entries.clear();

    QFile file(fileName);

    if(!file.exists())
        return;

    if(!file.open(QIODevice::ReadOnly))
        return;

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();

    for(const QJsonValue &value : array) {
        QJsonObject obj = value.toObject();

        PasswordEntry entry;

        entry.id = obj["id"].toInt();
        entry.portal = obj["portal"].toString();
        entry.login = obj["login"].toString();
        entry.password = obj["password"].toString();


        entries.append(entry);
    }
}

void PasswordStorage::save()
{
    QJsonArray array;

    for(const PasswordEntry &entry : entries) {
        QJsonObject obj;

        obj["id"] = entry.id;
        obj["portal"] = entry.portal;
        obj["login"] = entry.login;
        obj["password"] = entry.password;


        array.append(obj);
    }

    QJsonDocument doc(array);

    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly))
        return;

    file.write(doc.toJson());
    file.close();
}

void PasswordStorage::addEntry(const PasswordEntry &entry)
{
    entries.append(entry);
    save();
}
QVector<PasswordEntry> PasswordStorage::getEntries() const
{
    return entries;
}
void PasswordStorage::deleteEntry(int id)
{
    for(int i = 0; i < entries.size(); i++) {

        if(entries[i].id == id) {
            entries.remove(i);
            break;
        }
    }

    save();
}
void PasswordStorage::updateEntry(int id,
                                  const PasswordEntry &entry)
{
    for(int i = 0; i < entries.size(); i++) {

        if(entries[i].id == id) {
            entries[i] = entry;
            break;
        }
    }

    save();
}
