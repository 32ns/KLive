#ifndef MODEL_ROOMITEM_H
#define MODEL_ROOMITEM_H

#include <QAbstractListModel>

class Model_RoomItem : public QAbstractListModel
{
    Q_OBJECT


public:
    struct ItemInfo
    {
        int index;
        QString name;
        QString image;
        QString rtmp;
    };
    enum Info{
        index,
        name,
        image,
        rtmp
    };

public:
    explicit Model_RoomItem(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void clear();
    void addItem(ItemInfo item);
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE QString getUrl(int index);
    Q_INVOKABLE QString getName(int index);
    Q_INVOKABLE QString getImage(int index);

private:
    QList<ItemInfo> m_datas;
};

#endif // MODEL_ROOMITEM_H
