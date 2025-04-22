// === Region: Project Declaration ===
//
//  COMP2011 Spring 2025
//  PA1: Monster Game
//
//  Your name:WEN, Zhengtao
//  Your ITSC email:zwenao@connect.ust.hk
//
//  Note: Generative AI is NOT allowed in completing your lab exercises or programming assignments
//  Reference: https://course.cse.ust.hk/comp2011/web/code.html
//
//  Declaration:
//  I declare that I am not involved in plagiarism
//  I understand that both parties (i.e., students providing the codes and students copying the codes) will receive 0 marks.
//
//  Project TA: Peter CHUNG (cspeter@cse.ust.hk)
//
//  For code-level questions, please send a direct email to the above TA.
//  Asking questions with code blocks in a public discussion forum (e.g., Piazza) may cause plagiarism issues
//  Usually, you will get the quickest response via a direct email.
//
// =====================================


/* void handleActionDuel
 * @param aliceMonsterType: an array storing the monster types of Alice
 * @param aliceMonsterPower: an array storing the monster powers of alice
 * @param bobMonsterType: an array storing the monster types of Bob
 * @param bobMonsterPower: an array storing the monster powers of Bob
 * @param aliceIndex: The chosen monster index for Alice
 * @param bobIndex: The chosen monster index for Bob
 *
 * In this function, we have some return values and they are pass-by-reference
 *
 * @return alicePoint: The updated point for Alice
 * @return bobPoint: The updated point for bob
 *
 * @return a suitable ActionStatus (see the provided enum)
 */
ActionStatus handleActionDuel(const char aliceMonsterType[MAX_NUM_MONSTERS],
                              const char aliceMonsterPower[MAX_NUM_MONSTERS],
                              const char bobMonsterType[MAX_NUM_MONSTERS],
                              const char bobMonsterPower[MAX_NUM_MONSTERS],
                              int aliceIndex,
                              int bobIndex,
                              int &alicePoint,
                              int &bobPoint)
{//initialize the power of alice and bob.
    int tempAlicePower = (static_cast<int>(aliceMonsterPower[aliceIndex]))-(static_cast<int>('0'));
    int tempBobPower = (static_cast<int>(bobMonsterPower[bobIndex]))-(static_cast<int>('0'));

    //set a enum for the monster type, and use later in switch case. ENUM used because more readable
    enum Monstertypeinduel{
        F = 0,
        I = 1,
        W = 2
    };

    //Store all monster types to the enum types. 
    //step 1: create an array to store the enum type of the monster type.
    Monstertypeinduel aliceMonsterTypeinEnum[MAX_NUM_MONSTERS];
    Monstertypeinduel bobMonsterTypeinEnum[MAX_NUM_MONSTERS];
    //step 2: translate the monster type to the enum type.
    //ALICE one
    for(int i = 0; i < MAX_NUM_MONSTERS; i++){
        if (aliceMonsterType[i] == 'F'){
            aliceMonsterTypeinEnum[i] = F;
        }
        else if(aliceMonsterType[i] == 'I'){
            aliceMonsterTypeinEnum[i] = I;
        }
        else if(aliceMonsterType[i] == 'W'){
            aliceMonsterTypeinEnum[i] = W;
        }
    }
    //BOB one
    for(int j = 0; j < MAX_NUM_MONSTERS; j++){
        if (bobMonsterType[j] == 'F'){
            bobMonsterTypeinEnum[j] = F;
        }
        else if(bobMonsterType[j] == 'I'){
            bobMonsterTypeinEnum[j] = I;
        }
        else if(bobMonsterType[j] == 'W'){
            bobMonsterTypeinEnum[j] = W;
        }
    }

    //switch case to determine the additional advantage of the monster type during the duel.
    switch(aliceMonsterTypeinEnum[aliceIndex])
    {
        case F:
            if(bobMonsterTypeinEnum[bobIndex] == I)
            {
                tempAlicePower += MONSTER_TYPE_ADVANTAGE;
            }
            else if(bobMonsterTypeinEnum[bobIndex] == W)
            {
                tempBobPower += MONSTER_TYPE_ADVANTAGE;
            }
            break;
        case I:
            if(bobMonsterTypeinEnum[bobIndex] == W)
            {
                tempAlicePower += MONSTER_TYPE_ADVANTAGE;
            }
            else if(bobMonsterTypeinEnum[bobIndex] == F)
            {
                tempBobPower += MONSTER_TYPE_ADVANTAGE;
            }
            break;
        case W:
            if(bobMonsterTypeinEnum[bobIndex] == F)
            {
                tempAlicePower += MONSTER_TYPE_ADVANTAGE;
            }
            else if(bobMonsterTypeinEnum[bobIndex] == I)
            {
                tempBobPower += MONSTER_TYPE_ADVANTAGE;
            }
            break;
    }
    // compare the power of alice and bob, and update the resluts.
    int temp_result = (tempAlicePower > tempBobPower)? 1: (tempAlicePower == tempBobPower)? 2: 3;
    switch(temp_result)
    {
        case 1:
            alicePoint += 3;
            return ACTION_STATUS_ALICE_WIN;
        case 2:
            alicePoint += 1;
            bobPoint += 1;
            return ACTION_STATUS_DRAW;
        case 3:
            bobPoint += 3;
            return ACTION_STATUS_BOB_WIN;
    }
}


/* void handleActionBattle
 * @param numMonsters: The number of monsters
 * @param aliceMonsterType: an array storing the monster types of Alice
 * @param aliceMonsterPower: an array storing the monster powers of alice
 * @param bobMonsterType: an array storing the monster types of Bob
 * @param bobMonsterPower: an array storing the monster powers of Bob
 *
 * In this function, we have some return values and they are pass-by-reference
 *
 * @return alicePoint: The updated point for Alice
 * @return bobPoint: The updated point for bob
 * @return countAliceWin: The number of wins for Alice
 * @return countBobWin: The number of wins for Bob
 * @return countDraw: The number of draws
 *
 * @return a suitable ActionStatus (see the provided enum).
 * Alice wins if Alice's totalPointChange > Bob's totalPointChange.
 * Draws if they are equal, otherwise, Bob wins.
 */
ActionStatus handleActionBattle(int numMonsters,
                                const char aliceMonsterType[MAX_NUM_MONSTERS],
                                const char aliceMonsterPower[MAX_NUM_MONSTERS],
                                const char bobMonsterType[MAX_NUM_MONSTERS],
                                const char bobMonsterPower[MAX_NUM_MONSTERS],
                                int &alicePoint,
                                int &bobPoint,
                                int &countAliceWin,
                                int &countBobWin,
                                int &countDraw)
{
    //JUST REAPETING  DUEL
    const int tempalicePoint = alicePoint;
    const int tempbobPoint = bobPoint;

    for(int i = 0; i < numMonsters; i++){
        ActionStatus temp = handleActionDuel(aliceMonsterType, aliceMonsterPower, bobMonsterType, bobMonsterPower, i, i, alicePoint, bobPoint);
        if(temp == ACTION_STATUS_ALICE_WIN){
            countAliceWin++;
        }
        else if(temp == ACTION_STATUS_BOB_WIN){
            countBobWin++;
        }
        else{
            countDraw++;
        }
    
    
    }

    int return_state = ((alicePoint-tempalicePoint)>(bobPoint-tempbobPoint))? 1: ((alicePoint-tempalicePoint) == (bobPoint-tempbobPoint))? 2: 3;
    if (return_state == 1){
        return ACTION_STATUS_ALICE_WIN; 
    }
    else if (return_state == 2){
        return ACTION_STATUS_DRAW;
    }
    else{
        return ACTION_STATUS_BOB_WIN;
    }
}

/* void handleActionMiniBattle
 * @param numMonstersForMiniBattle: The number of monsters for mini battle
 * @param aliceMonsterType: an array storing the monster types of Alice
 * @param aliceMonsterPower: an array storing the monster powers of alice
 * @param bobMonsterType: an array storing the monster types of Bob
 * @param bobMonsterPower: an array storing the monster powers of Bob
 *
 * In this function, we have some return values and they are pass-by-reference
 *
 * @return alicePoint: The updated point for Alice
 * @return bobPoint: The updated point for bob
 * @return countAliceWin: The number of wins for Alice
 * @return countBobWin: The number of wins for Bob
 * @return countDraw: The number of draws
 *
 * @return a suitable ActionStatus (see the provided enum).
 * Alice wins if Alice's totalPointChange > Bob's totalPointChange.
 * Draws if they are equal, otherwise, Bob wins.
 */
ActionStatus handleActionMiniBattle(int numMonstersForMiniBattle,
                                    const char aliceMonsterType[MAX_NUM_MONSTERS],
                                    const char aliceMonsterPower[MAX_NUM_MONSTERS],
                                    const char bobMonsterType[MAX_NUM_MONSTERS],
                                    const char bobMonsterPower[MAX_NUM_MONSTERS],
                                    const int aliceMiniBattleIndices[MAX_NUM_MONSTERS],
                                    const int bobMiniBattleIndices[MAX_NUM_MONSTERS],
                                    int &alicePoint,
                                    int &bobPoint,
                                    int &countAliceWin,
                                    int &countBobWin,
                                    int &countDraw)
{
     // TODO: Implement handleActionMiniBattle

    int tempalicePoint = alicePoint;
    int tempbobPoint = bobPoint;

    
    for(int i = 0; i < numMonstersForMiniBattle; i++){
        ActionStatus temp = handleActionDuel(aliceMonsterType, aliceMonsterPower, bobMonsterType, bobMonsterPower, aliceMiniBattleIndices[i], bobMiniBattleIndices[i], alicePoint, bobPoint);
        if(temp == ACTION_STATUS_ALICE_WIN){
            countAliceWin++;
        }
        else if(temp == ACTION_STATUS_BOB_WIN){
            countBobWin++;
        }
        else{
            countDraw++;
        }
    }
    
    int return_state = ((alicePoint-tempalicePoint)>(bobPoint-tempbobPoint))? 1: ((alicePoint-tempalicePoint) == (bobPoint-tempbobPoint))? 2: 3;
    if (return_state == 1){
        return ACTION_STATUS_ALICE_WIN; 
    }
    else if (return_state == 2){
        return ACTION_STATUS_DRAW;
    }
    else{
        return ACTION_STATUS_BOB_WIN;
    }
}

/* void handleActionReorder
 * @param numMonsters: The number of monsters 
 * @param monsterType: an array storing the monster types (array content should be reordered after this function)
 * @param monsterPower: an array storing the monster powers  (array content should be reordered after this function)
 * @param reorderIndices: The reorder indices
 *
 * No return value for this function
 */
void handleActionRecorder(int numMonsters,
                          char monsterType[MAX_NUM_MONSTERS],
                          char monsterPower[MAX_NUM_MONSTERS],
                          const int reorderIndices[MAX_NUM_MONSTERS])
{   
    //make a temp copy of the original arrary
    char tempmonsterType[MAX_NUM_MONSTERS];
    char tempmonsterPower[MAX_NUM_MONSTERS];
    for(int i = 0; i < numMonsters; i++){
        tempmonsterType[i] = monsterType[i];
        tempmonsterPower[i] = monsterPower[i];
    }
    //reorder
    for(int j = 0; j < numMonsters; j++){
        monsterType[j] = tempmonsterType[reorderIndices[j]];
        monsterPower[j] = tempmonsterPower[reorderIndices[j]];
    }
}
