#include "clsLoginScreen.hpp"
#include "Global.h"


int main()
{
    while(true)
    {
        if(!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }
    
}
