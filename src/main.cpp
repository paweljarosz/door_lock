#include <cstddef>
#include <cstdint>
#include "hFramework.h"
#include "hCloudClient.h"

#define opened 2500      
#define closed 800   

bool status;

void cfgHandler()                               //UI
{
    
    platform.ui.loadHtml({Resource::WEBIDE, "/ui.html"});
}

void onButtonEvent(hId id, ButtonEventType type)
{

	if (id == "bo") 
	{
		if (type == ButtonEventType::Pressed) 
		{
		    hServoModule.enablePower();
            hServoModule.servo1.setWidth(opened);
            hSens1.pin1.write(0);
            sys.delay(1000);
            hSens1.pin3.write(1);
            hServoModule.disablePower();
		}
	}
	if (id == "bc") 
	{
		if (type == ButtonEventType::Pressed) 
		{
		    hServoModule.enablePower();
            hServoModule.servo1.setWidth(closed);
            hSens1.pin3.write(0);
            sys.delay(1000);
            hSens1.pin1.write(1);
            hServoModule.disablePower();
		}
	}
}

void hMain()
{
    status=false;
	platform.begin(&RPi);
	platform.ui.setProjectId("@@@PROJECT_ID@@@");
	platform.ui.configHandler = cfgHandler;
	platform.ui.onButtonEvent = onButtonEvent;
    hServoModule.setVoltage6V();
    hServoModule.enablePower();
    hServoModule.servo1.calibrate(-90,800,90,2400);
    hSens1.pin1.setOut();
    hSens1.pin3.setOut();
    hSens1.pin1.write(0);
    hSens1.pin3.write(1);
}
