#ifndef CREATURECREATEDIALOG_H
#define CREATURECREATEDIALOG_H

#include <QDialog>

namespace Ui {
class CreatureCreateDialog;
}

class CreatureCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreatureCreateDialog(QWidget *parent = 0);
    ~CreatureCreateDialog();

    QString name;
    int gold;
    int exp;

public slots:
    void accept();

private:
    Ui::CreatureCreateDialog *ui;
};

#endif // CREATURECREATEDIALOG_H
