#ifndef SUBLOCATIONDIALOG_H
#define SUBLOCATIONDIALOG_H

#include <QDialog>

namespace Ui {
class SublocationDialog;
}

class SublocationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SublocationDialog(QWidget *parent = 0);
    ~SublocationDialog();
    QString name;

public slots:
    void accept();

private:
    Ui::SublocationDialog *ui;
};

#endif // SUBLOCATIONDIALOG_H
