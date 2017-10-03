#include "creaturedialog.h"
#include "ui_creaturedialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

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
    query.prepare("SELECT location_creature.location, location_creature.creature FROM location_creature, creature WHERE creature.id != location_creature.creature AND location_creature.location = :location");
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

    QDialog::accept();
}
