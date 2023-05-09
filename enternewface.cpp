#include "enternewface.h"
#include "ui_enternewface.h"
#include "mainwindow.h"

EnterNewFace::EnterNewFace(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnterNewFace)
{
    ui->setupUi(this);

    this->ui->graphicsView->setScene(new QGraphicsScene());
    this->ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    this->ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    foto = new QGraphicsPixmapItem();
    this->ui->graphicsView->scene()->addItem(foto);
}

EnterNewFace::~EnterNewFace()
{
    delete ui;
}

void EnterNewFace::on_pushButton_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open file",QString(),"JPG (*.jpg)");
    if(!file_name.isNull()) {

       path = file_name;
       cv::Mat image = cv::imread(file_name.toStdString());
       this->ui->label_6->setText("Размер : " + QString::number(image.cols) + "x" + QString::number(image.rows));
       if (this->ui->checkBox->isChecked()){
            ((MainWindow*)(this->parent()))->addMarcersInFace(image);
       }

       double dx = this->ui->graphicsView->width() / (double)image.cols;
       double dy = this->ui->graphicsView->height() / (double)image.rows;
       cv::resize(image, image, cv::Size(), dx, dy, cv::INTER_AREA);

       auto qImaeg =  ((MainWindow*)(this->parent()))->cvMatToQImage(image);
       this->foto->setPixmap(QPixmap::fromImage(qImaeg));
       this->ui->graphicsView->scene()->update(QRectF(0,0,this->ui->graphicsView->width(),this->ui->graphicsView->height()));
    }
}


void EnterNewFace::on_buttonBox_accepted()
{
    QString name = this->ui->lineEdit_2->text();
    QString surname = this->ui->lineEdit->text();
    QString lastname = this->ui->lineEdit_3->text();
    QString url = path;

    if (!( name.isEmpty() || surname.isEmpty() || lastname.isEmpty() || url.isEmpty())) {
        this->name = name ;
        this->surname = surname ;
        this->lastname = lastname ;
        this->url = url;
        this->accept();
    } else {
        QMessageBox::critical(this, QObject::tr("Ошибка"), QObject::tr("Не заполнены все поля!"));
    }
}


void EnterNewFace::on_checkBox_stateChanged(int arg1)
{
    if(path.isEmpty())
        return;

    cv::Mat image = cv::imread(this->path.toStdString());

    if (this->ui->checkBox->isChecked()){
         ((MainWindow*)(this->parent()))->addMarcersInFace(image);
    }
    double dx = this->ui->graphicsView->width() / (double)image.cols;
    double dy = this->ui->graphicsView->height() / (double)image.rows;
    cv::resize(image, image, cv::Size(), dx, dy, cv::INTER_AREA);
    auto qImaeg = ((MainWindow*)(this->parent()))->cvMatToQImage(image);
    this->foto->setPixmap(QPixmap::fromImage(qImaeg));
}

