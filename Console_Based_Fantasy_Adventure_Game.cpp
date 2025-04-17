#include <iostream>
#include <string>
using namespace std;

enum ItemType
{
    WEAPON,
    ARMOUR,
    POTION,
    MISC
};

enum EnemyType
{
    GOBLIN,
    TROLL,
    DRAGON,
    SKELETON
};

enum TerrainType
{
    FOREST,
    CAVE,
    MOUNTAIN,
    VILLAGE
};

struct Item
{
    string name;
    ItemType item;
    int value;
    double weight;

    void describeItem()
    {
        cout << "\n  * Name: " << name;
        cout << "\n  * Value: " << value << " gold";
        cout << "\n  * Weight: " << weight << " kg";
        cout << "\n  * Type: ";
        switch (item)
        {
        case WEAPON:
            cout << "Weapon";
            break;
        case ARMOUR:
            cout << "Armour";
            break;
        case POTION:
            cout << "Potion";
            break;
        case MISC:
            cout << "Misc";
            break;
        default:
            cout << "Not Exists...";
            break;
        }
    }
};

struct Enemy
{
    string name;
    EnemyType type;
    int health;
    int attackPower;
    int defensePower;

    void attackEnemy(Enemy *enemy)
    {
        int damage = 0;
        damage = attackPower - enemy->defensePower;
        if (damage < 1)
        {
            damage = 1;
        }
        enemy->health -= damage;
        if (enemy->health < 0)
        {
            enemy->health = 0;
        }
    }
};

struct Character
{
    string name;
    int level;
    int experience;
    int health;
    int attackPower;
    int defensePower;
    int inventorySize = 3;
    Item **inventory;

    Character(string n, int l, int exp, int hp, int att, int def, int inventsize)
    {
        name = n;
        level = l;
        experience = exp;
        health = hp;
        attackPower = att;
        defensePower = def;
        inventorySize = inventsize;
        inventory = new Item *[inventorySize];
        for (int i = 0; i < inventorySize; i++)
        {
            inventory[i] = nullptr;
        }
    }

    void gainExperience(int exp)
    {
        if (exp < 0)
        {
            cout << "\n  *** Invalid Input... ***\n";
            return;
        }
        experience += exp;
        if (experience > 50)
        {
            level += 1;
            experience = 0;
            cout << "\n  *** Level Up! " << name << " is now Level " << level << "! ***\n";
        }
    }

    void useItem(Item *item)
    {
        if (item == nullptr)
        {
            cout << "\n  *** Invalid Input... ***\n";
            return;
        }

        bool itemFound = false;
        for (int i = 0; i < inventorySize; i++)
        {
            if (inventory[i] == item)
            {
                itemFound = true;

                switch (item->item)
                {
                case ItemType::POTION:

                    health += 50;
                    cout << "\n  *** Used " << item->name << ". Health restored by 50! ***\n";
                    break;
                case ItemType::WEAPON:
                    attackPower += 10;
                    cout << "\n  *** Equipped " << item->name << ". Attack power increased by 10! ***\n";
                    break;
                case ItemType::ARMOUR:
                    defensePower += 10;
                    cout << "\n  *** Equipped " << item->name << ". Defense power increased by 10! ***\n";
                    break;
                case ItemType::MISC:
                    cout << "\n  *** Used " << item->name << ". No changes. ***\n";
                    break;
                }

                if (item->item == ItemType::POTION)
                {
                    delete inventory[i];
                    for (int j = i; j < inventorySize - 1; j++)
                    {
                        inventory[j] = inventory[j + 1];
                    }
                    inventory[inventorySize - 1] = nullptr;
                    inventorySize--;
                }

                break;
            }
        }

        if (!itemFound)
        {
            cout << "Item not found in inventory!" << endl;
        }
    }

    void displayCharacterInfo()
    {
        cout << "\n=====================================\n";
        cout << "       PLAYER'S INFO       \n";
        cout << "=====================================\n";
        cout << "  Name: " << name << "\n";
        cout << "  Level: " << level << "\n";
        cout << "  Experience: " << experience << " / 50\n";
        cout << "  Health: " << health << " HP\n";
        cout << "  Attack Power: " << attackPower << "\n";
        cout << "  Defense Power: " << defensePower << "\n";
        cout << "\n  --- Inventory ---\n";
        for (int i = 0; i < inventorySize; i++)
        {
            if (inventory[i] != nullptr)
            {
                cout << "  Item " << i + 1 << ":";
                inventory[i]->describeItem();
                cout << endl;
            }
            else
            {
                cout << "  Item " << i + 1 << ": Empty\n";
            }
        }
        cout << "=====================================\n";
    }

    ~Character()
    {
        for (int i = 0; i < inventorySize; i++)
        {
            delete inventory[i];
        }
        delete[] inventory;
    }
};

struct Terrain
{
    string name;
    TerrainType type;
    Enemy *enemies[10];
    int numEnemies;
    Item *items[10];
    int numItems;

    Terrain(string n, TerrainType t)
    {
        name = n;
        type = t;
        numEnemies = 0;
        numItems = 0;
    }

    bool addEnemy(Enemy *enemy)
    {
        if (numEnemies >= 10)
        {
            cout << "\n  *** No more enemies can be added... ***\n";
            return false;
        }

        enemies[numEnemies++] = enemy;
        return true;
    }

    bool addItem(Item *item)
    {
        if (numItems >= 10)
        {
            cout << "\n  *** No more items can be added... ***\n";
            return false;
        }

        items[numItems++] = item;
        return true;
    }

    void displayTerrainInfo()
    {
        cout << "\n  +---------------------------+\n";
        cout << "  | Terrain: " << name << "\n";
        cout << "  +---------------------------+\n";
        cout << "  Type: ";
        switch (type)
        {
        case FOREST:
            cout << "Forest";
            break;
        case CAVE:
            cout << "Cave";
            break;
        case MOUNTAIN:
            cout << "Mountain";
            break;
        case VILLAGE:
            cout << "Village";
            break;
        default:
            cout << "Unknown";
            break;
        }

        cout << "\n  --- Enemies (" << numEnemies << ") ---\n";
        for (int i = 0; i < numEnemies; i++)
        {
            cout << "  " << i + 1 << ". " << enemies[i]->name << " (Health: " << enemies[i]->health << ")\n";
        }
        cout << "  --- Items (" << numItems << ") ---\n";
        for (int i = 0; i < numItems; i++)
        {
            if (items[i] != nullptr)
            {
                cout << "  " << i + 1 << ". " << items[i]->name << "\n";
            }
        }
        cout << "  +---------------------------+\n";
    }
};

struct Area
{
    string name;
    Terrain *terrain;
    Area *connectedAreas[4];
    int numConnectedAreas;

    Area(string n, Terrain *p) : name(n), terrain(p)
    {
        numConnectedAreas = 0;
        for (int i = 0; i < 4; i++)
        {
            connectedAreas[i] = nullptr;
        }
    }

    bool addConnectedArea(Area *area)
    {
        if (numConnectedAreas == 4)
        {
            cout << "\n  *** No more areas can be connected... ***\n";
            return false;
        }
        connectedAreas[numConnectedAreas++] = area;
        return true;
    }

    void displayAreaInfo()
    {
        cout << "\n========================================\n";
        cout << "      " << name << "\n";
        cout << "========================================\n";
        if (terrain != nullptr)
        {
            terrain->displayTerrainInfo();
        }
        else
        {
            cout << "  Terrain: None\n";
        }
        cout << "\n  --- Paths to Adventure (" << numConnectedAreas << ") ---\n";
        for (int i = 0; i < numConnectedAreas; i++)
        {
            if (connectedAreas[i] != nullptr)
            {
                cout << "  " << i + 1 << ". " << connectedAreas[i]->name << "\n";
            }
        }
        cout << "========================================\n";
    }
};

struct GameWorld
{
    Area **areas;
    int capacity;
    int numAreas;

    GameWorld(int cap) : capacity(cap)
    {
        numAreas = 0;
        areas = new Area *[capacity];
        for (int i = 0; i < capacity; i++)
        {
            areas[i] = nullptr;
        }
    }

    bool addArea(Area *area)
    {
        if (numAreas >= capacity)
        {
            cout << "\n  *** World is full! Cannot add more areas (Capacity: " << capacity << ") ***\n";
            return false;
        }
        areas[numAreas++] = area;
        return true;
    }

    void displayWorldInfo()
    {
        cout << "\n========================================\n";
        cout << "       THE GAME WORLD       \n";
        cout << "========================================\n";
        cout << "  Total Areas Explored: " << numAreas << "\n";
        for (int i = 0; i < numAreas; i++)
        {
            if (areas[i] != nullptr)
            {
                cout << "\n  --- Region " << i + 1 << " ---\n";
                areas[i]->displayAreaInfo();
            }
        }
        cout << "========================================\n";
    }

    ~GameWorld()
    {
        for (int i = 0; i < numAreas; i++)
        {
            delete areas[i];
        }

        delete[] areas;
    }
};

int main()
{

    // Create the game world
    GameWorld *world = new GameWorld(5);

    // Create terrains
    Terrain *forest = new Terrain("Dark Forest", FOREST);
    Terrain *cave = new Terrain("Dragon Cave", CAVE);
    Terrain *mountain = new Terrain("Snowy Mountain", MOUNTAIN);
    Terrain *village = new Terrain("Village", VILLAGE);

    // Create enemies
    Enemy *goblin = new Enemy{"Goblin", GOBLIN, 100, 50, 30};
    Enemy *troll = new Enemy{"Cave Troll", TROLL, 100, 60, 50};
    Enemy *dragon = new Enemy{"Ancient Dragon", DRAGON, 100, 85, 70};
    Enemy *skeleton = new Enemy{"Skeleton", SKELETON, 100, 10, 3};

    // Add enemies to terrains
    forest->addEnemy(goblin);
    cave->addEnemy(troll);
    mountain->addEnemy(skeleton);
    village->addEnemy(dragon);

    // Create items
    Item *sword = new Item{"Sword", WEAPON, 50, 5.5};
    Item *shield = new Item{"Shield", ARMOUR, 40, 3.0};
    Item *potion = new Item{"Health Potion (1 - Time use)", POTION, 20, 0.5};
    Item *herb = new Item{"Medicinal Herb", MISC, 10, 0.2};

    // Add items to terrains
    forest->addItem(sword);
    forest->addItem(herb);
    cave->addItem(shield);
    mountain->addItem(shield);
    village->addItem(potion);

    // Create areas
    Area *forestArea = new Area("Forest Woodland", forest);
    Area *caveArea = new Area("Cave (Mouth of death)", cave);
    Area *mountainArea = new Area("Mountain Peak", mountain);
    Area *villageArea = new Area("Village Square", village);

    // Connect areas
    forestArea->addConnectedArea(caveArea);
    forestArea->addConnectedArea(villageArea);
    caveArea->addConnectedArea(forestArea);
    caveArea->addConnectedArea(mountainArea);
    mountainArea->addConnectedArea(caveArea);
    villageArea->addConnectedArea(forestArea);

    // Add areas to the world
    world->addArea(forestArea);
    world->addArea(caveArea);
    world->addArea(mountainArea);
    world->addArea(villageArea);

    // Character Setup
    cout << "\n========================================\n";
    cout << "     FANTASY ADVENTURE QUEST     \n";
    cout << "========================================\n";
    string name;
    cout << "  Enter your hero's name: ";
    getline(cin, name);

    Character player(name, 1, 0, 100, 60, 40, 3);

    int areaChoice;
    Item item;
    Area *currentArea;
    bool x = true;
    while (x)
    {
        cout << "\n  Where will your journey begin?\n";
        cout << "  1. Forest Woodland\n";
        cout << "  2. Village Square\n";
        cout << "  Choose your path (1-2): ";
        cin >> areaChoice;
        switch (areaChoice)
        {
        case 1:
            currentArea = forestArea;
            x = false;
            break;
        case 2:
            currentArea = villageArea;
            x = false;
            break;
        default:
            cout << "\n  *** Invalid Choice! Choose again... ***\n";
            break;
        }
    }

    cout << "\n========================================\n";
    cout << "       CHOOSE YOUR ITEM       \n";
    cout << "========================================\n";
    cout << "  Your Inventory holds 3 items. Choose wisely:\n";
    cout << "  1. Sword\n";
    cout << "  2. Shield\n";
    cout << "  3. Health Potion\n";
    cout << "  4. Medicinal Herb\n";
    int items[3];
    for (int i = 0; i < player.inventorySize; i++)
    {
        cout << "Pick Item " << i + 1 << " : ";
        cin >> items[i];
        while (items[i] < 1 || items[i] > 4)
        {
            cout << "\n  *** Invalid Input! Choose again... ***\n";
            cout << "  Pick Item " << i + 1 << " (1-4): ";
            cin >> items[i];
        }
        int j = 0;
        while (j < i)
        {
            if (items[j] == items[i])
            {
                cout << "\n  *** Already Chosen! Pick again... ***\n";
                cout << "  Pick Item " << i + 1 << " (1-4): ";
                cin >> items[i];
                j = 0;
            }
            else
            {
                j++;
            }
        }

        switch (items[i])
        {
        case 1:
            player.inventory[i] = sword;
            break;
        case 2:
            player.inventory[i] = shield;
            break;
        case 3:
            player.inventory[i] = potion;
            break;
        case 4:
            player.inventory[i] = herb;
            break;
        default:
            break;
        }
    }

    int damage = 0;
    bool gameRunning = true;
    Enemy *enemy;
    bool c;
    while (gameRunning)
    {
        system("cls");
        // cout << "\n========================================\n";
        // cout << "     " << currentArea->name << "     \n";
        // cout << "========================================\n";
        currentArea->displayAreaInfo();
        player.displayCharacterInfo();
        cout << "\n  --- What will you do? ---\n";
        cout << "  1. Move in a new land\n";
        cout << "  2. Face the enemy\n";
        cout << "  3. Use an item\n";
        cout << "  4. End your journey\n";
        cout << "  Your choice (1-4): ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            cout << "\n========================================\n";
            cout << "       PATHS OF DESTINY       \n";
            cout << "========================================\n";
            for (int i = 0; i < currentArea->numConnectedAreas; i++)
            {
                cout << i + 1 << ". " << currentArea->connectedAreas[i]->name << endl;
            }
            int n;
            cout << "Enter Area number to move in: ";
            cin >> n;
            while (n < 1 || n > currentArea->numConnectedAreas)
            {
                cout << "Invalid Input...\nEnter Area number again to move in: ";
                cin >> n;
            }
            currentArea = currentArea->connectedAreas[n - 1];
            break;
        case 2:
            system("cls");
            if (currentArea->terrain->numEnemies == 0)
            {
                cout << "\n========================================\n";
                cout << "       PEACEFUL LANDS       \n";
                cout << "========================================\n";
                cout << "No enemies here!\n";
                system("pause");
                continue;
            }
            enemy = currentArea->terrain->enemies[0];
            cout << "\n========================================\n";
            cout << "       BATTLE BEGINS       \n";
            cout << "========================================\n";
            cout << "  You face the " << enemy->name << "!\n";
            c = true;
            while (enemy->health > 0 && player.health > 0 && c)
            {
                cout << "\n  ---------------------------\n";
                cout << "  Enemy Health: " << enemy->health << "\n";
                cout << "  Your Health: " << player.health << "\n";
                cout << "  ---------------------------\n";
                cout << "  1. Strike with enemy\n";
                cout << "  2. Use an item\n";
                cout << "  3. Flee the fight\n";
                cout << "  Your action (1-3): ";
                int action;
                cin >> action;
                switch (action)
                {
                case 1:
                    damage = player.attackPower - enemy->defensePower;
                    if (damage < 1)
                    {
                        damage = 1;
                    }
                    enemy->health -= damage;
                    if (enemy->health <= 0)
                    {
                        cout << "\n  *** Victory! The " << enemy->name << " falls! Gained 20 XP ***\n";
                        player.gainExperience(20);
                        c = false;
                        system("pause");
                    }
                    damage = enemy->attackPower - player.defensePower;
                    if (damage < 1)
                    {
                        damage = 1;
                    }
                    player.health -= damage;
                    if (player.health <= 0)
                    {
                        cout << "\n  *** Defeat! Darkness claims you... ***\n";
                        delete world;
                        return 0;
                    }
                    system("cls");
                    break;
                case 2:
                    player.displayCharacterInfo();
                    int itemNum;
                    cout << "Item use (1 - 3): ";
                    cin >> itemNum;
                    while (itemNum < 1 || itemNum > 3)
                    {
                        cout << "\n  *** Invalid Item! ***\n";
                        cout << "Enter Item number again to choose: ";
                        cin >> itemNum;
                    }
                    player.useItem(player.inventory[itemNum - 1]);
                    system("pause");
                    system("cls");
                    break;
                case 3:
                    cout << "\nRan away!\n";
                    c = false;
                    break;

                default:
                    cout << "\n  *** Invalid Action! The enemy waits... ***\n";
                    system("pause");
                    break;
                }
            }
            break;
        case 3:
            system("cls");
            cout << "\n========================================\n";
            cout << "       YOUR INVENTORY       \n";
            cout << "========================================\n";
            player.displayCharacterInfo();
            int itemNum;
            cout << "Item use (1 - 3): ";
            cin >> itemNum;
            while (itemNum < 1 || itemNum > 3)
            {
                cout << "\n  *** Invalid Item! ***\n";
                cout << "Enter Item number again to choose: ";
                cin >> itemNum;
            }
            player.useItem(player.inventory[itemNum - 1]);
            break;
        case 4:
            cout << "\n========================================\n";
            cout << "       JOURNEY'S END       \n";
            cout << "========================================\n";
            cout << "  Farewell, brave " << player.name << "! Thanks for playing!\n";
            gameRunning = false;
            break;
        default:
            cout << "\n  *** Invalid Choice! ***\n";
            system("pause");
            break;
        }
    }
    delete world;
    return 0;
}
