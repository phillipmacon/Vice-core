// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Vice developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0,      uint256("0x00000f186512642b3b8be1cd906df8b81028d58cfa7350fc123bc89b1644846e"))
    ;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1544696361, // * UNIX timestamp of last checkpoint block
    1130,       // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x0000063d69bab1632ede3c7195b6d9d82cc7a2dabf41c5f0663196e3524391ab"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1544536801,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256("0x0000082b6e9f62cfc2a54f5bb895f4d85f2a436f24069cfe202e8a75f4f5a6ea"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1544536802,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x72;
        pchMessageStart[1] = 0x65;
        pchMessageStart[2] = 0x6d;
        pchMessageStart[3] = 0x73;
        vAlertPubKey = ParseHex("0415eaa985ce836a004bb1b36b3c8a04aad00d19714e0aae1de1b21966e47e7af327dfafda895d60ac90dbb1ac4cc1c464b9680b4b902c1bfa0d2eab8064174684");
        nDefaultPort = 8933;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nSubsidyHalvingInterval = 1050000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Vice: 1 day
        nTargetSpacing = 2 * 60;  // Vice: 2 minutes
        nMaturity = 10;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 1; // we use the version 2 for VICE

        /**
        *python gen.py -a quark -z "Never send a human to do a machine's job, good day." -t 1544536800 -v 0 -p "04125120136cd8bddf4a7f3c116a16f1689575f997ad38157c162b465b41497af6819a5b980e823473bcb2c4972432359aaf7d93d16a2c412685c299d2b912a6fe"
        *04ffff001d0104334e657665722073656e6420612068756d616e20746f20646f2061206d616368696e652773206a6f622c20676f6f64206461792e
        *algorithm: quark
        *merkle hash: a0fdc6bb8907412e788a7c5ac458a091f46a5e142b5d78c8a9ca1aa6cbfdabdf
        *pszTimestamp: Never send a human to do a machine's job, good day.
        *pubkey: 04125120136cd8bddf4a7f3c116a16f1689575f997ad38157c162b465b41497af6819a5b980e823473bcb2c4972432359aaf7d93d16a2c412685c299d2b912a6fe
        *time: 1544536800
        *bits: 0x1e0ffff0
        *Searching for genesis hash...
        *genesis hash found!
        *nonce: 56048
        *genesis hash: 00000f186512642b3b8be1cd906df8b81028d58cfa7350fc123bc89b1644846e
        */
        const char* pszTimestamp = "Never send a human to do a machine's job, good day.";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04125120136cd8bddf4a7f3c116a16f1689575f997ad38157c162b465b41497af6819a5b980e823473bcb2c4972432359aaf7d93d16a2c412685c299d2b912a6fe") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1544536800;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 56048;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000f186512642b3b8be1cd906df8b81028d58cfa7350fc123bc89b1644846e"));
        assert(genesis.hashMerkleRoot == uint256("0xa0fdc6bb8907412e788a7c5ac458a091f46a5e142b5d78c8a9ca1aa6cbfdabdf"));


        // DNS Seeding
        vSeeds.push_back(CDNSSeedData("seed1.viceplatform.org", "seed1.viceplatform.org"));
        vSeeds.push_back(CDNSSeedData("seed2.viceplatform.org", "seed2.viceplatform.org"));
        vSeeds.push_back(CDNSSeedData("seed3.viceplatform.org", "seed3.viceplatform.org"));

        // Vice addresses start with 'V'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 71);
        // Vice script addresses start with '3'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 72);
        
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 144);
        // Vice BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x2D)(0x25)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Vice BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x21)(0x31)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xe4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0424ca1863bcfb8e0a86caaec04c36a14414048773a33d248ae27d480b0eef7dd28d8302b9d271de57f8722b7182c9da83532cd821a9df7b862bec0461d69442b3";
        strMasternodePoolDummyAddress = "VxRejSmVs2hxzUHosUQSncdF3jW1YkaujU";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis creation

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x73;
        pchMessageStart[1] = 0x69;
        pchMessageStart[2] = 0x6d;
        pchMessageStart[3] = 0x20;
        vAlertPubKey = ParseHex("046ff18c7c93ef0ea3fd1dbc7944721a9b98d3defcfaaf7b2c27dced5c8953ae89e8d656f25332a49e13b0fcd77e0be8c8a8370f4e6b074fe93d1e78d04fe68378");
        nDefaultPort = 8934;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Vice: 1 day
        nTargetSpacing = 2 * 60;  // Vice: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 21000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1544536801;
        genesis.nNonce = 572443;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000063d69bab1632ede3c7195b6d9d82cc7a2dabf41c5f0663196e3524391ab"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 132); // Testnet vice addresses start with 'v'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 12);  // Testnet vice script addresses start with '5' or '6'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 109);     // Testnet private keys start with 'k' or 'm' (Bitcoin defaults)
        // Testnet vice BIP32 pubkeys start with 'tpub'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet vice BIP32 prvkeys start with 'tprv'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet vice BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04a3099a1f68405b29220cbf4c3e85d93fc082407752ede28f9e460cbdef2021db712218971781c5c1847e54b97dec543613831a704476c199da18bd23b4c4ac64";
        strMasternodePoolDummyAddress = "VrerHkBHyyUGfqFKfikJGMWU1KUM9tUNxS";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x20;
        pchMessageStart[1] = 0xee;
        pchMessageStart[2] = 0x32;
        pchMessageStart[3] = 0xbc;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Vice: 1 day
        nTargetSpacing = 2 * 60;        // Vice: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1544536802;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 898959;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 8935;
        assert(hashGenesisBlock == uint256("0x0000082b6e9f62cfc2a54f5bb895f4d85f2a436f24069cfe202e8a75f4f5a6ea"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 42004;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
