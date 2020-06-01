#pragma once
#include "ServersModel.h"
#include "HttpRequester.h"
#include "INetBlocker.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

class Presenter : public QObject
{
    Q_OBJECT

public:
    explicit Presenter( QGuiApplication& app );

    Q_INVOKABLE ServersModel* get_model( );

    Q_INVOKABLE void on_block_ip( const QString& ip );

    void run( );

private:
    void download_servers_ip( );

private slots:
    void on_response_data( const QByteArray& data );

private:
    QQmlApplicationEngine m_engine;
    http::HttpRequester m_requester;
    ServersModel m_server_model;
    std::unique_ptr< blocker::INetBlocker > m_blocker;
};
