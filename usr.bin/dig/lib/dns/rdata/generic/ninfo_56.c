/*
 * Copyright (C) Internet Systems Consortium, Inc. ("ISC")
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef RDATA_GENERIC_NINFO_56_C
#define RDATA_GENERIC_NINFO_56_C

#define RRTYPE_NINFO_ATTRIBUTES (0)

static inline isc_result_t
totext_ninfo(ARGS_TOTEXT) {

	UNUSED(tctx);

	REQUIRE(rdata->type == dns_rdatatype_ninfo);

	return (generic_totext_txt(rdata, tctx, target));
}

static inline isc_result_t
fromwire_ninfo(ARGS_FROMWIRE) {

	REQUIRE(type == dns_rdatatype_ninfo);

	UNUSED(type);
	UNUSED(dctx);
	UNUSED(rdclass);
	UNUSED(options);

	return (generic_fromwire_txt(rdclass, type, source, dctx, options,
				     target));
}

static inline isc_result_t
towire_ninfo(ARGS_TOWIRE) {

	REQUIRE(rdata->type == dns_rdatatype_ninfo);

	UNUSED(cctx);

	return (mem_tobuffer(target, rdata->data, rdata->length));
}



static inline isc_result_t
tostruct_ninfo(ARGS_TOSTRUCT) {
	dns_rdata_ninfo_t *txt = target;

	REQUIRE(rdata->type == dns_rdatatype_ninfo);

	txt->common.rdclass = rdata->rdclass;
	txt->common.rdtype = rdata->type;
	ISC_LINK_INIT(&txt->common, link);

	return (generic_tostruct_txt(rdata, target));
}




#endif	/* RDATA_GENERIC_NINFO_56_C */
