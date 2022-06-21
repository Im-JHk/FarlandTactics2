#include "Stdafx.h"
#include "MapData.h"
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"

void MapData::Init(void)
{
}

void MapData::Release(void)
{
	for (int i = 0; i < mqMap.size(); i++) {
		SAFE_DELETE(mqMap.front());
		mqMap.pop();
	}
}

void MapData::SaveMapData(const vector<Tile*> vTile, const vector<Player*> vPlayer, 
	const vector<Enemy*> vEnemy, const int row, const int col, const int stageNum)
{
	Json::Value root;
	Json::Value stageInfo;
	Json::Value tileInfo;
	Json::Value playerInfo;
	Json::Value enemyInfo;
	string stage;
	string strStage = "stage_";
	int intStage = 1;
	
	for (auto iter : vTile) {
		tileInfo.clear();
		tileInfo["type"] = static_cast<int>(iter->GetType());
		tileInfo["center_x"] = iter->GetCenter().x;
		tileInfo["center_y"] = iter->GetCenter().y;
		tileInfo["width"] = iter->GetSize().x;
		tileInfo["height"] = iter->GetSize().y;
		tileInfo["row_max"] = row;
		tileInfo["column_max"] = col;
		tileInfo["row"] = iter->GetRow();
		tileInfo["column"] = iter->GetCol();
		tileInfo["index"] = iter->GetIndex();
		tileInfo["tile_frameX"] = iter->GetTileFrameX();
		tileInfo["floor_frameX"] = iter->GetFloorFrameX();
		tileInfo["floor_level"] = iter->GetFloorLevel();
		stageInfo["tile_info"].append(tileInfo);
	}
	for (auto iter : vPlayer) {
		playerInfo.clear();
		playerInfo["name"] = iter->GetName();
		playerInfo["hp_max"] = iter->GetMaxHp();
		playerInfo["mp_max"] = iter->GetMaxMp();
		playerInfo["hp"] = iter->GetCurrentHp();
		playerInfo["mp"] = iter->GetCurrentMp();
		playerInfo["atk"] = iter->GetPower();
		playerInfo["mgc"] = iter->GetMGPower();
		playerInfo["def"] = iter->GetDeffence();
		playerInfo["mgc_def"] = iter->GetMGDeffence();
		playerInfo["is_die"] = static_cast<int>(iter->GetIsDie());
		playerInfo["row"] = iter->GetRowAndCol().x;
		playerInfo["column"] = iter->GetRowAndCol().y;
		playerInfo["index"] = iter->GetIndex();
		playerInfo["direction"] = static_cast<int>(iter->GetDirection());
		playerInfo["state"] = static_cast<int>(iter->GetState());
		playerInfo["center_x"] = iter->GetCenter().x;
		playerInfo["center_y"] = iter->GetCenter().y;
		stageInfo["player_info"].append(playerInfo);
	}
	for (auto iter : vEnemy) {
		enemyInfo.clear();
		enemyInfo["name"] = iter->GetName();
		enemyInfo["hp_max"] = iter->GetMaxHp();
		enemyInfo["mp_max"] = iter->GetMaxMp();
		enemyInfo["hp"] = iter->GetCurrentHp();
		enemyInfo["mp"] = iter->GetCurrentMp();
		enemyInfo["atk"] = iter->GetPower();
		enemyInfo["mgc"] = iter->GetMGPower();
		enemyInfo["def"] = iter->GetDeffence();
		enemyInfo["mgc_def"] = iter->GetMGDeffence();
		enemyInfo["is_die"] = static_cast<int>(iter->GetIsDie());
		enemyInfo["row"] = iter->GetRowAndCol().x;
		enemyInfo["column"] = iter->GetRowAndCol().y;
		enemyInfo["index"] = iter->GetIndex();
		enemyInfo["direction"] = static_cast<int>(iter->GetDirection());
		enemyInfo["state"] = static_cast<int>(iter->GetState());
		enemyInfo["center_x"] = iter->GetCenter().x;
		enemyInfo["center_y"] = iter->GetCenter().y;
		stageInfo["enemy_info"].append(enemyInfo);
	}

	root["stage"] = intStage;
	root["stage_info"]["row_max"] = row;
	root["stage_info"]["column_max"] = col;
	root["stage_info"] = stageInfo;

	JSONDATAMANAGER->saveJsonFile("stage.json", root);
}

void MapData::LoadMapData(vector<Tile*> &vTile, vector<Player*> &vPlayer, vector<Enemy*> &vEnemy, int &row, int &col, int &num)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("stage.json");
	Map *map = new Map;
	map->SetStageNumber(root["stage"].isInt());
	map->SetColumn(root["stage_info"]["column_max"].asInt());
	map->SetRow(root["stage_info"]["row_max"].asInt());
	if (root["stage_info"]["tile_info"].isArray()) {
		for (auto iter = root["stage_info"]["tile_info"].begin(); iter != root["stage_info"]["tile_info"].end(); ++iter) {
			Tile* tile = new Tile;
			tile->init(
				static_cast<eObjectType>((*iter)["type"].asInt()),
				PointMake((*iter)["center_x"].asInt(), (*iter)["center_y"].asInt()),
				PointMake((*iter)["width"].asInt(), (*iter)["height"].asInt()),
				PointMake(root["stage_info"]["row_max"].asInt(), root["stage_info"]["column_max"].asInt()),
				PointMake((*iter)["row"].asInt(), (*iter)["column"].asInt()),
				(*iter)["index"].asInt(),
				(*iter)["tile_frameX"].asInt(),
				(*iter)["floor_frameX"].asInt(),
				(*iter)["floor_level"].asInt()
			);
			map->SetVecAddTile(tile);
		}
	}
	if (root["stage_info"]["player_info"].isArray()) {
		for (auto iter = root["stage_info"]["player_info"].begin(); iter != root["stage_info"]["player_info"].end(); ++iter) {
			Player* player = new Player;
			player->init(
				(*iter)["name"].asString(),
				static_cast<eDirection>((*iter)["direction"].asInt()),
				static_cast<eState>((*iter)["type"].asInt()),
				PointMake((*iter)["center_x"].asInt(), (*iter)["center_y"].asInt()),
				PointMake((*iter)["row"].asInt(), (*iter)["column"].asInt()),
				PointMake((*iter)["hp"].asInt(), (*iter)["mp"].asInt()),
				PointMake((*iter)["hp_max"].asInt(), (*iter)["mp_max"].asInt()),
				PointMake((*iter)["atk"].asInt(), (*iter)["mgc"].asInt()),
				PointMake((*iter)["def"].asInt(), (*iter)["mgc_def"].asInt()),
				(*iter)["index"].asInt(),
				static_cast<bool>((*iter)["is_die"].asInt())
			);
			map->SetVecAddPlayer(player);
		}
	}
	if (root["stage_info"]["enemy_info"].isArray()) {
		for (auto iter = root["stage_info"]["enemy_info"].begin(); iter != root["stage_info"]["enemy_info"].end(); ++iter) {
			Enemy* enemy = new Enemy;
			enemy->init(
				(*iter)["name"].asString(),
				static_cast<eDirection>((*iter)["direction"].asInt()),
				static_cast<eState>((*iter)["type"].asInt()),
				PointMake((*iter)["center_x"].asInt(), (*iter)["center_y"].asInt()),
				PointMake((*iter)["row"].asInt(), (*iter)["column"].asInt()),
				PointMake((*iter)["hp"].asInt(), (*iter)["mp"].asInt()),
				PointMake((*iter)["hp_max"].asInt(), (*iter)["mp_max"].asInt()),
				PointMake((*iter)["atk"].asInt(), (*iter)["mgc"].asInt()),
				PointMake((*iter)["def"].asInt(), (*iter)["mgc_def"].asInt()),
				(*iter)["index"].asInt(),
				static_cast<bool>((*iter)["is_die"].asInt())
			);
			map->SetVecAddEnemy(enemy);
		}
	}

	mqMap.push(map);
}

void MapData::MakeStringAttachInt(string & output, string str, int i)
{
	char num[10];
	_itoa_s(i, num, 10);
	output += str;
	output += num;
}
