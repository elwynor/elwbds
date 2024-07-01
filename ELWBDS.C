/*****************************************************************************
 * BattleDroids v2.0                                                         *
 * Written by Sean Ferrell of The Sourceror's Guild 1991-1995                *
 *                                                                           *
 * June 25, 2012 - Conversion to Worldgroup 3.2 - R. Hadsall                 *
 *                                                                           *
 * Copyright (C) 2005-2024 Rick Hadsall.  All Rights Reserved.               *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      * 
 * it under the terms of the GNU Affero General Public License as published  *
 * by the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              *
 * GNU Affero General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Affero General Public License  *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.     *
 *                                                                           *
 * Additional Terms for Contributors:                                        *
 * 1. By contributing to this project, you agree to assign all right, title, *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies.                              *
 * 2. You grant Rick Hadsall and Elwynor Technologies a non-exclusive,       *
 *    royalty-free, worldwide license to use, reproduce, prepare derivative  *
 *    works of, publicly display, publicly perform, sublicense, and          *
 *    distribute your contributions                                          *
 * 3. You represent that you have the legal right to make your contributions *
 *    and that the contributions do not infringe any third-party rights.     *
 * 4. Rick Hadsall and Elwynor Technologies are not obligated to incorporate *
 *    any contributions into the project.                                    *
 * 5. This project is licensed under the AGPL v3, and any derivative works   *
 *    must also be licensed under the AGPL v3.                               *
 * 6. If you create an entirely new project (a fork) based on this work, it  *
 *    must also be licensed under the AGPL v3, you assign all right, title,  *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies, and you must include these   *
 *    additional terms in your project's LICENSE file(s).                    *
 *                                                                           *
 * By contributing to this project, you agree to these terms.                *
 *                                                                           *
 *****************************************************************************/

#include "gcomm.h"
#include "majorbbs.h"
#include "elwbds.h"

DFAFILE *bdbb;

typedef struct {
  LONG credits;                 /* Credits                 */
  CHAR weapon;                  /* Weapon type             */
  INT xc;                       /* X coord on field        */
  INT yc;                       /* Y coord on field        */
  CHAR chs;                     /* Chassis type            */
  CHAR pwr;                     /* Power rating            */
  CHAR cmp;                     /* Computer rating         */
  CHAR stb;                     /* Stability rating        */
  CHAR man;                     /* Maneuverablility rating */
  CHAR str;                     /* Strength                */
  CHAR spd;                     /* Speed                   */
  CHAR agl;                     /* Agility                 */
  CHAR trg;                     /* Targeting               */
  INT  enr;                     /* Energy available        */
  INT  ar;                      /* Current armor           */
  INT  mar;                     /* Maximum armor           */
  INT  rfreq;                   /* Radio frequencey        */
  INT  pavol;                   /* PA volume               */
  INT  active;                  /* Droid is active         */
  LONG time;                    /* Time in game            */
  CHAR inv[12];                 /* Inventory               */
  INT  flag;                    /* Flag                    */
  INT  rsp;                     /* Resource Points         */
  INT  kills;                   /* Confirmed Kills         */
  INT  cbtdly;                  /* Combat Delay            */
} BDARR;

BDARR *bdarr,*bdptr;

struct bdsave {
  CHAR userid[UIDSIZ];          /* User id                 30 */
  LONG credits;                 /* Credits                 34 */
  CHAR weapon;                  /* Weapon type             35 */
  INT  xc;                      /* X coord on field        39 */
  INT  yc;                      /* Y coord on field        43 */
  CHAR chs;                     /* Chassis type            44 */
  CHAR pwr;                     /* Power rating            45 */
  CHAR cmp;                     /* Computer rating         46 */
  CHAR stb;                     /* Stability rating        47 */
  CHAR man;                     /* Maneuverablility rating 48 */
  CHAR str;                     /* Strength                49 */
  CHAR spd;                     /* Speed                   50 */
  CHAR agl;                     /* Agility                 51 */
  CHAR trg;                     /* Targeting               52 */
  INT  enr;                     /* Energy available        56 */
  INT  ar;                      /* Current armor           60 */
  INT  mar;                     /* Maximum armor           64 */
  INT  rfreq;                   /* Radio frequency         68 */
  INT  pavol;                   /* PA volume               72 */
  INT  active;                  /* Droid is active         76 */
  CHAR inv[12];                 /* Inventory               88 */
  INT  flag;                    /* Flag                    92 */
  INT  rsp;                     /* Resource Points         96 */
  INT  kills;                   /* Confirmed Kills         100 */
  INT  cbtdly;                  /* Combat Delay            104 */
  //CHAR spare[96-84];
} bdsptr;

typedef struct {
  CHAR name[21];                /* Borg name               */
  CHAR user[UIDSIZ];            /* Borg's creator          */
  LONG credits;                 /* Credits                 */
  CHAR weapon;                  /* Weapon type             */
  INT  xc;                      /* X coord on field        */
  INT  yc;                      /* Y coord on field        */
  INT  dx;                      /* X coord of destination  */
  INT  dy;                      /* Y coord of destination  */
  INT  dir;                     /* Direction of travel     */
  CHAR chs;                     /* Chassis type            */
  CHAR pwr;                     /* Power rating            */
  CHAR cmp;                     /* Computer rating         */
  CHAR stb;                     /* Stability rating        */
  CHAR man;                     /* Maneuverablility rating */
  CHAR str;                     /* Strength                */
  CHAR spd;                     /* Speed                   */
  CHAR agl;                     /* Agility                 */
  CHAR trg;                     /* Targeting               */
  INT  enr;                     /* Energy available        */
  INT  ar;                      /* Current armor           */
  INT  mar;                     /* Maximum armor           */
  INT  active;                  /* Droid is active         */
  LONG time;                    /* Time in game            */
  INT  agr;                     /* Aggression              */
  INT  mode;                    /* Active mode             */
  INT  usr;                     /* Following this user     */
  INT  hst;                     /* Hostility               */
  INT  mvbl;                    /* Mode variable           */
  INT  kills;                   /* Confirmed Kills         */
} BDBAR;

BDBAR *bdbar,*bdbpt;

typedef struct {
  CHAR name[15];          /* Borg name              */
  INT  lochs;             /* Borg low chassis model */
  INT  hichs;             /* Borg high chassis model*/
  INT  lowep;             /* Borg low weapon type   */
  INT  hiwep;             /* Borg high weapon type  */
} BDBRG;

BDBRG bbrg[]={
{"Blah",       0, 0, 1, 1},
{"Loki",       0, 0, 1, 1},
{"Hermes",     0, 1, 1, 1},
{"Achilles",   1, 2, 2, 2},
{"Proteus",    1, 2, 2, 2},
{"Odysseus",   1, 2, 2, 2},
{"Perseus",    2, 3, 3, 3},
{"Sparticus",  3, 4, 3, 3},
{"Theseus",    3, 4, 3, 3},
{"Prometheus", 4, 5, 4, 4},
{"Freya",      5, 7, 4, 5},
{"Fenris",     6, 8, 4, 6},
{"Thor",       7, 9, 5, 7},
{"Medusa",    10,12, 5, 8},
{"Cyclops",   11,13, 6,10},
{"Titan",     12,14, 8,10},
{"Dragon",    15,15,11,11}};

#define NUM_BBRG (sizeof(bbrg) / sizeof(bbrg[0]))

CHAR brgmode[8][20]={
"Wander",
"Evade",
"Visit Location",
"Follow User",
"Follow Borg",
"Garrison",
"Visit Base",
"Patrol"};

#define NBORGS 50

typedef struct {
  CHAR *name;             /* obj name         */
  CHAR *desc;             /* obj description  */
  LONG price;             /* price            */
} BDOBJ;

BDOBJ bobj[]={
{"Blah-1","a blah beam",0L},
{"Laser-1","a laser beam",100L},
{"Blaster-1","a particle beam",250L},
{"Plasmagun-1","a plasma beam",500L},
{"Disruptor-1","a disruptor beam",750L},
{"Laser-2","a powerful laser beam",2000L},
{"Blaster-2","a powerful particle beam",5000L},
{"Plasmagun-2","a powerful plasma beam",10000L},
{"Disruptor-2","a powerful disruptor beam",15000L},
{"Laser-3","a pulsed laser beam",20000L},
{"Blaster-3","a pulsed particle beam",50000L},
{"Plasmagun-3","a pulsed plasma beam",100000L},
{"Disruptor-3","a pulsed disruptor beam",150000L},
{"Laser-4","a barrage of pulsed laser beams",100000L},
{"Blaster-4","a barrage of pulsed particle beams",250000L},
{"Plasmagun-4","a barrage of pulsed plasma beams",500000L},
{"Disruptor-4","a barrage of pulsed disruptor beams",750000L},
{"RK-1","",50L},
{"RK-2","",500L},
{"RK-3","",1500L},
{"ER-Scanner","",2500L},
{"EnergyScreen","",5000L},
{"SRM-1","an explosion",100L},
{"SRM-2","an explosion",250L},
{"SRM-3","an explosion",500L},
{"SRM-4","an explosion",750L},
{"MRM-1","an explosion",1000L},
{"MRM-2","an explosion",1500L},
{"MRM-3","an explosion",2000L},
{"MRM-4","an explosion",2500L},
{"LRM-1","an explosion",3250L},
{"LRM-2","an explosion",4000L},
{"LRM-3","an explosion",4750L},
{"LRM-4","an explosion",5500L},
{"ERM-1","an explosion",6500L},
{"ERM-2","an explosion",8500L},
{"ERM-3","an explosion",11500L},
{"ERM-4","an explosion",15500L},
{"LM-1", "shrapnel",100L},
{"LM-2", "shrapnel",250L},
{"LM-3", "shrapnel",500L},
{"LM-4", "shrapnel",1000L},
{"LM-5", "shrapnel",2000L}};

#define NUM_BOBJ (sizeof(bobj) / sizeof(bobj[0]))

#define NUMITM 42

#define IRK1 17
#define IRK2 18
#define IRK3 19
#define IERS 20
#define ISCR 21
#define IMS1 22
#define IMS2 23
#define IMS3 24
#define IMS4 25
#define IMS5 26
#define IMS6 27
#define IMS7 28
#define IMS8 29
#define IMS9 30
#define IMS10 31
#define IMS11 32
#define IMS12 33
#define IMS13 34
#define IMS14 35
#define IMS15 36
#define IMS16 37
#define ILM1 38
#define ILM2 39
#define ILM3 40
#define ILM4 41
#define ILM5 42

typedef struct {
  INT mindm;              /* Minimum Damage     */
  INT maxdm;              /* Maximum Damage     */
  INT range;              /* Range              */
  INT pwrus;              /* Power Use          */
  INT distd;              /* Distance to Detect */
} BDWEP;

BDWEP bwep[]={
{  0,  0,  0,  0,  0},
{  2,  4,  6,  4,  1},
{  3,  6,  5,  5,  2},
{  7, 14,  4, 10,  3},
{  9, 18,  3, 12,  4},
{  4,  8, 12,  8,  2},
{  6, 12, 10, 10,  4},
{ 14, 28,  8, 20,  6},
{ 18, 36,  6, 24,  8},
{  8, 16, 24, 16,  3},
{ 12, 24, 20, 20,  8},
{ 28, 56, 16, 40, 12},
{ 36, 72, 12, 48, 15},
{ 16, 32, 48, 32,  6},
{ 24, 48, 40, 40, 16},
{ 56,112, 32, 80, 24},
{ 72,144, 24, 96, 31}};

#define NUM_BWEP (sizeof(bwep) / sizeof(bwep[0]))

typedef struct {
  INT mindm;              /* Minimum Damage     */
  INT maxdm;              /* Maximum Damage     */
  INT range;              /* Range              */
} BDMIS;

BDWEP bmis[]={
{  2,  4, 10},
{  3,  6, 10},
{  4,  8, 10},
{  5, 10, 10},
{  7, 14, 20},
{ 10, 20, 20},
{ 14, 28, 20},
{ 18, 36, 20},
{ 23, 46, 40},
{ 28, 56, 40},
{ 34, 68, 40},
{ 40, 80, 40},
{ 50,100,100},
{ 65,130,100},
{ 80,160,100},
{100,200,100}

};

typedef struct {
  INT x;                  /*  X Coord       */
  INT y;                  /*  Y Coord       */
  INT time;               /*  Time Left     */
  INT damage;             /*  Damage        */
  INT item;               /*  Item Number   */
} BLAST;

BLAST missle[100],mine[100];

typedef struct {
  CHAR *name;             /*  Chassis name            */
  CHAR *type;             /*  Chassis type            */
  INT weight;             /*  Chassis weight          */
  INT armor;              /*  Chassis armor           */
  INT pwr;                /*  Chassis Power Rating    */
  INT cmp;                /*  Chassis Computer Rating */
  INT stb;                /*  Chassis stability       */
  INT man;                /*  Chassis Maneuverability */
  INT str;                /*  Chassis Strength        */
  INT spd;                /*  Chassis Speed           */
  INT agl;                /*  Chassis Agility         */
  INT trg;                /*  Chassis Targeting       */
  INT wep;                /*  Maximum Weapon Power    */
  INT mis;                /*  Missle Capabilities     */
  INT min;                /*  Landmine Capabilities   */
  LONG price;             /*  Chassis price           */
} BDCHS;

BDCHS bchs[]={
{"Imp"        ,"Biped",
  1,  20,  1,  1,  5, 80,  5, 80, 90,  5,  4, 0, 0,  2000L},
{"Scorpion"   ,"Insectoid",
  2,  30,  2,  2, 10, 90, 10, 90,100, 10,  4, 1, 0,  5000L},
{"Stilleto"   ,"Biped",
  3,  40,  2,  3, 10,100, 10, 80, 90, 20,  5, 1, 0, 10000L},
{"Weasel"     ,"Quadruped",
  4,  50,  2,  4, 20, 95, 15,100, 95, 25,  5, 0, 1, 15000L},
{"Rapier"     ,"Biped",
  5,  60,  3,  5, 15, 90, 20, 80, 90, 40,  5, 2, 0, 20000L},
{"Griffon"    ,"Quadruped",
 10,  80,  4,  6, 35, 90, 30, 90, 90, 50, 10, 0, 1, 30000L},
{"Marauder"   ,"Insectoid",
 15, 100,  5,  7, 30, 90, 35, 80, 85, 55, 10, 2, 0, 35000L},
{"Archer"     ,"Tracked",
 20, 120,  5,  8, 45, 80, 35, 60, 70, 55, 10, 2, 1, 45000L},
{"Jackal"     ,"Quadruped",
 25, 140,  6,  9, 40, 85, 40, 75, 75, 60, 12, 1, 0, 60000L},
{"Centaur"    ,"Quadruped",
 30, 160,  7,  9, 45, 85, 40, 70, 75, 60, 12, 1, 1, 80000L},
{"Ares"       ,"Biped",
 35, 180,  7, 10, 40, 75, 45, 65, 70, 65, 12, 1, 0,110000L},
{"Hyperion"   ,"Biped",
 40, 200,  8, 11, 45, 75, 45, 65, 70, 70, 16, 2, 0,150000L},
{"Vulcan"     ,"Biped",
 45, 230,  9, 11, 50, 75, 50, 60, 65, 75, 16, 2, 0,200000L},
{"Shiva"      ,"Insectoid",
 50, 250, 10, 10, 70, 90, 55, 70, 75, 70, 16,10, 1,275000L},
{"Pleiades"    ,"Tracked",
 55, 260, 10, 11, 70, 80, 55, 70, 75, 70, 20, 2, 1,300000L},
{"Centipede"  ,"Insectoid",
 60, 270, 11, 10, 75, 90, 60, 80, 75, 75, 20, 2, 1,350000L},
{"Juggernaut" ,"Biped",
 65, 280, 10, 12, 60, 75, 65, 60, 60, 80, 20, 4, 0,375000L},
{"Unicorn"    ,"Quadruped",
 70, 290, 12, 12, 70, 85, 65, 70, 70, 75, 24, 4, 1,425000L},
{"Phoenix"    ,"Biped",
 75, 300, 12, 14, 60, 75, 70, 60, 50, 80, 24, 2, 0,475000L},
{"Viper"      ,"Tracked",
 80, 330, 13, 13, 75, 80, 70, 60, 55, 85, 24, 4, 1,500000L},
{"Spectre"    ,"Insectoid",
 85, 350, 15, 15, 90, 90, 60, 70, 90, 90, 32, 4, 1,550000L},
{"Ferret"     ,"Quadruped",
 90, 360, 15, 12, 90, 85, 70, 70, 75, 90, 32, 4, 1,600000L},
{"Colossus"   ,"Biped",
 95, 400, 14, 13, 75, 75,100, 60, 55, 95, 32, 2, 0,650000L},
{"Goliath"    ,"Tracked",
100, 450, 14, 14,100, 80,100, 60, 60,100, 40, 4, 1,700000L},
{"Seraph"     ,"Quadruped",
120, 480, 14, 15, 80, 85, 85, 70, 75,100, 40, 4, 0,800000L},
{"Puck"       ,"Insectoid",
140, 560, 15, 15, 85, 90, 90, 70, 90,100, 40, 4, 0,900000L},
{"Gremlin"    ,"Biped",
160, 640, 15, 16, 80, 80, 80, 60, 55,100, 48, 4, 0,1000000L},
{"Rakshasa"   ,"Quadruped",
180, 720, 15, 17, 85, 85, 85, 70, 75,100, 48, 4, 0,1100000L},
{"Diablo"     ,"Tracked",
200, 800, 16, 16, 85, 80, 90, 60, 60,100, 48, 4, 1,1200000L},
{"Fury"       ,"Tracked",
225, 900, 17, 16, 85, 80, 90, 60, 60,100, 80, 4, 0,1300000L},
{"Nymph"      ,"Insectoid",
250,1000, 17, 17, 90, 90, 95, 70, 90,100, 80,10, 1,1400000L},
{"Brahma"     ,"Biped",
275,1100, 18, 17, 80, 80, 80, 60, 55,100, 80, 4, 0,1500000L},
{"Devaki"     ,"Tracked",
300,1200, 19, 18, 85, 80,100, 60, 60,100, 80,10, 0,1600000L},
{"Savitar"    ,"Quadruped",
350,1400, 20, 19, 85, 85,115, 70, 75,100, 96,10, 1,1700000L},
{"Lotus"      ,"Biped",
400,1600, 30, 21, 80, 80,130, 60, 55,100, 96, 4, 0,1800000L},
{"Apocalypse" ,"Tracked",
450,1800, 40, 23,100, 80,150, 60, 60,100, 96,10, 0,1900000L},
{"Dragon"     ,"Quadruped",
500,2000, 50, 25,100, 20,200, 55, 70,100, 96,10, 1,2000000L}};

#define CHSMOD 37

CHAR *sensor[]={
"movement",
"rapid movement",
"slow movement",
"an explosion",
"an energy blast",
"small explosions",
"a missle arming",
"blah",
"energy pulse",
"energy pulse",
"energy pulse",
"energy pulse",
"energy burst",
"energy burst",
"energy burst",
"energy burst",
"several energy bursts",
"several energy bursts",
"several energy bursts",
"several energy bursts",
"a multitude of energy bursts",
"a multitude of energy bursts",
"a multitude of energy bursts",
"a multitude of energy bursts",
"transport ship",
"heavy impact"};

HMCVFILE bdmb;
INT newstt;
CHAR sel;
INT upddrd;
INT movbrg;
INT spnbrg;
INT chbrgd;
INT dist;
INT showlon;
/***
INT bdnl;
***/
CHAR *dirxl[]={"N","NE","E","SE","S","SW","W","NW"};
CHAR *dirbds[]={"south","southwest","west","northwest","north","northeast","east","southeast"};
CHAR *dirds[]={"north","northeast","east","southeast","south","southwest","west","northwest"};
CHAR *dircds[]={"North","Northeast","East","Southeast","South","Southwest","West","Northwest"};
INT dirmx[]={0,1,1,1,0,-1,-1,-1};
INT dirmy[]={-1,-1,0,1,1,1,0,-1};

typedef struct {
  CHAR *name1;           /* Obj Name 1   */
  CHAR *name2;           /* Obj Name 2   */
  INT  xc;               /* Obj X coords */
  INT  yc;               /* Obj Y coords */
} BDTER;

BDTER bter[]={
{"a huge building","the shop",2500,2500},
{"a large building","a headquarters building",2400,2400},
{"a large building","a headquarters building",2600,2600},
{"a large building","a headquarters building",2400,2600},
{"a large building","a headquarters building",2600,2400},
{"a building complex","a cyborg base",2500,2300},
{"a building complex","a cyborg base",2500,2700},
{"a building complex","a cyborg base",2300,2500},
{"a building complex","a cyborg base",2700,2500}
};

#define NTOBJS 9

INT chkbdu(INT usrn);
VOID bdkick(VOID);
VOID updbrg(VOID);
INT genbrg(INT brg, INT usr);
VOID updbchs(INT chs);
INT desbrg(INT brg, INT usr);
VOID brgmod(INT brg);
VOID brgdir(INT brg);
VOID brgmov(INT brg);
VOID mbrgto(INT who, INT newx, INT newy);
INT brgatt(INT brg);
VOID bdmnu(VOID);
GBOOL crsbd(VOID);
INT bdinp(VOID);
INT scan(INT who, INT max, INT di);
INT bscan(INT who, INT brg, INT max, INT di);
INT blast(BLAST *obj);
GBOOL logbd(VOID);
VOID radout(INT user);
VOID outloc(INT xc,INT yc,INT user,INT othusr);
VOID outall(INT user,INT othusr);
VOID outusr(INT brg);
VOID gendrd(VOID);
VOID updchs(INT chs);
INT drdcnt(VOID);
INT brgcnt(VOID);
INT btpcnt(CHAR *type);
VOID shwsta(VOID);
INT locdrd(CHAR *uid);
INT locbrg(CHAR *bid);
VOID lstbrg(INT usr);
INT scndrd(CHAR *drd, INT ds);
INT bscndrd(CHAR *drd, INT brg, INT ds);
VOID scnbrg(INT brg);
VOID exitbd(VOID);
INT bdgdir(CHAR *s);
INT chkdirf(INT xc, INT yc, INT xo, INT yo);
VOID gensnsu(INT from, INT type, INT max, INT pmt ,INT user);
VOID gensns(INT xloc, INT yloc, INT type, INT max, INT user);
VOID pasys(INT xloc, INT yloc, INT volume, CHAR *messg);
VOID shop(VOID);
VOID bdpmt(VOID);
VOID moveto(INT x, INT y);
INT bdmove(CHAR *whatd);
INT comm(CHAR *msg);
INT dmgdrd(INT usr, INT brg, INT who, INT damg, INT itnm, CHAR *dir, INT pmt, INT user);
INT dmgbrg(INT usr, INT brg, INT who, INT damg);
INT fire(CHAR *dir);
INT radio(CHAR *msg);
INT bdinv(INT cmd);
INT putms(INT dmg, INT nm);
INT putlm(INT dmg, INT nm);
INT use(CHAR *what);
INT arm(CHAR *what,INT ds);
INT launch(CHAR *d,INT ds);
VOID scanner(CHAR *d, INT scand);
VOID bscanner(CHAR *d, INT brg, INT scand);
INT attack(CHAR *who);
VOID playbd(VOID);
VOID strbd(VOID);
INT getnum(CHAR *us);
INT invspc(VOID);
VOID bdbuy(VOID);
VOID bdsell(VOID);
INT numinv(INT who, INT obj);
INT bdnum(CHAR *tmpstr);
INT bdrand(INT lo,INT hi);
VOID setbd(VOID);
VOID shtbd(VOID);
VOID hupbd(VOID);
VOID delbd(CHAR *id);
VOID bdlpl(VOID);
VOID bdspl(VOID);

#define VERSION "2.0"

INT bdstt;               /* BattleDroids State Number                 */

struct module elwbds={   /* Module interface block                    */
   "",                   /* Description for main menu  (config'able)  */
   logbd,                /*    user logon supplemental routine        */
   crsbd,                /*    input routine if selected              */
   dfsthn,               /*    status-input routine if selected       */
   NULL,                 /*    "injoth" routine for this module       */
   NULL,                 /*    user logoff supplemental routine       */
   hupbd,                /*    hangup (lost carrier) routine          */
   NULL,                 /*    midnight cleanup routine               */
   delbd,                /*    delete-account routine                 */
   shtbd,                /*    finish-up (sys shutdown) routine       */
};


/****************************************************************************/

INT
chkbdu(INT usrn)
{
  if ((usrn>=0) && (usrn<=nterms)) {
    if ((usroff(usrn)->usrcls<=SUPIPG) ||
	(usroff(usrn)->state!=bdstt) ||
	(bdarr[usrn].active==0))
      return(0);
    if (usroff(usrn)->substt!=PLYBD)
      return(2);
    return(1);
  } else return(0);
}

VOID EXPORT
init__elwbds(VOID)
{
  INT i;

  shocst(spr("ELW BattleDroids v%s",VERSION),"(C) Copyright 2005-2024 Elwynor Technologies - www.elwynor.com");
  stzcpy(elwbds.descrp,gmdnam("ELWBDS.MDF"),MNMSIZ);

  bdstt=register_module(&elwbds);
  bdbb=dfaOpen("elwbds.dat",sizeof(struct bdsave),NULL);
  bdarr=(BDARR *)alczer(nterms*sizeof(BDARR));
  bdbar=(BDBAR *)alczer(NBORGS*sizeof(BDBAR));
  for (i=0; i<NBORGS; i++) bdbar[i].active=0;

  bdmb=opnmsg("elwbds.mcv");
  setmbk(bdmb);
  showlon=ynopt(SHOWLON);

#ifdef __BUILDV10MODULE  
  srand((unsigned)time(NULL)); // BBSV10
#else
  randomize(); // WG32
#endif
  rtkick(20,bdkick);
}

VOID
bdkick(VOID)
{
  BDARR *bdtp;
  INT i,p;

  setbd();
  if (++upddrd==2) {
    upddrd=0;
    for (i=0; i<nterms; i++) {
      if (chkbdu(i)==1) {
	bdtp=&bdarr[i];
	p=(bdtp->pwr*5);
	if (bdtp->enr<p) {
	  bdtp->enr+=bdtp->pwr;
	  if (bdtp->enr>p) bdtp->enr=p;
	}
	bdtp->time+=2;
	bdtp->cbtdly-=2;
	if (bdtp->cbtdly<1) bdtp->cbtdly=0;
      }
    }
    updbrg();
  }
  for (i=0; i<100; i++) {
    if (missle[i].damage)
      if (!(--missle[i].time)) blast(&missle[i]);
    if (mine[i].damage)
      if (!(--mine[i].time)) mine[i].damage=0;
  }
  rtkick(1,bdkick);
}

VOID updbrg(VOID)
{
  INT i,p;

  setbd();
  if (++movbrg==2)  movbrg=0;
  if (++chbrgd==10) chbrgd=0;
  if (++spnbrg==20) spnbrg=0;
  for (i=0; i<NBORGS; i++) {
    if (bdbar[i].active == 1) {
      bdbar[i].time+=2;
      if (upddrd == 0) {
	p=(bdbar[i].pwr*5);
	if (bdbar[i].enr<p) bdbar[i].enr+=bdbar[i].pwr;
	if (bdbar[i].enr>p) bdbar[i].enr=p;
      }
      if (movbrg == 0) {
	brgmod(i);
	brgdir(i);
				if ((bdbar[i].mode==1) || ((bdrand(1,100) > bdbar[i].agr) &&
						((bdbar[i].mode == 7) || (bdbar[i].dx != bdbar[i].xc) ||
	    (bdbar[i].dy != bdbar[i].yc)))) {
	  brgmov(i);
	} else brgatt(i);
      }
    }
  }
}

INT
genbrg(INT brg, INT usr)
{
  INT j,k,b,c,rb;
  CHAR brgnum[12]; // sufficient to hold the largest possible integer - RH to elim V10 crash
  CHAR *dash="-",*zero1="0",*zero2="00"; // *brgnum="" RH eliminate V10 crash

  setbd();
  b=-1;
  for (j=0; j<NBORGS; j++) {
    if (bdbar[j].active == 0) {
      b=j;
      j=NBORGS;
    }
  }
  if (b == -1) return(0);
  bdbpt=&bdbar[b];
  if (usr <= -1) strcpy(bdbpt->user,"System***");
  else strcpy(bdbpt->user,uacoff(usr)->userid);
  bdbpt->credits=0;
  bdbpt->xc=  2526-bdrand(1,51);
  bdbpt->yc=  2526-bdrand(1,51);
  bdbpt->dx= -1;
  bdbpt->dy= -1;
  bdbpt->dir=(bdrand(1,8)-1);
  bdbpt->agr=bdrand(25,50);
  bdbpt->mode=0;
  bdbpt->mvbl=0;
  bdbpt->usr=-1;
  bdbpt->hst= 1;
  bdbpt->kills=0;
  if ((brg < 1) || (brg > 23) ||
      ((brg > 23) && (!sameas(usaptr->userid, "Sysop")))) rb = (bdrand(1, 9));
  else if (brg > NUM_BBRG - 1) rb = bdrand(1, 9); else rb = brg; // RH 6/19/2024 to eliminate C6385 Reading invalid data 
  bdbpt->weapon=(CHAR)bdrand(bbrg[rb].lowep,bbrg[rb].hiwep);
  updbchs(bdrand(bbrg[rb].lochs,bbrg[rb].hichs));
  strcpy(bdbar[b].name,bbrg[rb].name);
  c = btpcnt(bbrg[rb].name);
  strcat(bdbar[b].name, dash);
  if (c < 10) strcat(bdbar[b].name, zero2);
  else if (c < 100) strcat(bdbar[b].name, zero1);
  itoa(c, brgnum, 10);
  strcat(bdbar[b].name, brgnum);
  for (k=0; k<NBORGS; k++)
    if ((sameas(bdbar[b].name,bdbar[k].name)) &&
	(b != k) && (bdbar[k].active == 1)) return(0);
  if (usr > -1) {
    if (bchs[bdbar[b].chs].weight > bdarr[usrnum].rsp) {
      prfmlt(LOWRSP);
      outmlt(usrnum);
      return(0);
    } else {
      bdarr[usrnum].rsp-=bchs[bdbar[b].chs].weight;
      prfmlt(SPAWNB,b,bdbar[b].name);
      outmlt(usrnum);
    }
  }
	if (strlen(bdbar[b].name) > 4) {
	  bdbpt->active=1;
    bdbpt->time=0;
    prfmlt(TRNSIN,bdbar[b].name);
    bdpmt();
    outloc(bdbpt->xc,bdbpt->yc,-1,-1);
    gensns(bdbpt->xc,bdbpt->yc,24,5,usr);
    return(1);
	}
	return(0);
}

VOID
updbchs(INT chs)
{
  bdbpt->chs= (CHAR)chs;
  bdbpt->pwr= (CHAR)bchs[chs].pwr;
  bdbpt->cmp= (CHAR)bchs[chs].cmp;
  bdbpt->stb= (CHAR)bchs[chs].stb;
  bdbpt->man= (CHAR)bchs[chs].man;
  bdbpt->str= (CHAR)bchs[chs].str;
  bdbpt->spd= (CHAR)bchs[chs].spd;
  bdbpt->agl= (CHAR)bchs[chs].agl;
  bdbpt->trg= (CHAR)bchs[chs].trg;
  bdbpt->enr= bdbpt->pwr*5;
  bdbpt->ar=  bchs[chs].armor;
  bdbpt->mar= bchs[chs].armor;
}

INT
desbrg(INT brg, INT usr)
{
  INT j;

  setbd();
  if (brg < 0) {
    for (j=0; j<NBORGS; j++) {
      if (bdbar[j].active == 1) {
	bdbar[j].active=0;
	prfmlt(TRNSOT,bdbar[j].name);
	bdpmt();
	outloc(bdbar[j].xc,bdbar[j].yc,-1,-1);
	gensns(bdbar[j].xc,bdbar[j].yc,24,5,-1);
      }
    }
    return(1);
  } else if (sameas(uacoff(usr)->userid,bdbar[brg].user)) {
    if (bdbar[brg].active == 1) {
      bdbar[brg].active=0;
      prfmlt(TRNSOT,bdbar[brg].name);
      bdpmt();
      outloc(bdbar[brg].xc,bdbar[brg].yc,-1,-1);
      gensns(bdbar[brg].xc,bdbar[brg].yc,24,5,-1);
      bdarr[usr].rsp+=bchs[bdbar[brg].chs].weight;
      return(1);
    }
  }
  return(0);
}

VOID
brgmod(INT brg)
{
    LONG a,ca,ma;


    if ((bdbar[brg].ar >= 1) && (bdbar[brg].mar > 4) && (bdbar[brg].mar < 2001)) {
      ca=(bdbar[brg].ar*100000L);
      ma=(bdbar[brg].mar*1000L);
	    a=(ca/ma);
    } else a=0;
    // chkdirf(bdbar[brg].xc,bdbar[brg].yc,bdbar[brg].dx,bdbar[brg].dy);
    if ((a > (50-bdbar[brg].agr)) && (bdbar[brg].mode < 2))
      bdbar[brg].mode=0;
    else if (bdbar[brg].mode < 2)
      bdbar[brg].mode=1;
    else if (((bdbar[brg].mode == 7) && (bdbar[brg].dx==-1)) ||
	       ((bdbar[brg].mode == 6) && (bdbar[brg].dx==-1)) ||
	       ((bdbar[brg].mode == 5) && (bdbar[brg].dx==-1)) ||
	       ((bdbar[brg].mode == 4) && (bdbar[bdbar[brg].usr].active==0)) ||
	       ((bdbar[brg].mode == 3) && (chkbdu(bdbar[brg].usr)==0)) ||
	       ((bdbar[brg].mode == 2) && (bdbar[brg].dx == bdbar[brg].xc) &&
		(bdbar[brg].dy == bdbar[brg].yc))) {
      bdbar[brg].mode=bdbar[brg].mvbl=0;
      bdbar[brg].usr=bdbar[brg].dx=bdbar[brg].dy=-1;
    } else if ((bdbar[brg].mode == 6) && (bdbar[brg].dx == bdbar[brg].xc) &&
	       (bdbar[brg].dy == bdbar[brg].yc))
      bdbar[brg].mode=7;
    else if ((bdbar[brg].mode == 7) && (dist > bdbar[brg].mvbl))
      bdbar[brg].mode=6;
}

VOID
brgdir(INT brg)
{
    if ((bdbar[brg].usr != -1) && (chkbdu(bdbar[brg].usr)==1) &&
	(bdbar[brg].mode==3)) {
      bdbar[brg].dx=bdarr[bdbar[brg].usr].xc;
      bdbar[brg].dy=bdarr[bdbar[brg].usr].yc;
    } else if ((bdbar[brg].mode==4) && (bdbar[bdbar[brg].usr].active==1)) {
      bdbar[brg].dx=bdbar[bdbar[brg].usr].xc;
      bdbar[brg].dy=bdbar[bdbar[brg].usr].yc;
    } else {
      bdbar[brg].usr=-1;
      bdbar[brg].hst=1;
    }
    if ((chbrgd == 0) && ((bdbar[brg].mode == 0) || (bdbar[brg].mode == 7)))
      bdbar[brg].dir=(bdrand(1,8)-1);
    else if ((movbrg == 0) && (bdbar[brg].dx > -1) && (bdbar[brg].dy > -1) &&
	     ((bdbar[brg].dx != bdbar[brg].xc) || (bdbar[brg].dy != bdbar[brg].yc))
	     && (bdbar[brg].mode != 1) && (bdbar[brg].mode != 7))
      bdbar[brg].dir=chkdirf(bdbar[brg].xc,bdbar[brg].yc,
			     bdbar[brg].dx,bdbar[brg].dy);
}

VOID
brgmov(INT brg)
{
    INT td,tx,ty,nx,ny;

    /*tx=ty=nx=ny=0;*/
    tx=(bdbar[brg].xc+dirmx[bdbar[brg].dir]);
    ty=(bdbar[brg].yc+dirmy[bdbar[brg].dir]);
    if ((tx < 2400 || tx > 2600 || ty < 2400 || ty > 2600) && (bdbar[brg].mode == 0)) {
      td=(bdbar[brg].dir-4);
      if (td<0) td=(bdbar[brg].dir+4);
      bdbar[brg].dir=td;
      nx=(bdbar[brg].xc+dirmx[bdbar[brg].dir]);
      ny=(bdbar[brg].yc+dirmy[bdbar[brg].dir]);
    } else {
      nx=(bdbar[brg].xc+dirmx[bdbar[brg].dir]);
      ny=(bdbar[brg].yc+dirmy[bdbar[brg].dir]);
    }
    if (bdbar[brg].enr-=((bchs[bdbar[brg].chs].weight/5)+1)>=0) {
      bdbar[brg].enr-=((bchs[bdbar[brg].chs].weight/5)+1);
      if (nx >= 0 || nx <= 5000 || ny >= 0 || ny <= 5000)
	mbrgto(brg,nx,ny);
      else
	desbrg(brg,-1);
    }
}

VOID
mbrgto(INT who, INT newx, INT newy)
{
  INT l;

  setbd();
  gensns(bdbar[who].xc,bdbar[who].yc,0,((bchs[bdbar[who].chs].weight/5)+2),-1);
  prfmlt(LEVING,bdbar[who].name,dirds[bdbar[who].dir]);
  bdpmt();
  outloc(bdbar[who].xc,bdbar[who].yc,-1,-1);
  prfmlt(DROIDAR,bdbar[who].name);
  bdpmt();
  outloc(newx,newy,-1,-1);
  bdbar[who].xc=newx;
  bdbar[who].yc=newy;
  for (l=0; l<100; l++)
    if (mine[l].damage)
      if (mine[l].x==newx && mine[l].y==newy) blast(&mine[l]);
}

INT
brgatt(INT brg)
{
  INT u,b,d,dm,ds,dir,m,sp,sc;

  setbd();
  u=-1;
  b=-1;
  dir=-1;
  ds=5001;
  for (m=0; m<nterms; m++) {
    if ((usroff(m)->state == bdstt) && (usroff(m)->substt == PLYBD) &&
	(bdarr[m].active==1)) {
      d=chkdirf(bdbar[brg].xc,bdbar[brg].yc,bdarr[m].xc,bdarr[m].yc);
      if ((bdbar[brg].hst == 1) ||
		((bdbar[brg].usr != m) && (bdbar[brg].mode == 3)) || (bdbar[brg].mode != 3)) {
	      if ((bdarr[m].xc!=2500) || (bdarr[m].yc!=2500)) {
	  if (dist < ds) {
	    if (!sameas(uacoff(m)->userid,bdbar[brg].user)) {
	      u=m;
	      dir=d;
	      ds=dist;
	      if (u==bdbar[m].usr) m=nterms;
	    }
	  }
	}
      }
    }
  }
  for (m=0; m<NBORGS; m++) {
    if ((bdbar[m].active==1) && (m != brg)) {
      d=chkdirf(bdbar[brg].xc,bdbar[brg].yc,bdbar[m].xc,bdbar[m].yc);
      if ((bdbar[brg].hst == 1) ||
		((bdbar[brg].usr != m) && (bdbar[brg].mode == 4)) || (bdbar[brg].mode != 4)) {
	      if ((bdbar[m].xc!=2500) || (bdbar[m].yc!=2500)) {
	  if (!sameas(bdbar[brg].user,bdbar[m].user)) {
	    if (dist < ds) {
	      u=-1;
	      b=m;
	      dir=d;
	      ds=dist;
	      if (b==bdbar[m].usr) m=NBORGS;
	    }
	  }
	}
      }
    }
  }
  if ((ds > 0) && (ds <= bwep[bdbar[brg].weapon].range) &&
      (bwep[bdbar[brg].weapon].pwrus <= bdbar[brg].enr) &&
      ((u != -1) || (b != -1))) {
    bdbar[brg].enr-=bwep[bdbar[brg].weapon].pwrus;
    prfmlt(FIROTH,bdbar[brg].name,bobj[bdbar[brg].weapon].name,dirds[bdgdir(dirxl[dir])]);
    bdpmt();
    outloc(bdbar[brg].xc,bdbar[brg].yc,-1,-1);
    gensns(bdbar[brg].xc,bdbar[brg].yc,7+bdbar[brg].weapon,bwep[bdbar[brg].weapon].distd,-1);
    dm=(bdrand(bwep[bdbar[brg].weapon].mindm,bwep[bdbar[brg].weapon].maxdm));
    if (u != -1) {
      if (numinv(u,ISCR)==-1) sp=0;
      else sp=(bdarr[u].pwr*2);
      if (sp > 20) sp=20;
      if (sp > 0) sc=bdrand((bdarr[u].pwr/2),sp);
      else sc=0;
      dm-=sc;
      if (dm <= 0) {
	prfmlt(BDDMG3,bobj[bdbar[brg].weapon].desc,dirbds[dir]);
	bdpmt();
	outmlt(u);
      }
      dmgdrd(-1,brg,u,dm,bdbar[brg].weapon,dirxl[dir],-1,-1);
    } else dmgbrg(-1,brg,b,dm);
    return(1);
  } else if ((ds == 0) && ((u != -1) || (b != -1))) {
    if ((bdbar[brg].enr-((bchs[bdbar[brg].chs].weight/5)+1)) >= 0) {
      bdbar[brg].enr-=((bchs[bdbar[brg].chs].weight/5)+1);
      if (u != -1) {
	if ((bdrand(1,100))>bdbar[brg].agl) {
	  prfmlt(BDMSYU,bdbar[brg].name);
	  bdpmt();
	  outmlt(u);
	  prfmlt(BDMSOT,bdbar[brg].name,uacoff(u)->userid);
	  bdpmt();
	  outloc(bdbar[brg].xc,bdbar[brg].yc,u,-1);
	} else {
	  dm=bdrand(((bchs[bdbar[brg].chs].weight/5)+1),((bchs[bdbar[brg].chs].weight/2)+2));
	  prfmlt(BDDMYU,bdbar[brg].name,dm);
	  bdpmt();
	  outmlt(u);
	  prfmlt(BDDOTH,bdbar[brg].name,uacoff(u)->userid);
	  bdpmt();
	  outloc(bdbar[brg].xc,bdbar[brg].yc,u,-1);
	  dmgdrd(-1,brg,u,dm,-1,"-",-1,-1);
	}
      } else {
	if ((bdrand(1,100))>bdbar[brg].agl) {
	  prfmlt(BDMSOT,bdbar[brg].name,bdbar[b].name);
	  bdpmt();
	  outloc(bdbar[brg].xc,bdbar[brg].yc,-1,-1);
	} else {
	  dm=bdrand(bchs[bdbar[brg].chs].weight,(bchs[bdbar[brg].chs].weight*2))+(bdbar[brg].str/5);
	  prfmlt(BDDOTH,bdbar[brg].name,bdbar[b].name);
	  bdpmt();
	  outloc(bdbar[brg].xc,bdbar[brg].yc,-1,-1);
	  dmgbrg(-1,brg,b,dm);
	}
      }
      return(-1);
    }
  }
  return(0);
}

VOID
bdmnu(VOID)
{
  setbd();
  switch(sel) {
  case 'h':
    prfmlt(newstt=BDH1);
    outmlt(usrnum);
    break;
  case 'c':
    prfmlt(newstt=BDC);
    outmlt(usrnum);
    break;
  case 'p':
    if (bdptr->active==1) {
      prfmlt(newstt=PLYBD);
      outmlt(usrnum);
      prfmlt(TRNSIN,usaptr->userid);
      bdpmt();
      outloc(bdptr->xc,bdptr->yc,usrnum,-1);
      gensnsu(usrnum,24,5,usrnum,-1);
      shwsta();
      bdpmt();
      outmlt(usrnum);
    } else playbd();
    break;
  case 'x':
    prfmlt(EXTBD);
    outmlt(usrnum);
    newstt=0;
    break;
  case '?':
    prfmlt(newstt=BDM);
    outmlt(usrnum);
    break;
  default:
    prfmlt(newstt=BDP);
    outmlt(usrnum);
    break;
  }
}

GBOOL crsbd(VOID)
{
  INT inp;

  setbd();
  if (usrptr->flags&INJOIP) return(1);
  sel=(CHAR)tolower(margv[0][0]);
  switch(newstt=usrptr->substt) {
  case 0:
    prfmlt(newstt=BDM);
    outmlt(usrnum);
    break;
  case BDM:
  case BDP:
    bdmnu();
    break;
  case PLYBD:
    if (bdptr->active == 0) {
      gendrd();
    } else {
      if ((inp=bdinp())==1) {
	bdpmt();
	outmlt(usrnum);
      } else if (inp == 2) {
	prfmlt(NOSCMD);
	bdpmt();
	outmlt(usrnum);
      }
    }
    break;
  case BDH1:
  case BDH2:
    prfmlt(++newstt);
    outmlt(usrnum);
    break;
  case BDH3:
    prfmlt(newstt=BDP);
    outmlt(usrnum);
    break;
  case BDC:
    prfmlt(newstt=BDP);
    outmlt(usrnum);
    break;
  case STRMNU:
  case STRPMT:
    strbd();
    break;
  case BUYITM:
    bdbuy();
    break;
  case SELITM:
    bdsell();
    break;
  default:
    newstt=0;
    break;
  }
  usrptr->substt=newstt;
  if (newstt == 0) return(0);
  return(1);
}

INT
bdinp(VOID)
{
  INT m1,m3,m4,un;

  m1 = m3 = m4 = 0; // avoid c4701

  setbd();
  if (margc > 1) m1=atoi(margv[1]);
  if (margc > 3) m3=atoi(margv[3]);
  if (margc > 4) m4=atoi(margv[4]);
  if (spnbrg == 0) if (brgcnt() < NBORGS) genbrg(-1,-1);
  if ((sameas(usaptr->userid,"Sysop")) || (bdptr->flag > 1)) {
    if (margc == 1) {
      if (sameas(margv[0],"shelp")) {
	      prfmlt(BDSHLP);
	      outmlt(usrnum);
	      return(1);
      } else if (sameas(margv[0],"shop")) {
	      shop();
	      return(0);
      } else if ((sameas(margv[0],"ultrascan")) || (sameas(margv[0],"us"))) {
	      prfmlt(BDSCAN);
	      outmlt(usrnum);
	      scan(usrnum,5000,-1);
	      return(1);
      } else if (sameas(margv[0],"armegedon")) {
	      prfmlt(ALLGON);
	      outmlt(usrnum);
	      desbrg(-1,-1);
	      return(1);
      }
    } else if (margc > 1) {
      if (sameas(margv[0],"shop")) {
	      bdptr->credits+=atol(margv[1]);
	      shop();
	      return(0);
      } else if ((sameas(margv[0],"ultrascan")) || (sameas(margv[0],"us"))) {
	      if (bdgdir(margv[1])!=-1) scanner(margv[1],5000);
	      else {
		prfmlt(BDSCAN);
		outmlt(usrnum);
		scndrd(margv[1],5000);
	      }
	      return(1);
      } else if ((sameas(margv[0],"goto")) || (sameas(margv[0],"go"))) {
	      if (margc == 3) {
		moveto(atoi(margv[2]),atoi(margv[1]));
		return(1);
	      }
      } else if (sameas(margv[0],"move")) {
	      if (margc > 4) {
		if (sameas(margv[2],"user")) {
		  prfmlt(USRMOV,atoi(margv[1]),atoi(margv[3]),atoi(margv[4]));
		  outmlt(usrnum);
		  bdarr[atoi(margv[1])].xc=atoi(margv[4]);
		  bdarr[atoi(margv[1])].yc=atoi(margv[3]);
		  return(1);
		}
		if (sameas(margv[2],"borg")) {
		  prfmlt(BRGMOV,atoi(margv[1]),atoi(margv[3]),atoi(margv[4]));
		  outmlt(usrnum);
		  bdbar[atoi(margv[1])].xc=atoi(margv[4]);
		  bdbar[atoi(margv[1])].yc=atoi(margv[3]);
		  return(1);
		}
	      }
      } else if (sameas(margv[0],"flag")) {
	      if (margc == 3) {
		prfmlt(USRFLG,atoi(margv[1]),atoi(margv[2]));
		outmlt(usrnum);
		bdarr[atoi(margv[1])].flag=atoi(margv[2]);
		return(1);
	      }
      } else if (sameas(margv[0],"credits")) {
	      if (margc == 3) {
		prfmlt(USRCRD,atoi(margv[1]),margv[2]);
		outmlt(usrnum);
		bdarr[atoi(margv[1])].credits+=atol(margv[2]);
		return(1);
	      }
      } else if (sameas(margv[0],"resources")) {
	      if (margc == 3) {
		prfmlt(USRRSP,atoi(margv[1]),margv[2]);
		outmlt(usrnum);
		bdarr[atoi(margv[1])].rsp+=atoi(margv[2]);
		return(1);
	      }
      }
    }
  }
  if ((sameas(usaptr->userid,"Sysop")) || (sameas(usaptr->userid,"Sysop"))
		|| (bdptr->flag > 0)) {
    if (margc == 1) {
      if (sameas(margv[0],"whelp")) {
	prfmlt(BDWHLP);
	outmlt(usrnum);
	return(1);
      } else if (sameas(margv[0],"blist")) {
	      prfmlt(BDWHL2);
	      outmlt(usrnum);
	      return(1);
      } else if (sameas(margv[0],"borgs")) {
	      lstbrg(usrnum);
	      return(1);
      } else if (sameas(margv[0],"spawn")) {
	      genbrg(-1,usrnum);
	      return(1);
      }
    } else if (margc > 1) {
      if (sameas(margv[0],"spawn")) {
	      genbrg(atoi(margv[1]),usrnum);
	      return(1);
      } else if (sameas(margv[0],"destroy")) {
	      if ((m1 > -1) && (m1 < NBORGS) &&
		  ((sameas(bdbar[m1].user,usaptr->userid)) || (bdarr[usrnum].flag > 1))) {
		if (desbrg(atoi(margv[1]),usrnum)==1) {
		  prfmlt(BRGGON,atoi(margv[1]));
		  outmlt(usrnum);
		}
		return(1);
	      }
      } else if (sameas(margv[0],"check")) {
	      if ((m1 > -1) && (m1 < NBORGS) &&
		  ((sameas(bdbar[m1].user,usaptr->userid)) || (bdarr[usrnum].flag > 1))) {
		scnbrg(atoi(margv[1]));
		return(1);
	      }
      } else if (sameas(margv[0],"bscan")) {
	      if ((m1 > -1) && (m1 < NBORGS) &&
		  ((sameas(bdbar[m1].user,usaptr->userid)) || (bdarr[usrnum].flag > 1))) {
		if (margc == 3) {
		  if (bdgdir(margv[2])!=-1) {
		    bscanner(margv[2],atoi(margv[1]),20);
		  } else {
		    prfmlt(BDSCAN);
		    outmlt(usrnum);
		    bscndrd(margv[2],atoi(margv[1]),20);
		  }
		} else if (margc == 2) {
		  prfmlt(BDSCAN);
		  outmlt(usrnum);
		  bscan(usrnum,atoi(margv[1]),5,-1);
		}
		return(1);
	      }
      } else if (sameas(margv[0],"send")) {
	      if ((margc >= 4) && (m1 > -1) && (m1 < NBORGS) &&
		  ((sameas(bdbar[m1].user,usaptr->userid)) || (bdarr[usrnum].flag > 1))) {
		if (sameas(margv[2],"user")) {
		  if ((un=locdrd(margv[3]))>=0) {
		    prfmlt(BGSNTU,atoi(margv[1]),uacoff(un)->userid);
		    outmlt(usrnum);
		    bdbar[atoi(margv[1])].usr=un;
		    bdbar[atoi(margv[1])].mode=3;
		    return(1);
		  }
		} else if (sameas(margv[2],"borg")) {
		  if ((m3 > -1) && (m3 < NBORGS)) {
		    prfmlt(BGSNTB,atoi(margv[1]),atoi(margv[3]));
		    outmlt(usrnum);
		    bdbar[atoi(margv[1])].usr=atoi(margv[3]);
		    bdbar[atoi(margv[1])].mode=4;
		    return(1);
		  }
		}
		if ((m3 > -1) && (m3 < 5001) && (m4 > -1) && (m4 < 5001)) {
		  if (margc > 4) {
		    if (sameas(margv[2],"visit")) {
			    prfmlt(BGSNTD,atoi(margv[1]),atoi(margv[3]),atoi(margv[4]));
			    outmlt(usrnum);
			    bdbar[atoi(margv[1])].dx=atoi(margv[4]);
			    bdbar[atoi(margv[1])].dy=atoi(margv[3]);
			    bdbar[atoi(margv[1])].mode=2;
			    return(1);
		    } else if (sameas(margv[2],"garrison")) {
			    prfmlt(BGSNTG,atoi(margv[1]),atoi(margv[3]),atoi(margv[4]));
			    outmlt(usrnum);
			    bdbar[atoi(margv[1])].dx=atoi(margv[4]);
			    bdbar[atoi(margv[1])].dy=atoi(margv[3]);
			    bdbar[atoi(margv[1])].mode=5;
			    return(1);
		    } else if (sameas(margv[2],"patrol")) {
			    prfmlt(BGSNTP,atoi(margv[1]),atoi(margv[3]),atoi(margv[4]));
			    outmlt(usrnum);
			    bdbar[atoi(margv[1])].dx=atoi(margv[4]);
			    bdbar[atoi(margv[1])].dy=atoi(margv[3]);
			    bdbar[atoi(margv[1])].mode=6;
			    return(1);
		    }
		  }
		}
	      }
      }
      if ((m1 > -1) && (m1 < NBORGS)) {
	      if ((sameas(bdbar[m1].user,usaptr->userid)) || (bdarr[usrnum].flag > 1)) {
		if (margc == 3) {
		  if (sameas(margv[0],"hostility")) {
		    prfmlt(BRGHST,atoi(margv[1]),atoi(margv[2]));
		    outmlt(usrnum);
		    bdbar[atoi(margv[1])].hst=atoi(margv[2]);
		    return(1);
		  } else if (sameas(margv[0],"aggression")) {
		    prfmlt(BRGAGR,atoi(margv[1]),atoi(margv[2]));
		    outmlt(usrnum);
		    bdbar[atoi(margv[1])].agr=atoi(margv[2]);
		    return(1);
		  } else if (sameas(margv[0],"variable")) {
		    prfmlt(BRGVBL,atoi(margv[1]),atoi(margv[2]));
		    outmlt(usrnum);
		    bdbar[atoi(margv[1])].mvbl=atoi(margv[2]);
		    return(1);
		  }
		}
	      }
      }
    }
  }
  if (margc==0) {
    prfmlt(BDCOORD,bdptr->yc,bdptr->xc);
    outmlt(usrnum);
    scan(usrnum,0,-1);
    return(1);
  } else if (margc==1) {
    if ((sameas(margv[0],"help")) || (sameas(margv[0],"?"))) {
      prfmlt(BDGHLP);
      outmlt(usrnum);
      return(1);
    } else if ((sameas(margv[0],"shop")) &&
      (bdptr->xc==2500) && (bdptr->yc==2500)) {
      shop();
      return(0);
    } else if ((sameas(margv[0],"exit")) || (sameas(margv[0],"x"))) {
      if ((bdptr->cbtdly==0) || ((bdptr->xc==2500) && (bdptr->yc==2500)))
	exitbd();
      else {
	prfmlt(NOEXTN);
	bdpmt();
	outmlt(usrnum);
      }
      return(0);
    } else if ((sameas(margv[0],"status")) || (sameas(margv[0],"st"))) {
      shwsta();
      return(1);
    } else if ((sameas(margv[0],"scan")) || (sameas(margv[0],"sc"))) {
      prfmlt(BDSCAN);
      outmlt(usrnum);
      if (numinv(usrnum,IERS)==-1) scan(usrnum,5,-1);
      else scan(usrnum,10,-1);
      return(1);
    } else if ((sameas(margv[0],"inventory")) || (sameas(margv[0],"i"))) {
      bdinv(1);
      return(1);
    } else {
      if (bdmove(margv[0]))
	return(1);
      else return(2);
    }
  } else if (margc > 1) {
    if ((sameas(margv[0],"scan")) || (sameas(margv[0],"sc"))) {
      if (bdgdir(margv[1])!=-1) {
	      if (numinv(usrnum,IERS)==-1) scanner(margv[1],20);
	      else scanner(margv[1],50);
      } else {
	      prfmlt(BDSCAN);
	      outmlt(usrnum);
	      if (numinv(usrnum,IERS)==-1) scndrd(margv[1],20);
	      else scndrd(margv[1],50);
      }
      return(1);
    } else if ((sameas(margv[0],"fire")) || (sameas(margv[0],"f"))) {
      fire(margv[1]);
      return(1);
    } else if ((sameas(margv[0],"use")) || (sameas(margv[0],"u"))) {
      use(margv[1]);
      return(1);
    } else if ((sameas(margv[0],"attack")) || (sameas(margv[0],"a"))) {
      attack(margv[1]);
      return(1);
    } else if (((sameas(margv[0],"launch")) || (sameas(margv[0],"l"))) &&
	       (bdnum(margv[3])) && ((bdgdir(margv[2]))!=-1)) {
      if (margc == 4) {
	if (arm(margv[1],atoi(margv[3])))
		launch(margv[2],atoi(margv[3]));
	      return(1);
      }
    } else if (sameas(margv[0],"pa")) {
      if ((margc==2) && (bdnum(margv[1]))) {
	      bdptr->pavol=atoi(margv[1]);
	      prfmlt(PAVSET,atoi(margv[1]));
	      outmlt(usrnum);
	      return(1);
      } else {
	      comm(margv[1]);
	      return(1);
      }
    } else if ((sameas(margv[0],"radio")) || (sameas(margv[0],"r"))) {
      if (margc>=2) {
	      if ((margc==2) && (bdnum(margv[1]))) {
		bdptr->rfreq=atoi(margv[1]);
		prfmlt(RFRSET,atoi(margv[1]));
		outmlt(usrnum);
		return(1);
	      } else {
		radio(margv[1]);
		return(1);
	      }
      }
    }
  }
  return(2);
}

INT
scan(INT who, INT max, INT di)
{
  BDARR *bdtp,*bdwho;
  INT i,dir;

  setbd();
  if (chkbdu(who)==0) return(0);
  bdwho=&bdarr[who];
  for (i=0; i<NTOBJS; i++) {
    dir=chkdirf(bdwho->xc,bdwho->yc,bter[i].xc,bter[i].yc);
    if (((di==-1) || (di==dir)) && dist <= max) {
      if (dist > 0) {
	      prfmlt(TOBJAT,bter[i].name1,dist,dirds[dir]);
	      outmlt(who);
      } else if (dist == 0) {
	      prfmlt(TOBJHR,bter[i].name2);
	      outmlt(who);
      }
    }
  }
  for (i=0; i<nterms; i++) {
    if ((i!=who) && (chkbdu(i)==1)) {
      bdtp=&bdarr[i];
      dir=chkdirf(bdwho->xc,bdwho->yc,bdtp->xc,bdtp->yc);
      if (((di==-1) || (di==dir)) && dist <= max) {
	      if (dist > 0) {
		prfmlt(DROIDAT,uacoff(i)->userid,dist,dirds[dir]);
		outmlt(who);
	      } else if (dist == 0) {
		prfmlt(DROIDHR,uacoff(i)->userid);
		outmlt(who);
	      }
      }
    }
  }
  for (i=0; i<NBORGS; i++) {
    if (bdbar[i].active == 1) {
      dir=chkdirf(bdwho->xc,bdwho->yc,bdbar[i].xc,bdbar[i].yc);
      if (((di==-1) || (di==dir)) && dist <= max) {
	      if (dist > 0) {
		if (bdarr[who].flag > 0) pmlt("(%d) ",i);
		prfmlt(DROIDAT,bdbar[i].name,dist,dirds[dir]);
		outmlt(who);
	      } else if (dist == 0) {
		if (bdarr[who].flag > 0) pmlt("(%d) ",i);
		prfmlt(DROIDHR2,bdbar[i].name);
		outmlt(who);
	      }
      }
    }
  }
  return(0);
}

INT
bscan(INT who, INT brg, INT max, INT di)
{
  BDARR *bdtp;
  INT i,dir;

  setbd();
  if ((chkbdu(who)==0) || (bdbar[brg].active == 0)) return(0);
  for (i=0; i<NTOBJS; i++) {
    dir=chkdirf(bdbar[brg].xc,bdbar[brg].yc,bter[i].xc,bter[i].yc);
    if (((di==-1) || (di==dir)) && dist <= max) {
      if (dist > 0) {
	prfmlt(TOBJAT,bter[i].name1,dist,dirds[dir]);
	outmlt(who);
      } else if (dist == 0) {
	prfmlt(TOBJHR,bter[i].name2);
	outmlt(who);
      }
    }
  }
  for (i=0; i<nterms; i++) {
    if (chkbdu(i)==1) {
      bdtp=&bdarr[i];
      dir=chkdirf(bdbar[brg].xc,bdbar[brg].yc,bdtp->xc,bdtp->yc);
      if (((di==-1) || (di==dir)) && dist <= max) {
	if (dist > 0) {
	  prfmlt(DROIDAT,uacoff(i)->userid,dist,dirds[dir]);
	  outmlt(who);
	} else if (dist == 0) {
	  prfmlt(DROIDHR,uacoff(i)->userid);
	  outmlt(who);
	}
      }
    }
  }
  for (i=0; i<NBORGS; i++) {
    if (bdbar[i].active == 1) {
      dir=chkdirf(bdbar[brg].xc,bdbar[brg].yc,bdbar[i].xc,bdbar[i].yc);
      if (((di==-1) || (di==dir)) && dist <= max) {
	if (dist > 0) {
	  if (bdarr[who].flag > 0) pmlt("(%d) ",i);
	  prfmlt(DROIDAT,bdbar[i].name,dist,dirds[dir]);
	  outmlt(who);
	} else if ((dist == 0) && (i != brg)) {
	  if (bdarr[who].flag > 0) pmlt("(%d) ",i);
	  prfmlt(DROIDHR2,bdbar[i].name);
	  outmlt(who);
	}
      }
    }
  }
  return(0);
}

INT
blast(BLAST *obj)
{
  INT i,rng;
  BDARR *bdtp;

  if (obj->damage < 1) {
    return(0);
  }
  rng=(obj->damage/5);
  gensns(obj->x,obj->y,3,(obj->damage/2),-1);
  for (i=0; i<nterms; i++) {
    if (chkbdu(i)==1) {
      bdtp=&bdarr[i];
      chkdirf(obj->x,obj->y,bdtp->xc,bdtp->yc);
      if ((bdtp->xc!=2500) || (bdtp->yc!=2500))
	if (dist<=rng)
	  dmgdrd(-1,-1,i,obj->damage-(dist*5),obj->item,"+",-1,-1);
    }
  }
  for (i=0; i<NBORGS; i++) {
    if (bdbar[i].active == 1) {
      chkdirf(obj->x,obj->y,bdbar[i].xc,bdbar[i].yc);
      if ((bdbar[i].xc!=2500) || (bdbar[i].yc!=2500))
	if (dist<=rng) dmgbrg(-1,-1,i,obj->damage-(dist*5));
    }
  }
  obj->damage=0;
  return(0);
}

GBOOL
logbd(VOID)
{
  setbd();
  bdlpl();
  if (showlon) {
    setmbk(bdmb);
    prfmsg(BDSLON);
    outprf(usrnum);
  }
  return(0);
}

VOID
radout(INT user)
{
  INT i;

  for (i=0; i<nterms; i++)
    if ((chkbdu(i)==1) && (i!=user) && (bdarr[i].rfreq==bdptr->rfreq))
      if ((bdarr[i].xc!=2500) || (bdarr[i].yc!=2500)) outmlt(i);
  clrmlt();
  *prfptr=0;
}

VOID
outloc(INT xc,INT yc,INT user,INT othusr)
{
  INT i;

  for (i=0; i<nterms; i++)
    if ((chkbdu(i)==1) && (i!=user) &&  (i!=othusr) &&
       (bdarr[i].xc==xc) && (bdarr[i].yc==yc))
      if ((bdarr[i].xc!=2500) || (bdarr[i].yc!=2500)) outmlt(i);
  clrmlt();
  *prfptr=0;
}

VOID
outall(INT user,INT othusr)
{
  INT i;

  for (i=0; i<nterms; i++)
    if ((chkbdu(i)==1) && (i!=user) &&  (i!=othusr))
      if ((bdarr[i].xc!=2500) || (bdarr[i].yc!=2500)) outmlt(i);
  clrmlt();
  *prfptr=0;
}

VOID
outusr(INT brg)
{
  INT i;

  for (i=0; i<nterms; i++)
    if (chkbdu(i)==1)
      if ((bdarr[i].xc!=2500) || (bdarr[i].yc!=2500))
	      if (sameas(uacoff(i)->userid,bdbar[brg].user)) outmlt(i);
  clrmlt();
  *prfptr=0;
}

VOID
gendrd(VOID)
{
  INT i;

  setbd();
  for (i=0; i<12; bdptr->inv[i++]=255);
  bdptr->active=1;
  bdptr->credits=200;
  bdptr->rsp=0;
  bdptr->weapon=1;
  bdptr->rfreq=1;
  bdptr->pavol=1;
  bdptr->xc= 2526-bdrand(1,51);
  bdptr->yc= 2526-bdrand(1,51);
  updchs(0);
  bdptr->flag=0;
  bdptr->cbtdly=0;
  bdptr->kills=0;
}

VOID
updchs(INT chs)
{
  bdptr->chs= (CHAR)chs;
  bdptr->pwr= (CHAR)bchs[chs].pwr;
  bdptr->cmp= (CHAR)bchs[chs].cmp;
  bdptr->stb= (CHAR)bchs[chs].stb;
  bdptr->man= (CHAR)bchs[chs].man;
  bdptr->str= (CHAR)bchs[chs].str;
  bdptr->spd= (CHAR)bchs[chs].spd;
  bdptr->agl= (CHAR)bchs[chs].agl;
  bdptr->trg= (CHAR)bchs[chs].trg;
  bdptr->enr= bdptr->pwr*5;
  bdptr->ar=  bchs[chs].armor;
  bdptr->mar= bchs[chs].armor;
}

INT
drdcnt(VOID)
{
  INT c=0,j;

  for (j=0; j<nterms; j++)
    if ((usroff(j)->state == bdstt) && (bdarr[j].active==1)) c++;
  return(c);
}

INT
brgcnt(VOID)
{
  INT c=0,j;

  for (j=0; j<NBORGS; j++) if (bdbar[j].active == 1) c++;
  return(c);
}

INT
btpcnt(CHAR *type)
{
  INT c=0,j;

  for (j=0; j<NBORGS; j++)
    if ((bdbar[j].active == 1) && (sameto(type,bdbar[j].name))) c+=1;
  return(c);
}

VOID
shwsta(VOID)
{
  setbd();
  prfmlt(BDSTAT,bdptr->yc,bdptr->xc,
  bchs[bdptr->chs].name,
  bchs[bdptr->chs].type,
  bchs[bdptr->chs].weight,
  bdptr->pwr,
  bdptr->cmp,
  bdptr->str,
  bdptr->agl,
  bdptr->enr,
  bdptr->ar,
  bdptr->mar,
  (bdptr->weapon==255 ? "None" : bobj[bdptr->weapon].name),
  ltoa(bdptr->credits),
  bdptr->rsp,
  bdptr->kills);
  outmlt(usrnum);
}

INT
locdrd(CHAR *uid)
{
  INT cnt,dstusn=-1;

  cnt=0;
  for (othusn=0 /*,othusp=user*/ ; othusn < nterms ; othusn++ /*,othusp++ */) {
    if ((othusp->state != bdstt) || (!sameto(uid,uacoff(othusn)->userid)) ||
	      (bdarr[othusn].active==0)) {
      continue;
    } else if ((bdarr[othusn].xc!=2500) || (bdarr[othusn].yc!=2500)) {
      dstusn=othusn;
      cnt++;
    }
  }
  if (cnt <= 0) return(-2);
  if (cnt > 1)  return(-1);
  othusn=dstusn;
  /*othusp=&user[othusn];
  othuap=uacoff(othusn);*/
  return(dstusn);
}

INT
locbrg(CHAR *bid)
{
  INT cnt,j,b=1;

  for (j=0,cnt=0; j<NBORGS; j++) {
    if ((bdbar[j].active != 0) && (sameto(bid,bdbar[j].name))) {
      if ((bdbar[j].xc!=2500) || (bdbar[j].yc!=2500)) {
	      b=j;
	      cnt++;
      }
    }
  }
  if (cnt < 1)      return(-2);
  else if (cnt > 1) return(-1);
  else              return(b);
}

VOID
lstbrg(INT usr)
{
  INT j;

  setbd();
  for (j=0; j<NBORGS; j++) {
    if ((bdbar[j].active == 1) && (sameas(uacoff(usr)->userid,bdbar[j].user))) {
      prfmlt(BRGLST,j,bdbar[j].name,bdbar[j].yc,bdbar[j].xc);
      outmlt(usrnum);
    }
  }
}

INT
scndrd(CHAR *drd, INT ds)
{
  INT  who,b,dir,ia,ie;
  LONG a,e,ca,ma;

  setbd();
  b=locbrg(drd);
  who=locdrd(drd);
  if ((who<0) || (b<0)) {
    if ((who==-2) && (b==-2)) {
      prfmlt(NOFIND);
      outmlt(usrnum);
      return(0);
    } else if ((who==-1) || (b==-1)) {
      prfmlt(ATTWCH);
      outmlt(usrnum);
      return(0);
    }
  }
  if (who != -2) {
    if (b != -2) {
      if (((usroff(who)->state != bdstt) || (bdarr[who].active != 1)) &&
		 (bdbar[b].active == 0)) {
	      prfmlt(NOFIND);
	      outmlt(usrnum);
	      return(0);
      }
      if (usrnum == who) {
	      prfmlt(NSCSLF);
	      outmlt(usrnum);
	      return(0);
      }
    }
    //if (b == -2) dir=chkdirf(bdptr->xc,bdptr->yc,bdarr[who].xc,bdarr[who].yc);
    //else       dir=chkdirf(bdptr->xc,bdptr->yc,bdbar[b].xc,bdbar[b].yc);
  }
  if (dist > ds) {
    prfmlt(NINRNG);
    outmlt(usrnum);
    return(0);
  }
  if ((b == -2) && (who != -2)) {
    dir=chkdirf(bdptr->xc,bdptr->yc,bdarr[who].xc,bdarr[who].yc);
    if (bdarr[who].ar >= 1) {
      ca=(bdarr[who].ar*100000L);
      ma=(bdarr[who].mar*1000L);
	    a=(ca/ma);
    } else a=0;
    if (bdarr[who].enr >= 1) {
      ca=(bdarr[who].enr*100000L);
      ma=(bdarr[who].pwr*5000L);
	    e=(ca/ma);
    } else e=0;
    ia=atoi(ltoa(a));
    ie=atoi(ltoa(e));
    prfmlt(SCNDRD,uacoff(who)->userid,
    bdarr[who].kills,
    bdarr[who].yc,bdarr[who].xc,
    dist,
    dircds[dir],
    bchs[bdarr[who].chs].type,
    bchs[bdarr[who].chs].weight,
    ia,'%',
    ie,'%',
    (bdarr[who].weapon==255 ? "None" : bobj[bdarr[who].weapon].name));
  } else {
    dir=chkdirf(bdptr->xc,bdptr->yc,bdbar[b].xc,bdbar[b].yc);
    if (bdbar[b].ar > 0 && (bdbar[b].mar > 4) && (bdbar[b].mar < 2001)) {
      ca=(bdbar[b].ar*100000L);
      ma=(bdbar[b].mar*1000L);
	    a=(ca/ma);
    } else a=0;
    if (bdbar[b].enr > 0) {
      ca=(bdbar[b].enr*100000L);
      ma=(bdbar[b].pwr*5000L);
	    e=(ca/ma);
    } else e=0;
    ia=atoi(ltoa(a));
    ie=atoi(ltoa(e));
    prfmlt(SCNDRD,bdbar[b].name,
    bdbar[b].kills,
    bdbar[b].yc,bdbar[b].xc,
    dist,
    dircds[dir],
    bchs[bdbar[b].chs].type,
    bchs[bdbar[b].chs].weight,
    ia,'%',
    ie,'%',
    (bdbar[b].weapon==255 ? "None" : bobj[bdbar[b].weapon].name));
  }
  outmlt(usrnum);
  return(0);
}

INT
bscndrd(CHAR *drd, INT brg, INT ds)
{
  INT  who,b,dir,ia,ie;
  LONG a,e,ma,ca;

  setbd();
  b=locbrg(drd);
  who=locdrd(drd);
  if ((who<0) || (b<0)) {
    if ((who==-2) && (b==-2)) {
      prfmlt(NOFIND);
      outmlt(usrnum);
      return(0);
    } else if ((who==-1) || (b==-1)) {
      prfmlt(ATTWCH);
      outmlt(usrnum);
      return(0);
    }
  }
  if (who != -2) {
    if (b != -2) {
      if (((usroff(who)->state != bdstt) || (bdarr[who].active != 1)) &&
		 (bdbar[b].active == 0)) {
	      prfmlt(NOFIND);
	      outmlt(usrnum);
	      return(0);
      }
      if (brg == b) {
	      prfmlt(NSCSLF);
	      outmlt(usrnum);
	      return(0);
      }
    }
    //if ((b == -2) && (who != -2))
    //  dir=chkdirf(bdbar[brg].xc,bdbar[brg].yc,bdarr[who].xc,bdarr[who].yc);
    //else
    //  dir=chkdirf(bdbar[brg].xc,bdbar[brg].yc,bdbar[b].xc,bdbar[b].yc);
  }
  if (dist > ds) {
    prfmlt(NINRNG);
    outmlt(usrnum);
    return(0);
  }
  if ((b == -2) && (who != -2)) {
    dir=chkdirf(bdbar[brg].xc,bdbar[brg].yc,bdarr[who].xc,bdarr[who].yc);
    if (bdarr[who].ar >= 1) {
      ca=(bdarr[who].ar*100000L);
      ma=(bdarr[who].mar*1000L);
	    a=(ca/ma);
    } else a=0;
    if (bdarr[who].enr >= 1) {
      ca=(bdarr[who].enr*100000L);
      ma=(bdarr[who].pwr*5000L);
	    e=(ca/ma);
    } else e=0;
    ia=atoi(ltoa(a));
    ie=atoi(ltoa(e));
    prfmlt(SCNDRD,uacoff(who)->userid,
    bdarr[who].kills,
    bdarr[who].yc,bdarr[who].xc,
    dist,
    dircds[dir],
    bchs[bdarr[who].chs].type,
    bchs[bdarr[who].chs].weight,
    ia,'%',
    ie,'%',
    (bdarr[who].weapon==255 ? "None" : bobj[bdarr[who].weapon].name));
  } else {
    dir=chkdirf(bdbar[brg].xc,bdbar[brg].yc,bdbar[b].xc,bdbar[b].yc);
    if (bdbar[b].ar >= 1 && (bdbar[b].mar > 4) && (bdbar[b].mar < 2001)) {
      ca=(bdbar[b].ar*100000L);
      ma=(bdbar[b].mar*1000L);
	    a=(ca/ma);
    } else a=0;
    if (bdbar[b].enr >= 1) {
      ca=(bdbar[b].enr*100000L);
      ma=(bdbar[b].pwr*5000L);
	    e=(ca/ma);
    } else e=0;
    ia=atoi(ltoa(a));
    ie=atoi(ltoa(e));
    prfmlt(SCNDRD,bdbar[b].name,
    bdbar[b].kills,
    bdbar[b].yc,bdbar[b].xc,
    dist,
    dircds[dir],
    bchs[bdbar[b].chs].type,
    bchs[bdbar[b].chs].weight,
    ia,'%',
    ie,'%',
    (bdbar[b].weapon==255 ? "None" : bobj[bdbar[b].weapon].name));
  }
  outmlt(usrnum);
  return(0);
}

VOID
scnbrg(INT brg)
{
  INT dir;
  CHAR tmp[30];

  setbd();
  if (bdbar[brg].active == 1) {
    dir=chkdirf(bdptr->xc,bdptr->yc,bdbar[brg].xc,bdbar[brg].yc);
    if (bdbar[brg].mode < 4)
      sprintf(tmp,"User:      %s",(bdbar[brg].usr<=-1 ? "None" : uacoff(bdbar[brg].usr)->userid));
    else
      sprintf(tmp,"Borg:      %s",(bdbar[brg].usr<=-1 ? "None" : bdbar[bdbar[brg].usr].name));
    chkdirf(bdbar[brg].xc,bdbar[brg].yc,bdbar[brg].dx,bdbar[brg].dy);
    prfmlt(SCNBRG,bdbar[brg].name,
    bdbar[brg].user,
    bdbar[brg].yc,bdbar[brg].xc,
    dist,
    dircds[dir],
    brgmode[bdbar[brg].mode],
    bdbar[brg].mvbl,
    tmp,
    bdbar[brg].hst==0 ? "No" : "Yes",
    bdbar[brg].agr,
    dircds[bdbar[brg].dir],
    bdbar[brg].dy,bdbar[brg].dx,
    dist,
    ltoa(bdbar[brg].time/60L));
    outmlt(usrnum);
  }
}

VOID
exitbd(VOID)
{
  setbd();
  prfmlt(EXTBD);
  outmlt(usrnum);
  prfmlt(TRNSOT,usaptr->userid);
  bdpmt();
  outloc(bdptr->xc,bdptr->yc,usrnum,-1);
  gensnsu(usrnum,24,5,usrnum,-1);
  prfmlt(newstt=BDM);
  outmlt(usrnum);
}

INT
bdgdir(CHAR *s)
{
  INT i;

  for (i=0; i<8; i++) if (sameas(s,dirxl[i])) return(i);
  return(-1);
}

INT
chkdirf(INT xc, INT yc, INT xo, INT yo)
{
  INT xdif,ydif,axd,ayd;
  LONG tmp1,tmp2,tmp3;

  xdif=xo-xc;
  axd=abs((INT)(xdif/1));
  ydif=yo-yc;
  ayd=abs((INT)(ydif/1));
  //tmp1=tmp2=tmp3=0;
  tmp1=((axd+ayd)*100000L);
  if ((axd == 0) || (ayd == 0)) tmp2=100000L;
  else if (axd < ayd)           tmp2=(((axd*100000L)/(ayd))+100000L);
  else if (ayd < axd)           tmp2=(((ayd*100000L)/(axd))+100000L);
  else                          tmp2=200000L;
  if ((tmp1 != 0) && (tmp2 != 0)) {
    tmp3=(tmp1/tmp2);
    dist=(INT)tmp3;
  } else dist=0;
  if (abs(xdif)*2<=abs(ydif))      return(ydif<0 ? 0 : 4);
  else if (abs(ydif)*2<=abs(xdif)) return(xdif<0 ? 6 : 2);
  else if (xdif<0)                 return(ydif<0 ? 7 : 5);
  else                             return(ydif<0 ? 1 : 3);
}

VOID
gensnsu(INT from, INT type, INT max, INT pmt ,INT user)
{
  BDARR *bdop,*bdtp;
  INT j,df;

  setbd();
  bdop=&bdarr[from];
  for (j=0; j<nterms; j++) {
    if ((j!=from) && (chkbdu(j)==1)) {
      bdtp=&bdarr[j];
      df=chkdirf(bdtp->xc,bdtp->yc,bdop->xc,bdop->yc);
      if ((bdtp->xc!=2500) || (bdtp->yc!=2500)) {
	if ((dist > 0) && (dist <= max)) {
	  prfmlt(SNSORAT,sensor[type],dist,dirds[df]);
	  if (j != pmt) bdpmt();
	  if (j != user) outmlt(j);
	  else {
	    clrmlt();
	    *prfptr=0;
	  }
	}
      }
    }
  }
}

VOID
gensns(INT xloc, INT yloc, INT type, INT max, INT user)
{
  BDARR *bdtp;
  INT j,df;

  setbd();
  for (j=0; j<nterms; j++) {
    if (chkbdu(j)==1) {
      bdtp=&bdarr[j];
      df=chkdirf(bdtp->xc,bdtp->yc,xloc,yloc);
      if ((bdtp->xc!=2500) || (bdtp->yc!=2500)) {
	if ((dist > 0) && (dist <= max)) {
	  prfmlt(SNSORAT,sensor[type],dist,dirds[df]);
	  if (j != user) bdpmt();
	  outmlt(j);
	}
      }
    }
  }
}

VOID
pasys(INT xloc, INT yloc, INT volume, CHAR *messg)
{
  BDARR *bdtp;
  INT j,df;

  setbd();
  for (j=0; j<nterms; j++) {
    if ((j!=usrnum) && (chkbdu(j)==1)) {
      bdtp=&bdarr[j];
      df=chkdirf(bdtp->xc,bdtp->yc,xloc,yloc);
      if ((bdtp->xc!=2500) || (bdtp->yc!=2500)) {
	if ((dist > 0) && (dist <= volume)) {
	  prfmlt(PASYSAT,messg,dist,dirds[df]);
	  bdpmt();
	  outmlt(j);
	} else if (dist == 0) {
	  prfmlt(PASYSHR,usaptr->userid,messg);
	  bdpmt();
	  outmlt(j);
	}
      }
    }
  }
  prfmlt(PMSGSNT);
  outmlt(usrnum);
}

VOID
shop(VOID)
{
  setbd();
  prfmlt(newstt=STRMNU);
  outmlt(usrnum);
}

VOID
bdpmt(VOID)
{
  pmlt("\r>");
}

VOID
moveto(INT x, INT y)
{
  INT j;

  setbd();
  prfmlt(DROIDAR,usaptr->userid);
  bdpmt();
  outloc(x,y,usrnum,-1);
  bdptr->xc=x;
  bdptr->yc=y;
  for (j=0; j<100; j++)
    if (mine[j].damage)
      if (mine[j].x==x && mine[j].y==y) blast(&mine[j]);
}

INT
bdmove(CHAR *whatd)
{
    INT dir,x,y;

    setbd();
    if ((dir = bdgdir(whatd)) == -1) return(0);
    x=bdptr->xc+dirmx[dir];
    y=bdptr->yc+dirmy[dir];
    if (x < 0 || x > 5000 || y < 0 || y > 5000) {
      prfmlt(NOMOVE);
      outmlt(usrnum);
    } else if (bdptr->enr < ((bchs[bdptr->chs].weight/5)+1)) {
      prfmlt(CNMOVE);
      outmlt(usrnum);
    } else {
      bdptr->enr-=((bchs[bdptr->chs].weight/5)+1);
      prfmlt(LEVING,usaptr->userid,dirds[dir]);
      bdpmt();
      outloc(bdptr->xc,bdptr->yc,usrnum,-1);
      gensnsu(usrnum,0,(((bchs[bdptr->chs].weight/10)+2)),usrnum,-1);
      moveto(x,y);
      if (bdptr->active == 1) {
	prfmlt(ENTRNG,y,x);
	outmlt(usrnum);
	scan(usrnum,0,-1);
      }
    }
    return(1);
}

INT
comm(CHAR *msg)
{
  rstrin();
  if (bdptr->pavol > 10) bdptr->pavol=10;
  pasys(bdptr->xc,bdptr->yc,bdptr->pavol,msg);
  return(1);
}

INT
dmgdrd(INT usr, INT brg, INT who, INT damg, INT itnm, CHAR *dir, INT pmt, INT user)
{
  BDARR *bdtp,*bdop;
  INT j,w;

  setbd();
  bdop=&bdarr[usr];
  w=itnm;
  if (damg<=0)        return(0);
  if (chkbdu(who)==0) return(0);
  bdtp=&bdarr[who];
  bdtp->ar-=damg;
  bdtp->cbtdly=30;
  //if (dir != "-") {
  if (strcmp(dir, "-") != 0) {  // avoid C4130 warning
    //if (dir == "+") prfmlt(BDDMG1,bobj[w].desc,damg);
    if (strcmp(dir, "+") == 0) prfmlt(BDDMG1, bobj[w].desc, damg); // avoid C4130 warning
    else            prfmlt(BDDMG2,bobj[w].desc,dirbds[bdgdir(dir)],damg);
    if (bdtp->ar >= 0) {
      bdpmt();
      outmlt(who);
    } else outmlt(who);
  }
  if (bdtp->ar < 0) {
    prfmlt(BDDEAD);
    outmlt(who);
    prfmlt(BDODED,uacoff(who)->userid);
    outloc(bdarr[who].xc,bdarr[who].yc,who,-1);
    bdpmt();
    outloc(bdarr[who].xc,bdarr[who].yc,who,user);
    gensnsu(who,25,bchs[bdtp->chs].weight,pmt,user);
    bdtp->active=0;
    for (j=0; j<NBORGS; j++) {
      if ((bdbar[j].active == 1) && (sameas(bdbar[j].user,uacoff(who)->userid))) {
	strcpy(bdbar[j].user,"Renegade*");
	bdbar[j].mode=0;
      }
    }
    if (usr>=0) {
      prfmlt(BDKILL,uacoff(who)->userid);
      bdop->kills++;
      if ((bdop->flag < 1) || (bchs[bdtp->chs].weight < 2)) {
	prfmlt(SALVGE,((bchs[bdtp->chs].weight)*500));
	outmlt(usrnum);
	bdop->credits+=((bchs[bdtp->chs].weight)*500);
      } else {
	prfmlt(SALVGE2,((bchs[bdtp->chs].weight)*250),((bchs[bdtp->chs].weight)/2));
	outmlt(usrnum);
	bdop->credits+=((bchs[bdtp->chs].weight)*250);
	bdop->rsp+=((bchs[bdtp->chs].weight)/2);
      }
      return(1);
    }
    if (brg>=0) {
      bdbar[brg].kills++;
      if (!sameas(uacoff(who)->userid,bdbar[brg].user)) {
	prfmlt(BRGWON,bdbar[brg].name,uacoff(who)->userid);
	bdpmt();
	outusr(brg);
      }
      return(1);
    }
  }
  gensnsu(who,4,4+(bdrand(1,4)),pmt,user);
  return(0);
}

INT
dmgbrg(INT usr, INT brg, INT who, INT damg)
{
  BDARR *bdop;
  BDBAR *bdtp;

  setbd();
  bdop=&bdarr[usr];
  bdtp=&bdbar[who];
  if (damg<=0) return(0);
  if (bdbar[who].active == 0) return(0);
  if (usr >= 0) {
    if (sameas(bdtp->user,uacoff(usr)->userid)) {
      strcpy(bdtp->user,"Renegade*");
      bdtp->mode=0;
    }
  }
  if (damg>bdtp->ar) {
    prfmlt(BDODED,bdtp->name);
    outloc(bdtp->xc,bdtp->yc,-1,-1);
    bdpmt();
    outloc(bdtp->xc,bdtp->yc,usr,-1);
    gensns(bdtp->xc,bdtp->yc,25,(bchs[bdtp->chs].weight/5),usr);
    bdtp->active=0;
    if (usr>=0) {
      prfmlt(BDKILL,bdtp->name);
      bdop->kills++;
      if ((bdop->flag < 1) || (bchs[bdtp->chs].weight < 2)) {
	prfmlt(SALVGE,((bchs[bdtp->chs].weight)*500));
	outmlt(usrnum);
	bdop->credits+=((bchs[bdtp->chs].weight)*500);
      } else {
	prfmlt(SALVGE2,((bchs[bdtp->chs].weight)*250),
		       ((bchs[bdtp->chs].weight)/2));
	outmlt(usrnum);
	bdop->credits+=((bchs[bdtp->chs].weight)*250);
	bdop->rsp+=((bchs[bdtp->chs].weight)/2);
      }
      if (!sameas(uacoff(usr)->userid,bdbar[who].user)) {
	prfmlt(BRGDEF,bdtp->name,uacoff(usr)->userid);
	bdpmt();
	outusr(who);
      }
      return(1);
    }
    if (brg>=0) {
      bdbar[brg].kills++;
      prfmlt(BRGDEF,bdtp->name,bdbar[brg].name);
      bdpmt();
      outusr(who);
      prfmlt(BRGWON,bdbar[brg].name,bdtp->name);
      bdpmt();
      outusr(brg);
      return(1);
    }
  } else {
    gensns(bdtp->xc,bdtp->yc,4,(4+(bdrand(1,4))),usr);
    bdtp->ar-=damg;
    if ((usr >= 0) && (bdrand(1,100) <= bdtp->agr))
      if (bdtp->usr == -1) bdtp->usr=usr;
  }
  clrmlt();
  *prfptr=0;
  return(0);
}

INT
fire(CHAR *dir)
{
  BDARR *bdtp;
  INT i,pu,w,di,a,dmg,sp,sc;

  setbd();
  w=bdptr->weapon;
  if (w==255) {
    prfmlt(NOWEAP);
    outmlt(usrnum);
    return(1);
  }
  if (bwep[w].range<2) {
    prfmlt(NOFIRE);
    outmlt(usrnum);
    return(1);
  }
  pu=bwep[w].pwrus;
  if (pu>bdptr->enr) {
    prfmlt(NEEFIR);
    outmlt(usrnum);
    return(1);
  }
  if ((di=bdgdir(dir))==-1) {
    prfmlt(INVDIR);
    outmlt(usrnum);
    return(1);
  }
  gensnsu(usrnum,7+w,bwep[w].distd,usrnum,usrnum);
  bdptr->enr-=pu;
  a=(bdptr->cmp)+80;
  if (((bdrand(1,100)) > a) || ((bdptr->xc==2500) && (bdptr->yc==2500))) {
    prfmlt(MISFIR);
    outmlt(usrnum);
    return(1);
  }
  prfmlt(YOUFIR);
  outmlt(usrnum);
  prfmlt(FIROTH,usaptr->userid,bobj[w].name,dirds[di]);
  bdpmt();
  outloc(bdptr->xc,bdptr->yc,usrnum,-1);
  for (i=0; i<nterms; i++) {
    if ((chkbdu(i)==1) && (i!=usrnum)) {
      bdtp=&bdarr[i];
      if (chkdirf(bdptr->xc,bdptr->yc,bdtp->xc,bdtp->yc)==di) {
	if ((bdtp->xc!=2500) || (bdtp->yc!=2500)) {
	  if (dist<=bwep[w].range) {
	    dmg=(bdrand(bwep[w].mindm,bwep[w].maxdm));
	    if (numinv(i,ISCR)==-1)
	      sp=0;
	    else
	      if ((sp=(bdarr[i].pwr*2)) > 20) sp=20;
	    if (sp > 0) sc=bdrand((bdarr[i].pwr/2),sp);
	    else sc=0;
	    dmg-=sc;
	    if (dmg <= 0) {
	      prfmlt(BDDMG3,bobj[w].desc,dirbds[bdgdir(dir)]);
	      bdpmt();
	      outmlt(i);
	    }
	    dmgdrd(usrnum,-1,i,dmg,w,dir,usrnum,-1);
	  }
	}
      }
    }
  }
  for (i=0; i<NBORGS; i++)
    if (bdbar[i].active == 1)
      if (chkdirf(bdptr->xc,bdptr->yc,bdbar[i].xc,bdbar[i].yc)==di)
	if ((bdbar[i].xc!=2500) || (bdbar[i].yc!=2500))
	  if (dist<=bwep[w].range)
	    dmgbrg(usrnum,-1,i,(dmg=(bdrand(bwep[w].mindm,bwep[w].maxdm))));
  return(0);
}

INT
radio(CHAR *msg)
{
  setbd();
  rstrin();
  prfmlt(BDRADIO,msg);
  bdpmt();
  radout(usrnum);
  prfmlt(RMSGSNT);
  outmlt(usrnum);
  return(1);
}

INT
bdinv(INT cmd)
{
  INT i;

  setbd();
  prfmlt(BDINV1);
  prfmlt(BDINV2,ltoa(bdptr->credits));
  for (i=0; i<12; i++)
    if (bdptr->inv[i]!=255)
      pmlt("%s\r",bobj[bdptr->inv[i]].name,i);
  outmlt(usrnum);
  if (cmd) return(1);
  return(0);
}

INT
putms(INT dmg, INT nm)
{
  INT i;

  setbd();
  for (i=0; i<100; i++) {
    if (missle[i].damage==0) {
      missle[i].x=bdptr->xc;
      missle[i].y=bdptr->yc;
      missle[i].damage=dmg;
      missle[i].item=nm;
      return(0);
    }
  }
  prfmlt(NOLNCH);
  outmlt(usrnum);
  return(0);
}

INT
putlm(INT dmg, INT nm)
{
  INT i;

  setbd();
  if (bdptr->xc==-1 && bdptr->yc==-1) {
    prfmlt(RMVTRP);
    outmlt(usrnum);
    return(0);
  }
  for (i=0; i<100; i++) {
    if (mine[i].damage==0) {
      mine[i].time=600;
      mine[i].x=bdptr->xc;
      mine[i].y=bdptr->yc;
      mine[i].damage=dmg;
      mine[i].item=nm;
      return(0);
    }
  }
  prfmlt(NOUSEN);
  outmlt(usrnum);
  return(0);
}

INT
use(CHAR *what)
{
  INT a,inum,num;

  setbd();
  a=bdptr->mar;
  if ((inum=getnum(what))==-1) {
    prfmlt(DNOGOT,what);
    outmlt(usrnum);
    return(0);
  } else if ((num=numinv(usrnum,inum))==-1) {
    prfmlt(DNOGOT,what);
    outmlt(usrnum);
    return(0);
  }
  switch (inum) {
  case IRK1:
    prfmlt(BDIREP,bdptr->ar=min(a,bdptr->ar+10));
    outmlt(usrnum);
    break;
  case IRK2:
    prfmlt(BDIREP,bdptr->ar=min(a,bdptr->ar+100));
    outmlt(usrnum);
    break;
  case IRK3:
    prfmlt(BDIREP,bdptr->ar=min(a,bdptr->ar+250));
    outmlt(usrnum);
    break;
  case ILM1:
    prfmlt(BDMINE);
    outmlt(usrnum);
    putlm(bdrand(1,5),ILM1);
    break;
  case ILM2:
    prfmlt(BDMINE);
    outmlt(usrnum);
    putlm(bdrand(5,10),ILM2);
    break;
  case ILM3:
    prfmlt(BDMINE);
    outmlt(usrnum);
    putlm(bdrand(10,20),ILM3);
    break;
  case ILM4:
    prfmlt(BDMINE);
    outmlt(usrnum);
    putlm(bdrand(20,40),ILM4);
    break;
  case ILM5:
    prfmlt(BDMINE);
    outmlt(usrnum);
    putlm(bdrand(30,60),ILM5);
    break;
  }
  if (num==12) {
    prfmlt(DNOGOT,what);
    outmlt(usrnum);
  } else bdptr->inv[num]=255;
  return(0);
}

INT
arm(CHAR *what,INT ds)
{
  INT inum,num;

  setbd();
  if ((inum=getnum(what))==-1) {
    prfmlt(DNOGOT,what);
    outmlt(usrnum);
    return(0);
  } else if ((num=numinv(usrnum,inum))==-1) {
    prfmlt(DNOGOT,what);
    outmlt(usrnum);
    return(0);
  } else if (num==12) {
    prfmlt(DNOGOT,what);
    outmlt(usrnum);
    return(0);
  }
  if ((bdptr->xc==2500) && (bdptr->yc==2500)) {
    prfmlt(NOLNCH);
    outmlt(usrnum);
    return(0);
  }
  if (ds <= bmis[inum-IMS1].range)
    putms(bdrand(bmis[inum-IMS1].mindm,bmis[inum-IMS1].maxdm),inum);
  else {
    prfmlt(TOOFAR,bmis[inum-IMS1].range);
    outmlt(usrnum);
    return(0);
  }
  bdptr->inv[num]=255;
  return(1);
}

INT
launch(CHAR *d,INT ds)
{
  INT i,dir;

  setbd();
  dir=bdgdir(d);
  for (i=0; i<100; i++) {
    if (missle[i].damage>0 && bdptr->xc==missle[i].x && bdptr->yc==missle[i].y) {
      missle[i].x+=ds*dirmx[dir];
      missle[i].y+=ds*dirmy[dir];
      missle[i].time=((ds/5)+1);
      prfmlt(BDLNCH,ds,dirds[dir]);
      outmlt(usrnum);
      prfmlt(LNCOTH,usaptr->userid,dirds[dir]);
      bdpmt();
      outloc(bdptr->xc,bdptr->yc,usrnum,-1);
      return(0);
    }
  }
  return(0);
}

VOID
scanner(CHAR *d, INT scand)
{
  INT dir;

  setbd();
  if ((dir=bdgdir(d))==-1) {
    prfmlt(INVDIR);
    outmlt(usrnum);
  } else {
    prfmlt(BDSCAND,dirds[dir]);
    outmlt(usrnum);
    scan(usrnum,scand,dir);
  }
}

VOID
bscanner(CHAR *d, INT brg, INT scand)
{
  INT dir;

  setbd();
  if ((dir=bdgdir(d))==-1) {
    prfmlt(INVDIR);
    outmlt(usrnum);
  } else {
    prfmlt(BDSCAND,dirds[dir]);
    outmlt(usrnum);
    bscan(usrnum,brg,scand,dir);
  }
}

INT
attack(CHAR *who)
{
  BDARR *bdtp;
  INT i,a,b,n,othd=-2,dmg;

  setbd();
  n=0;
  b=0;
  for (i=0; i<nterms; i++) {
    if (chkbdu(i)==1) {
      bdtp=&bdarr[i];
      if ((sameto(who,uacoff(i)->userid)) && (bdtp->xc==bdptr->xc) && (bdtp->yc==bdptr->yc)) {
	if ((bdtp->xc!=2500) || (bdtp->yc!=2500)) {
	  n++;
	  othd=i;
	  b=-1;
	}
      }
    }
  }
  if (b > -1) {
    for (i=0; i<NBORGS; i++) {
      if (bdbar[i].active == 1) {
	if ((sameto(who,bdbar[i].name)) && (bdbar[i].xc==bdptr->xc) && (bdbar[i].yc==bdptr->yc)) {
	  if ((bdbar[i].xc!=2500) || (bdbar[i].yc!=2500)) {
	    n++;
	    b=i;
	  }
	}
      }
    }
  }
  if (n == 0) {
    prfmlt(NOFIND);
    outmlt(usrnum);
    return(1);
  }
  if (n > 1) {
    prfmlt(ATTWCH);
    outmlt(usrnum);
    return(1);
  }
  if (othd==usrnum) {
    prfmlt(NATTSF);
    outmlt(usrnum);
    return(1);
  }
  if (bdptr->enr < ((bchs[bdptr->chs].weight/5)+1)) {
    prfmlt(TOOEXH);
    outmlt(usrnum);
    return(1);
  }
  bdptr->enr-=((bchs[bdptr->chs].weight/5)+1);
  a=(bdptr->agl);
  if ((bdrand(1,100))>a) {
    prfmlt(YOUMIS);
    outmlt(usrnum);
    if (b==-1) {
      prfmlt(BDMSYU,usaptr->userid);
      bdpmt();
      outmlt(othd);
      prfmlt(BDMSOT,usaptr->userid,uacoff(othd)->userid);
      bdpmt();
      outloc(bdptr->xc,bdptr->yc,usrnum,othd);
    } else {
      prfmlt(BDMSOT,usaptr->userid,bdbar[b].name);
      bdpmt();
      outloc(bdptr->xc,bdptr->yc,usrnum,-1);
    }
    return(1);
  }
  dmg=bdrand(((bchs[bdptr->chs].weight/5)+1),((bchs[bdptr->chs].weight/2)+2));
  if (b==-1) {
    prfmlt(BDDMYU,usaptr->userid,dmg);
    bdpmt();
    outmlt(othd);
    prfmlt(BDDOTH,usaptr->userid,uacoff(othd)->userid);
    bdpmt();
    outloc(bdptr->xc,bdptr->yc,usrnum,othd);
  } else {
    prfmlt(BDDOTH,usaptr->userid,bdbar[b].name);
    bdpmt();
    outloc(bdptr->xc,bdptr->yc,usrnum,-1);
  }
  if (b==-1) {
    if (dmgdrd(usrnum,-1,othd,dmg,-1,"-",usrnum,usrnum)==0) {
      prfmlt(BDDMHM,uacoff(othd)->userid,dmg);
      outmlt(usrnum);
    }
  } else {
    if (dmgbrg(usrnum,-1,b,dmg)==0) {
      prfmlt(BDDMHM,bdbar[b].name,dmg);
      outmlt(usrnum);
    }
  }
  return(1);
}

VOID
playbd(VOID)
{
  setbd();
  prfmlt(newstt=PLYBD);
  outmlt(usrnum);
  gendrd();
  prfmlt(TRNSIN,usaptr->userid);
  bdpmt();
  outloc(bdptr->xc,bdptr->yc,usrnum,-1);
  gensnsu(usrnum,24,5,usrnum,-1);
  shwsta();
  bdpmt();
  outmlt(usrnum);
}

VOID
strbd(VOID)
{
  setbd();
  switch(sel) {
  case 0:
    prfmlt(newstt=STRPMT);
    outmlt(usrnum);
    break;
  case '?':
    prfmlt(newstt=STRMNU);
    outmlt(usrnum);
    break;
  case 'i':
    bdinv(0);
    prfmlt(newstt=STRPMT);
    outmlt(usrnum);
    break;
  case 'x':
    newstt=PLYBD;
    shwsta();
    bdpmt();
    outmlt(usrnum);
    break;
  case 'w':
    prfmlt(STRCAT1);
    prfmlt(STRPMT);
    outmlt(usrnum);
    break;
  case '1':
    prfmlt(STRCAT2);
    prfmlt(STRPMT);
    outmlt(usrnum);
    break;
  case '2':
    prfmlt(STRCAT3);
    prfmlt(STRPMT);
    outmlt(usrnum);
    break;
  case '3':
    prfmlt(STRCAT4);
    prfmlt(STRPMT);
    outmlt(usrnum);
    break;
  case 'e':
    prfmlt(STRCAT5);
    prfmlt(STRPMT);
    outmlt(usrnum);
    break;
  case 'b':
    prfmlt(newstt=BUYITM);
    outmlt(usrnum);
    break;
  case 's':
    prfmlt(newstt=SELITM);
    outmlt(usrnum);
    break;
  default:
    prfmlt(newstt=STRPMT);
    outmlt(usrnum);
    break;
  }
}

INT
getnum(CHAR *us)
{
  INT inum,i;

  inum=-1;
  for (i=0; i<NUMITM; i++) if (sameas(us,bobj[i].name)) inum=i;
  return(inum);
}

INT
invspc(VOID)
{
  INT i;

  for (i=0; i<12; i++) if (bdptr->inv[i]==255) return(i);
  return(-1);
}

VOID
bdbuy(VOID)
{
  INT num,where;

  setbd();
  if (!sameas(margv[0],"x")) {
      if ((num=getnum(margv[0]))==-1) {
          if ((sameas(margv[0],"chassis")) && (margc==2)) {
              if ((atoi(margv[1]) > CHSMOD) || (atoi(margv[1]) < 1)) {
                  prfmlt(NOSCHS);
                  outmlt(usrnum);
              } else if (bdptr->credits < bchs[atoi(margv[1])-1].price) {
                  prfmlt(CNACHS,atoi(margv[1]));
                  outmlt(usrnum);
              } else {
                  bdptr->credits-=bchs[atoi(margv[1])-1].price;
                  bdptr->credits+=bchs[bdptr->chs].price/2;
                  prfmlt(BUYCHS,ltoa(bchs[atoi(margv[1])-1].price),ltoa(bchs[bdptr->chs].price/2));
                  outmlt(usrnum);
                  updchs(atoi(margv[1])-1);
              }
          } else {
              prfmlt(DNTCAR);
              outmlt(usrnum);
          }
      } else if ((where=invspc())==-1) {
          prfmlt(INVFULL,margv[0]);
          outmlt(usrnum);
      } else if (bdptr->credits<bobj[num].price) {
          prfmlt(CNAITM,margv[0]);
          outmlt(usrnum);
      } else if ((bdptr->weapon!=255) && (num<IRK1)) {
          prfmlt(ALRWEP);
          outmlt(usrnum);
      } else if ((num<IRK3) && ( (num > NUM_BWEP - 1) || (bchs[bdptr->chs].wep < bwep[num].pwrus) ) ) {  // RH 6/19/2024 avoid C6385 warning
          prfmlt(NENPWR); 
          outmlt(usrnum);
      } else if ((num>=IMS1) && (num<=IMS16) && (bchs[bdptr->chs].mis*10 != bmis[num-IMS1].range)) {
          prfmlt(NTTMIS);
          outmlt(usrnum);
      } else if ((num>=ILM1) && (num<=ILM5) && (bchs[bdptr->chs].min < 1)) {
          prfmlt(NOMINE);
          outmlt(usrnum);
      } else {
          if (num<IRK1) bdptr->weapon=(CHAR)num;
          else bdptr->inv[where]=(CHAR)num;
          if (num < NUM_BOBJ - 1) {
              bdptr->credits -= bobj[num].price; // RH 6/19/2024 aboid C6385 warning.
              prfmlt(YOUBUY, bobj[num].name, ltoa(bobj[num].price));
              outmlt(usrnum);
          } else {
              shocst("ELWBDS: Overflow in bobj", spr("num was %d", num));
          }// else what, if there's overflow? 
      }
  }
  prfmlt(newstt=STRPMT);
  outmlt(usrnum);
}

VOID
bdsell(VOID)
{
  INT num,invloc;

  setbd();
  if (!sameas(margv[0],"x")) {
    if ((num=getnum(margv[0]))==-1) {
      prfmlt(DNOGOT,margv[0]);
      outmlt(usrnum);
    } else if ((invloc=numinv(usrnum,num))==-1) {
      prfmlt(DNOGOT,margv[0]);
      outmlt(usrnum);
    } else {
      prfmlt(SLDITM,bobj[num].name,ltoa(bobj[num].price/2));
      outmlt(usrnum);
      if (invloc==12) bdptr->weapon=255;
      else bdptr->inv[invloc]=255;
      bdptr->credits+=(bobj[num].price/2);
    }
  }
  prfmlt(newstt=STRPMT);
  outmlt(usrnum);
}

INT
numinv(INT who, INT obj)
{
  INT i;

  for (i=0; i<12; i++) if (bdarr[who].inv[i]==obj) return(i);
  if (bdarr[who].weapon==obj) return(12);
  return(-1);
}

INT bdnum(CHAR *tmpstr)
{
     INT x;

     x = atoi(tmpstr);
     if ((x > 0) && (x < 30001)) return(1);
     else return(0);
}

INT
bdrand(INT lo,INT hi)
{
/* // old WGDOS routine    
     INT ln,hn;
     static INT init=0;
     static ULONG seed=0x75BE6ACCL;
     union REGS regs;

     if (init++ == 0) {
       regs.h.ah=0x2C;
       intdos(&regs,&regs);
       ln=regs.x.cx+regs.x.dx;
       regs.h.ah=regs.h.dl;
       regs.h.al=regs.h.dh;
       hn=2*regs.x.ax+(regs.x.cx&1);
       seed=((LONG)hn<<16)+ln;
     }
     return((INT)((((hi+1L)-lo)*((seed=1664525L*seed+1L)>>16))>>16)+lo);
 */
#ifdef __BUILDV10MODULE
    return(lo + rand() % (hi - lo + 1)); // same idea, but for Visual Studio
#else
    return (random(hi - lo + 1) + lo);   // want 4-17, give me rand(14) which is 0-13 + 4 is 4-17 - WG32
#endif
}

VOID
setbd(VOID)
{
  setmbk(bdmb);
  dfaSetBlk(bdbb);
  bdptr=&bdarr[usrnum];
}

VOID
shtbd(VOID)
{
  clsmsg(bdmb);
  dfaClose(bdbb);
}

VOID
hupbd(VOID)
{
  setbd();
  if ((chkbdu(usrnum)==1) || (chkbdu(usrnum)==2)) exitbd();
  if (bdptr->ar>=0) bdspl();
}

VOID
delbd(CHAR *id)
{
  dfaSetBlk(bdbb);
  if (dfaAcqEQ(NULL,id,0)) dfaDelete();
}

VOID
bdlpl(VOID)
{
  INT i;
  setbd();
  if (dfaQueryEQ(usaptr->userid,0)) {
    dfaAbsRec(&bdsptr,0);
    bdptr->credits=bdsptr.credits;
    bdptr->weapon= bdsptr.weapon;
    bdptr->xc=     bdsptr.xc;
    bdptr->yc=     bdsptr.yc;
    bdptr->chs=    bdsptr.chs;
    bdptr->pwr=    bdsptr.pwr;
    bdptr->cmp=    bdsptr.cmp;
    bdptr->stb=    bdsptr.stb;
    bdptr->man=    bdsptr.man;
    bdptr->str=    bdsptr.str;
    bdptr->spd=    bdsptr.spd;
    bdptr->agl=    bdsptr.agl;
    bdptr->trg=    bdsptr.trg;
    bdptr->enr=    bdsptr.enr;
    bdptr->ar=     bdsptr.ar;
    bdptr->mar=    bdsptr.mar;
    bdptr->rfreq=  bdsptr.rfreq;
    bdptr->pavol=  bdsptr.pavol;
    bdptr->active= bdsptr.active;
    for (i=0; i<12; i++) bdptr->inv[i]=bdsptr.inv[i];
    bdptr->flag=   bdsptr.flag;
    bdptr->rsp=    bdsptr.rsp;
    bdptr->kills=  bdsptr.kills;
    bdptr->cbtdly= bdsptr.cbtdly;
  } else {
    gendrd();
  }
}

VOID
bdspl(VOID)
{
  INT i;
  setbd();
  setmem(&bdsptr,sizeof(struct bdsave),0);
  strncpy(bdsptr.userid,usaptr->userid,30);
  bdsptr.credits=bdptr->credits;
  bdsptr.weapon= bdptr->weapon;
  bdsptr.xc=     bdptr->xc;
  bdsptr.yc=     bdptr->yc;
  bdsptr.chs=    bdptr->chs;
  bdsptr.pwr=    bdptr->pwr;
  bdsptr.cmp=    bdptr->cmp;
  bdsptr.stb=    bdptr->stb;
  bdsptr.man=    bdptr->man;
  bdsptr.str=    bdptr->str;
  bdsptr.spd=    bdptr->spd;
  bdsptr.agl=    bdptr->agl;
  bdsptr.trg=    bdptr->trg;
  bdsptr.enr=    bdptr->enr;
  bdsptr.ar=     bdptr->ar;
  bdsptr.mar=    bdptr->mar;
  bdsptr.rfreq=  bdptr->rfreq;
  bdsptr.pavol=  bdptr->pavol;
  bdsptr.active= bdptr->active;
  for (i=0; i<12; i++) bdsptr.inv[i]=bdptr->inv[i];
  bdsptr.flag=   bdptr->flag;
  bdsptr.rsp=    bdptr->rsp;
  bdsptr.kills=  bdptr->kills;
  bdsptr.cbtdly= bdptr->cbtdly;
  if (!dfaQueryEQ(usaptr->userid,0)) dfaInsert(&bdsptr);
  else {
    dfaAbsRec(NULL,0);
    dfaUpdate(&bdsptr);
  }
}
