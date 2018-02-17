#include "Civilization.h"

#include "resource/DataManager.h"

#include <genie/dat/DatFile.h>
#include <genie/dat/Civ.h>
#include <genie/dat/Unit.h>
#include <genie/dat/DatFile.h>

Civilization::Civilization(const int civId, const genie::DatFile &dataFile) :
    m_civId(civId),
    m_data(dataFile.Civs.at(civId))
{
    for (const genie::Unit &unit : m_data.Units) {
        if (unit.Creatable.TrainLocationID <= 0) {
            continue;
        }
        if (unit.HideInEditor) {
            continue;
        }

        m_creatableUnits[unit.Creatable.TrainLocationID].push_back(&unit);
    }

    for (int i=0; i<dataFile.Techs.size(); i++) {
        const genie::Tech &research = dataFile.Techs.at(i);
        if (research.ResearchLocation <= 0) {
            continue;
        }
        if (research.Civ != m_civId) {
            continue;
        }

        m_techs[i] = research;
        m_researchAvailable[research.ResearchLocation].push_back(&m_techs.at(i));
    }

}

const std::vector<const genie::Unit *> Civilization::creatableUnits(int16_t creator) const
{
    if (creator != 118 && unit(creator).Class == genie::Unit::Civilian) {
        creator = 118;
    }

    if (m_creatableUnits.find(creator) == m_creatableUnits.end()) {
        return std::vector<const genie::Unit*>();
    }

    return m_creatableUnits.at(creator);
}

const std::vector<const genie::Tech *> Civilization::researchAvailableAt(int16_t creator) const
{
    if (m_researchAvailable.find(creator) == m_researchAvailable.end()) {
        return std::vector<const genie::Tech*>();
    }

    return m_researchAvailable.at(creator);
}

const genie::Unit &Civilization::unit(const uint16_t id) const
{
    if (id >= m_data.Units.size()) {
        std::cerr << "Invalid unit id " << id << std::endl;
        return nullUnit;
    }

    return m_data.Units.at(id);
}

const genie::Tech &Civilization::tech(const uint16_t id) const
{
    if (m_techs.find(id) == m_techs.end()) {
        return DataManager::nullTech;
    }

    return m_techs.at(id);
}