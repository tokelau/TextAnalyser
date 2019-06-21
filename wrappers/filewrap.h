#ifndef FILEWRAP_H
#define FILEWRAP_H

#include <QtCore>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QMap>
#include <QTextCodec>
#include "fileitem.h"
#include "files.h"
#include "fileparams.h"
#include "wrappers/dictwrap.h"

class FileWrap: public QObject {
    Q_OBJECT
private:
    Q_PROPERTY(QString curFile READ curFile WRITE setCurFile NOTIFY curFileChanged)
    Q_PROPERTY(QVariant dataList READ dataList WRITE setDataList NOTIFY dataListChanged)
    Q_PROPERTY(QVariant params READ params NOTIFY paramsChanged)

    QString m_nCurFile;
    QVariant m_nDataList;
    QVariant m_nParams;
    QList<QString> data;
    Files* f;

    QString getFilePath(QString str) {
        QString filePath;
        if (str.contains("///")) {
            filePath = str.right(str.length() - str.indexOf("///") - 3);
        } else {
            filePath = str;
        }
        return filePath;
    }
public:
    FileWrap(QObject* pobj = nullptr) : QObject(pobj), m_nCurFile(""), f(new Files) {}
    ~FileWrap() {
        delete f;
    }

    //возвращает текст для раздела "Справка"
    Q_INVOKABLE QString getAboutContent() {
        QFile* file = new QFile(QDir::currentPath() + "/data/about.html");
        if (!file->open(QIODevice::ReadOnly)) {
            return "";
        }

        QTextStream stream(file);
        QString text = file->readAll();
        file->close();
        return text;
    }
    Q_INVOKABLE QString getFileContent(const QString& str) {
        QString filePath = getFilePath(str);

        QFile* file = new QFile(filePath);
        if (!file->open(QIODevice::ReadOnly)) {
            return "";
        }

        QTextStream stream(file);
        stream.setCodec("Windows-1251");
        QString text = stream.readAll();
        file->close();
        return text;
    }
    //есть ли файл в папке?
    Q_INVOKABLE bool isFileCreated(const QString& fPath, const QString& fName) {
        QString filePath = getFilePath(fPath);

        QDir dir(filePath);
        QStringList entry = dir.entryList();
        if (entry.contains(fName)) {
            return true;
        }
        return false;
    }
    //добавть файл в приложение
    Q_INVOKABLE QString addFile(const QString& str) {
        QString filePath = getFilePath(str);

        QFile* file = new QFile(filePath);
        if (!file->open(QIODevice::ReadWrite)) {
            return "";
        }
        QString text = file->readAll();
        if (text.isEmpty()) {
        } else {
        }
        file->close();
        if (!f->addToFiles(filePath)) {
            emit dataListChanged(dataList());
        }
        return text;
    }
    Q_INVOKABLE qlonglong saveFile(const QString& fPath, const QString& content) {
        QFile* file = new QFile(fPath);
        if (!file->open(QIODevice::WriteOnly)) {
//            m_nFileState = -1;
            return -1;
        }
        QTextStream stream(file);
        stream.setCodec("Windows-1251");
        stream << content;
        file->close();

        f->setFilesList(fPath);
        emit paramsChanged(m_nParams);
        emit dataListChanged(dataList());
//        emit dataListChanged();
        return 0;
    }
    Q_INVOKABLE void closeFile(const QString& fPath) {
        f->setFilesList(fPath);
        emit paramsChanged(m_nParams);
        emit dataListChanged(dataList());
    }
    Q_INVOKABLE void deleteFile(const QString& fPath) {
        f->removeFromFiles(fPath);
        emit dataListChanged(dataList());
    }
    Q_INVOKABLE void countByDict(const QString& dictName, const QString& fPath) {
        QString dPath = DictWrap::getDictsPath() + dictName + "/" + dictName + ".txt";

        QString oPath = DictWrap::getDictsPath() + dictName + "/" + "files/";
//        qDebug()<<fPath;
//        qDebug()<<dPath;
//        qDebug()<<oPath;
        QDir d(oPath);
        QStringList lst = d.entryList();
        QString fName = fPath.right(fPath.length() - fPath.lastIndexOf("/") - 1);
        QString name = fName;
        if (lst.contains(fName)) {
            for(int i = 1;; i++) {
                name = fName.left(fName.lastIndexOf(".")) + "(" + QString::number(i) + ").txt";
                if (!lst.contains(name)) {
                    oPath += name;
                    break;
                }
            }
        } else {
            oPath += fName;
        }
//        qDebug() << "oPath "<< oPath << endl;
        f->countByDict(fPath, dPath, oPath);
        emit dataListChanged(m_nDataList);
    }

    //возвращает переменную
    QString curFile() {
        emit curFileChanged(m_nCurFile);
        return m_nCurFile;
    }
    QVariant dataList() {
        QList<QObject*> list;
        for (QStack<QString>::iterator it = f->filesStack.begin(); it != f->filesStack.end(); it++) {
            if (!((*it) == "")) {
                list.append(new FileItem(f->filesHash.value((*it))));
            }
        }
        m_nDataList = QVariant::fromValue(list);

        return m_nDataList;
    }
    QVariant params() {
        QList<QObject*> list;
        if (!m_nCurFile.isEmpty()) {
            list.append(new FileParams(f->filesHash.value(m_nCurFile)));
        }

        m_nParams = QVariant::fromValue(list);
        return m_nParams;
    }

    //задает переменную
    void setCurFile(const QString& fPath) {
        m_nCurFile = fPath;
        emit paramsChanged(m_nParams);
        emit curFileChanged(m_nCurFile);
    }
    void setDataList(const QVariant& list) {
        m_nDataList = list;
        emit dataListChanged(m_nDataList);
    }
signals:
    //сигнал изменения
    void curFileChanged(QString);
    void dataListChanged(QVariant);
    void paramsChanged(QVariant);
public slots:
};

#endif // FILEWRAP_H
