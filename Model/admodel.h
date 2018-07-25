#ifndef ADMODEL_H
#define ADMODEL_H

#include <QAbstractItemModel>

class AdModel : public QAbstractListModel
{
    Q_OBJECT

public:
    struct AdInfo
    {
        QString title;
        QString img;
        QString url;
    };

    enum AdType{
        title,
        img,
        url,
    };

public:
    explicit AdModel(QObject *parent = nullptr);
    ~AdModel();    

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void clear();
    void addData(AdInfo item);
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<AdInfo> m_datas;
};

#endif // ADMODEL_H
