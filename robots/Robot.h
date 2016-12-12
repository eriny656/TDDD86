/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
public:
    /* General constructor inherited from Unit */
    Robot();

    /* Constructor at point of parameter Unit */
    Robot(Unit c);

    /* Destructor */
    virtual ~Robot();

    /* Draws Robot to scene */
    void draw(QGraphicsScene* scene) const;

    /* Shows if unit is subclass Junk; returns False if not overriden*/
    virtual bool isJunk();
};

#endif // ROBOT_H
