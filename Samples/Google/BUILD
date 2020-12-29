load("//:tpm.bzl", "COPTS", "add_prototype_headers")
package(default_visibility = ["//Platform:__pkg__"])

# Base headers that don't require inclusion in a particular order
cc_library(
    name = "Headers",
    hdrs = [
        "tpm/include/TpmBuildSwitches.h",
        "tpm/include/CompilerDependencies.h",
        "tpm/include/TpmProfile.h",
        "tpm/include/BaseTypes.h",
        "tpm/include/TPMB.h",
        "tpm/include/ACT.h",
    ],
    copts = COPTS,
    includes = [
        "tpm/include",
        "tpm/include/prototypes",
    ],
)

ossl_srcs = add_prototype_headers([
    # OpenSSL declarations and macros
    "tpm/include/Ossl/TpmToOsslHash.h",
    "tpm/include/Ossl/TpmToOsslMath.h",
    "tpm/include/Ossl/TpmToOsslSym.h",
    # OpenSSL implementation (we don't need DES)
    "tpm/src/crypt/ossl/TpmToOsslMath.c",
    "tpm/src/crypt/ossl/TpmToOsslSupport.c",
])

core_srcs = add_prototype_headers([
    # Interface to all global data
    "tpm/include/Global.h",

    # Marshalling code
    "tpm/include/Marshal.h",
    "tpm/include/TableMarshal.h",
    "tpm/include/TableMarshalTypes.h",
    "tpm/include/TableMarshalDefines.h",

    # Other headers included directly/indirectly by Tpm.h
    "tpm/include/MinMax.h",
    "tpm/include/TpmAlgorithmDefines.h",
    "tpm/include/LibSupport.h",
    "tpm/include/GpMacros.h",
    "tpm/include/swap.h",
    "tpm/include/VendorString.h", # TODO replace w/ Google Vendor string
    "tpm/include/Capabilities.h",
    "tpm/include/TpmTypes.h",
    "tpm/include/CommandAttributes.h",
    "tpm/include/BnValues.h",
    "tpm/include/CryptHash.h",
    "tpm/include/CryptSym.h",
    "tpm/include/CryptRand.h",
    "tpm/include/CryptEcc.h",
    "tpm/include/CryptRsa.h",
    "tpm/include/TpmError.h",
    "tpm/include/NV.h",
    "tpm/include/OIDs.h",
    "tpm/include/X509.h",
    "tpm/include/TpmASN1.h",

    # Use a Google-specific InternalRoutines to allow for better build sharding.
    "InternalRoutines.h",
    "tpm/include/SupportLibraryFunctionPrototypes_fp.h", # TODO: move?
    "tpm/include/CommandAttributeData.h", # TODO: why needed

    # Test data files, necessary as we defined SELF_TEST (tpm/include/*Test*.h)
    "tpm/include/CryptTest.h",
    "tpm/include/PRNG_TestVectors.h",
    "tpm/include/EccTestData.h",
    "tpm/include/HashTestData.h",
    "tpm/include/KdfTestData.h",
    "tpm/include/RsaTestData.h",
    "tpm/include/SelfTest.h",
    "tpm/include/SymmetricTest.h",
    "tpm/include/SymmetricTestData.h",

    # ALL (Ecc{KeyExchange,Crypt} not strictly needed
    "tpm/src/crypt/AlgorithmTests.c",
    "tpm/src/crypt/BnConvert.c",
    "tpm/src/crypt/BnMath.c",
    "tpm/src/crypt/BnMemory.c",
    "tpm/src/crypt/CryptCmac.c",
    "tpm/src/crypt/CryptDes.c",
    "tpm/src/crypt/CryptEccCrypt.c",
    "tpm/src/crypt/CryptEccData.c",
    "tpm/src/crypt/CryptEccKeyExchange.c",
    "tpm/src/crypt/CryptEccMain.c",
    "tpm/src/crypt/CryptEccSignature.c",
    "tpm/src/crypt/CryptHash.c",
    "tpm/src/crypt/CryptPrime.c",
    "tpm/src/crypt/CryptPrimeSieve.c",
    "tpm/src/crypt/CryptRand.c",
    "tpm/src/crypt/CryptRsa.c",
    "tpm/src/crypt/CryptSelfTest.c",
    "tpm/src/crypt/CryptSmac.c",
    "tpm/src/crypt/CryptSym.c",
    "tpm/src/crypt/CryptUtil.c",
    "tpm/src/crypt/PrimeData.c",
    "tpm/src/crypt/RsaKeyCache.c",
    "tpm/src/crypt/Ticket.c",

    # ALL
    "tpm/src/subsystem/CommandAudit.c",
    "tpm/src/subsystem/DA.c",
    "tpm/src/subsystem/Hierarchy.c",
    "tpm/src/subsystem/NvDynamic.c",
    "tpm/src/subsystem/NvReserved.c",
    "tpm/src/subsystem/Object.c",
    "tpm/src/subsystem/PCR.c",
    "tpm/src/subsystem/PP.c",
    "tpm/src/subsystem/Session.c",
    "tpm/src/subsystem/Time.c",

    # All except Manufacture and TpmSizeChecks
    "tpm/src/support/AlgorithmCap.c",
    "tpm/src/support/Bits.c",
    "tpm/src/support/CommandCodeAttributes.c",
    "tpm/src/support/Entity.c",
    "tpm/src/support/Handle.c",
    "tpm/src/support/Global.c",
    "tpm/src/support/IoBuffers.c",
    "tpm/src/support/Locality.c",
    "tpm/src/support/Marshal.c",
    "tpm/src/support/MathOnByteBuffers.c",
    "tpm/src/support/Memory.c",
    "tpm/src/support/Power.c",
    "tpm/src/support/PropertyCap.c",
    "tpm/src/support/Response.c",
    "tpm/src/support/ResponseCodeProcessing.c",
    "tpm/src/support/TableDrivenMarshal.c",
    "tpm/src/support/TableMarshalData.c",
    "tpm/src/support/TpmFail.c",

    # Needed for TODO
    "tpm/src/main/SessionProcess.c",
    "tpm/src/command/Context/Context_spt.c",
    "tpm/src/command/Object/Object_spt.c",
])

cc_library(
    name = "Core",
    hdrs = [
        "tpm/include/Tpm.h",
    ],
    srcs = ossl_srcs + core_srcs,
    deps = [
        ":Headers",
        "//Platform:Headers",
        "@boringssl//:crypto",
    ],
    copts = COPTS,
)

cc_library(
    name = "Manufacture",
    hdrs = [
        "tpm/include/prototypes/Manufacture_fp.h",
    ],
    srcs = ["tpm/src/support/Manufacture.c"] + add_prototype_headers([
        "tpm/src/support/TpmSizeChecks.c",
    ]),
    deps = [
        ":Core",
    ],
    copts = COPTS,
)

cc_library(
    name = "hash_event",
    hdrs = [

    ],
    srcs = [

    ],
    deps = [

    ],
    copts = COPTS,
)



# cc_library(
#     name = "Tpm",
#     hdrs = [],
#     srcs = [],
#     deps = [
#         ":TpmProfile",
#     ]
#     copts = COPTS,
# )