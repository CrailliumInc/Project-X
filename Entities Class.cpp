    // Begin with general class for entities (player characters and enemies)

/*
 Notes: In order to implement a "difficulty" setting it could be as simple as have a
 general modifier attached to all stats.
 
 */


#include "cmath"


bool firstRun = true;

enum difficultySetting {	EASY = 0, NORMAL, HARD, DIE_DAMN_YOU_DIE	} difficulty;
int difficultyMultiplier[4] = {	0, 1, 2, 4 };
    // difficultySetting = EASY;			// The word 'difficulty' is beginning to look weird.     --> Was causing an error, so I commented it out. Can be reversed at anytime :)
                                    // ... It's also 2:22:33 AM...

const int MAX_CONDITIONS = difficultyMultiplier[(int) difficulty] + 4;

enum status { KNOCKOUT, WOUNDED, BLEEDING, POISON, PARALYSE, STUN, STONE, TERROR, SLEEP, WEAKNESS, SLOW, DULL, DOUBT, FRAIL, HEALTHY, PERFECT, STRENGTH, NUMBLE, WISE, METTLE, FORTITUDE, VALOUROUS, STONEWALL, DRAGON_SOUL, HASTE, BLITZ, ANNIHILATOR, BARRIER};

enum playClass {	Knight, Dragoon, Berzerker, Dark_Knight,
    Rogue, Archer, Ranger, Assassin,
    Mage, Wizard, Sorcerer, Healer	};

enum monstClass {	Dragon, Goblin, Undead_Ske, Undead_Zom, Undead_Shad /*Shade*/	};


void characterInitialization(playClass type, bool isMainChar);		// Less work if all stats predefined and scale with level
void monsterInitialization(monstClass type, bool isBoss, bool isMinBoss);		// As above

class Entity {
public:
    
    Entity(playClass character);
    Entity(Entity& orig);
    
        // Accessors
    int getTotalHP() {return totalHP;}
    int getTotalMP() {return totalMP;}
    int getTotalSP() {return totalSP;}
    int getStr() {return strength;}
    int getDex() {return dexterity;}
    int getInt() {return intelligence;}
    int getWill() {return willpower;}
    int getDura() {return durability;}
    int getEndu() {return endurance;}		// Endurance is temp, change if desired
    int getLevel() {return level;}
    
    status getStatus();			// Can have array of statuses. Max dependant on difficulty
    
        // Mutators
    void setTotalHP();			// All 'set' functions are for the base stat only.
    void setTotalMP();			// Modifiers from the objects will be considered within those
    void setTotalSP();			// objects.
    
    void setTotalHP(int setHP);
    void setTotalMP(int setHP);
    void setTotalSP(int setHP);
    
    void setStr(double setStr);
    void setDex(double setDex);
    void setInt(double setInt);
    void setWill(double setWill);
    void setDura(double setDura);
    void setEndu(double setEndu);
    
    void setStr(int incStr);
    void setDex(int incDex);
    void setInt(int incInt);
    void setWill(int incWill);
    void setDura(int incDura);
    void setEndu(int incEndu);
    
    void levelUp(int& level, double experience, int levelFactor);
    
    void knockout();			// Clear all status conditions and DIE!!1!!!1!!
    void clearStatus();			// Clear all status conditions
    void addStatus(int position, status toAdd);
    void removeStatus(int position, status toRemove);
    
    void characterInitialization(playClass type, bool isMainChar);					// Less work if all stats predefined and scale with level
    void monsterInitialization(monstClass type, bool isBoss, bool isMinBoss);		// As above
    
private:
    int totalHP;
    int totalMP;
    int totalSP;
    int strength;
    int dexterity;
    int intelligence;
    int willpower;
    int durability;
    int endurance;
    int level;
    int levelFactor;
    double base_xp = 50;
    
    status* conditions;
    
    int strengthBase;
    int dexterityBase;
    int intelligenceBase;
    int willpowerBase;
    int durabilityBase;
    int enduranceBase;
    
    bool isBoss;
    bool isMinBoss;
    bool isMainChar;
};



Entity::Entity(playClass character) { // Not sure if this is what you meant by the entity function, but this fixes the error lol on both this line and line 39.
	conditions = new status[MAX_CONDITIONS];
	strength = strengthBase;
	dexterity = dexterityBase;
	intelligence = intelligenceBase;
	willpower = willpowerBase;
	durability = durabilityBase;
	endurance = enduranceBase;
	
	if(firstRun)
		isMainChar = true;
	else isMainChar = false;
	isBoss = false;
	isMinBoss = false;
}

status getStatus() {
    return HEALTHY;    // This one may need to come WAY later in order to have everything just displayed to player rather than do anything here, What I did here was just to remove the error. Until something is developed the character shall remain healthy ;)
}

    // Mutators
void Entity::setTotalHP() {
	int baseHP;
	if(level <= 20)
		baseHP = 2 * level;
	else if(level <= 40)
		baseHP = 4 * level;
	else if(level <= 80)
		baseHP = 8 * level;
	else	baseHP = 10 * level;			// May need to balance baseHP more
	
	if(isMainChar || isMinBoss)
		baseHP *= 1.25;
	else if(isBoss)
		baseHP *= 2.5;
	
	totalHP = (level + durability) * (double) (level / 10 + 1) + baseHP;		// May need to balance HP more in general!
}

void Entity::setTotalMP() {
	int baseMP;
	if(level <= 20)
		baseMP = 2 * level;
	else if(level <= 40)
		baseMP = 4 * level;
	else if(level <= 80)
		baseMP = 8 * level;
	else	baseMP = 10 * level;			// May need to balance baseHP more
	
	if(isMainChar || isMinBoss)
		baseMP *= 1.25;
	else if(isBoss)
		baseMP *= 2.5;
	
	totalMP = (level + intelligence) * (double) (level / 10 + 1) + baseMP;
}

void Entity::setTotalSP() {
	int baseSP;
	if(level <= 20)
		baseSP = 2 * level;
	else if(level <= 40)
		baseSP = 4 * level;
	else if(level <= 80)
		baseSP = 8 * level;
	else	baseSP = 10 * level;
	
	if(isMainChar || isMinBoss)
		baseSP *= 1.25;
	else if(isBoss)
		baseSP *= 2.5;
	
	totalSP = (level + endurance) * (double) (level / 10 + 1) + baseSP;
}

void Entity::setTotalHP(int setHP) {
	totalHP = setHP;
}

void Entity::setTotalMP(int setMP) {
	totalMP = setMP;
}

void Entity::setTotalSP(int setSP) {
	totalSP = setSP;
}

void Entity::setStr(double setStr) {
    strength = setStr;
}

void Entity::setDex(double setDex) {
    dexterity = setDex;
}

void Entity::setInt(double setInt){
    intelligence = setInt;
}

void Entity::setWill(double setWill){
    willpower = setWill;
}

void Entity::setDura(double setDura) {
    durability = setDura;
}

void Entity::setEndu(double setEndu) {
    endurance = setEndu;
}

void Entity::setStr(int incStr) {       // Increment function.
    strength += incStr;
}

void Entity::setDex(int incDex) {      // Increment function.
    dexterity += incDex;
}

void Entity::setInt(int incInt) {       // Increment function.
    intelligence += incInt;
}

void Entity::setWill(int incWill) {     // Increment function.
    willpower += incWill;
}

void Entity::setDura(int incDura) {     // Increment function.
    durability += incDura;
}

void Entity::setEndu(int incEndu) {     // Increment function.
    endurance += incEndu;
}

void Entity::levelUp(int& level, double base_xp, int levelFactor) { // Not sure if we should have a selectable level factor, or just a factor of 2... Did up some samples,
    int nextLevel = level++;
        // Balanced for the first 20 levels based on calculations (with a factor of 2), after that... not sure, never bothered, maybe try an excel sheet using the equation?
    if (base_xp >= base_xp * pow(nextLevel,levelFactor)) {
        level++;
    }
    
}

void Entity::knockout() {
        // blank.clearStatus();         // where blank is the name of the entity passed in I suppose?!? Not sure, this is me making aumptions...
        //blank.kill();                 // Maybe use this "kill()" as the death bringer function :P
}

void Entity::clearStatus() {
    for (int i = 0; i < MAX_CONDITIONS; i++)    // Not sure if this is what you want... but oh wells lol
        conditions[i] = HEALTHY;
}

void Entity::addStatus(int position, status toAdd) {
    conditions[position] = toAdd;                // Dunno if this is right or not, but this is what xcode told me to do... XD You can change if you wish.
}
/*
 KNOCKOUT, WOUNDED, BLEEDING, HEALTHY, PERFECT,
 POISON, PARALYSE, STUN, STONE, TERROR, SLEEP,
 WEAKNESS, SLOW, DULL, DOUBT, FRAIL,
 STRENGTH, NIMBLE, WISE, METTLE, FORTITUDE,
 BERZERK, BLINK, MAGE_EYE, VALOUROUS, STONEWALL,
 DRAGON_SOUL, HASTE, BLITZ, ANNIHILATOR, BARRIER };
 */
void Entity::removeStatus(int position, status toRemove){
    int itemToDelete = 0;
    
    for (int i = 0; i < MAX_CONDITIONS; i++)             // trying something here... dunno how it'll work yet
        if(conditions[i] == toRemove)
            itemToDelete = i;

    
}