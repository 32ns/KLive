#ifndef MODEL_ROOMLIST_H
#define MODEL_ROOMLIST_H

#include <QAbstractListModel>

class Model_RoomList : public QAbstractListModel
{
    Q_OBJECT

public:
    struct RoomInfo
    {
        QString platform;   //平台
        QString image;  //平台图片
        QString address;   //平台地址
        QString anchor; //在线主播数
    };

    enum Info
    {
        platform,
        image,
        address,
        anchor
    };

public:
    explicit Model_RoomList(QObject *parent = nullptr);


    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void clear();
    void addRoom(RoomInfo item);
    QHash<int ,QByteArray> roleNames() const override;    

private:
    QList<RoomInfo> m_datas;
};

#endif // MODEL_ROOMLIST_H
