#include "polyNTL.h"
#include <cryptoTools/Common/Log.h>
#include <cryptoTools/Common/Timer.h>
#include <cryptoTools/Crypto/RandomOracle.h>

namespace osuCrypto
{

	polyNTL::polyNTL()
    {
    }


	polyNTL::~polyNTL()
    {
    }

	

	void polyNTL::NtlPolyInit(u64 numBytes) {
		mGf2x.~GF2X();
		mNumBytes = numBytes;
		NTL::BuildIrred(mGf2x, numBytes * 8);
		NTL::GF2E::init(mGf2x);
	}

	void polyNTL::GF2EFromBlock(NTL::GF2E &element, block& blk, u64 size) {
		NTL::GF2XFromBytes(mGf2x, (u8*)&blk, size);
		element = to_GF2E(mGf2x);
	}

	void polyNTL::BlockFromGF2E(block& blk, NTL::GF2E & element, u64 size) {
		NTL::GF2X fromEl = NTL::rep(element); //convert the GF2E element to GF2X element. the function rep returns the representation of GF2E as the related GF2X, it returns as read only.
		BytesFromGF2X((u8*)&blk, fromEl, size);
	}

	//computes coefficients (in blocks) of f such that f(x[i]) = y[i]
	void polyNTL::getBlkCoefficients(NTL::vec_GF2E& vecX, NTL::vec_GF2E& vecY, std::vector<block>& coeffs)
	{
		NTL::GF2E e;

		//interpolate
		NTL::GF2EX polynomial = NTL::interpolate(vecX, vecY);

		////convert coefficient to vector<block> 
		coeffs.resize(NTL::deg(polynomial) + 1);
		for (int i = 0; i < coeffs.size(); i++) {
			//get the coefficient polynomial
			e = NTL::coeff(polynomial, i);
			BlockFromGF2E(coeffs[i], e, mNumBytes);
		}
	}

	void polyNTL::getBlkCoefficients(u64 degree, std::vector<block>& setX, std::vector<block>& setY, std::vector<block>& coeffs)
	{
		//degree = setX.size() - 1;
		NTL::vec_GF2E x; NTL::vec_GF2E y;
		NTL::GF2E e;

		for (u64 i = 0; i < setX.size(); ++i)
		{
			polyNTL::GF2EFromBlock(e, setX[i], mNumBytes);
			x.append(e);

			polyNTL::GF2EFromBlock(e, setY[i], mNumBytes);
			y.append(e);
		}


		NTL::GF2EX polynomial = NTL::interpolate(x, y);


		//indeed, we dont need to pad dummy item to max_bin_size
		//we can compute a polynomial over real items
		//for exaple, there are 3 items in a bin (xi,yi) => interpolate poly p1(x) of a degree 2
		// gererate a root poly pRoot(x) of degree 2 over (xi,0)
		// gererate a dummy poly dummy(x) of degree max_bin_size - degree of p1(x)
		//send coff of poly dummy(x)*pRoot(x)+p1(x)
		//if x*=xi =>pRoot(xi)=0 => get p1(x*)

		if (degree > setX.size()-1)
		{
			NTL::GF2EX root_polynomial;
			NTL::BuildFromRoots(root_polynomial, x);


			NTL::GF2EX dummy_polynomial;
			NTL::random(dummy_polynomial, degree - setX.size()+1);
			NTL::GF2EX d_polynomial;
			polynomial = polynomial + dummy_polynomial*root_polynomial;
		}

		coeffs.resize(NTL::deg(polynomial) + 1);
		for (int i = 0; i <= NTL::deg(polynomial); i++) {
			//get the coefficient polynomial
			e = NTL::coeff(polynomial, i);
			BlockFromGF2E(coeffs[i], e, mNumBytes);
		}

		//GF2EFromBlock(e, setX[0], mNumBytes);
		//e = NTL::eval(polynomial, e); //get y=f(x) in GF2E
		//BlockFromGF2E(y1, e, mNumBytes); //convert to block 
		//std::cout << setX[0] << "\t" << y1 <<" 2"<< std::endl;
	}

	//compute y=f(x) giving coefficients (in block)
	void polyNTL::evalPolynomial(std::vector<block>& coeffs, block& x, block& y)
	{
		NTL::GF2EX res_polynomial;
		NTL::GF2E e;
		//std::cout << coeffs.size() << std::endl;
		for (u64 i = 0; i < coeffs.size(); ++i)
		{
			GF2EFromBlock(e, coeffs[i], mNumBytes);
			NTL::SetCoeff(res_polynomial, i, e); //build res_polynomial
		}

		GF2EFromBlock(e, x, mNumBytes);
		e = NTL::eval(res_polynomial, e); //get y=f(x) in GF2E
		BlockFromGF2E(y, e, mNumBytes); //convert to block 
	}

}
