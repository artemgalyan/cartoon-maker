#include "Body.h"
#include "../skeleton/point/SidePoint.h"

#include "BodySnapshot.h"
#include "../skeleton/Skeleton.h"

#include <utility>
#include <QGraphicsPixmapItem>

QString Body::GetBodyType() const {
  return type_;
}

const Skeleton &Body::GetSkeleton() const {
  return skeleton_;
}

void Body::AddTo(QGraphicsScene *scene) const {
  scene->addItem(skeleton_.GetMainPoint());
}

Body::Body(const Skeleton& skeleton, QVector<Image *> images, QHash<Image*, int> rule, QString type)
  : skeleton_(skeleton), images_(std::move(images)), indexFromImage_(std::move(rule)), type_(std::move(type)) {
  indexFromImage_.squeeze();
  ConnectImagesToPoints();
}

void Body::ConnectImagesToPoints() {
  const QVector<Point*>& points = skeleton_.GetPoints();
  for (auto i = 0; i < images_.count(); ++i) {
    Image* image = images_[i];
    int pointIndex = indexFromImage_[image];
    auto point = dynamic_cast<SidePoint*>(points[pointIndex]);
    auto item = new QGraphicsPixmapItem(image->GetImage(), point->parentItem());
    item->setOffset(image->GetOffset());
    item->setTransformationMode(Qt::SmoothTransformation);
    item->setFlags(QGraphicsItem::ItemStacksBehindParent | QGraphicsItem::ItemNegativeZStacksBehindParent);
    item->setZValue(-1);
    point->AddMouseMoveEventListener([item](SidePoint* point){
      item->setRotation(ToDegrees(point->GetAngle()));
    });
  }
}

double Body::ToDegrees(double rad) {
  return 180 * rad / std::numbers::pi;
}

Body *Body::Clone() const {
  auto newSkeleton = skeleton_.Clone();
  return new Body(newSkeleton, images_, indexFromImage_, type_);
}

void Body::LoadSnapshot(const BodySnapshot &snapshot) {
  skeleton_.LoadSnapshot(snapshot.GetSkeleton());
  skeleton_.SetVisible(snapshot.IsVisible());
}

void Body::SetVisible(bool visible) {
  skeleton_.SetVisible(visible);
}

bool Body::IsVisible() const {
  return skeleton_.IsVisible();
}

double Body::GetZIndex() const {
  return skeleton_.GetMainPoint()->zValue();
}

void Body::SetSkeletonVisible(bool value) {
  skeleton_.SetPointsVisibility(value);
}
