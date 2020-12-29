COPTS = [
    "-Wall",
    "-Wextra",
    "-Wpedantic",
    "-pedantic-errors",
    "-Wmissing-prototypes",
    "-Wold-style-definition",
    "-Wstrict-prototypes",
    "-Wsign-compare",
    "-Wmissing-field-initializers",
    "-Wwrite-strings",
    "-Wshadow",
    "-std=c17",
] + [
    "-DSIMULATION=NO",
    "-DCOMPILER_CHECKS=DEBUG",
    "-DRUNTIME_SIZE_CHECKS=DEBUG",
    "-DLIBRARY_COMPATIBILITY_CHECK=DEBUG",
    "-DSELF_TEST=YES",
    "-DUSE_DA_USED=NO",
    "-DCERTIFYX509_DEBUG=NO",
    "-DREMANUFACTURE=NO",
    # Disable insecure/unsupported crypto algorithms
    "-DECC_BN_P256=NO",
    "-DECC_BN_P638=NO",
    "-DALG_ECDAA=ALG_NO",
    "-DALG_ECMQV=ALG_NO",
    "-DALG_ECSCHNORR=ALG_NO",
    "-DALG_CAMELLIA=ALG_NO",
    "-DALG_TDES=ALG_NO",
    # We do not support the Chinese "Commercial Cryptographic Algorithms"
    "-DECC_SM2_P256=NO",
    "-DALG_SM2=ALG_NO",
    "-DALG_SM3_256=ALG_NO",
    "-DALG_SM4=ALG_NO",
    # We don't have any attached components
    "-DCC_AC_GetCapability=CC_NO",
    "-DCC_AC_Send=CC_NO",
    "-DCC_Policy_AC_SendSelect=CC_NO",
    # Enable supported algorithms that aren't on by default
    # "-DECC_NIST_P224=YES",
    # "-DECC_NIST_P521=YES",
    # "-DALG_SHA512=ALG_YES", # Could also add SHA3?
    # "-DMAX_CONTEXT_SIZE=1360",
]

def get_prototype_header(src):
    if not src.endswith(".c"):
        return None # Source {} does not end with .c
    name = src.split("/")[-1][:-2]
    if name in ["CryptEccData", "PrimeData", "TableMarshalData", "Global"]:
        return None
    return "tpm/include/prototypes/{}_fp.h".format(name)

def add_prototype_headers(srcs):
    hdrs = [get_prototype_header(src) for src in srcs]
    return srcs + [hdr for hdr in hdrs if hdr != None]
