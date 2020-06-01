#include "Utils.h"
#include "Presenter.h"

#include <QApplication>

int
main( int argc, char* argv[] )
{
    try
    {
        QCoreApplication::setAttribute( Qt::AA_EnableHighDpiScaling );

        QApplication app( argc, argv );

        if ( !utils::is_admin_rights( ) )
        {
            return 0;
        }

        Presenter presenter( app );

        presenter.run( );

        return app.exec( );
    }
    catch ( const std::exception& ex )
    {
        utils::show_msg_box( QMessageBox::Critical,
                             QString( "App crashed: %1" ).arg( ex.what( ) ) );
    }
}
