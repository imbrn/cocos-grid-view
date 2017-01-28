#include "grid_slot.h"
#include "grid_view.h"
#include <algorithm>

namespace cocosgridview {

GridSlot::GridSlot(GridView *grid_view, const Position &grid_position):
      grid_view_(grid_view),
      grid_position_(grid_position) {
}

GridSlot* GridSlot::create(GridView *grid_view, const Position &grid_position) {
  GridSlot *obj = new GridSlot(grid_view, grid_position);
  if (obj->init()) {
    obj->autorelease();
    return obj;
  } else {
    delete obj;
    return nullptr;
  }
}

void GridSlot::Align() {
  auto area = grid_view_->calculate_slot_area(grid_position_);
  this->setAnchorPoint({0, 0});
  this->setPosition(area.origin);
  this->setContentSize(area.size);
}

void GridSlot::onSizeChanged() {
  cocos2d::ui::Widget::onSizeChanged();
  
  for (auto component : components_) {
    FitComponent(component);
    AlignComponent(component);
  }
}

void GridSlot::AddComponent(cocos2d::ui::Widget *component) {
  if (!HasComponent(component)) {
    InsertComponent(component);
    FitComponent(component);
    AlignComponent(component);
  }
}

void GridSlot::InsertComponent(cocos2d::ui::Widget *component) {
  components_.push_back(component);
  this->addChild(component);
}

void GridSlot::AlignComponents() {
  for (auto component : components_) {
    AlignComponent(component);
  }
}

void GridSlot::AlignComponent(cocos2d::ui::Widget *component) {
  if (component) {
    float x = getContentSize().width / 2;
    float y = getContentSize().height / 2;
    component->setAnchorPoint({0.5, 0.5});
    component->setPosition({x, y});
  }
}

void GridSlot::FitComponents() {
  for (auto component : components_) {
    FitComponent(component);
  }
}

void GridSlot::FitComponent(cocos2d::ui::Widget *component) {
  float scale = CalculateComponentScale(component);
  component->setScale(scale, scale);
}

float GridSlot::CalculateComponentScale(cocos2d::ui::Widget *component) const {
  float horz_scale = area().size.width / component->getContentSize().width;
  float vert_scale = area().size.height / component->getContentSize().height;
  return GetScale(horz_scale, vert_scale);
}

float GridSlot::GetScale(float horz, float vert) const {
  if (horz < vert) {
    return horz;
  } else {
    return vert;
  }
}

void GridSlot::RemoveAllComponents() {
  for (auto component : components_) {
    RemoveComponent(component);
  }
}

void GridSlot::RemoveComponent(cocos2d::ui::Widget *component) {
  if (HasComponent(component)) {
    components_.remove(component);
    this->removeChild(component);
  }
}

bool GridSlot::HasComponent(cocos2d::ui::Widget *component) const {
  return std::find(components_.begin(), components_.end(), component) != components_.end();
}

cocos2d::Rect GridSlot::area() const {
  return getBoundingBox();
}

unsigned int GridSlot::components_amount() const {
  return components_.size();
}

GridView *GridSlot::get_grid_view() {
  return grid_view_;
}

const Position &GridSlot::grid_position() const {
  return grid_position_;
}

}
