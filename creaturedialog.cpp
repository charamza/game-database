#include "creaturedialog.h"
#include "ui_creaturedialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>

CreatureDialog::CreatureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreatureDialog)
{
    ui->setupUi(this);
}

CreatureDialog::~CreatureDialog()
{
    delete ui;
}

void CreatureDialog::setOptions(int location)
{
    QSqlQuery query;
    query.prepare("SELECT id, name "
                            "FROM creature "
                            "WHERE NOT EXISTS ( "
                                "SELECT 1 "
                                "FROM location_creature "
                                "WHERE creature.id = location_creature.creature "
                                "AND location_creature.location = :location "
                            ");");
    query.bindValue(":location", location);
    query.exec();
    while (query.next()) {
        QSqlRecord record = query.record();
        ui->inputCreature->addItem(record.value("name").toString(), record.value("id").toInt());
    }
}

void CreatureDialog::accept()
{
    creature = ui->inputCreature->currentData().toInt();

    if (creature == 0) {
        QMessageBox::warning(this, "Chyba", "Již nemůžeš přidat více kreatur. Raději vytvoř nějaké nové.");
        return;
    }

    QDialog::accept();
}
