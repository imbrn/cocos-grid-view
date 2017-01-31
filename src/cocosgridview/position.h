#ifndef COCOSGRIDVIEW_H
#define COCOSGRIDVIEW_H

namespace cocosgridview {

///
/// Position class.
///
struct Position {
  unsigned int row;
  unsigned int col;
  Position(unsigned int row, unsigned int col): row(row), col(col) {
  }
  bool operator==(const Position &other) const {
    return other.row == row && other.col == col;
  }
  bool operator!=(const Position &other) const {
    return !((*this) == other);
  }
};

}

#endif
