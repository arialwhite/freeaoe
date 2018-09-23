/*
    Copyright (C) 2018 Martin Sandsmark <martin.sandsmark@kde.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "core/Entity.h"
#include "core/ResourceMap.h"
#include "core/IAction.h"
#include <deque>
#include <map>

#include <genie/dat/UnitCommand.h>

class Civilization;
struct Player;

struct Task {
    Task(const genie::Task &t, uint16_t id) : data(&t), unitId(id) {}
    Task() = default;

    const genie::Task *data = nullptr;
    uint16_t unitId = 0; // for task group swapping

    bool operator==(const Task &other) const {
        return unitId == other.unitId && (
                (data && other.data && data->ID == other.data->ID) ||
                (data == other.data)
        );
    }
};

struct Unit : public Entity
{
    enum HardcodedTypes {
        TownCenter = 109,

        FemaleVillager = 293,

        MaleVillager = 83,
        MaleLumberjack = 123,
        MaleStoneMiner = 124,
        MaleHunter = 122,
        MaleFarmer = 259,
        MaleForager = 120,
        MaleFisherman = 56,
        MaleGoldMiner = 579,
        MaleShepherd = 592,
        MaleBuilder = 118,
        MaleRepairer = 156,

        Docket = 45,
        Castle = 82,
        Market = 84,

        ArcheryRange = 87,
        Barracks = 12,
        Monastery = 104,
        SiegeWorkshop = 49,
        Stable = 101,

        Dock = 45,

        Mill = 68,
        LumberCamp = 562,
        MiningCamp = 584,

        PalisadeWall = 72,
        StoneWall = 117,
        FortifiedWall = 155,
        Gate = 487,

        Farm = 50,

        Cobra = 748,
        VMDL = 206,
        FuriousTheMonkeyBoy = 860,
    };

    typedef std::shared_ptr<Unit> Ptr;

    struct Annex {
        Unit::Ptr unit;
        MapPos offset;
    };

    Unit() = delete;
    Unit(const Unit &unit) = delete;

    Unit(const genie::Unit &data_, const std::shared_ptr<Player> &player_, const std::shared_ptr<Civilization> &civilization_, const MapPtr &map);

    ~Unit();

    void setAngle(const float angle);

    void queueAction(const ActionPtr &action);
    void setCurrentAction(const ActionPtr &action);
    void clearActionQueue();
    const ActionPtr &currentAction() const { return m_currentAction; }

    void snapPositionToGrid();

    bool update(Time time) override;

    const std::vector<const genie::Unit *> creatableUnits();

    bool selected = false;
    int playerId;
    std::weak_ptr<Player> player;
    int constructors = 0;
    std::vector<Annex> annexes;
    std::shared_ptr<Civilization> civilization;

    ResourceMap resources;

    virtual ScreenRect rect() const;

    virtual void setCreationProgress(float progress);
    void increaseCreationProgress(float progress);
    float creationProgress() const;

    float hitPoints = 0;

    int garrisonedUnits = 0;

    std::unordered_set<Task> availableActions();

    void setUnitData(const genie::Unit &data_);
    const genie::Unit *data() const {return m_data; }

protected:
    void removeAction(const ActionPtr &action);
    int taskGraphicId(const genie::Task::ActionTypes taskType, const IAction::UnitState state);

    const genie::Unit *m_data = nullptr;
    GraphicPtr movingGraphics;
    ActionPtr m_currentAction;
    std::deque<ActionPtr> m_actionQueue;
    float m_creationProgress = 0.f;
};

namespace std {

template<> struct hash<Task>
{
    size_t operator()(const Task &b) const {
        return hash<int16_t>()(b.data->ID) ^ hash<uint16_t>()(b.unitId);
    }
};
}
