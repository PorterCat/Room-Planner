#ifndef DRAGTOOL_H
#define DRAGTOOL_H

#include "itool.h"

class DragTool : public ITool
{
	friend RoomEditor;
  public:
	DragTool();
	~DragTool();
	void prepareScene(RoomEditor* scene, ITool* tool) override;
};

#endif // DRAGTOOL_H
