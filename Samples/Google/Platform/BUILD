load("//:tpm.bzl", "COPTS")
package(default_visibility = ["//visibility:private"])

cc_library(
    name = "Platform",
    hdrs = ["include/Platform.h"],
    srcs = [
        "include/Platform_fp.h",
        "include/PlatformClock.h",
        "include/PlatformData.h",
        "Cancel.c",
        "Clock.c",
        "Entropy.c",
        "LocalityPlat.c",
        "NVMem.c",
        "PlatformACT.c",
        "PlatformData.c",
        "PowerPlat.c",
        "PPPlat.c",
    ],
    deps = [
        "//:Headers",
        "@boringssl//:crypto",
    ],
    copts = COPTS,
    includes = ["include"],
    visibility = ["//:__pkg__"],
)

cc_library(
    name = "Start",
    hdrs = ["Start.h"],
    srcs = ["Start.c"],
    deps = [
        ":Platform",
        "//:_TPM_Hash",
        "//:_TPM_Init",
        "//:ExecCommand",
        "//:Manufacture",
    ],
    copts = COPTS,
)

cc_binary(
    name = "Runner",
    srcs = ["Runner.c"],
    deps = [":Start"],
    copts = COPTS,
)