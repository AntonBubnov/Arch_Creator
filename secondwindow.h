#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include "thirdwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();    


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::SecondWindow *ui;
    QString Arch;
    QPushButton *lancet, *segment, *semicircle, *shamrock, *inflexed, *shouldered_flat, *parabolic, *root, *elliptical, *tudor, *rootR, *cycloid;
    ThirdWindow *window3;
    int h=0, a=0, b=0, n=0;
    void Write_to_file();
    void FormCreation();

};

#endif // SECONDWINDOW_H
