#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "story.h"
#include "mechanics.h"
#include "items.h"
#include "abilities.h"
#include "npc.h"
#include "utils.h"
#include "save.h"
#include "menu.h"
#include "fights.h"
#include "dialogue.h"
#include <unistd.h> 

float rank_exp_multiplier(int rank) {
    switch (rank) {
        case E: return 1.0f;
        case D: return 1.2f;
        case C: return 1.5f;
        case B: return 1.9f;
        case A: return 2.4f;
        case S: return 3.0f;
        default: return 1.0f;
    }
}

int exp_reward_for_npc(NPC npc) {
    int lvl = npc.LEVEL > 0 ? npc.LEVEL : 1;
    int base = 5 * (lvl * lvl + 5 * lvl); // not grindy: ~30 exp at level 1
    int reward = (int)(base * rank_exp_multiplier(npc.RANK));
    if (reward < 10) reward = 10; // floor to keep progress moving
    // Allow manual override if EXP_GIVEN is higher
    if (npc.EXP_GIVEN > reward) {
        reward = npc.EXP_GIVEN;
    }
    return reward;
}

int exp_required_for_next_level(int current_level) {
    int next_level = current_level + 1;
    return 25 * next_level * next_level + 75 * next_level; // gentle early, ramps later
}

Player level_up(Player main_character) {
    // Loop to handle multiple level-ups if a big reward comes in
    while (1) {
        int required_exp = exp_required_for_next_level(main_character.LEVEL);
        if (main_character.EXP < required_exp) {
            break;
        }
        main_character.EXP -= required_exp;
        main_character.LEVEL += 1;

        // Stat growth: steady, not grindy
        main_character.stats.MAX_HP += 2;
        main_character.stats.MAX_MANA += 1;
        main_character.stats.DAMAGE += 1;
        if (main_character.LEVEL % 2 == 0) {
            main_character.stats.SPEED += 1;
        }
        if (main_character.LEVEL % 5 == 0) {
            main_character.stats.MAX_HP += 1;
            main_character.stats.DAMAGE += 1;
            main_character.Skill_Points += 1; // bonus at milestones
        }

        main_character.Skill_Points += 1;

        // Refill resources
        main_character.HP = main_character.stats.MAX_HP * 10;
        main_character.MANA = main_character.stats.MAX_MANA;

        say(0,"Congratulations! You've reached level %d!\n", main_character.LEVEL);
    }
    return main_character;
}

NPC level_up_rival(NPC rival, int target_level) {
    if (target_level <= rival.LEVEL) {
        rival.LEVEL = target_level;
        rival.HP = rival.MAX_HP;
        rival.MANA = rival.MAX_MANA;
        return rival;
    }

    for (int next = rival.LEVEL + 1; next <= target_level; ++next) {
        rival.MAX_HP += 8;       // keep HP growth chunky so rival stays threatening
        rival.MAX_MANA += 6;     // rivals lean on abilities too
        rival.DAMAGE += 2;
        rival.DEFENCE += 1;
        if (next % 2 == 0) {
            rival.SPEED += 1;
        }
        rival.EXP_GIVEN += 5;    // scale rewards with power
    }

    rival.LEVEL = target_level;
    rival.HP = rival.MAX_HP;
    rival.MANA = rival.MAX_MANA;
    return rival;
}

