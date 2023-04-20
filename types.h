//
//  types.h
//  lwcalculator
//
//  Created by Fire937 on 6/8/22.
//

#ifndef types_h
#define types_h

#include "macro.h"

typedef cl_uint sc_stat_type;
typedef cl_uint bullet_type;
typedef cl_uchar bullet_element;
typedef cl_uint bullet_attribute; // YIN/YANG
typedef cl_uint attack_targetting; // SOLO/ALL

std::string macros =
    "#define STAT_BLANK    0\n"
    "#define STAT_HEALTH   1\n"
    "#define STAT_AGILITY  2\n"
    "#define STAT_YANG_ATK 3\n"
    "#define STAT_YANG_DEF 4\n"
    "#define STAT_YIN_ATK  5\n"
    "#define STAT_YIN_DEF  6\n"
    "#define BULLET_TYPE_OFUDA    0x1\n"
    "#define BULLET_TYPE_NORMAL   0x2\n"
    "#define BULLET_TYPE_ENERGY   0x3\n"
    "#define BULLET_TYPE_PHYSICAL 0x4\n"
    "#define BULLET_TYPE_LIQUID   0x5\n"
    "#define BULLET_TYPE_LIGHT    0x6\n"
    "#define BULLET_TYPE_LASER    0x7\n"
    "#define BULLET_TYPE_SHARP    0x8\n"
    "#define BULLET_TYPE_HEAVY    0x9\n"
    "#define BULLET_TYPE_MISSILE  0xA\n"
    "#define BULLET_TYPE_SLASH    0xB\n"
    "#define ELEMENT_NONE  0x00000000\n"
    "#define ELEMENT_SUN   (1 << 0)\n"
    "#define ELEMENT_MOON  (1 << 1)\n"
    "#define ELEMENT_FIRE  (1 << 2)\n"
    "#define ELEMENT_WATER (1 << 3)\n"
    "#define ELEMENT_WOOD  (1 << 4)\n"
    "#define ELEMENT_METAL (1 << 5)\n"
    "#define ELEMENT_EARTH (1 << 6)\n"
    "#define ELEMENT_STAR  (1 << 7)\n"
    "#define ELEMENT_ALL   0xFFFFFFFF\n"
    "#define RACE_HUMAN    (1 << 0)\n"
    "#define RACE_YOUKAI   (1 << 1)\n"
    "#define RACE GENSOKYO (1 << 2)\n"
    "#define RACE_MAGICIAN (1 << 3)\n"
    "#define BULLET_ATTRIBUTE_YIN 0x0\n"
    "#define BULLET_ATTRIBUTE_YANG 0x1\n"
    "#define ATTACK_TARGETTING_SOLO 1\n"
    "#define ATTACK_TARGETTING_ALL 3\n"
    "#define MOD_YANG_ATK 0\n"
    "#define MOD_YANG_DEF 1\n"
    "#define MOD_YIN_ATK  2\n"
    "#define MOD_YIN_DEF  3\n"
    "#define MOD_EVASION  4\n"
    "#define MOD_ACCURACY 5\n"
    "#define MOD_CRIT_ATK 6\n"
    "#define MOD_CRIT_ACC 8\n"
    "#define MOD_AGILITY  8\n"
    "#define SC_MAX_MODIFIERS 4\n"
    "#define SPELL_MAX_MODIFIERS 4\n"
    "#define SKILL_MAX_MODIFIERS 4\n"
    "#define NUMBER_OF_UNIQUE_MODIFIERS 9\n"
    "#define BARRIER_BROKEN    0\n"
    "#define BARRIER_HEALTHY   (1 << 0)\n"
    "#define BARRIER_POISON    (1 << 1)\n"
    "#define BARRIER_FREEZE    (1 << 2)\n"
    "#define BARRIER_PARALYZE  (1 << 3)\n"
    "#define BARRIER_BLIND     (1 << 4)\n"
    "#define BARRIER_BURN      (1 << 5)\n"
    "#define BARRIER_NUMBER_OF_STATES 6\n"
    "#define BARRIER_MAX_AMOUNT 7\n"
;

typedef struct __attribute__ ((packed)) skill
{
    cl_uint modifier_type[SKILL_MAX_MODIFIERS];
    cl_int modifier_value[SKILL_MAX_MODIFIERS];
    cl_uint modifier_duration[SKILL_MAX_MODIFIERS];
} skill;

typedef struct __attribute__ ((packed)) story_card
{
    sc_stat_type stat_type_1;
    cl_uint stat_value_1;
    sc_stat_type stat_type_2;
    cl_uint stat_value_2;
    
    cl_uint modifier_type[SC_MAX_MODIFIERS];
    cl_int modifier_value[SC_MAX_MODIFIERS];
    cl_uint modifier_duration[SC_MAX_MODIFIERS];
} story_card;

typedef struct __attribute__((packed)) attack_line
{
    cl_float pow;
    cl_float hit;
    cl_float crit;
    bullet_attribute attribute;
    bullet_type bullet;
    bullet_element element;
    cl_uint bullet_quantity;
    cl_ulong status_breaks;
    cl_ulong killers;
    cl_float hard;
    cl_float slicing;
    cl_ushort pierce;
} attack_line;

typedef struct __attribute__((packed)) attack
{
    attack_line line[6];
    cl_uint danmaku_modifier[5];
    cl_uint boost_layout[4];
    attack_targetting targetting;
    
    cl_uint pre_modifier_type[SPELL_MAX_MODIFIERS];
    cl_int pre_modifier_value[SPELL_MAX_MODIFIERS];
    cl_uint pre_modifier_duration[SPELL_MAX_MODIFIERS];
    
    cl_uint post_modifier_type[SPELL_MAX_MODIFIERS];
    cl_int post_modifier_value[SPELL_MAX_MODIFIERS];
    cl_uint post_modifier_duration[SPELL_MAX_MODIFIERS];
} attack;

typedef struct __attribute__((packed)) lw_character
{
    attack spell[7];
    
    cl_uint level;
    cl_uint weakness;
    cl_uint resistance;
    cl_uint stats[7];
    
    cl_ulong races;
    
    cl_ulong barriers;
    cl_uint barrier_status_duration[BARRIER_MAX_AMOUNT];
        
    cl_int modifier_value[NUMBER_OF_UNIQUE_MODIFIERS];
    cl_uint modifier_duration[NUMBER_OF_UNIQUE_MODIFIERS];
    
    skill skills[3];
} lw_character;

#endif /* types_h */
