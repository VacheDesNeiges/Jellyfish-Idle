#include "GameDataAccess.hpp"
#include "GameSystems.hpp"
#include "InputHandler.hpp"
#include "TextureAtlas.hpp"
#include "UIAbilitiesPanel.hpp"
#include "UIBuildingsPanel.hpp"
#include "UIDepthPanel.hpp"
#include "UIGardenPanel.hpp"
#include "UIJobsPanel.hpp"
#include "UINotification.hpp"
#include "UIOctopusPanel.hpp"
#include "UIResearchPanel.hpp"
#include "UIRessourcesPanel.hpp"

#include <memory>

class UIManager : public GameDataAccess
{
  public:
    void renderUI() const;
    void bindInputHandler(const std::shared_ptr<InputHandler> &);

    void setAtlas(TextureAtlas);

  private:
    std::shared_ptr<InputHandler> inputHandler = nullptr;

    TextureAtlas atlas;

    UIRessourcesPanel ressourcesPanel;
    UIBuildingPanel buildingsPanel;
    UIJobsPanel jobsPanel;
    UIAbilitiesPanel abilitiesPanel;
    UIResearchPanel researchPanel;
    UIDepthPanel depthPanel;
    UIOctopusPanel octopusPanel;
    UIGardenPanel gardenPanel;
    UINotification notifications;
};
