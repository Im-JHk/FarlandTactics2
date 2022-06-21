#include "Stdafx.h"
#include "ImageData.h"

HRESULT ImageData::init(void)
{
	//BackGround
	IMAGEMANAGER->addImage("bg_black", "Resources/Images/BackGround/black_board.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("bg_white", "Resources/Images/BackGround/white_board.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("bg_side", "Resources/Images/BackGround/bg_side.bmp", 100, WINSIZE_Y);
	IMAGEMANAGER->addImage("title", "Resources/Images/BackGround/title.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("select", "Resources/Images/BackGround/select.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("town", "Resources/Images/BackGround/town.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("town_text", "Resources/Images/BackGround/town_text.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("guild", "Resources/Images/BackGround/guild.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("game_over", "Resources/Images/BackGround/over.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("ending", "Resources/Images/BackGround/ending.bmp", WINSIZE_X, WINSIZE_Y * 0.75);
	IMAGEMANAGER->addImage("thank_you", "Resources/Images/BackGround/thank_you.bmp", WINSIZE_X, WINSIZE_Y / 2, true, RGB(255, 255, 255));

	//Player
	IMAGEMANAGER->addFrameImage("karin_idle", "Resources/Images/Object/Player/karin_idle.bmp", 300, 400, 3, 4, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("karin_move", "Resources/Images/Object/Player/karin_move.bmp", 400, 400, 4, 4, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("karin_attack", "Resources/Images/Object/Player/karin_attack.bmp", 960, 400, 8, 4, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("karin_spell", "Resources/Images/Object/Player/karin_spell.bmp", 1100, 400, 11, 4, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("karin_damage", "Resources/Images/Object/Player/karin_damage.bmp", 200, 400, 2, 4, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("karin_death", "Resources/Images/Object/Player/karin_death.bmp", 100, 400, 1, 4, true, RGB(0, 255, 255));

	IMAGEMANAGER->addFrameImage("al_idle", "Resources/Images/Object/Player/al_idle.bmp", 300, 400, 3, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("al_move", "Resources/Images/Object/Player/al_move.bmp", 400, 400, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("al_attack", "Resources/Images/Object/Player/al_attack.bmp", 500, 400, 5, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("al_spell", "Resources/Images/Object/Player/al_spell.bmp", 1100, 400, 11, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("al_damage", "Resources/Images/Object/Player/al_damage.bmp", 200, 400, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("al_death", "Resources/Images/Object/Player/al_death.bmp", 100, 400, 1, 4, true, RGB(255, 0, 255));

	//Enemy
	IMAGEMANAGER->addFrameImage("rogue1_idle", "Resources/Images/Object/Enemy/rogue1_idle.bmp", 300, 400, 3, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rogue1_move", "Resources/Images/Object/Enemy/rogue1_move.bmp", 400, 400, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rogue1_attack", "Resources/Images/Object/Enemy/rogue1_attack.bmp", 600, 400, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rogue1_damage", "Resources/Images/Object/Enemy/rogue1_damage.bmp", 200, 400, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rogue1_death", "Resources/Images/Object/Enemy/rogue1_death.bmp", 100, 400, 1, 4, true, RGB(255, 0, 255));

	//Effect
	IMAGEMANAGER->addFrameImage("flame_burst", "Resources/Images/Object/Effect/flame_burst.bmp", 2380, 210, 17, 1, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("number_red", "Resources/Images/Object/Effect/number_red.bmp", 128, 320, 8, 10, true, RGB(255, 255, 255));

	//UI
	IMAGEMANAGER->addFrameImage("tile", "Resources/Images/MapTool/Tile/test_tile.bmp", 384, 32, 6, 1, true, RGB(0, 0, 255));
	IMAGEMANAGER->addFrameImage("floor", "Resources/Images/MapTool/Tile/tile_floor.bmp", 256, 32, 4, 1, true, RGB(0, 0, 255));
	IMAGEMANAGER->addFrameImage("tile_select", "Resources/Images/Object/system.bmp", 128, 96, 2, 3, true, RGB(255, 0, 0));
	IMAGEMANAGER->addFrameImage("button", "Resources/Images/UI/button.bmp", 300, 50, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button_small", "Resources/Images/UI/button_small.bmp", 150, 20, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("system", "Resources/Images/UI/system.bmp", 552, 128, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("wall", "Resources/Images/UI/wall.bmp", 320, 288, true, RGB(128, 0, 128));
	IMAGEMANAGER->addImage("info_box", "Resources/Images/UI/unit_info.bmp", 320, 128, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("msg_box", "Resources/Images/UI/message_box.bmp", 600, 150, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("guild_button", "Resources/Images/UI/guild_button.bmp", 54, 32, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("outside_button", "Resources/Images/UI/outside_button.bmp", 74, 33, true, RGB(255, 255, 255));
	
	//Profile
	IMAGEMANAGER->addImage("karin_up", "Resources/Images/UI/karin_up.bmp", 240, 196, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("karin_down", "Resources/Images/UI/karin_down.bmp", 240, 196, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("gaston_up", "Resources/Images/UI/gaston_up.bmp", 240, 196, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("gaston_down", "Resources/Images/UI/gaston_down.bmp", 240, 196, true, RGB(255, 255, 255));

	return S_OK;
}

void ImageData::release(void)
{
}
