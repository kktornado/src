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

#ifndef RDATA_GENERIC_TALINK_58_C
#define RDATA_GENERIC_TALINK_58_C

#define RRTYPE_TALINK_ATTRIBUTES 0

static inline isc_result_t
totext_talink(ARGS_TOTEXT) {
	isc_region_t dregion;
	dns_name_t prev;
	dns_name_t next;
	dns_name_t prefix;
	isc_boolean_t sub;

	REQUIRE(rdata->type == dns_rdatatype_talink);
	REQUIRE(rdata->length != 0);

	dns_name_init(&prev, NULL);
	dns_name_init(&next, NULL);
	dns_name_init(&prefix, NULL);

	dns_rdata_toregion(rdata, &dregion);

	dns_name_fromregion(&prev, &dregion);
	isc_region_consume(&dregion, name_length(&prev));

	dns_name_fromregion(&next, &dregion);
	isc_region_consume(&dregion, name_length(&next));

	sub = name_prefix(&prev, tctx->origin, &prefix);
	RETERR(dns_name_totext(&prefix, sub, target));

	RETERR(str_totext(" ", target));

	sub = name_prefix(&next, tctx->origin, &prefix);
	return(dns_name_totext(&prefix, sub, target));
}

static inline isc_result_t
fromwire_talink(ARGS_FROMWIRE) {
	dns_name_t prev;
	dns_name_t next;

	REQUIRE(type == dns_rdatatype_talink);

	UNUSED(type);
	UNUSED(rdclass);

	dns_decompress_setmethods(dctx, DNS_COMPRESS_NONE);

	dns_name_init(&prev, NULL);
	dns_name_init(&next, NULL);

	RETERR(dns_name_fromwire(&prev, source, dctx, options, target));
	return(dns_name_fromwire(&next, source, dctx, options, target));
}

static inline isc_result_t
towire_talink(ARGS_TOWIRE) {
	isc_region_t sregion;
	dns_name_t prev;
	dns_name_t next;
	dns_offsets_t moffsets;
	dns_offsets_t roffsets;

	REQUIRE(rdata->type == dns_rdatatype_talink);
	REQUIRE(rdata->length != 0);

	dns_compress_setmethods(cctx, DNS_COMPRESS_NONE);

	dns_name_init(&prev, moffsets);
	dns_name_init(&next, roffsets);

	dns_rdata_toregion(rdata, &sregion);

	dns_name_fromregion(&prev, &sregion);
	isc_region_consume(&sregion, name_length(&prev));
	RETERR(dns_name_towire(&prev, cctx, target));

	dns_name_fromregion(&next, &sregion);
	isc_region_consume(&sregion, name_length(&next));
	return(dns_name_towire(&next, cctx, target));
}



static inline isc_result_t
tostruct_talink(ARGS_TOSTRUCT) {
	isc_region_t region;
	dns_rdata_talink_t *talink = target;
	dns_name_t name;
	isc_result_t result;

	REQUIRE(rdata->type == dns_rdatatype_talink);
	REQUIRE(target != NULL);
	REQUIRE(rdata->length != 0);

	talink->common.rdclass = rdata->rdclass;
	talink->common.rdtype = rdata->type;
	ISC_LINK_INIT(&talink->common, link);

	dns_rdata_toregion(rdata, &region);

	dns_name_init(&name, NULL);
	dns_name_fromregion(&name, &region);
	isc_region_consume(&region, name_length(&name));
	dns_name_init(&talink->prev, NULL);
	RETERR(name_duporclone(&name, &talink->prev));

	dns_name_fromregion(&name, &region);
	isc_region_consume(&region, name_length(&name));
	dns_name_init(&talink->next, NULL);
	result = name_duporclone(&name, &talink->next);
	if (result != ISC_R_SUCCESS)
		goto cleanup;

	return (ISC_R_SUCCESS);

 cleanup:
	dns_name_free(&talink->prev);
	return (ISC_R_NOMEMORY);
}




#endif	/* RDATA_GENERIC_TALINK_58_C */
