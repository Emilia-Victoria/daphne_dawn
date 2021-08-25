/*
 * Copyright 2021 The DAPHNE Consortium
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SRC_RUNTIME_LOCAL_KERNELS_SLICEROW_H
#define SRC_RUNTIME_LOCAL_KERNELS_SLICEROW_H

#include <runtime/local/context/DaphneContext.h>
#include <runtime/local/datastructures/DataObjectFactory.h>
#include <runtime/local/datastructures/DenseMatrix.h>
#include <runtime/local/datastructures/Frame.h>
#include <runtime/local/datastructures/ValueTypeCode.h>
#include <runtime/local/datastructures/ValueTypeUtils.h>

#include <stdexcept>

#include <cstddef>
#include <cstdint>

// ****************************************************************************
// Struct for partial template specialization
// ****************************************************************************

template<class DTRes, class DTArg>
struct SliceRow {
    static void apply(DTRes *& res, const DTArg * arg, size_t rowLowerIncl, size_t rowUpperExcl, DCTX(ctx)) = delete;
};

// ****************************************************************************
// Convenience function
// ****************************************************************************

template<class DTRes, class DTArg>
void sliceRow(DTRes *& res, const DTArg * arg, size_t rowLowerIncl, size_t rowUpperExcl, DCTX(ctx)) {
    SliceRow<DTRes, DTArg>::apply(res, arg, rowLowerIncl, rowUpperExcl, ctx);
}

// ****************************************************************************
// (Partial) template specializations for different data/value types
// ****************************************************************************

// ----------------------------------------------------------------------------
// DenseMatrix <- DenseMatrix
// ----------------------------------------------------------------------------

template<typename VT>
struct SliceRow<DenseMatrix<VT>, DenseMatrix<VT>> {
    static void apply(DenseMatrix<VT> *& res, const DenseMatrix<VT> * arg, size_t rowLowerIncl, size_t rowUpperExcl, DCTX(ctx)) {
        res = const_cast<DenseMatrix<VT> *>(arg)->slice(rowLowerIncl, rowUpperExcl);
    }        
};
#endif //SRC_RUNTIME_LOCAL_KERNELS_SLICEROW_H