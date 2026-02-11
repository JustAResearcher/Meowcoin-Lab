// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2017-2021 The Meowcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <primitives/pureheader.h>

#include <hash.h>
#include <serialize.h>
#include <tinyformat.h>

void CBlockVersion::SetBaseVersion(int32_t nBaseVersion, int32_t nChainId)
{
    nVersion = nBaseVersion | (nChainId << VERSION_START_BIT);
}

uint256 CPureBlockHeader::GetHash() const
{
    return (HashWriter{} << *this).GetHash();
}

std::string CPureBlockHeader::ToString() const
{
    return strprintf(
        "CPureBlockHeader(ver=0x%08x, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u)",
        nVersion.GetFullVersion(),
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce);
}
