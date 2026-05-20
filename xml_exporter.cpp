#include "xml_exporter.h"

#include <QFile>
#include <QXmlStreamWriter>

bool XmlExporter::exportToXml(const QVector<PasswordEntry> &entries, const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
        return false;

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true);

    writer.writeStartDocument();
    writer.writeStartElement("passwords");

    for (const PasswordEntry &entry : entries) {
        writer.writeStartElement("record");

        writer.writeTextElement("portal", entry.portal);
        writer.writeTextElement("login", entry.login);
        writer.writeTextElement("password", entry.password);

        writer.writeEndElement();
    }

    writer.writeEndElement();
    writer.writeEndDocument();

    file.close();

    return true;
}
