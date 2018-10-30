// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "pow.h"

#include "arith_uint256.h"
#include "chain.h"
#include "consensus/consensus.h"
#include "primitives/block.h"
#include "uint256.h"



static const int64_t nTargetSpacing = 10 * 60; // placeh 10 minutes between block

unsigned int static DarkGravityWave3(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params) {
    /* current difficulty formula, darkcoin - DarkGravity v3, written by Evan Duffield - evan@darkcoin.io */
    const CBlockIndex *BlockLastSolved = pindexLast;
    const CBlockIndex *BlockReading = pindexLast;
    const CBlockHeader *BlockCreating = pblock;
    BlockCreating = BlockCreating;
    int64_t nActualTimespan = 0;
    int64_t LastBlockTime = 0;
    int64_t PastBlocksMin = 24;
    int64_t PastBlocksMax = 24;
    int64_t CountBlocks = 0;
    arith_uint256 PastDifficultyAverage;
    arith_uint256 PastDifficultyAveragePrev;

	unsigned int bnProofOfWorkLimit = UintToArith256(params.powLimit).GetCompact();
	
	
	
    if (BlockLastSolved == NULL || BlockLastSolved->nHeight == 0 || BlockLastSolved->nHeight < PastBlocksMin) {
        // This is the first block or the height is < PastBlocksMin
        // Return minimal required work. (1e0fffff)
        return bnProofOfWorkLimit;//.GetCompact(); 
    }
    
    // loop over the past n blocks, where n == PastBlocksMax
    for (unsigned int i = 1; BlockReading && BlockReading->nHeight > 0; i++) {
        if (PastBlocksMax > 0 && i > PastBlocksMax) { break; }
        CountBlocks++;

        // Calculate average difficulty based on the blocks we iterate over in this for loop
        if(CountBlocks <= PastBlocksMin) {
            if (CountBlocks == 1) { PastDifficultyAverage.SetCompact(BlockReading->nBits); }
            else { PastDifficultyAverage = ((PastDifficultyAveragePrev * CountBlocks)+(arith_uint256().SetCompact(BlockReading->nBits))) / (CountBlocks+1); }
            PastDifficultyAveragePrev = PastDifficultyAverage;
        }

        // If this is the second iteration (LastBlockTime was set)
        if(LastBlockTime > 0){
            // Calculate time difference between previous block and current block
            int64_t Diff = (LastBlockTime - BlockReading->GetBlockTime());
            // Increment the actual timespan
            nActualTimespan += Diff;
        }
        // Set LastBlockTime to the block time for the block in current iteration
        LastBlockTime = BlockReading->GetBlockTime();      

        if (BlockReading->pprev == NULL) { assert(BlockReading); break; }
        BlockReading = BlockReading->pprev;
    }
    
    // bnNew is the difficulty
    arith_uint256 bnNew(PastDifficultyAverage);

    // nTargetTimespan is the time that the CountBlocks should have taken to be generated.
    int64_t nTargetTimespan = CountBlocks*nTargetSpacing;

    // Limit the re-adjustment to 3x or 0.33x
    // We don't want to increase/decrease diff too much.
    if (nActualTimespan < nTargetTimespan/3)
        nActualTimespan = nTargetTimespan/3;
    if (nActualTimespan > nTargetTimespan*3)
        nActualTimespan = nTargetTimespan*3;

    // Calculate the new difficulty based on actual and target timespan.
    bnNew *= nActualTimespan;
    bnNew /= nTargetTimespan;

    // If calculated difficulty is lower than the minimal diff, set the new difficulty to be the minimal diff.
    if (bnNew > bnProofOfWorkLimit){
        bnNew = bnProofOfWorkLimit;
    }
    
    // Some logging.
    // TODO: only display these log messages for a certain debug option.
    printf("Difficulty Retarget - Dark Gravity Wave 3\n");
    printf("Before: %08x %s\n", BlockLastSolved->nBits, arith_uint256().SetCompact(BlockLastSolved->nBits).ToString().c_str());
    printf("After: %08x %s\n", bnNew.GetCompact(), bnNew.ToString().c_str());

    // Return the new diff.
    return bnNew.GetCompact();
}

bool IsDGWActive(unsigned int nBlockNumber) {
    return nBlockNumber >= 39500;
}

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader* pblock, const Consensus::Params& params)
{
    assert(pindexLast != nullptr);
    unsigned int nProofOfWorkLimit = UintToArith256(params.powLimit).GetCompact();

    // Difficulty changes to 1 on fork block, so that nBits of block
    // [fork height] + 1 is minimum difficulty. We keep returning this for
    // one full difficulty adjustment interval, and then let the system handle
    // the difficulty adjustments as normal.
    if (pindexLast->nHeight >= FORK_BLOCK &&
        pindexLast->nHeight <= FORK_BLOCK + params.DifficultyAdjustmentInterval()) {
        return nProofOfWorkLimit;
    }

	// IS DGW active?
	if(isDGWActive(pindexLast->nHeight)) {
		return DarkGravityWave3( pindexLast, pblock, params );
	} 
	
    // Only change once per difficulty adjustment interval
    if ((pindexLast->nHeight + 1) % params.DifficultyAdjustmentInterval() != 0) {
        if (params.fPowAllowMinDifficultyBlocks) {
            // Special difficulty rule for testnet:
            // If the new block's timestamp is more than 2* 10 minutes
            // then allow mining of a min-difficulty block.
            if (pblock->GetBlockTime() > pindexLast->GetBlockTime() + params.nPowTargetSpacing * 2)
                return nProofOfWorkLimit;
            else {
                // Return the last non-special-min-difficulty-rules-block
                const CBlockIndex* pindex = pindexLast;
                while (pindex->pprev && pindex->nHeight % params.DifficultyAdjustmentInterval() != 0 && pindex->nBits == nProofOfWorkLimit)
                    pindex = pindex->pprev;
                return pindex->nBits;
            }
        }
        return pindexLast->nBits;
    }

    // Go back by what we want to be 14 days worth of blocks
    int nHeightFirst = pindexLast->nHeight - (params.DifficultyAdjustmentInterval() - 1);
    assert(nHeightFirst >= 0);
    const CBlockIndex* pindexFirst = pindexLast->GetAncestor(nHeightFirst);
    assert(pindexFirst);

    return CalculateNextWorkRequired(pindexLast, pindexFirst->GetBlockTime(), params);
}

unsigned int CalculateNextWorkRequired(const CBlockIndex* pindexLast, int64_t nFirstBlockTime, const Consensus::Params& params)
{
    if (params.fPowNoRetargeting)
        return pindexLast->nBits;

    // Limit adjustment step
    int64_t nActualTimespan = pindexLast->GetBlockTime() - nFirstBlockTime;
	  
	
	
    if (nActualTimespan < params.nPowTargetTimespan / 4)
        nActualTimespan = params.nPowTargetTimespan / 4;
    if (nActualTimespan > params.nPowTargetTimespan * 4)
        nActualTimespan = params.nPowTargetTimespan * 4;

    // Retarget
    const arith_uint256 bnPowLimit = UintToArith256(params.powLimit);
    arith_uint256 bnNew;
    bnNew.SetCompact(pindexLast->nBits);
    bnNew *= nActualTimespan;
    bnNew /= params.nPowTargetTimespan;

    if (bnNew > bnPowLimit)
        bnNew = bnPowLimit;

    return bnNew.GetCompact();
}

bool CheckProofOfWork(uint256 hash, unsigned int nBits, const Consensus::Params& params, uint256* best)
{
    bool fNegative;
    bool fOverflow;
    arith_uint256 bnTarget;

    bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

    // Check range
    if (fNegative || bnTarget == 0 || fOverflow || bnTarget > UintToArith256(params.powLimit))
        return false;

    // Check proof of work matches claimed amount
    if (UintToArith256(hash) > bnTarget) {
        if (best && (*best == uint256() || UintToArith256(*best) > UintToArith256(hash))) {
            *best = hash;
            printf("- new best:\n\t%s\nvs\t%s\n", hash.ToString().c_str(), ArithToUint256(bnTarget).ToString().c_str());
        }
        return false;
    }

    return true;
}
