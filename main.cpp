#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Set the application stylesheet
    QFile appStyleFile("app_style.qss");

//    if (!appStyleFile.open(QFile::ReadOnly))
//        QMessageBox::warning(nullptr, "Stylesheet Error", "Couldn't find/open \"app_style.qss\".\nHelp: Try & check if the file exists in the same direc");

    if (!appStyleFile.open(QFile::ReadWrite))
    {
        QFile file("app_style.qss");
        QTextStream stream(&file);
        stream << "/* Put your css/qss code in here and restart the app if you have it open. */";
        file.close();
    }

    QString styleSheet = QLatin1String(appStyleFile.readAll());

    app.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return app.exec();
}
