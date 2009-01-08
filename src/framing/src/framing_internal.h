//
// Framing
//

#ifndef __LIQUID_FRAMING_INTERNAL_H__
#define __LIQUID_FRAMING_INTERNAL_H__

#include <stdbool.h>

#include "../../sequence/src/sequence.h"
#include "../../random/src/scramble.h"      // data randomizer
#include "../../fec/src/fec.h"              // fec_scheme
#include "../../interleaver/src/interleaver.h"
#include "../../modem/src/modem_common.h"

#include "framing.h"

struct frame_s {
    // options
    unsigned int phasing_pattern_length;
    unsigned int pn_sequence_length;
    unsigned int header_length;

    // header length, with crc and encoded
    unsigned int header_length_enc;

    // entire frame header length
    unsigned int frame_header_length;

    // private member objects
    bsequence pn; // p/n synchronization sequence
    bsequence rx; // received sequence
    unsigned char crc32_key[4];

    unsigned int src0;
    unsigned int src1;
    unsigned int dst0;
    unsigned int dst1;
    modulation_scheme ms; 
    unsigned int bps;
    fec_scheme fec_inner;
    fec_scheme fec_outer;
    unsigned int intlv_inner;
    unsigned int intlv_outer;

    unsigned int protocol;
    unsigned int msg_length;
    unsigned int num_symbols;
};


//
// packetizer
//

struct fecintlv_plan {
    unsigned int dec_msg_len;
    unsigned int enc_msg_len;

    // fec codec
    fec_scheme fs;
    fec f;

    // interleaver
    unsigned int intlv_scheme;
    interleaver q;
};

struct packetizer_s {
    unsigned int msg_len;
    unsigned int packet_len;

    unsigned int crc32_key;

    struct fecintlv_plan * plan;
    unsigned int plan_len;

    // buffers
    unsigned int buffer_len;
    unsigned char * buffer_0;
    unsigned char * buffer_1;
};

// reallocate memory for buffers
void packetizer_realloc_buffers(packetizer _p, unsigned int _len);

#endif // __LIQUID_FRAMING_INTERNAL_H__

