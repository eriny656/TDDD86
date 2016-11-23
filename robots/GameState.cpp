/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include<iostream>
#include "GameState.h"
#include "utilities.h"
#include "constants.h"
using namespace std;

GameState::GameState(){}

GameState::GameState(int numberOfRobots) {
    for (int i = 0; i < numberOfRobots; i++) {
        robots.push_back(new Robot());
    }
    teleportHero();
}

// TODO: learn about operators and memory leaks.
GameState::GameState(const GameState &gs){
    this->operator =(gs);
}

GameState::~GameState(){
    for(auto i = robots.begin(); i != robots.end(); ++i){
        delete *i;
    }
}

GameState GameState::operator=(GameState gs) {
    robots.clear();

    // Creates copy of old robots in gs and inserts in new gameState
    for(Robot *r: gs.robots) {
        this->robots.push_back(new Robot(*r));
    }
    this->hero = gs.hero;

    return 0;
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




inline const char * const BoolToString(bool b)
{
  return b ? "true" : "false";
}



int GameState::countCollisions() {
    int numberDestroyed = 0;
    unsigned int i = 0;
    while (i < robots.size()) {
        bool collision = (countRobotsAt(*robots[i]) > 1);
        if (collision) {
            if (!robots[i]->isJunk()) {
                robots[i] = new Junk(*robots[i]);
                numberDestroyed++;
            }
        }
        i++;
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
