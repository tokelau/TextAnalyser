#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H

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
#include "dicthandler.h"
//#include "textProcessor/include/stdafx.h"

class TextHandler : public QObject
{
    Q_OBJECT
private:
    Q_PROPERTY(QString curFile READ curFile WRITE setCurFile NOTIFY curFileChanged)
    Q_PROPERTY(QVariant dataList READ dataList WRITE setDataList NOTIFY dataListChanged)
    Q_PROPERTY(QVariant params READ params NOTIFY paramsChanged)
//    qlonglong m_nFileState;

    QString m_nCurFile;
    QVariant m_nDataList;
    QVariant m_nParams;
    QList<QString> data;
    Files* f;

public:
    TextHandler(QObject* pobj = nullptr) : QObject(pobj) {
        f = new Files;
        m_nCurFile = "";
    }
    ~TextHandler() {
        delete f;
    }

    Q_INVOKABLE QString getFileContent(const QString& str) {
        QString fileName;
        if (str.contains("///")) {
            fileName = str.right(str.length() - str.indexOf("///") - 3);
        } else {
            fileName = str;
        }

        QFile* file = new QFile(fileName);
        if (!file->open(QIODevice::ReadOnly)) {
            return "";
        }

        QTextStream stream(file);
        stream.setCodec("Windows-1251");
        QString text = stream.readAll();
        file->close();
//        setFileName(fileName);
        return text;
    }
    Q_INVOKABLE bool isFileCreated(const QString& fPath, const QString& fName) {
        QString filePath;
        if (fPath.contains("///")) {
            filePath = fPath.right(fPath.length() - fPath.indexOf("///") - 3);
        } else {
            filePath = fPath;
        }
        QDir dir(filePath);
        QStringList entry = dir.entryList();
//        qDebug() << entry <<endl;
//        qDebug() << fName <<endl;
        if (entry.contains(fName)) {
            return true;
        }
        return false;
    }
    Q_INVOKABLE QString addFile(const QString& str) {
        QString filePath;
        if (str.contains("///")) {
            filePath = str.right(str.length() - str.indexOf("///") - 3);
        } else {
            filePath = str;
        }
        QFile* file = new QFile(filePath);
        if (!file->open(QIODevice::ReadWrite)) {
            qDebug() <<"didn't open" <<endl;
            return "";
        }
        QString text = file->readAll();
        if (text.isEmpty()) {
            ///qDebug() << "1";
        } else {
        }
        file->close();
        if (!f->addToFiles(filePath)) {
            emit dataListChanged(dataList());
        }
//        emit dataListChanged(dataList());

//        qDebug
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
    Q_INVOKABLE void countByDict(const QString& dictPath, const QString& fPath) {
        QString dPath;
        if (dictPath.contains("///")) {
            dPath = dictPath.right(dictPath.length() - dictPath.indexOf("///") - 3);
        }

        QString oPath = QDir::currentPath() + "/data/dictionaries";
        QDir d(oPath);
        QStringList lst = d.entryList();
        QString fName = fPath.right(fPath.length() - fPath.lastIndexOf("/") - 1);
        QString name = "res_" + fName;
        if (lst.contains("res_" + fName)) {
            for(int i = 1;; i++) {
                name = "res_" + fName.left(fName.lastIndexOf(".")) + "(" + QString::number(i) + ").txt";
                if (!lst.contains(name)) {
                    oPath += "/" + name;
                    break;
                }
            }
        } else {
            oPath += "/res_" + fName;
        }
//        qDebug() << oPath << endl;
        f->countByDict(fPath, dPath, oPath);
        DictHandler dct;
        dct.addToDicts(name);
//        dct.setFilesList(name);
    }

    //возвращает переменную
//    QString fileName() const {
//        return m_nFileName;
//    }
    QString curFile() {
        emit curFileChanged(m_nCurFile);
        return m_nCurFile;
    }
    QVariant dataList() {
        QList<QObject*> list;
//        qDebug()<< filesStack->length();
//        qDebug() << filesHash->contains("");
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

#endif // TEXTHANDLER_H
