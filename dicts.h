#ifndef DICTS_H
#define DICTS_H

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

class Dicts : public QObject
{
    Q_OBJECT
    bool getFileList() {
        QFile file("data/dictionaries.txt");
        if (!file.open(QIODevice::ReadWrite)) {
            return 1; //dictionaries.txt был удален вместе с папкой data
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
//            qDebug() << line[0] << endl;
        }
        file.close();

        filesStack.removeAll("");
        if (filesStack.size() > 50) {
            for(int i = 50; i < filesStack.size(); i++) {
                QFile f("data/dictionaries/" + filesStack[i]);
                f.remove();
//                qDebug() << filesStack[i] << " " << filesHash[filesStack[i]];
                filesHash.remove(filesStack[i]);
                filesStack.removeAt(i);
            }
        }

        return 0; //все хорошо
    }
public:
    Dicts() {
        getFileList();
    }
    QStack<QString> filesStack;
    QHash<QString, QList<QString>> filesHash;

    void setFilesList(QString fileName) {
        if (filesStack.contains("")) {
            filesStack.removeAll("");
            filesHash.remove("");
        }
        if (filesStack.contains(fileName)) {
            filesStack.remove(filesStack.indexOf(fileName));
        }

        filesStack.push_front(fileName);
        QList<QString> list;
        list.push_back(fileName);
        list.push_back(QDate::currentDate().toString("dd.MM.yyyy"));
        filesHash.insert(fileName, list);

        if (filesStack.size() > 50) {
            for(int i = 50;  filesStack.size() != i;) {
                if (filesStack[i] != "") {
                    QFile file("data/dictionaries/" + filesStack[i]);
//                    qDebug()  << file.fileName() << " " << filesStack.size();
                    file.remove();
//                    qDebug() <<filesStack[i] <<" " << filesHash[filesStack[i]];
                    filesHash.remove(filesStack[i]);
                    filesStack.remove(i);
//                    qDebug() << filesStack.size() << endl;
                }

            }
        }

        QFile file("data/dictionaries.txt");
        if (!file.open(QIODevice::ReadWrite)) {
//            qDebug() << "123" <<endl;
            return;
        }
        file.resize(0);

        QTextStream stream(&file);
        stream.setCodec("Windows-1251");
//        QHash<QString, QList<QString>>::iterator hash = filesHash->begin();
        for(QStack<QString>::iterator it = filesStack.begin(); it != filesStack.end(); it++) {
            stream << filesHash.value((*it)).join("&&?") << endl;
//            qDebug() << filesHash.value((*it)).join("&&?") << endl;
        }
        file.close();

        return;
    }
    bool addToDicts(QString fName) {
        if (filesStack.contains("")) {
            filesStack.removeAll("");
            filesHash.remove("");
        }
        if (filesStack.contains(fName)) {
            filesStack.remove(filesStack.indexOf(fName));
            filesStack.push_front(fName);
            return 0;
        }

        setFilesList(fName);
        return 0;
    }
};

#endif // DICTS_H
