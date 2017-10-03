#include "sublocationdialog.h"
#include "ui_sublocationdialog.h"
#include <QMessageBox>

SublocationDialog::SublocationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SublocationDialog)
{
    ui->setupUi(this);
}

SublocationDialog::~SublocationDialog()
{
    delete ui;
}

void SublocationDialog::accept()
{
    name = ui->inputName->text();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Chyba", "Prázdné jméno");
        return;
    }

    QDialog::accept();
}
