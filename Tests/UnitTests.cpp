#include <cryptoTools/Common/Log.h>
#include <cryptoTools/Common/TestCollection.h>
#include <functional>

#include "AknOt_Tests.h"
#include "BaseOT_Tests.h"
#include "OT_Tests.h"
#include "NcoOT_Tests.h"
#include "AknOt_Tests.h"
#include "miniPSI_Tests.h"
#include "PSI_Tests.h"


using namespace osuCrypto;
namespace tests_libOTe
{

    void run(std::string name, std::function<void(void)> func)
    {
        std::cout << name << std::flush;

        auto start = std::chrono::high_resolution_clock::now();
        try
        {
            func(); std::cout << Color::Green << "  Passed" << ColorDefault;
        }
        catch (const UnitTestSkipped& e)
        {
            std::cout << Color::Yellow << "  Skipped - " << e.what() << ColorDefault;
        }
        catch (const std::exception& e)
        {
            std::cout << Color::Red << "Failed - " << e.what() << ColorDefault;
        }

        auto end = std::chrono::high_resolution_clock::now();

        u64 time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "   " << time << "ms" << std::endl;

    }


    void tests_OT_all()
    {
        std::cout << std::endl;


        run("TransposeMatrixView_Test_Impl           ", TransposeMatrixView_Test_Impl);
        run("Transpose_Test_Impl                     ", Transpose_Test_Impl);
        run("KosOtExt_100Receive_Test_Impl           ", KosOtExt_100Receive_Test_Impl);
        run("KosDotExt_100Receive_Test_Impl          ", KosDotExt_100Receive_Test_Impl);
        run("IknpOtExt_100Receive_Test_Impl          ", IknpOtExt_100Receive_Test_Impl);
        run("AknOt_sendRecv1000_Test                 ", AknOt_sendRecv1000_Test);
        run("KkrtNcoOt_Test                          ", KkrtNcoOt_Test_Impl);
        run("OosNcoOt_Test_Impl                      ", OosNcoOt_Test_Impl);
        run("Rr17NcoOt_Test_Impl                     ", Rr17NcoOt_Test_Impl);
        run("LinearCode_Test_Impl                    ", LinearCode_Test_Impl);
        run("LinearCode_subBlock_Test_Impl           ", LinearCode_subBlock_Test_Impl);
        run("LinearCode_repetition_Test_Impl         ", LinearCode_repetition_Test_Impl);
        run("NaorPinkasOt_Test                       ", NaorPinkasOt_Test_Impl);
        run("exp_test                                ", exp_test);
        run("MiniPSI_impl2                           ", MiniPSI_impl2);
        run("DhPSI_impl                              ", DhPSI_impl);
        run("JL10PSI_impl                            ", JL10PSI_impl);
        run("JL10PSI_subsetsum_impl                  ", JL10PSI_subsetsum_impl);
        run("subsetSum_test                          ", subsetSum_test);
        run("MiniPSI_hasing_impl                     ", MiniPSI_hasing_impl);
        run("schnorrZKDL                             ", schnorrZKDL);
        run("MiniPSI_malicious_impl                  ", MiniPSI_malicious_impl);
        run("JL10PSI_subsetsum_malicious_impl        ", JL10PSI_subsetsum_malicious_impl);
        run("evalExp                                 ", evalExp);
        run("curveTest                               ", curveTest);
        //run("testNewGroup                            ", testNewGroup);
        //run("Simple_Test_Impl                        ", Simple_Test_Impl);
        //run("Ristretto_Test_Impl                     ", Ristretto_Test_Impl);

        //run("Hashing_Test_Impl                           ", Hashing_Test_Impl);
        //run("NTL_Poly_Test_Impl                          ", NTL_Poly_Test_Impl);
        //run("myTest                                      ", myTest);
        //run("seft_balance                                ", seft_balance);
        //run("Poly_Test_Impl                              ", Poly_Test_Impl);
        //run("Prty_PSI_impl                               ", Prty_PSI_impl);
        //run("prfOtRow_Test_Impl                          ", prfOtRow_Test_Impl);
    }




    void tests_all()
    {

        tests_OT_all();

    }
}
