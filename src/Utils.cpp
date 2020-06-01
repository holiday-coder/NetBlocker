#include "Utils.h"
#ifdef _WIN32
#include "WindowsNetBlocker.h"
#else
#include <unistd.h>
#include "LinuxNetBlocker.h"
#endif

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>

#include <memory>

namespace
{
void
parse_servers( const QJsonObject& root, utils::Servers_vt& container )
{
    if ( root.contains( "servers" ) && root[ "servers" ].isArray( ) )
    {
        const auto servers = root[ "servers" ].toArray( );
        for ( const auto& server : servers )
        {
            const auto server_obj = server.toObject( );
            if ( server_obj.contains( "ip" ) && server_obj[ "ip" ].isString( ) )
            {
                container.push_back( server[ "ip" ].toString( ) );
            }
        }
    }
}

}  // namespace

utils::Servers_vt
utils::parse_servers_adresses( const QByteArray& data )
{
    QJsonDocument doc = QJsonDocument::fromJson( data );

    QJsonObject root = doc.object( );

    Servers_vt container;

    if ( root.contains( "datacenters" ) && root[ "datacenters" ].isArray( ) )
    {
        const auto datacenters = root[ "datacenters" ].toArray( );
        for ( const auto& datacenter : datacenters )
        {
            const auto datatcentr_obj = datacenter.toObject( );

            parse_servers( datatcentr_obj, container );
        }
    }
    return container;
}

void
utils::show_msg_box( QMessageBox::Icon icon, const QString& msg_text )
{
    QMessageBox msg_box;
    msg_box.setText( msg_text );
    msg_box.setIcon( icon );
    msg_box.exec( );
}

void
utils::check_process_error( const int error_code, const QString& error_msg )
{
    qDebug( ) << error_code;
    if ( error_code != 0 )
    {
        utils::show_msg_box( QMessageBox::Warning, error_msg );
    }
}

std::unique_ptr< blocker::INetBlocker >
utils::create_blocker( )
{
#ifdef _WIN32
    return std::make_unique< blocker::WindowsNetBlocker >( );
#else
    return std::make_unique< blocker::LinuxNetBlocker >( );
#endif
}

bool
utils::is_admin_rights( )
{
#ifndef _WIN32
    if ( getuid( ) != 0 )
    {
        utils::show_msg_box( QMessageBox::Information, "Lauch application with admin rights" );
        return false;
    }
#endif
    return true;
}
