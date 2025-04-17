#include <iostream>
#include <string>
using namespace std;


void displayInstructions()
{
    cout << "========================================\n";
    cout << "           WELCOME TO THE GAME          \n";
    cout << "========================================\n";
    cout << "Game Rules:\n";
    cout << "1. Two players will take turns to move and attack.\n";
    cout << "2. Each player can place up to 10 units on the map.\n";
    cout << "3. Each unit has health, attack, defense, and movement range.\n";
    cout << "4. To win, eliminate all of your opponent's units.\n";
    cout << "5. Units can move within their movement range and attack enemy units.\n";
    cout << "6. Attack damage is calculated as: attack - defense (minimum 1 damage).\n";
    cout << "7. Units cannot move outside the map or onto occupied spaces.\n";
    cout << "\nHow to Play:\n";
    cout << "1. Enter the names of Player 1 and Player 2.\n";
    cout << "2. Each player will place their units on the map by specifying their positions.\n";
    cout << "3. During your turn, you can either:\n";
    cout << "   - Move a unit (enter new position).\n";
    cout << "   - Attack an enemy unit (select target position).\n";
    cout << "   - End your turn.\n";
    cout << "4. The game continues until one player has no units left.\n";

    system("pause");
    system("cls"); 
}

struct Position
{
    int x, y;
    void display()
    {
        cout << "( " << x << " , " << y << " )";
    }
};

struct Unit
{
    char unit_type;
    int health, attack, defense, movementRange;
    Position position;

    Unit()
    {
        unit_type = ' ';
        health = 0;
        attack = 0;
        defense = 0;
        movementRange = 0;
        position = {0, 0};
    }

    Unit(char unit, int hp, int attk, int def, int moveR, int x, int y)
    {
        unit_type = unit;
        health = hp;
        attack = attk;
        defense = def;
        movementRange = moveR;
        position = {x, y};
    }

    void moveunit(int newX, int newY)
    {
        position.x = newX;
        position.y = newY;
    }

    bool isAlive()
    {
        return health > 0;
    }

    void attackUnit(Unit *enemyUnit)
    {
        int damage = attack - enemyUnit->defense;
        if (damage < 1)
            damage = 1; 
        enemyUnit->health -= damage;
        if (enemyUnit->health < 0)
            enemyUnit->health = 0; 
    }

    void displayInfo()
    {
        cout << "\nName: " << unit_type
             << "\nHealth: " << health
             << "\nAttack: " << attack
             << "\nDefense: " << defense
             << "\nMovement Range: " << movementRange
             << "\nAt Position: ";
        position.display();
        cout << endl;
    }
};

struct Map
{
    int rows, cols;
    char **ptr;

    Map()
    {
        rows = 5;
        cols = 10;
        ptr = new char *[rows];
        for (int i = 0; i < rows; i++)
        {
            ptr[i] = new char[cols];
        }
    }

    void initializeMap()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                ptr[i][j] = ' ';
            }
        }
    }

    bool addUnitToMap(Unit *unit, int x, int y)
    {
        if ((x >= 0 && x < rows) && (y >= 0 && y < cols))
        {
            if (ptr[x][y] == ' ')
            {
                ptr[x][y] = unit->unit_type;
                return true;
            }
            else
            {
                cout << "Position (" << x << ", " << y << ") is already occupied. Choose another.\n";
                return false;
            }
        }
        else
        {
            cout << "Invalid position in Map...\n";
            return false;
        }
    }

    bool removeUnitFromMap(int x, int y)
    {
        if ((x >= 0 && x < rows) && (y >= 0 && y < cols))
        {
            if (ptr[x][y] != ' ')
            {
                ptr[x][y] = ' ';
                return true;
            }
            else
            {
                cout << "Position (" << x << ", " << y << ") is already empty. Choose another.\n";
                return false;
            }
        }
        else
        {
            cout << "Invalid position in Map...\n";
            return false;
        }
    }

    void displayMap()
    {
        system("pause");
        system("cls");
        cout << "========================================\n";
        cout << "              GAME BOARD               \n";
        cout << "========================================\n";
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << "| " << ptr[i][j] << " ";
            }
            cout << "|\n";
            cout << "----------------------------------------\n";
        }
    }

    ~Map()
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] ptr[i];
        }
        delete[] ptr;
        ptr = nullptr;
    }
};

struct Player
{
    string player_name;
    Unit **units;
    int capacity;
    int unitcount;

    Player(string name)
    {
        capacity = 5;
        units = new Unit *[capacity];
        player_name = name;
        unitcount = 0;
        for (int i = 0; i < capacity; i++)
        {
            units[i] = NULL;
        }
    }

    void addUnit(Unit *newUnit)
    {
        if (unitcount == capacity)
        {
            cout << "Can't add more units. Maximum limit reached!!!\n";
            return;
        }
        units[unitcount++] = newUnit;
    }

    bool isUnitNameUnique(char unit_name)
    {
        for (int i = 0; i < unitcount; i++)
        {
            if (units[i]->unit_type == unit_name)
            {
                return false; 
            }
        }
        return true; 
    }

    bool isAttackDefenseMovementUnique(int attack, int defense, int movementRange)
    {
        for (int i = 0; i < unitcount; i++)
        {
            if (units[i]->attack == attack || units[i]->defense == defense || units[i]->movementRange == movementRange)
            {
                return false; 
            }
        }
        return true; 
    }

    void displayUnits()
    {
        if (unitcount == 0)
        {
            cout << "No units in Player " << player_name << " units...\n";
            return;
        }
        cout << "========================================\n";
        cout << "Units in Player " << player_name << " are: \n";
        for (int i = 0; i < unitcount; i++)
        {
            units[i]->displayInfo();
            cout << "----------------------------------------\n";
        }
    }

    ~Player()
    {
        for (int i = 0; i < unitcount; i++)
        {
            delete units[i];
        }
        delete[] units;
        units = nullptr;
    }
};

struct Game
{
    Player *player1;
    Player *player2;
    Map gameMap;
    int currentPlayer = 1;

    Game(string p1, string p2)
    {
        player1 = new Player(p1);
        player2 = new Player(p2);
        gameMap.initializeMap();
    }

    void nextTurn()
    {
        currentPlayer = currentPlayer == 1 ? 2 : 1;
    }

    void performAction(int x, int y, int newX, int newY)
    {
        Unit *selectedUnit = nullptr;
        Player *current = (currentPlayer == 1) ? player1 : player2;
        int i = 0;
        while (i < current->unitcount && selectedUnit == nullptr)
        {
            if (current->units[i]->position.x == x && current->units[i]->position.y == y)
            {
                selectedUnit = current->units[i];
            }
            i++;
        }

        if (selectedUnit == nullptr)
        {
            cout << "No unit found at the given position.\n";
            return;
        }

        int dx = (newX > x) ? (newX - x) : (x - newX);
        int dy = (newY > y) ? (newY - y) : (y - newY);

        if (dx > selectedUnit->movementRange || dy > selectedUnit->movementRange)
        {
            cout << "Move out of range! Maximum movement range is " << selectedUnit->movementRange << ".\n";
            return;
        }

        if (newX < 0 || newX >= gameMap.rows || newY < 0 || newY >= gameMap.cols)
        {
            cout << "Invalid position! Cannot move outside the board.\n";
            return;
        }

        if (gameMap.ptr[newX][newY] != ' ')
        {
            cout << "Position (" << newX << ", " << newY << ") is already occupied. Choose another.\n";
            return;
        }

        gameMap.removeUnitFromMap(x, y);
        selectedUnit->moveunit(newX, newY);
        gameMap.addUnitToMap(selectedUnit, newX, newY);
    }

    bool checkVictory()
    {
        bool p1Alive = false, p2Alive = false;
        for (int i = 0; i < player1->unitcount; i++)
        {
            if (player1->units[i]->isAlive())
                p1Alive = true;
        }
        for (int i = 0; i < player2->unitcount; i++)
        {
            if (player2->units[i]->isAlive())
                p2Alive = true;
        }

        if (!p1Alive || !p2Alive)
        {
            gameMap.displayMap();
            cout << "\n========================================\n";
            cout << "           FINAL UNIT DETAILS           \n";
            cout << "========================================\n";
            player1->displayUnits();
            player2->displayUnits();

            if (!p1Alive)
            {
                cout << player2->player_name << " Wins!\n";
            }
            else
            {
                cout << player1->player_name << " Wins!\n";
            }
            return true;
        }
        return false;
    }

    Player *getCurrentPlayer()
    {
        return (currentPlayer == 1) ? player1 : player2;
    }

    void displayGameState()
    {
        gameMap.displayMap();
        cout << "========================================\n";
        cout << "Current Turn: Player " << currentPlayer << "\n";
        player1->displayUnits();
        player2->displayUnits();
    }

    ~Game()
    {
        delete player1;
        delete player2;
    }
};

void enterUnits(Game &game, Player *player)
{
    char unit_name;
    int num_units;
    int a, d, mr, x, y;
    const int h = 100;

    cout << "You can enter " << game.player1->capacity << " maximum units.\n";
    cout << "Enter number units of Player " << player->player_name << ": ";
    cin >> num_units;

    while (num_units < 0 || num_units > game.player1->capacity)
    {
        cout << "Enter again less than or equal " << game.player1->capacity << " : ";
        cin >> num_units;
    }

    for (int i = 0; i < num_units; i++)
    {
        cout << "Enter name of unit " << i + 1 << " (a single character): ";
        cin >> unit_name;

        // Check if the unit name is unique for the current player
        while (!player->isUnitNameUnique(unit_name))
        {
            cout << "Unit name already exists! Enter a unique name: ";
            cin >> unit_name;
        }

        cout << "Health of unit " << i + 1 << " is 100\n";

        // Input validation for attack, defense, and movement range
        cout << "Enter attack power of unit " << i + 1 << ": ";
        cin >> a;
        while (a < 0 || a > 100 || !player->isAttackDefenseMovementUnique(a, 0, 0))
        {
            cout << "Invalid input or attack value already exists! Enter a unique value between 0 and 100: ";
            cin >> a;
        }

        cout << "Enter defense of unit " << i + 1 << ": ";
        cin >> d;
        while (d < 0 || d > 100 || !player->isAttackDefenseMovementUnique(0, d, 0))
        {
            cout << "Invalid input or defense value already exists! Enter a unique value between 0 and 100: ";
            cin >> d;
        }

        cout << "Enter movement range of unit " << i + 1 << " (1-5): ";
        cin >> mr;
        while (mr < 1 || mr > 5 || !player->isAttackDefenseMovementUnique(0, 0, mr))
        {
            cout << "Invalid input or movement range already exists! Enter a unique value between 1 and 5: ";
            cin >> mr;
        }

        do
        {
            cout << "Enter position (x) of unit " << i + 1 << ": ";
            cin >> x;
            cout << "Enter position (y) of unit " << i + 1 << ": ";
            cin >> y;
        } while (!game.gameMap.addUnitToMap(new Unit(unit_name, h, a, d, mr, x, y), x, y));

        Unit *newUnit = new Unit(unit_name, h, a, d, mr, x, y);
        player->addUnit(newUnit);
        system("cls");
    }
}

int main()
{
    displayInstructions();
    char name1[30];
    char name2[30];
    cout << "Name of player 1: ";
    cin.getline(name1, 30);
    cout << "Name of player 2: ";
    cin.getline(name2, 30);

    Game game(name1, name2);
    enterUnits(game, game.player1);
    enterUnits(game, game.player2);

    int choice;
    while (!game.checkVictory())
    {
        game.displayGameState();
        cout << "\n1. Attack 2. Move Unit 3. End turn\nEnter choice for player " << game.currentPlayer << ": ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int x, y, targetX, targetY;
            cout << "Enter position(x,y) to select your unit: ";
            cin >> x >> y;
            cout << "Enter position(x,y) to attack: ";
            cin >> targetX >> targetY;

            Unit *attacker = nullptr;
            Unit *defender = nullptr;

            Player *current = game.getCurrentPlayer();
            for (int i = 0; i < current->unitcount; i++)
            {
                if (current->units[i]->position.x == x && current->units[i]->position.y == y)
                {
                    attacker = current->units[i];
                }
            }

            Player *opponent = (game.currentPlayer == 1) ? game.player2 : game.player1;
            for (int i = 0; i < opponent->unitcount; i++)
            {
                if (opponent->units[i]->position.x == targetX && opponent->units[i]->position.y == targetY)
                {
                    defender = opponent->units[i];
                }
            }

            if (attacker && defender)
            {

                int dx = (targetX > x) ? (targetX - x) : (x - targetX);
                int dy = (targetY > y) ? (targetY - y) : (y - targetY);


                if (dx > attacker->movementRange || dy > attacker->movementRange)
                {
                    cout << "Target is out of range! Maximum attack range is " << attacker->movementRange << ".\n";
                }
                else
                {
                    attacker->attackUnit(defender);
                    if (!defender->isAlive())
                    {
                        game.gameMap.removeUnitFromMap(defender->position.x, defender->position.y);
                    }
                }
            }
            else
            {
                cout << "Invalid attack position.\n";
            }
            game.nextTurn();
            break;
        }
        case 2:
        {
            int x, y, newX, newY;
            cout << "Enter position(x,y) to select your unit: ";
            cin >> x >> y;
            cout << "Enter new position(x,y): ";
            cin >> newX >> newY;
            game.performAction(x, y, newX, newY);
            game.nextTurn();
            break;
        }
        case 3:
            game.nextTurn();
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }

    return 0;
}