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
// MODIFICATIONS
// Date        Person            Comments
// ----        ------            --------
// 2001/Feb/23 Joseph Traub      Made skill texts runtime generated
//
#include "skills.h"
#include "items.h"
#include "object.h"
#include "gamedata.h"
#include "astring.h"

#define ITEM_ENABLED(X) (!(ItemDefs[(X)].flags & ItemType::DISABLED))
#define ITEM_DISABLED(X) (ItemDefs[(X)].flags & ItemType::DISABLED)
#define SKILL_ENABLED(X) (!(SkillDefs[(X)].flags & SkillType::DISABLED))
#define SKILL_DISABLED(X) (SkillDefs[(X)].flags & SkillType::DISABLED)
#define OBJECT_ENABLED(X) (!(ObjectDefs[(X)].flags & ObjectType::DISABLED))
#define OBJECT_DISABLED(X) (ObjectDefs[(X)].flags & ObjectType::DISABLED)


AString *ShowSkill::Report(Faction *f)
{
	if(SkillDefs[skill].flags & SkillType::DISABLED) return NULL;

	AString *str = new AString;
	int val;
	RangeType *range = NULL;

	// Here we pick apart the skill
	switch (skill) {
		case S_FARMING:
			if(level > 1) break;
			*str += "This skill deals with all aspects of grain production.";
			break;
		case S_RANCHING:
			if(level > 1) break;
			*str += "This skill deals with all aspects of livestock "
				"production.";
			break;
		case S_MINING:
			if(level > 1) break;
			*str += "This skill deals with all aspects of extracting raw "
				"metals and gems from the earth. Metals and gems tend to be "
				"found more often in mountainous regions, but may be found "
				"elsewhere as well.";
			break;
		case S_LUMBERJACK:
			if(level > 1) break;
			*str += "This skill deals with all aspects of various wood "
			    "production. Woods are more often found in forests, but "
				"may also be found elsewhere.";
			break;
		case S_QUARRYING:
			if(level > 1) break;
			*str += "This skill deals with all aspects of various stone "
				"production. Mountains are the main producers of stone, but "
				"it may be found in other regions as well.";
			break;
		case S_HUNTING:
			if(level > 1) break;
			*str += "This skill deals with all aspects of animal hide "
				"production.";
			break;
		case S_FISHING:
			if(level > 1) break;
			*str += "This skill deals with all aspects of fish production.";
			break;
		case S_HERBLORE:
			if(level > 1) break;
			*str += "This skill deals with all aspects of herb production.";
			break;
		case S_HORSETRAINING:
			if(level > 1) break;
			*str += "This skill deals with all aspects of horse production.";
			break;
		case S_WEAPONSMITH:
			if(level > 1) break;
			*str += "This skill deals with all aspects of weapon "
				"construction and production.";
			break;
		case S_ARMORER:
			if(level > 1) break;
			*str += "This skill deals with all aspects of armor construction "
				"and production.";
			break;
		case S_CARPENTER:
			if(level > 1) break;
			*str += "This skill deals with all aspects of wood based item "
				"production other than for use as weapons.";
			break;
		case S_BUILDING:
			if(level > 1) break;
			*str += "This skill deals with the construction of "
				"fortifications, roads and other buildings, except for "
				"most trade structures.";
			break;
		case S_SHIPBUILDING:
			if(level > 1) break;
			*str += "This skill deals with the constructions of all types "
				"of ships.";
			break;
		case S_ENTERTAINMENT:
			if(level > 1) break;
			*str += "A unit with this skill may use the ENTERTAIN order "
				"to generate funds. The amount of silver gained will "
				"be 20 per man, times the level of the entertainers. "
				"This amount is limited by the region that the unit is in.";
			break;
		case S_TACTICS:
			if(level > 1) break;
			*str += "Tactics allows the unit, and all allies, to gain a "
				"free round of attacks during battle. The army with the "
				"highest level tactician in a battle will receive this free "
				"round; if the highest levels are equal, no free round is "
				"awarded. Only one free round total will be awarded for any "
				"reason.";
			break;
		case S_COMBAT:
			if(level > 1) break;
			*str += "This skill gives the unit a bonus in hand to hand "
				"combat. Also, a unit with this skill may TAX or PILLAGE.";
			break;
		case S_RIDING:
			if(level > 1) break;
			*str += "A unit with this skill, if possessing a mount, may "
				"gain a bonus in combat, if the battle is in a location "
				"where that mount may be utilized and if the skill of the "
				"rider is sufficient to control that mount. The bonus "
				"gained can vary with the mount, the riders skill, and the "
				"terrain.";
			break;
		case S_CROSSBOW:
			if(level > 1) break;
			*str += "A unit with this skill may use a crossbow or other bow "
				"derived from one, either in battle, or to TAX or PILLAGE a "
				"region.";
			break;
		case S_LONGBOW:
			if(level > 1) break;
			*str += "A unit with this skill may use a longbow or other bow "
				"derived from one, either in battle, or to TAX or PILLAGE a "
				"region.";
			break;
		case S_STEALTH:
			if(level > 1) break;
			*str += "A unit with this skill is concealed from being seen";
			if(SKILL_ENABLED(S_OBSERVATION)) {
				*str += ", except by units with an Observation skill greater "
					"than or equal to the stealthy unit's Stealth level";
			}
			*str += ".";
			break;
		case S_OBSERVATION:
			if(level > 1) break;
			*str += "A unit with this skill can see stealthy units or "
				"monsters whose stealth rating is less than or equal to "
				"the observing unit's Observation level. The unit can "
				"also determine the faction owning a unit, provided its "
				"Observation level is higher than the other unit's Stealth "
				"level.";
			break;
		case S_HEALING:
			if(level > 1) break;
			*str += "A unit with this skill is able to heal units hurt in "
				"battle.";
			break;
		case S_SAILING:
			if(level > 1) break;
			*str += "A unit with this skill may use the SAIL order to sail "
				"ships.";
			break;
		case S_FORCE:
			if(level > 1) break;
			*str += "The Force skill is not directly useful to a mage, but "
				"is rather one of the Foundation skills on which other "
				"magical skills are based. The Force skill determines the "
				"power of the magical energy that a mage is able to use. "
				"Note that a Force skill level of 0 does not indicate that "
				"a mage cannot use magical energy, but rather can only "
				"perform magical acts that do not require great amounts of "
				"power.";
			break;
		case S_PATTERN:
			if(level > 1) break;
			*str += "The Pattern skill is not directly useful to a mage, but "
				"is rather one of the Foundation skills on which other "
				"magical skills are based. A mage's Pattern skill indicates "
				"the ability to handle complex magical patterns, and is "
				"important for complicated tasks such as healing and "
				"controlling nature.";
			break;
		case S_SPIRIT:
			if(level > 1) break;
			*str += "The Spirit skill is not directly useful to a mage, but "
				"is rather one of the Foundation skills on which other "
				"magical skills are based. Spirit skill indicates the mage's "
				"ability to control and affect magic and other powers beyond "
				"the material world.";
			break;
		case S_FIRE:
			if(level > 1) break;
			break;
		case S_EARTHQUAKE:
			if(level > 1) break;
			break;
		case S_FORCE_SHIELD:
			if(level > 1) break;
			break;
		case S_ENERGY_SHIELD:
			if(level > 1) break;
			break;
		case S_SPIRIT_SHIELD:
			if(level > 1) break;
			break;
		case S_MAGICAL_HEALING:
			/* XXX -- This should be cleaner somehow. */
			if(level == 1) {
				*str += "This skill enables the mage to magically heal units "
					"after battle. A mage at this level can heal up to 10 "
					"casualties, with a 50 percent rate of success. No order "
					"is necessary to use this spell, it will be used "
					"automatically when the mage is involved in battle.";
			} else if(level == 3) {
				*str += "A mage at this level of skill can work greater "
					"wonders of healing with his new found powers; he may "
					"heal up to 25 casualties, with a success rate of 75 "
					"percent.";
			} else if(level == 5) {
				*str += "A mage at this skill level can bring soldiers back "
					"from near death; he may heal up to 100 casualties, with "
					"a 90 percent rate of success.";
			}
			break;
		case S_GATE_LORE:
			/* XXX -- This should be cleaner somehow. */
			if(level == 1) {
				*str += "Gate Lore is the art of detecting and using magical "
					"Gates, which are spread through the world. The Gates are "
					"numbered in order, but spread out randomly, so there is "
					"no correlation between the Gate number and the Gate's "
					"location. A mage with skill 1 in Gate Lore can see a "
					"Gate if one exists in the same region as the mage. This "
					"detection is automatic; the Gate will appear in the "
					"region report. A mage with skill 1 in Gate Lore may "
					"also jump through a Gate into another region on the same "
					"level containing a gate, selected at random. To use "
					"Gate Lore in this manner, use the syntax CAST Gate_Lore "
					"RANDOM UNITS <unit> ... UNITS is followed by a list "
					"of units to follow the mage through the Gate (the mage "
					"always jumps through the Gate). At level 1, the mage "
					"may carry 150 weight units through the Gate (including "
					"the weight of the mage).";
			} else if (level == 2) {
				*str += "A mage with Gate Lore skill 2 can detect Gates in "
					"adjacent regions. The mage should use the syntax CAST "
					"Gate_Lore DETECT in order to detect these nearby Gates. "
					"Also, at level 2 Gate Lore, the mage may carry 500 "
					"weight units through a Gate when doing a random jump.";
			} else if(level == 3) {
				*str += "A mage with Gate Lore skill 3 and higher can step "
					"through a Gate into another region containing a specific "
					"Gate. To use this spell, use the syntax CAST Gate_Lore "
					"GATE <number> UNITS <unit> ... <number> specifies the "
					"Gate that the mage will jump to. UNITS is followed by a "
					"list of units to follow the mage through the gate (the "
					"mage always jumps through the gate). At level 3, the "
					"mage may carry 150 weight units through the Gate "
					"(including the mage). Also, a level 3 or higher mage "
					"doing a random gate jump may carry 5000 weight units "
					"through the Gate.";
			} else if(level == 4) {
				*str += "A mage with Gate Lore skill 4 may carry 500 weight "
					"units through a Gate.";
			} else if(level == 5) {
				*str += "A mage with Gate Lore skill 5 may carry 5000 weight "
					"units through a Gate.";
			}
			break;
		case S_PORTAL_LORE:
			if(level > 1) break;
			/* XXX -- This should be cleaner somehow. */
			if(ITEM_DISABLED(I_PORTAL)) break;
			*str += "A mage with the Portal Lore skill may, with the aid of "
				"another mage, make a temporary Gate between two regions, and "
				"send units from one region to another. In order to do this, "
				"both mages (the caster, and the target mage) must have "
				"Portals, and the caster must be trained in Portal Lore. The "
				"caster may teleport units weighing up to 500 weight units "
				"times his skill level squared, to the target mage's region. ";
			val = SkillDefs[skill].rangeIndex;
			if(val != -1) range = &RangeDefs[val];
			if(range) {
				*str += " The target region must be within ";
				*str += range->rangeMult;
				switch(range->rangeClass) {
					case RangeType::RNG_LEVEL:
						*str += " times the caster's skill level ";
						break;
					case RangeType::RNG_LEVEL2:
						*str += " times the caster's skill level squared ";
						break;
					case RangeType::RNG_LEVEL3:
						*str += " times the caster's skill level cubed ";
						break;
					default:
					case RangeType::RNG_ABSOLUTE:
						break;
				}
				*str += "regions of the caster. ";
			}
			*str += "To use this skill, CAST Portal_Lore <target> UNITS "
				"<unit> ..., where <target> is the unit number of the "
				"target mage, and <unit> is a list of units to be "
				"teleported (the casting mage may teleport himself, if "
				"he so desires).";
			break;
		case S_FARSIGHT:
			if(level > 1) break;
			*str += "A mage with this skill may obtain region reports on "
				"distant regions. The report will be as if the mage was in "
				"the distant region himself.";
			val = SkillDefs[skill].rangeIndex;
			if(val != -1) range = &RangeDefs[val];
			if(range) {
				if(range->flags & RangeType::RNG_SURFACE_ONLY) {
					*str += " This skill only works on the surface of the "
						"world.";
				}
				*str += " The target region must be within ";
				*str += range->rangeMult;
				switch(range->rangeClass) {
					case RangeType::RNG_LEVEL:
						*str += " times the caster's skill level ";
						break;
					case RangeType::RNG_LEVEL2:
						*str += " times the caster's skill level squared ";
						break;
					case RangeType::RNG_LEVEL3:
						*str += " times the caster's skill level cubed ";
						break;
					default:
					case RangeType::RNG_ABSOLUTE:
						break;
				}
				*str += "regions of the caster. ";
				if(range->flags & RangeType::RNG_CROSS_LEVELS) {
					*str += "Coordinates of locations not on the surface are "
						"scaled to the surface coordinates for this "
						"calculation. Attempting to view across different "
						"levels increases the distance by ";
					*str += range->crossLevelPenalty;
					*str += " per level difference. ";
					*str += "To use this skill, CAST Farsight REGION <x> <y> "
						"<z> where <x>, <y>, and <z> are the coordinates of "
						"the region that you wish to view. If you omit the "
						"<z> coordinate, the <z> coordinate of the caster's "
						"current region will be used.";
					if(Globals->UNDERWORLD_LEVELS +
							Globals->UNDERDEEP_LEVELS == 1) {
						*str += " The <z> coordinate for the surface is '1' "
							"and the <z>-coordinate for the underworld is "
							"'2'.";
					}
					*str += " Note that Farsight cannot be used either into "
						"or out of the Nexus.";
				} else {
					*str += "To use this skill, CAST Farsight REGION <x> "
						"<y>, where <x> and <y> are the coordinates of the "
						"region that you wish to view.";
				}
			}
			if(Globals->IMPROVED_FARSIGHT) {
				*str += " Any other skills which the mage has which give "
					"region information will be used when farsight is used.";
			} else {
				*str += " Note that Farsight does not work in conjunction "
					"with other skills or spells; the mage can only rely on "
					"his normal facilities while casting Farsight.";
			}
			break;
		case S_MIND_READING:
			/* XXX -- This should be cleaner somehow. */
			if(level == 1) {
				*str += "A mage with Mind Reading skill 1 may cast the spell "
					"and determine the faction affiliation of any unit he can "
					"see. To use the spell in this manner, CAST Mind_Reading "
					"<unit>, where <unit> is the target unit.";
			} else if (level == 3) {
				*str += "A mage with Mind Reading skill 3 will automatically "
					"determine the faction affiliation of any unit he can "
					"see. Usage of this skill is automatic, and no order is "
					"needed to use it.";
			} else if (level == 5) {
				*str += "A mage with Mind Reading skill 5 can get a full "
					"unit report on any unit he can see. To use this skill, "
					"CAST Mind_Reading <unit> where <unit> is the target "
					"unit.";
			}
			break;
		case S_TELEPORTATION:
			if(level > 1) break;
			/* XXX -- This should be cleaner somehow. */
			*str += "A mage with this skill may teleport himself across"
				"great distances, even without the use of a gate. The mage "
				"may teleport up to 50 weight units per skill level.";
			val = SkillDefs[skill].rangeIndex;
			if(val != -1) range = &RangeDefs[val];
			if(range) {
				if(range->flags & RangeType::RNG_SURFACE_ONLY) {
					*str += " This skill only works on the surface of the "
						"world.";
				}
				*str += " The target region must be within ";
				*str += range->rangeMult;
				switch(range->rangeClass) {
					case RangeType::RNG_LEVEL:
						*str += " times the caster's skill level ";
						break;
					case RangeType::RNG_LEVEL2:
						*str += " times the caster's skill level squared ";
						break;
					case RangeType::RNG_LEVEL3:
						*str += " times the caster's skill level cubed ";
						break;
					default:
					case RangeType::RNG_ABSOLUTE:
						break;
				}
				*str += "regions of the caster. ";
				if(range->flags & RangeType::RNG_CROSS_LEVELS) {
					*str += "Coordinates of locations not on the surface are "
						"scaled to the surface coordinates for this "
						"calculation. Attempting to view across different "
						"levels increases the distance by ";
					*str += range->crossLevelPenalty;
					*str += " per level difference. ";
					*str += "To use this skill, CAST Teleportation REGION "
						"<x> <y> <z> where <x>, <y>, and <z> are the "
						"coordinates of the region that you wish to "
						"teleport to. If you omit the <z> coordinate, the "
						"<z> coordinate of the caster's current region will "
						"be used.";
					if(Globals->UNDERWORLD_LEVELS +
							Globals->UNDERDEEP_LEVELS == 1) {
						*str += " The <z> coordinate for the surface is '1' "
							"and the <z>-coordinate for the underworld is "
							"'2'.";
					}
					*str += " Note that Teleportation cannot be used either "
						"into or out of the Nexus.";
				} else {
					*str += "To use this skill, CAST Teleportation REGION "
						"<x> <y>, where <x> and <y> are the coordinates of "
						"the region that you wish to teleport to.";
				}
			}
			break;
		case S_WEATHER_LORE:
			if(level > 1) break;
			/* XXX -- This should be templated */
			*str += "Weather Lore is the magic of the weather; a mage with "
				"this skill can predict the weather in nearby regions. "
				"Weather Lore also allows further study into more powerful "
				"areas of magic. The weather may be predicted for 3 months "
				"at level 1, 6 months at level 3 and a full year at level "
				"5.";
			val = SkillDefs[skill].rangeIndex;
			if(val != -1) range = &RangeDefs[val];
			if(range) {
				if(range->flags & RangeType::RNG_SURFACE_ONLY) {
					*str += " This skill only works on the surface of the "
						"world.";
				}
				*str += " The target region must be within ";
				*str += range->rangeMult;
				switch(range->rangeClass) {
					case RangeType::RNG_LEVEL:
						*str += " times the caster's skill level ";
						break;
					case RangeType::RNG_LEVEL2:
						*str += " times the caster's skill level squared ";
						break;
					case RangeType::RNG_LEVEL3:
						*str += " times the caster's skill level cubed ";
						break;
					default:
					case RangeType::RNG_ABSOLUTE:
						break;
				}
				*str += "regions of the caster. ";
				if(range->flags & RangeType::RNG_CROSS_LEVELS) {
					*str += "Coordinates of locations not on the surface are "
						"scaled to the surface coordinates for this "
						"calculation. Attempting to view across different "
						"levels increases the distance by ";
					*str += range->crossLevelPenalty;
					*str += " per level difference. ";
					*str += "To use this skill, CAST Weather_Lore REGION "
						"<x> <y> <z> where <x>, <y>, and <z> are the "
						"coordinates of the region where you wish to "
						"predict the weather. If you omit the <z> "
						"coordinate, the <z> coordinate of the caster's "
						"current region will be used.";
					if(Globals->UNDERWORLD_LEVELS +
							Globals->UNDERDEEP_LEVELS == 1) {
						*str += " The <z> coordinate for the surface is '1' "
							"and the <z>-coordinate for the underworld is "
							"'2'.";
					}
					*str += " Note that Weather Lore cannot be used either "
						"into or out of the Nexus.";
				} else {
					*str += "To use this skill, CAST Weather_Lore REGION "
						"<x> <y>, where <x> and <y> are the coordinates of "
						"the region where you wish to predict the weather.";
				}
			}
			*str += " A mage with Weather Lore skill will perceive the use "
				"of Weather Lore by any other mage in the same region.";
			break;
		case S_SUMMON_WIND:
			if(level > 1) break;
                        *str += "A mage with knowledge of Summon Wind can summon up the "
                                "powers of the wind to aid him in sea or air travel. When "
                                "aboard a ship mages with knowledge of Summon Wind can join "
                                "their forces in order to aid ship's movement. If sum total "
                                "of their skill levels is equal or greater than the ship's "
                                "class, the ship will gain 2 movement points bonus. Usage of "
                                "this spell is automatic.";
			break;
		case S_SUMMON_STORM:
			if(level > 1) break;
			break;
		case S_SUMMON_TORNADO:
			if(level > 1) break;
			break;
		case S_CALL_LIGHTNING:
			if(level > 1) break;
			break;
		case S_CLEAR_SKIES:
			/* XXX -- this range stuff needs cleaning up */
			if(level > 1) break;
			if(SkillDefs[skill].flags & SkillType::CAST) {
				*str += "When cast using the CAST order, it causes the "
					"region to have good weather for the entire month; "
					"movement is at the normal rate (even if it is winter) "
					"and the economic production of the region is improved "
					"for a month (this improvement of the economy will "
					"actually take effect during the turn after the spell "
					"is cast).";
				val = SkillDefs[skill].rangeIndex;
				if(val != -1) range = &RangeDefs[val];
				if(range) {
					if(range->flags & RangeType::RNG_SURFACE_ONLY) {
						*str += " This skill only works on the surface of "
							"the world.";
					}
					*str += " The target region must be within ";
					*str += range->rangeMult;
					switch(range->rangeClass) {
						case RangeType::RNG_LEVEL:
							*str += " times the caster's skill level ";
							break;
						case RangeType::RNG_LEVEL2:
							*str += " times the caster's skill level squared ";
							break;
						case RangeType::RNG_LEVEL3:
							*str += " times the caster's skill level cubed ";
							break;
						default:
						case RangeType::RNG_ABSOLUTE:
							break;
					}
					*str += "regions of the caster. ";
					if(range->flags & RangeType::RNG_CROSS_LEVELS) {
						*str += "Coordinates of locations not on the surface "
							"are scaled to the surface coordinates for this "
							"calculation. Attempting to view across "
							"different levels increases the distance by ";
						*str += range->crossLevelPenalty;
						*str += " per level difference. ";
						*str += "To use this skill, CAST Clear_Skies REGION "
							"<x> <y> <z> where <x>, <y>, and <z> are the "
							"coordinates of the region where you wish to "
							"improve the weather. If you omit the <z> "
							"coordinate, the <z> coordinate of the caster's "
							"current region will be used.";
						if(Globals->UNDERWORLD_LEVELS +
								Globals->UNDERDEEP_LEVELS == 1) {
							*str += " The <z> coordinate for the surface is "
								"'1' and the <z>-coordinate for the "
								"underworld is '2'.";
						}
						*str += " Note that Clear Skies cannot be used "
							"either into or out of the Nexus.";
					} else {
						*str += "To use this skill, CAST Clear_Skies REGION "
							"<x> <y>, where <x> and <y> are the coordinates "
							"of the region where you wish to improve the "
							"weather.";
					}
				} else {
					*str += " To use the spell in this fashion, CAST "
						"Clear_Skies; no arguments are necessary.";
				}
			}
			break;
		case S_NATURE_LORE:
			if(level > 1) break;
//			*str += "Earth Lore is the study of nature, plants, and animals. "
			*str += "Nature Lore is the study of nature, plants, and animals. "
				"A mage with knowledge of Nature Lore can use his knowledge "
				"of nature to aid local farmers, raising money for himself, "
				"and aiding the production of grain or livestock in the "
				"region. To use the spell, CAST Nature_Lore; the mage will "
				"receive an amount of money based on his level, and the "
				"economy of the region. Also, a mage with knowledge of Nature "
				"Lore will detect the use of Nature Lore by any other mage in "
				"the same region.";
			break;
		case S_WOLF_LORE:
			/* XXX -- This should be cleaner somehow. */
			if(level > 1) break;
			if(ITEM_DISABLED(I_WOLF)) break;
			*str += "A mage with Wolf Lore skill may summon dire wolves, who will "
				"fight for him in combat. A mage may summon a number of dire "
				"wolves equal 1 to 6 per his skill level; the dire wolves will "
				"be placed in the mages inventory. To summon dire wolves, the "
                                "mage should issue the order CAST Wolf_Lore.";
			break;
		case S_BIRD_LORE:
			/* XXX -- This should be cleaner somehow. */
			if(level == 1) {
				*str += "A mage with Bird Lore may control the birds of the "
					"sky. At skill level 1, the mage can control small "
					"birds, sending them to an adjacent region to obtain a "
					"report on that region. (This skill only works on the "
					"surface of the world, as there are no birds elsewhere)."
					" To use this skill, CAST Bird_Lore DIRECTION <dir>, "
					"where <dir> is the direction the mage wishes the birds "
					"to report on.";
			} else if (level == 2) {
				if(ITEM_DISABLED(I_RAVEN)) break;
				*str += "A mage with Bird Lore 2 can summon ravens to join "
					"him, who will aid him in combat, and provide for flying "
					"transportation. Ravens may be given to other units, as they follow "
				        "instructions mindlessly. A mage may summon a number of ravens "
					"equal 1 to 3 per his skill level; the ravens "
					"will appear in his inventory. To summon an raven, issue "
					"the order CAST Bird_Lore raven.";
			} else if (level == 3) {
				if(ITEM_DISABLED(I_EAGLE)) break;
				*str += "A mage with Bird Lore 3 can summon eagles to join "
					"him, who will aid him in combat, and provide for flying "
					"transportation. Eagles may be given to other units, as they follow "
				        "instructions mindlessly. A mage may summon number of eagles equal "
                                        "level - 2 under his control; the eagles "
					"will appear in his inventory. To summon an eagle, issue "
					"the order CAST Bird_Lore eagle.";
			} else if (level == 4) {
				if(ITEM_DISABLED(I_ALBATROSS)) break;
				*str += "A mage with Bird Lore 4 can summon albatrosses to join "
					"him, who will aid him in combat, and provide for flying "
					"transportation. Albatrosses may be given to other units, "
                                        "as they follow instructions mindlessly. A mage may summon "
                                        "a number of albatrosses equal level - 3; the albatrosses "
					"will appear in his inventory. To summon an albatross, issue "
					"the order CAST Bird_Lore albatross.";
			}
			break;
		case S_DRAGON_LORE:
			/* XXX -- This should be cleaner somehow. */
			if(level == 1) {
			        if(ITEM_DISABLED(I_WYVERN)) break;
			        *str += "A mage with Dragon Lore skill can summon dragons to "
				        "join him, to aid in battle, and provide flying "
				        "transportation. A mage at level 1 can summoning a wyverns. "
				        "Wyverns may be given to other units, as they follow "
                                        "instructions mindlessly. A mage may summon a number of"
				        "wyverns equal his skill level per turn "
				        "To attempt to summon a wyverns, CAST Dragon_Lore WYVR.";
                        } else if(level == 3) {
			        if(ITEM_DISABLED(I_GREENDRAGON)) break;
			        *str += "A mage with Dragon Lore 3 can summon green dragons to "
				        "join him, to aid in battle, and provide flying "
				        "transportation. A mage may summon a number of "
				        "green dragons equal 1 to 3 per turn. "
				        "To attempt to summon a green dragons, CAST Dragon_Lore GDRA.";
                        } else if(level == 4) {
			        if(ITEM_DISABLED(I_BLUEDRAGON)) break;
			        *str += "A mage with Dragon Lore 4 can summon blue dragons to "
				        "join him, to aid in battle, and provide flying "
				        "transportation. A mage may summon a one blue dragon per turn. "
                                        "A mage may have number of blue dragons equal level - 1 under "
                                        "his control. To attempt to summon a blue dragon, CAST Dragon_Lore UDRA.";
                        } else if(level == 5) {
			        if(ITEM_DISABLED(I_REDDRAGON)) break;
			        *str += "A mage with Dragon Lore 5 can summon red dragon to "
				        "join him, to aid in battle, and provide flying "
				        "transportation. A mage may summon only a one red dragon. "
                                        "A mage may not have red dragon with another a dragons. "
                                        "To attempt to summon a red dragon, CAST Dragon_Lore RDRA.";
                        }
			break;
		case S_NECROMANCY:
			if(level > 1) break;
			*str += "Necromancy is the magic of death; a mage versed in "
				"Necromancy may raise and control the dead, and turn the "
				"powers of death to his own nefarious purposes. The "
				"Necromancy skill does not have any direct application, but "
				"is required to study the more powerful Necromantic skills. "
				"A mage with knowledge of Necromancy will detect the use of "
				"Necromancy by any other mage in the same region.";
			break;
		case S_SUMMON_SKELETONS:
			/* XXX -- This should be cleaner somehow. */
			if(level > 1) break;
			if(ITEM_DISABLED(I_SKELETON)) break;
			*str += "A mage with the Summon Skeletons skill may summon "
				"skeletons into his inventory, to aid him in battle. "
				"Skeletons may be given to other units, as they follow "
				"instructions mindlessly. A mage can summon skeletons "
				"equal 1 to 12 per his skill level. "
				"To use the spell, use the order CAST Summon_Skeletons, "
				"and the mage will summon as many skeletons as he is able.";
			break;
		case S_RAISE_UNDEAD:
			/* XXX -- This should be cleaner somehow. */
			if(level > 1) break;
			if(ITEM_DISABLED(I_UNDEAD)) break;
			*str += "A mage with the Raise Undead skill may summon undead "
				"into his inventory, to aid him in battle. Undead may be "
				"given to other units, as they follow instructions "
				"mindlessly. A mage can summon undead equal 1 to 6 per "
                                "his skill level. To use the spell, use the order "
                                "CAST Raise_Undead and the mage will summon as many "
                                "undead as he is able.";
			break;
		case S_SUMMON_LICH:
			/* XXX -- This should be cleaner somehow. */
			if(level > 1) break;
			if(ITEM_DISABLED(I_LICH)) break;
			*str += "A mage with the Summon Lich skill may summon a lich "
				"into his inventory, to aid him in battle. Liches may be "
				"given to other units, as they follow instructions "
				"mindlessly. A mage has a 20 percent times his skill level "
				"chance of summoning a lich; to summon a lich, use "
				"the order CAST Summon_Lich.";
			break;
		case S_CREATE_AURA_OF_FEAR:
			if(level > 1) break;
			break;
		case S_SUMMON_BLACK_WIND:
			if(level > 1) break;
			break;
		case S_BANISH_UNDEAD:
			if(level > 1) break;
			break;
		case S_DEMON_LORE:
			if(level > 1) break;
			*str += "Demon Lore is the art of summoning and controlling "
				"demons. The Demon Lore skill does not give the mage any "
				"direct skills, but is required to study further into the "
				"Demonic arts. A mage with knowledge of Demon Lore will "
				"detect the use of Demon Lore by any other mage in the same "
				"region.";
			break;
		case S_SUMMON_IMPS:
			/* XXX -- This should be cleaner somehow. */
			if(level > 1) break;
			if(ITEM_DISABLED(I_IMP)) break;
			*str += "A mage with the Summon Imps skill may summon imps into "
				"his inventory, to aid him in combat. A mage may summon 1 to 10 "
				"imp per skill level. To use this spell, the mage should "
                                "issue the order CAST Summon_Imps, and the mage will "
                                "summon as many imps as he is able.";
			break;
		case S_SUMMON_DEMON:
			/* XXX -- This should be cleaner somehow. */
			if(level > 1) break;
			if(ITEM_DISABLED(I_DEMON)) break;
			*str += "A mage with the Summon Demon skill may summon demons "
				"into his inventory, to aid him in combat. A mage may summon "
				"1 to 4 demon per skill level. To use this spell, the mage "
                                "should issue the order CAST Summon_Demon.";
			break;
		case S_SUMMON_BALROG:
			/* XXX -- This should be cleaner somehow. */
			if(level > 1) break;
			if(ITEM_DISABLED(I_BALROG)) break;
			*str += "A mage with the Summon Balrog skill may summon a balrog "
				"into his inventory, to aid him in combat. A mage has a 20 "
				"percent times his skill level chance of summoning a balrog. "
				"A mage may have only one balrog under his control. "
				"To use this spell, the mage should issue the order "
                                "CAST Summon_Balrog.";
			break;
		case S_SUMMON_GOLEM:
			/* XXX -- This should be cleaner somehow. */
			if(level == 1) {
			        if(ITEM_DISABLED(I_EGOLEM)) break;
			        *str += "A mage with Summon Golem skill can summon golems to "
				        "join him, to aid in battle. A mage at level 1 can "
                                        "summoning a earth golem. Earth golems may not be given "
                                        "to other units. A mage may summon a number of "
				        "earth golems equal his skill level per turn. "
				        "To attempt to summon a earth golems, "
                                        "CAST Summon_Golem earth_golem.";
                        } else if(level == 2) {
			        if(ITEM_DISABLED(I_IGOLEM)) break;
			        *str += "A mage with Summon Golem skill can summon golems to "
				        "join him, to aid in battle. A mage at level 2 can "
                                        "summoning a iron golem. Iron golems may not be given "
                                        "to other units. A mage may summon a number of "
				        "iron golems equal his skill level minus 1 per turn. "
				        "To attempt to summon a iron golems, "
                                        "CAST Summon_Golem iron_golem.";
                        } else if(level == 3) {
			        if(ITEM_DISABLED(I_FGOLEM)) break;
			        *str += "A mage with Summon Golem skill can summon golems to "
				        "join him, to aid in battle. A mage at level 3 can "
                                        "summoning a fire golem. Fire golems may not be given "
                                        "to other units. A mage may summon a number of "
				        "fire golems equal his skill level minus 2 per turn. "
				        "To attempt to summon a fire golems, "
                                        "CAST Summon_Golem fire_golem.";
                        }
			break;
		case S_BANISH_DEMONS:
			if(level > 1) break;
			break;
		case S_ILLUSION:
			if(level > 1) break;
			*str += "Illusion is the magic of creating images of things that "
				"do not actually exist. The Illusion skill does not have any "
				"direct applications, but is required for further study of "
				"Illusionary magic. A mage with knowledge of the Illusion "
				"skill will detect the use of Illusion by any other mage in "
				"the same region.";
			break;
		case S_PHANTASMAL_ENTERTAINMENT:
			/* XXX -- This should be cleaner somehow */
			if(level > 1) break;
			*str += "A mage with the Phantasmal Entertainment skill may use "
				"his powers of Illusion to earn money by creating "
				"illusionary fireworks, puppet shows, etc. In effect, "
				"Phantasmal Entertainment grants the mage Entertainment "
				"skill equal to five times his Phantasmal Entertainment "
				"level. To use this skill, use the ENTERTAIN order.";
			break;
		case S_CREATE_PHANTASMAL_BEASTS:
			/* XXX -- This should be cleaner somehow. */
			if(level == 1) {
				*str += "A mage with Create Phantasmal Beasts may summon "
					"illusionary beasts that appear in the mage's inventory. "
					"These beasts will fight in combat, but do not attack, "
					"and are killed whenever they are attacked.";
				if(ITEM_ENABLED(I_IWOLF)) {
					*str += " Create Phantasmal Beasts at level 1 allows the "
						"mage to summon illusionary dire wolves; the number the "
						"mage can summon, or have in his inventory at one "
						"time is equal to the mage's skill squared times 4. "
						"To use this spell, the mage should CAST "
						"Create_Phantasmal_Beasts WOLF <number>, where "
						"<number> is the number of dire wolves that the mage "
						"wishes to have appear in his inventory.";
				}
				*str += " Note: illusionary beasts will appear on reports as "
					"if they were normal items, except on the owner's "
					"report, where they are marked as illusionary. To "
					"reference these items in orders, you must prepend an "
					"'i' to the normal string. (For example: to reference "
					"an illusionary wolf, you would use 'iwolf').";
			} else if (level == 3) {
				if(ITEM_DISABLED(I_IEAGLE)) break;
				*str += "Create Phantasmal Beasts at level 3 allows the mage "
					"to summon illusionary eagles into his inventory. To "
					"summon illusionary eagles, the mage should CAST "
					"Create_Phantasmal_Beasts EAGLE <number>, where <number> "
					"is the number of eagles that the mage wishes to have "
					"appear in his inventory. The number of eagles that a "
					"mage may have in his inventory is equal to his skill "
					"level, minus 2, squared.";
			} else if(level == 5) {
				if(ITEM_DISABLED(I_IDRAGON)) break;
				*str += "Create Phantasmal Beasts at level 5 allows the "
					"mage to summon an illusionary dragon into his "
					"inventory. To summon an illusionary dragon, the mage "
					"should CAST Create_Phantasmal_Beasts DRAGON; the mage "
					"can only have one illusionary dragon in his inventory "
					"at one time.";
			}
			break;
		case S_CREATE_PHANTASMAL_UNDEAD:
			/* XXX -- This should be cleaner somehow. */
			if(level == 1) {
				*str += "A mage with Create Phantasmal Undead may summon "
					"illusionary undead that appear in the mage's inventory. "
					"These undead will fight in combat, but do not attack, "
					"and are killed whenever they are attacked.";
				if(ITEM_ENABLED(I_ISKELETON)) {
					*str += " Create Phantasmal Undead at level 1 allows the "
						"mage to summon illusionary skeletons; the number "
						"the mage can summon, or have in his inventory at "
						"one time is equal to the mage's skill squared times "
						"4. To use this spell, the mage should CAST "
						"Create_Phantasmal_Undead SKELETON <number>, where "
						"<number> is the number of skeletons that the mage "
						"wishes to have appear in his inventory.";
				}
				*str += " Note: illusionary undead will appear on reports as "
					"if they were normal items, except on the owner's "
					"report, where they are marked as illusionary. To "
					"reference these items in orders, you must prepend an "
					"'i' to the normal string. (Example: to reference an "
					"illusionary skeleton, you would use 'iskeleton').";
			} else if(level == 3) {
				if(ITEM_DISABLED(I_IUNDEAD)) break;
				*str += "Create Phantasmal Undead at level 3 allows the mage "
					"to summon illusionary undead into his inventory. To "
					"summon illusionary undead, the mage should CAST "
					"Create_Phantasmal_Undead UNDEAD <number>, where <number> "
					"is the number of undead that the mage wishes to have "
					"appear in his inventory. The number of undead that a "
					"mage may have in his inventory is equal to his skill "
					"level, minus 2, squared.";
			} else if (level == 5) {
				if(ITEM_DISABLED(I_ILICH)) break;
				*str += "Create Phantasmal Undead at level 5 allows the mage "
					"to summon an illusionary lich into his inventory. To "
					"summon an illusionary lich, the mage should CAST "
					"Create_Phantasmal_Undead LICH; the mage can only have "
					"one illusionary lich in his inventory at one time.";
			}
			break;
		case S_CREATE_PHANTASMAL_DEMONS:
			/* XXX -- This should be cleaner somehow. */
			if(level == 1) {
				*str += "A mage with Create Phantasmal Demons may summon "
					    "illusionary demons that appear in the mage's "
						"inventory. These demons will fight in combat, but "
						"do not attack, and are killed whenever they are "
						"attacked.";
				if(ITEM_ENABLED(I_IIMP)) {
					*str += " Create Phantasmal Demons at level 1 allows the "
						"mage to summon illusionary imps; the number the "
						"mage can summon, or have in his inventory at one "
						"time is equal to the mage's skill squared times 4. "
						"To use this spell, the mage should CAST "
						"Create_Phantasmal_Demons IMP <number>, where "
						"<number> is the number of imps that the mage wishes "
						"to have appear in his inventory.";
				}
				*str += " Note: illusionary demons will appear on reports as "
					"if they were normal items, except on the owner's "
					"report, where they are marked as illusionary. To "
					"reference these items in orders, you must prepend an "
					"'i' to the normal string. (Example: to reference an "
					"illusionary imp, you would use 'iimp').";
			} else if (level == 3) {
				if(ITEM_DISABLED(I_IDEMON)) break;
				*str += "Create Phantasmal Demons at level 3 allows the mage "
					"to summon illusionary demons into his inventory. To "
					"summon illusionary demons, the mage should CAST "
					"Create_Phantasmal_Demons DEMON <number>, where <number> "
					"is the number of demons that the mage wishes to have "
					"appear in his inventory. The number of demons that a "
					"mage may have in his inventory is equal to his skill "
					"level, minus 2, squared.";
			} else if (level == 5) {
				if(ITEM_DISABLED(I_IBALROG)) break;
				*str += "Create Phantasmal Demons at level 5 allows the mage "
					"to summon an illusionary balrog into his inventory. To "
					"summon an illusionary balrog, the mage should CAST "
					"Create_Phantasmal_Demons BALROG; the mage can only have "
					"one illusionary balrog in his inventory at one time.";
			}
			break;
		case S_INVISIBILITY:
			/* XXX -- This should be cleaner somehow. */
			if(level > 1) break;
			*str += "The Invisibility skill allows a mage to render other "
				"units nearly invisible to other factions, giving them a +3 "
				"bonus to Stealth. This invisibility will last until the "
				"next Magic round. To cast this spell, use the order CAST "
				"Invisibility UNITS <unit> ..., where <unit> is a list of "
				"the units that the mage wishes to render invisible. A mage "
				"may render invisible a number of men equal to "
				"his skill level squared.";
			break;
		case S_TRUE_SEEING:
			if(level > 1) break;
			*str += "A mage with the True Seeing spell can see illusions "
				"for what they really are. Whether or not the mage can see "
				"through the illusion depends on his True Seeing skill "
				"being higher that the Illusion skill of the mage casting "
				"the illusion. This spell does not require any order to "
				"use; it is used automatically.";
			if(SKILL_ENABLED(S_OBSERVATION)) {
				*str += "In addition, a mage with the True Seeing skill "
					"receives a bonus to his Observation skill equal to his "
					"True Seeing skill divided by 2, rounded up. ";
			}
			*str += "This spell allows a mage to cast other units, giving them a +1 "
				"bonus to Observation. This bonus will last until the "
				"next Magic round. To cast this spell, use the order CAST "
				"True_Seeing UNITS <unit> ..., where <unit> is a list of "
				"the units. A mage may add bonus a number of men equal to "
				"his double skill level. This bonus don't added to True "
                                "Seeing passive bonus.";
			break;
		case S_DISPEL_ILLUSIONS:
			if(level > 1) break;
			break;
		case S_ARTIFACT_LORE:
			if(level > 1) break;
			*str += "Artifact Lore is one of the most advanced forms of "
				"magic; in general, creation of an artifact requires both "
				"Artifact Lore, and the appropriate skill for the item being "
				"created. A mage with knowledge of the Artifact Lore skill "
				"will detect the use of Artifact Lore by any other mage in "
				"the region.";
			break;
		case S_CREATE_RING_OF_INVISIBILITY:
			/* XXX -- This should be cleaner somehow. */
			if(ITEM_DISABLED(I_RINGOFI)) break;
			if(level > 1) break;
			*str += "A mage with the Create Ring of Invisibility skill may "
				"create a Ring of Invisibility, which grants a 3 bonus to a "
				"unit's effective Stealth (note that a unit must possess "
				"one ring for each man to gain this bonus).";
			if(ITEM_ENABLED(I_AMULETOFTS)) {
				*str += " A Ring of Invisibility has one limitation; a "
					"unit possessing a ring cannot assassinate, nor steal "
					"from, a unit with an Amulet of True Seeing.";
			}
			*str += " A mage has a 100 percent times his level chance to "
				"create a Ring of Invisibility. To use this spell, the mage "
				"should CAST Create_Ring_of_Invisibility.";
			break;
		case S_CREATE_CLOAK_OF_INVULNERABILITY:
			/* XXX -- This should be cleaner somehow. */
			if(ITEM_DISABLED(I_CLOAKOFI)) break;
			if(level > 1) break;
			*str += "A mage with the Create Cloak of Invulnerability skill "
				"may create a Cloak of Invulnerability. A mage has a 100 "
				"percent times his level chance to create a Cloak of "
				"Invulnerability. To use this spell, the mage should CAST "
				"Create_Cloak_of_Invulnerability.";
			break;
		case S_CREATE_STAFF_OF_FIRE:
			/* XXX -- This should be cleaner somehow. */
			if(ITEM_DISABLED(I_STAFFOFF)) break;
			if(level > 1) break;
			*str += "A mage with the Create Staff of Fire skill may create a "
				"Staff of Fire. A Staff of Fire allows any mage to throw "
				"fireballs in combat as if he had a Fire skill of 3. A mage "
				"has a 100 percent times his level chance to create a Staff "
				"of Fire. To use this spell, CAST Create_Staff_of_Fire.";
			break;
		case S_CREATE_STAFF_OF_LIGHTNING:
			/* XXX -- This should be cleaner somehow. */
			if(ITEM_DISABLED(I_STAFFOFL)) break;
			if(level > 1) break;
			*str += "A mage with the Create Staff of Lightning skill may "
				"create a Staff of Lightning. A Staff of Lightning allows "
				"any mage to call down lightning bolts as if he had Call "
				"Lightning skill of 3. A mage has a 100 percent times his "
				"level chance to create a Staff of Lightning. To use this "
				"spell, CAST Create_Staff_of_Lightning.";
			break;
		case S_CREATE_AMULET_OF_TRUE_SEEING:
			/* XXX -- This should be cleaner somehow. */
			if(ITEM_DISABLED(I_AMULETOFTS)) break;
			if(level > 1) break;
			*str += "A mage with the Create Amulet of Tree Seeing skill may "
				"create an Amulet of True Seeing. This amulet gives the "
				"possessor a bonus of 2 to his effective Observation skill.";
			if(ITEM_ENABLED(I_RINGOFI)) {
				*str += "Also, a unit with an Amulet of True Seeing cannot "
					"be assassinated by, nor have items stolen by, a unit "
					"with a Ring of Invisibility (Note that the unit must "
					"have at least one Amulet of True Seeing per man to "
					"repel a unit with a Ring of Invisibility).";
			}
			*str += "A mage has a 100 percent times his skill level chance to "
			   "create an Amulet of True Seeing. To use this spell, CAST "
			   "Create_Amulet_of_True_Seeing.";
			break;
		case S_CREATE_AMULET_OF_PROTECTION:
			/* XXX -- This should be cleaner somehow. */
			if(ITEM_DISABLED(I_AMULETOFP)) break;
			if(level > 1) break;
			*str += "A mage with the Create Amulet of Protection skill may "
				"create Amulets of Protection, which grants the possesor a "
				"personal Spirit Shield of 3. A mage may create his skill "
				"level of these amulets per turn. To use this spell, CAST "
				"Create_Amulet_of_Protection.";
			break;
		case S_CREATE_RUNESWORD:
			/* XXX -- This should be cleaner somehow. */
			if(ITEM_DISABLED(I_RUNESWORD)) break;
			if(level > 1) break;
			*str += "A mage with the Create Runesword skill may create a "
				"Runesword, which allows the wielder "
				"to project an Aura of Fear in battle, as if he had Create "
				"Aura of Fear skill of level 3 (provided the wielder is "
				"not casting any other combat spells). A mage has a 100 "
				"percent times his skill level chance of creating a "
				"Runesword. To cast this spell, CAST Create_Runesword.";
			break;
		case S_CREATE_SHIELDSTONE:
			/* XXX -- This should be cleaner somehow. */
			if(ITEM_DISABLED(I_SHIELDSTONE)) break;
			if(level > 1) break;
			*str += "A mage with the Create Shieldstone skill may create "
				"Shieldstones, which confers upon the possessor a personal "
				"Energy Shield of 3. A mage may create his skill level in "
				"Shieldstones per turn. To use this spell, CAST "
				"Create_Shieldstone.";
			break;
		case S_CREATE_MAGIC_CARPET:
			/* XXX -- This should be cleaner somehow. */
			if(ITEM_DISABLED(I_MCARPET)) break;
			if(level > 1) break;
			*str += "A mage with the Create Magic Carpet skill may create "
				"Magic Carpets, which provide for flying transportation. A "
				"Magic Carpet can carry up to 15 weight units in the air. "
				"Casting this spell allows the mage to create his skill "
				"level in Magic Carpets. To cast the spell, CAST "
				"Create_Magic_Carpet.";
			break;
		case S_ENGRAVE_RUNES_OF_WARDING:
			/* XXX -- This should be cleaner somehow. */
			if(level == 1) {
				*str += "A mage with the Engrave Runes of Warding may "
					"engrave runes of warding on a building; these runes "
					"will give any occupants of the building a +3 "
					"bonus defence versus energy and spirit attacks. "
					"To use this spell, the mage should CAST Engrave_Runes_of_Warding, "
					"and be within the building he wishes to engrave runes "
					"upon. This spell costs 10000 silver to cast.";
				if(OBJECT_ENABLED(O_TOWER)) {
					*str += " At level 1, the mage may engrave runes of "
						"warding upon a Tower.";
				}
			} else if (level == 2) {
				int comma = 0;
				if(OBJECT_DISABLED(O_FORT) && OBJECT_DISABLED(O_MTOWER) && OBJECT_DISABLED(O_KEEP))
					break;
				*str += "At this level, the mage may engrave runes of "
					"warding upon ";
				if(OBJECT_ENABLED(O_MTOWER)) {
					*str += "a Magic Tower";
					comma = 1;
				}
				if(OBJECT_ENABLED(O_FORT)) {
					if(comma) *str += ", ";
					*str += "a Fort";
					comma = 1;
				}
				if(OBJECT_ENABLED(O_KEEP)) {
					if(comma) *str += ", and ";
					*str += "a Keep";
				}
				*str += ".";
			} else if (level == 3) {
				if(OBJECT_ENABLED(O_CASTLE)) {
					*str += "At this level, the mage may engrave runes of "
						"warding upon a Castle.";
				}
			} else if (level == 4) {
				if(OBJECT_ENABLED(O_CITADEL)) {
					*str += "At this level, the mage may engrave runes of "
						"warding upon a Citadel.";
				}
			} else if(level == 5) {
				int comma = 0;
				if(OBJECT_DISABLED(O_MKEEP) && OBJECT_DISABLED(O_MCASTLE) && OBJECT_DISABLED(O_MCITADEL))
					break;
				*str += "At this level, the mage may engrave runes of "
					"warding upon ";
				if(OBJECT_ENABLED(O_MKEEP)) {
					*str += "a Magical Keep";
					comma = 1;
				}
				if(OBJECT_ENABLED(O_MCASTLE)) {
					if(comma) *str += ", ";
					*str += "a Magical Castle";
				}
				if(OBJECT_ENABLED(O_MCITADEL)) {
					if(comma) *str += ", and ";
					*str += "a Magical Citadel";
				}
				*str += ", which grants the inhabitants"
					"a +5 defence bonus versus energy and spirit attacks.";
			}
			break;
		case S_CONSTRUCT_GATE:
			/* XXX -- This should be cleaner somehow. */
			if(level > 1) break;
			*str += "A mage with the Construct Gate skill may construct a "
				"Gate in a region. The mage has a 20 percent times his "
				"skill level chance of success, and the attempt costs 50000 "
				"silver. To use this spell, the mage should issue the order "
				"CAST Construct_Gate.";
			break;
                // Goony
		case S_EARTH_LORE:
			if(level > 1) break;
			*str += "Earth Lore is the study of materials and how they can be combined together. "
				"This is a pure knowledge without direct application. "
				"A mage with knowledge of Earth "
				"Lore will detect the use of Earth Lore by any other mage in "
				"the same region.";
			break;
		case S_ALCHEMY:
			if(level > 1) break;
			*str += "Alchemy is the study of non-mechanical material transformations. "
				"A mage with knowledge of Alchemy can use his knowledge "
				"to create amount of money from almost any common material. "
                                "To use the spell, CAST Alchemy; the mage will "
				"receive 100 times square of skill level coins. ";
			break;
		case S_TRANSMUTE:
			/* XXX -- This should be cleaner somehow. */
			if(level > 1) break;
			*str += "A mage with the Transmute skill may magically "
				"transform some common raw materials to advanced ones, e.g. "
                                "iron to mithril. A mage may create "
                                "square of his skill level raw units per turn. "
                                "The mage should issue the order "
                                "CAST Transmute <Material_to_Transmute> to cast this spell.";
			break;
		case S_TRANSMUTE_WEAPON:
			/* XXX -- This should be cleaner somehow. */
			if(level > 1) break;
			*str += "A mage with the Transmute Weapon skill may magically "
				"transform simple weapons to similar advanced ones, e.g. "
                                "simple swords to mithril swords. A mage may create "
                                "square of his skill level advanced weapons per turn. "
                                "The mage should issue the order "
                                "CAST Transmute_Weapon <Weapon_to_Transmute> to cast this spell.";
			break;
		case S_ENCHANT_WEAPON:
			/* XXX -- This should be cleaner somehow. */
			if(level > 1) break;
			*str += "A mage with the Enchant Weapon skill may magically "
				"transform simple weapons to their enchanted variants, e.g. "
                                "simple swords to enchanted swords. A mage may create "
                                "5 times of his skill level enchanted weapons per turn. "
                                "The mage should issue the order "
                                "CAST Enchant_Weapon <Weapon_to_Enchant> to cast this spell.";
			break;
		case S_TRANSMUTE_ARMOR:
			/* XXX -- This should be cleaner somehow. */
			if(level > 1) break;
			*str += "A mage with the Transmute Armor skill may magically "
				"transform simple armors to similar advanced ones, e.g. "
                                "plate armors to mithril armors. A mage may create "
                                "square of his skill level advanced armors per turn. "
                                "The mage should issue the order "
                                "CAST Transmute_Armor <Armor_to_Transmute> to cast this spell.";
			break;
		case S_ENCHANT_ARMOR:
			/* XXX -- This should be cleaner somehow. */
			if(level > 1) break;
			*str += "A mage with the Enchant Armor skill may magically "
				"transform simple armors to their enchanted variants, e.g. "
                                "plate armors to enchanted plate armors. A mage may create "
                                "5 times of his skill level enchanted armors per turn. "
                                "The mage should issue the order "
                                "CAST Enchant_Armor <Armor_to_Enchant> to cast this spell.";
			break;
                //--
		case S_CONSTRUCT_PORTAL:
			/* XXX -- This should be cleaner somehow. */
			if(level > 1) break;
			if(ITEM_DISABLED(I_PORTAL)) break;
			*str += "A mage with the Construct Portal skill may construct a "
				"Portal";
			if(SKILL_ENABLED(S_PORTAL_LORE)) {
				*str += " for use with the Portal Lore skill";
			}
			*str += ". The mage has a 20 percent times his skill level "
				"chance of creating a Portal, and the attempt costs 600 "
				"silver. To use this spell, CAST Construct_Portal.";
			break;
		case S_MANIPULATE:
			if(!Globals->APPRENTICES_EXIST) break;
			if(level > 1) break;
			*str += "A unit with this skill becomes an apprentice mage. "
				"While apprentices cannot cast spells directly, they can "
				"use magic items normally only usable by mages. Continued "
				"study of this skill gives no further advantages.";
			break;
		case S_WEAPONCRAFT:
			if(level > 1) break;
			*str += "The weaponcraft skill is an advanced version of the "
				"weaponsmith skill.";
			break;
		case S_ARMORCRAFT:
			if(level > 1) break;
			*str += "The armorcraft skill is an advanced version of the "
				"armorsmith skill.";
			break;
		case S_CAMELTRAINING:
			if(level > 1) break;
			*str += "This skill deals with all aspects of camel production.";
			break;
		case S_GEMCUTTING:
			if(level > 1) break;
			*str += "This skill enables a unit to fashion higher quality "
				"gems from lower quality ones.";
			break;
		case S_MONSTERTRAINING:
			if(level > 1) break;
			*str += "This skill deals with all aspects of traking monster "
				"mounts.";
			break;
		case S_COOKING:
			if(level > 1) break;
			*str += "This skill deals with creating provisions from basic "
					"foodstuffs.  A skilled cook can feed many more people "
					"than a farmer alone.";
			break;
		case S_CREATE_FOOD:
			/* XXX -- This should be cleaner somehow. */
			if(level > 1) break;
			if(ITEM_DISABLED(I_FOOD)) break;
			*str += "A mage with the Create Food skill may magically "
				"create food. A mage may create 5 times his skill level "
				"provisions per turn. The mage should issue the order "
				"CAST Create_Food to cast this spell.";
                        break;
                case S_CONCENTRATE_POWER:
			if(level > 1) break;
                        *str += "This skill deals with all aspects of extracting mana "
				"potions. Mana potions tend to be found more often in "
                                "plains, mountains, forests and jungles regions, but "
                                "may be found elsewhere as well.";
                        break;
                case S_MANA_GENERATION:
                        if(level > 1) break;
                        *str += "A mage with the Mana Generation skill may generate "
                                "mana to faction mana pool. A mage generates amount of "
                                "mana equal to the sum of Force, Pattern and Spirit skill "
                                "levels plus the Mana Generation skill level.";
                        break;
                case S_CREATE_MANA_POTION:
                        if(level > 1) break;
                        *str += "A mage with the Create Mana Potion skill may create "
                                "mana potions from faction mana pool. A mage may create "
                                "5 times his skill level mana potions per turn. The mage "
                                "should issue the order CAST Create_Mana_Potion to cast this spell.";
                        break;
                case S_CREATE_CLOAKS:
                        if(level > 1) break;
			*str += "A mage with the Create Cloaks skill may create a Cloak of "
                                "Defence, Cloak of Reflection, Cape of Protection, Cape of "
                                "Shield, Cape of Stability and Cloak of Negation. A mage may "
                                "create a number of these cloaks equal to his skill level per turn."
				" To use this spell, the mage should CAST Create_Cloaks <param>,"
                                " where <param> is name of a cloak.";

                        break;
                case S_CREATE_WINDSTONE:
                        if(level > 1) break;
			*str += "A mage with the Create Windstone skill may create Windstones. "
                                "If loaded on a ship, these bulky items can summon winds, thus "
                                "aiding the ship's movement. To accelerate a ship four Windstones "
                                "are required per class of the ship. A mage can create his skill "
                                "of Windsones per turn. The mage should issue the order "
                                "CAST Create_Windstone to cast this spell.";

                        break;
           
                case S_CHANNEL:
                        if(level > 1) break;
			*str += "A mage with the Channeling skill may channel mana from faction "
			        "Pool to personal pool for later personal usage, charging items,"
                                " and feeding magical monsters. The mage should issue the order "
                                "CAST Channel <from|to> [target] to cast this spell.";

                        break;
	}

	AString temp;
	AString temp1;
	AString temp2;
	int comma = 0;
	int comma1 = 0;
	int comma2 = 0;
	int last = -1;
	int last1 = -1;
	int last2 = -1;
	unsigned int c;
	int i;

        // If this is magic skill
        if(level == 1 && (SkillDefs[skill].flags & SkillType::MAGIC) &&
						(SkillDefs[skill].costcast[0] >= 0) &&
						(Globals->PERSONAL_MANA || (SkillDefs[skill].flags & SkillType::CAST)))
		{
				*str += AString(" Cost of cast this spell is ") +
						SkillDefs[skill].costcast[0] + "/" +
						SkillDefs[skill].costcast[1] + "/" +
						SkillDefs[skill].costcast[2] + "/" +
						SkillDefs[skill].costcast[3] + "/" +
						SkillDefs[skill].costcast[4] + " mana for levels.";
		}
        if(level == 1 && Globals->SUP_SKILL_PP && (SkillDefs[skill].flags & SkillType::MAGIC) &&
                                                                        SkillDefs[skill].costsupply ){
                *str += AString(" Knowlege of this skill demands supply of ") +
                                SkillDefs[skill].costsupply + " faction power points.";
        }

	// If this is a combat spell, note it.
	if(level == 1 && (SkillDefs[skill].flags & SkillType::COMBAT)) {
		*str += AString(" A mage with this skill can cast ") +
			ShowSpecial(SkillDefs[skill].special, level, 0, 0);
		*str += " In order to use this spell in combat, the mage should use "
			"the COMBAT order to set it as his combat spell.";
	}

	// production and ability to see items
	temp += "A unit with this skill is able to determine if a region "
		"contains ";
	temp1 += "A unit with this skill may PRODUCE ";
	temp2 += "A unit with this skill may create ";
	for(i = NITEMS - 1; i >= 0; i--) {
		if(ITEM_DISABLED(i)) continue;
		if(ItemDefs[i].mSkill==skill &&
				ItemDefs[i].mLevel==level &&
				last2==-1) {
			int canmagic = 1;
			for(c = 0; c < sizeof(ItemDefs[i].mInput)/sizeof(Materials); c++) {
				if(ItemDefs[i].mInput[c].item == -1) continue;
				if(ITEM_DISABLED(ItemDefs[i].mInput[c].item)) {
					canmagic = 0;
				}
			}
			if(canmagic) {
				last2 = i;
			}
		}
		if(ItemDefs[i].pSkill == skill && ItemDefs[i].pLevel == level) {
			int canmake = 1;
			int resource = 1;
			for(c = 0; c < sizeof(ItemDefs[i].pInput)/sizeof(Materials); c++) {
				if(ItemDefs[i].pInput[c].item == -1) continue;
				resource = 0;
				if(ITEM_DISABLED(ItemDefs[i].pInput[c].item)) {
					canmake = 0;
				}
			}
			if(canmake && last1 == -1) {
				last1 = i;
			}
			if(resource && (ItemDefs[i].type & IT_ADVANCED) && last == -1) {
				last = i;
			}
		}

	}
	for(i = 0; i < NITEMS; i++) {
		if(ITEM_DISABLED(i)) continue;
		int illusion = ((ItemDefs[i].type & IT_MONSTER) &&
				(ItemDefs[i].index == MONSTER_ILLUSION));
		if(ItemDefs[i].mSkill == skill && ItemDefs[i].mLevel == level) {
			int canmagic = 1;
			for(c = 0; c < sizeof(ItemDefs[i].mInput)/sizeof(Materials); c++) {
				if(ItemDefs[i].mInput[c].item == -1) continue;
				if(ITEM_DISABLED(ItemDefs[i].mInput[c].item)) {
					canmagic = 0;
				}
			}
			if(canmagic) {
				if(comma2) {
					if(last2 == i) {
						if(comma2 > 1) temp2 += ",";
						temp2 += " and ";
					} else {
						temp2 += ", ";
					}
				}
				comma2++;
				temp2 += AString(illusion?"illusory ":"") + ItemDefs[i].names;
				if(f) {
					f->DiscoverItem(i, 1, 1);
				}
			}
		}
		if(ItemDefs[i].pSkill == skill && ItemDefs[i].pLevel == level) {
			int canmake = 1;
			int resource = 1;
			for(c = 0; c < sizeof(ItemDefs[i].pInput)/sizeof(Materials); c++) {
				if(ItemDefs[i].pInput[c].item == -1) continue;
				resource = 0;
				if(ITEM_DISABLED(ItemDefs[i].pInput[c].item)) {
					canmake = 0;
				}
			}
			if(canmake) {
				if(comma1) {
					if(last1 == i) {
						if(comma1 > 1) temp1 += ",";
						temp1 += " and ";
					} else {
						temp1 += ", ";
					}
				}
				comma1++;
				temp1 += AString(illusion?"illusory ":"") + ItemDefs[i].names;
				if(f) {
					f->DiscoverItem(i, 1, 1);
				}
			}
			if(resource && (ItemDefs[i].type & IT_ADVANCED)) {
				if(comma) {
					if(last == i) {
						if(comma > 1) temp += ",";
						temp += " and ";
					} else {
						temp += ", ";
					}
				}
				comma++;
				temp += AString(illusion?"illusory ":"") + ItemDefs[i].names;
			}
		}
	}
	if(comma1) {
		if(!(*str == "")) *str += " ";
		*str += temp1 + ".";
	}
	if(comma) {
		if(!(*str == "")) *str += " ";
		*str += temp + ".";
	}
	if(comma2) {
		if(!(*str == "")) *str += " ";
		*str += temp2 + " via magic.";
	}

	// Buildings
	comma = 0;
	temp = "A unit with this skill may BUILD the following structures: ";
	for(i = 0; i < NOBJECTS; i++) {
		if(OBJECT_DISABLED(i)) continue;
		if(ObjectDefs[i].skill == skill && ObjectDefs[i].level == level) {
			if(comma) temp += ", ";
			comma = 1;
			temp += ObjectDefs[i].name;
			if(f) {
				f->objectshows.Add(ObjectDescription(i));
			}
		}
	}
	if(comma) {
		if(!(*str == "")) *str += " ";
		*str += temp + ".";
	}

	// Required skills
	last = -1;
	if(level == 1) {
		comma = 0;
		int found = 0;
		temp = "This skill requires ";
		for(c=0; c<sizeof(SkillDefs[skill].depends)/sizeof(SkillDepend); c++) {
			if(SkillDefs[skill].depends[c].skill == -1) continue;
			if(SKILL_DISABLED(SkillDefs[skill].depends[c].skill)) continue;
			found = 1;
			if(last == -1) {
				last = c;
				continue;
			}
			temp += SkillStrs(SkillDefs[skill].depends[last].skill) + " " +
				SkillDefs[skill].depends[last].level + ", ";
			last = c;
			comma++;
		}
		if(comma) {
			temp += "and ";
		}
		temp += SkillStrs(SkillDefs[skill].depends[last].skill) + " " +
				SkillDefs[skill].depends[last].level;

		if(found) {
			if(!(*str == "")) *str += " ";
			*str += temp + " to begin to study.";
		}
	}

	if(level == 1) {
		if(SkillDefs[skill].cost) {
			if(!(*str == "")) *str += " ";
			*str += AString("This skill costs ") + SkillDefs[skill].cost +
				" silver per month of study.";
		}
		if(SkillDefs[skill].flags & SkillType::SLOWSTUDY) {
			if(!(*str == "")) *str += " ";
			*str += "This skill is studied at one half the normal speed.";
		}
	}

	temp1 = SkillStrs(skill) + " " + level + ": ";
	if(*str == "") {
		*str = temp1 + "No skill report.";
	} else {
		*str = temp1 + *str;
	}

	return str;
}