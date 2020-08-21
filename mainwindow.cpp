#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_imageChanger(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Animation Demo");
    m_imageChanger = new CarouselImageWindow(this);
    ui->horizontalLayout_main->addWidget(m_imageChanger);

    m_imageChanger->addImage(":/images/Resources/1.jpg");
    m_imageChanger->addImage(":/images/Resources/2.jpg");
    m_imageChanger->addImage(":/images/Resources/3.jpg");
    m_imageChanger->addImage(":/images/Resources/4.jpg");
    m_imageChanger->addImage(":/images/Resources/5.jpg");
    m_imageChanger->addImage(":/images/Resources/6.jpg");
    m_imageChanger->addImage(":/images/Resources/7.jpg");

    m_imageChanger->setControlButtonColor(Qt::yellow);
    m_imageChanger->setBorderColor(Qt::red);

    m_imageChanger->startPlay();

    m_imageChanger->show();
    this->centralWidget()->setMouseTracking(true);
    m_imageChanger->setMouseTracking(true);
    this->setMouseTracking(true);
    m_mouseEventTimer.start(50);
    connect(&m_mouseEventTimer, SIGNAL(timeout()), this, SLOT(onMouseMoveTimeout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::onMouseMoveTimeout()
{
    //获取鼠标在屏幕上的位置
    QPoint mouse_in_screen = QCursor::pos();
    //获取界面顶点在屏幕上的位置
    QPoint app_in_screen = this->geometry().topLeft();

    const QRect rect = m_imageChanger->geometry();
    const QPointF mouse_in_app = mouse_in_screen - app_in_screen;

    //qDebug() << mousePos;

    //如果鼠标位置在图片上，停止切换
    if(rect.contains(mouse_in_app.toPoint())) //on
        m_imageChanger->disableImageChange(true);
    else
        m_imageChanger->disableImageChange(false);
}

void MainWindow::on_pushButton_exit_clicked()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int button = QMessageBox::question(this,"Confirm Exit",
                                       "exit ?",
                                       QMessageBox::Yes|QMessageBox::No,
                                       QMessageBox::No);
    if(button == QMessageBox::Yes)
    {
        event->accept();
        QMainWindow::closeEvent(event);
    }
    else
        event->ignore();
}

void MainWindow::on_checkBox_drawBorder_stateChanged(int arg1)
{
    m_imageChanger->setBorderVisible(ui->checkBox_drawBorder->isChecked());
}
