#include "position.h"

namespace cocosgridview {

Position::Position(unsigned int row, unsigned int col): row(row), col(col) {
}

Position::Position(): Position(UINT_MAX, UINT_MAX) {
}

bool Position::operator==(const Position &other) const {
  return other.row == row && other.col == col;
}

bool Position::operator!=(const Position &other) const {
  return !((*this) == other);
}

Position::operator bool const() {
  return row != UINT_MAX && col != UINT_MAX;
}

}
