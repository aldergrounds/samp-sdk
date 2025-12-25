/* ============================================================================ *
 * SA-MP SDK - A Modern C++ SDK for San Andreas Multiplayer Plugin Development  *
 * ================================= About ==================================== *
 *                                                                              *
 * This SDK provides a modern, high-level C++ abstraction layer over the native *
 * SA-MP Plugin SDK. It is designed to simplify plugin development by offering  *
 * type-safe, object-oriented, and robust interfaces for interacting with the   *
 * SA-MP server and the Pawn scripting environment.                             *
 *                                                                              *
 * =============================== Copyright ================================== *
 *                                                                              *
 * Copyright (c) 2025, AlderGrounds                                             *
 * All rights reserved.                                                         *
 *                                                                              *
 * Repository: https://github.com/aldergrounds/samp-sdk                         *
 *                                                                              *
 * ================================ License =================================== *
 *                                                                              *
 * Licensed under the MIT License (the "License"); you may not use this file    *
 * except in compliance with the License. You may obtain a copy of the License  *
 * at:                                                                          *
 *                                                                              *
 *     https://opensource.org/licenses/MIT                                      *
 *                                                                              *
 * Unless required by applicable law or agreed to in writing, software          *
 * distributed under the License is distributed on an "AS IS" BASIS,            *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.     *
 * See the License for the specific language governing permissions and          *
 * limitations under the License.                                               *
 *                                                                              *
 * ============================================================================ */

#pragma once

// General Limits and Invalid IDs
constexpr int MAX_PLAYER_NAME = 24 + 1;
constexpr int MAX_PLAYERS = 1000;
constexpr int MAX_VEHICLES = 2000;
constexpr int MAX_ACTORS = 1000;
constexpr int MAX_OBJECTS = 1000;
constexpr int MAX_GANG_ZONES = 1024;
constexpr int MAX_TEXT_DRAWS = 2048;
constexpr int MAX_PLAYER_TEXT_DRAWS = 256;
constexpr int MAX_MENUS = 128;
constexpr int MAX_3DTEXT_GLOBAL = 1024;
constexpr int MAX_3DTEXT_PLAYER = 1024;
constexpr int MAX_PICKUPS = 4096;
constexpr int MAX_PLAYER_ATTACHED_OBJECTS = 10;
constexpr int MAX_CHATBUBBLE_LENGTH = 144;

constexpr int INVALID_PLAYER_ID = 0xFFFF;
constexpr int INVALID_VEHICLE_ID = 0xFFFF;
constexpr int INVALID_ACTOR_ID = 0xFFFF;
constexpr int INVALID_OBJECT_ID = 0xFFFF;
constexpr int INVALID_MENU = 0xFF;
constexpr int INVALID_TEXT_DRAW = 0xFFFF;
constexpr int INVALID_GANG_ZONE = -1;
constexpr int INVALID_3DTEXT_ID = 0xFFFF;

constexpr int NO_TEAM = 255;

// Player States and Actions
constexpr int PLAYER_STATE_NONE = 0;
constexpr int PLAYER_STATE_ONFOOT = 1;
constexpr int PLAYER_STATE_DRIVER = 2;
constexpr int PLAYER_STATE_PASSENGER = 3;
constexpr int PLAYER_STATE_EXIT_VEHICLE = 4;
constexpr int PLAYER_STATE_ENTER_VEHICLE_DRIVER = 5;
constexpr int PLAYER_STATE_ENTER_VEHICLE_PASSENGER = 6;
constexpr int PLAYER_STATE_WASTED = 7;
constexpr int PLAYER_STATE_SPAWNED = 8;
constexpr int PLAYER_STATE_SPECTATING = 9;

constexpr int SPECIAL_ACTION_NONE = 0;
constexpr int SPECIAL_ACTION_DUCK = 1;
constexpr int SPECIAL_ACTION_USEJETPACK = 2;
constexpr int SPECIAL_ACTION_ENTER_VEHICLE = 3;
constexpr int SPECIAL_ACTION_EXIT_VEHICLE = 4;
constexpr int SPECIAL_ACTION_DANCE1 = 5;
constexpr int SPECIAL_ACTION_DANCE2 = 6;
constexpr int SPECIAL_ACTION_DANCE3 = 7;
constexpr int SPECIAL_ACTION_DANCE4 = 8;
constexpr int SPECIAL_ACTION_HANDSUP = 10;
constexpr int SPECIAL_ACTION_USECELLPHONE = 11;
constexpr int SPECIAL_ACTION_SITTING = 12;
constexpr int SPECIAL_ACTION_STOPUSECELLPHONE = 13;
constexpr int SPECIAL_ACTION_DRINK_BEER = 20;
constexpr int SPECIAL_ACTION_SMOKE_CIGGY = 21;
constexpr int SPECIAL_ACTION_DRINK_WINE = 22;
constexpr int SPECIAL_ACTION_DRINK_SPRUNK = 23;
constexpr int SPECIAL_ACTION_CUFFED = 24;
constexpr int SPECIAL_ACTION_CARRY = 25;

constexpr int FIGHT_STYLE_NORMAL = 4;
constexpr int FIGHT_STYLE_BOXING = 5;
constexpr int FIGHT_STYLE_KUNGFU = 6;
constexpr int FIGHT_STYLE_KNEEHEAD = 7;
constexpr int FIGHT_STYLE_GRABKICK = 15;
constexpr int FIGHT_STYLE_ELBOW = 16;

// Player Keys
constexpr int KEY_ACTION = 1;
constexpr int KEY_CROUCH = 2;
constexpr int KEY_FIRE = 4;
constexpr int KEY_SPRINT = 8;
constexpr int KEY_SECONDARY_ATTACK = 16;
constexpr int KEY_JUMP = 32;
constexpr int KEY_LOOK_RIGHT = 64;
constexpr int KEY_HANDBRAKE = 128;
constexpr int KEY_LOOK_LEFT = 256;
constexpr int KEY_SUBMISSION = 512;
constexpr int KEY_LOOK_BEHIND = 512;
constexpr int KEY_WALK = 1024;
constexpr int KEY_ANALOG_UP = 2048;
constexpr int KEY_ANALOG_DOWN = 4096;
constexpr int KEY_ANALOG_LEFT = 8192;
constexpr int KEY_ANALOG_RIGHT = 16384;
constexpr int KEY_YES = 65536;
constexpr int KEY_NO = 131072;
constexpr int KEY_CTRL_BACK = 262144;

constexpr int KEY_UP = -128;
constexpr int KEY_DOWN = 128;
constexpr int KEY_LEFT = -128;
constexpr int KEY_RIGHT = 128;

// Weapons and Skills
constexpr int WEAPON_BRASSKNUCKLE = 1;
constexpr int WEAPON_GOLFCLUB = 2;
constexpr int WEAPON_NITESTICK = 3;
constexpr int WEAPON_KNIFE = 4;
constexpr int WEAPON_BAT = 5;
constexpr int WEAPON_SHOVEL = 6;
constexpr int WEAPON_POOLSTICK = 7;
constexpr int WEAPON_KATANA = 8;
constexpr int WEAPON_CHAINSAW = 9;
constexpr int WEAPON_DILDO = 10;
constexpr int WEAPON_DILDO2 = 11;
constexpr int WEAPON_VIBRATOR = 12;
constexpr int WEAPON_VIBRATOR2 = 13;
constexpr int WEAPON_FLOWER = 14;
constexpr int WEAPON_CANE = 15;
constexpr int WEAPON_GRENADE = 16;
constexpr int WEAPON_TEARGAS = 17;
constexpr int WEAPON_MOLTOV = 18;
constexpr int WEAPON_COLT45 = 22;
constexpr int WEAPON_SILENCED = 23;
constexpr int WEAPON_DEAGLE = 24;
constexpr int WEAPON_SHOTGUN = 25;
constexpr int WEAPON_SAWEDOFF = 26;
constexpr int WEAPON_SHOTGSPA = 27;
constexpr int WEAPON_UZI = 28;
constexpr int WEAPON_MP5 = 29;
constexpr int WEAPON_AK47 = 30;
constexpr int WEAPON_M4 = 31;
constexpr int WEAPON_TEC9 = 32;
constexpr int WEAPON_RIFLE = 33;
constexpr int WEAPON_SNIPER = 34;
constexpr int WEAPON_ROCKETLAUNCHER = 35;
constexpr int WEAPON_HEATSEEKER = 36;
constexpr int WEAPON_FLAMETHROWER = 37;
constexpr int WEAPON_MINIGUN = 38;
constexpr int WEAPON_SATCHEL = 39;
constexpr int WEAPON_BOMB = 40;
constexpr int WEAPON_SPRAYCAN = 41;
constexpr int WEAPON_FIREEXTINGUISHER = 42;
constexpr int WEAPON_CAMERA = 43;
constexpr int WEAPON_PARACHUTE = 46;
constexpr int WEAPON_VEHICLE = 49;
constexpr int WEAPON_DROWN = 53;
constexpr int WEAPON_COLLISION = 54;

constexpr int WEAPONSKILL_PISTOL = 0;
constexpr int WEAPONSKILL_PISTOL_SILENCED = 1;
constexpr int WEAPONSKILL_DESERT_EAGLE = 2;
constexpr int WEAPONSKILL_SHOTGUN = 3;
constexpr int WEAPONSKILL_SAWNOFF_SHOTGUN = 4;
constexpr int WEAPONSKILL_SPAS12_SHOTGUN = 5;
constexpr int WEAPONSKILL_MICRO_UZI = 6;
constexpr int WEAPONSKILL_MP5 = 7;
constexpr int WEAPONSKILL_AK47 = 8;
constexpr int WEAPONSKILL_M4 = 9;
constexpr int WEAPONSKILL_SNIPERRIFLE = 10;

constexpr int WEAPONSTATE_UNKNOWN = -1;
constexpr int WEAPONSTATE_NO_BULLETS = 0;
constexpr int WEAPONSTATE_LAST_BULLET = 1;
constexpr int WEAPONSTATE_MORE_BULLETS = 2;
constexpr int WEAPONSTATE_RELOADING = 3;

// Vehicles
constexpr int CARMODTYPE_SPOILER = 0;
constexpr int CARMODTYPE_HOOD = 1;
constexpr int CARMODTYPE_ROOF = 2;
constexpr int CARMODTYPE_SIDESKIRT = 3;
constexpr int CARMODTYPE_LAMPS = 4;
constexpr int CARMODTYPE_NITRO = 5;
constexpr int CARMODTYPE_EXHAUST = 6;
constexpr int CARMODTYPE_WHEELS = 7;
constexpr int CARMODTYPE_STEREO = 8;
constexpr int CARMODTYPE_HYDRAULICS = 9;
constexpr int CARMODTYPE_FRONT_BUMPER = 10;
constexpr int CARMODTYPE_REAR_BUMPER = 11;
constexpr int CARMODTYPE_VENT_RIGHT = 12;
constexpr int CARMODTYPE_VENT_LEFT = 13;

constexpr int VEHICLE_PARAMS_UNSET = -1;
constexpr int VEHICLE_PARAMS_OFF = 0;
constexpr int VEHICLE_PARAMS_ON = 1;

constexpr int VEHICLE_MODEL_INFO_SIZE = 1;
constexpr int VEHICLE_MODEL_INFO_FRONTSEAT = 2;
constexpr int VEHICLE_MODEL_INFO_REARSEAT = 3;
constexpr int VEHICLE_MODEL_INFO_PETROLCAP = 4;
constexpr int VEHICLE_MODEL_INFO_WHEELSFRONT = 5;
constexpr int VEHICLE_MODEL_INFO_WHEELSREAR = 6;
constexpr int VEHICLE_MODEL_INFO_WHEELSMID = 7;
constexpr int VEHICLE_MODEL_INFO_FRONT_BUMPER_Z = 8;
constexpr int VEHICLE_MODEL_INFO_REAR_BUMPER_Z = 9;

// Dialogs, Menus, and UI
constexpr int DIALOG_STYLE_MSGBOX = 0;
constexpr int DIALOG_STYLE_INPUT = 1;
constexpr int DIALOG_STYLE_LIST = 2;
constexpr int DIALOG_STYLE_PASSWORD = 3;
constexpr int DIALOG_STYLE_TABLIST = 4;
constexpr int DIALOG_STYLE_TABLIST_HEADERS = 5;

constexpr int TEXT_DRAW_FONT_SPRITE_DRAW = 4;
constexpr int TEXT_DRAW_FONT_MODEL_PREVIEW = 5;

// Objects
constexpr int OBJECT_MATERIAL_SIZE_32x32 = 10;
constexpr int OBJECT_MATERIAL_SIZE_64x32 = 20;
constexpr int OBJECT_MATERIAL_SIZE_64x64 = 30;
constexpr int OBJECT_MATERIAL_SIZE_128x32 = 40;
constexpr int OBJECT_MATERIAL_SIZE_128x64 = 50;
constexpr int OBJECT_MATERIAL_SIZE_128x128 = 60;
constexpr int OBJECT_MATERIAL_SIZE_256x32 = 70;
constexpr int OBJECT_MATERIAL_SIZE_256x64 = 80;
constexpr int OBJECT_MATERIAL_SIZE_256x128 = 90;
constexpr int OBJECT_MATERIAL_SIZE_256x256 = 100;
constexpr int OBJECT_MATERIAL_SIZE_512x64 = 110;
constexpr int OBJECT_MATERIAL_SIZE_512x128 = 120;
constexpr int OBJECT_MATERIAL_SIZE_512x256 = 130;
constexpr int OBJECT_MATERIAL_SIZE_512x512 = 140;

constexpr int OBJECT_MATERIAL_TEXT_ALIGN_LEFT = 0;
constexpr int OBJECT_MATERIAL_TEXT_ALIGN_CENTER = 1;
constexpr int OBJECT_MATERIAL_TEXT_ALIGN_RIGHT = 2;

// Events and Callbacks
constexpr int CLICK_SOURCE_SCOREBOARD = 0;

constexpr int EDIT_RESPONSE_CANCEL = 0;
constexpr int EDIT_RESPONSE_FINAL = 1;
constexpr int EDIT_RESPONSE_UPDATE = 2;

constexpr int SELECT_OBJECT_GLOBAL_OBJECT = 1;
constexpr int SELECT_OBJECT_PLAYER_OBJECT = 2;

constexpr int BULLET_HIT_TYPE_NONE = 0;
constexpr int BULLET_HIT_TYPE_PLAYER = 1;
constexpr int BULLET_HIT_TYPE_VEHICLE = 2;
constexpr int BULLET_HIT_TYPE_OBJECT = 3;
constexpr int BULLET_HIT_TYPE_PLAYER_OBJECT = 4;

// Variables (PVars/SVars)
constexpr int PLAYER_VARTYPE_NONE = 0;
constexpr int PLAYER_VARTYPE_INT = 1;
constexpr int PLAYER_VARTYPE_STRING = 2;
constexpr int PLAYER_VARTYPE_FLOAT = 3;

constexpr int SERVER_VARTYPE_NONE = 0;
constexpr int SERVER_VARTYPE_INT = 1;
constexpr int SERVER_VARTYPE_STRING = 2;
constexpr int SERVER_VARTYPE_FLOAT = 3;

// Others
constexpr int PLAYER_MARKERS_MODE_OFF = 0;
constexpr int PLAYER_MARKERS_MODE_GLOBAL = 1;
constexpr int PLAYER_MARKERS_MODE_STREAMED = 2;

constexpr int MAPICON_LOCAL = 0;
constexpr int MAPICON_GLOBAL = 1;
constexpr int MAPICON_LOCAL_CHECKPOINT = 2;
constexpr int MAPICON_GLOBAL_CHECKPOINT = 3;

constexpr int CAMERA_CUT = 2;
constexpr int CAMERA_MOVE = 1;

constexpr int SPECTATE_MODE_NORMAL = 1;
constexpr int SPECTATE_MODE_FIXED = 2;
constexpr int SPECTATE_MODE_SIDE = 3;

constexpr int PLAYER_RECORDING_TYPE_NONE = 0;
constexpr int PLAYER_RECORDING_TYPE_DRIVER = 1;
constexpr int PLAYER_RECORDING_TYPE_ONFOOT = 2;

constexpr int HTTP_GET = 1;
constexpr int HTTP_POST = 2;
constexpr int HTTP_HEAD = 3;

constexpr int HTTP_ERROR_BAD_HOST = 1;
constexpr int HTTP_ERROR_NO_SOCKET = 2;
constexpr int HTTP_ERROR_CANT_CONNECT = 3;
constexpr int HTTP_ERROR_CANT_WRITE = 4;
constexpr int HTTP_ERROR_CONTENT_TOO_BIG = 5;
constexpr int HTTP_ERROR_MALFORMED_RESPONSE = 6;