#include "grid_slot.h"
#include "grid_view.h"
#include <algorithm>

namespace cocosgridview {

GridSlot::GridSlot(GridView *grid_view, const Position &grid_position):
      grid_view_(grid_view),
      grid_position_(grid_position) {
}

void GridSlot::Align() {
  area_ = grid_view_->calculate_slot_area(grid_position_);
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
  grid_view_->addChild(component);
}

void GridSlot::AlignComponents() {
  for (auto component : components_) {
    AlignComponent(component);
  }
}

void GridSlot::AlignComponent(cocos2d::ui::Widget *component) {
  if (component) {
    float x = area_.getMidX();
    float y = area_.getMidY();
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
  float horz_scale = area_.size.width / component->getContentSize().width;
  float vert_scale = area_.size.height / component->getContentSize().height;
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
  while (components_.size() > 0) {
    auto component = components_.back();
    RemoveComponent(component);
  }
}

void GridSlot::RemoveComponent(cocos2d::ui::Widget *component) {
  if (HasComponent(component)) {
    components_.erase(std::remove(components_.begin(), components_.end(), component), components_.end());
    grid_view_->removeChild(component);
  }
}

bool GridSlot::HasComponent(cocos2d::ui::Widget *component) const {
  return std::find(components_.begin(), components_.end(), component) != components_.end();
}

cocos2d::Rect GridSlot::area() const {
  return area_;
}

unsigned int GridSlot::components_amount() const {
  return components_.size();
}

cocos2d::ui::Widget *GridSlot::get_component(unsigned int index) {
  if (index < components_amount()) {
    return components_[index];
  } else {
    return nullptr;
  }
}

const cocos2d::ui::Widget *GridSlot::get_component(unsigned int index) const {
  if (index < components_amount()) {
    return components_.at(index);
  } else {
    return nullptr;
  }
}

GridView *GridSlot::get_grid_view() {
  return grid_view_;
}

const Position &GridSlot::grid_position() const {
  return grid_position_;
}

}
