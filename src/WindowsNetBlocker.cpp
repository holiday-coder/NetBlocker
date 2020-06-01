#include "WindowsNetBlocker.h"
#include "Utils.h"

#include <QStringList>
#include <QProcess>

namespace
{
constexpr char s_firewall[] = "netsh";

const auto s_block_outgoing = QStringList( ) << "advfirewall"
                                             << "set"
                                             << "allprofiles"
                                             << "firewallpolicy"
                                             << "blockinbound,blockoutbound";

const auto s_unblock_ip = QStringList( ) << "advfirewall"
                                         << "firewall"
                                         << "add"
                                         << "rule"
                                         << "name=\"NetBlocker\""
                                         << "action=allow"
                                         << "dir=OUT"
                                         << "remoteip=";

const auto s_unblock_outgoing = QStringList( ) << "advfirewall"
                                               << "reset";

const auto s_delete_rule = QStringList() << "advfirewall"
                                         << "firewall" << "delete" << "rule" << "name=\"NetBlocker\"";
}  // namespace

void
blocker::WindowsNetBlocker::block( const QString& ip )
{
    if (!m_is_blocked)
    {
        utils::check_process_error( QProcess::execute( s_firewall, s_block_outgoing ),
                                    "Block all traffic failed" );
        m_is_blocked = true;

    }
    else {
        utils::check_process_error( QProcess::execute( s_firewall, s_delete_rule ),
                                    "Reset previous ip unblock ip rule failed" );
    }

    utils::check_process_error(
        QProcess::execute( s_firewall, QStringList( s_unblock_ip ) << ip.toStdString( ).c_str( ) ),
        "Unblock " + ip + " ip failed" );
}

void
blocker::WindowsNetBlocker::unblock( )
{
    m_is_blocked = false;
    utils::check_process_error( QProcess::execute( s_firewall, s_unblock_outgoing ),
                                "Unblock outgoing network traffic failed" );
}
