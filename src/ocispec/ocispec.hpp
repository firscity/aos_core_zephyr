/*
 * Copyright (C) 2023 Renesas Electronics Corporation.
 * Copyright (C) 2023 EPAM Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef OCISPEC_HPP_
#define OCISPEC_HPP_

#include <aos/common/ocispec.hpp>
#include <aos/common/tools/thread.hpp>

// Image spec

/**
 * OCI image config.
 */
struct ImageConfig {
    const char* Cmd[aos::oci::cMaxParamCount];
    size_t      cmdLen;
    const char* Env[aos::oci::cMaxParamCount];
    size_t      envLen;
    const char* entrypoint[aos::oci::cMaxParamCount];
    size_t      entrypointLen;
};

/**
 * OCI image specification.
 */
struct ImageSpec {
    ImageConfig config;
};

// Runtime spec

/**
 * Contains information about the hypervisor to use for a virtual machine.
 */
struct VMHypervisor {
    const char* path;
    const char* parameters[aos::oci::cMaxParamCount];
    size_t      parametersLen;
};

/**
 * Contains information about the kernel to use for a virtual machine.
 */
struct VMKernel {
    const char* path;
    const char* parameters[aos::oci::cMaxParamCount];
    size_t      parametersLen;
};

/**
 * Contains information about HW configuration.
 */
struct VMHWConfig {
    const char* devicetree;
};

/**
 * Contains information for virtual-machine-based containers.
 */
struct VM {
    VMHypervisor hypervisor;
    VMKernel     kernel;
    VMHWConfig   hwconfig;
};

/**
 * OCI runtime specification.
 */
struct RuntimeSpec {
    const char* ociVersion;
    VM          vm;
};

/**
 * OCISpec instance.
 */
class OCISpec : public aos::OCISpecItf {
public:
    OCISpec()
        : mJsonFileBuffer()
        , mRuntimeSpec()
        , mImageSpec()
    {
    }
    /**
     * Loads OCI image spec.
     *
     * @param path file path.
     * @param imageSpec image spec.
     * @return Error.
     */
    aos::Error LoadImageSpec(const aos::String& path, aos::oci::ImageSpec& imageSpec) override;

    /**
     * Saves OCI image spec.
     *
     * @param path file path.
     * @param imageSpec image spec.
     * @return Error.
     */
    aos::Error SaveImageSpec(const aos::String& path, const aos::oci::ImageSpec& imageSpec) override;

    /**
     * Loads OCI runtime spec.
     *
     * @param path file path.
     * @param runtimeSpec runtime spec.
     * @return Error.
     */
    aos::Error LoadRuntimeSpec(const aos::String& path, aos::oci::RuntimeSpec& runtimeSpec) override;

    /**
     * Saves OCI runtime spec.
     *
     * @param path file path.
     * @param runtimeSpec runtime spec.
     * @return Error.
     */
    virtual aos::Error SaveRuntimeSpec(const aos::String& path, const aos::oci::RuntimeSpec& runtimeSpec) override;

private:
    static constexpr size_t cJsonMaxContentSize = 4096;

    aos::RetWithError<size_t> ReadFileContentToBuffer(const aos::String& path, size_t maxContentSize);
    aos::Error                WriteEncodedJsonBufferToFile(const aos::String& path, size_t len);

    aos::StaticBuffer<cJsonMaxContentSize> mJsonFileBuffer;
    aos::Mutex                             mMutex;
    RuntimeSpec                            mRuntimeSpec;
    ImageSpec                              mImageSpec;
};

#endif
