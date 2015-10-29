#include <QCoreApplication>
#include <QDebug>
#include "cmdlineparser.h"

#include <locale>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    QCoreApplication a(argc, argv);

    CmdLineParser parser;
    parser << CmdLineItem("param1", true, true, true, "Parametr number 1")
           << CmdLineItem("param2", false, false, false, "Long parametr number 2 " \
                                                        "Long parametr number 2 " \
                                                        "Long parametr number 2 " \
                                                        "Long parametr number 2")
            << CmdLineItem("param3", true, false, true, "Description for parametr 3");

    int result = parser.parse(argc, argv);
    switch(result)
    {
    case CmdLineParser::Error:
        qDebug() << (parser.getLastError() + "\n\n" + parser.getHelpString()).toStdString().c_str();
        return 0;
        break;
    case CmdLineParser::Help:
        qDebug() << parser.getHelpString().toStdString().c_str();
        return 0;
        break;
    }

    if(parser.at("param1")) qDebug() << "param1:" << parser.at("param1")->getValue();
    if(parser.at("param2")) qDebug() << "param2:" << parser.at("param2")->getValue();
    if(parser.at("param3")) qDebug() << "param3:" << parser.at("param3")->getValue();

    return a.exec();
}

