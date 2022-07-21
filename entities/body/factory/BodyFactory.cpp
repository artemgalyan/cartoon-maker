#include "BodyFactory.h"
#include "QFile"

BodyFactory *BodyFactory::Instance() {
  if (instance_ == nullptr) {
    instance_ = new BodyFactory();
  }
  return instance_;
}

void BodyFactory::Initialize() {
  instance_ = Instance();
}
void BodyFactory::LoadModels() {
  QFile inputFile("Snake/skeleton.txt");
  if (inputFile.open(QIODevice::ReadOnly))
  {
    QTextStream in(&inputFile);
    int lineBlock = in.readLine().toInt();
    int coord1;
    int coord2;
    int parent;
    QVector<Point*> points;
    while (lineBlock!=0)
    {
      in>>coord1;
      in>>coord2;
      in>>parent;
      if (parent==-1) points.push_back(new MainPoint(coord1, coord2));
      else points.push_back(new SidePoint(coord1, coord2, points[parent]));
      --lineBlock;
    }
    Skeleton skeleton(points);

    lineBlock = in.readLine().toInt();
    int pngNumber;
    QString fileName;
    QPointF offset;
    int pointIndex;
    QVector<Image*> images;
    QHash<Image*, int> indexFromImage;
    while (lineBlock!=0)
    {
      in>>pngNumber;
      fileName = "Snake/" + QString::number(pngNumber) +".png";
      in>>offset.rx();
      in>>offset.ry();
      in>>pointIndex;
      QPixmap pixmap(fileName);
      Image *image= new Image(pixmap,offset);
      images.push_back(image);
      indexFromImage.insert(image, pointIndex);
      --lineBlock;
    }
    Body body(skeleton, images, indexFromImage, "Snake/");
    models_.push_back(body);
    inputFile.close();
  }
}
Body *BodyFactory::CreateByType(QString &type) const {
  int i;
  for(i=0; i< models_.size(); i++){
    if (models_[i].GetBodyType()==type)
      return models_[i].Clone();
  }
  return nullptr;
}
