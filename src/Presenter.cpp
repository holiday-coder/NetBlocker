#include "Presenter.h"
#include "Utils.h"

#include <QQmlContext>
#include "ServersModel.h"
#include <QIcon>

namespace
{
const QIcon app_icon( "qrc:/icon.ico" );
const QUrl s_qml_main( QStringLiteral( "qrc:/MainWindow.qml" ) );
const QUrl s_servers_url( "https://www.ovpn.com/v2/api/client/entry" );
}  // namespace

Presenter::Presenter( QGuiApplication& app )
    : m_blocker( utils::create_blocker( ) )
{
    connect( &m_engine, &QQmlApplicationEngine::objectCreated, &app,
             []( QObject* obj, const QUrl& objUrl ) {
                 if ( !obj && s_qml_main == objUrl )
                     QCoreApplication::exit( -1 );
             },
             Qt::QueuedConnection );

    connect( &m_requester, &http::HttpRequester::response_data, this,
             &Presenter::on_response_data );

    QQmlContext* context = m_engine.rootContext( );
    if ( context )
    {
        context->setContextProperty( "myModel", QVariant::fromValue( &m_server_model ) );
        context->setContextProperty( "presenter", this );
    }
    else
    {
        qCritical( ) << "QQmlContext is nullptr";
    }

    app.setWindowIcon( app_icon );
}

ServersModel*
Presenter::get_model( )
{
    return &m_server_model;
}

void
Presenter::run( )
{
    m_engine.load( s_qml_main );
    download_servers_ip( );
}

void
Presenter::download_servers_ip( )
{
    try
    {
        m_requester.request( s_servers_url );
    }
    catch ( const std::exception& ex )
    {
        utils::show_msg_box( QMessageBox::Warning,
                             QString( "Download servers ip failed: %1" ).arg( ex.what( ) ) );
    }
}

void
Presenter::on_response_data( const QByteArray& data )
{
    try
    {
        const auto res = utils::parse_servers_adresses( data );
        for ( const auto& server : res )
        {
            m_server_model.add_server( server );
        }
    }
    catch ( const std::exception& ex )
    {
        utils::show_msg_box( QMessageBox::Warning,
                             QString( "Parsing servers failed: %1" ).arg( ex.what( ) ) );
    }
}

void
Presenter::on_block_ip( const QString& ip )
{
    if ( !m_blocker )
    {
        utils::show_msg_box(
            QMessageBox::Warning,
            QString( "Blocker is not initialized. Block/unblock is not working" ) );
        return;
    }

    ip.isEmpty( ) ? m_blocker->unblock( ) : m_blocker->block( ip );
}
