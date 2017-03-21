/*
 * Frederico Miguel Santos - frederico.miguel.santos@gmail.com
 * CAMBADA robotic soccer team - www.ieeta.pt/atri/cambada
 * University of Aveiro
 * Copyright (C) 2009
 *
 * This file is part of RTDB middleware.
 * http://code.google.com/p/rtdb/
 *
 * RTDB middleware is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RTDB middleware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RTDB middleware.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdio.h>
#include <signal.h>
#include <boost/thread.hpp>
#include "nuflie/rtdb/rtdb_api.h"
#include "nuflie/rtdb/rtdb_user.h"
#include "nuflie/world_model/station2UAVInfo.h"
#include <ros/ros.h>



// *************************
//   main function
// *************************
int main(int argc, char **argv)
{
    nuflie::station2UAVInfo code;
    code.code=0;
     float a=0;
    while(1)
    {
       printf("the size of data is %d \n",sizeof(a));
 
    }

    return 0;


}


