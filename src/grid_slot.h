#ifndef COCOSGRIDVIEW_GRID_SLOT_H
#define COCOSGRIDVIEW_GRID_SLOT_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include "position.h"

namespace cocosgridview {

// Forward reference to GridView.
class GridView;

///
/// GridSlot class.
///
class GridSlot: public cocos2d::ui::Widget {
public:

  static GridSlot* create(GridView *grid_view, const Position &grid_position);
  virtual ~GridSlot() {}

  void Align();

  void AddComponent(cocos2d::ui::Widget *component);
  void RemoveComponent(cocos2d::ui::Widget *component);

  unsigned int components_amount() const;

  GridView *get_grid_view();
  const Position &grid_position() const;

protected:

  GridSlot(GridView *grid_view, const Position &grid_position);
  virtual void onSizeChanged() override;

private:

  bool HasComponent(cocos2d::ui::Widget *component) const;
  void InsertComponent(cocos2d::ui::Widget *component);
  void AlignComponents();
  void AlignComponent(cocos2d::ui::Widget* component);

private:

  GridView *grid_view_ = nullptr;
  Position grid_position_;
  std::list<cocos2d::ui::Widget*> components_;

};

}

#endif
