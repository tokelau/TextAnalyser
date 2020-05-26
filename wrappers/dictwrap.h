#ifndef DICTWRAP_H
#define DICTWRAP_H

#include <QtCore>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QMap>
#include <QTextCodec>
#include "dictitem.h"
#include "buttonitem.h"
#include "dicts.h"

class DictWrap : public QObject
{
    Q_OBJECT
private:

public:
    Q_PROPERTY(QString curFile READ curFile WRITE setCurFile NOTIFY curFileChanged)
    Q_PROPERTY(QVariant dataList READ dataList WRITE setDataList NOTIFY dataListChanged)
    Q_PROPERTY(QVariant buttonList READ buttonList WRITE setButtonList NOTIFY buttonListChanged)

    QString m_nCurFile;
    QVariant m_nDataList;
    QVariant m_nButtonList;
    QList<QString> data;
    Dicts* d;
    QString dictPath;

    DictWrap(QObject* pobj = nullptr) : QObject(pobj) {
        d = new Dicts;
        m_nCurFile = "cur";
    }
    ~DictWrap() {
        delete d;
    }

    static QString getDictsPath() {
        return QDir::currentPath() + "/data/dictionaries/";
    }

    Q_INVOKABLE QString getFileContent(const QString& fName) {
        QString fileName = QDir::currentPath() + "/data/dictionaries/" + fName + "/" + fName + ".txt";

        QFile* file = new QFile(fileName);
        if (!file->open(QIODevice::ReadOnly)) {
//            qDebug() << fileName << endl;
            return "";
        }

        QTextStream stream(file);
        stream.setCodec("UTF-8");
        QString text = stream.readAll();
        file->close();

        d->setFilesList(fName);
        emit dataListChanged(dataList());
        emit buttonListChanged(m_nButtonList);
        return text;
    }
    //отличается от предыдущей тем, что не меняет список словарей
    Q_INVOKABLE QString getPrFileContent(const QString& fName) {
        QString fileName = QDir::currentPath() + "/data/dictionaries/" + fName;

        QFile* file = new QFile(fileName);
        if (!file->open(QIODevice::ReadOnly)) {
//            qDebug() << fileName << endl;
            return "";
        }

        QTextStream stream(file);
        stream.setCodec("UTF-8");
        QString text = stream.readAll();
        file->close();

        return text;
    }
    Q_INVOKABLE void addToDicts(const QString& fName) {
        QString name;
        if (fName.contains("/")) {
            name = fName.split("/").last().split(".")[0];
        } else {
            name = fName;
        }
        deleteDict(name);
        if (!d->addToDicts(name)) {
            emit dataListChanged(dataList());
            emit buttonListChanged(m_nButtonList);
        }

        if (fName.contains("/")) {
            QFile* file = new QFile(fName.split("///")[1]);
            if (!file->open(QIODevice::ReadWrite)) {}
            QTextStream stream(file);
            stream.setCodec("UTF-8");
            QString content = stream.readAll();
            file->close();

            QString fPath = QDir::currentPath() + "/data/dictionaries/" + name + "/" + name + ".txt";
            file = new QFile(fPath);
            if (!file->open(QIODevice::WriteOnly)) {}
            QTextStream outStream(file);
            outStream.setCodec("UTF-8");
            outStream << content;
            file->close();
        }
    }
    Q_INVOKABLE qlonglong saveFile(const QString& fName, const QString& content) {
        QString fPath = QDir::currentPath() + "/data/dictionaries/" + fName + "/" + fName + ".txt";
        QFile* file = new QFile(fPath);
        if (!file->open(QIODevice::WriteOnly)) {
//            m_nFileState = -1;
            return -1;
        }
        QTextStream stream(file);
        stream.setCodec("UTF-8");
        stream << content;
        file->close();

//        d->setFilesList(fPath);
//        emit dataListChanged(dataList());
        return 0;
    }
    Q_INVOKABLE void deleteDict(const QString& fName) {
        QDir dir(QDir::currentPath() + "/data/dictionaries/" + fName);
//        qDebug() << dir.removeRecursively();
        dir.removeRecursively();
        d->removeFromDict(fName);
        emit dataListChanged(dataList());
        emit buttonListChanged(m_nButtonList);
    }
    Q_INVOKABLE bool isDictCreated(const QString& dName) {
        QString name;
        if (dName.contains("/")) {
            name = dName.split("/").last().split(".")[0];
        } else {
            name = dName;
        }
//        qDebug() << name;
        return d->isDictCreated(name);
    }
    //нужна, когда мы выбираем словарь и хотим обновить список кнопок только для одного словаря
    Q_INVOKABLE void setFilesList(const QString& dictName) {
//        qDebug() << dictName;
        d->setFilesList(dictName);
    }

    //отличается от buttonList()!!! возвращает кнопки только одного словаря!!!
    Q_INVOKABLE QVariant getButtonList(QString dictName) {
        QList<QObject*> list;
//        d->setFilesList(dictName);
        for(int i = 2; i < d->filesHash.value(dictName).length(); i++) {
            if (d->filesHash.value(dictName)[i] != "") {
                list.append(new ButtonItem(d->filesHash.value(dictName)[i]));
            }
        }

        m_nButtonList = QVariant::fromValue(list);
        emit buttonListChanged(m_nButtonList);
        return m_nButtonList;
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
//                qDebug() << (*it) <<endl;
                list.append(new DictItem(d->filesHash.value(*it)));
            }
        }
        m_nDataList = QVariant::fromValue(list);
//        emit dataListChanged(m_nDataList);
        return m_nDataList;
    }

    QVariant buttonList() {
        QList<QObject*> list;
//        qDebug() << m_nCurFile;
        for (QStack<QString>::iterator it = d->filesStack.begin(); it != d->filesStack.end(); it++) {
            for(int i = 2; i < d->filesHash.value(*it).length(); i++) {
                if (d->filesHash.value(*it)[i] != "") {
//                    qDebug() << "name: " << *it << " ???: " << d->filesHash.value(*it)[i];
                    list.append(new ButtonItem(d->filesHash.value(*it)[i]));
                }

            }
        }
        m_nButtonList = QVariant::fromValue(list);
//        emit buttonListChanged(m_nButtonList);
        return m_nButtonList;
    }

    //задает переменную
    void setCurFile(const QString& fName) {
        m_nCurFile = fName;
        emit curFileChanged(m_nCurFile);
    }
    void setDataList(const QVariant& list) {
        m_nDataList = list;
        emit dataListChanged(m_nDataList);
    }
    void setButtonList(const QVariant& list) {
        m_nButtonList = list;
        emit buttonListChanged(m_nButtonList);
    }
signals:
    //сигнал изменения
    void curFileChanged(QString);
    void dataListChanged(QVariant);
    void buttonListChanged(QVariant);
};

#endif // DICTWRAP_H
