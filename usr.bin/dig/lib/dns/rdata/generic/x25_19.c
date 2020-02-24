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

/* $Id: x25_19.c,v 1.7 2020/02/24 17:44:45 florian Exp $ */

/* Reviewed: Thu Mar 16 16:15:57 PST 2000 by bwelling */

/* RFC1183 */

#ifndef RDATA_GENERIC_X25_19_C
#define RDATA_GENERIC_X25_19_C

#define RRTYPE_X25_ATTRIBUTES (0)

static inline isc_result_t
totext_x25(ARGS_TOTEXT) {
	isc_region_t region;

	UNUSED(tctx);

	REQUIRE(rdata->type == dns_rdatatype_x25);
	REQUIRE(rdata->length != 0);

	dns_rdata_toregion(rdata, &region);
	return (txt_totext(&region, ISC_TRUE, target));
}

static inline isc_result_t
fromwire_x25(ARGS_FROMWIRE) {
	isc_region_t sr;

	REQUIRE(type == dns_rdatatype_x25);

	UNUSED(type);
	UNUSED(dctx);
	UNUSED(rdclass);
	UNUSED(options);

	isc_buffer_activeregion(source, &sr);
	if (sr.length < 5)
		return (DNS_R_FORMERR);
	return (txt_fromwire(source, target));
}

static inline isc_result_t
towire_x25(ARGS_TOWIRE) {
	UNUSED(cctx);

	REQUIRE(rdata->type == dns_rdatatype_x25);
	REQUIRE(rdata->length != 0);

	return (mem_tobuffer(target, rdata->data, rdata->length));
}



static inline isc_result_t
tostruct_x25(ARGS_TOSTRUCT) {
	dns_rdata_x25_t *x25 = target;
	isc_region_t r;

	REQUIRE(rdata->type == dns_rdatatype_x25);
	REQUIRE(target != NULL);
	REQUIRE(rdata->length != 0);

	x25->common.rdclass = rdata->rdclass;
	x25->common.rdtype = rdata->type;
	ISC_LINK_INIT(&x25->common, link);

	dns_rdata_toregion(rdata, &r);
	x25->x25_len = uint8_fromregion(&r);
	isc_region_consume(&r, 1);
	x25->x25 = mem_maybedup(r.base, x25->x25_len);
	if (x25->x25 == NULL)
		return (ISC_R_NOMEMORY);

	return (ISC_R_SUCCESS);
}




#endif	/* RDATA_GENERIC_X25_19_C */
