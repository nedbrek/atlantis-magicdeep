// START A3HEADER
//
// This source file is part of the Atlantis PBM game program.
// Copyright (C) 1995-1999 Geoff Dunbar
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program, in the file license.txt. If not, write
// to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
//
// See the Atlantis Project web page for details:
// http://www.prankster.com/project
//
// END A3HEADER
// MODIFICATONS
// Date	    Person            Comments
// ----	    ------            --------
// 2000/SEP/06 Joseph Traub	  Added base man cost to allow races to have
//	                           different base costs
// 2001/FEB/01 Joseph Traub	  Added options for flying over water and
//	                           easier underworld viewing and farseeing
// 2001/FEB/07 Joseph Traub	  Added option to make starting cities safe
//	                           or not and to control the guard numbers
//	                           and to make them slightly tougher.
//	                           Added option to give starting city guards
//	                           mage support.
// 2001/Feb/18 Joseph Traub	  Added Apprentices idea from Lacandon Conquest
// 2001/Feb/18 Joseph Traub	  Added back in support for Conquest
// 2001/Feb/19 Joseph Traub	  Removed the ENGINE_VERSION from the gamedef
//	                           since it wasn't being used.
// 2001/Feb/21 Joseph Traub	  Added a FACLIM_UNLIMITED option
// 2001/Apr/08 Joseph Traub	  Added WORLD_NAME option
// 2001/Apr/28 Joseph Traub	  Added MORE_PROFITABLE_TRADE_GOODS option
//

#ifndef GAME_DEFS
#define GAME_DEFS

#include "helper.h"

/* Directions */
enum {
	D_NORTH,
	D_NORTHEAST,
	D_SOUTHEAST,
	D_SOUTH,
	D_SOUTHWEST,
	D_NORTHWEST,
	NDIRS
};

extern char **DirectionStrs;
extern char **DirectionAbrs;

extern char **MonthNames;

extern char **SeasonNames;

extern int *allowedMages;
extern int allowedMagesSize;
extern int *allowedApprentices;
extern int allowedApprenticesSize;
extern int *allowedTaxes;
extern int allowedTaxesSize;
extern int *allowedTrades;
extern int allowedTradesSize;

extern int *magesPPCosts;
extern int magesPPCostsSize;

extern int *apprenticesPPCosts;
extern int apprenticesPPCostsSize;

class GameDefs {
public:
	char *RULESET_NAME;
	ATL_VER RULESET_VERSION;

	int FOOT_SPEED;
	int HORSE_SPEED;
	int SHIP_SPEED;
	int FLY_SPEED;
	int MAX_SPEED;

	int STUDENTS_PER_TEACHER;

	int MAINTENANCE_COST;
	int LEADER_COST;
        int MAGE_COST;

	// If we use skill level multiplier then no units, all units, leaders,
	// or just mages pay X per level of skill they have per man.   The
	// first value (MAINTENCE_MULTIPLIER) is how much is payed per skill
	// level.   The second value (MULTIPLIER_USE) is set to one of the
	// values in the given enumeration.
	// The costs listed above are used for any units NOT covered by the
	// multiplier use
	int MAINTENANCE_MULTIPLIER;

	enum {
		MULT_NONE,
		MULT_MAGES,
		MULT_LEADERS,
		MULT_ALL,
	};
	int MULTIPLIER_USE;

	int STARVE_PERCENT;

	enum {
		STARVE_NONE,
		STARVE_MAGES,
		STARVE_LEADERS,
		STARVE_ALL,
	};

	// Instead of dying, lose skill levels, but only for the types of
	// units listed below.   Any unit which should lose a skill level and
	// is unable to will die, period.
	int SKILL_STARVATION;

	int START_MONEY;
	int WORK_FRACTION;
	int ENTERTAIN_FRACTION;
	int ENTERTAIN_INCOME;

	int TAX_INCOME;

	int HEALS_PER_MAN;

	int GUARD_REGEN; /* percent */
	int CITY_GUARD;
	int GUARD_MONEY;
	int CITY_POP;

	int WMON_FREQUENCY;
	int LAIR_FREQUENCY;

	int FACTION_POINTS;

	int TIMES_REWARD;

	int TOWNS_EXIST;
        int STARTCITYES;
	int LEADERS_EXIST;
	int SKILL_LIMIT_NONLEADERS;
	int MAGE_NONLEADERS;
	int RACES_EXIST;
	int GATES_EXIST;
	int FOOD_ITEMS_EXIST;
	int CITY_MONSTERS_EXIST;
	int WANDERING_MONSTERS_EXIST;
	int LAIR_MONSTERS_EXIST;
	int WEATHER_EXISTS;
	int OPEN_ENDED;
	int NEXUS_EXISTS;
	int CONQUEST_GAME;

	//
	// RANDOM_ECONOMY determines whether the economy for different regions
	// is randomized, or is always the same.
	//
	int RANDOM_ECONOMY;

	//
	// If VARIABLE_ECONOMY is set, the economy of a region is altered after
	// each turn.
	//
	int VARIABLE_ECONOMY;

	//
	// Some economy figures.
	//
	int CITY_MARKET_NORMAL_AMT;
	int CITY_MARKET_ADVANCED_AMT;
	int CITY_MARKET_TRADE_AMT;
	// If any magic items are not set NOMARKET, how many are allowed?
	int CITY_MARKET_MAGIC_AMT;
	// JLT -- Allow higher margins on trade goods.
	int MORE_PROFITABLE_TRADE_GOODS;

	// JLT -- Allow races to have differing base costs
	int BASE_MAN_COST;

	// Are the lastorders values maintained by external scripts?
	int LASTORDERS_MAINTAINED_BY_SCRIPTS;

	// How many turns to allow a faction to be inactive.
	// Set to -1 if you don't want this check performed.
	int MAX_INACTIVE_TURNS;

	// Is it easier to deal with the underworld (allows teleport and
	// farsight into the underworld)
	int EASIER_UNDERWORLD;

	// Should units with no orders perform a default 'work' order
	int DEFAULT_WORK_ORDER;

	//
	// The type of faction limits that are in effect in this game.
	//
	enum {
		FACLIM_MAGE_COUNT,
		FACLIM_FACTION_TYPES,
		FACLIM_POWER_POINTS,	// [ufas]
		FACLIM_UNLIMITED,
	};
	int FACTION_LIMIT_TYPE;

	//
	// The type of flight over water that is available.
	//
	enum {
		WFLIGHT_NONE,
		WFLIGHT_MUST_LAND,
		WFLIGHT_UNLIMITED,
	};
	int FLIGHT_OVER_WATER;

	//
	// Are starting cities safe regions?  Also controls if guards in
	// the starting cities get amulets of invulnerability.
	//
	int SAFE_START_CITIES;

	//
	// How many guards in starting cities?
	//
	int AMT_START_CITY_GUARDS;

	//
	// Should starting city guards be made tougher than normal city guards?
	// (this means giving them plate armor)
	//
	int START_CITY_GUARDS_PLATE;

	//
	// Do starting cities have a fire mages.  (0 for no mages, otherwise
	// this is the level of their fire skill)
	//
	//
	int START_CITY_MAGES;

	// Do the starting city guards also have tactician skill (0 for
	// no tactician, otherwise this is their level of tactician)
	int START_CITY_TACTICS;

	//
	// Are we allowing apprentices?
	//
	int APPRENTICES_EXIST;

	// What is the name of the world?
	char *WORLD_NAME;

	// Does the nexus allow gating out of it
	int NEXUS_GATE_OUT;

	// Is the nexus also a city?
	int NEXUS_IS_CITY;

	// Do battle reports show factions if ANY unit on the opposing side
	// could see it.   Non-involved observers will ALSO see this
	// information.
	int BATTLE_FACTION_INFO;

	// Is the withdraw order enabled
	int ALLOW_WITHDRAW;

	// Do cities have a cost to rename them?  If this value is set,
	// the cost is the city size (1, 2, 3) * this value
	int CITY_RENAME_COST;

	// Are taxing and pillaging month-long actions?
	int TAX_PILLAGE_MONTH_LONG;

	// Are we allowing a multi-hex nexus
	int MULTI_HEX_NEXUS;

	// How many levels of the underworld do we want?
	int UNDERWORLD_LEVELS;

	// How many levels of the underdeep do we want?
	int UNDERDEEP_LEVELS;

	// Is there an abyss level?
	int ABYSS_LEVEL;

	// Town probability; 100 = default
	int TOWN_PROBABILITY;

	// Raising this value will lessen the effects
	// of a region type's economy on the chance
	// for creating towns (overall probability
	// will also vary a bit).
	// Default = 0. For high values the town probability
	// will need to be adjusted downwards to get
	// comparable number of towns.
	int TOWN_SPREAD;

	// Flag for disallowing settlements in adjacent regions
	// (except near starting cities)
	int TOWNS_NOT_ADJACENT;

	// Make settlements near the arctic less likely and smaller
	// Higher values decrease likeliness of settlements
	// suggested: 0-5
	int LESS_ARCTIC_TOWNS;

	// Enable Archipelago Creation
	// = chance of creating archipelagos vs continents
	// (note that archipelagos are smaller so that
	//  the overall contribution of archipelagos to
	//  land mass will be much lower than this percentage)
	// Setting ARCHIPELAGO means that smaller inland seas will be
	// converted into continent mass.
	// suggested value: 10, 25, 50+ it's really a matter of taste
	int ARCHIPELAGO;

	// Chance for Lake Creation
	// Setting LAKES_EXIST means that smaller inland seas will be
	// converted into continent mass - this is the chance that
	// such regions will end up as lakes.
	// suggested value: around 12.
	int LAKES_EXIST;

	// 1 or 0. If 1 then terrains "shallows", "river", "hills",
	// "high mountains" will be used for world generation, else not.
	int ADVANCED_MAP;	//Klaus

	// if 1 then using forbidding scheme, when every terrain type has
	// a list of mount types, which can be used in it. Else used just
	// movement cost, regardless of mount type.
	int ADVANCED_MOVEMENT;	//Klaus

	// Lake Effect on Wages Options
	// Lakes will add one to adjacent regions wages if set
	enum {
		NO_EFFECT = 0x00,
		ALL = 0x01,
		TOWNS = 0x02,
		NONPLAINS = 0x04,
		NONPLAINS_TOWNS_ONLY=0x08,
		DESERT_ONLY = 0x10,
	};

	// LAKE_WAGE_EFFECT: effect on surrounding wages
	int LAKE_WAGE_EFFECT;

	// LAKESIDE_IS_COASTAL: lakeside regions count as
	// coastal for all purposes - races and such
	int LAKESIDE_IS_COASTAL;

	// ODD_TERRAIN: chance (x 0.1%) for single-hex terrain oddities
	// suggested: between 5 and 40
	int ODD_TERRAIN;

	// Does farsight make use of a mages other skills
	int IMPROVED_FARSIGHT;

	// Should the GM get a full world report every turn
	int GM_REPORT;

	// Do we allow objects to decay according to the parameters in the object
	// definition table
	int DECAY;

	// Do we limit the number of mages which can study inside of certain
	// buildings.
	int LIMITED_MAGES_PER_BUILDING;

	// Transit report options
	enum {
		REPORT_NOTHING = 0x0000,
		// Various things which can be shown
		REPORT_SHOW_PEASANTS = 0x0001,
		REPORT_SHOW_REGION_MONEY = 0x0002,
		REPORT_SHOW_WAGES = 0x0004,
		REPORT_SHOW_MARKETS = 0x0008,
		REPORT_SHOW_RESOURCES = 0x0010,
		REPORT_SHOW_ENTERTAINMENT = 0x0020,
		// Collection of the the above
		REPORT_SHOW_ECONOMY = (REPORT_SHOW_PEASANTS |
							   REPORT_SHOW_REGION_MONEY |
							   REPORT_SHOW_WAGES |
							   REPORT_SHOW_MARKETS |
							   REPORT_SHOW_RESOURCES |
							   REPORT_SHOW_ENTERTAINMENT),
		// Which type of exits to show
		REPORT_SHOW_USED_EXITS = 0x0040,
		REPORT_SHOW_ALL_EXITS = 0x0080,
		// Which types of units to show
		REPORT_SHOW_GUARDS = 0x0100,
		REPORT_SHOW_INDOOR_UNITS = 0x0200,
		REPORT_SHOW_OUTDOOR_UNITS = 0x0400,
		// Collection of the above
		REPORT_SHOW_UNITS = (REPORT_SHOW_GUARDS | REPORT_SHOW_INDOOR_UNITS |
							 REPORT_SHOW_OUTDOOR_UNITS),
		// Various types of buildings
		REPORT_SHOW_BUILDINGS = 0x0800,
		REPORT_SHOW_ROADS = 0x1000,
		REPORT_SHOW_SHIPS = 0x2000,
		// Collection of the above
		REPORT_SHOW_STRUCTURES = (REPORT_SHOW_BUILDINGS |
								  REPORT_SHOW_ROADS |
								  REPORT_SHOW_SHIPS),
		// Should the unit get to use their advanced skills?
		REPORT_USE_UNIT_SKILLS = 0x8000,

		// Some common collections
		REPORT_SHOW_REGION = (REPORT_SHOW_ECONOMY | REPORT_SHOW_ALL_EXITS),
		REPORT_SHOW_FASTVIEW = (REPORT_SHOW_REGION | REPORT_SHOW_STRUCTURES | REPORT_SHOW_GUARDS),
		REPORT_SHOW_EVERYTHING = (REPORT_SHOW_REGION |
								  REPORT_SHOW_UNITS |
								  REPORT_SHOW_STRUCTURES),
	};

	// What sort of information should be shown to a unit just passing
	// through a hex?
	int TRANSIT_REPORT;

	// Should advanced items be shown in markets at all times.
	int MARKETS_SHOW_ADVANCED_ITEMS;

	// Do we require the 'ready' command to set up battle items
	int USE_PREPARE_COMMAND;

	// Monsters have the option of advancing occasionally instead of just
	// using move.
	// There are two values which control this.
	// MONSTER_ADVANCE_MIN_PERCENT is the minimum amount which monsters
	// should advance.
	// MONSTER_ADVANCE_HOSTILE_PERCENT is the percent of their hostile
	// rating which should be used to determine if they advance.
	// If you don't want monsters to EVER advance, use 0 for both.
	// If you want a flat percent, use MIN_PERCENT and set HOSTILE_PERCENT
	// to 0.  If you only want it based on the HOSTILE value, set MIN_PERCENT
	// to 0 and HOSTILE_PERCENT to what you want.
	int MONSTER_ADVANCE_MIN_PERCENT;
	int MONSTER_ADVANCE_HOSTILE_PERCENT;

	// Set this to 1 if your scripts can handle the following commands
	// #create, #resend, #times, #rumor, #remind, #email
	int HAVE_EMAIL_SPECIAL_COMMANDS;

	// Should starting cities begin with unlimited markets at world
	// generation time.
	int START_CITIES_START_UNLIMITED;

	// If this is enabled, then when a unit has more men than Amulets of
	// True Seeing, and it is targetted by an assassin, then there is a
	// chance that the target picked will be one of the men carrying
	// the amulet and the attempt will be foiled.  If not enabled, the
	// attempt always succeeds.
	int PROPORTIONAL_AMTS_USAGE;

	// If this is enabled, then the ARMOR and WEAPON commands for selecting
	// armor/weapon priorities for a unit are enabled. If a preferred weapon
	// or armor isn't available, then the code will fall back to the internal
	// list.
	int USE_WEAPON_ARMOR_COMMAND;

	// Set MONSTER_NO_SPOILS > 0 to disable spoils from released monsters
	// for that many months.
	int MONSTER_NO_SPOILS;
	// Set MONSTER_SPOILS_RECOVERY > 0 to set a time in months over which
	// monster spoils are slowly regained.
	// This has no effect unles MONSTER_NO_SPOILS is also set.
	int MONSTER_SPOILS_RECOVERY;

	// Use this to limit the number of attacks an assassin gets in the free
	// round.
	int MAX_ASSASSIN_FREE_ATTACKS;

	// Set to 1 to allow 'GIVE 0 <num> <monster>' for summoned monsters
	// (dragons, wolves, eagles currently)
	int RELEASE_MONSTERS;

	// Set to 1 to check for demons breaking free and undead decaying before
	// movemeent rather than at the end of the turn.  This prevents 'balrog
	// missiles'
	int CHECK_MONSTER_CONTROL_MID_TURN;

	// Set to 1 if CAST GATE DETECT shows the actual gate numbers.
	int DETECT_GATE_NUMBERS;

	// Should army routes be basd on the number of hits lost rather than the
	// number of figures lost.
	enum {
		// Default -- rout if half of the total figures die.  All figures are
		// treated equally.
		ARMY_ROUT_FIGURES = 0,
		// Rout if half the total hits die, all hits are counted independantly
		// This means you could rout even if none of your men are dead but
		// you have just taken a lot of hits and are getting clobbered
		ARMY_ROUT_HITS_INDIVIDUAL,
		// Rout if half of the total hits die, but figures hits only stop
		// counting toward the total when the figure is fully dead.
		ARMY_ROUT_HITS_FIGURE,
	};

	int ARMY_ROUT;

	// If this is set to 0 then a mage gets his TRUE_SEEING skill/2
	// rounded up as a bonus to observation.  Lacandon (and perhaps others)
	// should set this to 1.
	int FULL_TRUESEEING_BONUS;

	// If this is set to 1 then an AMTS will give 3 bonus to OBSE rather
	// than 2. This was added for Lacandon
	int IMPROVED_AMTS;

	// If this is set to 1 then a mage automatically gets his INVISIBILITY
	// skill added to his stealth.  I only recommend setting this if you
	// also set the FULL_TRUESEEING_BONUS above.  This was added for
	// Lacandon.
	int FULL_INVIS_ON_SELF;

	// Do monsters regenerate during battle?
	int MONSTER_BATTLE_REGEN;

	// Options to control who is able to tax
	enum {
		TAX_ANYONE = 0x00001,
		TAX_COMBAT_SKILL = 0x00002,
		TAX_BOW_SKILL = 0x00004,
		TAX_RIDING_SKILL = 0x00008,
		TAX_USABLE_WEAPON = 0x00010, // no requirement or has required skill
		TAX_ANY_WEAPON = 0x00020, // Pay up lest I beat thee with my longbow!
		TAX_HORSE = 0x00040, // someone who HAS a horse, not the horse itself
		// Usually a weapon that requires no skill, plus COMB, but also
		// LANC (which requires RIDI) and RIDI
		TAX_MELEE_WEAPON_AND_MATCHING_SKILL = 0x00080,
		TAX_BOW_SKILL_AND_MATCHING_WEAPON = 0x00100,
		TAX_HORSE_AND_RIDING_SKILL = 0x00200,
		// Probably more petty theft than tax, but then there are those
		// who argue that taxation IS theft ;->
		TAX_STEALTH_SKILL = 0x00400,
		// Should mages be able to tax?  I'd give my tax to someone who
		// was aiming the black wind at me...
		TAX_MAGE_DAMAGE = 0x00800,
		TAX_MAGE_FEAR = 0x01000, // or able to flatten my barn?
		TAX_MAGE_OTHER = 0x02000, // or able to create magical armour?
		TAX_ANY_MAGE = 0x04000, // or who just has an impressive pointy hat?
		// Wasn't sure whether mages should be judged on whether they
		// know the spell, or their current combat spell (he's ordered
		// to cast shield in combat, but still knows how to fireball
		// unruly peasants).  Setting this uses only the current
		// spell set with the COMBAT order.
		TAX_MAGE_COMBAT_SPELL = 0x08000,
		TAX_BATTLE_ITEM = 0x10000, // Has a staff of lightning?
		TAX_USABLE_BATTLE_ITEM = 0x20000,
		TAX_CREATURES = 0x40000, // Do magical critters help to tax?
		TAX_ILLUSIONS = 0x80000, // What if they're not really there?

		// Abbreviation for "the usual"
		TAX_NORMAL = TAX_COMBAT_SKILL | TAX_USABLE_WEAPON,
	};
	int WHO_CAN_TAX;

	// Amount of skill improvement when a skill is used
	int SKILL_PRACTISE_AMOUNT;

	// Options on using food for upkeep
	// Note that all these values are in silver equivalents!
	int UPKEEP_MINIMUM_FOOD;
	// MAXIMUM_FOOD is the maximum contribution of food to upkeep
	// per man, and therefore CAN be lower than MINIMUM_FOOD
	// (although this seems a silly thing to do).
	// A negative value for this def indicates no maximum.
	int UPKEEP_MAXIMUM_FOOD;
	int UPKEEP_FOOD_VALUE;

	// Should ships be prevented from sailing through single hex landmasses
	// during the same turn. (does not prevent them from stopping in a
	// single hex one turn and sailing on through the next turn.
	int PREVENT_SAIL_THROUGH;

	// If we are preventing sail through, should we also prevent the 'easy
	// portage' that the above allows by default?
	int ALLOW_TRIVIAL_PORTAGE;
		// Default = 150. Unit is get minus_bonus to stealth.
		// If this is set to 0 then unit is get no minus_bonus
		int SPY_WEIGHT;         // VVR
		int LEADER_CITY_ONLY;   // VVR
		int MULTY_RACIAL_CITIES;   // Klaus
		// Max number in a Game
		int NUM_LESSAVATAR;     // VVR
		int NUM_AVATAR;         // VVR
                bool SUP_SKILL_PP;      // VVR  cost of mage calc as sum cost of skills in PP

		// *** Klaus
	// Probabiliti of fortresses, owned by NPC, in the settlements...
	int ARM_FORTRESS_PROBABILITY;
	// Chance, that fortress is ruined.
	// If negative, than it'a a chance,that fortress isn't ruined...
	int ARM_FORTRESS_RUINED_CHANCE;

	// Probability of inns, owned by NPC, in the settlements
	int ARM_INN_PROBABILITY;
	// Chance, that inn is ruined
	int ARM_INN_RUINED_CHANCE;

	// Probability of trade structures, owned by NPC
	int ARM_FACTORY_PROBABILITY;
	// Chance, that factory is ruined
	int ARM_FACTORY_RUINED_CHANCE;

	// Probability of roads, builded by ancient NPC, between the settlements
	int ARM_ROAD_PROBABILITY;
	// Chance, that inn is ruined
	int ARM_ROAD_RUINED_CHANCE;     // Klaus  ***
	int GUARDS_LEVEL_BY_TAX;         // Beholder
	// are we allowing to withdraw men? (suited for LEADER_CITY_ONLY
	// option turned on)
	int ALLOW_WITHDRAW_MEN;          // Beholder

	// options that control how different ship types sail
	enum {
		SAIL_HEAVY_SLOWED_ON_SHALLOWS =    0x001, //self explanatory.

		// bad weather increases movement costs for light ships 3
		// times instead of usual 2 times.
		SAIL_LIGHT_SLOWED3_BAD_WEATHER =   0x002,//        Mutually exclusive (1)
		// bad weather increases movement costs for light ships 4
		// times instead of usual 2 times.
		SAIL_LIGHT_SLOWED4_BAD_WEATHER =   0x004,//        Mutually exclusive (1)
		//self explanatory.
		SAIL_LIGHT_STOPPED_BAD_WEATHER =   0x008,//        Mutually exclusive (1)

		// bad weather increases movement costs for airborn ships 3
		// times instead of usual 2 times.
		SAIL_AIR_SLOWED3_BAD_WEATHER =     0x010,//        Mutually exclusive (2)
		// bad weather increases movement costs for airborn ships 4
		// times instead of usual 2 times.
		SAIL_AIR_SLOWED4_BAD_WEATHER =     0x020,//        �utually exclusive (2)
		//self explanatory.
		SAIL_AIR_STOPPED_BAD_WEATHER =     0x040,//        Mutually exclusive (2)

		//heavy ships can sail in coastral region only when has full MP...
		SAIL_HEAVY_STOPPED_BEFORE_LAND =     0x100,           //Klaus
		//...or when coastral region ig guarded by ally, friendly or without guard faction...
		SAIL_HEAVY_FREEMOVE_BEFORE_FRIENDLYLAND =     0x200,           //Klaus
		//...or when there is a town in coastral region
		SAIL_HEAVY_FREEMOVE_BEFORE_SETTLEMENT =     0x400,           //Klaus

		SAIL_SET_FRIENDLYLAND = SAIL_LIGHT_SLOWED4_BAD_WEATHER|SAIL_AIR_STOPPED_BAD_WEATHER|SAIL_HEAVY_STOPPED_BEFORE_LAND|SAIL_HEAVY_FREEMOVE_BEFORE_FRIENDLYLAND,           //Klaus
		SAIL_SET_SETTLEMENT = SAIL_LIGHT_SLOWED4_BAD_WEATHER|SAIL_AIR_STOPPED_BAD_WEATHER|SAIL_HEAVY_STOPPED_BEFORE_LAND|SAIL_HEAVY_FREEMOVE_BEFORE_SETTLEMENT,           //Klaus
		SAIL_SET_COMPLEX = SAIL_LIGHT_SLOWED4_BAD_WEATHER|SAIL_AIR_STOPPED_BAD_WEATHER|SAIL_HEAVY_STOPPED_BEFORE_LAND|SAIL_HEAVY_FREEMOVE_BEFORE_FRIENDLYLAND|SAIL_HEAVY_FREEMOVE_BEFORE_SETTLEMENT,           //Klaus
	};
	int SHIP_CLASS_MODIFERS;

	enum{
		VISIBLE_SEA_ALWAIS = 0x001,
		VISIBLE_SEA_FROM_LIGHTHOUSE   = 0x002,
		VISIBLE_SEA_FROM_ANY_FORTRESS = 0x004,
		VISIBLE_ALL_FROM_WATCHTOWER   = 0x008,
		VISIBLE_ALL_FROM_ANY_FORTRESS = 0x010,
	};
	int ADVANCED_VISIBILITY; // Klaus
	//VISIBILITY_TRANSIT - adjacent regions shown used TRANSIT_REPORT setting
	//VISIBILITY_FARSIGHT - used usual farsight with OBSE0
	enum{
		VISIBILITY_TRANSIT  = 1,
		VISIBILITY_FARSIGHT = 2,
	};
	int ADVANCED_VISIBILITY_TYPE; // Klaus

	// Are we allowing personal mana pool?
	int PERSONAL_MANA;

	// This means powerpoints total of each faction.
	int FACTION_POWER_POINTS;

   enum {
		// activity info (ie taxing 0 regions) will be omitted in report.
		VOID_ACTIVITY_SHOWN = 0x01,

		// taxing a village will count for 2 tax regions, town - 3, city - 4.
		VARIABLE_TAX_COSTS = 0x02,

	  // Each leader uses 1 power point
	  LEADERS_COST_PP = 0x04,

		// Each hero allows to maintain some amount of leaders without using PP
      HEROES_PROVIDE_FREE_LEADERS = 0x08,

   	DEFAULT_UFAS = VOID_ACTIVITY_SHOWN | VARIABLE_TAX_COSTS | LEADERS_COST_PP | HEROES_PROVIDE_FREE_LEADERS,
   };
   int UFAS_OPTIONS;

	// if this option is enabled, every dead soldier's weapon, armor & mount have
   // chance to break (this affects both losers and winners)
   int WIN_AMUNITION_LOSS;

   // how much items will go into spoils
   // (100 - SPOILS_PERCENTAGE) is the percent of items lost
   int SPOILS_PERCENTAGE;

   // if set, then mages at sea regions generates only quarter amount of mana.
   int QUARTER_MANA_AT_SEA;

   // no more than this amount of mana can be generated in starting cities per
	// mage in month independent of skills.
   int STARTING_CITY_MANA_LIMIT;
};

extern GameDefs * Globals;

#endif
