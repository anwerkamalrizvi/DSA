#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Combatant {
public:
    int id;
    string name;
    int hp;
    int attackPower;
    
    Combatant() {
        id = 0;
        name = "";
        hp = 0;
        attackPower = 0;
    }
    
    Combatant(int i, string n, int h, int ap) {
        id = i;
        name = n;
        hp = h;
        attackPower = ap;
    }
};

class CombatNode {
public:
    Combatant data;
    CombatNode* left;
    CombatNode* right;
    
    CombatNode(Combatant c) {
        data = c;
        left = nullptr;
        right = nullptr;
    }
};

class CombatBST {
public:
    CombatNode* root;
    
    CombatBST() {
        root = nullptr;
    }
    
    CombatNode* insert(CombatNode* node, Combatant c) {
        if (node == nullptr) {
            return new CombatNode(c);
        }
        
        if (c.id < node->data.id) {
            node->left = insert(node->left, c);
        } else if (c.id > node->data.id) {
            node->right = insert(node->right, c);
        }
        
        return node;
    }
    
    void insert(Combatant c) {
        root = insert(root, c);
    }
    
    CombatNode* findMin(CombatNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    CombatNode* deleteNode(CombatNode* node, int id) {
        if (node == nullptr) {
            return nullptr;
        }
        
        if (id < node->data.id) {
            node->left = deleteNode(node->left, id);
        } else if (id > node->data.id) {
            node->right = deleteNode(node->right, id);
        } else {
            if (node->left == nullptr) {
                CombatNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                CombatNode* temp = node->left;
                delete node;
                return temp;
            }
            
            CombatNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data.id);
        }
        
        return node;
    }
    
    void deleteNode(int id) {
        root = deleteNode(root, id);
    }
    
    CombatNode* getFrontline() {
        if (root == nullptr) {
            return nullptr;
        }
        return findMin(root);
    }
    
    bool isEmpty() {
        return root == nullptr;
    }
    
    void inorder(CombatNode* node) {
        if (node == nullptr) {
            return;
        }
        
        inorder(node->left);
        cout << "    " << node->data.name << " [HP: " << node->data.hp << "]" << endl;
        inorder(node->right);
    }
    
    void displayAll() {
        inorder(root);
    }
    
    void updateHP(int id, int newHP) {
        updateHPHelper(root, id, newHP);
    }
    
    void updateHPHelper(CombatNode* node, int id, int newHP) {
        if (node == nullptr) {
            return;
        }
        
        if (node->data.id == id) {
            node->data.hp = newHP;
            return;
        } else if (id < node->data.id) {
            updateHPHelper(node->left, id, newHP);
        } else {
            updateHPHelper(node->right, id, newHP);
        }
    }
};

class BattleGame {
public:
    CombatBST playerTeam;
    CombatBST enemyTeam;
    int roundNumber;
    
    BattleGame() {
        roundNumber = 0;
        srand(time(0));
    }
    
    void initializeTeams() {
        cout << " BATTLEQUEST: BST ARENA " << endl;
        cout << "\nInitializing Teams...\n" << endl;
        
        playerTeam.insert(Combatant(3, "Barbarian", 100, 15));
        playerTeam.insert(Combatant(1, "Giant", 120, 12));
        playerTeam.insert(Combatant(4, "Minion", 80, 20));
        playerTeam.insert(Combatant(2, "Archer", 90, 18));
        playerTeam.insert(Combatant(5, "Valkyrie", 310, 140));
        
        enemyTeam.insert(Combatant(3, "Pasha, The Don of Hadeed Ruins", 95, 14));
        enemyTeam.insert(Combatant(1, "Goblin Giant", 70, 10));
        enemyTeam.insert(Combatant(5, "Aen, The Great", 150, 25));
        enemyTeam.insert(Combatant(2, "Ma Hatma, The dangerous Grandma", 100, 16));
        enemyTeam.insert(Combatant(4, "Kazuya Demon", 120, 20));
        
        cout << "Player Team:" << endl;
        playerTeam.displayAll();
        
        cout << "\nEnemy Team:" << endl;
        enemyTeam.displayAll();
        
        cout << "\n=== BATTLE START ===\n" << endl;
    }
    
    int calculateDamage(int basePower) {
        return basePower + (rand() % 5);
    }
    
    void displayRoundInfo() {
        cout << "--- ROUND " << roundNumber << " ---" << endl;
        cout << "\nPlayer Team:" << endl;
        playerTeam.displayAll();
        cout << "\nEnemy Team:" << endl;
        enemyTeam.displayAll();
        cout << endl;
    }
    
    void performAttack(CombatNode* attacker, CombatNode* defender, CombatBST& defenderTeam, string attackerType, string defenderType) {
        int damage = calculateDamage(attacker->data.attackPower);
        
        cout << attackerType << " " << attacker->data.name << " attacks " << defenderType << " " << defender->data.name << "!" << endl;
        cout << "Damage dealt: " << damage << endl;
        
        int newHP = defender->data.hp - damage;
        defenderTeam.updateHP(defender->data.id, newHP);
        
        cout << defender->data.name << "'s HP: " << defender->data.hp << " -> " << newHP << endl;
        
        if (newHP <= 0) {
            cout << "\n" << defender->data.name << " has been defeated!\n" << endl;
            defenderTeam.deleteNode(defender->data.id);
        } else {
            cout << endl;
        }
    }
    
    void playRound() {
        roundNumber++;
        displayRoundInfo();
        
        CombatNode* playerFrontline = playerTeam.getFrontline();
        CombatNode* enemyFrontline = enemyTeam.getFrontline();
        
        if (playerFrontline == nullptr || enemyFrontline == nullptr) {
            return;
        }
        
        performAttack(playerFrontline, enemyFrontline, enemyTeam, "Hero", "Enemy");
        
        if (enemyTeam.isEmpty()) {
            return;
        }
        
        enemyFrontline = enemyTeam.getFrontline();
        playerFrontline = playerTeam.getFrontline();
        
        performAttack(enemyFrontline, playerFrontline, playerTeam, "Enemy", "Hero");
    }
    
    void startBattle() {
        initializeTeams();
        
        while (!playerTeam.isEmpty() && !enemyTeam.isEmpty()) {
            playRound();
        }
        
        cout << "BATTLE END" << endl;
        if (playerTeam.isEmpty()) {
            cout << "\nDEFEAT! The enemy team has won!" << endl;
        } else {
            cout << "\nVICTORY! Your team has won!" << endl;
        }
    }
};

int main() {
    BattleGame game;
    game.startBattle();
    
    return 0;
}