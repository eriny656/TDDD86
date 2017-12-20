/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    /* General constructor */
    Junk();

    /* Construct Junk at point of parameter Robot */
    Junk(Robot c);

    /* Destructor */
    ~Junk();

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;

    /* Overrides Robot move function to idle at position */
    void moveTowards(const Unit& u) override;

    /* Overrides Robot attacks function to idle */
    bool attacks(const Unit& u) const override;

    /* Overrides Robot isJunk to return True */
    bool isJunk() const override;

    /* Overrides Robot clone */
    Junk *clone() override;

};

#endif // JUNK_H
