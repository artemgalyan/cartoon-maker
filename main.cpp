#include <QApplication>

#include "ui/testwidget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  TestWidget w;
  w.show();
  return QApplication::exec();
}
