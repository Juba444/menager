#include "csv_exporter.h"

#include <QFile>
#include <QTextStream>

bool CsvExporter::exportToCsv(const QVector<PasswordEntry> &entries,
                              const QString &fileName)
{
    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);

    out << "Portal,Login,Haslo\n";

    for(const PasswordEntry &entry : entries) {
        out << entry.portal << ","
            << entry.login << ","
            << entry.password << "\n";
    }

    file.close();

    return true;
}
