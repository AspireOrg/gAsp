// Copyright (c) 2022 The Aspire devlopers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "internal_miner.h"

// forward declarations
bool ShutdownRequested();
UniValue generateBlocks(boost::shared_ptr<CReserveScript> coinbaseScript, int nGenerate, uint64_t nMaxTries, bool keepScript);

bool isMempoolPopulated()
{
    LOCK(mempool.cs);
    unsigned int pendingTx = mempool.mapTx.size() - 1;
    return !pendingTx;
}

unsigned int secSinceLastblock()
{
    const CBlockIndex *pindex = chainActive.Tip();
    return GetAdjustedTime() - pindex->nTime;
}

void ThreadGaspMiner()
{
    boost::shared_ptr<CReserveScript> coinbaseScript;
    GetMainSignals().ScriptForMining(coinbaseScript);

    while (true) {

        bool pendingMempool = isMempoolPopulated();
        unsigned int elapsedBlock = secSinceLastblock();

        LogPrintf("pendingMempool %d elapsedblock %d\n", pendingMempool, elapsedBlock);

        if (ShutdownRequested()) {
            break;
        }

        bool shouldMine = (elapsedBlock > EMPTYMEMPOOL) || (pendingMempool && (elapsedBlock > POPULATEDMEMPOOL));

        if (shouldMine) {
            generateBlocks(coinbaseScript, 1, 0xffffff, true);
        }

        MilliSleep(3000);
    }
}
