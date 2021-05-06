#include "thirdwindow.h"
#include "ui_thirdwindow.h"
#include "secondwindow.h"

ThirdWindow::ThirdWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThirdWindow)
{
    ui->setupUi(this);

    Read_from_file();   // Считываем данные из файла, которые записали в прошлом окне

    h = B/200.0;        // Устанавливаем шаг
    xBegin = -B/2.0;    // Начало цикла
    xEnd = B/2.0;       // Конец цикла

    ui->widget->xAxis2->setVisible(true);       //
    ui->widget->yAxis2->setVisible(true);       // Настраиваем внешний вид
    ui->widget->xAxis2->setTickLabels(false);   // координатных осей
    ui->widget->yAxis2->setTickLabels(false);   //

    // Определяем области значений осей координат

    if(B>=A+H){
        L = (1.5*B-A-H)/2.0;
        ui->widget->xAxis->setRange(-0.75*B,0.75*B); // Область по оси x
        ui->widget->yAxis->setRange(-L-A,L+H);       // Область по оси y
    }
    else{
        L = (1.5*A+H-B)/2.0;
        ui->widget->xAxis->setRange(-L-B/2.0,L+B/2.0);
        ui->widget->yAxis->setRange(-1.25*A,H+A/4.0);
    }

    ui->widget->axisRect()->setupFullAxesBox(); // Показываем все оси

    ui->widget->xAxis->setLabel("мм");  // Значение по оси x
    ui->widget->yAxis->setLabel("мм");  // Значение по оси y

    // Определяем какую арку выбрали
    // Рисуем график соответствующей арки

    switch (N) {
    case 1: DrawSemicircular();
        break;
    case 2: DraweSegment();
        break;
    case 3: DraweLancet();
        break;
    case 4: DraweShamrock();
        break;
    case 5: DraweInflexed();
        break;
    case 6: DrawShouldered_flat();
        break;
    case 7: DrawParabolic();
        break;
    case 8: DrawRoot();
        break;
    case 9: DrawElliptical();
        break;
    case 10: DrawCycloid();
        break;
    case 11: DrawRootR();
        break;
    case 12: DrawTudor();
        break;
    }

    setWindowTitle(Name);       // Изменяем имя окна в зависимости от выбраной арки

    // Добавляем стрелки и значения высоты, ширины, стрелы подъёма арки на чертёж

    QCPItemLine *arrow_A = new QCPItemLine(ui->widget); // Создаём стрелку, для высоты
    arrow_A->start->setCoords(-0.625*B, -A);            // Координаты начала стрелки
    arrow_A->end->setCoords(-0.625*B, 0);               // Координаты конца стрелки
    arrow_A->setHead(QCPLineEnding::esSpikeArrow);      // Рисуем стрелу в конце
    arrow_A->setTail(QCPLineEnding::esSpikeArrow);      // Рисуем стрелу в начале

    QString str_A=QString("%1").arg(A);                 // Создаём строку и записываем в неё значение высоты
    QCPItemText *Text_A = new QCPItemText(ui->widget);  // Создаём текстовую надпись, для значения высоты
    Text_A->position->setCoords(-0.7*B, -A/2.0);        // Задаём координаты надписи
    Text_A->setRotation(-90);                           // Поворачиваем надпись
    Text_A->setText(str_A);                             // Передаём в надпись строку со значением высоты
    Text_A->setFont(QFont(font().family(), 10));        // Отображаем надпись

    QCPItemLine *arrow_B = new QCPItemLine(ui->widget); // Создаём стрелку, для ширины
    arrow_B->start->setCoords(-0.5*B, -A-0.125*B);
    arrow_B->end->setCoords(0.5*B, -A-0.125*B);
    arrow_B->setHead(QCPLineEnding::esSpikeArrow);
    arrow_B->setTail(QCPLineEnding::esSpikeArrow);

    QString str_B=QString("%1").arg(B);
    QCPItemText *Text_B = new QCPItemText(ui->widget);  // Создаём текстовую надпись, для значения ширины
    Text_B->position->setCoords(0, -A-0.2*B);
    Text_B->setText(str_B);
    Text_B->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_H = new QCPItemLine(ui->widget); // Создаём стрелку, для стрелы подъёма
    arrow_H->start->setCoords(-0.625*B, 0);
    arrow_H->end->setCoords(-0.625*B, H);
    arrow_H->setHead(QCPLineEnding::esSpikeArrow);
    arrow_H->setTail(QCPLineEnding::esSpikeArrow);

    QString str_H=QString("%1").arg(H);
    QCPItemText *Text_H = new QCPItemText(ui->widget);  // Создаём текстовую надпись, для значения стрелы подъёма
    Text_H->position->setCoords(-0.7*B, H/2.0);
    Text_H->setRotation(-90);
    Text_H->setText(str_H);
    Text_H->setFont(QFont(font().family(), 10));

    ui->widget->setInteraction(QCP::iRangeZoom, true); // Возможность зума осей
    ui->widget->setInteraction(QCP::iRangeDrag, true); // Возможность перетаскивания графика

    ui->widget->replot();   // Рисуем всё на графике
}

ThirdWindow::~ThirdWindow()
{
    delete ui;
}

// Функция которая рисует прямоугольную часть арки и добавляет начало и конец в вектор криволинейной части

void ThirdWindow::DrawPerimeter()
{
    x1.push_back(xBegin);   //
    y1.push_back(0);        //
    x1.push_back(xBegin);   // Добавляем в вектора координаты 4-х точек
    y1.push_back(-A);       // При отрисовке графика эти точки соеденятся прямыми
    x1.push_back(xEnd);     // Получим прямоугольную часть арки
    y1.push_back(-A);       //
    x1.push_back(xEnd);     //
    y1.push_back(0);        //

    x.push_back(xBegin);    //
    y.push_back(0);         // Добавляем в вектора координаты начала и конца криволинейной части
    x.push_back(xEnd);      // При отрисовке графика координаты сортируется
    y.push_back(0);         // Получим кривую которая точно начинается и заканчивается в указаных точках
}

// Функция которая читает данные из файла

void ThirdWindow::Read_from_file()
{
    QFile file(".//data.txt");      // Создаём объект типа QFile в который передаём созданый текстовый файл

    // Открываем файл только для чтения текста
    // Проверяем открытие файла

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(this,"Ошибка","Неправильный путь!");   // Выводим информацию, если неудалось открыть файл
        return;
    }

    QTextStream stream(&file);

    stream >> N >> H >> B >> A;     // Считываем значение параметров арки из файла

    file.close();   // Закрываем файл
}

// Функция для отрисовки чертежа полукруглой арки

void ThirdWindow::DrawSemicircular()
{
    Name = "Круговая арка"; // Изменяем имя окна, на название выбраной арки
    DrawPerimeter();        // Рисуем прямоугольную часть графика
    R=B/2.0;                // Расчитываем радиус окружности

    // В цикле заполняем векторы координат, для криволинейной части

    for(X=xBegin;X<=xEnd;X+=h){
        x.push_back(X);
        y.push_back(sqrt(R*R-X*X));
    }

    // В цикле заполняем векторы координат, для дополнительных построений

    for(X=xBegin;X<=xEnd;X+=h){
        x3.push_back(X);
        y3.push_back(-sqrt(R*R-X*X));
    }

    x2.push_back(0);    // Координаты ключевой точки
    y2.push_back(0);    //

    DrawGraph();    // Рисуем график арки с дополнительными построениями

    // Создаём и рисуем стрелки на графике

    QString str_R=QString("%1").arg(R);

    QCPItemLine *arrow_R1 = new QCPItemLine(ui->widget);
    arrow_R1->start->setCoords(0, 0);
    arrow_R1->end->setCoords(0, R);
    arrow_R1->setHead(QCPLineEnding::esSpikeArrow);

    // Выводим числениое значение размеров стрелок

    QCPItemText *Text_R1 = new QCPItemText(ui->widget);
    Text_R1->position->setCoords(-0.075*B, H/2.0);
    Text_R1->setRotation(-90);
    Text_R1->setText(str_R);
    Text_R1->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R2 = new QCPItemLine(ui->widget);
    arrow_R2->start->setCoords(0, 0);
    arrow_R2->end->setCoords(R, 0);
    arrow_R2->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R2 = new QCPItemText(ui->widget);
    Text_R2->position->setCoords(0.25*B,-0.075*B);
    Text_R2->setText(str_R);
    Text_R2->setFont(QFont(font().family(), 10));

    // Выводим информацию о соединении прямоугольной и криволинейной части арки

    QString str=" Арка плавно входит ";
    QCPItemText *Text = new QCPItemText(ui->widget);
    Text->position->setCoords(0, -A-0.3*B);
    Text->setText(str);
    Text->setFont(QFont(font().family(), 10));
    Text->setPen(QPen(Qt::black));

    DrawPoint();    // Рисуем ключевые точки
}

// Функция для отрисовки чертежа сегментной арки

void ThirdWindow::DraweSegment()
{
    Name = "Сегментная арка";
    DrawPerimeter();
    C = ((B*B)/4.0-H*H)/(2.0*H);
    R = H+C;
    for(X=xBegin;X<=xEnd;X+=h){
        x.push_back(X);
        y.push_back(sqrt(R*R-X*X)-C);
    }

    for(X=-R;X<=R;X+=h){
        x3.push_back(X);
        y3.push_back(-sqrt(R*R-X*X)-C);
    }

    for(X=-R;X<=xBegin;X+=h){
        x4.push_back(X);
        y4.push_back(sqrt(R*R-X*X)-C);
    }

    for(X=xEnd;X<=R;X+=h){
        x5.push_back(X);
        y5.push_back(sqrt(R*R-X*X)-C);
    }


    x2.push_back(0);
    y2.push_back(-C);

    DrawGraph();

    dx=(0.075*2*B*C)/sqrt(B*B+4*C*C);
    dy=dx*B/(2*C);
    Angle = 90+atan(-(2*B*H)/(B*B/4.0-H*H))*180/M_PI ;

    QString str_R=QString("%1").arg(R, 0, 'f', 0);

    QCPItemLine *arrow_R1 = new QCPItemLine(ui->widget);
    arrow_R1->start->setCoords(0, -C);
    arrow_R1->end->setCoords(B/2.0, 0);
    arrow_R1->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R1 = new QCPItemText(ui->widget);
    Text_R1->position->setCoords(0.25*B+dx, -0.5*C-dy);
    Text_R1->setRotation(-atan(C/(B/2.0))*180/M_PI);
    Text_R1->setText(str_R);
    Text_R1->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R2 = new QCPItemLine(ui->widget);
    arrow_R2->start->setCoords(0, -C);
    arrow_R2->end->setCoords(-B/2.0, 0);
    arrow_R2->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R2 = new QCPItemText(ui->widget);
    Text_R2->position->setCoords(-0.25*B-dx,-0.5*C-dy);
    Text_R2->setRotation(atan(C/(B/2.0))*180/M_PI);
    Text_R2->setText(str_R);
    Text_R2->setFont(QFont(font().family(), 10));

    QString str_grad=QString::fromUtf8("\u030A");
    QString str=QString(" Арка входит под углом %1%2 ").arg(Angle, 0, 'f', 0).arg(str_grad);
    QCPItemText *Text = new QCPItemText(ui->widget);
    Text->position->setCoords(0, -A-0.3*B);
    Text->setText(str);
    Text->setFont(QFont(font().family(), 10));
    Text->setPen(QPen(Qt::black));

    DrawPoint();
}

// Функция для отрисовки чертежа стрельчатой арки

void ThirdWindow::DraweLancet()
{
    Name = "Стрельчатая арка";
    DrawPerimeter();
    C = (H*H-(B*B)/4.0)/B;
    R = B/2.0 + C;
    for(X=xBegin;X<=xEnd;X+=h){
        x.push_back(X);
        y.push_back(sqrt(R*R-(abs(X)+C)*(abs(X)+C)));
    }

    for(Y=-H;Y<=0;Y+=h){
        x3.push_back(sqrt(R*R-Y*Y)-C);
        y3.push_back(Y);
        x3.push_back(C-sqrt(R*R-Y*Y));
        y3.push_back(Y);
    }

    for(Y=H;Y<=R;Y+=h){
        x4.push_back(sqrt(R*R-Y*Y)-C);
        y4.push_back(Y);
        x4.push_back(C-sqrt(R*R-Y*Y));
        y4.push_back(Y);
    }

    for(Y=-R;Y<=-H;Y+=h){
        x5.push_back(sqrt(R*R-Y*Y)-C);
        y5.push_back(Y);
        x5.push_back(C-sqrt(R*R-Y*Y));
        y5.push_back(Y);
    }

    x2.push_back(-C);
    y2.push_back(0);
    x2.push_back(C);
    y2.push_back(0);

    DrawGraph();

    dx=(0.075*B*C)/sqrt(H*H+C*C);
    dy=dx*H/C;

    QString str_R=QString("%1").arg(R, 0, 'f', 0);

    QCPItemLine *arrow_R1 = new QCPItemLine(ui->widget);
    arrow_R1->start->setCoords(-C, 0);
    arrow_R1->end->setCoords(B/2.0, 0);
    arrow_R1->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R1 = new QCPItemText(ui->widget);
    Text_R1->position->setCoords((-C+(B/2.0))/2.0, -0.075*B);
    Text_R1->setText(str_R);
    Text_R1->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R2 = new QCPItemLine(ui->widget);
    arrow_R2->start->setCoords(-C, 0);
    arrow_R2->end->setCoords(0, H);
    arrow_R2->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R2 = new QCPItemText(ui->widget);
    Text_R2->position->setCoords(-0.5*C-dx,0.5*H+dy);
    Text_R2->setRotation(-atan(H/C)*180/M_PI);
    Text_R2->setText(str_R);
    Text_R2->setFont(QFont(font().family(), 10));

    QString str=" Арка плавно входит ";
    QCPItemText *Text = new QCPItemText(ui->widget);
    Text->position->setCoords(0, -A-0.3*B);
    Text->setText(str);
    Text->setFont(QFont(font().family(), 10));
    Text->setPen(QPen(Qt::black));

    DrawPoint();
}

// Функция для отрисовки чертежа трилисной арки

void ThirdWindow::DraweShamrock()
{
    Name = "Арка в форме трилистника";
    DrawPerimeter();
    R = B/4.0;
    for(X=xBegin+h;X<xEnd;X+=h){
        x.push_back(X);
        if(X<=-R || X>=R){
            y.push_back(sqrt(R*R-(abs(X)-R)*(abs(X)-R)));
        }
        else{
            y.push_back(sqrt(R*R-X*X)+R);
        }

    }

    for(X=-R;X<=R;X+=h){
        x3.push_back(X);
        y3.push_back(R-sqrt(R*R-X*X));
        x4.push_back(X);
        y4.push_back(sqrt(R*R-(abs(X)-R)*(abs(X)-R)));
    }

    for(X=xBegin;X<=xEnd;X+=h){
        x5.push_back(X);
        y5.push_back(-sqrt(R*R-(abs(X)-R)*(abs(X)-R)));
    }

    x2.push_back(-R);
    y2.push_back(0);
    x2.push_back(0);
    y2.push_back(R);
    x2.push_back(R);
    y2.push_back(0);

    DrawGraph();

    QString str_R=QString("%1").arg(R, 0, 'f', 0);

    QCPItemLine *arrow_R1 = new QCPItemLine(ui->widget);
    arrow_R1->start->setCoords(-R, 0);
    arrow_R1->end->setCoords(-B/2.0, 0);
    arrow_R1->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R1 = new QCPItemText(ui->widget);
    Text_R1->position->setCoords((-R-(B/2.0))/2.0, -0.075*B);
    Text_R1->setText(str_R);
    Text_R1->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R2 = new QCPItemLine(ui->widget);
    arrow_R2->start->setCoords(-R, 0);
    arrow_R2->end->setCoords(-R, R);
    arrow_R2->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R2 = new QCPItemText(ui->widget);
    Text_R2->position->setCoords(-R-0.075*B,0.5*R);
    Text_R2->setRotation(-90);
    Text_R2->setText(str_R);
    Text_R2->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R3 = new QCPItemLine(ui->widget);
    arrow_R3->start->setCoords(R, 0);
    arrow_R3->end->setCoords(B/2.0, 0);
    arrow_R3->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R3 = new QCPItemText(ui->widget);
    Text_R3->position->setCoords((R+(B/2.0))/2.0, -0.075*B);
    Text_R3->setText(str_R);
    Text_R3->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R4 = new QCPItemLine(ui->widget);
    arrow_R4->start->setCoords(R, 0);
    arrow_R4->end->setCoords(R, R);
    arrow_R4->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R4 = new QCPItemText(ui->widget);
    Text_R4->position->setCoords(R+0.075*B,0.5*R);
    Text_R4->setRotation(90);
    Text_R4->setText(str_R);
    Text_R4->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R5 = new QCPItemLine(ui->widget);
    arrow_R5->start->setCoords(0, R);
    arrow_R5->end->setCoords(-R, R);
    arrow_R5->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R5 = new QCPItemText(ui->widget);
    Text_R5->position->setCoords(-R/2.0, R-0.075*B);
    Text_R5->setText(str_R);
    Text_R5->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R6 = new QCPItemLine(ui->widget);
    arrow_R6->start->setCoords(0, R);
    arrow_R6->end->setCoords(R, R);
    arrow_R6->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R6 = new QCPItemText(ui->widget);
    Text_R6->position->setCoords(R/2.0, R-0.075*B);
    Text_R6->setText(str_R);
    Text_R6->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R7 = new QCPItemLine(ui->widget);
    arrow_R7->start->setCoords(0, R);
    arrow_R7->end->setCoords(0, H);
    arrow_R7->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R7 = new QCPItemText(ui->widget);
    Text_R7->position->setCoords(-0.075*B, 0.375*B);
    Text_R7->setRotation(-90);
    Text_R7->setText(str_R);
    Text_R7->setFont(QFont(font().family(), 10));

    QString str=" Арка плавно входит ";
    QCPItemText *Text = new QCPItemText(ui->widget);
    Text->position->setCoords(0, -A-0.3*B);
    Text->setText(str);
    Text->setFont(QFont(font().family(), 10));
    Text->setPen(QPen(Qt::black));

    DrawPoint();
}

// Функция для отрисовки чертежа арки в форие занавесы

void ThirdWindow::DraweInflexed()
{
    Name = "Арка в форме занавеса";
    DrawPerimeter();
    R = (H*H+(B*B)/4.0)/(2.0*H);
    for(X=xBegin;X<=xEnd;X+=h){
        x.push_back(X);
        y.push_back(R-sqrt(R*R-(abs(X)-B/2.0)*(abs(X)-B/2.0)));
    }

    for(X=-2*R;X<=2*R;X+=h){
        x3.push_back(X);
        y3.push_back(R-sqrt(R*R-pow(sqrt((abs(X)-B/2.0)),4)));
        x4.push_back(X);
        y4.push_back(R-sqrt(R*R-pow(sqrt((abs(X)+B/2.0)),4)));
    }

    x2.push_back(xBegin);
    y2.push_back(R);
    x2.push_back(xEnd);
    y2.push_back(R);

    DrawGraph();

    dx=(0.075*2*B*(R-H))/sqrt(B*B+4*(R-H)*(R-H));
    dy=dx*B/(2*(R-H));

    QString str_R=QString("%1").arg(R, 0, 'f', 0);

    QCPItemLine *arrow_R1 = new QCPItemLine(ui->widget);
    arrow_R1->start->setCoords(-B/2.0, R);
    arrow_R1->end->setCoords(-B/2.0, 0);
    arrow_R1->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R1 = new QCPItemText(ui->widget);
    Text_R1->position->setCoords((-(B/2.0))-0.075*B, R/2.0);
    Text_R1->setRotation(-90);
    Text_R1->setText(str_R);
    Text_R1->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R2 = new QCPItemLine(ui->widget);
    arrow_R2->start->setCoords(B/2.0, R);
    arrow_R2->end->setCoords(B/2.0, 0);
    arrow_R2->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R2 = new QCPItemText(ui->widget);
    Text_R2->position->setCoords((B/2.0)+0.075*B, R/2.0);
    Text_R2->setRotation(90);
    Text_R2->setText(str_R);
    Text_R2->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R3 = new QCPItemLine(ui->widget);
    arrow_R3->start->setCoords(-B/2.0, R);
    arrow_R3->end->setCoords(0, H);
    arrow_R3->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R3 = new QCPItemText(ui->widget);
    if(H!=R){
        Text_R3->position->setCoords((-B/4.0)-dx, (H+R)/2.0-dy);
        Text_R3->setRotation(atan((R-H)/(B/2.0))*180/M_PI);
    }
    else Text_R3->position->setCoords(-(B/4.0), H+0.075*B);
    Text_R3->setText(str_R);
    Text_R3->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R4 = new QCPItemLine(ui->widget);
    arrow_R4->start->setCoords(B/2.0, R);
    arrow_R4->end->setCoords(0, H);
    arrow_R4->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R4 = new QCPItemText(ui->widget);
    if(H!=R){
        Text_R4->position->setCoords((B/4.0)+dx, (H+R)/2.0-dy);
        Text_R4->setRotation(-atan((R-H)/(B/2.0))*180/M_PI);
    }
    else Text_R4->position->setCoords((B/4.0), H+0.075*B);
    Text_R4->setText(str_R);
    Text_R4->setFont(QFont(font().family(), 10));

    QString str=" Арка входит перпендикулярно ";
    QCPItemText *Text = new QCPItemText(ui->widget);
    Text->position->setCoords(0, -A-0.3*B);
    Text->setText(str);
    Text->setFont(QFont(font().family(), 10));
    Text->setPen(QPen(Qt::black));

    DrawPoint();
}

// Функция для отрисовки чертежа арки в форме плеча

void ThirdWindow::DrawShouldered_flat()
{
    Name = "Арка в форме плеча";
    DrawPerimeter();
    R = B/4.0;
    for(X=xBegin+h;X<xEnd;X+=h){
        if(X<-R || X>R){
            x.push_back(X);
            y.push_back(sqrt(R*R-(abs(X)-R)*(abs(X)-R)));
        }
        else{
            x.push_back(-R);
            y.push_back(R);
            x.push_back(-R);
            y.push_back(H);
            x.push_back(R);
            y.push_back(H);
            x.push_back(R);
            y.push_back(R);
            X=R+h;
        }
    }

    for(X=-R;X<=R;X+=h){
        x4.push_back(X);
        y4.push_back(sqrt(R*R-(abs(X)-R)*(abs(X)-R)));
    }

    for(X=xBegin;X<=xEnd;X+=h){
        x5.push_back(X);
        y5.push_back(-sqrt(R*R-(abs(X)-R)*(abs(X)-R)));
    }



    x2.push_back(-R);
    y2.push_back(0);
    x2.push_back(R);
    y2.push_back(0);

    DrawGraph();

    QString str_R=QString("%1").arg(R, 0, 'f', 0);
    QString str_H1=QString("%1").arg(H-R, 0, 'f', 0);
    QString str_B1=QString("%1").arg(B/2.0, 0, 'f', 0);

    QCPItemLine *arrow_R1 = new QCPItemLine(ui->widget);
    arrow_R1->start->setCoords(-R, 0);
    arrow_R1->end->setCoords(-B/2.0, 0);
    arrow_R1->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R1 = new QCPItemText(ui->widget);
    Text_R1->position->setCoords((-R-(B/2.0))/2.0, -0.075*B);
    Text_R1->setText(str_R);
    Text_R1->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R2 = new QCPItemLine(ui->widget);
    arrow_R2->start->setCoords(-R, 0);
    arrow_R2->end->setCoords(-R, R);
    arrow_R2->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R2 = new QCPItemText(ui->widget);
    Text_R2->position->setCoords(-R-0.075*B,0.5*R);
    Text_R2->setRotation(-90);
    Text_R2->setText(str_R);
    Text_R2->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R3 = new QCPItemLine(ui->widget);
    arrow_R3->start->setCoords(R, 0);
    arrow_R3->end->setCoords(B/2.0, 0);
    arrow_R3->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R3 = new QCPItemText(ui->widget);
    Text_R3->position->setCoords((R+(B/2.0))/2.0, -0.075*B);
    Text_R3->setText(str_R);
    Text_R3->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R4 = new QCPItemLine(ui->widget);
    arrow_R4->start->setCoords(R, 0);
    arrow_R4->end->setCoords(R, R);
    arrow_R4->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R4 = new QCPItemText(ui->widget);
    Text_R4->position->setCoords(R+0.075*B,0.5*R);
    Text_R4->setRotation(90);
    Text_R4->setText(str_R);
    Text_R4->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R5 = new QCPItemLine(ui->widget);
    arrow_R5->start->setCoords(R+0.125*B, R);
    arrow_R5->end->setCoords(R+0.125*B, H);
    arrow_R5->setHead(QCPLineEnding::esSpikeArrow);
    arrow_R5->setTail(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R5 = new QCPItemText(ui->widget);
    Text_R5->position->setCoords(R+0.2*B, (H+R)/2.0);
    Text_R5->setRotation(90);
    Text_R5->setText(str_H1);
    Text_R5->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_R6 = new QCPItemLine(ui->widget);
    arrow_R6->start->setCoords(-R, H+0.125*B);
    arrow_R6->end->setCoords(R, H+0.125*B);
    arrow_R6->setHead(QCPLineEnding::esSpikeArrow);
    arrow_R6->setTail(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_R6 = new QCPItemText(ui->widget);
    Text_R6->position->setCoords(0, H+0.2*B);
    Text_R6->setText(str_B1);
    Text_R6->setFont(QFont(font().family(), 10));

    QString str=" Арка плавно входит ";
    QCPItemText *Text = new QCPItemText(ui->widget);
    Text->position->setCoords(0, -A-0.3*B);
    Text->setText(str);
    Text->setFont(QFont(font().family(), 10));
    Text->setPen(QPen(Qt::black));

    DrawPoint();
}

// Функция для отрисовки чертежа параболической арки

void ThirdWindow::DrawParabolic()
{
    Name = "Параболическая арка";
    DrawPerimeter();
    C = (-4.0*H)/(B*B);
    for(X=xBegin;X<=xEnd;X+=h){
            x.push_back(X);
            y.push_back(C*X*X+H);
    }

    DrawGraph();

    QString str_x="x";
    QString str_y=QString(" y = %1%2%3 ").arg(C, 0, 'f', 2).arg(str_x+QString(0x00B2)+" + ").arg(H, 0, 'f',0 );
    Angle = 90+atan(-4*H/B)*180/M_PI ;

    QCPItemText *Text = new QCPItemText(ui->widget);
    Text->position->setCoords(0, H+0.1*B);
    Text->setText(str_y);
    Text->setFont(QFont(font().family(), 10));
    Text->setPen(QPen(Qt::black));

    QString str_grad=QString::fromUtf8("\u030A");
    QString str=QString(" Арка входит под углом %1%2 ").arg(Angle, 0, 'f', 0).arg(str_grad);
    QCPItemText *Text_1 = new QCPItemText(ui->widget);
    Text_1->position->setCoords(0, -A-0.3*B);
    Text_1->setText(str);
    Text_1->setFont(QFont(font().family(), 10));
    Text_1->setPen(QPen(Qt::black));

    DrawPoint();
}

// Функция для отрисовки чертежа арки в форме корня квадратного

void ThirdWindow::DrawRoot()
{
    Name = "Арка в форме квадратного корня";
    DrawPerimeter();
    C = H/sqrt(B);
    for(X=xBegin;X<=xEnd;X+=h){
            x.push_back(X);
            y.push_back(C*sqrt(X+B/2.0));
    }

    DrawGraph();

    QString str_x="(x + ";
    QString str_y=QString(" y = %1%2%3%4 ").arg(C, 0, 'f', 2).arg(QString(0x221A)+str_x).arg(B/2.0, 0, 'f',0 ).arg(')');

    QCPItemText *Text = new QCPItemText(ui->widget);
    Text->position->setCoords(0, H+0.1*B);
    Text->setText(str_y);
    Text->setFont(QFont(font().family(), 10));
    Text->setPen(QPen(Qt::black));

    QString str=" Арка плавно входит ";
    QCPItemText *Text_1 = new QCPItemText(ui->widget);
    Text_1->position->setCoords(0, -A-0.3*B);
    Text_1->setText(str);
    Text_1->setFont(QFont(font().family(), 10));
    Text_1->setPen(QPen(Qt::black));

    DrawPoint();
}

// Функция для отрисовки чертежа арки в форме перевёрнутого корня квадратного
void ThirdWindow::DrawRootR()
{
    Name = "Арка в форме квадратного корня";
    DrawPerimeter();
    C = H/sqrt(B);
    for(X=xBegin;X<=xEnd;X+=h){
            x.push_back(X);
            y.push_back(C*sqrt(-X+B/2.0));
    }

    DrawGraph();

    QString str_x="(-x + ";
    QString str_y=QString(" y = %1%2%3%4 ").arg(C, 0, 'f', 2).arg(QString(0x221A)+str_x).arg(B/2.0, 0, 'f',0 ).arg(')');

    QCPItemText *Text = new QCPItemText(ui->widget);
    Text->position->setCoords(0, H+0.1*B);
    Text->setText(str_y);
    Text->setFont(QFont(font().family(), 10));
    Text->setPen(QPen(Qt::black));

    QString str=" Арка плавно входит ";
    QCPItemText *Text_1 = new QCPItemText(ui->widget);
    Text_1->position->setCoords(0, -A-0.3*B);
    Text_1->setText(str);
    Text_1->setFont(QFont(font().family(), 10));
    Text_1->setPen(QPen(Qt::black));

    DrawPoint();
}

// Функция для отрисовки чертежа арки в стиле тюдор
void ThirdWindow::DrawTudor()
{
    Name = "Арка в стиле тюдор";
    DrawPerimeter();

    R = B/6.0;
    C = ((pow(B, 3)/27)-(sqrt(36*B*B*pow(H, 4) + 3*H*H*pow(B, 4))/9.0))/(4*H*H+(4*B*B)/9);

    for(X=xBegin+h;X<xEnd;X+=h){
        if(X<=C-B/3.0){
            x.push_back(X);
            y.push_back(sqrt(R*R-(X+2*R)*(X+2*R)));
        }
        else if(X>=B/3.0-C){
            x.push_back(X);
            y.push_back(sqrt(R*R-(X-2*R)*(X-2*R)));
        }
        else{
            x3.push_back(X);
            y3.push_back(sqrt(R*R-(abs(X)-2*R)*(abs(X)-2*R)));
        }
        x4.push_back(X);
        y4.push_back(-sqrt(R*R-(abs(X)-2*R)*(abs(X)-2*R)));
    }

    x.push_back(0);
    y.push_back(H);

    DrawGraph();

    x2.push_back(-2*R);
    y2.push_back(0);
    x2.push_back(2*R);
    y2.push_back(0);

    QString str_C=QString("%1").arg(R+C, 0, 'f', 0);

    QCPItemLine *arrow_C = new QCPItemLine(ui->widget);
    arrow_C->start->setCoords(2*R, 0);
    arrow_C->end->setCoords(B/3.0-C, 0);
    arrow_C->setHead(QCPLineEnding::esSpikeArrow);
    arrow_C->setTail(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_C = new QCPItemText(ui->widget);
    Text_C->position->setCoords((B/3.0-C+2*R)/2.0, -0.075*B);
    Text_C->setText(str_C);
    Text_C->setFont(QFont(font().family(), 10));

    QString str_a=QString("%1").arg(R, 0, 'f', 0);

    QCPItemLine *arrow_a = new QCPItemLine(ui->widget);
    arrow_a->start->setCoords(-2*R, 0);
    arrow_a->end->setCoords(-B/2.0, 0);
    arrow_a->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_a = new QCPItemText(ui->widget);
    Text_a->position->setCoords((-2*R-B/2.0)/2.0, -0.075*B);
    Text_a->setText(str_a);
    Text_a->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_b = new QCPItemLine(ui->widget);
    arrow_b->start->setCoords(B/3.0-C, 0);
    arrow_b->end->setCoords(B/3.0-C, sqrt(R*R-C*C));
    arrow_b->setHead(QCPLineEnding::esSpikeArrow);


    QString str=" Арка плавно входит ";
    QCPItemText *Text = new QCPItemText(ui->widget);
    Text->position->setCoords(0, -A-0.3*B);
    Text->setText(str);
    Text->setFont(QFont(font().family(), 10));
    Text->setPen(QPen(Qt::black));

    DrawPoint();
}

// Функция для отрисовки чертежа эллиптической арки

void ThirdWindow::DrawElliptical()
{
    Name = "Эллиптическая арка";
    DrawPerimeter();    
    for(X=xBegin;X<=xEnd;X+=h){
        x.push_back(X);
        y.push_back(H*sqrt(1-(4*X*X)/(B*B)));
    }

    for(X=xBegin;X<=xEnd;X+=h){
        x3.push_back(X);
        y3.push_back(-H*sqrt(1-(4*X*X)/(B*B)));
    }

    DrawGraph();

    if(H<=B/2.0){
        C = sqrt(((B*B)/4.0) - H*H);
        x2.push_back(-C);
        y2.push_back(0);
        x2.push_back(C);
        y2.push_back(0);

        QString str_C=QString("%1").arg(C, 0, 'f', 0);

        QCPItemLine *arrow_C = new QCPItemLine(ui->widget);
        arrow_C->start->setCoords(-C, 0);
        arrow_C->end->setCoords(0, 0);
        arrow_C->setHead(QCPLineEnding::esSpikeArrow);
        arrow_C->setTail(QCPLineEnding::esSpikeArrow);

        QCPItemText *Text_C = new QCPItemText(ui->widget);
        Text_C->position->setCoords(-C/2.0, -0.075*B);
        Text_C->setText(str_C);
        Text_C->setFont(QFont(font().family(), 10));
    }
    else{
        C = sqrt(H*H - ((B*B)/4.0));
        x2.push_back(0);
        y2.push_back(-C);
        x2.push_back(0);
        y2.push_back(C);

        QString str_C=QString("%1").arg(C, 0, 'f', 0);

        QCPItemLine *arrow_C = new QCPItemLine(ui->widget);
        arrow_C->start->setCoords(0, -C);
        arrow_C->end->setCoords(0, 0);
        arrow_C->setHead(QCPLineEnding::esSpikeArrow);
        arrow_C->setTail(QCPLineEnding::esSpikeArrow);

        QCPItemText *Text_b = new QCPItemText(ui->widget);
        Text_b->position->setCoords(-0.075*B, -C/2.0);
        Text_b->setRotation(-90);
        Text_b->setText(str_C);
        Text_b->setFont(QFont(font().family(), 10));
    }

    QString str_a=QString("%1").arg(B/2.0, 0, 'f', 0);
    QString str_b=QString("%1").arg(H, 0, 'f', 0);

    QCPItemLine *arrow_a = new QCPItemLine(ui->widget);
    arrow_a->start->setCoords(0, 0);
    arrow_a->end->setCoords(B/2.0, 0);
    arrow_a->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_a = new QCPItemText(ui->widget);
    Text_a->position->setCoords((B/4.0), -0.075*B);
    Text_a->setText(str_a);
    Text_a->setFont(QFont(font().family(), 10));

    QCPItemLine *arrow_b = new QCPItemLine(ui->widget);
    arrow_b->start->setCoords(0, 0);
    arrow_b->end->setCoords(0, H);
    arrow_b->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemText *Text_b = new QCPItemText(ui->widget);
    Text_b->position->setCoords(-0.075*B, H/2.0);
    Text_b->setRotation(-90);
    Text_b->setText(str_b);
    Text_b->setFont(QFont(font().family(), 10));

    QString str=" Арка плавно входит ";
    QCPItemText *Text = new QCPItemText(ui->widget);
    Text->position->setCoords(0, -A-0.3*B);
    Text->setText(str);
    Text->setFont(QFont(font().family(), 10));
    Text->setPen(QPen(Qt::black));

    DrawPoint();
}

// Функция для отрисовки чертежа циклоидной арки

void ThirdWindow::DrawCycloid()
{
    Name = "Циклоидная арка";
    DrawPerimeter();
    R=B/(2*3.14);
    for(X=-2*3.14;X<=0;X+=0.01){
        x.push_back(R*(X+3.14)-R*sin(X));
        y.push_back(R-R*cos(X));
    }

    DrawGraph();

    QString str_x="x = ";
    QString str_y="y = ";
    QString str_E=QString::fromUtf8("\u03F5");
    QString str_Pi=QString::fromUtf8("\u03C0");
    QString str=QString(" t %1%2%3%4%5 ").arg(str_E+" [-2"+str_Pi+"; 0] \n"+str_y).arg(R, 0, 'f', 0).arg("*(1-cos(t)) \n"+str_x).arg(R, 0, 'f',0 ).arg("*(t+"+str_Pi+"-sin(t))");

    QCPItemText *Text = new QCPItemText(ui->widget);
    Text->position->setCoords(0, H+0.2*B);
    Text->setText(str);
    Text->setFont(QFont(font().family(), 10));
    Text->setPen(QPen(Qt::black));

    QString str_1=" Арка плавно входит ";
    QCPItemText *Text_1 = new QCPItemText(ui->widget);
    Text_1->position->setCoords(0, -A-0.3*B);
    Text_1->setText(str_1);
    Text_1->setFont(QFont(font().family(), 10));
    Text_1->setPen(QPen(Qt::black));

    DrawPoint();
}

// Функция для сохранения файла
// Срабатывает по клику на кнопку

void ThirdWindow::on_pushButton_clicked()
{
    // Создаё строку, в которую передаём путь по которому надо сохранить файл
    QString fileName = QFileDialog::getSaveFileName(this, "Save document...", qApp->applicationDirPath(), "*.pdf");
    if (!fileName.isEmpty())
    {
          ui->widget->savePdf(fileName); // Сохраняем чертёж в PDF формате, по выбраному пути
    }
}

// Функция для отрисовки графиков

void ThirdWindow::DrawGraph()
{
    QPen Pen1; //описывает линиии графика
    Pen1.setWidthF(3);  // толщина линии
    Pen1.setColor(Qt::blue);    // цвет линии


    QPen Pen2;
    Pen2.setWidthF(3);
    Pen2.setColor(Qt::red);
    Pen2.setStyle(Qt::DashLine);    // Стиль линии

    ui->widget->addGraph();             // Добавляем новый график
    ui->widget->graph(0)->addData(x,y); // Передаём координаты точек
    ui->widget->graph(0)->setPen(Pen1); // Передаём данные о виде линии

    ui->widget->addGraph();
    ui->widget->graph(1)->addData(x1,y1);
    ui->widget->graph(1)->setPen(Pen1);     

    ui->widget->addGraph();
    ui->widget->graph(2)->addData(x3,y3);
    ui->widget->graph(2)->setPen(Pen2);

    ui->widget->addGraph();
    ui->widget->graph(3)->addData(x4,y4);
    ui->widget->graph(3)->setPen(Pen2);

    ui->widget->addGraph();
    ui->widget->graph(4)->addData(x5,y5);
    ui->widget->graph(4)->setPen(Pen2);
}

// Функция для отрисовки ключевых точек

void ThirdWindow::DrawPoint()
{
    QCPScatterStyle Scatter1; //описывает точки
    Scatter1.setShape(QCPScatterStyle::ssPlus);//тип точки
    Scatter1.setPen(QPen(Qt::red)); // цвет точки
    Scatter1.setSize(10);  //размер точки

    ui->widget->addGraph();
    ui->widget->graph(5)->setData(x2, y2);
    ui->widget->graph(5)->setScatterStyle(Scatter1); // Передаём данные о виде точек
    ui->widget->graph(5)->setLineStyle(QCPGraph::lsNone); //убирает линию
}
