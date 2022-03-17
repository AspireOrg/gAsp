// Copyright (c) 2022 The Aspire devlopers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef INTERNAL_MINER_H
#define INTERNAL_MINER_H

#include "miner.h"
#include "timedata.h"
#include "txmempool.h"
#include "validation.h"
#include "validationinterface.h"

#include <univalue.h>

// delay settings for miner
const int EMPTYMEMPOOL = 90;
const int POPULATEDMEMPOOL = 15;

void ThreadGaspMiner();

#endif // INTERNAL_MINER_H
