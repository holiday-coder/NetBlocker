#include "LinuxNetBlocker.h"
#include "Utils.h"

#include <QStringList>
#include <QProcess>

namespace
{
constexpr char s_firewall[] = "iptables";
const auto s_block_outgoing = QStringList( ) << "-P"
                                             << "OUTPUT"
                                             << "DROP";
const auto s_unblock_ip = QStringList( ) << "-A"
                                         << "OUTPUT"
                                         << "-j"
                                         << "ACCEPT"
                                         << "-d";
const auto s_reset_unblock_rule = QStringList( ) << "-F"
                                                 << "OUTPUT";

const auto s_unblock_outgoing = QStringList( ) << "-P"
                                               << "OUTPUT"
                                               << "ACCEPT";
}  // namespace

void
blocker::LinuxNetBlocker::block( const QString& ip )
{
    if ( !m_is_blocked )
    {
        utils::check_process_error( QProcess::execute( s_firewall, s_block_outgoing ),
                                    "Block all traffic failed" );
        m_is_blocked = true;
    }
    else
    {
        utils::check_process_error( QProcess::execute( s_firewall, s_reset_unblock_rule ),
                                    "Reset previous ip unblock ip rule failed" );
    }

    utils::check_process_error(
        QProcess::execute( s_firewall, QStringList( s_unblock_ip ) << ip.toStdString( ).c_str( ) ),
        "Unblock " + ip + " ip failed" );
}

void
blocker::LinuxNetBlocker::unblock( )
{
    m_is_blocked = false;
    utils::check_process_error( QProcess::execute( s_firewall, s_unblock_outgoing ),
                                "Unblock outgoing network traffic failed" );

    utils::check_process_error( QProcess::execute( s_firewall, s_reset_unblock_rule ),
                                "Reset unblock ip rules failed" );
}
