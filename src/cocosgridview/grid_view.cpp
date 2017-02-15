#include "grid_view.h"
#include <climits>

namespace cocosgridview {

GridView *GridView::create(unsigned int rows, unsigned int cols, float gap) {
  GridView *obj = new GridView(rows, cols, gap);
  if (obj->init()) {
    obj->autorelease();
    return obj;
  } else {
    delete obj;
    return nullptr;
  }
}

GridView::GridView(unsigned int rows, unsigned int cols, float gap) : rows_(rows), cols_(cols), gap_(gap) {
}

bool GridView::init() {
  if (!cocos2d::ui::Widget::init())
    return false;
  DoInit();
  return true;
}

void GridView::DoInit() {
  components_ = std::vector<std::vector<cocos2d::ui::Widget*>>(rows_, std::vector<cocos2d::ui::Widget*>(cols_));
}

cocos2d::Rect GridView::get_slot_area(const Position &at) const {
  auto size = get_slot_size();
  unsigned int row = rows_ - at.row - 1;
  unsigned int col = at.col;
  return {(col * size.width) + (col * gap_), (row * size.height) + (row * gap_), size.width, size.height};
}

cocos2d::Size GridView::get_slot_size() const {
  float available_width = getContentSize().width - ((cols_ - 1) * gap_);
  float available_height = getContentSize().height - ((rows_ - 1) * gap_);
  float w = available_width / cols_;
  float h = available_height / rows_;
  return {w, h};
}

void GridView::set_dimension(unsigned int rows, unsigned int cols) {
  rows_ = rows;
  cols_ = cols;
  RecicleComponents();
  ScaleComponents();
  AlignComponents();
}

void GridView::RecicleComponents() {
  std::vector<std::vector<cocos2d::ui::Widget*>> new_components(rows_, std::vector<cocos2d::ui::Widget*>(cols_));
  for (unsigned int row = 0; row < components_.size(); row++)
    for (unsigned int col = 0; col < components_[row].size(); col++)
      ReciclePosition({row, col}, new_components);
  components_ = new_components;
}

void GridView::ReciclePosition(const Position &at, std::vector<std::vector<cocos2d::ui::Widget *>> &new_components) {
  if (at.row > rows_ - 1 || at.col > cols_ - 1)
    DiscardComponent(at);
  else
    KeepComponent(at, new_components);
}

void GridView::DiscardComponent(const Position &at) {
  set_component(at, nullptr);
}

void GridView::KeepComponent(const Position &at, std::vector<std::vector<cocos2d::ui::Widget*>> &new_components) {
  new_components[at.row][at.col] = components_[at.row][at.col];
}

float GridView::get_gap() const {
  return gap_;
}

void GridView::set_gap(float gap) {
  gap_ = gap;
  ScaleComponents();
  AlignComponents();
}

cocos2d::ui::Widget *GridView::get_component(const Position &at) {
  return components_[at.row][at.col];
}

void GridView::set_component(const Position &at, cocos2d::ui::Widget *component) {
  auto old = get_component(at);
  if (old != component) {
    RemoveComponent(at, old);
    AddComponent(at, component);
  }
}

void GridView::RemoveComponent(const Position &at, cocos2d::ui::Widget *component) {
  if (component) {
    removeChild(component);
    components_[at.row][at.col] = nullptr;
  }
}

void GridView::AddComponent(const Position &at, cocos2d::ui::Widget *component) {
  if (component) {
    addChild(component);
    components_[at.row][at.col] = component;
    DoScaleComponent(at, component);
    DoAlignComponent(at, component);
  }
}

void GridView::onSizeChanged() {
  cocos2d::ui::Widget::onSizeChanged();
  ScaleComponents();
  AlignComponents();
}

void GridView::Iterate(const std::function<void(const Position &at, cocos2d::ui::Widget*)> &function) {
  IteratePositions([this, function](const Position &at) {
    function(at, get_component(at));
  });
}

void GridView::IteratePositions(const std::function<void(const Position &at)> &function) {
  for (unsigned int row = 0; row < rows_; row++)
    for (unsigned int col = 0; col < cols_; col++)
      function({row, col});
}

void GridView::ScaleComponents() {
  IteratePositions([this](const Position &at) { ScaleComponent(at); });
}

void GridView::ScaleComponent(const Position &at) {
  auto component = get_component(at);
  if (component) DoScaleComponent(at, component);
}

void GridView::DoScaleComponent(const Position &at, cocos2d::ui::Widget *component) {
  auto size = get_slot_size();
  DoScaleComponent(component, size);
}

void GridView::DoScaleComponent(cocos2d::ui::Widget *component, const cocos2d::Size &size) {
  float scale_vert = size.width / component->getContentSize().width;
  float scale_horz = size.height / component->getContentSize().height;
  float scale = MIN(scale_vert, scale_horz);
  component->setScale(scale);
}

void GridView::AlignComponents() {
  IteratePositions([this](const Position &at) {
    AlignComponent(at);
  });
}

void GridView::AlignComponent(const Position &at) {
  auto component = get_component(at);
  if (component) DoAlignComponent(at, component);
}

void GridView::DoAlignComponent(const Position &at, cocos2d::ui::Widget *component) {
  auto area = get_slot_area(at);
  component->setAnchorPoint({0.5, 0.5});
  component->setPosition({area.getMidX(), area.getMidY()});
}

unsigned int GridView::rows() {
  return rows_;
}

unsigned int GridView::cols() {
  return cols_;
}

}
