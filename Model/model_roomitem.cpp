#include "model_roomitem.h"
#include <QDebug>

Model_RoomItem::Model_RoomItem(QObject *parent)
    : QAbstractListModel(parent)
{
}

int Model_RoomItem::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_datas.size();
}

QVariant Model_RoomItem::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(index.row() < 0 || index.row() >= (int)m_datas.size())
    {
        return QVariant();
    }

    const ItemInfo &d = m_datas[index.row()];
    switch (role) {

    case Info::index : {
        return d.index;
    }break;

    case Info::name : {
        return d.name;
    }break;

    case Info::image : {
        return d.image;
    }break;

    case Info::rtmp : {
        return d.rtmp;
    }break;


    default:
        break;
    }

    return QVariant();
}

void Model_RoomItem::clear()
{
    beginRemoveRows(QModelIndex(),0,m_datas.size());
    m_datas.clear();
    endRemoveRows();
}



void Model_RoomItem::addItem(ItemInfo item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_datas.push_back(item);
    endInsertRows();
}


QHash<int, QByteArray> Model_RoomItem::roleNames() const
{
    QHash<int,QByteArray> d;
    d[Info::index] = "index";
    d[Info::name] = "name";
    d[Info::image] = "image";
    d[Info::rtmp] = "rtmp";
    return d;
}

QString Model_RoomItem::getUrl(int index)
{
    return m_datas[index].rtmp;
}

QString Model_RoomItem::getName(int index)
{
    return m_datas[index].name;
}

QString Model_RoomItem::getImage(int index)
{
    return m_datas[index].image;
}
