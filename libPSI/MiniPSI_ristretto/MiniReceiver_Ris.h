#pragma once
// This file and the associated implementation has been placed in the public domain, waiving all copyright. No restrictions are placed on its use.
#include <array>
#include <cryptoTools/Crypto/PRNG.h>
#include <cryptoTools/Common/Timer.h>
#include "libOTe/NChooseOne/Kkrt/KkrtNcoOtSender.h"
#include "libOTe/NChooseOne/Kkrt/KkrtNcoOtReceiver.h"
#include "libOTe/TwoChooseOne/IknpOtExtReceiver.h"
#include "Poly/polyNTL.h"
#include "PsiDefines.h"
#include <NTL/ZZ_p.h>
#include <NTL/vec_ZZ_p.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ.h>
#include "Tools/BalancedIndex.h"
#include "Tools/SimpleIndex.h"
#include "cryptoTools/Crypto/Curve.h"
#include "cryptoTools/Crypto/RandomOracle.h"

using namespace NTL;

namespace osuCrypto
{

    class MiniReceiver_Ris : public TimerAdapter
    {
    public:

		u64 mSetSeedsSize, mChoseSeedsSize, mCurveByteSize, mBoundCoeffs;
#ifdef ENABLE_MIRACL
		Ecc2mParams mCurveParam;
#endif // ENABLE_MIRACL
		block mCurveSeed;
		ropo_fe25519 mfe25519_one;

		//std::vector<u8*> mSeeds; //all ri in bytes for computing (g^k)^(subsum ri) later
		//std::vector<std::pair<u64, std::vector<u64>>> mSubsetSum; //all ri in sum ri


		bool mHasBase;
		BalancedIndex mBalance;
		SimpleIndex simple;


		std::vector<std::vector<int>> mIntCi;
		std::vector<unsigned char*> mScalars;
		std::vector<unsigned char*> mG_pairs; //T^1(..)
		std::vector <std::vector< block>> mG_pairs_elligator; //pk,representative


		u64 mMyInputSize, mTheirInputSize, mPolyBytes, mPolyDegree, mPsiSecParam;
		std::vector<block> mS;
		u64 mFieldSize;

		block mTruncateBlk;
		/*std::vector<u8*> mSeeds_Byte;
		std::vector<u8*> pG_seeds_Byte;*/

		PRNG mPrng;
		ZZ mPrime;
		ZZ mPrimeLastSlice;

		std::vector<u64> mIntersection; //index

		block recvMaskForDebug;
		//AES mAesHasher;

		std::vector<block> Outputs;

#ifdef ENABLE_MIRACL
		void expTinvert(u64 myInputSize, u64 psiSecParam, PRNG& prng);
#endif // ENABLE_MIRACL
		void outputBigPoly(u64 myInputSize, u64 theirInputSize, u64 psiSecParam, PRNG& prng, span<block> inputs, span<Channel> chls);
		void outputBigPoly_elligator(u64 myInputSize, u64 theirInputSize, u64 psiSecParam, PRNG& prng, span<block> inputs, span<Channel> chls);
		void outputBigPoly_moeller(u64 myInputSize, u64 theirInputSize, u64 psiSecParam, PRNG& prng, span<block> inputs, span<Channel> chls);

		//void output(span<block> inputs, span<Channel> chls);
		//void outputBestComm(span<block> inputs, span<Channel> chls);
		//void outputBigPoly(span<block> inputs, span<Channel> chls);

    };

}
