#pragma once
#include <QAbstractListModel>
#include <QHash>

class ServersModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DemoRoles
    {
        serverRole = Qt::UserRole + 1,
    };

    ServersModel( );

    void add_server( const QString& server );

    int rowCount( const QModelIndex& parent = QModelIndex( ) ) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    QHash< int, QByteArray > roleNames( ) const override;

private:
    QList< QString > m_servers;
};
