#ifndef DICTHANDLER_H
#define DICTHANDLER_H

#include <QtCore>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QMap>
#include <QTextCodec>
#include "dictitem.h"
#include "dicts.h"

class DictHandler : public QObject
{
    Q_OBJECT
private:

public:
    Q_PROPERTY(QString curFile READ curFile WRITE setCurFile NOTIFY curFileChanged)
    Q_PROPERTY(QVariant dataList READ dataList WRITE setDataList NOTIFY dataListChanged)

    QString m_nCurFile;
    QVariant m_nDataList;
    QList<QString> data;
    Dicts* d;

    DictHandler(QObject* pobj = nullptr) : QObject(pobj) {
        d = new Dicts;
        m_nCurFile = "";
    }
    ~DictHandler() {
        delete d;
    }

    Q_INVOKABLE QString getFileContent(const QString& fName) {
        QString fileName = QDir::currentPath() + "/data/dictionaries/" + fName;

        QFile* file = new QFile(fileName);
        if (!file->open(QIODevice::ReadOnly)) {
//            qDebug() << fileName << endl;
            return "";
        }

        QTextStream stream(file);
        stream.setCodec("Windows-1251");
        QString text = stream.readAll();
        file->close();

//        qDebug() << "gfc" <<endl;
        d->setFilesList(fName);
        emit dataListChanged(dataList());
//        setFileName(fileName);
        return text;
    }
    Q_INVOKABLE void addToDicts(const QString& fName) {
        if (!d->addToDicts(fName)) {
            emit dataListChanged(dataList());
        }
    }

    //возвращает переменную
    QString curFile() {
        emit curFileChanged(m_nCurFile);
        return m_nCurFile;
    }
    QVariant dataList() {
        QList<QObject*> list;
        for (QStack<QString>::iterator it = d->filesStack.begin(); it != d->filesStack.end(); it++) {
            if (!((*it) == "")) {
//                qDebug() << d->filesStack.size() << (*it) << " " <<d->filesHash.value(*it) <<endl;
                list.append(new DictItem(d->filesHash.value(*it)));
            }
        }
        m_nDataList = QVariant::fromValue(list);
//        emit dataListChanged(m_nDataList);
        return m_nDataList;
    }

    //задает переменную
    void setCurFile(const QString& fPath) {
        m_nCurFile = fPath;
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
};

#endif // DICTHANDLER_H
