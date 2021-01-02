load("//:tpm.bzl", "COPTS", "add_prototype_headers", "tpm_command")
package(default_visibility = ["//Platform:__pkg__"])

# Base headers used by the Platform and TPM code
cc_library(
    name = "Headers",
    hdrs = [
        "tpm/include/TpmBuildSwitches.h",
        "tpm/include/CompilerDependencies.h",
        "tpm/include/BaseTypes.h",
        "tpm/include/TPMB.h",
        "tpm/include/MinMax.h",
        "tpm/include/TpmProfile.h",
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
    "tpm/include/ACT.h",
    "tpm/include/OIDs.h",
    "tpm/include/X509.h",
    "tpm/include/TpmASN1.h",

    "tpm/include/InternalRoutines.h",
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
    "tpm/src/command/ClockTimer/ACT_spt.c",
    "tpm/src/command/NVStorage/NV_spt.c",
])

cc_library(
    name = "Core",
    hdrs = ["tpm/include/Tpm.h"],
    srcs = ossl_srcs + core_srcs,
    deps = [
        ":Headers",
        "//Platform",
        "@boringssl//:crypto",
    ],
    copts = COPTS,
)

cc_library(
    name = "TpmASN1",
    hdrs = ["tpm/include/prototypes/TpmASN1_fp.h"],
    srcs = ["tpm/src/X509/TpmASN1.c"],
    deps = [":Core"],
    copts = COPTS,
)

cc_library(
    name = "X509_spt",
    hdrs = ["tpm/include/prototypes/X509_spt_fp.h"],
    srcs = ["tpm/src/X509/X509_spt.c"] + add_prototype_headers([
        "tpm/src/X509/X509_ECC.c",
        "tpm/src/X509/X509_RSA.c",
    ]),
    deps = [":Core", ":TpmASN1"],
    copts = COPTS,
)

cc_library(
    name = "_TPM_Hash",
    hdrs = [
        "tpm/include/prototypes/_TPM_Hash_Data_fp.h",
        "tpm/include/prototypes/_TPM_Hash_End_fp.h",
        "tpm/include/prototypes/_TPM_Hash_Start_fp.h",
    ],
    srcs = [
        "tpm/src/events/_TPM_Hash_Data.c",
        "tpm/src/events/_TPM_Hash_End.c",
        "tpm/src/events/_TPM_Hash_Start.c",
    ],
    deps = [":Core"],
    copts = COPTS,
)

cc_library(
    name = "_TPM_Init",
    hdrs = ["tpm/include/prototypes/_TPM_Init_fp.h"],
    srcs = ["tpm/src/events/_TPM_Init.c"],
    deps = [":Core"],
    copts = COPTS,
)

cc_library(
    name = "Manufacture",
    hdrs = ["tpm/include/prototypes/Manufacture_fp.h"],
    srcs = ["tpm/src/support/Manufacture.c"] + add_prototype_headers([
        "tpm/src/support/TpmSizeChecks.c",
    ]),
    deps = [":Core"],
    copts = COPTS,
)

cc_library(
    name = "EncryptDecrypt",
    hdrs = [
        "tpm/include/prototypes/EncryptDecrypt_fp.h",
        "tpm/include/prototypes/EncryptDecrypt2_fp.h",
    ],
    srcs = [
        "tpm/src/command/Symmetric/EncryptDecrypt.c",
        "tpm/src/command/Symmetric/EncryptDecrypt2.c",
    ] + add_prototype_headers([
        "tpm/src/command/Symmetric/EncryptDecrypt_spt.c",
    ]),
    deps = [":Core"],
    copts = COPTS,
)

tpm_command("Attestation/Attest_spt")

# No AttachedComponent
CMDS = [
    # ALL
    tpm_command("Startup/Startup"),
    tpm_command("Startup/Shutdown"),
    # ALL
    tpm_command("Testing/SelfTest"),
    tpm_command("Testing/IncrementalSelfTest"),
    tpm_command("Testing/GetTestResult"),
    # ALL
    tpm_command("Session/StartAuthSession"),
    tpm_command("Session/PolicyRestart"),
    # ALL
    tpm_command("Object/Create"),
    tpm_command("Object/Load"),
    tpm_command("Object/LoadExternal"),
    tpm_command("Object/ReadPublic"),
    tpm_command("Object/ActivateCredential"),
    tpm_command("Object/MakeCredential"),
    tpm_command("Object/Unseal"),
    tpm_command("Object/ObjectChangeAuth"),
    tpm_command("Object/CreateLoaded"),
    # ALL
    tpm_command("Duplication/Duplicate"),
    tpm_command("Duplication/Rewrap"),
    tpm_command("Duplication/Import"),
    # No EC_Ephemeral
    tpm_command("Asymmetric/RSA_Encrypt"),
    tpm_command("Asymmetric/RSA_Decrypt"),
    tpm_command("Asymmetric/ECDH_KeyGen"),
    tpm_command("Asymmetric/ECDH_ZGen"),
    tpm_command("Asymmetric/ECC_Parameters"),
    tpm_command("Asymmetric/ZGen_2Phase"),
    tpm_command("Asymmetric/ECC_Encrypt"),
    tpm_command("Asymmetric/ECC_Decrypt"),
    # Encrypt/Decrypt is weird, and no HMAC
    ":EncryptDecrypt",
    tpm_command("Symmetric/Hash"),
    tpm_command("Symmetric/MAC"),
    # ALL
    tpm_command("Random/GetRandom"),
    tpm_command("Random/StirRandom"),
    # No HMAC_Start
    tpm_command("HashHMAC/MAC_Start"),
    tpm_command("HashHMAC/HashSequenceStart"),
    tpm_command("HashHMAC/SequenceUpdate"),
    tpm_command("HashHMAC/SequenceComplete"),
    tpm_command("HashHMAC/EventSequenceComplete"),
    # ALL, except Attest_spt handled above
    tpm_command("Attestation/Certify", deps=[":Attest_spt"]),
    tpm_command("Attestation/CertifyCreation", deps=[":Attest_spt"]),
    tpm_command("Attestation/Quote", deps=[":Attest_spt"]),
    tpm_command("Attestation/GetSessionAuditDigest", deps=[":Attest_spt"]),
    tpm_command("Attestation/GetCommandAuditDigest", deps=[":Attest_spt"]),
    tpm_command("Attestation/CertifyX509", deps=[
        ":TpmASN1",
        ":X509_spt",
        ":Attest_spt",
    ]),
    tpm_command("Attestation/GetTime", deps=[":Attest_spt"]),
    # ALL
    tpm_command("Ecdaa/Commit"),
]

cc_library(
    name = "ExecCommand",
    hdrs = ["tpm/include/prototypes/ExecCommand_fp.h"],
    srcs = ["tpm/src/main/ExecCommand.c"] + add_prototype_headers([
        "tpm/include/CommandDispatchData.h",
        "tpm/src/main/CommandDispatcher.c",
    ]),
    deps = CMDS + [":Core"],
    copts = COPTS,
)


