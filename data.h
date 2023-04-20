//
//  data.h
//  lwcalculator
//
//  Created by Fire937 on 6/8/22.
//

#ifndef data_h
#define data_h

#include "types.h"

#define SC_BLANK {0, 0, 0, 0, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}
#define SC_FROGGY_HAT { STAT_YANG_ATK, 60, STAT_YIN_DEF, 60, {MOD_ACCURACY}, {2}, {2}}
#define SC_A_CURIOUS_FESTIVAL { STAT_AGILITY, 81, STAT_YANG_DEF, 99, {MOD_YIN_ATK}, {3}, {2}}
#define SC_ITS_SPRING { STAT_YANG_ATK, 72, STAT_YANG_DEF, 68 }
#define SC_POLTERGEIST_SISTERS_CONCERT { STAT_YANG_DEF, 90, STAT_YIN_DEF, 90, {MOD_ACCURACY}, {3}, {2}}
#define SC_WHERE_THE_WIND_PRIESTESS_IS { STAT_HEALTH, 675, STAT_AGILITY, 45, {MOD_BULLET_TYPE_ENERGY, MOD_BULLET_TYPE_LIQUID}, {35,35}, {1,1} }
#define SC_UNKNOWN_BARRIER_TEAM { STAT_YANG_ATK, 70, STAT_YIN_ATK, 80, {MOD_BULLET_TYPE_ENERGY, MOD_YANG_ATK}, {50, 2}, {1, 1} }
#define SC_BOO { STAT_YANG_ATK, 68, STAT_YIN_ATK, 72, {MOD_YIN_ATK}, {2}, {2}}

#define SC_GOOD_OR_EVIL { STAT_YANG_ATK, 66, STAT_YIN_ATK, 66, {MOD_YANG_ATK}, {1}, {3}}
#define SC_753 { STAT_YANG_ATK, 46, STAT_YIN_ATK, 32, {MOD_ACCURACY}, {1}, {3}}
#define SC_EATING_CONTEST { STAT_HEALTH, 600, STAT_YIN_ATK, 60, {MOD_BULLET_TYPE_BODY}, {45}, {1} }
#define SC_PUPPETEER_AND_NECROMANCER { STAT_YIN_ATK, 96, STAT_YIN_DEF, 54 }

namespace lwdata
{
inline constexpr cl_ulong HEALTHY_BARRIER_5 = (BARRIER_HEALTHY + (BARRIER_HEALTHY << BARRIER_NUMBER_OF_STATES) + (BARRIER_HEALTHY << (BARRIER_NUMBER_OF_STATES * 2)) + (BARRIER_HEALTHY << (BARRIER_NUMBER_OF_STATES * 3)) + (BARRIER_HEALTHY << (BARRIER_NUMBER_OF_STATES * 4))) << (BARRIER_MAX_AMOUNT - 5);
inline constexpr cl_ulong HEALTHY_BARRIER_7 = HEALTHY_BARRIER_5 + BARRIER_HEALTHY + (BARRIER_HEALTHY << 1);

inline attack reisen_ss = {
    {
        { 12.21, 0.67, 0.1, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_NORMAL, ELEMENT_NONE, 3, 0, RACE_GENSOKYO },
        { 2.05, 0.80, 0.10, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_LASER, ELEMENT_NONE, 8 },
        { 2.05, 0.80, 0.10, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_LASER, ELEMENT_NONE, 8 },
        { 2.05, 0.80, 0.10, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_LASER, ELEMENT_NONE, 8 },
        { 2.05, 0.80, 0.10, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_LASER, ELEMENT_NONE, 8 },
        { 2.05, 0.80, 0.10, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_LASER, ELEMENT_NONE, 8 },
    },
    { 105, 109, 114, 119, 123 },
    { 1, 1, 1, 1 },
    ATTACK_TARGETTING_ALL
};

inline attack focus_shot = {
    {
        { 2.05, 0.80, 0.10, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_LASER, ELEMENT_NONE, 8 },
        { 2.05, 0.80, 0.10, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_LASER, ELEMENT_NONE, 8 },
        { 2.05, 0.80, 0.10, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_LASER, ELEMENT_NONE, 8 },
        { 2.05, 0.80, 0.10, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_LASER, ELEMENT_NONE, 8 },
        { 2.05, 0.80, 0.10, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_LASER, ELEMENT_NONE, 8 },
        { 2.05, 0.80, 0.10, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_LASER, ELEMENT_NONE, 8 },
    },
    { 104, 109, 113, 117, 121 },
    { 1, 1, 1, 1 },
    ATTACK_TARGETTING_ALL
};

inline attack meiling_spell_1 = {
    {
        { 7.60, 0.75, 0.05, BULLET_ATTRIBUTE_YIN, BULLET_TYPE_ENERGY, ELEMENT_NONE, 13, 0, RACE_YOUKAI },
        { 13.17, 0.75, 0.05, BULLET_ATTRIBUTE_YIN, BULLET_TYPE_ENERGY, ELEMENT_STAR, 2, 0, RACE_YOUKAI },
        { 12.07, 0.75, 0.05, BULLET_ATTRIBUTE_YIN, BULLET_TYPE_ENERGY, ELEMENT_STAR, 2, 0, RACE_MAGICIAN },
        { 21.94, 0.75, 0.05, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_ENERGY, ELEMENT_NONE, 1, 0, RACE_MAGICIAN, 0.8 },
        { 19.75, 0.75, 0.05, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_ENERGY, ELEMENT_NONE, 1, 0, RACE_MAGICIAN, 0.8 },
        { 17.55, 0.75, 0.05, BULLET_ATTRIBUTE_YIN, BULLET_TYPE_ENERGY, ELEMENT_STAR, 1 },
    },
    { 100, 107, 113, 120, 127 },
    { 1, 3, 5, 6 },
    ATTACK_TARGETTING_SOLO,
    
    { MOD_YIN_DEF, MOD_YIN_ATK, 0, 0 }, // type
    { 2, 4, 0, 0 }, // value
    { 3, 1, 0, 0 }, // duration
    
    { 0, 0, 0, 0 }, // type
    { 0, 0, 0, 0 }, // value
    { 0, 0, 0, 0 }, // duration
};

inline attack meiling_spell_2 = {
    {
        { 10.97, 0.75, 0.05, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_BODY, ELEMENT_NONE, 9, 0, RACE_HUMAN },
        { 13.17, 0.75, 0.05, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_BODY, ELEMENT_EARTH, 2, 0, 0, 0.3 },
        { 12.07, 0.75, 0.05, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_BODY, ELEMENT_EARTH, 2, 0, 0, 0.3 },
        { 21.94, 0.75, 0.05, BULLET_ATTRIBUTE_YIN, BULLET_TYPE_BODY, ELEMENT_NONE, 1, 0, RACE_HUMAN, 0.4 },
        { 19.75, 0.75, 0.05, BULLET_ATTRIBUTE_YIN, BULLET_TYPE_BODY, ELEMENT_NONE, 1, 0, RACE_HUMAN, 0.4 },
        { 17.55, 0.75, 0.05, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_BODY, ELEMENT_EARTH, 1, 0, 0, 0.8 }
    },
    { 100, 107, 113, 120, 127 },
    { 1, 3, 5, 6 },
    ATTACK_TARGETTING_SOLO,
    { MOD_YANG_ATK, 0, 0, 0 },
    { 4, 0, 0, 0 },
    { 1, 0, 0, 0 },
    
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
};

inline attack meiling_spell_lw = {
    {
        { 14.07, 0.75, 0.05, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_ENERGY, ELEMENT_NONE, 13, 0, RACE_INCIDENT_RESOLVER, 1.20 },
        { 10.97, 0.75, 0.05, BULLET_ATTRIBUTE_YIN, BULLET_TYPE_ENERGY, ELEMENT_NONE, 4, 0, RACE_TENGU | RACE_INCIDENT_RESOLVER, 0 },
        { 9.14, 0.75, 0.05, BULLET_ATTRIBUTE_YIN, BULLET_TYPE_ENERGY, ELEMENT_STAR, 4, 0, RACE_TENGU | RACE_INCIDENT_RESOLVER, 0 },
        { 7.31, 0.75, 0.05, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_ENERGY, ELEMENT_EARTH, 4, 0, 0, 1.40, 0, 1 },
        { 7.31, 0.75, 0.05, BULLET_ATTRIBUTE_YIN, BULLET_TYPE_ENERGY, ELEMENT_STAR, 3, 0, RACE_TENGU | RACE_INCIDENT_RESOLVER, 0 },
        { 4.88, 0.75, 0.05, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_ENERGY, ELEMENT_EARTH, 3, 0, 0, 1.50, 0, 1 }
    },
    { 100, 107, 114, 122, 129 },
    { 1, 4, 5, 6 },
    ATTACK_TARGETTING_ALL,
    { MOD_YANG_ATK, 0, 0, 0 },
    { 4, 0, 0, 0 },
    { 1, 0, 0, 0 },
    
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
};

inline attack reisen_udongein_spell_2 = {
    {
        { 76.80, 0.75, 0.05, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_LASER, ELEMENT_MOON, 1 },
        { 10.97, 0.75, 0.05, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_BODY, ELEMENT_NONE, 9 },
        { 10.97, 0.75, 0.05, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_BODY, ELEMENT_NONE, 9 },
        { 10.97, 0.75, 0.05, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_BODY, ELEMENT_NONE, 9 },
        { 10.97, 0.75, 0.05, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_BODY, ELEMENT_NONE, 9 },
        { 10.97, 0.75, 0.05, BULLET_ATTRIBUTE_YANG, BULLET_TYPE_BODY, ELEMENT_NONE, 9 }
    },
    { 100, 106, 113, 119, 126 },
    { 1, 2, 4, 6 },
    ATTACK_TARGETTING_SOLO,
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
};

inline attack remilia_spell_2 = {
    {
        { 32.91, 0.75, 0.05, BULLET_ATTRIBUTE_YIN, BULLET_TYPE_SHARP, ELEMENT_FIRE, 2 },
        { 7.60, 0.75, 0.05, BULLET_ATTRIBUTE_YIN, BULLET_TYPE_ENERGY, ELEMENT_NONE, 13 },
        { 7.60, 0.75, 0.05, BULLET_ATTRIBUTE_YIN, BULLET_TYPE_ENERGY, ELEMENT_NONE, 13 },
        { 7.60, 0.75, 0.05, BULLET_ATTRIBUTE_YIN, BULLET_TYPE_ENERGY, ELEMENT_NONE, 13 },
        { 7.60, 0.75, 0.05, BULLET_ATTRIBUTE_YIN, BULLET_TYPE_ENERGY, ELEMENT_NONE, 13 },
        { 7.60, 0.75, 0.05, BULLET_ATTRIBUTE_YIN, BULLET_TYPE_ENERGY, ELEMENT_NONE, 13 },
    },
    { 100, 107, 114, 121, 128 },
    { 1, 2, 3, 6 },
    ATTACK_TARGETTING_SOLO,
    
    { MOD_YIN_ATK, MOD_ACCURACY, 0, 0 }, // type
    { 1, 1, 0, 0 }, // value
    { 3, 3, 0, 0 }, // duration
    
    { 0, 0, 0, 0 }, // type
    { 0, 0, 0, 0 }, // value
    { 0, 0, 0, 0 }, // duration
};

inline lw_character azusa =
{
    {
        focus_shot,
        focus_shot,
        focus_shot,
        focus_shot,
        focus_shot,
        focus_shot,
        focus_shot
    },
    100,
    ELEMENT_NONE,
    ELEMENT_NONE,
    {
        0,
        5625,
        1285+229,
        1795+286,
        905+95,
        1315+32,
        925
    },
    0,
    HEALTHY_BARRIER_5,
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0}
};

inline lw_character meiling =
{
    {
        meiling_spell_1,
        meiling_spell_2,
        meiling_spell_1,
        meiling_spell_2,
        meiling_spell_lw,
        meiling_spell_1,
        meiling_spell_1
    },
    100,
    ELEMENT_SUN | ELEMENT_METAL,
    ELEMENT_MOON | ELEMENT_WATER,
    {
        0,
        (cl_uint)(5800*1.09),
        (cl_uint)(920*1.09),
        (cl_uint)(1190*1.09),
        (cl_uint)(990*1.09),
        (cl_uint)(1230*1.09),
        (cl_uint)(960*1.09)
    },
    RACE_YOUKAI,
    HEALTHY_BARRIER_5,
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {
        { {MOD_YANG_DEF, MOD_YANG_ATK, 0, 0}, {3, 3, 0, 0}, {3, 3, 0, 0} }, // type value duration
        { {MOD_YIN_ATK}, {3}, {3} },
        { {MOD_EVASION}, {-1}, {2} }
    }
};

inline lw_character reisen =
{
    {
        reisen_ss,
        reisen_ss,
        reisen_ss,
        reisen_ss,
        reisen_ss,
        reisen_ss,
        reisen_ss,
    },
    57,
    ELEMENT_SUN | ELEMENT_METAL,
    ELEMENT_MOON | ELEMENT_WATER,
    {
        0,
        1280,
        284,
        172,
        272,
        217,
        281
    },
    RACE_YOUKAI,
    HEALTHY_BARRIER_5,
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0}
};

inline lw_character reisen_udongein =
{
    {
        reisen_udongein_spell_2,
        reisen_udongein_spell_2,
        reisen_udongein_spell_2,
        reisen_udongein_spell_2,
        reisen_udongein_spell_2,
        reisen_udongein_spell_2,
        reisen_udongein_spell_2
    },
    57,
    ELEMENT_SUN | ELEMENT_METAL,
    ELEMENT_MOON | ELEMENT_WATER,
    {
        0,
        2297,
        512,
        543,
        462,
        486,
        435
    },
    RACE_YOUKAI,
    HEALTHY_BARRIER_5,
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0}
};

inline lw_character remilia =
{
    {
        remilia_spell_2,
        remilia_spell_2,
        remilia_spell_2,
        remilia_spell_2,
        remilia_spell_2,
        remilia_spell_2,
        remilia_spell_2
    },
    100,
    ELEMENT_SUN | ELEMENT_METAL,
    ELEMENT_MOON | ELEMENT_WATER,
    {
        0,
        3942,
        964,
        791,
        696,
        1027,
        830
    },
    RACE_YOUKAI,
    HEALTHY_BARRIER_5,
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0}
};

inline lw_character iku =
{
    {
        focus_shot,
        focus_shot,
        focus_shot,
        focus_shot,
        focus_shot,
        focus_shot,
        focus_shot
    },
    100,
    ELEMENT_MOON,
    ELEMENT_ALL & ~ELEMENT_MOON,
    {
        0,
        1500000,
        1500,
        2700,
        800,
        3100,
        1400
    },
    RACE_YOUKAI,
    HEALTHY_BARRIER_7,
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0}
};

static inline lw_character witch_moon =
{
    {
        focus_shot,
        focus_shot,
        focus_shot,
        focus_shot,
        focus_shot,
        focus_shot,
        focus_shot
    },
    100,
    ELEMENT_EARTH,
    ELEMENT_NONE,
    {
        0,
        2500000,
        1500,
        1800,
        2000,
        1800,
        2000
    },
    RACE_YOUKAI,
    HEALTHY_BARRIER_7,
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0}
};

static inline const lw_character witch =
{
    {
        focus_shot,
        focus_shot,
        focus_shot,
        focus_shot,
        focus_shot,
        focus_shot,
        focus_shot
    },
    100,
    ELEMENT_WOOD,
    ELEMENT_SUN | ELEMENT_MOON | ELEMENT_STAR,
    {
        0,
        133200,
        1500,
        1800,
        766,// from jp wiki -- 900, // Empirical as well, not 100% reliable yang def
        1800,
        800// from jp wiki -- 1000 // Deduced from experimentation (between 915 and 1012) yin def
    },
    RACE_YOUKAI | RACE_GENSOKYO | RACE_MAGICIAN,
    HEALTHY_BARRIER_7,
    { 0, 0, 0, 0, 0, 0, 0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 8, 0, 8, 0, 0, 0, 0, 0, 3, 3},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 10, 0, 10, 0, 0, 0, 0, 0, 3, 3}
};
}

#endif /* data_h */
