#pragma once
#include "AUIScreen.h"
#include "GameObjectManager.h"
class MenuScreen :
    public AUIScreen
{
public:
    void drawUI() override;

    MenuScreen(String name);
    ~MenuScreen();
private:
};

