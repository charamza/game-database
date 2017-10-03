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
    QSqlQuery query("SELECT * FROM creature");
    query.exec();
    while (query.next()) {
        QSqlRecord record = query.record();
        ui->inputCreature->addItem(record.value("name").toString(), record.value("id").toInt());
    }
}

CreatureDialog::~CreatureDialog()
{
    delete ui;
}

void CreatureDialog::accept()
{
    creature = ui->inputCreature->currentData().toInt();

    QDialog::accept();
}
