
#ifndef CARTOON_MAKER_LOGIC_CARTOONEDITORSNAPHOT_H_
#define CARTOON_MAKER_LOGIC_CARTOONEDITORSNAPHOT_H_

#include "../entities/Frame.h"

struct CartoonEditorSnapshot {
 int current_frame = 0;
 int number_of_bodies = 0;
 QVector<Frame> frames;
 QVector<QPixmap> images;
};

#endif //CARTOON_MAKER_LOGIC_CARTOONEDITORSNAPHOT_H_
