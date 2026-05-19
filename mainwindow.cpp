#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "passwordgenerator.h"
#include "xml_exporter.h"
#include "csv_exporter.h"
#include "passwordstorage.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadTable()
{
    ui->tableWidget->setRowCount(0);

    QVector<PasswordEntry> entries = storage.getEntries();

    for(int i = 0; i < entries.size(); i++) {

        ui->tableWidget->insertRow(i);

        ui->tableWidget->setItem(i, 0,
                                 new QTableWidgetItem(QString::number(entries[i].id)));

        ui->tableWidget->setItem(i, 1,
                                 new QTableWidgetItem(entries[i].portal));

        ui->tableWidget->setItem(i, 2,
                                 new QTableWidgetItem(entries[i].login));

        ui->tableWidget->setItem(i, 3,
                                 new QTableWidgetItem(entries[i].password));
    }
}

int MainWindow::generateId()
{
    QVector<PasswordEntry> entries = storage.getEntries();

    int maxId = 0;

    for(const PasswordEntry &entry : entries) {
        if(entry.id > maxId)
            maxId = entry.id;
    }

    return maxId + 1;
}

void MainWindow::on_addButton_clicked()
{
    PasswordEntry entry;

    entry.id = generateId();
    entry.portal = ui->portalEdit->text();
    entry.login = ui->loginEdit->text();
    entry.password = ui->passwordEdit->text();


    storage.addEntry(entry);

    loadTable();
}
void MainWindow::on_deleteButton_clicked()
{
    int row = ui->tableWidget->currentRow();

    if(row < 0)
    {
        return;
    }
    int id = ui->tableWidget->item(row, 0)->text().toInt();

    storage.deleteEntry(id);

    loadTable();
}

void MainWindow::on_generateButton_clicked()
{
    ui->passwordEdit->setText(
        PasswordGenerator::generate()
        );
}

void MainWindow::on_exportXmlButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Eksport XML",
        "passwords.xml",
        "XML (*.xml)"
        );

    if(fileName.isEmpty())
        return;

    XmlExporter::exportToXml(
        storage.getEntries(),
        fileName
        );

    QMessageBox::information(this,
                             "Sukces",
                             "Wyeksportowano XML");
}
void MainWindow::on_updateButton_clicked()
{
    int row = ui->tableWidget->currentRow();

    if(row < 0)
        return;

    int id = ui->tableWidget->item(row, 0)->text().toInt();

    PasswordEntry entry;

    entry.id = id;
    entry.portal = ui->portalEdit->text();
    entry.login = ui->loginEdit->text();
    entry.password = ui->passwordEdit->text();

    storage.updateEntry(id, entry);

    loadTable();
}
void MainWindow::on_exportCsvButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Eksport CSV",
        "passwords.csv",
        "CSV (*.csv)"
        );

    if(fileName.isEmpty())
        return;

    CsvExporter::exportToCsv(
        storage.getEntries(),
        fileName
        );

    QMessageBox::information(this,
                             "Sukces",
                             "Wyeksportowano CSV");
}
