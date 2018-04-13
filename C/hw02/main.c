#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    HIGH_CARD = 1,
    PAIR = 2,
    TWO_PAIRS = 3,
    THREE_OF_A_KIND = 4,
    STRAIGHT = 5,
    FLUSH = 6,
    FULL_HOUSE = 7,
    FOUR_OF_A_KIND = 8,
    STRAIGHT_FLUSH = 9
} combination;

enum results {
    WINS = 0,
    LOSES = 1,
    DRAWS = 2
};

bool whoWins();
bool lastRiver(char ch);
void orderValues(char hand[2][2], char table[5][2], int values[7]);
void orderTable(char table[4][2], int values[4]);
void countSuitsOnTable(int table[4], int suits[4]);
void addValue(int size, int value, int values[size], int allValues[size + 1]);
void addTwoValues(int size, int value1, int value2, int values[size], int allValues[size + 2]);
bool loadCards(char cards[][2], size_t size);
void printCard(int value, int existingCards[6], bool *isFirst);
int value(char card[2]);
int analyze(int val[7], int hand[6]);
int analyzeWithAce(int val[7], int hand[6]);
double computePot(int Alice[7], int table[5], int suits[4]);
void computePotForMoreSpecialCards(int Alice[7], int table[5], combination AliceAnalyze, int AliceHand[5], int specialSuit, double WLDcounter[3]);
void computePotForThreeSpecialCards(int Alice[7], int table[5], combination AliceAnalyze, int AliceHand[5], int specialSuit, double WLDcounter[3]);
void computePotForNoSpecialCards(int Alice[7], int table[5], combination AliceAnalyze, int AliceHand[5], double WLDcounter[3]);
int computeWinner(int AliceAnalyze, int AliceHand[5], int Bob[7]);
int GCD(int a, int b);
bool isAce(int value);



int main(int argc, char *argv[])
{
    if(argc == 1){
        while(whoWins());
    }
    if((argc == 2) && (argv[1][0] == '-') && (argv[1][1] == 'r')) {
        while(lastRiver(argv[1][2]));
    }
    return 0;
}


/**
 * @brief lastRiver computes cards with best pot
 * @param ch parameter of decimal points (1 - 9)
 * @return false if EOF was typed
 */
bool lastRiver(char ch)
{
    char Alice[2][2], table[4][2];
    int orderedTable[4], orderedAlice[6], completeOrderedTable[5], completeOrderedAlice[7];
    int suits[4], count;
    double maxPot = 0, suitedPots[4][13], universalPots[13];

    if(!loadCards(Alice, 2))                                                        //loads cards from keyboard
        return false;
    loadCards(table, 4);

    orderTable(table, orderedTable);
    countSuitsOnTable(orderedTable, suits);                                         //creates ordered set of four cards on table
    addTwoValues(4, value(Alice[0]), value(Alice[1]), orderedTable, orderedAlice);  //creates ordered set of six Alice's cards
    for(int i = 2; i < 15; i++) {                                                   //computes pot for every card with no respect to suits
        addValue(6, i * 10 + 4, orderedAlice, completeOrderedAlice);
        addValue(4, i * 10 + 4, orderedTable, completeOrderedTable);
        universalPots[i - 2] = computePot(completeOrderedAlice, completeOrderedTable, suits);
    }
    for(int j = 0; j < 4; j++) {
        for(int i = 2; i < 15; i++) {                                               //computes pot for every card with respect to suits
            if(suits[j] >= 2) {
                count = 0;
                for(int k = 0; k < 6; k++) {
                    if(orderedAlice[k]  == i * 10 + j)
                        count++;
                }
                if(count > 0){
                    suitedPots[j][i - 2] = 0;
                } else {
                    suits[j]++;                                                         //it makes sense to compute card with respect to suit
                    addValue(6, i * 10 + j, orderedAlice, completeOrderedAlice);        //if there is a chance to have flush or strait flush. It means there are
                    addValue(4, i * 10 + j, orderedTable, completeOrderedTable);        //two cards of the suit on the table so that with river and two opponent's
                    suitedPots[j][i - 2] = computePot(completeOrderedAlice, completeOrderedTable, suits);   //cards there can be five cards of the same suit.
                }
            } else {
                count = 0;
                for(int k = 0; k < 6; k++) {
                    if((orderedAlice[k] / 10 == i) && (suits[orderedAlice[k] % 10] < 2))
                        count++;
                }
                for(int k = 0; k < 4; k++) {
                    if(suits[k] >= 2)
                        count++;
                }
                if(count >= 4){
                    suitedPots[j][i - 2] = 0;
                } else {
                    suitedPots[j][i - 2] = universalPots[i - 2];                        //if any suit isn't in cards twice, pot is same as for universal suits
                }
            }
            if(suitedPots[j][i - 2] > maxPot) {
                maxPot = suitedPots[j][i - 2];
            }
        }

    }
    bool isFirst = true;
    for(int i = 0; i < 13; i++) {                                       //prints card with the biggest pot
        for(int j = 3; j >= 0; j--) {
            if(suitedPots[j][i] == maxPot){
                printCard((i + 2) * 10 + j, orderedAlice, &isFirst);
            }
        }
    }
    putchar('\n');
    if((ch <= 57) && (ch >= 49)) {                                      //bonus no. 1
        printf("%.*lf", (int) ch - 48, maxPot);
        putchar('\n');
    }
    if(ch == 48){
        int a = (int) (maxPot * 1980.0 * 10);                           //bonus no. 2
        if(a % 10 >= 5){
            a = a / 10 + 1;
        } else {
            a = a / 10;
        }
        int b = 1980;
        printf("%d/%d\n", a / GCD(a, b), b / GCD(a, b));
    }
    return true;
}

/**
 * @brief whoWins determines who wins
 * @return false if EOF was typed
 */
bool whoWins()
{
    char Alice[2][2], Bob[2][2], table[5][2];
    int values1[7], values2[7], result, hand1[5], hand2[5], res1, res2;

    if(!loadCards(Alice, 2))
        return false;                               // loads cards from keyboard
    loadCards(Bob, 2);
    loadCards(table, 5);
    orderValues(Alice, table, values1);             // turns cards into values and orders them
    orderValues(Bob, table, values2);

    if(isAce(values1[0]))                       // tests if result would be better with ace treated as the lowest card
        res1 = analyzeWithAce(values1, hand1);
    else
        res1 = analyze(values1, hand1);

    if(isAce(values2[0]))
        res2 = analyzeWithAce(values2, hand2);
    else
        res2 = analyze(values2, hand2);

    result = res1 - res2;

    if(result > 0) {                                  // determines who wins
        putchar('W');
        putchar('\n');
    }
    else if(result < 0) {
        putchar('L');
        putchar('\n');
    }
    else {
        size_t i = 0;
        while(hand1[i] / 10 == hand2[i] / 10) {
            if(i == 4){
                putchar('D');
                putchar('\n');
                break;
            }
            i++;
        }
        if(hand1[i] / 10 > hand2[i] / 10) {
            putchar('W');
            putchar('\n');
        } else if(hand1[i] / 10 < hand2[i] / 10) {
            putchar('L');
            putchar('\n');
        }
    }

    return true;
}

bool isAce(int value) {
    return (value / 10 == 14);
}

/**
 * @brief GCD greatest common divisor
 * @param a
 * @param b
 * @return GCD of a and b
 */
int GCD(int a, int b) {
    while(b > 0) {
        if(a > b) {
            a = a - b;
        } else {
            b = b - a;
        }
    }
    return a;
}

/**
 * @brief value turn number and suit into one value
 * @param card  card to be turned
 * @return value / 10 gives card number; value % 10 gives its suit
 */
int value(char card[]){
    int numberValue = 0;
    int colourValue = 4;
    if(card[0] < 58)
        numberValue = card[0] - 48;
    if(card[0] == 'T')
        numberValue = 10;
    if(card[0] == 'J')
        numberValue = 11;
    if(card[0] == 'Q')
        numberValue = 12;
    if(card[0] == 'K')
        numberValue = 13;
    if(card[0] == 'A')
        numberValue = 14;
    if(card[1] == 'h')
        colourValue = 3;
    if(card[1] == 'd')
        colourValue = 2;
    if(card[1] == 's')
        colourValue = 1;
    if(card[1] == 'c')
        colourValue = 0;
    return 10 * numberValue + colourValue;
}

/**
 * @brief loadCards loads chards from keyboard
 * @param cards to be loaded
 * @param size number of cards
 */
bool loadCards(char cards[][2], size_t size){
    for(size_t i = 0; i < size; i++){
        cards[i][0] = getchar();
        if(cards[i][0] == EOF)
            return false;
        cards[i][1] = getchar();
        getchar();
    }
    return true;
}

/**
 * @brief printCard print card of concrete suit.
 * Also checks whether the card is not already on table.
 * @param value value of the card
 * @param existingCards cards on table or in hand
 */
void printCard(int value, int existingCards[6], bool *isFirst){
    bool isExisting;
    int numberValue = value / 10, suitValue = value % 10;
    char numberChar, suitChar;
    isExisting = false;
    for(size_t i = 0; i < 6; i++)
        if(existingCards[i] == numberValue * 10 + suitValue){
            isExisting = true;
        }
    if(!isExisting){
        if(numberValue < 10)
            numberChar = numberValue + 48;
        if(numberValue == 10)
            numberChar = 'T';
        if(numberValue == 11)
            numberChar = 'J';
        if(numberValue == 12)
            numberChar = 'Q';
        if(numberValue == 13)
            numberChar = 'K';
        if(numberValue == 14)
            numberChar = 'A';
        if(suitValue == 0)
            suitChar = 'c';
        if(suitValue == 1)
            suitChar = 's';
        if(suitValue == 2)
            suitChar = 'd';
        if(suitValue == 3)
            suitChar = 'h';
        if(*isFirst) {
            *isFirst = false;
        } else {
            putchar(' ');
        }
        putchar(numberChar);
        putchar(suitChar);
    }
}

/**
 * @brief orderValues
 * 1. creates one set of 7 cards for each player
 * 2. turns cards into values
 * 3. orders them using bubble sort
 * @param hand two cards in player's hand
 * @param table five common cards
 * @param values final set
 */
void orderValues(char hand[2][2], char table[5][2], int values[7]){
    int help;
    for(size_t i = 0; i < 2; i++){
        values[i] = value(hand[i]);
    }
    for(size_t i = 0; i < 5; i++){
        values[i+2] = value(table[i]);
    }
    for(size_t i = 0; i < 6; i++){
        for(size_t j = 0; j < 6 - i; j++){
            if(values[j] < values[j+1]){
                help = values[j];
                values[j] = values[j+1];
                values[j+1] = help;
            }
        }
    }
}

/**
 * @brief orderTable order just cards on table
 * @param table cards on table
 * @param values array of ordered card values
 */
void orderTable(char table[4][2], int values[4]) {
    int help;
    for(size_t i = 0; i < 4; i++){
        values[i] = value(table[i]);

    }
    for(size_t i = 0; i < 4; i++){
        for(size_t j = 0; j < 3 - i; j++){
            if(values[j] < values[j + 1]){
                help = values[j];
                values[j] = values[j + 1];
                values[j + 1] = help;
            }
        }
    }
}

/**
 * @brief addValue add a card to the right place of ordered set
 * @param size size of the ordered set
 * @param value card to be added
 * @param values ordered set of cards
 * @param allValues complete set of cards
 */
void addValue(int size, int value, int values[size], int allValues[size + 1]) {
    bool isAssigned = false;
    for(int i = 0; i < size; i++){
        if(value > values[i]) {
            if(!isAssigned) {
                allValues[i] = value;
                isAssigned = true;
            }
            allValues[i + 1] = values[i];
        } else {
            allValues[i] = values[i];
        }
    }
    if(!isAssigned){
        allValues[size] = value;
    }
}

/**
 * @brief addTwoValues add a card to the right place of ordered set
 * @param size size of the ordered set
 * @param value card to be added
 * @param values ordered set of cards
 * @param allValues complete set of cards
 */
void addTwoValues(int size, int value1, int value2, int values[size], int allValues[size + 2]) {
    int semiValues[size + 1];
    addValue(size, value1, values, semiValues);
    addValue(size + 1, value2, semiValues, allValues);
}
/**
 * @brief countSuitsOnTable
 * @param table cards on table
 * @param suits number of cards of each suit
 */
void countSuitsOnTable(int table[4], int suits[4]) {
    for(size_t j = 0; j < 4; j++) {
        suits[j] = 0;
    }
    for(size_t i = 0; i < 4; i++) {
        suits[table[i] % 10]++;
    }
}

/**
 * @brief computePot computes how big part of pot player gets
 * @param Alice Alice's card
 * @param table cards on table
 * @param suits number of cards of suits
 * @return part of pot
 */
double computePot(int Alice[7], int table[5], int suits[4]) {
    int AliceHand[5];
    int specialSuit = 4;
    combination AliceAnalyze;
    double WLDcounter[3] = {0, 0, 0};

    for(int j = 0; j < 4; j++) {
        if(suits[j] >= 3) {
            specialSuit = j;                                        //if there are three card on table of the same suit, the suit is special
        }
    }
    if(isAce(Alice[0]))                                         //tests if result would be better with ace treated as the lowest card
        AliceAnalyze = analyzeWithAce(Alice, AliceHand);
    else
        AliceAnalyze = analyze(Alice, AliceHand);

    if((specialSuit != 4) & (suits[specialSuit] > 3)){
        computePotForMoreSpecialCards(Alice, table, AliceAnalyze, AliceHand, specialSuit, WLDcounter);
    }
    if((specialSuit != 4) & (suits[specialSuit] == 3)) {
        computePotForMoreSpecialCards(Alice, table, AliceAnalyze, AliceHand, specialSuit, WLDcounter);
    }
    if(specialSuit == 4) {
        computePotForNoSpecialCards(Alice, table, AliceAnalyze, AliceHand, WLDcounter);
    }
    return (WLDcounter[WINS] + WLDcounter[DRAWS] / 2) / (WLDcounter[WINS] + WLDcounter[DRAWS] + WLDcounter[LOSES]);
}


void computePotForMoreSpecialCards(int Alice[7], int table[5], combination AliceAnalyze, int AliceHand[5], int specialSuit, double WLDcounter[3]){
    int V1, V2, VS1, VS2;
    int firstAliceCounter = 6, secondAliceCounter;
    int Bob[7];
    double sameCards;

    for(int i = 2; i < 15; i++) {
        V1 = 0;
        VS1 = 0;
        while((Alice[firstAliceCounter] / 10 == i) && (firstAliceCounter >= 0)) {
            if(Alice[firstAliceCounter] % 10 != specialSuit) {
                V1++;
            } else {
                VS1++;
            }
            firstAliceCounter--;
        }
        for(int j = i; j < 15; j++) {
            sameCards = 1;
            V2 = 0;
            if(i == j) {
                V2++;
                sameCards = 0.5;
            }
            VS2 = 0;
            for(secondAliceCounter = 6; secondAliceCounter >= 0; secondAliceCounter--) {
                if(Alice[secondAliceCounter] / 10 == j) {
                    if(Alice[secondAliceCounter] % 10 != specialSuit) {
                        V2++;
                    } else {
                        VS2++;
                    }
                }
            }
            addTwoValues(5, i * 10 + 4, j * 10 + 4, table, Bob);
            WLDcounter[computeWinner(AliceAnalyze, AliceHand, Bob)] += (3 - V1) * (3 - V2) * sameCards; //computes how many cases covers each of above described cases
            if(i != j) {
                addTwoValues(5, i * 10 + specialSuit, j * 10 + 4, table, Bob);
                WLDcounter[computeWinner(AliceAnalyze, AliceHand, Bob)] += (1 - VS1) * (3 - V2);
                addTwoValues(5, i * 10 + specialSuit, j * 10 + specialSuit, table, Bob);


                WLDcounter[computeWinner(AliceAnalyze, AliceHand, Bob)] += (1 - VS1) * (1 - VS2);
            }
            addTwoValues(5, i * 10 + 4, j * 10 + specialSuit, table, Bob);
            WLDcounter[computeWinner(AliceAnalyze, AliceHand, Bob)] += (3 - V1) * (1 - VS2);
        }
    }
}

void computePotForThreeSpecialCards(int Alice[7], int table[5], combination AliceAnalyze, int AliceHand[5], int specialSuit, double WLDcounter[3]){
    int V1, V2, VS1, VS2;
    int firstAliceCounter = 6, secondAliceCounter;
    int Bob[7];
    double sameCards;
    enum results winner;

    for(int i = 2; i < 15; i++) {
        V1 = 0;
        VS1 = 0;
        while((Alice[firstAliceCounter] / 10 == i) && (firstAliceCounter >= 0)) {
            if(Alice[firstAliceCounter] % 10 != specialSuit) {
                V1++;
            } else {
                VS1++;
            }
            firstAliceCounter--;
        }
        for(int j = i; j < 15; j++) {
            V2 = 0;
            sameCards = 1;
            if(i == j) {
                V2++;
                sameCards = 0.5;
            }
            VS2 = 0;
            for(secondAliceCounter = 6; secondAliceCounter >= 0; secondAliceCounter--) {
                if(Alice[secondAliceCounter] / 10 == j) {
                    if(Alice[secondAliceCounter] % 10 != specialSuit) {
                        V2++;
                    } else {
                        VS2++;
                    }
                }
            }
            addTwoValues(5, i * 10 + 4, j * 10 + 4, table, Bob);
            winner = computeWinner(AliceAnalyze, AliceHand, Bob);
            WLDcounter[winner] += (3 - V1) * (3 - V2) * sameCards;          //computes how many cases covers each of above described cases
            if(i != j) {
                WLDcounter[winner] += (1 - VS1) * (3 - V2);
                addTwoValues(5, i * 10 + specialSuit, j * 10 + specialSuit, table, Bob);
                WLDcounter[computeWinner(AliceAnalyze, AliceHand, Bob)] += (1 - VS1) * (1 - VS2);
            }
            WLDcounter[winner] += (3 - V1) * (1 - VS2);
        }
    }
}

void computePotForNoSpecialCards(int Alice[7], int table[5], combination AliceAnalyze, int AliceHand[5],  double WLDcounter[3]){
    int V1, V2;
    int firstAliceCounter = 6, secondAliceCounter;
    int Bob[7];
    double sameCards;

    for(int i = 2; i < 15; i++) {                                   //all cases have no difference with respect to suit
        V1 = 0;
        while((Alice[firstAliceCounter] / 10 == i) && (firstAliceCounter >= 0)) {
            V1++;
            firstAliceCounter--;
        }
        for(int j = i; j < 15; j++) {
            sameCards = 1;
            V2 = 0;
            if(i == j) {
                V2++;
                sameCards = 0.5;
            }
            for(secondAliceCounter = 6; secondAliceCounter >= 0; secondAliceCounter--) {
                if(Alice[secondAliceCounter] / 10 == j) {
                    V2++;
                }
            }
            addTwoValues(5, i * 10 + 4, j * 10 + 4, table, Bob);
            WLDcounter[computeWinner(AliceAnalyze, AliceHand, Bob)] += (4 - V1) * (4 - V2) * sameCards;
        }
    }
}

/**
 * @brief computeWinner computes who wins
 * @param Alice
 * @param Bob
 * @return  0 if Alice wins,
 *          1 if Alice loses,
 *          2 if draw happens
 */
int computeWinner(int AliceAnalyze, int AliceHand[5], int Bob[7]){
    int hand2[5], res2, result;

    if(isAce(Bob[0]))
        res2 = analyzeWithAce(Bob, hand2);
    else
        res2 = analyze(Bob, hand2);
    result = AliceAnalyze - res2;
    if(result > 0) {
        return WINS;
    }
    if(result < 0) {
        return LOSES;
    }
    for(size_t i = 0; i < 5; i++) {
        if(AliceHand[i] / 10 > hand2[i] / 10) {
            return 0;
        }
        if(AliceHand[i] / 10 < hand2[i] / 10) {
            return 1;
        }
    }
    return DRAWS;
}

/**
 * @brief isStraightFlush determines whether our card is begin of straight flush
 * @param val set of cards
 * @param index index of our card
 * @return true if so
 */
bool isStraightFlush(int val[7], size_t index){
    int value = val[index];
    int straightCards = 1;
    bool isNextStraight;
    do{
        isNextStraight = false;
        for(size_t i = index + 1; i < 7; i++){
            if(val[i] == value - 10 * straightCards){
                straightCards++;
                isNextStraight = true;
            }
        }
    } while(isNextStraight);
    return straightCards >= 5 ? true : false;
}

/**
 * @brief isStraightFlush determines whether our card is begin of straight
 * @param val set of cards
 * @param index index of our card
 * @return true if so
 */
bool isStraight(int val[7], size_t index){
    int value = val[index];
    int straightCards = 1;
    bool isNextStraight;
    do{
        isNextStraight = false;
        for(size_t i = index + 1; i < 7; i++){
            if(val[i] / 10 == value / 10 - straightCards){
                straightCards++;
                isNextStraight = true;
            }
        }
    } while(isNextStraight);
    return straightCards >= 5 ? true : false;
}

/**
 * @brief sameValueCards returns number of cards in the set with the same number as our card
 * @param val set of cards
 * @param index of our card
 * @return number of cards
 */
int sameValueCards(int val[7], int index) {
    int value = val[index] / 10;
    int count = 1;
    for(size_t i = index + 1; i < 7; i++){
        if(val[i] / 10 == value)
            count++;
    }
    return count;
}

// These method tests combinations (from pair to straight flush)

bool testPair(int val[7], int hand[5]) {
    for(size_t j = 0; j < 6; j++) {
        if(val[j] / 10 == val[j + 1] / 10) {
            hand[0] = val[j];
            hand[1] = val[j + 1];
            hand[2] = j < 1 ? val[2] : val[0];
            hand[3] = j < 2 ? val[3] : val[1];
            hand[4] = j < 3 ? val[4] : val[2];
            return true;
        }
    }
    return false;
}

bool testTwoPairs(int val[7], int hand[5]) {
    for(size_t j = 0; j < 6; j++) {
        if(val[j] / 10 == val[j + 1] / 10) {
            for(size_t i = j + 2; i < 6; i++){
                if(val[i] / 10 == val[i + 1] / 10){
                    hand[0] = val[j];
                    hand[1] = val[j + 1];
                    hand[2] = val[i];
                    hand[3] = val[i + 1];
                    size_t k = 0;
                    while((k == j) || (k == j + 1) || (k == i) || (k == i + 1)){
                        k++;
                    }
                    hand[4] = val[k];
                    return true;
                }
            }
        }
    }
    return false;
}

bool testTriple(int val[7], int hand[5]) {
    for(size_t j = 0; j < 5; j++) {
        if(sameValueCards(val, j) == 3) {
            hand[0] = val[j];
            hand[1] = val[j + 1];
            hand[2] = val[j + 2];
            hand[3] = j == 0 ? val[3] : val[0];
            hand[4] = j < 2 ? val[4] : val[1];
            return true;
        }
    }
    return false;
}

bool testStraight(int val[7], int hand[5]) {
    for(size_t j = 0; j < 3; j++) {
        if(isStraight(val, j)) {
            hand[0] = val[j];
            for(size_t i = 1; i < 5; i++) {
                hand[i] = val[j] - i * 10;
            }
            return true;
        }
    }
    return false;
}

bool testFlush(int val[7], int hand[5]) {
    int suit, count, k = 1;
    for(size_t i = 0; i < 3; i++){
        count = 1;
        suit = val[i] % 10;
        for(size_t j = i + 1; j < 7; j++){
            if(val[j] % 10 == suit){
                count++;
            }
        }
        if(count >= 5) {
            hand[0] = val[i];
            for(size_t j = i + 1; k < 5; j++){
                if(val[j] % 10 == suit){
                    hand[k] = val[j];
                    k++;
                }
            }
            return true;
        }
    }
    return false;
}

bool testFullHouse(int val[7], int hand[5]) {
    for(size_t i = 0; i < 5; i++) {
        if(sameValueCards(val, i) == 3) {
            for(size_t j = 0; j < 6; j++) {
                if((i != j) && (i + 1 != j))
                    if(sameValueCards(val, j) == 2) {
                        hand[0] = val[i];
                        hand[1] = val[i + 1];
                        hand[2] = val[i + 2];
                        hand[3] = val[j];
                        hand[4] = val[j + 1];
                        return true;
                    }
            }
        }
    }
    return false;
}

bool testPoker(int val[7], int hand[5]){
    for(size_t i = 0; i < 4; i++) {
        if(sameValueCards(val, i) == 4) {
            for(size_t j = 0; j < 4; j++) {
                hand[j] = val[j + i];
            }
            hand[4] = i == 0 ? val[4] : val[0];
            return true;
        }
    }
    return false;
}

bool testStraightFlush(int val[7], int hand[5]) {
    for(size_t j = 0; j < 3; j++) {
        if(isStraightFlush(val, j)) {
            hand[0] = val[j];
            for(size_t i = 1; i < 5; i++) {
                hand[i] = val[j] - i * 10;
            }
            return true;
        }
    }
    return false;
}

/**
 * @brief analyze looks for combinations
 * @param val set of seven cards
 * @param hand five chosen cards with best combination
 * @return level of combination (pair - 2, ..., straight flush - 9)
 */
int analyze(int val[7], int hand[5]) {
    if(testStraightFlush(val, hand))
        return STRAIGHT_FLUSH;

    if(testPoker(val, hand))
        return FOUR_OF_A_KIND;

    if(testFullHouse(val, hand))
        return FULL_HOUSE;

    if(testFlush(val, hand))
        return FLUSH;

    if(testStraight(val, hand))
        return STRAIGHT;

    if(testTriple(val, hand))
        return THREE_OF_A_KIND;

    if(testTwoPairs(val, hand))
        return TWO_PAIRS;

    if(testPair(val, hand))
        return PAIR;

    for(size_t i = 0; i < 5; i++){
        hand[i] = val[i];
    }
    return HIGH_CARD;
}

/**
 * @brief analyzeWithAce moves possible aces at the edn as the lowest cards and tries another analyze
 * @param val set of cards
 * @param hand five chosen cards
 * @return better analyze
 */
int analyzeWithAce(int val[7], int hand[5]) {
    int acedVal[7], acedResult, result;
    size_t numberOfAces = 0;

    while(isAce(val[numberOfAces])) {
        numberOfAces++;
    }
    for(size_t i = 0; i < 7 - numberOfAces; i++){
        acedVal[i] = val[i + numberOfAces];
    }
    for(size_t i = 0; i < numberOfAces; i++){
        acedVal[7 - numberOfAces + i] = val[i] - 130;
    }
    acedResult = analyze(acedVal, hand);
    if (((acedResult == STRAIGHT) || (acedResult == STRAIGHT_FLUSH)) && (hand[4] / 10 == 1)) {
        return acedResult;
    }
    result = analyze(val, hand);
    return result;
}
