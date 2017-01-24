#ifndef COCOSGRIDVIEW_H
#define COCOSGRIDVIEW_H

namespace cocosgridview {

///
/// Position class.
///
struct Position {
  unsigned int row;
  unsigned int col;
  bool operator==(const Position &other) const {
    return other.row == row && other.col == col;
  }
};

}

#endif
