#pragma once
#include "AUIScreen.h"
class InspectorWindow :
    public AUIScreen
{
public:
    void drawUI() override;


    InspectorWindow(String name);
    ~InspectorWindow();

    
};

