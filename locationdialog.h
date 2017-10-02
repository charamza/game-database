#ifndef LOCATIONDIALOG_H
#define LOCATIONDIALOG_H

#include <QDialog>

namespace Ui {
class LocationDialog;
}

class LocationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LocationDialog(QWidget *parent = 0);
    ~LocationDialog();
    QString name;
    int level;

public slots:
    void accept();

private:
    Ui::LocationDialog *ui;
};

#endif // LOCATIONDIALOG_H
