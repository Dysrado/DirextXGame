#pragma once
#include "AUIScreen.h"
class SceneOutliner :
    public AUIScreen
{
public:
    void drawUI() override;

    SceneOutliner(String name);
    ~SceneOutliner();
};

