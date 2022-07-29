#ifndef CARTOON_MAKER_UI_CONTEXT_MENU_MAINPOINTCONTEXTMENU_H_
#define CARTOON_MAKER_UI_CONTEXT_MENU_MAINPOINTCONTEXTMENU_H_

#include <QMenu>
#include "../../entities/skeleton/point/MainPoint.h"

class MainPointContextMenu : public QMenu {
 public:
  explicit MainPointContextMenu(MainPoint *point);
 private slots:
  void DeletePoint();
  void ScaleChanged(double new_scale);
  void PlaceBehind();
  void PlaceInFront();
 private:
  void ForceSceneUpdate() const;
  MainPoint *const point_;
};

#endif //CARTOON_MAKER_UI_CONTEXT_MENU_MAINPOINTCONTEXTMENU_H_
