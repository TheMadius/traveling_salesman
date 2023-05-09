#include "dialogvstreamview.h"
#include "ui_dialogvstreamview.h"
#include <QDebug>
#include <QKeyEvent>
#include "mainwindow.h"

DialogVStreamView::DialogVStreamView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVStreamView)
{
    ui->setupUi(this);
    this->layout()->setContentsMargins(0,0,0,0);

    scene = new QGraphicsScene();

    this->ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    this->ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->ui->graphicsView->setScene(scene);
    photo = new QGraphicsPixmapItem();
    scene->addItem(photo);

    num_frame = 0;
}

void DialogVStreamView::setNameCam(QString name)
{
    this->name_cam = name;
    num_frame = 0;
    setFrame();
}

void DialogVStreamView::setFrame()
{
    QStringList param;
    QStringList value;

    param.push_back("vstream");
    value.push_back(this->name_cam);

    param.push_back("frame");
    value.push_back(QString::number(this->num_frame));

    auto main_parent = (MainWindow *)(this->parent());

    QString event = main_parent->sendServerGetRequest(main_parent->getURLServer() + "/vstreamRecordFrame", param, value);
    if (!event.isEmpty() && event != "\n" && event[0] != '<') {
        QStringList list = event.split('\n');
        this->ui->textBrowser->clear();
            try {
                for( int i = 1; i < list.size(); ++i)
                    this->ui->textBrowser->append(list[i]);
                this->ui->textBrowser->scroll(0,0);
                QByteArray array =  QByteArray::fromBase64(list[0].toUtf8());
                std::string face = array.toStdString();
                std::vector<uchar> image(face.begin(), face.end());
                cv::Mat frame = cv::imdecode(image, cv::IMREAD_COLOR);
                auto qImaeg = QImage( (const unsigned char*)(frame.data), frame.cols, frame.rows, static_cast<int>(frame.step), QImage::Format_RGB888).rgbSwapped();;
                this->photo->setPixmap(QPixmap::fromImage(qImaeg));

                this->setFixedHeight(frame.rows);
                this->ui->graphicsView->setFixedWidth(frame.cols);

            } catch (...) {
                this->photo->setPixmap(QPixmap());
                this->ui->textBrowser->setText("");
            }
    } else {
        num_frame--;
        if (num_frame < 0) {
            num_frame = 0;
            return;
        }
    }
}

void DialogVStreamView::keyPressEvent(QKeyEvent *event)
{
    if (event->nativeScanCode() == 60) {
        num_frame++;
        qDebug() << ">" << num_frame;
        setFrame();
    } else if (event->nativeScanCode() == 59) {
        num_frame--;
        if (num_frame < 0) {
            num_frame = 0;
            return;
        }
        setFrame();
    }
}

DialogVStreamView::~DialogVStreamView()
{
    delete ui;
}
