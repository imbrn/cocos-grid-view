#ifndef COCOSGRIDVIEW_GRID_VIEW_H
#define COCOSGRIDVIEW_GRID_VIEW_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <vector>
#include "dimension.h"
#include "position.h"
#include "grid_slot.h"

namespace cocosgridview
{

///
/// GridView class.
///
class GridView : public cocos2d::ui::Widget {
protected:

  GridView(const Dimension &dimension, float items_gap);

public:

  static GridView *create(const Dimension &dimension, float items_gap = 10);
  virtual ~GridView() {}

  void AddComponent(const Position &at, cocos2d::ui::Widget *component);
  void RemoveComponent(const Position &at, cocos2d::ui::Widget *component);

  cocos2d::Size available_size() const;
  cocos2d::Size slot_size() const;
  cocos2d::Rect slot_area(const Position &at) const;

  unsigned int rows() const;
  unsigned int cols() const;
  const Dimension &dimension() const;
  float items_gap() const;

  void set_dimension(const Dimension &dimension);
  void set_items_gap(float items_gap);

protected:

  virtual void onSizeChanged() override;

private:

  void RecicleSlots();
  void AddSlot(GridSlot *slot);
  void RemoveSlots();
  void PositionSlots();

  GridSlot *get_slot(const Position &at);

private:

  Dimension dimension_;
  float items_gap_;
  std::vector<GridSlot*> slots_;

};
}

#endif
