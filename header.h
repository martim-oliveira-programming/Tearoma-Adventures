#ifndef HEADER_H
#define HEADER_H
 
#define MAX_INPUT 20

typedef enum{
    QUIT = -1,
    MENU,
    PLAYING,
    //PAUSE,
    //MISSION_SELECTION
}GameState;

typedef enum{
    ASSASSIN,
    TANK,
    MONK,
    NINJA,
    MAGE,
    HEALER,
    SUMMONER,
    BALANCED,
}Builds;

typedef enum{
    Character_Creation,
    Chapter_1,
    Chapter_2,
    Chapter_3,
    Chapter_4,
    Chapter_5,
}Chapters;

typedef struct story{
    int Chapter;
    int Path;
}Story;

typedef struct initial_build_attributes{
    char *MOUNT;
    int armor_points;
    int MAX_HP;
    int MAX_MANA;
    int MAGIC_POWER;
    int WEAPON_DAMAGE;
    int DAMAGE;
    int SPEED;
    int STEALTH;
    int DUAL_WILDING;
}Attributes;

typedef struct player {
    // Basic info
    char *name;
    char *eye_colour;
    char *hair_colour;
    int age;
    
    // Game attributes
    char *build;
    char **abilities;
    char **items;
    char armor[4][20];  // Array for armor slots (helm, chest, legs, boots)
    char *weapon;
    char *weapon_OFF_Hand;
    char RANK;
    int LEVEL;
    int EXP;
    int HP;
    int MANA;
    int GOODNESS;
    Attributes stats;  // Contains all build-specific attributes
} Player;




typedef struct other_characters{
    char *name;
    char **abilities;
    char RANK;
    char *MOUNT;
    int LEVEL;
    int EXP;
    int HP;
    int MAX_HP;
    int DAMAGE;
    int SPEED;
}NPC;

char* get_input(char* input);

//Save Functions
void save_game(Story story,Player player,NPC* chapter_NPCs);
int load_save(Story *story, Player *player, NPC *chapter_NPCs);
void secure_wipe();
int file_exists(const char* filename);

//Menu Functions
int menu_selection();
int NewGame();
int Continue();
int QuitGame();

//Build Character Functions
Player character_creation();
void get_attributes(Player *main_character);

#endif
