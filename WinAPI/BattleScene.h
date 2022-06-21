#pragma once
#include "GameNode.h"

class Map;
class MapData;
class AStar;
class Player;
class Enemy;
class Range;
class Button;

class BattleScene : public GameNode
{
private:
	MapData* mcMapdata;
	Map* mcCurrMap;
	AStar* mcAStar;
	Range* mcRange;

	map<string, void(*) (void)> mmCBFunc;
	vector<Button*> mvBTN;
	vector<Tile*> mvTile;
	vector<Player*> mvPlayer;
	vector<Enemy*> mvEnemy;
	deque<int> mqPath;
	set<int> msTile;
	set<int> msMoveRange;
	set<int> msAttackRange;
	set<int> msSpellRange;
	set<int> msSpellHitRange;

	eObjectType meCurrObj;
	POINT mtAttackPoint;

	RECT mtCameraRect;
	POINT mtCameraPos;

	int miAttackHitIndex;

	int miStage;
	int miRow;
	int miCol;
	int miStart;
	int miEnd;

	int miCurrTile;
	int miTileIndex;
	int miPickTileIndex;

	int miEnemyBehaviorCount;
	int miTurnCount;

	bool mbIsMoveTile;

	bool mbIsAddPlayer;
	bool mbIsAddEnemy;
	bool mbPlayerExist;

	bool mbIsPathOn;
	bool mbIsMoveOn;
	bool mbIsStartMove;

	bool mbIsAttackRangeOn;
	bool mbIsAttackHitRangeOn;

	bool mbIsSpellRangeOn;
	bool mbIsSpellHitRangeOn;
	
	bool mbIsPlayerTurn;
	bool mbIsGameOver;
	bool mbIsGameEnd;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void LoadTheMapInfo();

	bool OnTheTile(eMouseEventType type);

	//Move
	eDirection FindDirection(int prev, int next);
	void StartAStar();
	void ClearMove(eObjectType type, int nextIndex);
	void ClearAttack();
	void ClearSpell();
	void ClearPhase();
	void ClearAllButton(const char* str = "");

	//CallBack Function
	void MoveCharacter(eObjectType type);
	void ShowInfomation(int index);

	void DoAttackPlayer(void);
	void DoSpellPlayer(void);

	void EffectIsStart(int evType, int atkType, int rcvType, int index);
	void EffectIsEnd(int evType, int rcvType);

	void AttackButton(void);
	void SpellButton(void);
	void CancelButton(void);

	void ShowAttackRange(void);
	void ShowSpellRange(void);

	void SelectUnit(int index);
	void SelectMoveTile(int dest);
	void SelectAttackType(int index);
	void SelectAttackTile(int dest);
	void SelectSpellTile(int dest); 

	void TurnButton();
	void EndOfTurn();

	BattleScene() {}
	~BattleScene() {}
};