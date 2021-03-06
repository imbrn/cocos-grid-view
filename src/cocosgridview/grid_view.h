#ifndef COCOSGRIDVIEW_GRID_VIEW_H
#define COCOSGRIDVIEW_GRID_VIEW_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <vector>
#include "position.h"

namespace cocosgridview {

///
/// GridView class.
///
class GridView : public cocos2d::ui::Widget {
public:
  static GridView *create(unsigned int rows, unsigned int cols, float gap = 10);
  GridView(unsigned int rows, unsigned int cols, float gap);
  virtual ~GridView() {}
  virtual bool init() override;

  cocos2d::Point get_slot_origin(const Position &at) const;
  cocos2d::Rect get_slot_area(const Position &at) const;
  cocos2d::Size get_slot_size(const Position &at) const;

  unsigned int rows();
  unsigned int cols();
  void set_dimension(unsigned int rows, unsigned int cols);

  float get_gap() const;
  void set_gap(float gap);

  Position get_slot(const std::function<bool(Position)> &criteria) const;
  Position get_slot(const cocos2d::Point &location) const;

  cocos2d::ui::Widget *get_component(const std::function<bool(Position, cocos2d::ui::Widget*)> &criteria);
  cocos2d::ui::Widget *get_component(const cocos2d::Point &location);
  cocos2d::ui::Widget *get_component(const Position &at);
  void set_component(const Position &at, cocos2d::ui::Widget *component);
  void RemoveAllComponents();

  void Iterate(const std::function<void(const Position &at, cocos2d::ui::Widget *)> &function);
  void IteratePositions(const std::function<void(const Position &at)> &function);

  const std::vector<Position> positions() const;

protected:
  virtual void onSizeChanged() override;

private:
  void DoInit();

  void RecicleComponents();
  void ReciclePosition(const Position &at, std::vector<std::vector<cocos2d::ui::Widget *>> &new_components);
  void DiscardComponent(const Position &at);
  void KeepComponent(const Position &at, std::vector<std::vector<cocos2d::ui::Widget *>> &new_components);
  void RemoveComponent(const Position &at, cocos2d::ui::Widget *component);
  void AddComponent(const Position &at, cocos2d::ui::Widget *component);

  void ScaleComponents();
  void ScaleComponent(const Position &at);
  void DoScaleComponent(const Position &at, cocos2d::ui::Widget *component);
  void DoScaleComponent(cocos2d::ui::Widget *component, const cocos2d::Size &size);
  void AlignComponents();
  void AlignComponent(const Position &at);
  void DoAlignComponent(const Position &at, cocos2d::ui::Widget *component);

  bool IsValidPosition(const Position &at) const;

 private:
  unsigned int rows_;
  unsigned int cols_;
  float gap_;
  std::vector<std::vector<cocos2d::ui::Widget *>> components_;
};
}

#endif
