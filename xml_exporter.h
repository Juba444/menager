#ifndef XML_EXPORTER_H
#define XML_EXPORTER_H

#include "passwordentry.h"
#include <QVector>

class XmlExporter
{
public:
    static bool exportToXml(const QVector<PasswordEntry> &entries,
                            const QString &fileName);
};

#endif
