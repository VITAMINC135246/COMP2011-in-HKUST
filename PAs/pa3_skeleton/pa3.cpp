// === Header / Constant ===
// Necessary header files are included
// DO NOT include extra header files
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

const int MAX_STRING_LENGTH = 25;
enum SugarLevel
{
    None = 0,
    Half,
    Standard,
    Extra
};

// === Data structure ===
// Helper Structures for the Database
struct TeaType
{
    char name[MAX_STRING_LENGTH];
    int caffeine;
    TeaType *next;
};

struct MilkType
{
    char name[MAX_STRING_LENGTH];
    int calories;
    int stock;
    MilkType *next;
};

struct ToppingType
{
    char name[MAX_STRING_LENGTH];
    int calories;
    int stock;
    ToppingType *next;
};

struct ToppingListNode
{
    ToppingType *topping;
    ToppingListNode *next;
};

struct ReplacementListNode
{
    MilkType *milk;
    ReplacementListNode *next;
};

// Drink
struct Drink
{
    char name[MAX_STRING_LENGTH];
    int id;
    int price;
    TeaType *tea;
    MilkType *milk;
    ToppingListNode *toppings;
};
// Order
struct Order
{
    int number;
    Drink *drink;
    SugarLevel sugarLevel;
    int calories;
    int caffeine;
    Order *next;
};

// === Initializations ===
void initialize_database(TeaType *&teaTypes, MilkType *&milkTypes, ToppingType *&toppingTypes, const char *path)
{
    ifstream database(path);
    if (!database.is_open())
    {
        cout << "Error: Database file not found" << endl;
        exit(EXIT_FAILURE);
    }

    int numTea = -1, numMilk = -1, numTopping = -1;
    if (!(database >> numTea) || !(database >> numMilk) || !(database >> numTopping))
    {
        cout << "Error: Database file structure failed when inputting numbers" << endl;
        exit(EXIT_FAILURE);
    }
    if (numTea < 0 || numMilk < 0 || numTopping < 0)
    {
        cout << "Error: Database file structure failed when inputting numbers" << endl;
        exit(EXIT_FAILURE);
    }

    if (numTea > 0)
    {
        TeaType *current = new TeaType;
        teaTypes = current;
        if (!(database >> current->name) || !(database >> current->caffeine))
        {
            cout << "Error: Database file structure failed when inputting tea types" << endl;
            exit(EXIT_FAILURE);
        }
        current->next = nullptr;
        for (int i = 1; i < numTea; i++)
        {
            current->next = new TeaType;
            current = current->next;
            if (!(database >> current->name) || !(database >> current->caffeine))
            {
                cout << "Error: Database file structure failed when inputting tea types" << endl;
                exit(EXIT_FAILURE);
            }
            current->next = nullptr;
        }
    }
    else
    {
        teaTypes = nullptr;
    }

    if (numMilk > 0)
    {
        MilkType *current = new MilkType;
        milkTypes = current;
        if (!(database >> current->name) || !(database >> current->calories) || !(database >> current->stock))
        {
            cout << "Error: Database file structure failed when inputting milk types" << endl;
            exit(EXIT_FAILURE);
        }
        current->next = nullptr;
        for (int i = 1; i < numMilk; i++)
        {
            current->next = new MilkType;
            current = current->next;
            if (!(database >> current->name) || !(database >> current->calories) || !(database >> current->stock))
            {
                cout << "Error: Database file structure failed when inputting milk types" << endl;
                exit(EXIT_FAILURE);
            }
            current->next = nullptr;
        }
    }
    else
    {
        milkTypes = nullptr;
    }

    if (numTopping > 0)
    {
        ToppingType *current = new ToppingType;
        toppingTypes = current;
        if (!(database >> current->name) || !(database >> current->calories) || !(database >> current->stock))
        {
            cout << "Error: Database file structure failed when inputting topping types" << endl;
            exit(EXIT_FAILURE);
        }
        current->next = nullptr;
        for (int i = 1; i < numTopping; i++)
        {
            current->next = new ToppingType;
            current = current->next;
            if (!(database >> current->name) || !(database >> current->calories) || !(database >> current->stock))
            {
                cout << "Error: Database file structure failed when inputting topping types" << endl;
                exit(EXIT_FAILURE);
            }
            current->next = nullptr;
        }
    }
    else
    {
        toppingTypes = nullptr;
    }

    TeaType *testCurrent = teaTypes;
    while (testCurrent != nullptr && testCurrent->next != nullptr)
    {
        if (strcmp(testCurrent->name, testCurrent->next->name) >= 0)
        {
            cout << "Warning: Tea types are not sorted in alphabetical order" << endl;
        }
        testCurrent = testCurrent->next;
    }
    MilkType *testCurrentMilk = milkTypes;
    while (testCurrentMilk != nullptr && testCurrentMilk->next != nullptr)
    {
        if (strcmp(testCurrentMilk->name, testCurrentMilk->next->name) >= 0)
        {
            cout << "Warning: Milk types are not sorted in alphabetical order" << endl;
        }
        testCurrentMilk = testCurrentMilk->next;
    }
    ToppingType *testCurrentTopping = toppingTypes;
    while (testCurrentTopping != nullptr && testCurrentTopping->next != nullptr)
    {
        if (strcmp(testCurrentTopping->name, testCurrentTopping->next->name) >= 0)
        {
            cout << "Warning: Topping types are not sorted in alphabetical order" << endl;
        }
        testCurrentTopping = testCurrentTopping->next;
    }

    database.close();
}

void initialize_recipe(TeaType *teaTypes, MilkType *milkTypes, ToppingType *toppingTypes, Drink **&recipes, int &numRecipes, const char *path)
{
    ifstream recipe(path);
    if (!recipe.is_open())
    {
        cout << "Error: Recipe file not found" << endl;
        exit(EXIT_FAILURE);
    }
    if (!(recipe >> numRecipes))
    {
        cout << "Error: Recipe file structure failed when inputting numbers" << endl;
        exit(EXIT_FAILURE);
    }
    if (numRecipes < 0)
    {
        cout << "Error: Recipe file structure failed when inputting numbers" << endl;
        exit(EXIT_FAILURE);
    }
    if (numRecipes == 0)
    {
        recipes = nullptr;
        return;
    }
    recipes = new Drink *[numRecipes];
    for (int i = 0; i < numRecipes; i++)
    {
        recipes[i] = new Drink;
        if (!(recipe >> recipes[i]->name) || !(recipe >> recipes[i]->id) || !(recipe >> recipes[i]->price))
        {
            cout << "Error: Recipe file structure failed when inputting drink information " << i << "" << endl;
            exit(EXIT_FAILURE);
        }
        recipes[i]->tea = nullptr;
        recipes[i]->milk = nullptr;
        recipes[i]->toppings = nullptr;

        char tea[MAX_STRING_LENGTH];
        recipe >> tea;
        for (TeaType *current = teaTypes; current != nullptr; current = current->next)
        {
            if (strcmp(current->name, tea) == 0)
            {
                recipes[i]->tea = current;
                break;
            }
        }
        if (recipes[i]->tea == nullptr)
        {
            cout << "Error: Tea type not found - " << tea << " - when creating recipe No. " << i << "" << endl;
            exit(EXIT_FAILURE);
        }

        char milk[MAX_STRING_LENGTH];
        recipe >> milk;
        for (MilkType *current = milkTypes; current != nullptr; current = current->next)
        {
            if (strcmp(current->name, milk) == 0)
            {
                recipes[i]->milk = current;
                break;
            }
        }
        if (recipes[i]->milk == nullptr)
        {
            cout << "Error: Milk type not found - " << milk << " - when creating recipe No. " << i << "" << endl;
            exit(EXIT_FAILURE);
        }

        int numToppings = -1;
        if (!(recipe >> numToppings) || numToppings < 0)
        {
            cout << "Error: Recipe file structure failed when inputting number of toppings for recipe No. " << i << "" << endl;
            exit(EXIT_FAILURE);
        }
        if (numToppings == 0)
            continue;
        ToppingListNode *current = new ToppingListNode;
        current->topping = nullptr;
        current->next = nullptr;
        recipes[i]->toppings = current;
        char toppingName[MAX_STRING_LENGTH];
        if (!(recipe >> toppingName))
        {
            cout << "Error: Recipe file structure failed when inputting topping information for recipe No. " << i << "" << endl;
            exit(EXIT_FAILURE);
        }
        for (ToppingType *currentTopping = toppingTypes; currentTopping != nullptr; currentTopping = currentTopping->next)
        {
            if (strcmp(currentTopping->name, toppingName) == 0)
            {
                current->topping = currentTopping;
                current->next = nullptr;
                break;
            }
        }
        if (i == 0)
            cout << current->topping->name << endl;
        if (current->topping == nullptr)
        {
            cout << "Error: Topping type not found for recipe No. " << i << "" << endl;
            exit(EXIT_FAILURE);
        }
        for (int j = 1; j < numToppings; j++)
        {
            current->next = new ToppingListNode;
            current = current->next;
            current->topping = nullptr;
            current->next = nullptr;
            if (!(recipe >> toppingName))
            {
                cout << "Error: Recipe file structure failed when inputting topping information for recipe No. " << i << "" << endl;
                exit(EXIT_FAILURE);
            }
            for (ToppingType *currentTopping = toppingTypes; currentTopping != nullptr; currentTopping = currentTopping->next)
            {
                if (strcmp(currentTopping->name, toppingName) == 0)
                {
                    current->topping = currentTopping;
                    current->next = nullptr;
                    break;
                }
            }
            if (current->topping == nullptr)
            {
                cout << "Error: Topping type not found for recipe No. " << i << "" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    recipe.close();

    for (int i = 1; i < numRecipes; i++)
    {
        if (recipes[i]->id <= recipes[i - 1]->id)
        {
            cout << "Warning: Recipe IDs are not in increasing order" << endl;
        }
    }
}

// === Pretty Printing ===
/**
 * function print_ingredients prints the information of the ingredients database
 * @param teaTypes: a linked list of TeaType
 * @param milkTypes: a linked list of MilkType
 * @param toppingTypes: a linked list of ToppingType
 */
void print_ingredients(TeaType *teaTypes, MilkType *milkTypes, ToppingType *toppingTypes)
{
    cout << "===================================" << endl;
    cout << "===    Ingredients Database     ===" << endl;
    cout << "===================================" << endl;

    cout << "  --- Tea Types ---" << endl;
    if (teaTypes == nullptr)
    {
        cout << "    (None)" << endl;
    }
    else
    {
        for (TeaType *current = teaTypes; current != nullptr; current = current->next)
        {
            cout << "    - " << left << setw(MAX_STRING_LENGTH) << current->name
                 << " (Caffeine: " << current->caffeine << "mg)" << endl;
        }
    }
    cout << endl; // Add spacing

    cout << "  --- Milk Types ---" << endl;
    if (milkTypes == nullptr)
    {
        cout << "    (None)" << endl;
    }
    else
    {
        for (MilkType *current = milkTypes; current != nullptr; current = current->next)
        {
            cout << "    - " << left << setw(MAX_STRING_LENGTH) << current->name
                 << " (Calories: " << current->calories << "kcal, Stock: " << current->stock << ")" << endl; // Added stock
        }
    }
    cout << endl; // Add spacing

    cout << "  --- Topping Types ---" << endl;
    if (toppingTypes == nullptr)
    {
        cout << "    (None)" << endl;
    }
    else
    {
        for (ToppingType *current = toppingTypes; current != nullptr; current = current->next)
        {
            cout << "    - " << left << setw(MAX_STRING_LENGTH) << current->name
                 << " (Calories: " << current->calories << "kcal, Stock: " << current->stock << ")" << endl; // Added stock
        }
    }

    cout << "===================================" << endl;
    cout << "=== End of Ingredients Database ===" << endl;
    cout << "===================================" << endl
         << endl; // Add final spacing
}

/**
 * function print_drink prints the information of a drink recipe
 * @param drink: a pointer to the drink to be printed
 */
void print_drink(Drink *drink)
{
    cout << "  ---------------------------------" << endl;
    cout << "  Drink ID:     " << drink->id << endl;
    cout << "  Drink Name:   " << drink->name << endl;
    cout << "  Price:        $" << drink->price << endl; // Added price for completeness
    cout << "  Tea:          " << drink->tea->name << " (Caffeine: " << drink->tea->caffeine << "mg)" << endl;
    cout << "  Milk:         " << drink->milk->name << " (Calories: " << drink->milk->calories << "kcal)" << endl;
    cout << "  Toppings:" << endl;
    if (drink->toppings == nullptr)
    {
        cout << "    - None" << endl;
    }
    else
    {
        ToppingListNode *current = drink->toppings;
        while (current != nullptr)
        {
            cout << "    - " << current->topping->name << " (Calories: " << current->topping->calories << "kcal)" << endl;
            current = current->next;
        }
    }
    cout << "  ---------------------------------" << endl;
}

/**
 * function print_recipe prints the information of a drink recipe
 * @param recipes: a pointer to the dynamic array of drinks
 * @param numRecipes: the number of drinks in the recipe
 *
 */
void print_recipe(Drink **recipes, int numRecipes)
{
    cout << "===================================" << endl;
    cout << "===       Drink Recipes         ===" << endl;
    cout << "===================================" << endl;
    if (numRecipes == 0)
    {
        cout << "  (No recipes available)" << endl;
    }
    else
    {
        for (int i = 0; i < numRecipes; i++)
        {
            print_drink(recipes[i]);
            if (i < numRecipes - 1)
            {
                cout << endl; // Add space between drinks
            }
        }
    }
    cout << "===================================" << endl;
    cout << "===    End of Drink Recipes     ===" << endl;
    cout << "===================================" << endl
         << endl; // Add final spacing
}

/**
 * function print_order prints the information of an order
 * @param order: a pointer to the order to be printed
 * @param isPending: a boolean indicating if the order is pending (true) or completed (false)
 */
void print_order(Order *order, bool isPending = true)
{
    cout << "  *********************************" << endl;
    cout << "  Order Number: " << order->number << endl;
    cout << "  Drink Name:   " << order->drink->name << endl;
    cout << "  Calories:     " << order->calories << "kcal" << endl;
    cout << "  Caffeine:     " << order->caffeine << "mg" << endl;
    cout << "  Sugar Level:  ";
    switch (order->sugarLevel)
    {
    case None:
        cout << "None";
        break;
    case Half:
        cout << "Half";
        break;
    case Standard:
        cout << "Standard";
        break;
    case Extra:
        cout << "Extra";
        break;
    }
    cout << endl;
    cout << "  Ingredients:" << endl;
    cout << "    * Tea:    " << order->drink->tea->name << endl;
    cout << "    * Milk:   " << order->drink->milk->name << endl;
    if (isPending)
    {
        // Only show stock information for pending orders
        cout << "              (Stock: " << order->drink->milk->stock << (order->drink->milk->stock <= 0 ? " - Needs Replacement!" : "") << ")" << endl;
    }
    cout << "    * Toppings:" << endl;
    if (order->drink->toppings == nullptr)
    {
        cout << "      - None" << endl;
    }
    else
    {
        ToppingListNode *current = order->drink->toppings;
        while (current != nullptr)
        {
            cout << "      - " << current->topping->name;
            if (isPending)
            {
                // Only show stock information for pending orders
                cout << " (Stock: " << current->topping->stock << (current->topping->stock <= 0 ? " - Will be Skipped!" : "") << ")";
            }
            cout << endl;
            current = current->next;
        }
    }
    cout << "  *********************************" << endl;
}

/**
 * function print_pending_orders prints the information of the pending order list
 * @param pending: a pointer to the head of the pending order list
 */
void print_pending_orders(Order *pending)
{
    cout << "===================================" << endl;
    cout << "===       Pending Orders        ===" << endl;
    cout << "===================================" << endl;
    if (pending == nullptr)
    {
        cout << "  (No pending orders)" << endl;
    }
    else
    {
        Order *current = pending;
        while (current != nullptr)
        {
            print_order(current, true); // Explicitly stating these are pending orders
            if (current->next != nullptr)
            {
                cout << endl; // Add space between orders
            }
            current = current->next;
        }
    }
    cout << "===================================" << endl;
    cout << "===    End of Pending Orders    ===" << endl;
    cout << "===================================" << endl
         << endl; // Add final spacing
}

/**
 * function print_ready_orders prints the information of the completed order list
 * @param ready: an array of pointers to the head of the completed order list
 */
void print_ready_orders(Order *ready[])
{
    cout << "###################################" << endl;
    cout << "###      Completed Orders       ###" << endl;
    cout << "###################################" << endl;
    bool anyReady = false;
    for (int i = 0; i < 10; i++)
    {
        if (ready[i] != nullptr)
        { // Only print bucket if it has orders
            anyReady = true;
            cout << "--- Orders ending with digit " << i << " ---" << endl;
            Order *current = ready[i];
            while (current != nullptr)
            {
                print_order(current, false); // These are completed orders, so passing false
                if (current->next != nullptr)
                {
                    cout << endl; // Add space between orders within a bucket
                }
                current = current->next;
            }
            cout << "--- End of orders ending with " << i << " ---" << endl
                 << endl;
        }
    }
    if (!anyReady)
    {
        cout << "  (No completed orders)" << endl
             << endl;
    }
    cout << "###################################" << endl;
    cout << "### End of Completed Orders     ###" << endl;
    cout << "###################################" << endl
         << endl; // Add final spacing
}

/**
 * function print_replacement_cycle prints the information of the milk replacement cycle
 * @param replacement: a pointer to the head of the replacement list (can be nullptr)
 */
void print_replacement_cycle(ReplacementListNode *replacement)
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "~~~    Milk Replacements        ~~~" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    if (replacement == nullptr)
    {
        cout << "  (No milk replacements available)" << endl;
    }
    else
    {
        ReplacementListNode *current = replacement;
        cout << "  Start -> ";
        do
        {
            cout << current->milk->name
                 << " (Cal: " << current->milk->calories << ", Stock: " << current->milk->stock << ")";
            current = current->next;
            cout << (current == replacement ? " -- Loop" : " -> "); // Indicate loop or next item
        } while (current != replacement);
        cout << endl;
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "~~~ End of Milk Replacements    ~~~" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
         << endl; // Add final spacing
}

// === Tasks ===
/**
 * function create_recipe creates a new drink recipe with no toppings and adds it to the correct place in the recipes array
 *
 * @param name: the name of the drink
 * @param id: the id of the drink
 * @param price: the price of the drink
 * @param tea: the name of the tea type of the drink
 * @param milk: the name of the milk type of the drink
 * @param teaTypes: an array of pointers to TeaType
 * @param milkTypes: an array of pointers to MilkType
 * @param recipes: a pointer to the dynamic array of recipes
 * @param numRecipes: the number of drinks in the recipe - MISSING in original description
 *
 * @return true if the drink is successfully created and added.
 *         false if:
 *         - a drink with the same name already exists
 *         - a drink with the same id already exists
 *         - the specified tea type doesn't exist in teaTypes
 *         - the specified milk type doesn't exist in milkTypes
 */
bool create_recipe(const char name[], const int id, const int price, const char tea[], const char milk[], TeaType *teaTypes, MilkType *milkTypes, Drink **&recipes, int &numRecipes)
{
    // check for duplicate drink names and drink IDs
    for (int i = 0; i < numRecipes; ++i)
    {
        if (strcmp(recipes[i]->name, name) == 0 || recipes[i]->id == id)
        {
            return false;
        }
    }

    // check for the case that the specified tea type doesn't exist in teaTypes and the specified milk type doesn't exist in milkTypes
    TeaType *t = teaTypes; // temp variable, avoid bug
    while (t != nullptr && strcmp(t->name, tea) != 0)
    {
        t = t->next;
    } // 2 possible outcomes;

    if (t == nullptr)
    {
        return false; // outcome1: not found;
    }
    // outcome2: defalut, already found, t points to the target type tea.

    MilkType *m = milkTypes;
    while (m != nullptr && strcmp(m->name, milk) != 0)
    {
        m = m->next;
    }
    if (m == nullptr)
    {
        return false;
    }

    // allocate memory and initialize the new Drink
    Drink *newDrink = new Drink;
    strcpy(newDrink->name, name);
    newDrink->id = id;
    newDrink->price = price;
    newDrink->tea = t;
    newDrink->milk = m;
    newDrink->toppings = nullptr;

    // prepare and insert
    Drink **newReci = new Drink *[numRecipes + 1];
    for (int i = 0; i < numRecipes; ++i)
    {
        newReci[i] = recipes[i];
    }
    newReci[numRecipes] = newDrink;
    delete[] recipes;
    recipes = newReci;
    ++numRecipes;

    // ranking
    for (int pass = 0; pass < numRecipes - 1; ++pass)
    {
        for (int j = 0; j < numRecipes - 1 - pass; ++j)
        {
            if (recipes[j]->id > recipes[j + 1]->id)
            {
                Drink *tmp = recipes[j];
                recipes[j] = recipes[j + 1];
                recipes[j + 1] = tmp;
            }
        }
    }
    return true;
}

/**
 * function remove_recipe removes a drink recipe from the recipes array and
 * reallocates memory for the array to maintain contiguous elements
 *
 * @param drink: the name of the drink to be removed
 * @param recipes: a pointer to the dynamic array of recipes
 * @param numRecipes: the number of drinks in the recipe array (will be decremented if successful)
 *
 * @return true if the drink is successfully found and removed
 *         false if the drink with the specified name doesn't exist
 */
bool remove_recipe(const char drink[], Drink **&recipes, int &numRecipes)
{
    int index = -1;
    for (int i = 0; i < numRecipes; ++i)
    {
        if (strcmp(recipes[i]->name, drink) == 0)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        return false; // nout found;
    }

    delete recipes[index];

    Drink **newReci = nullptr;
    if (numRecipes > 1)
    {
        newReci = new Drink *[numRecipes - 1];
        int j = 0;
        for (int i = 0; i < numRecipes; ++i)
        {
            if (i == index)
                continue;
            newReci[j++] = recipes[i];
        }
    }
    delete[] recipes;
    recipes = newReci;
    --numRecipes;

    return true;
}

// === Region: Order Functions ===
/**
 * function create_order creates a new order and inserts it into the pending list
 * in ascending order of number
 *
 * @param pending: a pointer to the head of the pending order list
 * @param number: the order number
 * @param drink: the name of the drink to order
 * @param recipes: a pointer to the dynamic array of recipes
 * @param numRecipes: the number of drinks in the recipe
 * @param sugarLevel: the sugar level of the drink
 *
 * @return true if the order is successfully created and added to the pending list
 *         false if:
 *         - an order with the same number already exists in the pending list
 *         - the specified drink name doesn't exist in the recipes array
 */
bool create_order(Order *&pending, const int number, const char drink[], Drink **&recipes, const int numRecipes, const SugarLevel sugarLevel)
{
    // case of same order number
    Order *temp_pending = pending; // temp variable, avoid bug
    while (temp_pending != nullptr)
    {
        if (temp_pending->number == number)
            return false;
        temp_pending = temp_pending->next;
    }

    // case of the specified drink name doesn't exist in the recipes array
    Drink *Reci_order = nullptr;
    for (int i = 0; i < numRecipes; ++i)
    {
        if (strcmp(recipes[i]->name, drink) == 0)
        {
            Reci_order = recipes[i];
            break;
        } // same name
    }
    if (Reci_order == nullptr)
        return false; // still not find

    // get the info from original reci or Reci_order
    Drink *newDrink = new Drink;
    strcpy(newDrink->name, Reci_order->name);
    newDrink->id = -1;
    newDrink->price = Reci_order->price;
    newDrink->tea = Reci_order->tea;
    newDrink->milk = Reci_order->milk;

    // get the info of toppings
    if (Reci_order->toppings == nullptr)
    {
        newDrink->toppings = nullptr;
    }
    else
    {
        // create the head node for the new list
        ToppingListNode *srcNode = Reci_order->toppings;
        ToppingListNode *dstHead = new ToppingListNode;
        dstHead->topping = srcNode->topping;
        dstHead->next = nullptr;

        // use two pointers to traverse, srcNode reads the original list, dstTail builds the new list
        ToppingListNode *dstTail = dstHead;
        srcNode = srcNode->next;
        while (srcNode != nullptr)
        {
            // for each original node, create a new node and attach it to the tail
            ToppingListNode *newNode = new ToppingListNode;
            newNode->topping = srcNode->topping;
            newNode->next = nullptr;

            dstTail->next = newNode;
            dstTail = newNode;
            srcNode = srcNode->next;
        }
        newDrink->toppings = dstHead;
    }

    // new order, fill the info into it this new order
    Order *newOrder = new Order;
    newOrder->number = number;
    newOrder->drink = newDrink;
    newOrder->sugarLevel = sugarLevel;
    newOrder->next = nullptr;

    // calories cal
    int totalCal = newDrink->milk->calories;
    {
        ToppingListNode *pointer_topping_calor = newDrink->toppings;
        while (pointer_topping_calor != nullptr)
        {
            totalCal += pointer_topping_calor->topping->calories;
            pointer_topping_calor = pointer_topping_calor->next;
        }
    }
    newOrder->calories = totalCal;

    // caffine cal
    newOrder->caffeine = newDrink->tea->caffeine;

    // insert into pending list
    //  at first
    if (pending == nullptr || number < pending->number)
    {
        newOrder->next = pending;
        pending = newOrder;
    }
    // find the specific place
    else
    {
        Order *current = pending;
        while (current->next != nullptr && current->next->number < number)
        {
            current = current->next;
        }
        newOrder->next = current->next;
        current->next = newOrder;
    }
    return true;
}

// helper function used in 4.3.1 and 4.3.2
// 1. find order in pending list by order number
Order *find_order(Order *pending, int number)
{
    // start from head pointer
    Order *ptr = pending;
    while (ptr != nullptr)
    {
        // if order number matches, return it
        if (ptr->number == number)
        {
            return ptr;
        }
        // otherwise, move to next order
        ptr = ptr->next;
    }
    // not found after traversal
    return nullptr;
}

// 2. find topping in toppingType database list
ToppingType *find_topping_type(ToppingType *head, const char *name)
{
    // start from the list head
    ToppingType *ptr = head;
    while (ptr != nullptr)
    {
        if (strcmp(ptr->name, name) == 0)
        {
            return ptr;
        }
        ptr = ptr->next;
    }
    return nullptr;
}

// 3. find specific topping in an order's toppings list
bool find_topping_in_order(
    ToppingListNode *head,
    const char *name,
    ToppingListNode *&prev,
    ToppingListNode *&cur)
{
    prev = nullptr;
    cur = head;
    // traverse until cur==nullptr or name matches
    while (cur != nullptr)
    {
        if (strcmp(cur->topping->name, name) == 0)
        {
            return true; // found
        }
        prev = cur;
        cur = cur->next;
    }
    return false; // not found
}

/**
 * function add_topping_to_order adds a topping to a pending order's drink
 * and adds the topping's calories to the order's calorie count.
 * The toppings are maintained in alphabetical order by name.
 *
 * @param number: the order number of the pending order
 * @param topping: the name of the topping to add
 * @param toppingTypes: a linked list storing the topping types
 * @param pending: a pointer to the head of the pending order list
 *
 * @return true if the topping is successfully added
 *         false if:
 *         - the pending list is empty
 *         - no order with the specified number exists
 *         - the order already has this topping
 *         - the specified topping doesn't exist in the toppingTypes list
 */
bool add_topping_to_order(const int number, const char topping[], ToppingType *toppingTypes, Order *pending)
{
    // step1. check the order exist or not
    Order *Order_Pointer = find_order(pending, number);
    if (Order_Pointer == nullptr)
    {
        return false;
    }

    // step2. same toppings?
    ToppingListNode *Previous_Node = nullptr;
    ToppingListNode *Current_Node = nullptr;
    if (find_topping_in_order(Order_Pointer->drink->toppings, topping, Previous_Node, Current_Node))
    {
        return false;
    }

    // step3. topping type check
    ToppingType *Topping_Type_Pointer = find_topping_type(toppingTypes, topping);
    if (Topping_Type_Pointer == nullptr)
    {
        return false;
    }

    // step 4. insert
    ToppingListNode *New_Node = new ToppingListNode;
    New_Node->topping = Topping_Type_Pointer;
    New_Node->next = nullptr;

    if (Previous_Node == nullptr)
    {
        New_Node->next = Order_Pointer->drink->toppings;
        Order_Pointer->drink->toppings = New_Node;
    }
    else
    {
        New_Node->next = Previous_Node->next;
        Previous_Node->next = New_Node;
    }

    Order_Pointer->calories += Topping_Type_Pointer->calories;

    return true;
}
/**
 * function remove_topping_from_order removes a topping from a pending order's drink
 * and subtracts the topping's calories from the order's calorie count
 *
 * @param number: the order number of the pending order
 * @param topping: the name of the topping to remove
 * @param pending: a pointer to the head of the pending order list
 *
 * @return true if the topping is successfully found and removed
 *         false if:
 *         - no order with the specified number exists in the pending list
 *         - the order's drink has no toppings
 *         - the specified topping doesn't exist in the order's toppings list
 */
bool remove_topping_from_order(const int number, const char topping[], Order *pending)
{
    // step1. check if the order exists
    Order *Order_Pointer = find_order(pending, number);
    if (Order_Pointer == nullptr)
    {
        return false;
    }

    // step2. check if any toppings exist
    if (Order_Pointer->drink->toppings == nullptr)
    {
        return false;
    }

    // step3. find the specified topping node and its previous node in the order's toppings list
    ToppingListNode *Previous_Node = nullptr;
    ToppingListNode *Current_Node = nullptr;
    if (!find_topping_in_order(Order_Pointer->drink->toppings, topping, Previous_Node, Current_Node))
    {
        return false; // topping not found in the order
    }

    // step4. delete the node
    if (Previous_Node == nullptr)
    {
        // deleting the first node
        Order_Pointer->drink->toppings = Current_Node->next;
    }
    else
    {
        // deleting a middle or last node
        Previous_Node->next = Current_Node->next;
    }

    Order_Pointer->calories -= Current_Node->topping->calories;

    delete Current_Node; // assuming the node was allocated with 'new ToppingListNode'

    return true;
}

/**
 * function build_replacement_list builds a circular linked list of milk replacements
 * sorted by calories in ascending order. The function creates new ReplacementListNode objects
 * that reference the existing MilkType objects.
 * When milk types have equal calories, their relative order from the original list is preserved.
 *
 * @param milkTypes: a linked list of MilkType objects
 * @param replacement: a reference to the pointer that will point to the head of the circular replacement list
 *
 * @return true if the replacement cycle is successfully built
 *         false if the milkTypes list is empty (nullptr)
 */
bool build_replacement_list(MilkType *milkTypes, ReplacementListNode *&replacement)
{
    if (milkTypes == nullptr)
    {
        return false;
    } // if milkTypes is an empty list, then return false;

    // step 1. copy to a temporary linear linked list ---
    ReplacementListNode *linear_head = nullptr;
    ReplacementListNode *linear_tail = nullptr;
    MilkType *current_milk_type = milkTypes;
    while (current_milk_type != nullptr)
    {
        // create a new node for each original node
        ReplacementListNode *new_node = new ReplacementListNode;
        new_node->milk = current_milk_type; // keep reference to original MilkType
        new_node->next = nullptr;

        // insert to the end of the temporary list
        if (linear_head == nullptr)
        {
            linear_head = linear_tail = new_node;
        }
        else
        {
            linear_tail->next = new_node;
            linear_tail = new_node;
        }
        current_milk_type = current_milk_type->next;
    }

    // step 2. repeatedly select the smallest node from the temporary list to build a sorted list ---
    ReplacementListNode *sorted_head = nullptr;
    ReplacementListNode *sorted_tail = nullptr;
    while (linear_head != nullptr)
    {
        // find the node with the smallest calories in linear_head list
        ReplacementListNode *min_previous_node = nullptr;
        ReplacementListNode *min_node = linear_head;
        ReplacementListNode *previous_node = linear_head;
        ReplacementListNode *iterator_node = linear_head->next;
        while (iterator_node != nullptr)
        {
            if (iterator_node->milk->calories < min_node->milk->calories)
            {
                min_previous_node = previous_node;
                min_node = iterator_node;
            }
            previous_node = iterator_node;
            iterator_node = iterator_node->next;
        }
        // remove min_node from the temporary list
        if (min_previous_node == nullptr)
        {
            // the smallest node is the head node
            linear_head = min_node->next;
        }
        else
        {
            min_previous_node->next = min_node->next;
        }
        // append min_node to the end of the sorted list
        min_node->next = nullptr;
        if (sorted_head == nullptr)
        {
            sorted_head = sorted_tail = min_node;
        }
        else
        {
            sorted_tail->next = min_node;
            sorted_tail = min_node;
        }
    }

    // step 3. form a circular linked list ---
    // Also., at this point, sorted_tail points to the last node
    sorted_tail->next = sorted_head;
    replacement = sorted_head;
    return true;
}

/**
 * function find_available_in_replacement_circle finds a milk replacement with available stock
 * starting from the position after the target milk in the circular list, going around once.
 *
 * @param targetMilk: a pointer to the original milk type that needs replacement
 * @param replacement: a pointer to the head of the replacement circular list
 *
 * @return a pointer to the first available milk replacement if found.
 *         Returns nullptr if:
 *         - The replacement list is empty (nullptr)
 *         - The targetMilk is not found in the replacement list
 *         - No milk with stock > 0 is found after traversing the entire circular list once
 */
MilkType *find_available_in_replacement_circle(MilkType *targetMilk, ReplacementListNode *replacement)
{
    // 1. nullptr case
    if (replacement == nullptr)
    {
        return nullptr;
    }

    // 2. find targetMilk
    ReplacementListNode *start = replacement;
    bool found = false;
    do
    {
        if (start->milk == targetMilk)
        {
            found = true;
            break;
        }
        start = start->next;
    } while (start != replacement);

    // 3.not found
    if (!found)
        return nullptr;

    // 4. search for stock > 0 from next
    ReplacementListNode *iter = start->next;
    while (iter != start)
    {
        if (iter->milk->stock > 0)
            return iter->milk;
        iter = iter->next;
    }

    return nullptr;
}

/**
 * Moves an order from the pending list to the ready list, handling ingredient availability
 *
 * This function:
 * 1. Finds the specified order in the pending list
 * 2. Checks each ingredient's availability
 * 3. Makes substitutions where possible (for milk)
 * 4. Skips unavailable toppings
 * 5. Moves the order to the appropriate ready list
 *
 * @param number: The unique number of the order to process
 * @param pending: Reference to the head of the pending order list
 * @param ready: Array of pointers to the heads of ready order lists (buckets)
 * @param replacement: Pointer to the head of the circular replacement list for milk
 *
 * @return ORDER_NOT_READY (0) if the order cannot be processed (not found or
 *                           required ingredients unavailable without substitution)
 *         ORDER_READY_PERFECT (1) if the order is processed with all original ingredients
 *         ORDER_READY_MODIFIED (2) if the order is processed with substitutions or omissions
 */
int get_order_ready(const int order_number, Order *&pending_orders, Order *ready_orders[], ReplacementListNode *replacement_list)
{
    // check if pending list is empty or order not found
    if (pending_orders == nullptr)
    {
        return 0;
    }
    Order *previous_order = nullptr;
    Order *current_order = pending_orders;
    while (current_order->number != order_number && current_order)
    {
        previous_order = current_order;
        current_order = current_order->next;
    }
    if (current_order == nullptr)
    {
        return 0;
    }

    // remove the order from pending list
    if (previous_order == nullptr)
    {
        pending_orders = current_order->next;
    }
    else
    {
        previous_order->next = current_order->next;
    }
    current_order->next = nullptr;

    // check milk stock and replace if necessary
    if (current_order->drink->milk->stock > 0)
    {
        current_order->drink->milk->stock--;
    }
    else
    {
        MilkType *replacement_milk = find_available_in_replacement_circle(
            current_order->drink->milk, replacement_list);
        if (replacement_milk == nullptr)
        {
            return 0;
        }
        current_order->drink->milk = replacement_milk;
    }

    // check and remove unavailable toppings
    ToppingListNode *previous_topping = nullptr;
    ToppingListNode *current_topping = current_order->drink->toppings;
    while (current_topping)
    {
        if (current_topping->topping->stock > 0)
        {
            current_topping->topping->stock--;
            previous_topping = current_topping;
            current_topping = current_topping->next;
        }
        else
        {
            ToppingListNode *topping_to_delete = current_topping;
            if (previous_topping == nullptr)
            {
                current_order->drink->toppings = current_topping->next;
                current_topping = current_order->drink->toppings;
            }
            else
            {
                previous_topping->next = current_topping->next;
                current_topping = previous_topping->next;
            }
            delete topping_to_delete;
        }
    }

    // move the order to ready list
    int bucket = order_number % 10;
    current_order->next = ready_orders[bucket];
    ready_orders[bucket] = current_order;

    return 1;
}

// === Region: Destructors ===
/**
 * function delete_database deletes the linked lists storing the ingredients database
 *
 * @param teaTypes: an array of pointers to TeaType
 * @param milkTypes: an array of pointers to MilkType
 * @param toppingTypes: an array of pointers to ToppingType
 */
void delete_database(TeaType *&teaTypes, MilkType *&milkTypes, ToppingType *&toppingTypes)
{
    // delete TeaType linked list
    TeaType *teatea = teaTypes;
    while (teatea != nullptr)
    {
        TeaType *a = teatea->next;
        delete teatea;
        teatea = a;
    }
    // delete MilkType ll
    MilkType *milkmilk = milkTypes;
    while (milkmilk != nullptr)
    {
        MilkType *b = milkmilk->next;
        delete milkmilk;
        milkmilk = b;
    }
    // delete ToppingType ll
    ToppingType *toppingtopping = toppingTypes;
    while (toppingtopping != nullptr)
    {
        ToppingType *c = toppingtopping->next;
        delete toppingtopping;
        toppingtopping = c;
    }
}

/**
 * function delete_recipe deletes the dynamic array storing the drink recipes
 *
 * @param recipes: a pointer to the dynamic array of drinks
 * @param numRecipes: the number of drinks in the recipe
 */
void delete_recipe(Drink **&recipes, int numRecipes)
{
    // delete each Drink*
    for (int i = 0; i < numRecipes; ++i)
    {
        delete recipes[i];
    }
    // for pointer array
    delete[] recipes;
    recipes = nullptr;
    numRecipes = 0;
}

/**
 * function delete_pending_orders deletes the linked lists storing the pending orders
 *
 * @param pending: a pointer to the head of the pending order list
 */
void delete_pending_orders(Order *&pending)
{
    while (pending != nullptr)
    {
        Order *current_order = pending;
        pending = pending->next; // break head

        // delete toppings list
        ToppingListNode *topping_node = current_order->drink->toppings;
        while (topping_node != nullptr)
        {
            ToppingListNode *next_topping = topping_node->next;
            delete topping_node;
            topping_node = next_topping;
        }
        // delete drink object
        delete current_order->drink;
        // delete order node
        delete current_order;
    }
}

/**
 * function delete_ready_orders deletes the linked lists storing the ready orders
 *
 * @param ready: an array of pointers to the head of the ready order list
 */
void delete_ready_orders(Order *ready_orders[])
{
    for (int index = 0; index < 10; ++index)
    {
        Order *current_order = ready_orders[index];
        while (current_order != nullptr)
        {
            Order *order_to_delete = current_order;
            current_order = current_order->next;

            // Delete toppings list
            ToppingListNode *topping_node = order_to_delete->drink->toppings;
            while (topping_node != nullptr)
            {
                ToppingListNode *next_topping_node = topping_node->next;
                delete topping_node;
                topping_node = next_topping_node;
            }

            // Delete drink object
            delete order_to_delete->drink;

            // Delete order node
            delete order_to_delete;
        }
        ready_orders[index] = nullptr;
    }
}

/**
 * function delete_replacement_circle deletes the circular linked list of milk replacements
 *
 * @param replacement: a pointer to the head of the replacement list
 */
void delete_replacement_circle(ReplacementListNode *&replacement)
{
    if (replacement == nullptr)
        return;

    // make the tail's next = nullptr
    ReplacementListNode *slow_pointer = replacement;
    while (slow_pointer->next != replacement)
    {
        slow_pointer = slow_pointer->next;
    }
    slow_pointer->next = nullptr;

    // delete just like a normal linked list
    ReplacementListNode *current_node = replacement;
    while (current_node != nullptr)
    {
        ReplacementListNode *temp_node = current_node->next;
        delete current_node;
        current_node = temp_node;
    }
    replacement = nullptr;
}
