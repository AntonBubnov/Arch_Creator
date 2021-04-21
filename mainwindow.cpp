#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Logo = "image: url(:/new/Логотип.png);";    // Передаём путь к картинке логотипа в страку
    logo = ui->pushButton;                      // Передаём кнопку
    logo ->setStyleSheet(Logo);                 // Устанавлеваем картику логотипа на кнопку
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Функция создания нового окна
// Срабатывает при нажатии на кнопку

void MainWindow::on_pushButton_clicked()
{
    hide(); // Закрывает окно
    window2 = new SecondWindow(this); // создаём второе окно
    window2->show();                  // показываем его
}
