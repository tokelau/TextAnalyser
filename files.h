#ifndef FILES_H
#define FILES_H

#include <QObject>
#include <QFile>
#include <QIODevice>
#include <QStack>
#include <QHash>
#include <QList>
#include <QDate>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include "textProcessor/include/stdafx.h"

class Files : public QObject
{
    Q_OBJECT

    bool getFileList() {
        QFile file("data/files.txt");
        if (!file.open(QIODevice::ReadWrite)) {
            return 1; //files.txt был удален вместе с папкой data
        }

        QTextStream stream(&file);
        stream.setCodec("Windows-1251");
        QString all = stream.readAll();
        QList<QString> lines = all.split("\n");
//        qDebug() << lines;
        for(int i = 0; i < lines.length(); i++) {
            QList<QString> line = lines[i].split("&&?");
            filesStack.push(line[0]);
            filesHash.insert(line[0], QList<QString>(line));
        }
        file.close();
        return 0; //все хорошо
    }
public:
    Files() {
        getFileList();
    }
    QStack<QString> filesStack;
    QHash<QString, QList<QString>> filesHash;

    bool addToFiles(QString filePath) {
        if (filesStack.contains("")) {
            filesStack.removeAll(""); //зачем сначала all
            filesHash.remove(""); //а потом просто remove
        }
        if (filesStack.contains(filePath)) {
            filesStack.remove(filesStack.indexOf(filePath));
            filesStack.push_front(filePath);
            return 0;
        }

//        TextProcessor tp(filePath.toStdWString(), (QDir::currentPath() + "/data/dict.txt").toStdWString());
//        QByteArray arr();
//        for(std::set<std::wstring>::iterator it = tp.service.begin(); it != tp.service.end(); it++) {
//            qDebug() << QString::fromStdWString(*it) << endl;
//        }

        setFilesList(filePath);

        return 0;
    }
    void setFilesList(QString filePath) {
        if (filesStack.contains("")) {
            filesStack.removeAll("");
            filesHash.remove("");
        }
        if (filesStack.contains(filePath)) {
//            QList<QString> list = filesHash.value(filePath);
//            list[2] = QDate::currentDate().toString("dd.MM.yyyy");
//            filesHash.insert(filePath, list);

            filesStack.remove(filesStack.indexOf(filePath));
//            filesStack.push_front(filePath);
//            return;
        }

        filesStack.push_front(filePath);
        QList<QString> list;
        list.push_back(filePath);
//        qDebug() << filePath.lastIndexOf("/") + 1<<endl;
        QString fileName = filePath.right(filePath.length() - filePath.lastIndexOf("/") - 1);
        list.push_back(fileName);
        list.push_back(QDate::currentDate().toString("dd.MM.yyyy"));

        QString dict = QDir::currentPath() + "/data/dict.txt";
//        qDebug() << QDir::currentPath();
        TextProcessor tp(filePath.toStdWString(), dict.toStdWString());
//        qDebug() << tp.text.clearedText.size();
        list.push_back(QString::number(tp.textVolume));
        list.push_back(QString::number(tp.uniqVolume));
        list.push_back(QString::number(tp.lexWealth));
        list.push_back(QString::number(tp.hc1.pos));
        list.push_back(QString::fromStdWString(tp.hc1.word));
        list.push_back(QString::fromStdWString(tp.hc1.sent));
        list.push_back(QString::number(tp.hc2.pos));
        list.push_back(QString::fromStdWString(tp.hc2.word));
        list.push_back(QString::fromStdWString(tp.hc2.sent));

//        filesHash->
        filesHash.insert(filePath, list);

        return;
    }
    void removeFromFiles(QString filePath) {
        filesStack.removeAll(filePath);
        filesHash.remove(filePath);
    }
    bool countByDict(QString fPath, QString dictPath, QString outPath) {
        QString dPath = QDir::currentPath() + "/data/dict.txt";
        TextProcessor tp(fPath.toStdWString(), dPath.toStdWString());
        qDebug() << TextProcessor::countByDict(tp, dictPath.toStdWString(), outPath.toStdWString());
        return 0;
    }
    
    ~Files() {
//        qDebug() << "destr"<<endl;
        //сохраняем информацию о файле
        QFile file("data/files.txt");
        if (!file.open(QIODevice::ReadWrite)) {
            return;
        }
        file.resize(0);
        QTextStream stream(&file);
        stream.setCodec("Windows-1251");
//        QHash<QString, QList<QString>>::iterator hash = filesHash->begin();
        for(QStack<QString>::iterator it = filesStack.begin(); it != filesStack.end(); it++) {
            if ((*it) != "") {
                stream << filesHash.value((*it)).join("&&?") << endl;
//                qDebug() << "i " << (*it) << endl;
            }
//            hash++;
        }
        file.close();
    }
};

#endif // FILES_H
