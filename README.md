cocos-grid-view
===

## What is it?

Cocos Grid View is a [Cocos2d-x](http://cocos2d-x.org/) component for laying out components (widgets) in a grid system.
It can be configured to have how many rows and columns are needed. You can place in a same *cell* how many components
you want.

## How to use

### Installation

You can choose one of the following options to install this project inside your project:

#### Downloading files

* Download the repo.

* Extract and paste it inside your project.

* Configure CMakeLists.txt. [See how](#configuring-cmakelists)

#### Adding as git submodule

* Open the terminal

* cd into your project directory

* Type the command:
`git submodule add https://github.com/bruno02221/cocos-grid-view.git`.

* Configure CMakeLists.txt. [See how](#configuring-cmakelists)

### Configuring CMakeLists
<a name="configuring-cmakelists"></a>

* Add source files to your include directory:

```cmake
include_directories(
    /usr/local/include/GLFW
    /usr/include/GLFW
    ${COCOS2D_ROOT}/cocos
    ${COCOS2D_ROOT}/cocos/platform
    ${COCOS2D_ROOT}/cocos/audio/include/
    Classes
    cocos-grid-view/src # Add this line
)
```

* Create sources set

```cmake
set(COCOS_GRID_VIEW_SRC)
file(GLOB_RECURSE COCOS_GRID_VIEW_SRC
  cocos-grid-view/src/cocosgridview/*.h
  cocos-grid-view/src/cocosgridview/*.hpp
  cocos-grid-view/src/cocosgridview/*.cpp
  cocos-grid-view/src/cocosgridview/*.cc
  cocos-grid-view/src/cocosgridview/*.c
)
```

* Add your sources set to the project

```cmake
set(GAME_SRC
  Classes/AppDelegate.cpp
  Classes/HelloWorldScene.cpp
  ${PLATFORM_SPECIFIC_SRC}
  ${COCOS_GRID_VIEW_SRC} # Add this line
)
```

### API

* Include component

```c++
#include <cocosgridview/grid_view.h>
```

* Namespace 

```c++
using namespace cocosgridview;
```


* Create component

```c++
/// {5, 4} -> The grid dimension (5 rows and 4 columns);
/// 10 -> gap between items.
auto grid = GridView::create({5, 4}, 10);
 // Congigure the grid size and position as you want.
grid->setContentSize(theGridSize);
grid->setPosition(theGridPosition);
```

* Populate component


```c++
/// {2, 3} -> The grid position to add the component into.
/// myComponent -> The component to add to the grid.
grid->AddComponent({2, 3}, myComponent1);
```

* Add the grid to your scene

```c++
myScene->addChild(grid);
```

### License

[MIT License](https://opensource.org/licenses/MIT)
