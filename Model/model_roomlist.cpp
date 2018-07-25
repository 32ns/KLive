#include "model_roomlist.h"
#include <QDebug>

Model_RoomList::Model_RoomList(QObject *parent)
    : QAbstractListModel(parent)
{
}


int Model_RoomList::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_datas.size();
}

QVariant Model_RoomList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();


    if(index.row() < 0 || index.row() >= (int)m_datas.size())
    {
        return QVariant();
    }
    const RoomInfo &d = m_datas[index.row()];
    switch (role) {

    case Info::platform : {
        return d.platform;
    }break;

    case Info::image : {
        return d.image;
    }break;

    case Info::address : {
        return d.address;
    }break;

    case Info::anchor : {
        return d.anchor;
    }break;


    default:
        break;
    }



    return QVariant();
}

void Model_RoomList::clear()
{
    beginRemoveRows(QModelIndex(), 0, m_datas.size());
    m_datas.clear();
    endRemoveRows();
}


/******************************************************************
  添加房间
******************************************************************/
void Model_RoomList::addRoom(RoomInfo item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_datas.push_back(item);
    endInsertRows();
}


QHash<int, QByteArray> Model_RoomList::roleNames() const
{
    QHash<int,QByteArray> d;
    d[Info::platform] = "platform";
    d[Info::image] = "image";
    d[Info::address] = "address";
    d[Info::anchor] = "anchor";
    return d;
}


