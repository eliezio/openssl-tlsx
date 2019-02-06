#ifndef HEADER_TLSX_H
#define HEADER_TLSX_H

#ifdef  __cplusplus
extern "C" {
#endif

#define TLSX_SERVER_NAME_INDICATION         0
#define TLSX_MAX_FRAGMENT_LENGTH            1
#define TLSX_CLIENT_CERTIFICATE_URL         2
#define TLSX_TRUSTED_CA_IDS                 3
#define TLSX_TRUNCATED_HMAC                 4
#define TLSX_CERTIFICATE_STATUS_REQUEST     5
#define TLSX_SERVER_CERTIFICATE_ID          10

#define TLSX_LAST_EXTENSION                 TLSX_SERVER_CERTIFICATE_ID

#define TLSX_MASK(e)                        (1 << (e))
#define TLSX_ALL_EXTENSIONS                 (TLSX_MASK (TLSX_LAST_EXTENSION + 1) - 1)

#define MAX_HOSTNAME_LEN                    255

#define MAX_URL_LEN                         255

#define TLSX_CERT_CHAIN_TYPE_INDIVIDUAL 0
#define TLSX_CERT_CHAIN_TYPE_PKIPATH        1

#define TLSX_CERT_ID_PRE_AGREED             0
#define TLSX_CERT_ID_KEY_SHA1_HASH          1
#define TLSX_CERT_ID_X509_NAME              2
#define TLSX_CERT_ID_CERT_SHA1_HASH         3

#define TLSX_TRUNCATED_HMAC_SIZE	    10

/*
 * Extended Alert Descriptions.
 */
#define TLSX_AD_UNSUPPORTED_EXTENSION                   110
#define TLSX_AD_CERTIFICATE_UNOBTAINABLE                111
#define TLSX_AD_UNRECOGNIZED_NAME                       112
#define TLSX_AD_BAD_CERTIFICATE_STATUS_RESPONSE         113
#define TLSX_AD_BAD_CERTIFICATE_HASH_VALUE              114

typedef struct certificate_url_st
    {
    char url [MAX_URL_LEN+1];
    int hash_present;
    unsigned char sha1hash [SHA_DIGEST_LENGTH];
    } CERTIFICATE_URL;

#define SK_CERTIFICATE_URL      STACK_OF(CERTIFICATE_URL)

typedef struct
    {
    int chain_type;
    SK_CERTIFICATE_URL *chain;
    } CERTIFICATE_CHAIN;

typedef struct
    {
    int type;
    union
        {
        BUF_MEM *subject;
        unsigned char sha1hash [SHA_DIGEST_LENGTH];
        } value;
    } CERT_ID;

#define SK_CERT_ID          STACK_OF(CERT_ID)
#define SK_X509             STACK_OF(X509)

typedef struct
	{
	/* Common variables. */
	int agreeded;		   	/* proposed and accepted extensions. */

	/* Client-side variables. */
	int wanted;			/* Intended extensions. */
	int required;          		/* Indicates which extensions are mandatory. */
	char *servername;
	unsigned int max_fragment_length_id;
	CERTIFICATE_CHAIN certificate_chain;
	SK_CERT_ID *trusted_ca_list;
	int truncated_hmac;
	SK_X509 *server_cert_chain;
	int server_cert_id_type;

	/* Server-side variables. */
	int allowed;			/* Permitted extensions. */
	int (*servername_cb) (SSL *, const char *, void *);
	void *servername_arg;
	int (*certificate_fetcher_cb) (SSL *, void *, const char *, unsigned char **, unsigned int *);
	void *certificate_fetcher_arg;
	SK_CERT_ID *cert_id_list;   	/* IDs received with the ClientHello message. */
	} TLS_EXTENSIONS;

/*
 * Client-side API.
 */
void TLSX_CTX_set_maximum_fragment_length(SSL_CTX *ctx, int frag_length);
void TLSX_CTX_set_servername_callback(SSL_CTX *ctx, int (*cb) (SSL *, const char *, void *), void *arg);
void TLSX_CTX_set_certificate_fetcher_callback(SSL_CTX *ctx, int (*cb) (SSL *, void *, const char *, unsigned char **, unsigned int *), void *arg);
void TLSX_CTX_allow (SSL_CTX *ctx, int mask);

void TLSX_set_servername(SSL *ssl, const char *server_name);

void TLSX_set_maximum_fragment_length(SSL *ssl, int frag_length);

void TLSX_cert_chain_empty(CERTIFICATE_CHAIN *cert_chain);
int  TLSX_cert_chain_add(CERTIFICATE_CHAIN *cert_chain, int cert_type, const char *url, const unsigned char *sha1hash);
void TLSX_set_certificate_chain(SSL *ssl, const CERTIFICATE_CHAIN *cert_chain);

void TLSX_set_trusted_ca(SSL *ssl, int id_type, const char *CAfile, const char *CApath);

void TLSX_enable_truncated_hmac(SSL *ssl);

SK_X509 *TLSX_get_cert_chain(SSL *ssl);
void TLSX_free_cert_chain(SK_X509 **chain);
void TLSX_set_server_cert_chain(SSL *ssl, SK_X509 *cert_chain, int id_type);

/*
 * Server-side API.
 */
void TLSX_allow (SSL *ssl, int mask);

#ifdef  __cplusplus
}
#endif
#endif
