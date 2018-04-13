#pragma once
// This file and the associated implementation has been placed in the public domain, waiving all copyright. No restrictions are placed on its use.  
#include <cryptoTools/Common/BitVector.h>
#include <cryptoTools/Common/Timer.h>
#include <cryptoTools/Crypto/PRNG.h>
#include <cryptoTools/Network/Channel.h>
#include "libOTe/NChooseOne/Kkrt/KkrtNcoOtReceiver.h"
#include "libOTe/NChooseOne/Kkrt/KkrtNcoOtSender.h"
#include "libOTe/TwoChooseOne/IknpOtExtReceiver.h"
#include "Poly/polyNTL.h"
#include "PsiDefines.h"
#include <NTL/ZZ_p.h>
#include <NTL/vec_ZZ_p.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ.h>
#include "Poly/polyFFT.h"

#include <array>
namespace osuCrypto {

	class PrtySender :public TimerAdapter
	{
	public:

		
		bool mHasBase;

		u64 mNumOTs, mPolyNumBytes, mPolyDegree, mStepSize, mPsiSecParam, mNumBins;
		std::vector<block> mS;
		KkrtNcoOtReceiver recvOprf;
		KkrtNcoOtSender sendOprf; //PQET
		
		u64 mFieldSize;
		ZZ mPrime;

		polyNTL poly;
		PRNG mPrng;
		
		BitVector mOtChoices;
		std::vector<std::array<block, numSuperBlocks>> mRowQ;
		std::vector<AES> mAesQ;
		std::vector<u8> sendBuff;
		std::vector<u8> recvBuff;

		
		void init(u64 psiSecParam, PRNG& prng, span<block> inputs, span<Channel> chls);
		void output(span<block> inputs, span<Channel> chls);
	};
}
