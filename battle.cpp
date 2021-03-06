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
#include "game.h"
#include "battle.h"
#include "army.h"
#include "gamedefs.h"
#include "gamedata.h"

Battle::Battle()
{
    asstext = 0;
    spoils = new ItemList;
}

Battle::~Battle()
{
    if (asstext)
    {
        delete asstext;
    }
    spoils->DeleteAll();
    delete spoils;
}

void Battle::FreeRound(Army * att,Army * def, int ass)
{
	/* Write header */
	AddLine(*(att->leader->name) + " gets a free round of attacks.");

	/* Update both army's shields */
	att->shields.DeleteAll();
	UpdateShields(att);

	def->shields.DeleteAll();
	UpdateShields(def);

        CastEffects(att, def);      // cast one time effects

	//
	// Update the attacking armies round counter
	//
	att->round++;

	/* Run attacks until done */
	int alv = def->NumAlive();
	while (att->CanAttack() && def->NumAlive()) {
		int num = getrandom(att->CanAttack());
		int behind;
		Soldier * a = att->GetAttacker(num, behind);
		DoAttack(att->round, a, att, def, behind, ass);
	}

	/* Write losses */
	def->Regenerate(this);
	alv -= def->NumAlive();
	AddLine(*(def->leader->name) + " loses " + alv + ".");
	AddLine("");
	att->Reset();
}

void Battle::DoAttack(int round, Soldier *a, Army *attackers, Army *def,
		int behind, int ass)
{
	DoSpecialAttack(round, a, attackers, def, behind, 0);
	if (!def->NumAlive()) return;

	if (!behind && (a->riding != -1))
	{
		MountType *pMt = &MountDefs[ItemDefs[a->riding].index];
		if(pMt->mountSpecial != -1)
		{
			int i, num, tot = -1;
			SpecialType *spd = &SpecialDefs[pMt->mountSpecial];
			for(i = 0; i < 4; i++)
			{
				int times = spd->damage[i].value;
				if(spd->effectflags & SpecialType::FX_USE_LEV)
					times *= pMt->specialLev;
				int realtimes = spd->damage[i].minnum + getrandom(times) +
					getrandom(times);
                                if(spd->targflags & SpecialType::HIT_ALLY) {
        				num  = attackers->DoAnAttack(pMt->mountSpecial, realtimes,
						spd->damage[i].type, pMt->specialLev,
						spd->damage[i].flags, spd->damage[i].dclass,
						spd->damage[i].effect, 0, 0, a);
                                }
                                else {
        				num  = def->DoAnAttack(pMt->mountSpecial, realtimes,
						spd->damage[i].type, pMt->specialLev,
						spd->damage[i].flags, spd->damage[i].dclass,
						spd->damage[i].effect, 0, 1, a);
                                }
				if(num != -1)
				{
					if(tot == -1) tot = num;
					else tot += num;
				}
			}
			if(tot != -1)
			{
				AddLine(a->name + " " + spd->spelldesc + ", " +
						spd->spelldesc2 + tot + spd->spelltarget + ".");
			}
		}
	}
	if(!def->NumAlive()) return;

	int numAttacks = a->attacks;
	if(a->attacks < 0) {
		if(round % ( -1 * a->attacks ) == 1)
			numAttacks = 1;
		else
			numAttacks = 0;
	} else if(ass && (Globals->MAX_ASSASSIN_FREE_ATTACKS > 0) &&
			(numAttacks > Globals->MAX_ASSASSIN_FREE_ATTACKS)) {
		numAttacks = Globals->MAX_ASSASSIN_FREE_ATTACKS;
	}

	for (int i = 0; i < numAttacks; i++) {
		WeaponType *pWep = 0;
		if(a->weapon != -1) pWep = &WeaponDefs[ItemDefs[a->weapon ].index];

		if(behind) {
			if(!pWep) break;
			if(!( pWep->flags & WeaponType::RANGED)) break;
		}

		int flags = WeaponType::SHORT;
		int attackType = ATTACK_COMBAT;
		int mountBonus = 0;
		int attackClass = SLASHING;
		if(pWep) {
			flags = pWep->flags;
			attackType = pWep->attackType;
			mountBonus = pWep->mountBonus;
			attackClass = pWep->weapClass;
		}
		def->DoAnAttack( 0, 1, attackType, a->askill, flags, attackClass,
				0, mountBonus, 1, a);
		if (!def->NumAlive()) break;
	}

	a->ClearOneTimeEffects();
}

void Battle::NormalRound(int round,Army * a,Army * b)
{
	/* Write round header */
	AddLine(AString("Round ") + round + ":");

	/* Update both army's shields */
	a->shields.DeleteAll();
	UpdateShields(a);

	b->shields.DeleteAll();
	UpdateShields(b);

        if(round == 1) {   // cast one time effects
                if(a->tac > b->tac) CastEffects(b, a);
                if(a->tac < b->tac) CastEffects(a, b);
                if(a->tac == b->tac) {
                        CastEffects(a, b);
                        CastEffects(b, a);
                }
        }
        
	/* Initialize variables */
	a->round++;
	b->round++;
	int aalive = a->NumAlive();
	int aialive = aalive;
	int balive = b->NumAlive();
	int bialive = balive;
	int aatt = a->CanAttack();
	int batt = b->CanAttack();

	/* Run attacks until done */
	while (aalive && balive && (aatt || batt))
	{
		int num = getrandom(aatt + batt);
		int behind;
		if (num >= aatt)
		{
			num -= aatt;
			Soldier * s = b->GetAttacker(num, behind);
			DoAttack(b->round, s, b, a, behind);
		}
		else
		{
			Soldier * s = a->GetAttacker(num, behind);
			DoAttack(a->round, s, a, b, behind);
                }
		aalive = a->NumAlive();
		balive = b->NumAlive();
		aatt = a->CanAttack();
		batt = b->CanAttack();
	}

	/* Finish round */
	a->Regenerate(this);
	b->Regenerate(this);
	aialive -= aalive;
	AddLine(*(a->leader->name) + " loses " + aialive + ".");
	bialive -= balive;
	AddLine(*(b->leader->name) + " loses " + bialive + ".");
	AddLine("");
	a->Reset();
	b->Reset();
}

void Battle::GetSpoils(AList * losers, ItemList *losses, int ass)
{
	forlist(losers)
	{
		Unit * u = ((Location *) elem)->unit;
		int numalive = u->GetSoldiers();
		int numdead = u->losses;
		forlist(&u->items)
		{
			Item * i = (Item *) elem;
			if(IsSoldier(i->type) || ( ItemDefs[i->type].type & IT_ETHEREAL) ) continue;
			// New rule:  Assassins with RINGS cannot get AMTS in spoils
			// This rule is only meaningful with Proportional AMTS usage
			// is enabled, otherwise it has no effect.
			if((ass == 2) && (i->type == I_AMULETOFTS)) continue;

			// shouldn't happen, however to avoid division by zero it is checked
			float percent;
			if (numalive < 1) percent = 1;
			else percent = (float)numdead/(float)(numalive);

			int num = (int)(i->num * percent);
			int num2;
         
			if(!(ItemDefs[i->type].type & IT_ARTIFACT))
				num2 = (num * Globals->SPOILS_PERCENTAGE + getrandom(100))/100;
			else // IT_ARTIFACT cannot be lost in battle (however it can be broken)
				num2 = num;
			losses->SetNum(i->type, losses->GetNum(i->type) + num);
			spoils->SetNum(i->type, spoils->GetNum(i->type) + num2);
			u->items.SetNum(i->type, i->num - num);
		}
	}
}

int Battle::Run( ARegion * region,
                 Unit * att,
                 AList * atts,
                 Unit * tar,
                 AList * defs,
                 int ass,
                 ARegionList *pRegs )
{
	Army * armies[2];
	assassination = ASS_NONE;
	attacker = att->faction;

	armies[0] = new Army(att,atts,region->type,ass);
	armies[1] = new Army(tar,defs,region->type,ass);

//	WriteArmies(armies[0], armies[1]); //battle report

	int aste = att->GetStealth();
	int dobs = 0;
	forlist(&region->objects)
	{
		Object *o = (Object *) elem;
		forlist(&o->units)
		{
			Unit *u = (Unit *) elem;
			if (u->faction == tar->faction || /* defend EITHER if from same faction */
			   (u->guard != GUARD_AVOID &&
				u->GetAttitude(region,tar) == A_ALLY && /* or from mutually ally factions */
				tar->GetAttitude(region,u) == A_ALLY))
			{
				if(u->GetObservation() > dobs)
					dobs = u->GetObservation();
			}
		}
	}

	if (ass)
	{
		FreeRound(armies[0],armies[1], ass);
	}
	else
	{
		if (armies[0]->tac > armies[1]->tac) FreeRound(armies[0],armies[1]);
		if (armies[1]->tac > armies[0]->tac) FreeRound(armies[1],armies[0]);
	}

	int round = 1;
	while (!armies[0]->Broken() && !armies[1]->Broken() && ((round < 101 && !ass) || round < aste-dobs))
	{
		NormalRound(round++,armies[0],armies[1]);
	}

	if ((armies[0]->Broken() && !armies[1]->Broken()) ||
		(!armies[0]->NumAlive() && armies[1]->NumAlive()))
	{
		if (ass) assassination = ASS_FAIL;

		if (armies[0]->NumAlive())
		{
			AddLine(*(armies[0]->leader->name) + " is routed!");
			FreeRound(armies[1],armies[0]);
		}
		else
		{
			AddLine(*(armies[0]->leader->name) + " is destroyed!");
		}

		DoWonBattleResults(armies[1], armies[0], atts, ass);

		delete armies[0];
		delete armies[1];
		return BATTLE_LOST;
	}

	if ((armies[1]->Broken() && !armies[0]->Broken()) ||
		(!armies[1]->NumAlive() && armies[0]->NumAlive()))
	{
		if (ass)
		{
			assassination = ASS_SUCC;
			asstext = new AString(*(armies[1]->leader->name) +
                                   " is assassinated in " +
                              region->ShortPrint( pRegs ) +
                                                      "!");
		}
		if (armies[1]->NumAlive())
		{
			AddLine(*(armies[1]->leader->name) + " is routed!");
			FreeRound(armies[0],armies[1]);
		}
		else
		{
			if(ass)
			{
				AddLine(*(armies[1]->leader->name) + " is assassinated!");
			}
			else
			{
				AddLine(*(armies[1]->leader->name) + " is destroyed!");
			}
		}

		DoWonBattleResults(armies[0], armies[1], defs, ass);

		delete armies[0];
		delete armies[1];
		return BATTLE_WON;
	}

	if(ass)
	{
		AddLine("The assassin escaped, frightened by alarm.");
	}
	else
	{
		AddLine("The battle ends indecisively.");
	}
	AddLine("");
	AddLine("Total Casualties:");
	armies[0]->Tie(this);
	armies[1]->Tie(this);
	AddLine("");
	AddLine("Spoils: none.");
	AddLine("");
	delete armies[0];
	delete armies[1];

	if(ass)
	{
		att->nomove = 0;
	}

	return BATTLE_DRAW;
}

void Battle::DoWonBattleResults(Army * winners, Army * losers,
                                AList * loseUnits, int ass)
{
	// 1. First losers
	// 1.1. do ammunition breakdown
	losers->GetAmmunitionLosses();

	// 1.2. calculate units' human losses
	losers->GetMenLosses();

	// 1.3. get spoils
	// 1.3.1. get spoils from units' backpacks
	GetSpoils(loseUnits, losers->itemLosses, ass);

	// 1.3.2. get spoils from dead soldiers (get all their
	//        ammunition + generate monspoil)
	// 1.4. disassemble losing army, assemble units
	losers->Lose(this);

	// 1.5. display all losses (men + ammunition + damaged units)
	AddLine("Total Casualties:");
	losers->WriteAllLosses(this);

	// 2. Then winners:
	// 2.1. do ammunition breakdown
	winners->GetAmmunitionLosses();

	// 2.2. do healing
	winners->DoHeal(this);

	// 2.3. calculate units' human losses
	winners->GetMenLosses();

	// 2.4. display all losses (men + ammunition + damaged units)
	winners->WriteAllLosses(this);

	// 2.5. display spoils before it is distributed

	AddLine("");
	if (spoils->Num())
	{
		AddLine(AString("Spoils: ") + spoils->Report(2,0,1) + ".");
		//                                           obs, seeillusions, notfirstcomma  
	}
	else
	{
		AddLine(AString("Spoils: none."));
	}
	AddLine("");

	// 2.6. disassemble winning army, assemble units
	// 2.7. distribute the spoils
	winners->Win(this);
}

void Battle::WriteSides(ARegion * r,
                        Unit * att,
                        Unit * tar,
                        AList * atts,
                        AList * defs,
                        int ass,
                        ARegionList *pRegs )
{
  if (ass) {
    AddLine(*att->name + " attempts to assassinate " + *tar->name
	    + " in " + r->ShortPrint( pRegs ) + "!");
  } else {
    AddLine(*att->name + " attacks " + *tar->name + " in " +
	    r->ShortPrint( pRegs ) + "!");
  }
  AddLine("");

  int dobs = 0;
  int aobs = 0;
  {
	  forlist(defs) {
		  int a = ((Location *)elem)->unit->GetObservation();
		  if(a > dobs) dobs = a;
	  }
  }

  AddLine("Attackers:");
  {
	  forlist(atts) {
		  int a = ((Location *)elem)->unit->GetObservation();
		  if(a > aobs) aobs = a;
		  AString * temp = ((Location *) elem)->unit->BattleReport(dobs);
		  AddLine(*temp);
		  delete temp;
	  }
  }
  AddLine("");
  AddLine("Defenders:");
  {
	  forlist(defs) {
		  AString * temp = ((Location *) elem)->unit->BattleReport(aobs);
		  AddLine(*temp);
		  delete temp;
	  }
  }
  AddLine("");
}

void Battle::Report(Areport * f,Faction * fac) {
  if (assassination == ASS_SUCC && fac != attacker) {
    f->PutStr(*asstext);
    f->PutStr("");
    return;
  }
  forlist(&text) {
    AString * s = (AString *) elem;
    f->PutStr(*s);
  }
}

void Battle::AddLine(const AString & s) {
  AString * temp = new AString(s);
  text.Add(temp);
}

void Game::GetDFacs(ARegion * r,Unit * t,AList & facs)
{
	forlist((&r->objects))
	{
		Object * obj = (Object *) elem;
		forlist((&obj->units))
		{
			Unit * u = (Unit *) elem;
			if (u->IsAlive())
			{
				if (u->faction == t->faction || /* defend EITHER if from same faction */
				   (u->guard != GUARD_AVOID &&
					u->GetAttitude(r,t) == A_ALLY && /* or from mutually ally factions */
					t->GetAttitude(r,u) == A_ALLY))
				/* note that City Guards are added in Game::GetSides, not here */
				{
					if (!GetFaction2(&facs,u->faction->num))
					{  /* if not on the list of defending factions, add it! */
						FactionPtr * p = new FactionPtr;
						p->ptr = u->faction;
						facs.Add(p);
					}
				}
			}
		}
	}
}

void Game::GetAFacs(ARegion *r, Unit *att, Unit *tar, AList &dfacs,
		AList &afacs, AList &atts)
{
	forlist((&r->objects))
	{
		Object * obj = (Object *) elem;
		forlist((&obj->units))
		{
			Unit * u = (Unit *) elem;
			if (u->IsAlive() && u->canattack)
			{
				int add = 0;
				if ((u->faction == att->faction ||
							u->GetAttitude(r,tar) == A_HOSTILE) &&
						(u->guard != GUARD_AVOID || u == att))
				{
					add = 1;
				}
				else
				{
					if(u->guard == GUARD_ADVANCE &&
					   (tar->Forbids(r,u) ||
					    (u->GetAttitude(r,att) == A_ALLY && u->GetAttitude(r,tar) != A_ALLY)))
//					if (u->guard == GUARD_ADVANCE &&
//							u->GetAttitude(r,tar) != A_ALLY)
					{
						add = 1;
					}
					else
					{
						if (u->attackorders)
						{
							forlist(&(u->attackorders->targets))
							{
								UnitId * id = (UnitId *) elem;
								Unit *t = r->GetUnitId(id, u->faction->num);
								if (!t) continue;
								if (t == tar)
								{
									u->attackorders->targets.Remove(id);
									delete id;
								}
								if(t->faction == tar->faction) add = 1;
							}
						}
					}
				}

				if (add)
				{
					if (!GetFaction2(&dfacs,u->faction->num))
					{
						Location * l = new Location;
						l->unit = u;
						l->obj = obj;
						l->region = r;
						atts.Add(l);
						if (!GetFaction2(&afacs,u->faction->num))
						{
							FactionPtr * p = new FactionPtr;
							p->ptr = u->faction;
							afacs.Add(p);
						}
					}
				}
			}
		}
	}
}

int Game::CanAttack(ARegion * r,AList * afacs,Unit * u) {
  int see = 0;
  int ride = 0;
  forlist(afacs) {
    FactionPtr * f = (FactionPtr *) elem;
    if (f->ptr->CanSee(r,u) == 2) {
      if (ride == 1) return 1;
      see = 1;
    }
    if (f->ptr->CanCatch(r,u)) {
      if (see == 1) return 1;
      ride = 1;
    }
  }
  return 0;
}

void Game::GetSides(ARegion *r, AList &afacs, AList &dfacs, AList &atts,
		AList &defs, Unit *att, Unit *tar, int ass, int adv)
{
	if (ass) {
		/* Assassination attempt */
		Location * l = new Location;
		l->unit = att;
		l->obj = r->GetDummy();
		l->region = r;
		atts.Add(l);

		l = new Location;
		l->unit = tar;
		l->obj = r->GetDummy();
		l->region = r;
		defs.Add(l);

		return;
	}

	int j=NDIRS;
	int noaida = 0, noaidd = 0;
	for (int i=-1;i<j;i++) {
		ARegion * r2 = r;
		if (i>=0) {
			r2 = r->neighbors[i];
			if (!r2) continue;
			forlist(&r2->objects) {
				/* Can't get building bonus in another region */
				((Object *) elem)->capacity = 0;
			}
		} else {
			forlist(&r2->objects) {
				Object * o = (Object *) elem;
				/* Set building capacity */
				if (o->incomplete < 1 && o->IsBuilding()) {
					o->capacity = ObjectDefs[o->type].protect;
				}
			}
		}
		forlist (&r2->objects) {
			Object * o = (Object *) elem;
			forlist (&o->units) {
				Unit * u = (Unit *) elem;
				int add = 0;

#define ADD_ATTACK 1
#define ADD_DEFENSE 2
				/* First, can the unit be involved in the battle at all? */
				if (u->IsAlive() && (i==-1 || u->GetFlag(FLAG_HOLDING) == 0)) {
					if (GetFaction2(&afacs,u->faction->num)) {
						/*
						 * The unit is on the attacking side, check if the
						 * unit should be in the battle
						 */
						if (i == -1 || (!noaida)) {
							if (u->canattack &&
									(u->guard != GUARD_AVOID || u==att) &&
									u->CanMoveTo(r2,r) &&
									!::GetUnit(&atts,u->num)) {
								add = ADD_ATTACK;
							}
						}
					} else {
						/* The unit is not on the attacking side */
						/*
						 * First, check for the noaid flag; if it is set,
						 * only units from this region will join on the
						 * defensive side
						 */
						if (!(i != -1 && noaidd)) {
							if (u->type == U_GUARD) {
								/* The unit is a city guardsman */
								if (i == -1 && adv == 0)
									add = ADD_DEFENSE;
							} else if(u->type == U_GUARDMAGE) {
								/* the unit is a city guard support mage */
								if(i == -1 && adv == 0)
									add = ADD_DEFENSE;
							} else {
								/*
								 * The unit is not a city guardsman, check if
								 * the unit is on the defensive side
								 */
								if (GetFaction2(&dfacs,u->faction->num)) {
									if (u->guard == GUARD_AVOID) {
										/*
										 * The unit is avoiding, and doesn't
										 * want to be in the battle if he can
										 * avoid it
										 */
										if (u == tar ||
												(u->faction == tar->faction &&
												 i==-1 &&
												 CanAttack(r,&afacs,u))) {
											add = ADD_DEFENSE;
										}
									} else {
										/*
										 * The unit is not avoiding, and wants
										 * to defend, if it can
										 */
										if (u->CanMoveTo(r2,r)) {
											add = ADD_DEFENSE;
										}
									}
								}
							}
						}
					}
				}

				if (add == ADD_ATTACK) {
					Location * l = new Location;
					l->unit = u;
                                        if(ObjectDefs[o->type].sailors > 0)
                                                l->obj = o;	// Attacker dont give def-bonus from a non-ship-object
                                        else l->obj = r->GetDummy();
					l->region = r2;
					atts.Add(l);
				} else if (add == ADD_DEFENSE) {
						Location * l = new Location;
						l->unit = u;
						l->obj = o;
						l->region = r2;
						defs.Add(l);
				}
			}
		}
		//
		// If we are in the original region, check for the noaid status of
		// the units involved
		//
		if (i == -1) {
			noaida = 1;
			forlist (&atts) {
				Location *l = (Location *) elem;
				if (!l->unit->GetFlag(FLAG_NOAID)) {
					noaida = 0;
					break;
				}
			}
		}

		noaidd = 1;
		{
			forlist (&defs) {
				Location *l = (Location *) elem;
				if (!l->unit->GetFlag(FLAG_NOAID)) {
					noaidd = 0;
					break;
				}
			}
		}
	}
}

void Game::KillDead(Location * l)
{
	if (!l->unit->IsAlive()) {
		l->region->Kill(l->unit);
	} else {
		if (l->unit->advancefrom) {
			l->unit->MoveUnit( l->unit->advancefrom->GetDummy() );
		}
	}
}

int Game::RunBattle(ARegion * r,Unit * attacker,Unit * target,int ass,
                     int adv)
{
	AList afacs,dfacs;
	AList atts,defs;
	FactionPtr * p;
	int result;

	if (ass) {
		if(attacker->GetAttitude(r,target) == A_ALLY) {
			attacker->Error("ASSASSINATE: Can't assassinate an ally.");
			return BATTLE_IMPOSSIBLE;
		}
		/* Assassination attempt */
		p = new FactionPtr;
		p->ptr = attacker->faction;
		afacs.Add(p);
		p = new FactionPtr;
		p->ptr = target->faction;
		dfacs.Add(p);
	} else {
		if( r->IsSafeRegion() ) {
			attacker->Error("ATTACK: No battles allowed in safe regions.");
			return BATTLE_IMPOSSIBLE;
		}
		if(attacker->GetAttitude(r,target) == A_ALLY) {
			attacker->Error("ATTACK: Can't attack an ally.");
			return BATTLE_IMPOSSIBLE;
		}
		GetDFacs(r,target,dfacs);
		if (GetFaction2(&dfacs,attacker->faction->num)) {
			attacker->Error("ATTACK: Can't attack an ally.");
			return BATTLE_IMPOSSIBLE;
		}
		GetAFacs(r,attacker,target,dfacs,afacs,atts);
	}

	GetSides(r,afacs,dfacs,atts,defs,attacker,target,ass,adv);

	if(atts.Num() <= 0) {
		// This shouldn't happen, but just in case
		Awrite(AString("Cannot find any attackers!"));
		return BATTLE_IMPOSSIBLE;
	}
	if(defs.Num() <= 0) {
		// This shouldn't happen, but just in case
		Awrite(AString("Cannot find any defenders!"));
		return BATTLE_IMPOSSIBLE;
	}

	Battle * b = new Battle;
	b->WriteSides(r,attacker,target,&atts,&defs,ass, &regions );

	battles.Add(b);
	forlist(&factions) {
		Faction * f = (Faction *) elem;
		if (GetFaction2(&afacs,f->num) || GetFaction2(&dfacs,f->num) ||
				r->Present(f)) {
			BattlePtr * p = new BattlePtr;
			p->ptr = b;
			f->battles.Add(p);
		}
	}
	result = b->Run(r,attacker,&atts,target,&defs,ass, &regions );

	/* Remove all dead units */
	{
		forlist(&atts) {
			KillDead((Location *) elem);
		}
	}
	{
		forlist(&defs) {
			KillDead((Location *) elem);
		}
	}
	return result;
}


void Soldier::CopyItems (ItemList * it)
{
	it->SetNum(race, it->GetNum(race)+1);

	if (weapon != -1)
	{
		it->SetNum(weapon, it->GetNum(weapon) + 1);
	}
	if(armor != -1)
	{
		it->SetNum(armor, it->GetNum(armor) + 1);
	}
	if(cloakarmor != -1)
	{
		it->SetNum(cloakarmor, it->GetNum(cloakarmor) + 1);
	}
	if(riding != -1)
	{
		it->SetNum(riding, it->GetNum(riding) + 1);
	}

	int battleType;
	for(battleType = 1; battleType < NUMBATTLEITEMS; battleType++)
	{
		BattleItemType *pBat = &BattleItemDefs[ battleType ];

		if(GET_BIT(battleItems, battleType))
		{
			int item = pBat->itemNum;
			it->SetNum(item, it->GetNum(item) + 1);
		}
	}
}

void Army::Display(Battle * b, AString caption)
{
// compile a caption
   AString fullcapt = caption + " (" + (AString)count + "/" +
                      (AString)NumAlive() + " soldiers, " +
                      (AString)hitsalive + "/" + (AString)hitstotal +
                      " hits):";
   b->AddLine(fullcapt);

   AList attnames;
   // first make a list of names
	for (int i =0; i<count;i++)
	{
		int fl = 0;
		forlist(&attnames)
                {
			AString * tmp = (AString *) elem;
			if(soldiers[i]->name == *tmp)
				fl=1; // this name is already in list
		}
		if (!fl)
		{	// if the name is not in the list, add it
			AString * nam = new AString;
			*nam = soldiers[i]->name;
			attnames.Add(nam);
		}
	}

	forlist(&attnames)
	{
   		AString * tmp = (AString *) elem;
		// now for each name make a list of items and remember it's skills

		AString * nameSkills = NULL;
		int beh = 0;
		ItemList * it = new ItemList;
		for (int i =0; i<count;i++)
		{
			if(soldiers[i]->name==*tmp)
			{
				// copy soldier's items (race, weapon, armor, etc) to temporary list
				soldiers[i]->CopyItems(it);
				if (i>canfront) beh = 1;
				if (!nameSkills)
				{	// if skills not defined
					nameSkills = new AString("");

					// make a string of skills
					int lvl;
					lvl = soldiers[i]->unit->GetRealSkill(S_TACTICS);
					if (lvl)
					{
						*nameSkills += ", ";
						*nameSkills += SkillDefs[S_TACTICS].name;
						*nameSkills += " ";
						*nameSkills += lvl;
					}

					lvl = soldiers[i]->unit->GetRealSkill(S_COMBAT);
					if (lvl)
					{
						*nameSkills += ", ";
						*nameSkills += SkillDefs[S_COMBAT].name;
						*nameSkills += " ";
						*nameSkills += lvl;
					}

					lvl = soldiers[i]->unit->GetRealSkill(S_LONGBOW);
					if (lvl)
					{
						*nameSkills += ", ";
						*nameSkills += SkillDefs[S_LONGBOW].name;
						*nameSkills += " ";
						*nameSkills += lvl;
					}

					lvl = soldiers[i]->unit->GetRealSkill(S_CROSSBOW);
					if (lvl)
					{
						*nameSkills += ", ";
						*nameSkills += SkillDefs[S_CROSSBOW].name;
						*nameSkills += " ";
						*nameSkills += lvl;
					}

					lvl = soldiers[i]->unit->GetRealSkill(S_RIDING);
					if (lvl)
					{
						*nameSkills += ", ";
						*nameSkills += SkillDefs[S_RIDING].name;
						*nameSkills += " ";
						*nameSkills += lvl;
					}

					if ( Globals->PERSONAL_MANA )
					if ( soldiers[i]->unit->combat != -1 )
					{
						*nameSkills += ", Spell: ";
						*nameSkills += SkillDefs[soldiers[i]->unit->combat].name;
						*nameSkills += " ";
						*nameSkills += soldiers[i]->unit->GetRealSkill(soldiers[i]->unit->combat);
					}
				}
			}
		}

		AString nameRep = *tmp;
		if (beh) nameRep += ", behind";
		nameRep += it->BattleReport();
		if (nameSkills) nameRep += *nameSkills;

/*		if (soldiers[i]->unit->describe)
		{
			*nameRep += "; ";
			*nameRep += *soldiers[i]->unit->describe;
		}*/
		nameRep += ".";
		b->AddLine (nameRep);
		delete it;
   }

}

void Battle::WriteArmies(Army * attarm, Army * defarm)
{
	AddLine("Sides (exact battle report):");
	attarm->Display(this, "Attacking army");
	AddLine("");
	defarm->Display(this, "Defending army");
	AddLine("");
}
