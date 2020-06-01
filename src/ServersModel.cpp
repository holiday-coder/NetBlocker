#include "ServersModel.h"

#include <QDebug>
#include <QListIterator>

ServersModel::ServersModel( )
    : QAbstractListModel( nullptr )
{
}

void
ServersModel::add_server( const QString& server )
{
    beginInsertRows( QModelIndex( ), m_servers.size( ), m_servers.size( ) );
    m_servers.push_back( server );
    endInsertRows( );
}

int
ServersModel::rowCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent );
    return m_servers.count( );
}

QVariant
ServersModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid( ) )
        return QVariant( );

    if ( role == serverRole )
    {
        return m_servers[ index.row( ) ];
    }
    return QVariant( );
}

QHash< int, QByteArray >
ServersModel::roleNames( ) const
{
    QHash< int, QByteArray > roles;
    roles[ serverRole ] = "name";
    return roles;
}
