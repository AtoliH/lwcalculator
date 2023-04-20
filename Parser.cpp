//
// Created by Fire937 on 1/8/23.
//

#include "Parser.h"

#include <type_traits>

ModifierContainer Parser::modifiersFromJson(json data) {
    typedef std::variant<
            ModifierType::Stat,
            ModifierType::Element,
            ModifierType::Bullet,
            ModifierType::Effect
    > ModifierTypeVariant;
    // todo these maps will all be static and in a class
    static const std::unordered_map <std::string, ModifierTypeVariant> stringToModifierType = {
            {"yangAtk", ModifierType::YangAttack},
            {"yangDef", ModifierType::YangDefense},
            {"yinAt",   ModifierType::YinAttack},
            {"yinDef",  ModifierType::YinDefense}
    };

    ModifierContainer modifiers;
    for (auto &modifier: data) {
        std::visit([&modifier, &modifiers](auto &&modifierType)
        {
            modifiers.insert(
                    modifierType,
                    Modifier<std::decay_t<decltype(modifierType)>>(
                            modifier.at("value").get<int>(),
                            modifier.at("duration").get<int>(),
                            modifier.at("rate").get<float>(),
                            modifier.at("add").get<int>()
                    ));
        }, stringToModifierType.at(modifier.at("name").get<std::string>()));
    }
}

Attack::Line Parser::lineFromJson(json data) {
    const std::map <std::string, BulletType> stringToBulletType = {
            {"ofuda",   BulletType::Ofuda},
            {"normal",  BulletType::Normal},
            {"energy",  BulletType::Energy},
            {"body",    BulletType::Body},
            {"liquid",  BulletType::Liquid},
            {"light",   BulletType::Light},
            {"laser",   BulletType::Laser},
            {"sharp",   BulletType::Sharp},
            {"heavy",   BulletType::Heavy},
            {"missile", BulletType::Missile},
            {"slash",   BulletType::Slash}
    };
    const std::map <std::string, Element> stringToElement = {
            {"sun",   Element::Sun},
            {"moon",  Element::Moon},
            {"fire",  Element::Fire},
            {"water", Element::Water},
            {"wood",  Element::Wood},
            {"metal", Element::Metal},
            {"earth", Element::Earth},
            {"star",  Element::Star}
    };
    const std::map <std::string, Attack::Line::Tag> stringToLineTag = {
            {"hard",         Attack::Line::Hard},
            {"slicing",      Attack::Line::Slicing},
            {"piercing",     Attack::Line::Piercing},
            {"specular",     Attack::Line::Specular},
            {"elastic",      Attack::Line::Elastic},
            {"precise",      Attack::Line::Precise},
            {"explosive",    Attack::Line::Explosive},
            {"melting",      Attack::Line::Melting},
            {"toxic",        Attack::Line::Toxic},
            {"discharged",   Attack::Line::Discharged},
            {"incineration", Attack::Line::Incineration},
            {"flash",        Attack::Line::Flash}
    };

    // todo Move all json parsing functions to dedicated class and make all maps static
    const std::map <std::string, CharacterTag> stringToCharacterTag = {
            {"gensokyo",         CharacterTag::Gensokyo},
            {"human",            CharacterTag::Human},
            {"magician",         CharacterTag::Magician},
            {"youkai",           CharacterTag::Youkai},
            {"incidentResolver", CharacterTag::IncidentResolver},
            {"tengu",            CharacterTag::Tengu}
    };


    std::set <CharacterTag> killers;
    for (const auto &tag: data.at("killers")) {
        killers.emplace(stringToCharacterTag.at(tag.at("name").get<std::string>()));
    }

    return Attack::Line(
            data.at("power").get<float>(),
            data.at("accuracy").get<float>(),
            data.at("critical").get<float>(),
            data.at("bulletCount").get<float>(),
            (data.at("yinYang").get<std::string>() == "yin") ? Attack::Line::Yin : Attack::Line::Yang,
            stringToBulletType.at(data.at("type").get<std::string>()),
            stringToElement.at(data.at("element").get<std::string>()),
            killers,
            // todo Modifier level has to be deduced from
            modifiersFromJson(data.at("tags").at("levels").at(0).at("effects"))
    );
}

Attack Parser::attackFromJson(json data) {
    const auto &danmaku = data.at("danmakuMultiplier");
    const auto &boost = data.at("boostLayout");

    return Attack(
            {
                    lineFromJson(data.at("line").at(0)),
                    lineFromJson(data.at("line").at(0)),
                    lineFromJson(data.at("line").at(0)),
                    lineFromJson(data.at("line").at(0)),
                    lineFromJson(data.at("line").at(0)),
                    lineFromJson(data.at("line").at(0))
            },
            {danmaku.at(0), danmaku.at(1), danmaku.at(2), danmaku.at(3), danmaku.at(4)},
            {
                    {TurnAction::noBoost,     1},
                    {TurnAction::boostOnce,   boost.at(0).get<int>()},
                    {TurnAction::boostTwice,  boost.at(1).get<int>()},
                    {TurnAction::boostThrice, 6}
            },
            modifiersFromJson(data.at("preEffects")),
            modifiersFromJson(data.at("postEffects"))
    );
}

Character::Skill Parser::skillFromJson(json data) {
    return Character::Skill(data.at("cooldown"), modifiersFromJson(data.at("effects")));
}

Character Parser::characterFromJson(json data) {
    const std::map<int, float> temperamentToMultiplier = {
            {1,    0.5f},
            {2, 1.0f},
            {3,      2.0f}
    };
    const std::map <std::string, CharacterTag> stringToCharacterTag = {
            {"gensokyo",         CharacterTag::Gensokyo},
            {"human",            CharacterTag::Human},
            {"magician",         CharacterTag::Magician},
            {"youkai",           CharacterTag::Youkai},
            {"incidentResolver", CharacterTag::IncidentResolver},
            {"tengu",            CharacterTag::Tengu}
    };

    std::set <CharacterTag> tags;
    for (const auto &tag: data.at("characterTags")) {
        tags.emplace(stringToCharacterTag.at(tag.at("name").get<std::string>()));
    }

    const int firstSkillLevel = data.at("skills").at(0).at("level").get<int>();
    const int secondSkillLevel = data.at("skills").at(1).at("level").get<int>();
    const int thirdSkillLevel = data.at("skills").at(2).at("level").get<int>();
    const Character::Skill firstSkill = skillFromJson(data.at("skills").at(0).at("levels").at(firstSkillLevel));
    const Character::Skill secondSkill = skillFromJson(data.at("skills").at(1).at("levels").at(firstSkillLevel));
    const Character::Skill thirdSkill = skillFromJson(data.at("skills").at(2).at("levels").at(firstSkillLevel));

    return Character(
            data.at("level").get<int>(),
            data.at("awakening").get<int>(),
            {
                    {Character::Stat::Health,      data.at("stats").at("health").get<int>()},
                    {Character::Stat::YangAttack,  data.at("stats").at("yangAtk").get<int>()},
                    {Character::Stat::YinAttack,   data.at("stats").at("yinAtk").get<int>()},
                    {Character::Stat::Agility,     data.at("stats").at("agility").get<int>()},
                    {Character::Stat::YangDefense, data.at("stats").at("yangDef").get<int>()},
                    {Character::Stat::YinDefense,  data.at("stats").at("yinDef").get<int>()},
            },
            {
                    {Element::Sun,   temperamentToMultiplier.at(data.at("sun").get<int>())},
                    {Element::Moon,  temperamentToMultiplier.at(data.at("moon").get<int>())},
                    {Element::Fire,  temperamentToMultiplier.at(data.at("fire").get<int>())},
                    {Element::Water, temperamentToMultiplier.at(data.at("water").get<int>())},
                    {Element::Wood,  temperamentToMultiplier.at(data.at("wood").get<int>())},
                    {Element::Metal, temperamentToMultiplier.at(data.at("metal").get<int>())},
                    {Element::Earth, temperamentToMultiplier.at(data.at("earth").get<int>())},
                    {Element::Star,  temperamentToMultiplier.at(data.at("star").get<int>())},

            },
            {
                    {TurnAction::spreadShot,      attackFromJson(data.at("spreadShot"))},
                    {TurnAction::focusShot,       attackFromJson(data.at("focusShot"))},

                    {TurnAction::firstSpellCard,  attackFromJson(data.at("firstSpellCard"))},
                    {TurnAction::secondSpellCard, attackFromJson(data.at("secondSpellCard"))},
                    {TurnAction::thirdSpellCard,  attackFromJson(data.at("firstSpellCard"))},
                    {TurnAction::fourthSpellCard, attackFromJson(data.at("secondSpellCard"))},
                    {TurnAction::lastWord,        attackFromJson(data.at("lastWord"))},
            },
            {
                    {TurnAction::firstSkill,  firstSkill},
                    {TurnAction::secondSkill, secondSkill},
                    {TurnAction::thirdSkill,  thirdSkill},
            },
            tags
    );
}
