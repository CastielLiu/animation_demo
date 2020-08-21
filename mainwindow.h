#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "carouselimagewindow.h"
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_pushButton_exit_clicked();
    void onMouseMoveTimeout();
    void on_checkBox_drawBorder_stateChanged(int arg1);

private:
    void closeEvent(QCloseEvent *event);


private:
    Ui::MainWindow *ui;
    CarouselImageWindow *m_imageChanger;
    QTimer m_mouseEventTimer;
};

#endif // MAINWINDOW_H
