#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("RoPad");

    // Shortcut to close the current tab when CTRl and W are pressed
    QShortcut* sc1 = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_W), this);
    QObject::connect(sc1, &QShortcut::activated, this, &MainWindow::on_actionCloseTab_triggered);

    // Shortcut to open a new editor/tab when CTRL and T are pressed
    QShortcut* sc2 = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_T), this);
    QObject::connect(sc2, &QShortcut::activated, this, &MainWindow::on_actionNewTab_triggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNewTab_triggered()
{
    auto tabWidget = ui->tabWidget;
    int tabCount = tabWidget->count();
    QPlainTextEdit* editor = new QPlainTextEdit(tabWidget);
    editor->setLayout(new QGridLayout(tabWidget));
    tabWidget->addTab(editor, QString("File " + QString::number(tabCount)));
}


void MainWindow::on_actionCloseTab_triggered()
{
    auto tabWidget = ui->tabWidget;
    int currentTab = tabWidget->currentIndex();

    // TODO: Check if the current tab's editor has been saved or not.
    // If not then prompt if the user wants to save it or not

    // Prevent user from removing the first tab
    if (currentTab == 0)
        return;

    tabWidget->removeTab(currentTab);
}


void MainWindow::on_actionNew_Tab_triggered()
{
    on_actionNewTab_triggered();
}

