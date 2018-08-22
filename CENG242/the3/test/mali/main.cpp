#include <iostream>
#include "Koin.h"
#include "Blockchain.h"
#include "Miner.h"

using namespace std;

void testBlockchain() {
    cout << "-------------------------------------------" << endl;
    cout << "--------- STARTING BLOCKCHAIN TEST --------" << endl;
    cout << "-------------------------------------------" << endl;
    
    // Phase 1 : Constructor
    
    Blockchain blockchain1(1);
    Blockchain blockchain2(2);
    
    Koin *head1 = blockchain1.getHead();
    Koin *head2 = blockchain2.getHead();
    
    Koin *head3 = new Koin(0.5);
    
    Blockchain blockchain3(3, head3);
    
    Koin *actualHead3 = blockchain3.getHead();
    
    cout << blockchain3 << endl;
    
    // Phase 2 : Copy Constructor
    
    Blockchain blockchain4(blockchain3);
    
    cout << "Copy Constructor : " << blockchain4 << endl;

    // Phase 3 : Move
    
    Blockchain blockchain5(blockchain4);
    
    cout << "After Copy Constructor B5 is : " << blockchain5 << endl;
    
    blockchain5 = std::move(blockchain3);
    
    cout << "After Move Constructor B5 is : " << blockchain5 << endl;
    
    // Phase 4 : Operations
    
    cout << "Starting operations on B1 : " << endl;
    
    int koinCount = 10;
    
    for(int i = 0; i < koinCount; i++) {
        ++blockchain1;
    }
    
    cout << blockchain1 << endl;
    
    double actualValue = 6.0434;
    
    blockchain1 *= 10;
    
    cout << blockchain1 << endl;
    
    blockchain1 /= 10;

    cout << blockchain1 << endl;
    
    for(int i = 0; i < 100; i++) {
        --blockchain1;
    }
    
    cout << blockchain1 << endl;
    
    int chainLength = blockchain1.getChainLength();
    
    cout << "Chain length is : " << chainLength << endl;

    cout << "-------------------------------------------" << endl;
    cout << "---------- END OF BLOCKCHAIN TEST ---------" << endl;
    cout << "-------------------------------------------" << endl;

}



void testMiner() {
    
    cout << "-------------------------------------------" << endl;
    cout << "----------- STARTING MINER TEST -----------" << endl;
    cout << "-------------------------------------------" << endl;
    
    // Phase 1 : Creating New Blockchain
    
    Miner btcMiner = Miner("ugur");
    
    int blockchainToCreate = 5;
    
    for (int i = 0; i < blockchainToCreate; i++) {
        btcMiner.createNewBlockchain();
    }
    
    cout << "Chain count : " << btcMiner.getBlockchainCount() << endl;
    
    // Phase 2 : Indexing
    
    for (int i = 0; i < blockchainToCreate; i++) {
        Blockchain *createdBlockchain = btcMiner[i];
    }
    
    Blockchain *shouldBeNull = btcMiner[blockchainToCreate + 1];
    
    cout << "Should be null : " << shouldBeNull << endl;
    
    // Phase 3 : Mine/Demine
    
    int mineCount = 100;
    int demineCount = 50;
    
    btcMiner.mineUntil(100);
    
    for (int i = 0; i < blockchainToCreate; i++) {
        Blockchain *blockchain = btcMiner[i];
    }
    
    btcMiner.demineUntil(demineCount);
    
    cout << btcMiner << endl;
    
    // Phase 4 : Soft Fork
    
    Miner antMiner = Miner("ANTMiner");
    antMiner.createNewBlockchain();
    antMiner.mineUntil(1);
    antMiner.softFork(0);
    antMiner.softFork(1);
    antMiner.softFork(2);
    antMiner.mineUntil(1);
    antMiner.softFork(3);
    antMiner.softFork(4);
    antMiner.softFork(5);
    antMiner.mineUntil(1);
    
    cout << "Soft Fork half point " << endl << antMiner << endl;
    
    antMiner.softFork(6);
    antMiner.softFork(6);
    antMiner.softFork(6);
    antMiner.mineUntil(1);
    antMiner.softFork(7);
    antMiner.mineUntil(1);
    antMiner.softFork(8);
    antMiner.mineUntil(1);
    antMiner.softFork(9);
    antMiner.mineUntil(1);
    antMiner.mineUntil(10);
    
    cout << "Soft fork 0.75 " << endl << antMiner << endl;
    
    antMiner.mineUntil(1);
    antMiner.softFork(0);
    antMiner.softFork(1);
    antMiner.softFork(2);
    antMiner.mineUntil(1);
    antMiner.softFork(3);
    antMiner.softFork(4);
    antMiner.softFork(5);
    antMiner.mineUntil(10);
    
    cout << "Soft fork end point " << endl << antMiner << endl;
    
    antMiner.demineUntil(10);
    
    cout << "Soft fork end point " << endl << antMiner << endl;
    
    // Phase 5 : Hard Fork
    
    Miner ethMiner = Miner("ETHMiner");
    ethMiner.createNewBlockchain(); // Pure blockchain
    ethMiner.mineUntil(1);
    
    int blockchainCountToCreate = 10;
    
    for(int i = 0; i < blockchainCountToCreate - 2; i++) {
        ethMiner.mineUntil(1);
        ethMiner.hardFork(i);
    }
    
    ethMiner.createNewBlockchain(); // Empty blockchain
    
    cout << ethMiner << endl;
    
    ethMiner.mineUntil(50);
    
    
    cout << ethMiner << endl;
    
    cout << "-------------------------------------------" << endl;
    cout << "------------- END OF MINER TEST -----------" << endl;
    cout << "-------------------------------------------" << endl;
    
}

int main() {
    
    testBlockchain();
    testMiner();
    
    return 0;
}
