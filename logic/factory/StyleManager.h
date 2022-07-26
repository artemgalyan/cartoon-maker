#ifndef CARTOON_MAKER_LOGIC_FACTORY_STYLEMANAGER_H_
#define CARTOON_MAKER_LOGIC_FACTORY_STYLEMANAGER_H_

#include <QString>
#include <QMap>
class StyleManager {
 public:
  [[nodiscard]]  QString StyleByType(const QString &type) const;
  static StyleManager *Instance();
 private:
  void LoadStyles();
  void LoadStyleByType(const QString &subDirName);
  StyleManager();
  QMap<QString, QString> styles_;
  static StyleManager *instance_;
};

#endif //CARTOON_MAKER_LOGIC_FACTORY_STYLEMANAGER_H_
