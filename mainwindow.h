#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QShortcut>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextStream>


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

    void on_actionExit_triggered();

    void on_actionPrint_triggered();

    void on_actionFile_triggered();

    void on_actionSave_as_triggered();

    void on_actionCpy_triggered();

    void on_actionCute_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionEdit_Theme_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
};
#endif // MAINWINDOW_H
