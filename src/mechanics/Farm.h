#pragma once

#include "Building.h"

class Map;

class FarmRender : public GraphicRender
{
public:
    FarmRender(const Size &size);

    void render(sf::RenderTarget &renderTarget, const ScreenPos screenPos, const RenderType pass) override;

private:
    sf::Texture m_texture;
    ScreenPos m_hotspot;
    Size m_size;
};


class Farm : public Building
{
    enum TerrainTypes {
        FarmFinished = 7,
        FarmDead = 8,
        FarmConstruct0 = 29,
        FarmConstruct1 = 30,
        FarmConstruct2 = 31,
    };

public:
    Farm(const genie::Unit &data_, const std::shared_ptr<Player> &player, UnitManager &unitManager);
    void setCreationProgress(float progress) override;
    bool update(Time time) override;

    GraphicRender &renderer() override { return m_farmRenderer; }
    ScreenRect rect() const override;

private:
    void setTerrain(const TerrainTypes terrainToSet);

    int m_currentTerrain = -1;
    bool m_updated = true;
    FarmRender m_farmRenderer;
};

