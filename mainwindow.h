#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_Tab_2_triggered();

    void on_actionNewTab_triggered();

    void on_actionCloseTab_triggered();

    void on_actionNew_Tab_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
