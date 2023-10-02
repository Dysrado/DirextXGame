#include "EngineTime.h"
EngineTime* EngineTime::sharedInstance = nullptr;
void EngineTime::initialize()
{// If there is no instance of class
    // then we can create an instance.
    if (sharedInstance == nullptr)
    {
        // We can access private members
        // within the class.
        EngineTime::sharedInstance = new EngineTime();

        // returning the instance pointer
    }
    LogFrameStart();
    LogFrameEnd();
    
}

double EngineTime::getDeltaTime()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(EngineTime::sharedInstance->start - EngineTime::sharedInstance->end).count() / 1000000.0f;
}

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
    delete this;
}

void EngineTime::LogFrameStart()
{
    EngineTime::sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
    EngineTime::sharedInstance->end = std::chrono::system_clock::now();
}
