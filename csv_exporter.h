#ifndef CSV_EXPORTER_H
#define CSV_EXPORTER_H

#include "passwordentry.h"
#include <QVector>

class CsvExporter
{
public:
    static bool exportToCsv(const QVector<PasswordEntry> &entries,
                            const QString &fileName);
};

#endif
