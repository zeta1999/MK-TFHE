#include "tfhe_core.h"
#include "mkTFHEparams.h"
#include "polynomials.h"
#include "lwekey.h"
#include "tlwe.h"
#include "lweparams.h"
#include <new>
#include <stdlib.h>
#include <iostream>

#include "mkTFHEkeys.h"
#include "mkTFHEsamples.h"
#include "mkTFHEkeygen.h"

using namespace std;



MKLweKey::MKLweKey(const LweParams* LWEparams, const MKTFHEParams* MKparams): 
        LWEparams(LWEparams), MKparams(MKparams) {

    // A secret LWE key for each party
    key = new_LweKey_array(MKparams->parties, LWEparams);
}

MKLweKey::~MKLweKey() {
    delete_LweKey_array(MKparams->parties, key);
}



// allocate memory space 
EXPORT MKLweKey* alloc_MKLweKey() {
    return (MKLweKey*) malloc(sizeof(MKLweKey));
}
EXPORT MKLweKey* alloc_MKLweKey_array(int32_t nbelts) {
    return (MKLweKey*) malloc(nbelts*sizeof(MKLweKey));
}

// free memory space 
EXPORT void free_MKLweKey(MKLweKey* ptr) {
    free(ptr);
}
EXPORT void free_MKLweKey_array(int32_t nbelts, MKLweKey* ptr) {
    free(ptr);
}

// initialize the structure
EXPORT void init_MKLweKey(MKLweKey* obj, const LweParams* LWEparams, const MKTFHEParams* MKparams) {
    new(obj) MKLweKey(LWEparams, MKparams);
}
EXPORT void init_MKLweKey_array(int32_t nbelts, MKLweKey* obj, const LweParams* LWEparams, 
        const MKTFHEParams* MKparams)
    {
    for (int i = 0; i < nbelts; i++) {
        new(obj+i) MKLweKey(LWEparams, MKparams);
    }
}

// destroys the structure
EXPORT void destroy_MKLweKey(MKLweKey* obj) {
    obj->~MKLweKey();
}
EXPORT void destroy_MKLweKey_array(int32_t nbelts, MKLweKey* obj) {
    for (int i = 0; i < nbelts; i++) {
        (obj+i)->~MKLweKey();
    }
}
 
// new = alloc + init
EXPORT MKLweKey* new_MKLweKey(const LweParams* LWEparams, const MKTFHEParams* MKparams) {
    return new MKLweKey(LWEparams, MKparams);
}
EXPORT MKLweKey* new_MKLweKey_array(int32_t nbelts, const LweParams* LWEparams, const MKTFHEParams* MKparams) {
    MKLweKey* obj = alloc_MKLweKey_array(nbelts);
    init_MKLweKey_array(nbelts,obj,LWEparams,MKparams);
    return obj;
}

// delete = destroy + free
EXPORT void delete_MKLweKey(MKLweKey* obj) {
    delete obj;
}
EXPORT void delete_MKLweKey_array(int32_t nbelts, MKLweKey* obj) {
    destroy_MKLweKey_array(nbelts,obj);
    free_MKLweKey_array(nbelts,obj);
}


























MKRLweKey::MKRLweKey(const TLweParams* RLWEparams, const MKTFHEParams* MKparams): 
        RLWEparams(RLWEparams), MKparams(MKparams) {

    // A secret RLWE key for each party
    key = new_TLweKey_array(MKparams->parties, RLWEparams);
    
    // Public key for all the parties (T = TorusPoly of size N)
    // Pkey_{parties*d} is a=U(T^d) equal for all the parties
    // Pkey_{i*d} is the b_i = key_i*a + e_i \in T^d (i=0, ..., parties-1)
    Pkey = new_TorusPolynomial_array((1 + MKparams->parties)*MKparams->dg, RLWEparams->N);
}

MKRLweKey::~MKRLweKey() {
    delete_TLweKey_array(MKparams->parties, key);
    delete_TorusPolynomial_array((1 + MKparams->parties)*MKparams->dg, Pkey);
}


// allocate memory space 
EXPORT MKRLweKey* alloc_MKRLweKey() {
    return (MKRLweKey*) malloc(sizeof(MKRLweKey));
}
EXPORT MKRLweKey* alloc_MKRLweKey_array(int32_t nbelts) {
    return (MKRLweKey*) malloc(nbelts*sizeof(MKRLweKey));
}

// free memory space 
EXPORT void free_MKRLweKey(MKRLweKey* ptr) {
    free(ptr);
}
EXPORT void free_MKRLweKey_array(int32_t nbelts, MKRLweKey* ptr) {
    free(ptr);
}

// initialize the structure
EXPORT void init_MKRLweKey(MKRLweKey* obj, const TLweParams* RLWEparams, const MKTFHEParams* MKparams) {
    new(obj) MKRLweKey(RLWEparams, MKparams);
}
EXPORT void init_MKRLweKey_array(int32_t nbelts, MKRLweKey* obj, const TLweParams* RLWEparams, 
        const MKTFHEParams* MKparams)
    {
    for (int i = 0; i < nbelts; i++) {
        new(obj+i) MKRLweKey(RLWEparams, MKparams);
    }
}

// destroys the structure
EXPORT void destroy_MKRLweKey(MKRLweKey* obj) {
    obj->~MKRLweKey();
}
EXPORT void destroy_MKRLweKey_array(int32_t nbelts, MKRLweKey* obj) {
    for (int i = 0; i < nbelts; i++) {
        (obj+i)->~MKRLweKey();
    }
}
 
// new = alloc + init
EXPORT MKRLweKey* new_MKRLweKey(const TLweParams* RLWEparams, const MKTFHEParams* MKparams) {
    return new MKRLweKey(RLWEparams, MKparams);
}
EXPORT MKRLweKey* new_MKRLweKey_array(int32_t nbelts, const TLweParams* RLWEparams, const MKTFHEParams* MKparams) {
    MKRLweKey* obj = alloc_MKRLweKey_array(nbelts);
    init_MKRLweKey_array(nbelts,obj,RLWEparams,MKparams);
    return obj;
}

// delete = destroy + free
EXPORT void delete_MKRLweKey(MKRLweKey* obj) {
    delete obj;
}
EXPORT void delete_MKRLweKey_array(int32_t nbelts, MKRLweKey* obj) {
    destroy_MKRLweKey_array(nbelts,obj);
    free_MKRLweKey_array(nbelts,obj);
}





























/* *******************************************************
*************** Key Switching Key ************************
******************************************************* */

MKLweKeySwitchKey::MKLweKeySwitchKey(int32_t n_in, const MKTFHEParams* params, MKLweSample* ks0_raw){
    this->n_in = n_in;
    this->n_out = params->n;
    this->parties = params->parties;
    this->Bksbit = params->Bksbit;
    this->Bks = 1 << Bksbit;
    this->dks = params->dks;
    this->ks0_raw = ks0_raw;
    ks1_raw = new MKLweSample*[parties*n_in*dks];
    ks2_raw = new MKLweSample**[parties*n_in];
    ks = new MKLweSample***[parties];

    for (int i = 0; i < parties*n_in*dks; ++i)
    {
        ks1_raw[i] = ks0_raw + Bks*i;
    }
    for (int i = 0; i < parties*n_in; ++i)
    {
        ks2_raw[i] = ks1_raw + dks*i;
    }
    for (int i = 0; i < parties; ++i)
    {
        ks[i] = ks2_raw + n_in*i;
    }
}

MKLweKeySwitchKey::~MKLweKeySwitchKey() {
    delete[] ks1_raw;
    delete[] ks2_raw;
    delete[] ks;
}



// alloc 
EXPORT MKLweKeySwitchKey* alloc_MKLweKeySwitchKey() {
    return (MKLweKeySwitchKey*) malloc(sizeof(MKLweKeySwitchKey));
}
EXPORT MKLweKeySwitchKey* alloc_MKLweKeySwitchKey_array(int32_t nbelts) {
    return (MKLweKeySwitchKey*) malloc(nbelts*sizeof(MKLweKeySwitchKey));
}

// free memory space 
EXPORT void free_MKLweKeySwitchKey(MKLweKeySwitchKey* ptr) {
    free(ptr);
}
EXPORT void free_MKLweKeySwitchKey_array(int32_t nbelts, MKLweKeySwitchKey* ptr) {
    free(ptr);
}

// initialize the structure
EXPORT void init_MKLweKeySwitchKey(MKLweKeySwitchKey* obj, int32_t n_in, const LweParams* LWEparams, 
        const MKTFHEParams* params) 
{
    const int32_t parties = params->parties;
    const int32_t dks = params->dks;
    const int32_t Bksbit = params->Bksbit;
    const int32_t Bks = 1 << Bksbit;
    
    MKLweSample* ks0_raw = new_MKLweSample_array(parties*n_in*dks*Bks, LWEparams, params);
    new(obj) MKLweKeySwitchKey(n_in, params, ks0_raw);
}
EXPORT void init_MKLweKeySwitchKey_array(int32_t nbelts, MKLweKeySwitchKey* obj, int32_t n_in, 
        const LweParams* LWEparams, const MKTFHEParams* params) 
{
    for (int32_t i = 0; i < nbelts; i++) {
        init_MKLweKeySwitchKey(obj+i, n_in, LWEparams, params);
    }
}

// destroy 
EXPORT void destroy_MKLweKeySwitchKey(MKLweKeySwitchKey* obj) {
    const int32_t parties = obj->parties;
    const int32_t n_in = obj->n_in;
    const int32_t dks = obj->dks;
    const int32_t Bks = obj->Bks;
    
    delete_MKLweSample_array(parties*n_in*dks*Bks, obj->ks0_raw);
    obj->~MKLweKeySwitchKey();
}
EXPORT void destroy_MKLweKeySwitchKey_array(int32_t nbelts, MKLweKeySwitchKey* obj) {
    for (int32_t i = 0; i < nbelts; i++) {
        destroy_MKLweKeySwitchKey(obj+i);
    }
}

// new = alloc + init 
EXPORT MKLweKeySwitchKey* new_MKLweKeySwitchKey(int32_t n_in, const LweParams* LWEparams, const MKTFHEParams* params) {
    MKLweKeySwitchKey* obj = alloc_MKLweKeySwitchKey();
    init_MKLweKeySwitchKey(obj, n_in, LWEparams, params);
    return obj;
}
EXPORT MKLweKeySwitchKey* new_MKLweKeySwitchKey_array(int32_t nbelts, int32_t n_in, const LweParams* LWEparams, 
        const MKTFHEParams* params) {
    MKLweKeySwitchKey* obj = alloc_MKLweKeySwitchKey_array(nbelts);
    init_MKLweKeySwitchKey_array(nbelts, obj, n_in, LWEparams, params);
    return obj;
}

// delete = destroy + free 
EXPORT void delete_MKLweKeySwitchKey(MKLweKeySwitchKey* obj) {
    destroy_MKLweKeySwitchKey(obj);
    free_MKLweKeySwitchKey(obj);
}
EXPORT void delete_MKLweKeySwitchKey_array(int32_t nbelts, MKLweKeySwitchKey* obj) {
    destroy_MKLweKeySwitchKey_array(nbelts,obj);
    free_MKLweKeySwitchKey_array(nbelts,obj);
}
























/* *******************************************************
*************** Bootstrapping Key ************************
******************************************************* */


MKLweBootstrappingKey::MKLweBootstrappingKey(const MKTFHEParams* MKparams, 
        MKTGswExpSample* bk, 
        LweKeySwitchKey* ks): //MKLweKeySwitchKey* ks) :
        MKparams(MKparams), 
        bk(bk), 
        ks(ks) {}

MKLweBootstrappingKey::~MKLweBootstrappingKey() {}


// alloc
EXPORT MKLweBootstrappingKey *alloc_MKLweBootstrappingKey() {
    return (MKLweBootstrappingKey *) malloc(sizeof(MKLweBootstrappingKey));
}
EXPORT MKLweBootstrappingKey *alloc_MKLweBootstrappingKey_array(int32_t nbelts) {
    return (MKLweBootstrappingKey *) malloc(nbelts * sizeof(MKLweBootstrappingKey));
}

// free memory space 
EXPORT void free_MKLweBootstrappingKey(MKLweBootstrappingKey *ptr) {
    free(ptr);
}
EXPORT void free_MKLweBootstrappingKey_array(int32_t nbelts, MKLweBootstrappingKey *ptr) {
    free(ptr);
}

//initialize the structure
// in mkTFHEkeygen.h
// init_MKLweBootstrappingKey(MKLweBootstrappingKey *obj, const int32_t n_in, 
//        const LweParams* LWEparams, const TLweParams* RLWEparams, const MKTFHEParams* MKparams);
EXPORT void init_MKLweBootstrappingKey_array(int32_t nbelts, MKLweBootstrappingKey *obj, 
        const LweParams* LWEparams, const TLweParams* RLWEparams, const MKTFHEParams* MKparams) 
{
    for (int32_t i = 0; i < nbelts; i++) {
        init_MKLweBootstrappingKey(obj + i, LWEparams, RLWEparams, MKparams);
    }
}

// destroys the structure
// in mkTFHEkeygen.h
// destroy_MKLweBootstrappingKey(MKLweBootstrappingKey *obj);
EXPORT void destroy_MKLweBootstrappingKey_array(int32_t nbelts, MKLweBootstrappingKey *obj) {
    for (int32_t i = 0; i < nbelts; i++) {
        destroy_MKLweBootstrappingKey(obj + i);
    }
}

// new = alloc + init
EXPORT MKLweBootstrappingKey *new_MKLweBootstrappingKey(const LweParams* LWEparams, 
        const TLweParams* RLWEparams, const MKTFHEParams* MKparams) 
{
    MKLweBootstrappingKey *obj = alloc_MKLweBootstrappingKey();
    init_MKLweBootstrappingKey(obj, LWEparams, RLWEparams, MKparams);
    return obj;
}
EXPORT MKLweBootstrappingKey *new_MKLweBootstrappingKey_array(int32_t nbelts, 
        const LweParams* LWEparams, const TLweParams* RLWEparams, const MKTFHEParams* MKparams) 
{
    MKLweBootstrappingKey *obj = alloc_MKLweBootstrappingKey_array(nbelts);
    init_MKLweBootstrappingKey_array(nbelts, obj, LWEparams, RLWEparams, MKparams);
    return obj;
}

// delete = destroy + free
EXPORT void delete_MKLweBootstrappingKey(MKLweBootstrappingKey *obj) {
    destroy_MKLweBootstrappingKey(obj);
    free_MKLweBootstrappingKey(obj);
}
EXPORT void delete_MKLweBootstrappingKey_array(int32_t nbelts, MKLweBootstrappingKey *obj) {
    destroy_MKLweBootstrappingKey_array(nbelts, obj);
    free_MKLweBootstrappingKey_array(nbelts, obj);
}





























/*
 * MKLweBootstrappingKey is converted to a BootstrappingKeyFFT
 */
MKLweBootstrappingKeyFFT::MKLweBootstrappingKeyFFT(const MKTFHEParams* MKparams, 
        MKTGswExpSampleFFT* bkFFT, LweKeySwitchKey* ks) : 
        MKparams(MKparams), bkFFT(bkFFT), ks(ks) {}

MKLweBootstrappingKeyFFT::~MKLweBootstrappingKeyFFT() {}




// alloc
EXPORT MKLweBootstrappingKeyFFT *alloc_MKLweBootstrappingKeyFFT() {
    return (MKLweBootstrappingKeyFFT *) malloc(sizeof(MKLweBootstrappingKeyFFT));
}
EXPORT MKLweBootstrappingKeyFFT *alloc_MKLweBootstrappingKeyFFT_array(int32_t nbelts) {
    return (MKLweBootstrappingKeyFFT *) malloc(nbelts * sizeof(MKLweBootstrappingKeyFFT));
}

// free memory space 
EXPORT void free_MKLweBootstrappingKeyFFT(MKLweBootstrappingKeyFFT *ptr) {
    free(ptr);
}
EXPORT void free_MKLweBootstrappingKeyFFT_array(int32_t nbelts, MKLweBootstrappingKeyFFT *ptr) {
    free(ptr);
}

//initialize the structure
// in mkTFHEkeygen.h
// EXPORT void init_MKLweBootstrappingKeyFFT(MKLweBootstrappingKeyFFT *obj, LagrangeHalfCPolynomial *arr, const MKLweBootstrappingKey *bk,
//   const LweParams* LWEparams, const TLweParams* RLWEparams, const MKTFHEParams* MKparams);
EXPORT void init_MKLweBootstrappingKeyFFT_array(int32_t nbelts, MKLweBootstrappingKeyFFT *obj, 
        const MKLweBootstrappingKey *bk, const LweParams* LWEparams, 
        const TLweParams* RLWEparams, const MKTFHEParams* MKparams) 
{
    for (int32_t i = 0; i < nbelts; i++) {
        init_MKLweBootstrappingKeyFFT(obj + i, bk, LWEparams, RLWEparams, MKparams);
    }
}

// destroys the structure
// in mkTFHEkeygen.h
// EXPORT void destroy_MKLweBootstrappingKeyFFT(MKLweBootstrappingKeyFFT *obj);
EXPORT void destroy_MKLweBootstrappingKeyFFT_array(int32_t nbelts, MKLweBootstrappingKeyFFT *obj) {
    for (int32_t i = 0; i < nbelts; i++) {
        destroy_MKLweBootstrappingKeyFFT(obj + i);
    }
}

// new = alloc + init
EXPORT MKLweBootstrappingKeyFFT *new_MKLweBootstrappingKeyFFT(const MKLweBootstrappingKey *bk,  
        const LweParams* LWEparams, const TLweParams* RLWEparams, const MKTFHEParams* MKparams) 
{
    MKLweBootstrappingKeyFFT *obj = alloc_MKLweBootstrappingKeyFFT();
    init_MKLweBootstrappingKeyFFT(obj, bk, LWEparams, RLWEparams, MKparams);
    return obj;
}
EXPORT MKLweBootstrappingKeyFFT *new_MKLweBootstrappingKeyFFT_array(int32_t nbelts, const MKLweBootstrappingKey *bk,  
        const LweParams* LWEparams, const TLweParams* RLWEparams, const MKTFHEParams* MKparams) 
{
    MKLweBootstrappingKeyFFT *obj = alloc_MKLweBootstrappingKeyFFT_array(nbelts);
    init_MKLweBootstrappingKeyFFT_array(nbelts, obj, bk, LWEparams, RLWEparams, MKparams);
    return obj;
}

// delete = destroy + free
EXPORT void delete_MKLweBootstrappingKeyFFT(MKLweBootstrappingKeyFFT *obj) {
    destroy_MKLweBootstrappingKeyFFT(obj);
    free_MKLweBootstrappingKeyFFT(obj);
}
EXPORT void delete_MKLweBootstrappingKeyFFT_array(int32_t nbelts, MKLweBootstrappingKeyFFT *obj) {
    destroy_MKLweBootstrappingKeyFFT_array(nbelts, obj);
    free_MKLweBootstrappingKeyFFT_array(nbelts, obj);
}
 






