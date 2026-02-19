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

Player add_summon(Player main_character, int summonID){
    if (main_character.summons_ammount == main_character.stats.SUMMONS_STORAGE) {
        say(0,"Cannot add more abilities, storage full.\n");
        return main_character;
    }

    for (int i = 0; i < main_character.summons_ammount; i++) {
        if (main_character.summonIDs[i] == summonID) {
            return main_character; // Already present, do nothing
        }
    }
    main_character.summonIDs = realloc(main_character.summonIDs, (main_character.summons_ammount + 1) * sizeof(int));
    main_character.summonIDs[main_character.summons_ammount] = summonID;
    main_character.summons_ammount += 1;
    return main_character;
}

Player remove_summon(Player main_character, int summonID){
    if(not_in(summonID,main_character.summonIDs,main_character.summons_ammount)) {
        say(0,"Summon not found in player's summons.\n");
        return main_character;
    }
    for (int i = 0; i < main_character.summons_ammount; i++) {
        if (main_character.summonIDs[i] == summonID) {
            for (int k = i; k < main_character.summons_ammount - 1; k++) {
                main_character.summonIDs[k] = main_character.summonIDs[k + 1];
            }
            main_character.summons_ammount -= 1;
            main_character.summonIDs = realloc(main_character.summonIDs, main_character.summons_ammount * sizeof(int));
            break;
        }
    }
    main_character.stats.MAGIC_POWER += 10;//If a summoner's summon is destrouyed, they loose the ability to even summon it again, but they also gain a boost
    return main_character;
}

Player add_team_member(Player main_character, int memberID, bool is_summon_member) {
    // Prevent duplicates
    if (is_team_member(main_character, memberID)) {
        return main_character;
    }

    // Enforce summon storage if applicable
    if (is_summon_member && main_character.stats.SUMMONS_STORAGE > 0) {
        int summon_count = 0;
        for (int i = 0; i < main_character.team_size; i++) {
            if (is_summon(main_character.team_memberIDs[i])) {
                summon_count++;
            }
        }
        if (summon_count >= main_character.stats.SUMMONS_STORAGE) {
            say(0,"Summon storage full. Cannot add more summons.\n");
            return main_character;
        }
    }

    int new_size = main_character.team_size + 1;
    int *new_ids = realloc(main_character.team_memberIDs, new_size * sizeof(int));
    int *new_hp = realloc(main_character.team_member_hp, new_size * sizeof(int));
    int *new_mana = realloc(main_character.team_member_mana, new_size * sizeof(int));
    if (!new_ids || !new_hp || !new_mana) {
        free(new_ids);
        free(new_hp);
        free(new_mana);
        return main_character;
    }
    main_character.team_memberIDs = new_ids;
    main_character.team_member_hp = new_hp;
    main_character.team_member_mana = new_mana;
    main_character.team_memberIDs[main_character.team_size] = memberID;
    NPC member = is_summon(memberID) ? get_summon_by_id(memberID) : get_npc_by_id(memberID);
    main_character.team_member_hp[main_character.team_size] = member.HP > 0 ? member.HP : member.MAX_HP;
    main_character.team_member_mana[main_character.team_size] = member.MANA > 0 ? member.MANA : member.MAX_MANA;
    main_character.team_size = new_size;
    return main_character;
}

Player remove_team_member(Player main_character, int memberID, bool is_summon_member) {
    (void)is_summon_member;
    int removed = 0;
    for (int i = 0; i < main_character.team_size; i++) {
        if (main_character.team_memberIDs[i] == memberID) {
            for (int k = i; k < main_character.team_size - 1; k++) {
                main_character.team_memberIDs[k] = main_character.team_memberIDs[k + 1];
                main_character.team_member_hp[k] = main_character.team_member_hp[k + 1];
                main_character.team_member_mana[k] = main_character.team_member_mana[k + 1];
            }
            main_character.team_size -= 1;
            if (main_character.team_size == 0) {
                free(main_character.team_memberIDs);
                free(main_character.team_member_hp);
                free(main_character.team_member_mana);
                main_character.team_memberIDs = NULL;
                main_character.team_member_hp = NULL;
                main_character.team_member_mana = NULL;
            } else {
                int *shrunk = realloc(main_character.team_memberIDs, main_character.team_size * sizeof(int));
                if (shrunk) {
                    main_character.team_memberIDs = shrunk;
                }
                int *shrunk_hp = realloc(main_character.team_member_hp, main_character.team_size * sizeof(int));
                if (shrunk_hp) {
                    main_character.team_member_hp = shrunk_hp;
                }
                int *shrunk_mana = realloc(main_character.team_member_mana, main_character.team_size * sizeof(int));
                if (shrunk_mana) {
                    main_character.team_member_mana = shrunk_mana;
                }
            }
            removed = 1;
            break;
        }
    }
    (void)removed; // silence unused warning if not used later
    return main_character;
}

int is_team_member_summon(Player main_character, int memberID) {
    if(is_team_member(main_character, memberID) && is_summon(memberID)){
        return 1;
    }
    return 0;
}

int is_team_member(Player main_character, int memberID) {
    for (int i = 0; i < main_character.team_size; i++) {
        if (main_character.team_memberIDs[i] == memberID) {
            return 1;
        }
    }
    return 0;
}

int is_summon(int memberID) {
    return memberID >= 100 && memberID < 100 + TOTAL_SUMMONS;
}

void free_team(Player *main_character) {
    if (!main_character) return;
    if (main_character->team_memberIDs) {
        free(main_character->team_memberIDs);
        main_character->team_memberIDs = NULL;
    }
    if (main_character->team_member_hp) {
        free(main_character->team_member_hp);
        main_character->team_member_hp = NULL;
    }
    if (main_character->team_member_mana) {
        free(main_character->team_member_mana);
        main_character->team_member_mana = NULL;
    }
    main_character->team_size = 0;
}

char* team_names(Player main_character) {
    if (main_character.team_size == 0) {
        return strdup("No team members.");
    }
    size_t buffer_size = 256;
    char *buffer = malloc(buffer_size);
    if (!buffer) return NULL;
    buffer[0] = '\0';
    for (int i = 0; i < main_character.team_size; i++) {
        int member_id = main_character.team_memberIDs[i];
        NPC member = get_npc_by_id(member_id);
        const char *name = member.ID >= 0 ? member.name : "Unknown";
        size_t needed = strlen(name) + 3; // for ", " or null terminator
        if (strlen(buffer) + needed >= buffer_size) {
            buffer_size *= 2;
            char *new_buffer = realloc(buffer, buffer_size);
            if (!new_buffer) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }
        strcat(buffer, name);
        if (i < main_character.team_size - 1) {
            strcat(buffer, ", ");
        }
    }
    return buffer;
}

NPC heal_npc(NPC npc, int heal_amount) {
    npc.HP += heal_amount;
    if (npc.HP > npc.MAX_HP) {
        npc.HP = npc.MAX_HP;
    }
    return npc;
}

Player build_team(Player main_character, int* chapter_team_ids, int team_size) {
    if (!chapter_team_ids || team_size <= 0) return main_character;
    for (int i = 0; i < team_size; i++) {
    int memberID = chapter_team_ids[i];
        if (!is_team_member(main_character, memberID)) {
            bool is_summon_member = is_summon(memberID);
            main_character = add_team_member(main_character, memberID, is_summon_member);
        }
    }
    return main_character;
}
