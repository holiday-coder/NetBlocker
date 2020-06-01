#pragma once

#include <QByteArray>
#include <QtWidgets/QMessageBox>

namespace blocker
{
class INetBlocker;
}

namespace utils
{
using Servers_vt = std::vector< QString >;
Servers_vt parse_servers_adresses( const QByteArray& data );
void show_msg_box( QMessageBox::Icon icon, const QString& msg_text );
void check_process_error( const int error_code, const QString& error_msg );
std::unique_ptr< blocker::INetBlocker > create_blocker( );
bool is_admin_rights( );
}  // namespace utils
