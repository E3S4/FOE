#include <QApplication>
#include "ui.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    FOEMainWindow win;
    win.show();
    return app.exec();
}

