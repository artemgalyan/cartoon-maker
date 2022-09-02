#include <QApplication>

#include "entities/body/factory/BodyFactory.h"
#include "ui/cartooneditor.h"
#include "logic/factory/StyleManager.h"
#include "ui/main_window/mainwindow.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  BodyFactory::Initialize();
  StyleManager::Initialize();
  MainWindow mw;
  mw.setWindowTitle("Make your own cartoon!");
  mw.setWindowIcon(QIcon(":res/icons/icon.png"));
  mw.showFullScreen();
  return QApplication::exec();
}
