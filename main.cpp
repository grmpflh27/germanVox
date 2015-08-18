#include <QtGui>
#include <QApplication>
//#include "voxsystem.h"

#include "voxUI.h"
#include "voxcardsystem.h"

int main( int argc, char **argv )
{

    QApplication app( argc, argv );
    voxUI voxy;
    //voxy.setWindowIcon(QIcon(":/cfg/res/Icon.png"));
    voxy.setWindowTitle("VoxCards");
    voxy.show();

    return app.exec();
}
