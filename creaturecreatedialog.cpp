#include "creaturecreatedialog.h"
#include "ui_creaturecreatedialog.h"
#include <QMessageBox>

CreatureCreateDialog::CreatureCreateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreatureCreateDialog)
{
    ui->setupUi(this);
}

CreatureCreateDialog::~CreatureCreateDialog()
{
    delete ui;
}

void CreatureCreateDialog::accept()
{
    name = ui->inputName->text();
    gold = ui->inputGold->text().toInt();
    exp = ui->inputExp->text().toInt();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Chyba", "Prázdné jméno");
        return;
    }

    QDialog::accept();
}
