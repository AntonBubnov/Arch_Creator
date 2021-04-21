#include "secondwindow.h"
#include "ui_secondwindow.h"

SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);

    setWindowTitle("Каталог"); // Изменяем заголовок окна

    ui->pushButton_2->setEnabled(false);    //
    ui->pushButton_3->setEnabled(false);    //
    ui->pushButton_4->setEnabled(false);    //
    ui->pushButton_5->setEnabled(false);    //
    ui->pushButton_6->setEnabled(false);    //
    ui->pushButton_7->setEnabled(false);    // Делаем кнопки неактивными
    ui->pushButton_8->setEnabled(false);    //
    ui->pushButton_9->setEnabled(false);    //
    ui->pushButton_10->setEnabled(false);   //
    ui->pushButton_11->setEnabled(false);   //
    ui->pushButton_12->setEnabled(false);   //
    ui->pushButton_13->setEnabled(false);   //

    // Устанавливаем картинки неактивных арок на соответствующте кнопки

    //***************************************************************//
    Arch = "image: url(:/new/Круговая_1.png);";                      //
    semicircle = ui->pushButton_2;                                   //
    semicircle ->setStyleSheet(Arch);                                //
                                                                     //
    Arch = "image: url(:/new/Сегментная_1.png);";                    //
    segment = ui->pushButton_3;                                      //
    segment ->setStyleSheet(Arch);                                   //
                                                                     //
    Arch = "image: url(:/new/Стрельчатая_1.png);";                   //
    lancet = ui->pushButton_4;                                       //
    lancet ->setStyleSheet(Arch);                                    //
                                                                     //
    Arch = "image: url(:/new/Трилисник_1.png);";                     //
    shamrock = ui->pushButton_5;                                     //
    shamrock ->setStyleSheet(Arch);                                  //
                                                                     //
    Arch = "image: url(:/new/Плечо_1.png);";                         //
    shouldered_flat = ui->pushButton_6;                              //
    shouldered_flat ->setStyleSheet(Arch);                           //
                                                                     //
    Arch = "image: url(:/new/Корень_1.png);";                        //
    root = ui->pushButton_7;                                         //
    root ->setStyleSheet(Arch);                                      //
                                                                     //
    Arch = "image: url(:/new/Занавеса_1.png);";                      //
    inflexed = ui->pushButton_8;                                     //
    inflexed ->setStyleSheet(Arch);                                  //
                                                                     //
    Arch = "image: url(:/new/Парабола_1.png);";                      //
    parabolic = ui->pushButton_9;                                    //
    parabolic ->setStyleSheet(Arch);                                 //
                                                                     //
    Arch = "image: url(:/new/Циклоида_1.png);";                      //
    cycloid = ui->pushButton_10;                                     //
    cycloid ->setStyleSheet(Arch);                                   //
                                                                     //
    Arch = "image: url(:/new/Эллипс_1.png);";                        //
    elliptical = ui->pushButton_12;                                  //
    elliptical ->setStyleSheet(Arch);                                //
    //***************************************************************//
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

// Функция фильтра арок
// Срабатывает при нажатии на кнопку

void SecondWindow::on_pushButton_clicked()
{


    QString arrow = ui->arrow->text();      //
    h = arrow.toInt();                      //
                                            //
    QString height = ui->height->text();    // Считываем текст из поля в строку
    a = height.toInt();                     // Преобразуем строку в число
                                            //
    QString width = ui->width->text();      //
    b = width.toInt();                      //

    // Проверяем введённые данные

    if(h>=1 && b>=1 && a>=1 && h<=10000 && b<=10000 && a<=10000){

        // Проверяем возможность построения арки
        // Делаем кнопки активными или неактивными

        ui->pushButton_7->setEnabled(true);     // Делаем кнопку активной
        Arch = "image: url(:/new/Корень.png);"; //
        root = ui->pushButton_7;                // Устанавливаем картинку активной арки
        root ->setStyleSheet(Arch);             //

        ui->pushButton_9->setEnabled(true);
        Arch = "image: url(:/new/Парабола.png);";
        parabolic = ui->pushButton_9;
        parabolic ->setStyleSheet(Arch);

        if(h==b/2){
            ui->pushButton_2->setEnabled(true);
            Arch = "image: url(:/new/Круговая.png);";
            semicircle = ui->pushButton_2;
            semicircle ->setStyleSheet(Arch);

            ui->pushButton_5->setEnabled(true);
            Arch = "image: url(:/new/Трилисник.png);";
            shamrock = ui->pushButton_5;
            shamrock ->setStyleSheet(Arch);

            ui->pushButton_12->setEnabled(false);
            Arch = "image: url(:/new/Эллипс_1.png);";
            elliptical = ui->pushButton_12;
            elliptical ->setStyleSheet(Arch);
        }
        else{
            ui->pushButton_2->setEnabled(false);
            Arch = "image: url(:/new/Круговая_1.png);";
            semicircle = ui->pushButton_2;
            semicircle ->setStyleSheet(Arch);

            ui->pushButton_5->setEnabled(false);
            Arch = "image: url(:/new/Трилисник_1.png);";
            shamrock = ui->pushButton_5;
            shamrock ->setStyleSheet(Arch);

            ui->pushButton_12->setEnabled(true);
            Arch = "image: url(:/new/Эллипс.png);";
            elliptical = ui->pushButton_12;
            elliptical ->setStyleSheet(Arch);
        }

        if(h>b/2){
            ui->pushButton_4->setEnabled(true);
            Arch = "image: url(:/new/Стрельчатая.png);";
            lancet = ui->pushButton_4;
            lancet ->setStyleSheet(Arch);

            ui->pushButton_8->setEnabled(false);
            Arch = "image: url(:/new/Занавеса_1.png);";
            inflexed = ui->pushButton_8;
            inflexed ->setStyleSheet(Arch);
        }
        else{
            ui->pushButton_4->setEnabled(false);
            Arch = "image: url(:/new/Стрельчатая_1.png);";
            lancet = ui->pushButton_4;
            lancet ->setStyleSheet(Arch);

            ui->pushButton_8->setEnabled(true);
            Arch = "image: url(:/new/Занавеса.png);";
            inflexed = ui->pushButton_8;
            inflexed ->setStyleSheet(Arch);
        }

        if(h>=b/4){
            ui->pushButton_6->setEnabled(true);
            Arch = "image: url(:/new/Плечо.png);";
            shouldered_flat = ui->pushButton_6;
            shouldered_flat ->setStyleSheet(Arch);
        }
        else{
            ui->pushButton_6->setEnabled(false);
            Arch = "image: url(:/new/Плечо_1.png);";
            shouldered_flat = ui->pushButton_6;
            shouldered_flat ->setStyleSheet(Arch);
        }

        if(h>=b/M_PI-1 && h<=b/M_PI+1){
            ui->pushButton_10->setEnabled(true);
            Arch = "image: url(:/new/Циклоида.png);";
            cycloid = ui->pushButton_10;
            cycloid ->setStyleSheet(Arch);
        }
        else{
            ui->pushButton_10->setEnabled(false);
            Arch = "image: url(:/new/Циклоида_1.png);";
            cycloid = ui->pushButton_10;
            cycloid ->setStyleSheet(Arch);
        }

        if(h<b/2){
            ui->pushButton_3->setEnabled(true);
            Arch = "image: url(:/new/Сегментная.png);";
            segment = ui->pushButton_3;
            segment ->setStyleSheet(Arch);
        }
        else{
            ui->pushButton_3->setEnabled(false);
            Arch = "image: url(:/new/Сегментная_1.png);";
            segment = ui->pushButton_3;
            segment ->setStyleSheet(Arch);
        }
    }
    else{
        ui->pushButton_2->setEnabled(false);        // Делаем кнопку неактивной
        Arch = "image: url(:/new/Круговая_1.png);"; //
        semicircle = ui->pushButton_2;              // Устанавливаем картинку неактивной арки
        semicircle ->setStyleSheet(Arch);           //

        ui->pushButton_3->setEnabled(false);
        Arch = "image: url(:/new/Сегментная_1.png);";
        segment = ui->pushButton_3;
        segment ->setStyleSheet(Arch);

        ui->pushButton_4->setEnabled(false);
        Arch = "image: url(:/new/Стрельчатая_1.png);";
        lancet = ui->pushButton_4;
        lancet ->setStyleSheet(Arch);

        ui->pushButton_5->setEnabled(false);
        Arch = "image: url(:/new/Трилисник_1.png);";
        shamrock = ui->pushButton_5;
        shamrock ->setStyleSheet(Arch);

        ui->pushButton_6->setEnabled(false);
        Arch = "image: url(:/new/Плечо_1.png);";
        shouldered_flat = ui->pushButton_6;
        shouldered_flat ->setStyleSheet(Arch);

        ui->pushButton_7->setEnabled(false);
        Arch = "image: url(:/new/Корень_1.png);";
        root = ui->pushButton_7;
        root ->setStyleSheet(Arch);

        ui->pushButton_8->setEnabled(false);
        Arch = "image: url(:/new/Занавеса_1.png);";
        inflexed = ui->pushButton_8;
        inflexed ->setStyleSheet(Arch);

        ui->pushButton_9->setEnabled(false);
        Arch = "image: url(:/new/Парабола_1.png);";
        parabolic = ui->pushButton_9;
        parabolic ->setStyleSheet(Arch);

        ui->pushButton_10->setEnabled(false);
        Arch = "image: url(:/new/Циклоида_1.png);";
        cycloid = ui->pushButton_10;
        cycloid ->setStyleSheet(Arch);

        ui->pushButton_12->setEnabled(false);
        Arch = "image: url(:/new/Эллипс_1.png);";
        elliptical = ui->pushButton_12;
        elliptical ->setStyleSheet(Arch);

        QMessageBox::critical(this,"Ошибка","Неверный формат ввода"); // Сообщение об ошибке, при неправельных входных данных
        return;
    }
}

// Функция записи данных в файл

void SecondWindow::Write_to_file()
{
    QFile file(".//data.txt");  // Создаём объект типа QFile в который записываем создаваемый текстовый файл

    // Открываем файл только для записи текста
    // Проверяем открытие файла

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::information(this,"Ошибка","Неправильный путь!"); // Выводим информацию, если неудалось открыть файл
        return;
    }

    QTextStream stream(&file);

    stream << n << " " << h << " " << b << " " << a; // Записываем значение параметров арки в файл

    file.close(); // Закрываем файл
}

// Функция создания нового окна

void SecondWindow::FormCreation()
{
    Write_to_file();
    window3 = new ThirdWindow(this);    // Создаём новое окно
    window3->setWindowFlags(window3->windowFlags() & ~Qt::WindowContextHelpButtonHint); // Удаляем Help из окна
    window3->show();    // Демонстрируем новое окно
}

// Дальше обрабатываем нажатия на кнопки, которые отвечают за разные арки
// При нажатии записываем номер арки и создаём новое окно

void SecondWindow::on_pushButton_2_clicked()
{
    n=1;
    FormCreation();
}

void SecondWindow::on_pushButton_3_clicked()
{
    n=2;
    FormCreation();
}

void SecondWindow::on_pushButton_4_clicked()
{
    n=3;
    FormCreation();
}

void SecondWindow::on_pushButton_5_clicked()
{
    n=4;
    FormCreation();
}

void SecondWindow::on_pushButton_8_clicked()
{
    n=5;
    FormCreation();
}

void SecondWindow::on_pushButton_6_clicked()
{
    n=6;
    FormCreation();
}

void SecondWindow::on_pushButton_9_clicked()
{
    n=7;
    FormCreation();
}

void SecondWindow::on_pushButton_7_clicked()
{
    n=8;
    FormCreation();
}

void SecondWindow::on_pushButton_12_clicked()
{
    n=9;
    FormCreation();
}

void SecondWindow::on_pushButton_10_clicked()
{
    n=10;
    FormCreation();
}

void SecondWindow::on_pushButton_13_clicked()
{
    n=11;
    FormCreation();
}

void SecondWindow::on_pushButton_11_clicked()
{
    n=12;
    FormCreation();
}
