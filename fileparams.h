#ifndef FILEPARAMS_H
#define FILEPARAMS_H

#include <QObject>
#include <QHash>
#include <QDebug>

class FileParams : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString textVol READ textVol NOTIFY textVolChanged)
    Q_PROPERTY(QString uniqVol READ uniqVol NOTIFY uniqVolChanged)
    Q_PROPERTY(QString lexWealth READ lexWealth NOTIFY lexWealthChanged)

    Q_PROPERTY(QString hc1Pos READ hc1Pos NOTIFY hc1PosChanged)
    Q_PROPERTY(QString hc1Word READ hc1Word NOTIFY hc1WordChanged)
    Q_PROPERTY(QString hc1Sent READ hc1Sent NOTIFY hc1SentChanged)

    Q_PROPERTY(QString hc2Pos READ hc2Pos NOTIFY hc2PosChanged)
    Q_PROPERTY(QString hc2Word READ hc2Word NOTIFY hc2WordChanged)
    Q_PROPERTY(QString hc2Sent READ hc2Sent NOTIFY hc2SentChanged)

    FileParams(QList<QString> data = QList<QString>(), QObject *parent = nullptr) : QObject(parent)
    {
        if (!data.isEmpty()) {
//            qDebug() << data;
            m_nTextVol = data[3];
            m_nUniqVol = data[4];
            m_nLexWealth = data[5];

            m_nHC1pos = data[6];
            m_nHC1word = data[7];
            m_nHC1sentense = data[8];

            m_nHC2pos = data[9];
            m_nHC2word = data[10];
            m_nHC2sentense = data[11];
        }
    }

    QString m_nTextVol;
    QString m_nUniqVol;
    QString m_nLexWealth;

    QString m_nHC1pos; //попробовать потом QVariant
    QString m_nHC1word;
    QString m_nHC1sentense;

    QString m_nHC2pos; //попробовать потом QVariant
    QString m_nHC2word;
    QString m_nHC2sentense;

    //возвращает переменную
    QString textVol() const {
        return m_nTextVol;
    }
    QString uniqVol() const {
        return m_nUniqVol;
    }
    QString lexWealth() const {
        return m_nLexWealth;
    }

    QString hc1Pos() const {
        return m_nHC1pos;
    }
    QString hc1Word() {
        return m_nHC1word;
    }
    QString hc1Sent() {
        return m_nHC1sentense;
    }

    QString hc2Pos() const {
        return m_nHC2pos;
    }
    QString hc2Word() {
        return m_nHC2word;
    }
    QString hc2Sent() {
        return m_nHC2sentense;
    }
private:

signals:
    void textVolChanged(QString);
    void uniqVolChanged(QString);
    void lexWealthChanged(QString);

    void hc1PosChanged(QString);
    void hc1WordChanged(QString);
    void hc1SentChanged(QString);

    void hc2PosChanged(QString);
    void hc2WordChanged(QString);
    void hc2SentChanged(QString);
};

#endif // FILEPARAMS_H
