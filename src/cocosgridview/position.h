#ifndef COCOSGRIDVIEW_H
#define COCOSGRIDVIEW_H

#include <climits>

namespace cocosgridview {

///
/// Position class.
///
struct Position {
  unsigned int row;
  unsigned int col;
  Position(unsigned int row, unsigned int col);
  Position();
  bool operator==(const Position &other) const;
  bool operator!=(const Position &other) const;
  operator bool const();
};

}

#endif
