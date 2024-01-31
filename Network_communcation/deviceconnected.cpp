#include "deviceconnected.h"

DeviceConnected::DeviceConnected(QObject *parent)
    : QAbstractItemModel(parent)
{}

QVariant DeviceConnected::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex DeviceConnected::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex DeviceConnected::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int DeviceConnected::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int DeviceConnected::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant DeviceConnected::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
