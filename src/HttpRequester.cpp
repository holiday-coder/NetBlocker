#include "HttpRequester.h"
#include "Utils.h"

#include <QNetworkReply>

http::HttpRequester::HttpRequester( )
    : QObject( nullptr )
{
    connect( &m_manager, &QNetworkAccessManager::finished, this,
             &HttpRequester::on_response_received );
}

void
http::HttpRequester::request( const QUrl& url )
{
    QNetworkRequest request;

    QSslConfiguration config = QSslConfiguration::defaultConfiguration( );
    config.setProtocol( QSsl::TlsV1_2 );
    request.setSslConfiguration( config );

    request.setUrl( url );
    request.setHeader( QNetworkRequest::ServerHeader, "application/json" );

    m_manager.get( request );
}

void
http::HttpRequester::on_response_received( QNetworkReply* reply )
{
    if ( reply->error( ) )
    {
        utils::show_msg_box( QMessageBox::Critical, "Request failed: " + reply->errorString( ) );
    }
    else
    {
        emit response_data( reply->readAll( ) );
    }

    reply->deleteLater( );
}
