#include "StyleManager.h"
#include <QDir>
#include <QDirIterator>

StyleManager *StyleManager::instance_ = nullptr;

StyleManager::StyleManager() {
  LoadStyles();
}

StyleManager *StyleManager::Instance() {
  if (instance_ == nullptr) {
    instance_ = new StyleManager();
  }
  return instance_;
}

QString StyleManager::StyleByType(const QString &type) const {
  return styles_.value(type, "");
}

void StyleManager::LoadStyles() {
  QDir styles(":/res/styles/");
  styles.setFilter(QDir::Dirs);
  QDirIterator iterator(styles, QDirIterator::Subdirectories);
  while (iterator.hasNext()) {
    LoadStyleByType(iterator.next());
  }
}

void StyleManager::LoadStyleByType(const QString &subDirName) {
  QString fileName = subDirName + "/style.txt";
  QFile inputFile(fileName);
  if (inputFile.open(QIODevice::ReadOnly)) {
    QTextStream in(&inputFile);
    QString typeStyle = in.readAll();
    QDir dir(subDirName);
    QString type = dir.dirName();
    styles_[type] = typeStyle;
  }
  inputFile.close();
}

void StyleManager::Initialize() {
  Instance();
}



