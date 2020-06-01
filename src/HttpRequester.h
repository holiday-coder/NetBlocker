#pragma once
#include <QNetworkAccessManager>

namespace http
{
class HttpRequester : public QObject
{
    Q_OBJECT
public:
    HttpRequester( );
    void request( const QUrl& url );

signals:
    void response_data( const QByteArray& );

private slots:
    void on_response_received( QNetworkReply* );

private:
    QNetworkAccessManager m_manager;
};
}  // namespace http
