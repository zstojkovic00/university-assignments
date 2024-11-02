#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <random>
#include <set>


using namespace std;

class Pokemon {
protected:
    string name;
    int health;
    int attack;
    int mana;
public:
    Pokemon(string n, int h, int a, int m) {
        name = n;
        health = h;
        attack = a;
        mana = m;
    }
    virtual void attackPokemon(Pokemon* target) = 0;
    virtual void spellAttack(Pokemon* target) = 0;


    void reduceHealth(int damage) {
        health -= damage;
        if (health < 0) {
            health = 0;
        }
    }

    void reduceMana(int cost) {
        mana -= cost;
        if (mana < 0) {
            mana = 0;
        }
    }

    int getMana() {
        return mana;
    }

    bool isAlive() {
        return health > 0;
    }

    string getName() {
        return name;
    }

    int getHealth() {
        return health;
    }

    int getAttack() {
        return attack;
    }

    bool operator==(const Pokemon& other) const {
        return (name == other.name) && (health == other.health) && (attack == other.attack) && (mana == other.mana);
    }


};

class FirePokemon : public Pokemon {
public:
    FirePokemon(string n, int h, int a, int m) : Pokemon(n, h, a, m) {}

    void attackPokemon(Pokemon* target) {
        int damage = attack;
        target->reduceHealth(damage);
        cout << name << " attacked " << target->getName() << " with " << damage << " damage!" << endl;
    }

    void spellAttack(Pokemon* target) override {
        if (mana >= 20) {
            int damage = attack + 10;
            target->reduceHealth(damage);
            mana -= 20;
            cout << name << " casted a fire spell on " << target->getName() << " dealing " << damage << " damage!" << endl;
        } else {
            cout << name << " doesn't have enough mana to cast a spell, so he will use basic attack instead" << endl;
            attackPokemon(target);
        }
    }
};


class WaterPokemon : public Pokemon {
public:
    WaterPokemon(string n, int h, int a, int m) : Pokemon(n, h, a, m) {}

    void attackPokemon(Pokemon* target) {
        int damage = attack;
        target->reduceHealth(damage);
        cout << name << " attacked " << target->getName() << " with " << damage << " damage!" << endl;
    }
    void spellAttack(Pokemon* target) override {
        if (mana >= 20) {
            int damage = attack + 10;
            target->reduceHealth(damage);
            mana -= 20;
            cout << name << " casted a water spell on " << target->getName() << " dealing " << damage << " damage!" << endl;
        } else {
            cout << name << " doesn't have enough mana to cast a spell, so he will use basic attack instead" << endl;
            attackPokemon(target);
        }
    }
};


class ElectricPokemon : public Pokemon {
public:
    ElectricPokemon(string n, int h, int a, int m) : Pokemon(n, h, a, m) {}

    void attackPokemon(Pokemon* target) {
        int damage = attack;
        target->reduceHealth(damage);
        cout << name << " attacked " << target->getName() << " with " << damage << " damage!" << endl;
    }
    void spellAttack(Pokemon* target) override {
        if (mana >= 20) {
            int damage = attack + 10;
            target->reduceHealth(damage);
            mana -= 20;
            cout << name << " casted a electric spell on " << target->getName() << " dealing " << damage << " damage!" << endl;
        } else {
            attackPokemon(target);
        }
    }
};

class OpponentPokemons : public Pokemon {
public:
    OpponentPokemons(string n, int h, int a, int m) : Pokemon(n, h, a, m) {}

    void attackPokemon(Pokemon* target) {
        int damage = attack;
        target->reduceHealth(damage);
        cout << name << " attacked " << target->getName() << " with " << damage << " damage!" << endl;
    }

    void spellAttack(Pokemon* target) override {
      return;
    }

};


class Trainer {
private:
    vector<Pokemon *> pokemons;
    int money;
public:
    Trainer(int m) {
        money = m;
    }

    bool buyPokemon(Pokemon *p) {
        int price = (p->getAttack() + p->getHealth()) * 2;
        if (money >= price) {
            pokemons.push_back(p);
            money -= price;
            return true;
        }
        return false;
    }

    void display() {
        cout << "My Pokemons: ";
        for (int i = 0; i < pokemons.size(); i++) {
            cout << pokemons[i]->getName() << ": " << pokemons[i]->getHealth() << "HP";
            if (i < pokemons.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
        cout << "Money: " << money << "e" << endl;
    }


    vector<Pokemon *> getPokemons() {
        return pokemons;
    };

};


class OpponentTrainer : public Trainer {
public:
    OpponentTrainer(int m) : Trainer(m) {}

    void loadPokemons() {
        ifstream file("pokemons.txt");
        string name;
        int health, attack,mana;
        set<string> loadedNames;

        while (file >> name >> health >> attack) {
            // Nemoj dozvoliti duplikate
            if (loadedNames.find(name) != loadedNames.end()) {
                continue;
            }
            Pokemon *p = new OpponentPokemons(name, health, attack, mana);
            opponentPokemons.push_back(p);
            loadedNames.insert(name);
        }

        // Dodeli n (U ovom slucaju 2) random pokemona iz pokemons.txt fajla.
        unsigned seed = time(0);
        for (int i = 0; i < 2; i++) {
            opponentPokemons[i] = opponentPokemons[opponentPokemons.size() - 1 - i];
        }
        shuffle(opponentPokemons.begin(), opponentPokemons.end(), default_random_engine (seed));
        opponentPokemons.resize(2);
    }


    void displayPokemons() {
        cout << "Opponent Trainer's Pokemons: ";
        for (Pokemon *p: opponentPokemons) {
            cout << p->getName() << ": " << p->getHealth() << "HP ";
        }

        cout << endl;
        cout << "----------------------------" << endl;

    }

    vector<Pokemon *> getOpponentPokemons() {
        return opponentPokemons;
    }


private:
    vector<Pokemon *> opponentPokemons;
};


// Metoda da postanete uspesan robovlasnik pokemona
void chooseTrainerPokemons(Trainer& player, const vector<Pokemon*>& pokemons) {

    while (player.getPokemons().size() < 2) {
        cout << "Choose your Pokemon" << endl;
        for (int i = 0; i < pokemons.size(); i++) {
            // Cena pokemona je njihov napad + zdravlje puta 2
            cout << i + 1 << ". " << pokemons[i]->getName() << " (cost: "
                 << (pokemons[i]->getAttack() + pokemons[i]->getHealth()) * 2 << "e)" << endl;
        }
        int choice;
        cin >> choice;
        if (choice >= 1 && choice <= pokemons.size()) {
            Pokemon* p = pokemons[choice - 1];
            bool alreadyInTeam = false;

            // Proveri da li se pokemon nalazi u timu.
            for (const auto& teamPokemon : player.getPokemons()) {
                if (*teamPokemon == *p) {
                    alreadyInTeam = true;
                    break;
                }
            }

            // Ako se nalazi, ne dozvoli da ga kupi.
            if (alreadyInTeam) {
                cout << "You already have " << p->getName() << " in your team!" << endl;
            } else {
                if (player.buyPokemon(p)) {
                    cout << "You bought " << p->getName() << "!" << endl;
                } else {
                    cout << "You don't have enough money to buy " << p->getName() << "!" << endl;
                }
            }
        } else {
            cout << "Invalid choice!" << endl;
        }
        player.display();

    }


}

string winner(int playerWins, int opponentWins) {
    if (playerWins == opponentWins) {
        return "Match is a draw!";
    } else if (playerWins > opponentWins) {
        return "Player wins the match!";
    } else {
        return "Opponent wins the match!";
    }
}

// Metoda da naterate pokemona da se biju.
void battle(Trainer& player, OpponentTrainer& opponent) {
    vector<Pokemon*> playerPokemons = player.getPokemons();
    vector<Pokemon*> opponentPokemons = opponent.getOpponentPokemons();

    int playerWins = 0;
    int opponentWins = 0;

    cout << "Battle started!" << endl;

    // Provera da li su dostupni pokemoni za borbu
    if (playerPokemons.empty() || opponentPokemons.empty()) {
        cout << "Not enough Pokemons for battle!" << endl;
        return;
    }

    size_t maxRounds = min(playerPokemons.size(), opponentPokemons.size());

    // Glavna petlja za runde
    for (size_t round = 0; round < maxRounds; round++) {

        cout << "Round " << round + 1 << ":" << endl;

        Pokemon* playerPokemon = playerPokemons[round];
        Pokemon* opponentPokemon = opponentPokemons[round];

        // Trenutni pokemoni
        cout << "Player's Pokemon: " << playerPokemon->getName() << " (HP: " << playerPokemon->getHealth() << ")" << endl;
        cout << "Opponent's Pokemon: " << opponentPokemon->getName() << " (HP: " << opponentPokemon->getHealth() << ")" << endl;
        cout << "----------------------" << endl;

        // Glavna petlja borbe između pokemona
        while (playerPokemon->isAlive() && opponentPokemon->isAlive()) {
            // Potez igrača
            cout << "Player's turn:" << endl;
            cout << "Choose your attack: 1) Basic Attack, 2) Spell" << endl;
            int attackChoice;
            cin >> attackChoice;

            // Napad na protivnika
            if (attackChoice == 1) {
                playerPokemon->attackPokemon(opponentPokemon);
                cout << "------------------------------------------" << endl;
            } else if (attackChoice == 2) {
                playerPokemon->spellAttack(opponentPokemon);
            } else {
                cout << "Invalid choice! Skipping turn." << endl;
            }

            // Provera da li je borba završena
            if (!opponentPokemon->isAlive()) {
                cout << "Player wins this round!" << endl;
                playerWins++;
                break;
            }

            // Potez protivnika
            cout << "Opponent's turn:" << endl;
            opponentPokemon->attackPokemon(playerPokemon);
            cout << "------------------------------------------" << endl;

            // Prikaz stanja posle napada
            cout << "Player's Pokemon: " << playerPokemon->getName() << " (HP: " << playerPokemon->getHealth() << ")" << endl;
            cout << "Opponent's Pokemon: " << opponentPokemon->getName() << " (HP: " << opponentPokemon->getHealth() << ")" << endl;
            cout << "------------------------------------------" << endl;

            // Provera da li je borba završena
            if (!playerPokemon->isAlive()) {
                cout << "Opponent wins this round!" << endl;
                opponentWins++;
                break;
            }
        }

    }

    ofstream outFile("match_results.txt");

    cout << "Battle finished!" << endl;
    outFile << "Player wins: " << playerWins << " rounds" << endl;
    outFile << "Opponent wins: " << opponentWins << " rounds" << endl;
    outFile << winner(playerWins, opponentWins) << endl;

    outFile.close();
}

bool compareByAttack(Pokemon* p1, Pokemon* p2) {
    return p1->getAttack() > p2->getAttack();
}

int main() {
    vector<Pokemon *> pokemons;
    pokemons.push_back(new FirePokemon("Charmander", 1000, 20, 55));
    pokemons.push_back(new WaterPokemon("Squirtle", 1200, 15, 70));
    pokemons.push_back(new ElectricPokemon("Pikachu", 800, 25, 50));
    pokemons.push_back(new FirePokemon("Vulpix", 900, 18, 50));
    pokemons.push_back(new WaterPokemon("Magikarp", 600, 10, 40));
    pokemons.push_back(new ElectricPokemon("Raichu", 1200, 30, 60));
    pokemons.push_back(new FirePokemon("Charizard", 1500, 35, 70));
    pokemons.push_back(new WaterPokemon("Blastoise", 1800, 25, 80));
    pokemons.push_back(new ElectricPokemon("Zapdos", 1400, 40, 75));

    sort(pokemons.begin(), pokemons.end(), compareByAttack);

    Trainer player(100000);
    OpponentTrainer opponent(2);

    chooseTrainerPokemons(player, pokemons);
    opponent.loadPokemons();
    opponent.displayPokemons();
    battle(player, opponent);

    return 0;
}
