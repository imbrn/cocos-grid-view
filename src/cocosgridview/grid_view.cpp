#include "grid_view.h"
#include <climits>

namespace cocosgridview {

GridView::GridView(const Dimension &dimension, float items_gap):
      dimension_(dimension),
      items_gap_(items_gap),
      invalid_position_(UINT_MAX, UINT_MAX) {
  RecicleSlots();
}

GridView *GridView::create(const Dimension &dimension, float items_gap) {
  GridView *obj = new GridView(dimension, items_gap);
  if (obj->init()) {
    obj->autorelease();
    return obj;
  } else {
    delete obj;
    return nullptr;
  }
}

void GridView::onSizeChanged() {
  cocos2d::ui::Widget::onSizeChanged();
  PositionSlots();
}

void GridView::RecicleSlots() {
  RemoveSlots();
  for (unsigned int row = 0; row < rows(); row++) {
    for (unsigned int col = 0; col < cols(); col++) {
      auto slot = GridSlot::create(this, {row, col});
      AddSlot(slot);
    }
  }
}

void GridView::AddSlot(GridSlot *slot) {
  slots_.push_back(slot);
  this->addChild(slot);
}

void GridView::RemoveSlots() {
  for (auto it = slots_.begin(); it != slots_.end(); it++) {
    auto slot = *it;
    this->removeChild(slot);
  }
  slots_.clear();
}

void GridView::PositionSlots() {
  for (auto slot : slots_) {
    slot->Align();
  }
}

void GridView::AddComponent(const Position &at, cocos2d::ui::Widget *component) {
  auto slot = get_slot(at);
  if (slot) {
    slot->AddComponent(component);
  }
}

void GridView::RemoveAllComponents() {
  for (auto slot : slots_) {
    slot->RemoveAllComponents();
  }
}

void GridView::RemoveAllComponents(const Position &at) {
  auto slot = get_slot(at);
  if (slot) {
    slot->RemoveAllComponents();
  }
}

void GridView::RemoveComponent(const Position &at, cocos2d::ui::Widget *component) {
  auto slot = get_slot(at);
  if (slot) {
    slot->RemoveComponent(component);
  }
}

cocos2d::Rect GridView::get_slot_area(const Position &at) const {
  auto slot = get_slot(at);
  if (slot) {
    return slot->area();
  } else {
    return {0, 0, 0, 0};
  }
}

cocos2d::Size GridView::calculate_available_size() const {
  auto size = getContentSize();
  auto horz_gap = items_gap_ * (cols() - 1);
  auto vert_gap = items_gap_ * (rows() - 1);
  return {
    size.width - horz_gap,
    size.height - vert_gap
  };
}

cocos2d::Size GridView::calculate_slot_size() const {
  auto available_size = this->calculate_available_size();
  return {
    available_size.width / cols(),
    available_size.height / rows()
  };
}

cocos2d::Rect GridView::calculate_slot_area(const Position &at) const {
  auto size = calculate_slot_size();
  float x = size.width * at.col + items_gap_ * at.col;
  float y = size.height * at.row + items_gap_ * at.row;
  return { x, y, size.width, size.height };
}

GridSlot *GridView::get_slot(const Position &at) {
  for (GridSlot *slot : slots_) {
    if (slot && slot->grid_position() == at)
      return slot;
  }
  return nullptr;
}

const GridSlot *GridView::get_slot(const Position &at) const {
  for (GridSlot *slot : slots_) {
    if (slot && slot->grid_position() == at)
      return slot;
  }
  return nullptr;
}

unsigned int GridView::components_count(const Position &at) const {
  auto slot = get_slot(at);
  if (slot) {
    return slot->components_amount();
  } else {
    return 0;
  }
}

cocos2d::ui::Widget *GridView::get_component(const Position &at, unsigned int index) {
  auto slot = get_slot(at);
  if (slot) {
    return slot->get_component(index);
  } else {
    return nullptr;
  }
}

const cocos2d::ui::Widget *GridView::get_component(const Position &at, unsigned int index) const {
  auto slot = get_slot(at);
  if (slot) {
    return slot->get_component(index);
  } else {
    return nullptr;
  }
}

Position GridView::get_slot_by_location(const cocos2d::Point &location) const {
  for (auto slot : slots_) {
    if (slot->getBoundingBox().containsPoint(location))
      return slot->grid_position();
  }
  return invalid_position_;
}

unsigned int GridView::rows() const {
  return dimension_.rows;
}

unsigned int GridView::cols() const {
  return dimension_.cols;
}

const Dimension &GridView::dimension() const {
  return dimension_;
}

float GridView::items_gap() const {
  return items_gap_;
}

void GridView::set_dimension(const Dimension &dimension) {
  dimension_ = dimension;
  RecicleSlots();
  PositionSlots();
}

void GridView::set_items_gap(float items_gap) {
  items_gap_ = items_gap;
  PositionSlots();
}

const Position &GridView::invalid_position() const {
  return invalid_position_;
}

}
