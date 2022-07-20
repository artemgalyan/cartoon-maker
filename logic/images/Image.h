#ifndef CARTOON_MAKER_LOGIC_IMAGES_IMAGE_H_
#define CARTOON_MAKER_LOGIC_IMAGES_IMAGE_H_

#include <QString>
#include <QPixmap>

class Image {
 public:
  explicit Image(QPixmap image, const QPointF &offset);
  [[nodiscard]] const QPixmap &GetImage() const;
  [[nodiscard]] QPointF GetOffset() const;
 private:
  QPixmap image_;
 QPointF offset_;
};

#endif //CARTOON_MAKER_LOGIC_IMAGES_IMAGE_H_
