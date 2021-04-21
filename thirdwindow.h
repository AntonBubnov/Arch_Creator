#ifndef THIRDWINDOW_H
#define THIRDWINDOW_H

#include <QDialog>
#include <math.h>

namespace Ui {
class ThirdWindow;
}

class ThirdWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ThirdWindow(QWidget *parent = nullptr);
    ~ThirdWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ThirdWindow *ui;
    int  N;
    double H, A, B, xBegin, xEnd, h, X, Y, C, R, L, dx, dy, Angle;
    QVector<double> x, y, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;
    QString Name;
    void DrawGraph();
    void DrawPoint();
    void DrawPerimeter();
    void Read_from_file();
    void DrawSemicircular();
    void DraweSegment();
    void DraweLancet();
    void DraweShamrock();
    void DraweInflexed();
    void DrawShouldered_flat();
    void DrawParabolic();
    void DrawRoot();
    void DrawElliptical();
    void DrawCycloid();
};

#endif // THIRDWINDOW_H
