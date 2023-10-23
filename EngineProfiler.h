#pragma once
#include "AUIScreen.h"
class EngineProfiler :
    public AUIScreen
{
public:
    void drawUI() override;

    EngineProfiler(String name);
    ~EngineProfiler();
};

