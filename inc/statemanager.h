/*********************************************************************
 _____ _            __    __      _ _                                 
/__   \ |__   ___  / / /\ \ \__ _| | | __   /\  /\___  _ __ ___   ___ 
  / /\/ '_ \ / _ \ \ \/  \/ / _` | | |/ /  / /_/ / _ \| '_ ` _ \ / _ \
 / /  | | | |  __/  \  /\  / (_| | |   <  / __  / (_) | | | | | |  __/
 \/   |_| |_|\___|   \/  \/ \__,_|_|_|\_\ \/ /_/ \___/|_| |_| |_|\___|
                                                                      
----------------------------------------------------------------------
By: Joseph Deming & Hunter Craig

Version: alpha-0.1.5


***********************************************************************/


#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "raylib.h"
#include "raymath.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Typedefs for State and Statehandler
typedef unsigned int (*Command)();
typedef unsigned int (*CommandFl)(float);

typedef struct {
    Command init;
    CommandFl update;
    CommandFl draw;
    Command destroy;
} State;

typedef struct {
    State **stack;
    int capacity;
    int top;
} StateManager;

// int InitState (StateManager *statemanager);
// int FreeState (StateManager *statemanager);
// int PushState (StateManager *statemanager);
// int PopState (StateManager *statemanager);
// State *GetTopState (StateManager *statemanager);
// int UpdateState (StateManager *statemanager);
// int DrawState (StateManager *statemanager);
#endif