#include "BodyFactory.h"
#include "QFile"

BodyFactory* BodyFactory::instance_ = nullptr;

BodyFactory::BodyFactory() {
  LoadModels();
}

BodyFactory* BodyFactory::Instance() {
  if (instance_ == nullptr) {
    instance_ = new BodyFactory();
  }
  return instance_;
}

void BodyFactory::Initialize() {
  instance_ = Instance();
}

void BodyFactory::LoadModels() {
  QDir models(":/res/models/");
  models.setFilter(QDir::Dirs);
  QDirIterator iterator(models, QDirIterator::Subdirectories);
  while (iterator.hasNext()) {
    LoadModelByType(iterator.next());
  }
}

Body* BodyFactory::CreateByType(const QString& type) const {
  for (const auto& model : models_) {
    if (model.GetBodyType() == type)
      return model.Clone();
  }
  return nullptr;
}

void BodyFactory::LoadModelByType(const QString& subDirName) {
  QString fileName = subDirName + "/skeleton.txt";
  QFile inputFile(fileName);
  if (inputFile.open(QIODevice::ReadOnly)) {
    QTextStream in(&inputFile);
    int lineBlock = in.readLine().toInt();
    int coord1;
    int coord2;
    int parent;
    QVector < Point * > points;
    while (lineBlock != 0) {
      in >> coord1;
      in >> coord2;
      in >> parent;
      if (parent == -1) points.push_back(new MainPoint(coord1, coord2));
      else points.push_back(new SidePoint(coord1, qDegreesToRadians(coord2), points[parent]));
      QString ends = in.readLine();
      if (ends.startsWith(" fixed")) {
        points.last()->setFlag(QGraphicsItem::ItemIsMovable, false);
        auto p = dynamic_cast<SidePoint*>(points.last());
        if (p != nullptr) {
          auto parent_point = dynamic_cast<SidePoint*>(points[parent]);
          if (parent_point != nullptr) {
            parent_point->AddMouseMoveEventListener([coord2](SidePoint* point) {
              auto children = point->childItems();
              for (auto p: children) {
                if (p->flags().testFlag(QGraphicsItem::ItemIsMovable))
                  continue;
                auto p1 = dynamic_cast<SidePoint*>(p);
                if (p1 != nullptr) {
                  p1->SetAngle(point->GetAngle() + qDegreesToRadians(coord2));
                }
              }
            });
          }
        }
      }
      --lineBlock;
    }
    Skeleton skeleton(points);

    lineBlock = in.readLine().toInt();
    QString pointFileName;
    QPointF offset;
    int pointIndex;
    QVector < Image * > images;
    QHash<Image*, int> indexFromImage;
    while (lineBlock != 0) {
      in >> pointFileName;
      in >> offset.rx();
      in >> offset.ry();
      in >> pointIndex;
      QPixmap pixmap(subDirName + "/" + pointFileName);
      auto* image = new Image(pixmap, offset);
      images.push_back(image);
      indexFromImage.insert(image, pointIndex);
      --lineBlock;
    }
    QDir dir(subDirName);
    QString entityName = dir.dirName();
    Body body(skeleton, images, indexFromImage, entityName);
    models_.push_back(body);
    inputFile.close();

    QPixmap preview(subDirName + "/preview.png");
    previews_.push_back({entityName, preview});
  }
}

const QVector<QPair<QString, QPixmap>>& BodyFactory::GetPreviews() const {
  return previews_;
}

