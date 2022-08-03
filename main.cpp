#include <QApplication>

#include "entities/body/factory/BodyFactory.h"
#include "ui/cartooneditor.h"
#include "logic/factory/StyleManager.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  BodyFactory::Initialize();
  StyleManager::Initialize();
  CartoonEditor ce;
  ce.setWindowTitle("Make your own cartoon!");
  ce.setWindowIcon(QIcon(":res/icons/icon.png"));
  ce.show();
  return QApplication::exec();
}
