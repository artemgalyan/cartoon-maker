#include <QApplication>

#include "ui/testwidget.h"
#include "entities/body/factory/BodyFactory.h"
#include "ui/cartooneditor.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  BodyFactory::Initialize();
  CartoonEditor ce;
  ce.showFullScreen();
  return QApplication::exec();
}
