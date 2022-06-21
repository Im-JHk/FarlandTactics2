#pragma once

#define TileWidth 64
#define TileHeight 32
#define FloorHeight 16
#define MaxHpMp 1500.f
#define MaxHpMpWidth 150
#define MaxHpMpHeight 12

#define ButtonWidth 100
#define ButtonHeight 50
#define ButtonSize 16
#define ButtonTextGap 5
#define ButtonSmallWidth 50
#define ButtonSmallHeight 20
#define ButtonSmallSize 10
#define ButtonSmallTextGap 3

#define NumberStart 70
#define NumberUpMax 30
#define NumberDownMax 70
#define NumberWidth 8

enum class eWindowType
{
	MAIN = 0,
	POPUP,
	MODAL,
	MODALESS
};

enum class eMapObject
{
	TILE_1,
	TILE_2,
	TILE_3,
	TILE_4,
	TILE_5,
	TILE_6,
	KARIN,
	AL,
	ROGUE_1
};

enum class eDirection
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum class eState
{
	IDLE,
	MOVE,
	ATTACK,
	SPELL,
	ITEM,
	DAMAGE,
	DEATH
};

enum class eAttackType
{
	NONE,
	NORMAL,
	SPELL
};

enum class eChangeType
{
	UP,
	DOWN
};

enum class eMouseEventType
{
	NONE,
	OVER,
	DOWN,
	UP,
	CLICK,
	R_DOWN,
	R_UP
};

enum class eButtonShapeType
{
	RECTANGLE,
	ISOMETRIC
};

enum class eObjectType
{
	TILE = 0,
	BLOCK,
	ITEM,
	PLAYER,
	ENEMY,
	BUTTON,
	START,
	END,
	PATH
};

enum class eSelectableType
{
	ALL_NOT,
	ALL,
	BUTTON,
	TILE
};

enum class eSelectPhase
{
	ALL,
	UNIT_SELECT,
	MOVE_SELECT,
	ATK_TYPE_SELECT,
	ATTACK_SELECT,
	SPELL_SELECT,
	BUTTON_SELECT
};

enum class eAnimationType
{
	ONE,
	SECTION_LOOP,
	ALL_LOOP,
	REVERSE
};

enum class eEventType
{
	NONE,
	ATTACK,
	ATTACKED,
	DIE
};

typedef std::function<void(void)> VoidEventAsVoid;
typedef std::function<void(int)> VoidEventAsInt;
typedef std::function<void(int, int)> VoidEventAs2Int;
typedef std::function<void(int, int, int)> VoidEventAs3Int;
typedef std::function<void(int, int, int, int)> VoidEventAs4Int;
typedef pair<int, int> PAIR_INT;
typedef pair<float, float> PAIR_F;
typedef pair<POINT, POINT> DB_PT;

typedef struct tagIsometric
{
public:
	POINT point[4];
} ISOMETRIC;

typedef struct tagNode
{
	eObjectType type;
	tagNode* parent;
	int f, g, h;
	int index;
	int row;
	int col;
} NODE, *PNODE;

typedef struct tagButton
{
public:
	RECT rect;
	POINT center;
	POINT size;
	ImageBase* imageUp;
	ImageBase* imageDown;
} BTN;

inline ISOMETRIC MakeIsometric(POINT center, POINT size)
{
	ISOMETRIC tmp;
	tmp.point[0] = PointMake(center.x - size.x / 2, center.y);
	tmp.point[1] = PointMake(center.x, center.y - size.y / 2);
	tmp.point[2] = PointMake(center.x + size.x / 2, center.y);
	tmp.point[3] = PointMake(center.x, center.y + size.y / 2);
	return tmp;
}

inline ISOMETRIC MoveIsometric(ISOMETRIC iso, RECT rect)
{
	ISOMETRIC tmp;
	tmp.point[0].x = iso.point[0].x - rect.left;
	tmp.point[0].y = iso.point[0].y - rect.top;
	tmp.point[1].x = iso.point[1].x - rect.left;
	tmp.point[1].y = iso.point[1].y - rect.top;
	tmp.point[2].x = iso.point[2].x - rect.left;
	tmp.point[2].y = iso.point[2].y - rect.top;
	tmp.point[3].x = iso.point[3].x - rect.left;
	tmp.point[3].y = iso.point[3].y - rect.top;
	return tmp;
}

inline void DrawIsometric(HDC hdc, ISOMETRIC ismtr)
{
	MoveToEx(hdc, static_cast<int>(ismtr.point[0].x), static_cast<int>(ismtr.point[0].y), NULL);
	LineTo(hdc, static_cast<int>(ismtr.point[1].x), static_cast<int>(ismtr.point[1].y));
	LineTo(hdc, static_cast<int>(ismtr.point[2].x), static_cast<int>(ismtr.point[2].y));
	LineTo(hdc, static_cast<int>(ismtr.point[3].x), static_cast<int>(ismtr.point[3].y));
	LineTo(hdc, static_cast<int>(ismtr.point[0].x), static_cast<int>(ismtr.point[0].y));
}

inline void MakeStringAttachInt(string & output, string str, int i)
{
	char num[10];
	_itoa_s(i, num, 10);
	output += str;
	output += num;
}

inline void MakeUnitInfomationBox(vector<DB_PT> &v, int x, int y, int row, int col)
{
	/*POINT pos = { x, y };
	POINT sizeEdge = { 16, 16 };
	POINT sizeMidTB = { 32, 16 };
	POINT sizeLRMid = { 16, 32 };
	POINT sizeMidMid = { 32, 32 };

	DB_PT imageLT = { { 0,0 }, sizeEdge };
	DB_PT imageRT = { { 48,0 }, sizeEdge };
	DB_PT imageLB = { { 0,48 }, sizeEdge };
	DB_PT imageRB = { { 48,48 }, sizeEdge };

	DB_PT imageMT = { { 16,0 }, sizeMidTB };
	DB_PT imageMB = { { 16,48 }, sizeMidTB };
	DB_PT imageLM = { { 0,16 }, sizeLRMid };
	DB_PT imageRM = { { 48,16 }, sizeLRMid };

	DB_PT imageMM = { { 16,16 }, sizeMidMid };
	pos = { pos.x + 16, pos.y };
	for (int i = 1; i < 5; i++) {
		pos = { pos.x + 16 * i, pos.y };
		DB_PT render = make_pair(pos, sizeMidTB);
		v.push_back(render);
	}
	DB_PT image = make_pair(pos, size);
	DB_PT render = make_pair(pos, size);
	mvBox.push_back(make_pair(image, render));
	for (int i = 1; i < 5; i++) {
		pos = { pos.x + 16 * i, pos.y };
		size = { 32, 32 };
		image = make_pair(pos, size);
		render = make_pair(pos, size);
		mvBox.push_back(make_pair(image, render));
	}
	pos = { pos.x + 16, pos.y };
	size = { 32, 32 };
	image = make_pair(pos, size);
	render = make_pair(pos, size);
	mvBox.push_back(make_pair(image, render));*/
}