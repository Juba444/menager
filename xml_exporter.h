#ifndef XML_EXPORTER_H
#define XML_EXPORTER_H

#include <QVector>
#include "passwordentry.h"

class XmlExporter
{
public:
    static bool exportToXml(const QVector<PasswordEntry> &entries, const QString &fileName);
};

#endif
