#ifndef CREATUREDIALOG_H
#define CREATUREDIALOG_H

#include <QDialog>

namespace Ui {
class CreatureDialog;
}

class CreatureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreatureDialog(QWidget *parent = 0);
    ~CreatureDialog();

    int creature;

public slots:
    void accept();

private:
    Ui::CreatureDialog *ui;
};

#endif // CREATUREDIALOG_H
