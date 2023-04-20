//
// Created by Fire937 on 1/8/23.
//

#ifndef LWCALCULATOR_PARSER_H
#define LWCALCULATOR_PARSER_H

#include <lwlib/Attack.hpp>
#include <lwlib/Modifier.hpp>
#include <nlohmann/json.hpp>
#include <lwlib/Character.hpp>

using json = nlohmann::json;

class Parser {
    static ModifierContainer modifiersFromJson(json data);

    /**
     * Use json data to build the corresponding attack line
     * @param data
     * @return
     */
    static Attack::Line lineFromJson(json data);

    /**
     * Use json data to build the corresponding attack (spell card or shot)
     * @param data
     * @return
     */
    static Attack attackFromJson(json data);

    /**
     * Use json data to build the corresponding character skill
     * @param data
     * @return
     */
    static Character::Skill skillFromJson(json data);

public:
    static Character characterFromJson(json data);
};


#endif //LWCALCULATOR_PARSER_H
