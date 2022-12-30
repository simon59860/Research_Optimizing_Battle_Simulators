#pragma once
#include "Health.h"
#include "MeleeAttack.h"

class AgentBasePooler;
class Cell;

class AgentBase
{
public:
	AgentBase();
	~AgentBase();

	AgentBase(const AgentBase& other) = delete;
	AgentBase& operator=(const AgentBase& other) = delete;
	AgentBase(AgentBase&& other) = delete;
	AgentBase& operator=(AgentBase&& other) = delete;
	
	void SetCell(Cell* pCell) { m_pCell = pCell; };

	void Enable(int teamId, const Elite::Vector2& position, float radius, const Elite::Color& color, float healthAmount, float damage, float attackSpeed, float attackRange, float speed);
	
	bool GetIsEnabled() { return m_IsEnabled; };

	const Elite::Vector2& GetPosition() { return m_Position; };
	int GetTeamId() { return m_TeamId; };

	void Update(float dt, AgentBasePooler* pAgentBasePooler, bool separation, bool checkCell);
	void CheckIfCellChanged(AgentBasePooler* pAgentBasePooler);
	void Render();

	void Damage(float damageAmount) { m_Health.Damage(damageAmount); };

private:
	//components
	Health m_Health{};
	MeleeAttack m_MeleeAttack{};

	//const data (not actually const cause can be changed when reenabling)
	int m_TeamId{};
	float m_Speed;

	float m_Radius{};
	Elite::Color m_Color{};

	//temp data
	AgentBase* m_pTargetAgent{};
	Elite::Vector2 m_TargetPosition{}; //used if no targetagent

	Elite::Vector2 m_Velocity{};
	Elite::Vector2 m_Position{};	

	bool m_IsEnabled{};

	Cell* m_pCell;

	std::vector<AgentBase*> m_Neighbors{};

	int m_NeighborCount{};

	void CalculateVelocity(bool separation);

	void Disable();

	bool Move(float dt);

	void FindTarget(AgentBasePooler* pAgentBasePooler);

	void CheckCell(AgentBasePooler* pAgentBasePooler, int row, int col);
};
