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

    QShortcut* sc3 = new QShortcut(QKeySequence(QKeyCombination(Qt::CTRL | Qt::SHIFT | Qt::Key_S)), this);
    QObject::connect(sc3, &QShortcut::activated, this,  &MainWindow::on_actionSave_as_triggered);

    QShortcut* sc4 = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this);
    QObject::connect(sc4, &QShortcut::activated, this, &MainWindow::on_actionSave_triggered);
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
    tabWidget->setCurrentIndex(tabWidget->count() - 1);
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


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionPrint_triggered()
{
    auto tabWidget = ui->tabWidget;
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);

    if (printDialog.exec() == QDialog::Rejected)
    {
        QMessageBox::warning(this, "Printer Unavailable", "Cannot access printer");
        return;
    }

    tabWidget->findChild<QPlainTextEdit*>()->print(&printer);
}


void MainWindow::on_actionFile_triggered()
{
    auto tabWidget = ui->tabWidget;
    QString filename = QFileDialog::getOpenFileName(this, "Open File");
    QFile file(filename);
    currentFile = filename;

    // Check to see if the file can be opened for read & write or for other errors
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "File Error", "Failed to open file: " + file.errorString());
        return;
    }

    setWindowTitle(filename + " - RoPad");
    QTextStream in(&file);
    QString fileContents = in.readAll();
    tabWidget->widget(tabWidget->currentIndex())->findChild<QPlainTextEdit*>()->setPlainText(fileContents);
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    auto tabWidget = ui->tabWidget;
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename);

    // Check if the file can be saved or not
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "File Error", "Failed to save file: " + file.errorString());
        return;
    }

    currentFile = filename;
    setWindowTitle(filename + " - RoPad");
    QTextStream out(&file);
    QString fileContents = tabWidget->widget(tabWidget->currentIndex())->findChild<QPlainTextEdit*>()->toPlainText();
    out << fileContents;
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    auto tabWidget = ui->tabWidget;
    auto currentTab = tabWidget->widget(tabWidget->currentIndex())->findChild<QPlainTextEdit*>();

    QString fileName = QFileDialog::getSaveFileName(this, "Save the file");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "File not saved");
        return;
    }

    QTextStream out(&file);
    QString text = currentTab->toPlainText();
    out << text;
    file.flush();
    file.close();

}
void MainWindow::on_actionCpy_triggered()
{
    ui->tabWidget->widget(ui->tabWidget->currentIndex())->findChild<QPlainTextEdit*>()->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->tabWidget->widget(ui->tabWidget->currentIndex())->findChild<QPlainTextEdit*>()->cut();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->tabWidget->widget(ui->tabWidget->currentIndex())->findChild<QPlainTextEdit*>()->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->tabWidget->widget(ui->tabWidget->currentIndex())->findChild<QPlainTextEdit*>()->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->tabWidget->widget(ui->tabWidget->currentIndex())->findChild<QPlainTextEdit*>()->redo();
}


void MainWindow::on_actionEdit_Theme_triggered()
{

}
