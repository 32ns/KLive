#include "admodel.h"

AdModel::AdModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

AdModel::~AdModel()
{

}

int AdModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_datas.size();
}



QVariant AdModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= (int)m_datas.size())
    {
        return QVariant();
    }
    const AdInfo &d = m_datas[index.row()];
    switch (role) {
    case AdType::title:{
        return d.title;
    }break;
    case AdType::img : {
        return d.img;
    }break;
    case AdType::url :{
        return d.url;
    }break;


    default:
        break;
    }


    return QVariant();
}

QHash<int, QByteArray> AdModel::roleNames() const
{
    QHash<int,QByteArray> d;
    d[AdType::title] = "title";
    d[AdType::img] = "img";
    d[AdType::url] = "url";
    return d;
}

void AdModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, m_datas.size());
    m_datas.clear();
    endRemoveRows();
}

void AdModel::addData(AdModel::AdInfo item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_datas.push_back(item);
    endInsertRows();
}
