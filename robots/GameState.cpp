/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"

GameState::GameState(){}

GameState::GameState(int numberOfRobots) {
    for (int i = 0; i < numberOfRobots; i++) {
        Robot *robot = new Robot();

        while(!isEmpty(*robot)) {
            delete robot;
            robot = new Robot();
        }

        robots.push_back(robot);
    }
    teleportHero();
}

GameState::GameState(const GameState &gs){
    // Create new instances of existing units in copy
    // duplicate value (no "shallow copy")

    // our hero is not a pointer value, so no clone needed
    hero = gs.hero;

    for(Robot *robot: gs.robots) {
        robots.push_back(robot->clone());
    }
}

GameState::~GameState(){
    clearRobots();
}

GameState &GameState::operator=(const GameState &gs) {
    clearRobots();

    // Creates copy of old robots in gs and inserts in new GameState
    for(Robot *r: gs.robots) {
        robots.push_back(r->clone());
    }

    hero = gs.hero;

    return *this;
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    for (size_t i = 0; i < robots.size(); ++i)
        robots[i]->draw(scene);
    hero.draw(scene);
}

void GameState::teleportHero() {
    do {
        hero.teleport();
    }
    while (!isEmpty(hero));

}

void GameState::moveRobots() {
    for (unsigned int i = 0; i < robots.size(); i++)
        robots[i]->moveTowards (hero);
}

int GameState::countCollisions() {
    int numberDestroyed = 0;

    for (unsigned i = 0; i < robots.size(); ++i){
        bool collision = (countRobotsAt(*robots[i]) > 1);

        // Will only create junk and give points when
        // there is a collision with a non-junk robot
        if (collision && !robots[i]->isJunk()) {
            Robot *oldRobot = robots[i];
            robots[i] = new Junk(*oldRobot);
            delete oldRobot;
            numberDestroyed++;
        }
    }
    return numberDestroyed;
}

bool GameState::anyRobotsLeft() const {
    for(unsigned int i = 0; i < robots.size(); ++i){
        if(!robots[i]->isJunk()) {
            return true;
        }
    }
    return false;
}

bool GameState::heroDead() const {
    return !isEmpty(hero);
}

bool GameState::isSafe(const Unit& unit) const {
    for (unsigned int i = 0; i < robots.size(); i++){
        if (robots[i]->attacks(unit)) return false;
        if (!isEmpty(unit)) return false;
    }
    return true;
}

void GameState::moveHeroTowards(const Unit& dir) {
    hero.moveTowards(dir);
}

Hero GameState::getHero() const {return hero;}

/*
 * Free of robots and junk only
 */
bool GameState::isEmpty(const Unit& unit) const {
    return (countRobotsAt(unit) == 0);
}

/*
 * How many robots are there at unit?
 */
int GameState::countRobotsAt(const Unit& unit) const {
    int count = 0;
    for (size_t i = 0; i < robots.size(); ++i) {
        if (robots[i]->at(unit))
            count++;
    }
    return count;
}

void GameState::clearRobots() {
    for(auto i = robots.begin(); i != robots.end(); ++i){
        delete *i;
    }
    robots.clear();
}
