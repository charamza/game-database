#include "locationdialog.h"
#include "ui_locationdialog.h"
#include <QMessageBox>
#include <QIntValidator>

LocationDialog::LocationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LocationDialog)
{
    ui->setupUi(this);
    ui->inputLevel->setValidator(new QIntValidator(0, 255, this));
}

LocationDialog::~LocationDialog()
{
    delete ui;
}

void LocationDialog::accept()
{
    name = ui->inputName->text();
    level = ui->inputLevel->text().toInt();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Chyba", "Vyplň všechny údaje.");
        return;
    }

    if (level == 0) {
        QMessageBox::warning(this, "Chyba", "Špatná úroveň oblasti.");
        return;
    }

    QDialog::accept();
}
