load("//:tpm.bzl", "COPTS")
package(default_visibility = ["//visibility:private"])

cc_library(
    name = "Headers",
    hdrs = glob(["include/*.h"]),
    copts = COPTS,
    includes = ["include"],
    visibility = ["//:__pkg__"],
)

cc_library(
    name = "Data",
    hdrs = ["Data.h"],
    srcs = ["Data.c"],
    deps = ["//:Headers"],
    copts = COPTS,
)

cc_library(
    name = "Clock",
    hdrs = ["Clock.h"],
    srcs = ["Clock.c"],
    deps = [
        ":Headers",
        ":Data",
    ],
    copts = COPTS,
)

cc_library(
    name = "NVMem",
    srcs = ["NVMem.c"],
    deps = [
        ":Headers",
        ":Data",
    ],
    copts = COPTS,
)

cc_library(
    name = "Stubs",
    srcs = [
        "ACT.c",
        "Cancel.c",
        "Entropy.c",
        "Locality.c",
        "NVMem.c",
        "PPPlat.c",
    ],
    deps = [
        ":Headers",
        "@boringssl//:crypto",
    ],
    copts = COPTS,
)

cc_library(
    name = "Platform",
    hdrs = ["Start.h"],
    srcs = ["Start.c"],
    deps = [
        ":Headers",
        ":Data",
        ":Clock",
        ":NVMem",
        ":Stubs",
    ],
    copts = COPTS,
)